/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayer.cpp
// Desc		: Mofus network player wrapper
/////////////////////////////////////////////////////////////////////////////

// include files
#include "MPlayer.h"

#include "Assert.h"
#include "MJob.h"
#include "MPacket.h"
#include "MPacketManager.h"
#include "Mofus.h"
#include "Properties.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

// include packet header
#include <unistd.h>

#include "PKTConnectAsk.h"
#include "PKTLogout.h"
#include "PKTReceiveOK.h"
#include "PKTResult.h"
#include "PKTSError.h"
#include "PKTUserInfo.h"

const int defaultMPlayerInputStreamSize = 10240;
const int defaultMPlayerOutputStreamSize = 10240;

// constructor
MPlayer::MPlayer(MJob* pJob) {
    Assert(pJob != NULL);

    m_pSocket = NULL;
    m_pInputStream = NULL;
    m_pOutputStream = NULL;

    m_pJob = pJob;
}

// destructor
MPlayer::~MPlayer() {
    // delete socket input stream
    SAFE_DELETE(m_pInputStream);

    // delete socket output stream
    SAFE_DELETE(m_pOutputStream);

    // delete socket
    if (m_pSocket != NULL) {
        m_pSocket->close();
        SAFE_DELETE(m_pSocket);

        filelog(MOFUS_LOG_FILE, "Close socket");
    }
}

void MPlayer::processInput() {
    try {
        m_pInputStream->fill();
    } catch (NonBlockingIOException& nibe) {
    }
}

void MPlayer::processOutput() {
    try {
        m_pOutputStream->flush();
    } catch (InvalidProtocolException&) {
        throw DisconnectException("Invalid packet");
    }
}

void MPlayer::processCommand() {
    __BEGIN_TRY

    try {
        // Continuously pull packets from the input stream and dispatch handlers.
        while (true) {
            // Peek packet header to read ID and size without consuming stream data.
            char header[szMPacketHeader];
            MPacketSize_t packetSize;
            MPacketID_t packetID;

            if (!m_pInputStream->peek(&header[0], szMPacketHeader))
                return;

            memcpy(&packetSize, &header[0], szMPacketSize);
            memcpy(&packetID, &header[szMPacketSize], szMPacketID);

            // packetSize = ntohl( packetSize );
            // packetID = ntohl( packetID );

            // Verify we have a handler for this packet ID.
            if (!g_pMPacketManager->hasHandler(packetID)) {
                filelog(MOFUS_ERROR_FILE, "Invalid PacketID : %d", packetID);
                throw ProtocolException("Invalid PacketID");
            }

            // Validate packet size.
            if (g_pMPacketManager->getPacketSize(packetID) != packetSize) {
                filelog(MOFUS_ERROR_FILE, "Invalid PacketSize : %d, expected size : %d", packetSize,
                        g_pMPacketManager->getPacketSize(packetID));
                throw ProtocolException("Invalid PacketSize");
            }

            // Ensure the input stream already holds the full packet payload.
            if (m_pInputStream->length() < (unsigned int)(packetSize + szMPacketSize))
                return;

            // Create the packet object.
            MPacket* pPacket = g_pMPacketManager->createPacket(packetID);

            // Fill the packet from the stream.
            pPacket->read(*m_pInputStream);

            // Execute the packet handler.
            g_pMPacketManager->execute(this, pPacket);
        }
    } catch (const InsufficientDataException&) {
        // Not enough data yet; wait for more.
    }

    __END_CATCH
}

void MPlayer::sendPacket(MPacket* pPacket) {
    Assert(pPacket != NULL);

    pPacket->write(*m_pOutputStream);
}

void MPlayer::connect() {
    // Must not already have an active socket.
    Assert(m_pSocket == NULL);

    // Load Mofus host/port from configuration.
    const string MofusIP = g_pConfig->getProperty("MofusIP");
    uint MofusPort = g_pConfig->getPropertyInt("MofusPort");

    try {
        // create socket
        m_pSocket = new Socket(MofusIP, MofusPort);

        // connect
        m_pSocket->connect();

        // make nonblocking socket
        m_pSocket->setNonBlocking(true);

        // make no-linger socket
        m_pSocket->setLinger(0);

        // Prepare buffered read/write streams on the socket.
        m_pInputStream = new SocketInputStream(m_pSocket, defaultMPlayerInputStreamSize);
        m_pOutputStream = new SocketOutputStream(m_pSocket, defaultMPlayerOutputStreamSize);

        cout << "connection to Mofus server established - " << MofusIP.c_str() << ":" << MofusPort << endl;
        filelog(MOFUS_LOG_FILE, "----- connection extablished(%s:%u) -----", MofusIP.c_str(), MofusPort);
    } catch (Throwable& t) {
        cout << "connect to Mofus server fail - " << MofusIP.c_str() << ":" << MofusPort << endl;
        filelog(MOFUS_LOG_FILE, "----- connecti fail(%s:%u) -----", MofusIP.c_str(), MofusPort);

        // Release socket resources on failure.
        try {
            SAFE_DELETE(m_pSocket);
        } catch (Throwable& t) {
            filelog(MOFUS_ERROR_FILE, "[socket release error] %s", t.toString().c_str());
        }

        // Back off briefly before retrying.
        usleep(1000000); // 1 second
    }
}

void MPlayer::disconnect(bool bDisconnected) {
    __BEGIN_TRY

    try {
        if (bDisconnected == UNDISCONNECTED) {
            m_pOutputStream->flush();
        }

        m_pSocket->close();
    } catch (InvalidProtocolException& t) {
        cerr << "MPlayer::disconnect() exception occur!!" << endl;
        cerr << t.toString() << endl;
        m_pSocket->close();
    }

    __END_CATCH
}

