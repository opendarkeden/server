//////////////////////////////////////////////////////////////////////
//
// SocketInputStream.cpp
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "SocketInputStream.h"

#include <errno.h>

#include "Assert.h"
#include "Packet.h"

#if __LINUX__
#include <sys/ioctl.h>
#elif __WINDOWS__
#include <winsock.h>
#endif


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
SocketInputStream::SocketInputStream(Socket* sock, uint BufferLen)
    : m_pSocket(sock), m_Buffer(NULL), m_BufferLen(BufferLen), m_Head(0), m_Tail(0) {
    __BEGIN_TRY

    Assert(m_pSocket != NULL);
    Assert(m_BufferLen > 0);

    m_Buffer = new char[m_BufferLen];
    // add by viva 2008-12-31
    m_EncryptKey = 0;
    m_HashTable = NULL;
    // end

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
SocketInputStream::~SocketInputStream() noexcept {
    SAFE_DELETE_ARRAY(m_Buffer);
}


//////////////////////////////////////////////////////////////////////
//
// read data from input buffer
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::read(char* buf, uint len) {
    //	__BEGIN_TRY

    Assert(buf != NULL);

    if (len == 0)
        throw InvalidProtocolException("len==0");

    // ��û�� ��ŭ�� ����Ÿ�� ���۳��� �������� ���� ��� ���ܸ� ������.
    // ���� ��� read �� peek() �� üũ�� �� ȣ��ȴٸ�, �Ʒ� if-throw ��
    // �ߺ��� ���� �ִ�. ����, �ڸ�Ʈ�� ó���ص� �����ϴ�.
    // �� �Ʒ� �ڵ带 �ڸ�Ʈó���ϸ�, �ٷ� �Ʒ��� if-else �� 'if'-'else if'-'else'
    // �� ��������� �Ѵ�.
    if (len > length())
        throw InsufficientDataException(len - length());

    if (m_Head < m_Tail) { // normal order

        //
        //    H   T
        // 0123456789
        // ...abcd...
        //

        memcpy(buf, &m_Buffer[m_Head], len);

    } else { // reversed order ( m_Head > m_Tail )

        //
        //     T  H
        // 0123456789
        // abcd...efg
        //

        uint rightLen = m_BufferLen - m_Head;
        if (len <= rightLen) {
            memcpy(buf, &m_Buffer[m_Head], len);
        } else {
            memcpy(buf, &m_Buffer[m_Head], rightLen);
            memcpy(&buf[rightLen], m_Buffer, len - rightLen);
        }
    }

    m_Head = (m_Head + len) % m_BufferLen;

    return len;

    //	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// read data from input buffer
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::read(string& str, uint len) {
    __BEGIN_TRY

    if (len == 0)
        throw InvalidProtocolException("len==0");

    // ��û�� ��ŭ�� ����Ÿ�� ���۳��� �������� ���� ��� ���ܸ� ������.
    // ���� ��� read �� peek() �� üũ�� �� ȣ��ȴٸ�, �Ʒ� if-throw ��
    // �ߺ��� ���� �ִ�. ����, �ڸ�Ʈ�� ó���ص� �����ϴ�.
    // �� �Ʒ� �ڵ带 �ڸ�Ʈó���ϸ�, �ٷ� �Ʒ��� if-else �� if-else if-else
    // �� ��������� �Ѵ�.
    if (len > length())
        throw InsufficientDataException(len - length());

    // ��Ʈ�����ٰ� len ��ŭ ������ �̸� �Ҵ��Ѵ�.
    str.reserve(len);

    if (m_Head < m_Tail) { // normal order

        //
        //    H   T
        // 0123456789
        // ...abcd...
        //

        str.assign(&m_Buffer[m_Head], len);

    } else { // reversed order ( m_Head > m_Tail )

        //
        //     T  H
        // 0123456789
        // abcd...efg
        //

        uint rightLen = m_BufferLen - m_Head;
        if (len <= rightLen) {
            str.assign(&m_Buffer[m_Head], len);
        } else {
            str.assign(&m_Buffer[m_Head], rightLen);
            str.append(m_Buffer, len - rightLen);
        }
    }

    m_Head = (m_Head + len) % m_BufferLen;

    return len;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// read packet from input buffer
//////////////////////////////////////////////////////////////////////
void SocketInputStream::readPacket(Packet* pPacket) {
    __BEGIN_TRY

    // �̹� ���� �������� ID, Size�� �а� ID�� �´� ��Ŷ��ü��
    // ���� �Ķ���ͷ� �Ѱ����Ƿ� ID �� skip �Ѵ�. Size�� ��ü�� ���̳ʸ� �̹����� ���
    // �����ߴ����� üũ�һ�, ��ü�� �ʱ�ȭ�ʹ� �����ϱ� ������ skip �Ѵ�.
    skip(szPacketHeader);

    // ���� ���� ��Ŷ Ŭ������ ���ǵ� �޽�带 �����ϸ�,
    // ���ο��� �˾Ƽ� �� �ʱ�ȭ�ϰ� �ȴ�.
    // �� � ��Ŷ�� read()���� Ʋ���� �Ǹ� �� ������ ���
    // ��Ŷ�� �Ľ��� �Ұ����ϰ� �ȴ�. ����, ��Ŷ Ŭ������ �������� �� �����ؾ� �Ѵ�.
    // cout<<"Receive_before:"<<pPacket->toString()<<endl;
    pPacket->read(*this);
    cout << "Receive:" << pPacket->toString() << endl;
    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// peek data from buffer
//////////////////////////////////////////////////////////////////////
bool SocketInputStream::peek(char* buf, uint len) {
    //	__BEGIN_TRY

    Assert(buf != NULL);

    if (len == 0)
        throw InvalidProtocolException("len==0");

    // ��û�� ũ�⺸�� ������ ����Ÿ�� ���� ���, ���ܸ� ������.
    if (len > length())
        // throw InsufficientDataException( len - length() );
        //  NoSuch����. by sigi. 2002.5.4
        return false;

    // buf �� ����� �ϵ�, m_Head �� ��ȭ��Ű�� �ʴ´�.
    if (m_Head < m_Tail) { // normal order

        //
        //    H   T
        // 0123456789
        // ...abcd...
        //

        memcpy(buf, &m_Buffer[m_Head], len);

    } else { // reversed order ( m_Head > m_Tail )

        //
        //     T  H
        // 0123456789
        // abcd...efg
        //

        uint rightLen = m_BufferLen - m_Head;
        if (len <= rightLen) {
            memcpy(&buf[0], &m_Buffer[m_Head], len);
        } else {
            memcpy(&buf[0], &m_Buffer[m_Head], rightLen);
            memcpy(&buf[rightLen], &m_Buffer[0], len - rightLen);
        }
    }

    return true;
    //	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// skip data from buffer
//
// read(N) == peek(N) + skip(N)
//
//////////////////////////////////////////////////////////////////////
void SocketInputStream::skip(uint len) {
    __BEGIN_TRY

    if (len == 0)
        throw InvalidProtocolException("len==0");

    if (len > length())
        throw InsufficientDataException(len - length());

    // m_Head �� ������Ų��.
    m_Head = (m_Head + len) % m_BufferLen;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// fill buffer from socket
//
// ����Ÿ�� ���� ��� 0 �� �����Ѵ�.
// �׷���, NonBlocking �� ��� NonBlockingIOException �� ������.
//
// *NOTES*
//
// ���� ���� ����� �Լ����ٰ� char buf[N]; �� ������ �Ŀ� ����ٰ�
// receive() ������� ������ ��, ���ۿ� �����ϴ� ���̴�.
// �׷���, �� ����� ���簡 2ȸ �߻��ϱ� ������ ����Ǿ��
// �ϰڴ�.
//
// ����, ��Ʈ���� ���� ���ۿ��ٰ� ���� ��� �ϴµ�, �̶� ���� ���۰�
// circular �̹Ƿ�, normal order �� ��쿡�� 2ȸ �̻� receive()�� ȣ���
// Ȯ���� �ְ� �ȴ�.
//
// �̶� ù��° receive()���� ������ receive ������ ����Ÿ�� �� �о������,
// ���ÿ� ������ ���� ������ ��� �ι�° receive() ���� NonBlockingIOException
// �� �߻��ϰ� �ȴ�. (���� �̷� ���� �幰��. ������ ����
// �Ǿտ� ���ļ� ����Ÿ�� ���� ���� ���� �߻��Ѵ�
// ġ����..
// )
//
// ��. �̷� ��� fill()�� �ܺη� NonBlockingIOException �� ������ �ϴ°�?
// �ƴϸ� ���ݱ��� ���� ����Ÿ ũ�⸦ �����ؾ� �ϴ°�? ������ ���ڴ�. ^^;
// �� �� ����ξ�~~~ ������������~
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::fill() {
    __BEGIN_TRY

    uint nFilled = 0; // ���ۿ� ä������ ũ��
    uint nReceived;   // Socket::receive()�� �ѹ� �о���� ũ��
    uint nFree;       // ������ �� ������ ũ��

    if (m_Head <= m_Tail) { // normal order
                            // m_Head == m_Tail �� ���� ���۰� �� ���¸� ��Ÿ����.

        // �ϴ� ������ ������ �� �������� ä���.
        if (m_Head == 0) {
            //
            // H   T
            // 0123456789
            // abcd......
            //

            // ������ ����, m_Head == 0 �� ���, m_Tail �� ������ ���� ���Ƽ� �ٽ� 0 ����
            // �ǰ� �Ǹ� buffer empty �� ���� ���°� �ȴٴ� ���̴�. ����, m_Head �� üũ
            // �ؼ� 0 �� ��� m_Tail �� ���ؼ� ������ �� ������ ĭ�� ����־� �ϰڴ�. ^^

            nFree = m_BufferLen - m_Tail - 1;
            nReceived = m_pSocket->receive(&m_Buffer[m_Tail], nFree);

            // by sigi. NonblockException����. 2002.5.17
            if (nReceived == 0)
                return 0;
            // add by viva
            if (nReceived > 0)
                m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
            // end
            m_Tail += nReceived;
            nFilled += nReceived;

            if (nReceived == nFree) {
                // ������ receive ���ۿ� ����Ÿ�� �������� ���ɼ��� �ִ�.
                // �׷���, �Է� ���ۿ� ���� ������ �����Ƿ�
                // ����Ÿ�� ���� �ִٸ� ���۸� �������Ѿ� �Ѵ�.
                uint available = m_pSocket->available();
                if (available > 0) {
                    resize(available + 1);
                    // resize �Ǹ�, ������ ����Ÿ�� ���ĵǹǷ� m_Tail ���� ���� �ȴ�.
                    nReceived = m_pSocket->receive(&m_Buffer[m_Tail], available);

                    // by sigi. NonblockException����. 2002.5.17
                    if (nReceived == 0)
                        return 0;
                    // add by viva
                    if (nReceived > 0)
                        m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
                    // end
                    m_Tail += nReceived;
                    nFilled += nReceived;
                }
            }

        } else { // m_Head != 0

            //
            //    H   T
            // 0123456789
            // ...abcd...
            //

            // �� ���, m_Tail �� ������ �������� �Ѿ��
            // �����ϴ�.
            nFree = m_BufferLen - m_Tail;
            nReceived = m_pSocket->receive(&m_Buffer[m_Tail], nFree);

            // by sigi. NonblockException����. 2002.5.17
            if (nReceived == 0)
                return 0;
            // add by viva
            if (nReceived > 0)
                m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
            // end
            m_Tail = (m_Tail + nReceived) % m_BufferLen;
            nFilled += nReceived;

            if (nReceived == nFree) {
                Assert(m_Tail == 0);

                // ������ receive ���ۿ� ����Ÿ�� �� �������� ���ɼ��� �ִ�.
                // ����, �Է� ������ ���� ���� ������ ����Ÿ�� ������ �Ѵ�.
                // �� �̶����� m_Head == m_Tail �̸� empty �� �ǹǷ�,
                // -1 ���̵��� �Ѵ�.
                nFree = m_Head - 1;
                nReceived = m_pSocket->receive(&m_Buffer[0], nFree);

                // by sigi. NonblockException����. 2002.5.17
                if (nReceived == 0)
                    return 0;
                // add by viva
                if (nReceived > 0)
                    m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
                // end
                m_Tail += nReceived;
                nFilled += nReceived;

                if (nReceived == nFree) { // buffer is full

                    // ���۰� ���� �� ������ ���, ������ receive ���ۿ� ����Ÿ�� ��
                    // �������� ���ɼ��� �ִ�. ����, �о�� ��
                    // ������ ���۸� ������Ų��.
                    uint available = m_pSocket->available();
                    if (available > 0) {
                        resize(available + 1);
                        // resize �Ǹ�, ������ ����Ÿ�� ���ĵǹǷ� m_Tail ���� ���� �ȴ�.
                        nReceived = m_pSocket->receive(&m_Buffer[m_Tail], available);

                        // by sigi. NonblockException����. 2002.5.17
                        if (nReceived == 0)
                            return 0;
                        // add by viva
                        if (nReceived > 0)
                            m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
                        // end
                        m_Tail += nReceived;
                        nFilled += nReceived;
                    }
                }
            }
        }

    } else { // reversed order ( m_Head > m_Tail )

        //
        //     T  H
        // 0123456789
        // abcd...efg
        //

        nFree = m_Head - m_Tail - 1;
        nReceived = m_pSocket->receive(&m_Buffer[m_Tail], nFree);

        // by sigi. NonblockException����. 2002.5.17
        if (nReceived == 0)
            return 0;
        // add by viva
        if (nReceived > 0)
            m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
        // end
        m_Tail += nReceived;
        nFilled += nReceived;

        if (nReceived == nFree) { // buffer is full

            // �� ���, ������ receive ���ۿ� ����Ÿ�� �� ��������
            // ���ɼ��� �ִ�. ����, �о�� �� ������ ���۸�
            // ������Ų��.
            uint available = m_pSocket->available();
            if (available > 0) {
                resize(available + 1);
                // resize �Ǹ�, ������ ����Ÿ�� ���ĵǹǷ� m_Tail ���� ���� �ȴ�.
                nReceived = m_pSocket->receive(&m_Buffer[m_Tail], available);

                // by sigi. NonblockException����. 2002.5.17
                if (nReceived == 0)
                    return 0;
                // add by viva
                if (nReceived > 0)
                    m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail], nReceived);
                // end
                m_Tail += nReceived;
                nFilled += nReceived;
            }
        }
    }
    // add by viva 2008-12-31
    //	if(nFilled>0)
    //	{
    //		if(m_Tail>=nFilled)
    //			m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_Tail-nFilled], nFilled);
    //		else
    //		{
    //			m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[m_BufferLen - m_Tail], nFilled - m_Tail);
    //			m_EncryptKey = EncryptData(m_EncryptKey, &m_Buffer[0], m_Tail);
    //		}
    //	}
    // end
    return nFilled;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// fill buffer from socket
//
// ����Ʈ ��� - ���� �� ������. 0 -;
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::fill_RAW() {
    __BEGIN_TRY

#if __LINUX__
    uint nfree = m_BufferLen - m_Tail - 1;

    int nread = recv(m_pSocket->getSOCKET(), &m_Buffer[m_Tail], nfree, 0);

    if (nread < 0) {
        if (errno == EWOULDBLOCK) {
            // NonBlockingIOException
            nread = 0;
        } else if (errno == ECONNRESET) {
            // ConnectException
            throw ConnectException();
        } else {
            // Error
            throw UnknownError(strerror(errno), errno);
        }
    } else if (nread == 0) {
        // EOFException
        throw EOFException();
    }

    m_Tail += nread;

    if (nread == (int)nfree) {
        // ����Ÿ�� �� ���� ���ɼ��� �ִ�.
        uint more = 0;
        int result = ioctl(m_pSocket->getSOCKET(), FIONREAD, &more);
        if (result < 0)
            throw UnknownError(strerror(errno), errno);

        if (more > 0) {
            // ���۸� ������Ų��.
            resize(more + 1);

            // ���۸� ä���.
            nread = recv(m_pSocket->getSOCKET(), &m_Buffer[m_Tail], more, 0);

            // ������ more ��ŭ �о�� �Ѵ�. �׷��� ���� ���
            // ������.
            Assert((int)more == nread);

            nread += more;
        }
    }

    return nread;

#elif __WINDOWS__
    throw UnsupportedError();
#endif

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// resize buffer
//////////////////////////////////////////////////////////////////////
void SocketInputStream::resize(int size) {
    __BEGIN_TRY

    Assert(size != 0);

    // resize size����. by sigi. 2002.10.7
    size = max(size, (int)(m_BufferLen >> 1));
    uint newBufferLen = m_BufferLen + size;
    uint len = length();

    if (size < 0) {
        // ���� ũ�⸦ ���̷��µ� ���ۿ� ����ִ� ����Ÿ��
        // �� ����Ƴ� ���
        if (newBufferLen < 0 || newBufferLen < len)
            throw IOException("new buffer is too small!");
    }

    // �� ���۸� �Ҵ�޴´�.
    char* newBuffer = new char[newBufferLen];

    // ���� ������ ������ �����Ѵ�.
    if (m_Head < m_Tail) {
        //
        //    H   T
        // 0123456789
        // ...abcd...
        //

        memcpy(newBuffer, &m_Buffer[m_Head], m_Tail - m_Head);

    } else if (m_Head > m_Tail) {
        //
        //     T  H
        // 0123456789
        // abcd...efg
        //

        memcpy(newBuffer, &m_Buffer[m_Head], m_BufferLen - m_Head);
        memcpy(&newBuffer[m_BufferLen - m_Head], m_Buffer, m_Tail);
    }

    // ���� ���۸� �����Ѵ�.
    delete[] m_Buffer;

    // ???�� ���� ũ�⸦ �缳���Ѵ�.
    m_Buffer = newBuffer;
    m_BufferLen = newBufferLen;
    m_Head = 0;
    m_Tail = len; // m_Tail �� ����ִ� ����Ÿ�� ���̿� ����.

    ofstream ofile("buffer_resized.log", ios::app);
    ofile << "SocketInputStream resized " << size << " bytes!" << endl;
    ofile.close();

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get data's size in buffer
//
// NOTES
//
//       H   T           T  H
//    0123456789     0123456789
//    ...abcd...     abcd...efg
//
//    7 - 3 = 4      10 - ( 7 - 4 ) = 7
//
// CAUTION
//
//    m_Tail �� �� ĭ�� ����Ű�� �ִٴ� �Ϳ� �����϶�.
//    ������ ũ�Ⱑ m_BufferLen ��� ���� �� ť�� ��
//    �� �ִ� ����Ÿ�� ( m_BufferLen - 1 ) �� �ȴ�.
//
//////////////////////////////////////////////////////////////////////
uint SocketInputStream::length() const {
    __BEGIN_TRY

    if (m_Head < m_Tail)
        return m_Tail - m_Head;

    else if (m_Head > m_Tail)
        return m_BufferLen - m_Head + m_Tail;

    return 0;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get debug string
//////////////////////////////////////////////////////////////////////
string SocketInputStream::toString() const {
    StringStream msg;

    msg << "SocketInputStream("
        << "BufferLen:" << m_BufferLen << ",Head:" << m_Head << ",Tail:" << m_Tail << ")";

    return msg.toString();
}
// add by viva 2008-12-31
WORD SocketInputStream::EncryptData(WORD EncryptKey, char* buf, int len) {
    return EncryptKey;

    for (int i = 0; i < len; i++)
        *(buf + i) ^= 0xCC;

    if (m_HashTable == NULL)
        return EncryptKey;

    for (int i = 0; i < len; i++) {
        *(buf + i) ^= m_HashTable[EncryptKey];
        if (++EncryptKey == 512)
            EncryptKey = 0;
    }
    return EncryptKey;
}
// end
