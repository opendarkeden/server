/////////////////////////////////////////////////////////////////////////////
// Filename : MPacket.h
// Desc		: ���۽� �� ��Ŷ
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPACKET_H__
#define __MPACKET_H__


// include files
#include "Types.h"
#include "Exception.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

// packet size type
typedef int MPacketSize_t;
const unsigned int szMPacketSize = sizeof(MPacketSize_t);

// packet type
typedef int MPacketID_t;
const unsigned int szMPacketID = sizeof(MPacketID_t);

const unsigned int szMPacketHeader = szMPacketSize + szMPacketID;


class MPacket
{
public:
	virtual ~MPacket() = default;

	// ��Ŷ ���̵� ��ȯ�Ѵ�.
	virtual MPacketID_t getID() const = 0;

	// ��Ŷ�� ũ���� ��ȯ�Ѵ�.
	virtual MPacketSize_t getSize() const = 0;

	// ���ο� ��Ŷ�� �����ؼ� ��ȯ
	virtual MPacket* create() = 0;

	// �Է� ��Ʈ�����κ��� �����͸� �о ��Ŷ�� �ʱ�ȭ �Ѵ�.
	virtual void read( SocketInputStream& iStream ) = 0;

	// ��� ��Ʈ������ ��Ŷ�� ���̳ʸ� �̹����� ������.
	virtual void write( SocketOutputStream& oStream ) = 0;

	// debug message
	virtual string toString() const = 0;
};

#endif