void MPlayer::process() {
    __BEGIN_TRY

    Assert(m_pJob != NULL);

    try {
        while (true) {
            usleep(100);

            // Attempt connection if the socket is not yet established.
            if (m_pSocket == NULL) {
                connect();

                // After connecting, send the initial connect packet.
                if (m_pSocket != NULL)
                    sendConnectAsk();
            }

            // If connected, process I/O and job state.
            if (m_pSocket != NULL) {
                __BEGIN_TRY

                if (getSocket()->getSockError()) {
                    filelog(MOFUS_ERROR_FILE, "[MPlayer socket error]");

                    // On socket errors, close everything and return.
                    m_pSocket->close();
                    SAFE_DELETE(m_pSocket);
                    SAFE_DELETE(m_pInputStream);
                    SAFE_DELETE(m_pOutputStream);

                    // Exit loop so caller can retry later.
                    cout << "return" << endl;
                    return;
                } else {
                    // When job is finished and output is empty, cleanly close and exit.
                    if (m_pJob->isEnd() && m_pOutputStream->isEmpty()) {
                        // Close streams and socket before returning.
                        m_pSocket->close();
                        SAFE_DELETE(m_pSocket);
                        SAFE_DELETE(m_pInputStream);
                        SAFE_DELETE(m_pOutputStream);

                        // Exit loop.
                        cout << "return" << endl;
                        return;
                    }

                    try {
                        // Drive input/command/output processing for this socket.
                        processInput();
                        processCommand();
                        processOutput();
                    } catch (ConnectException& ce) {
                        filelog(MOFUS_LOG_FILE, "----- connection close");

                        // On disconnect, close socket and streams before returning.
                        m_pSocket->close();
                        SAFE_DELETE(m_pSocket);
                        SAFE_DELETE(m_pInputStream);
                        SAFE_DELETE(m_pOutputStream);

                        cout << "return" << endl;
                        return;
                    } catch (Throwable& t) {
                        filelog(MOFUS_ERROR_FILE, "[MPlayer process error]");

                        // On processing error, close socket and streams before returning.
                        m_pSocket->close();
                        SAFE_DELETE(m_pSocket);
                        SAFE_DELETE(m_pInputStream);
                        SAFE_DELETE(m_pOutputStream);

                        cout << "return" << endl;
                        return;
                    }
                }

                __END_CATCH
            }
        }
    } catch (Throwable& t) {
        filelog("MPlayerManager.log", "MPlayerManager::run() %s", t.toString().c_str());
    }

    __END_CATCH
}

void MPlayer::sendConnectAsk() {
    PKTConnectAsk pkt;

    pkt.setOnGameCode(1);

    sendPacket(&pkt);

    cout << "--------------------------------------------------" << endl;
    cout << "SEND [" << m_pJob->getName() << "] ConnectAsk" << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "SEND [%s] ConnectAsk", m_pJob->getName().c_str());
    filelog(MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str());
}

void MPlayer::sendLogout() {
    PKTLogout pkt;

    sendPacket(&pkt);

    cout << "--------------------------------------------------" << endl;
    cout << "SEND [" << m_pJob->getName() << "] Logout" << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "SEND [%s] Logout", m_pJob->getName().c_str());
    filelog(MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str());
}

void MPlayer::sendUserInfo() {
    PKTUserInfo pkt;

    pkt.setCellNum(m_pJob->getCellNum());

    sendPacket(&pkt);

    cout << pkt.toString() << endl;

    cout << "--------------------------------------------------" << endl;
    cout << "SEND [" << m_pJob->getName() << "] UserInfo" << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "SEND [%s] UserInfo(cellnum:%s)", m_pJob->getName().c_str(), m_pJob->getCellNum().c_str());
    filelog(MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str());
}

void MPlayer::sendReceiveOK() {
    PKTReceiveOK pkt;

    sendPacket(&pkt);

    cout << "--------------------------------------------------" << endl;
    cout << "SEND [" << m_pJob->getName() << "] ReceiveOK" << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "SEND [%s] ReceiveOK", m_pJob->getName().c_str());
    filelog(MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str());
}

void MPlayer::sendResult() {
    PKTResult pkt;

    sendPacket(&pkt);

    cout << "--------------------------------------------------" << endl;
    cout << "SEND [" << m_pJob->getName() << "] Result" << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "SEND [%s] Result", m_pJob->getName().c_str());
    filelog(MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str());
}

void MPlayer::sendSError(int errorCode) {
    PKTSError pkt;

    pkt.setErrorCode(errorCode);

    sendPacket(&pkt);

    cout << "--------------------------------------------------" << endl;
    cout << "SEND [" << m_pJob->getName() << "] SError" << endl;
    cout << "--------------------------------------------------" << endl;

    filelog(MOFUS_LOG_FILE, "SEND [%s] SError", m_pJob->getName().c_str());
    filelog(MOFUS_PACKET_FILE, "SEND : [%s] %s", m_pJob->getName().c_str(), pkt.toString().c_str());
}

void MPlayer::addPowerPoint(int point) {
    Assert(m_pJob != NULL);

    m_pJob->addPowerPoint(point);
}

void MPlayer::setErrorCode(int errorCode) {
    Assert(m_pJob != NULL);

    m_pJob->setErrorCode(errorCode);
}

void MPlayer::setEnd(bool bEnd) {
    Assert(m_pJob != NULL);

    m_pJob->setEnd(bEnd);
}
