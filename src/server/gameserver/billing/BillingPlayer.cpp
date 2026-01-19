//////////////////////////////////////////////////////////////////////
//
// Filename    : BillingPlayer.cpp
// Written By  : Reiot
//
//////////////////////////////////////////////////////////////////////

// include files
#include "BillingPlayer.h"

#include <exception>

#include "Assert.h"
#include "CommonBillingPacket.h"
#include "Packet.h"
#include "PacketFactoryManager.h"
#include "Properties.h"
#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#ifdef __GAME_SERVER__
#include "GamePlayer.h"
#include "PCFinder.h"
#elif defined(__LOGIN_SERVER__)
#include "LoginPlayer.h"
#endif

// by sigi. 2002.11.12
const int defaultBillingPlayerInputStreamSize = 10240;
const int defaultBillingPlayerOutputStreamSize = 10240;


//////////////////////////////////////////////////////////////////////
//
// constructor
//
//////////////////////////////////////////////////////////////////////
BillingPlayer::BillingPlayer()
//: m_pSocket(NULL), m_pInputStream(NULL), m_pOutputStream(NULL)
{}


BillingPlayer::BillingPlayer(Socket* pSocket)
//: Player( pSocket )//m_pSocket(pSocket), m_pInputStream(NULL), m_pOutputStream(NULL)
{
    __BEGIN_TRY

    Assert(pSocket != NULL);
    m_pSocket = pSocket;

    // create socket input stream
    m_pInputStream = new SocketInputStream(m_pSocket, defaultBillingPlayerInputStreamSize);
    Assert(m_pInputStream != NULL);

    // create socket output stream
    m_pOutputStream = new SocketOutputStream(m_pSocket, defaultBillingPlayerOutputStreamSize);
    Assert(m_pOutputStream != NULL);

    m_RetryCount = 0;
    m_RetryValue = 0;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
//////////////////////////////////////////////////////////////////////
BillingPlayer::~BillingPlayer() noexcept {
    try {
        // delete socket input stream
        SAFE_DELETE(m_pInputStream);

        // delete socket output stream
        SAFE_DELETE(m_pOutputStream);

        // delete socket
        if (m_pSocket != NULL) {
            m_pSocket->close();
            delete m_pSocket;
            m_pSocket = NULL;

            filelog(LOGFILE_BILLING_PLAYER, "Close Socket");
        }
    } catch (const std::exception&) {
        // ignore during teardown
    }
}


void BillingPlayer::processInput() {
    __BEGIN_TRY

    try {
        m_pInputStream->fill();
    } catch (NonBlockingIOException& nbie) {
    }

    __END_CATCH
}


void BillingPlayer::processOutput() {
    __BEGIN_TRY

    try {
        m_pOutputStream->flush();
    } catch (InvalidProtocolException&) {
        throw DisconnectException("Invalid packet");
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// parse packet and execute handler for the packet
//
//////////////////////////////////////////////////////////////////////
void BillingPlayer::processCommand() {
    __BEGIN_TRY

    try {
        // Legacy temporary storage when reading header and size separately.
        // char header[szPacketHeader];
        // PacketID_t packetID;
        // PacketSize_t packetSize;
        CommonBillingPacket cbPacket;

        // Process every full packet currently buffered; return when incomplete.
        while (true) {
            /*
            // Legacy flow: read only the header and bail if not enough data.
            if ( !m_pInputStream->peek( header , szPacketHeader ) )
                break;

            // Extract id and size from the header.
            memcpy( &packetID   , &header[0] , szPacketID );
            memcpy( &packetSize , &header[szPacketID] , szPacketSize );

            // Guard against invalid packet id values.
            if ( packetID >= Packet::PACKET_MAX )
                throw InvalidProtocolException("invalid packet id");

            // Reject payloads larger than allowed for the id.
            if ( packetSize > g_pPacketFactoryManager->getPacketMaxSize(packetID) )
                throw InvalidProtocolException("too large packet size");
            */

            // Ensure a full packet is buffered; otherwise wait for more data.
            // if ( m_pInputStream->length() < szPacketHeader + packetSize )
            if (m_pInputStream->length() < cbPacket.getPacketSize()) {
                // throw InsufficientDataException();
                return;
            }

            // Legacy: allocate the specific packet type once we knew the id.
            // pPacket = g_pPacketFactoryManager->createPacket( packetID );

            // Initialize and read a packet from the stream, then dispatch to handler.
            // The packet class implements read() via virtual methods so derived types
            // can populate themselves correctly.
            // m_pInputStream->read( pPacket );
            cbPacket.read(*m_pInputStream);

            // Execute the parsed packet. If the id was invalid, the handler will throw.
            // pPacket->execute( this );
            cbPacket.execute(this);

            // delete pPacket;
        }

    } catch (NoSuchElementException& nsee) {
        // PacketFactoryManager::createPacket(PacketID_t)
        // PacketFactoryManager::getPacketMaxSize(PacketID_t)
        // could both fail.
        throw Error(nsee.toString());

    } catch (const InsufficientDataException&) {
        // do nothing
    }
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// send packet to player's output buffer
//
//////////////////////////////////////////////////////////////////////
void BillingPlayer::sendPacket(Packet* pPacket) {
    __BEGIN_TRY

    // m_pOutputStream->write( pPacket );    // packetHeader is unnecessary.
    pPacket->write(*m_pOutputStream);

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// disconnect ( close socket )
//
//////////////////////////////////////////////////////////////////////
void BillingPlayer::disconnect(bool bDisconnected) {
    __BEGIN_TRY

    try {
        // If the player requested a disconnect, flush any pending output first.
        // Otherwise buffered data could trigger SIG_PIPE when the socket closes.
        if (bDisconnected == UNDISCONNECTED) {
            m_pOutputStream->flush();
        }

        m_pSocket->close();
    } catch (InvalidProtocolException& t) {
        cerr << "BillingPlayer::disconnect Exception Check!!" << endl;
        cerr << t.toString() << endl;
        m_pSocket->close();
        // throw Error("disconnect error");
    }

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// set socket
//////////////////////////////////////////////////////////////////////
void BillingPlayer::setSocket(Socket* pSocket) {
    __BEGIN_TRY

    m_pSocket = pSocket;

    if (m_pInputStream != NULL) {
        delete m_pInputStream;
        m_pInputStream = new SocketInputStream(m_pSocket);
    }

    if (m_pOutputStream != NULL) {
        delete m_pOutputStream;
        m_pOutputStream = new SocketOutputStream(m_pSocket);
    }

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Send the billing init packet.
//////////////////////////////////////////////////////////////////////
void BillingPlayer::sendPayInit() {
    __BEGIN_TRY

    CommonBillingPacket cbPacket;

    BillingInfo* pBillingInfo = &cbPacket;
    memset((char*)pBillingInfo, 0, sizeof(BillingInfo));

    cbPacket.setPacket_Type(BILLING_PACKET_INIT);
    cbPacket.setUser_CC();

    sendPacket(&cbPacket);

    filelog(LOGFILE_BILLING_PLAYER, "-------------------- send BillingInit --------------------");
    filelog(LOGFILE_BILLING_PLAYER, "%s", cbPacket.toString().c_str());

#ifdef __COUT_BILLING_SYSTEM__
    cout << "[send] BillingPlayer::sendPayInit" << endl;
#endif

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Check whether the character is still playing.
//////////////////////////////////////////////////////////////////////
void BillingPlayer::sendPayCheck(CommonBillingPacket* pPacket) {
    __BEGIN_TRY

#ifdef __COUT_BILLING_SYSTEM__
    cout << "BillingPlayer::sendPayCheck" << endl;
#endif

    string PlayerID = pPacket->User_ID;

    CommonBillingPacket cbPacket;


    BillingInfo* pBillingInfo = &cbPacket;
    memset((char*)pBillingInfo, 0, sizeof(BillingInfo));

    cbPacket.setPacket_Type(BILLING_PACKET_CHECK);
    cbPacket.setSession(pPacket->Session);

    // Verify whether the user is still online using PlayerID.
#ifdef __GAME_SERVER__
    Creature* pCreature = g_pPCFinder->getCreatureByID(PlayerID);
    bool isPlaying = (pCreature != NULL);
#else
    bool isPlaying = true;
#endif

    if (isPlaying) {
        cbPacket.setResult(BILLING_RESULT_CHECK_PLAYING);

        filelog(LOGFILE_BILLING_PLAYER, "SEND PayCheck : (%s) Playing", PlayerID.c_str());
    } else {
        cbPacket.setExpire_Date(PlayerID);
        cbPacket.setResult(BILLING_RESULT_CHECK_DISCONNECTED);

        filelog(LOGFILE_BILLING_PLAYER, "SEND PayCheck : Disconnected(%s, %s)", PlayerID.c_str(), cbPacket.Expire_Date);
    }

    cbPacket.setUser_CC();

    sendPacket(&cbPacket);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Send login billing info when a character is joining.
//////////////////////////////////////////////////////////////////////
void BillingPlayer::sendPayLogin(Player* pPlayer) {
    __BEGIN_TRY

    static int GameNo = g_pConfig->getPropertyInt("BillingGameNo");

    CommonBillingPacket cbPacket;

    BillingInfo* pBillingInfo = &cbPacket;
    memset((char*)pBillingInfo, 0, sizeof(BillingInfo));

#ifdef __GAME_SERVER__
    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

    if (pGamePlayer != NULL) {
        cbPacket.setPacket_Type(BILLING_PACKET_LOGIN);
        cbPacket.setSession(pGamePlayer->getBillingSession());
        cbPacket.setUser_CC();
        cbPacket.setUser_No(pGamePlayer->getBillingUserKey());
        cbPacket.setUser_ID(pGamePlayer->getID());
        cbPacket.setUser_IP(pGamePlayer->getSocket()->getHost());
        cbPacket.setGame_No(GameNo);

        // for TEST
        cbPacket.setExpire_Date(pPlayer->getID());

        int requestCount = pGamePlayer->getBillingLoginRequestCount();

        if (requestCount == 0) {
            filelog(LOGFILE_BILLING_PLAYER, "SEND PayLogin(%s)", pPlayer->getID().c_str());
        } else {
            filelog(LOGFILE_BILLING_PLAYER, "SEND PayLogin(%s) Retrying[%d]", pPlayer->getID().c_str(), requestCount);
        }

        sendPacket(&cbPacket);

#ifdef __COUT_BILLING_SYSTEM__
        cout << "[send] BillingPlayer::sendPayLogin (" << pPlayer->getID().c_str() << ") trying[" << requestCount << "]"
             << endl;
#endif
    } else {
        filelog(LOGFILE_BILLING_PLAYER, "ERROR Not GamePlayer(%s)", pPlayer->getID().c_str());
#ifdef __COUT_BILLING_SYSTEM__
        cout << "[ERROR] BillingPlayer::Not GamePlayer (" << pPlayer->getID().c_str() << ")" << endl;
#endif
    }


#elif defined(__LOGIN_SERVER__)

    LoginPlayer* pLoginPlayer = dynamic_cast<LoginPlayer*>(pPlayer);

    if (pLoginPlayer != NULL) {
        cbPacket.setPacket_Type(BILLING_PACKET_LOGIN_CHECK);
        cbPacket.setSession(pLoginPlayer->getBillingSession());
        cbPacket.setUser_CC();
        cbPacket.setUser_No(pLoginPlayer->getBillingUserKey());
        cbPacket.setUser_ID(pLoginPlayer->getID());
        cbPacket.setUser_IP(pLoginPlayer->getSocket()->getHost());
        cbPacket.setGame_No(GameNo);

        int requestCount = pLoginPlayer->getBillingLoginRequestCount();

        if (requestCount == 0) {
            filelog(LOGFILE_BILLING_PLAYER, "SEND PayLoginCheck(%s)", pPlayer->getID().c_str());
        } else {
            filelog(LOGFILE_BILLING_PLAYER, "SEND PayLoginCheck(%s) Retrying[%d]", pPlayer->getID().c_str(),
                    requestCount);

            if (requestCount > 1) {
                m_RetryCount++;
                m_RetryValue += requestCount;
            }
        }

        sendPacket(&cbPacket);

#ifdef __COUT_BILLING_SYSTEM__
        cout << "[send] BillingPlayer::sendPayLoginCheck (" << pPlayer->getID().c_str() << ") trying[" << requestCount
             << "]" << endl;
#endif
    } else {
        filelog(LOGFILE_BILLING_PLAYER, "ERROR Not GamePlayer(%s)", pPlayer->getID().c_str());
#ifdef __COUT_BILLING_SYSTEM__
        cout << "[ERROR] BillingPlayer::Not GamePlayer (" << pPlayer->getID().c_str() << ")" << endl;
#endif
    }

#endif

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Send logout billing info when a character leaves.
//////////////////////////////////////////////////////////////////////
void BillingPlayer::sendPayLogout(Player* pPlayer) {
    __BEGIN_TRY

    CommonBillingPacket cbPacket;

    BillingInfo* pBillingInfo = &cbPacket;
    memset((char*)pBillingInfo, 0, sizeof(BillingInfo));

#ifdef __GAME_SERVER__

    GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

    if (pGamePlayer != NULL) {
        cbPacket.setPacket_Type(BILLING_PACKET_LOGOUT);
        cbPacket.setSession(pGamePlayer->getBillingSession());
        cbPacket.setUser_CC();
        cbPacket.setUser_ID(pGamePlayer->getID());
        cbPacket.setUser_IP(pGamePlayer->getSocket()->getHost());
        cbPacket.setUser_Status(pGamePlayer->getBillingUserStatus());

        filelog(LOGFILE_BILLING_PLAYER, "SEND PayLogout(%s)", pPlayer->getID().c_str());
        sendPacket(&cbPacket);

#ifdef __COUT_BILLING_SYSTEM__
        cout << "[send] BillingPlayer::sendPayLogout (" << pPlayer->getID().c_str() << ")" << endl;
#endif
    } else {
        filelog(LOGFILE_BILLING_PLAYER, "ERROR Not GamePlayer(%s)", pPlayer->getID().c_str());
#ifdef __COUT_BILLING_SYSTEM__
        cout << "[ERROR] BillingPlayer::Not GamePlayer (" << pPlayer->getID().c_str() << ")" << endl;
#endif
    }

#endif


    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// get debug string
//
//////////////////////////////////////////////////////////////////////
string BillingPlayer::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "BillingPlayer("
        << "SocketID:" << m_pSocket->getSOCKET() << ",Host:" << m_pSocket->getHost() << ",ID:" << m_ID << ")";

    return msg.toString();

    __END_CATCH
}
