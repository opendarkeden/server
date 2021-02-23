//////////////////////////////////////////////////////////////////////
// 
// SocketEncryptOutputStream.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __SOCKET_ENCRYPT_OUTPUT_STREAM_H__
#define __SOCKET_ENCRYPT_OUTPUT_STREAM_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "SocketOutputStream.h"
#include "Encrypter.h"

const unsigned int DefaultSocketEncryptOutputBufferSize = 81920;

//////////////////////////////////////////////////////////////////////
//
// class SocketEncryptOutputStream
//
//////////////////////////////////////////////////////////////////////

class SocketEncryptOutputStream : public SocketOutputStream {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	SocketEncryptOutputStream (Socket* sock, uint BufferSize = DefaultSocketEncryptOutputBufferSize) throw (Error);
	~SocketEncryptOutputStream () throw (Error);
	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public :
	
	// write data to stream (output buffer)
	// *CAUTION*
	// string 을 버퍼에 writing 할 때, 자동으로 size 를 앞에 붙일 수도 있다.
	// 그러나, string 의 크기를 BYTE/WORD 중 어느 것으로 할 건지는 의문이다.
	// 패킷의 크기는 작을 수록 좋다는 정책하에서 필요에 따라서 string size 값을
	// BYTE 또는 WORD 를 수동으로 사용하도록 한다.
    uint writeEncrypt (bool   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (char   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (uchar  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (short  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (ushort buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (int    buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (uint   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (long   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }
    uint writeEncrypt (ulong  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write(buf); }

/*    uint writeEncrypt (bool   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szbool  ); }
    uint writeEncrypt (char   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szchar  ); }
    uint writeEncrypt (uchar  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szuchar ); }
    uint writeEncrypt (short  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szshort ); }
    uint writeEncrypt (ushort buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szushort); }
    uint writeEncrypt (int    buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szint   ); }
    uint writeEncrypt (uint   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szuint  ); }
    uint writeEncrypt (long   buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szlong  ); }
    uint writeEncrypt (ulong  buf) throw (ProtocolException, Error) { buf = m_Encrypter.convert(buf); return write((const char*)&buf, szulong ); }
*/
	void	setEncryptCode(uchar code)	{ m_Encrypter.setCode(code); }
	uchar   getEncryptCode() const      { return m_Encrypter.getCode(); }

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private :
	Encrypter m_Encrypter;
	
};

#endif
