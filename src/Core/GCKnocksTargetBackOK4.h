//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK4.h 
// Written By  : elca@ewestsoft.com
// Description : 기술 피해자는 볼 수 있고, 사용자는 볼 수 없는 사람에게 보내는 패킷
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_KNOCKS_TARGET_BACK_OK_4_H__
#define __GC_KNOCKS_TARGET_BACK_OK_4_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK4;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK4 : public Packet {

public :
	
	// constructor
	GCKnocksTargetBackOK4() ;
	
	// destructor
	~GCKnocksTargetBackOK4() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_KNOCKS_TARGET_BACK_OK_4; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
//	PacketSize_t getPacketSize() const  { return szObjectID + szObjectID + szbool; }
	PacketSize_t getPacketSize() const  { return szObjectID + szSkillType 
		+ szCoord*2 + szDir; }

	// get packet's name
	string getPacketName() const  { return "GCKnocksTargetBackOK4"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set ObjectID
//	ObjectID_t getObjectID() const  { return m_ObjectID; }
//	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set ObjectID
	ObjectID_t getTargetObjectID() const  { return m_TargetObjectID; }
	void setTargetObjectID(ObjectID_t TargetObjectID)  { m_TargetObjectID = TargetObjectID; }
//	Coord_t getTargetX() const  { return m_X;}
//	Coord_t getTargetY() const  { return m_Y;}
//	void setTargetXY(Coord_t X, Coord_t Y)  { m_X = X; m_Y = Y;}

	// get / set success
//	bool getSkillSuccess() const  { return m_bSuccess;}
//	void setSkillSuccess(bool bSuccess)  { m_bSuccess = bSuccess;}
//	
    void setXYDir(Coord_t x, Coord_t y, Coord_t dir) 
    {
        m_X = x; m_Y = y; m_dir = dir;
    }
    Coord_t getX() const  { return m_X;}
    Coord_t getY() const  { return m_Y;}
    Dir_t getDir() const  { return m_dir;}
	SkillType_t getSkillType() const  { return m_SkillType;}
	void setSkillType(SkillType_t s)  { m_SkillType = s;}

private :
	
	// ObjectID
//	ObjectID_t m_ObjectID;
//	Coord_t m_X, m_Y;

	// TargetObjectID
	ObjectID_t m_TargetObjectID;
	
    Coord_t m_X, m_Y;   // 이동된 좌표.
    Dir_t m_dir;        // 밀려난 방향.
    SkillType_t m_SkillType;
			
	// bool
//	bool m_bSuccess;

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK4Factory;
//
// Factory for GCKnocksTargetBackOK4
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK4Factory : public PacketFactory {

public :
	
	// constructor
	GCKnocksTargetBackOK4Factory()  {}
	
	// destructor
	virtual ~GCKnocksTargetBackOK4Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCKnocksTargetBackOK4(); }

	// get packet name
	string getPacketName() const  { return "GCKnocksTargetBackOK4"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_KNOCKS_TARGET_BACK_OK_4; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szObjectID + szSkillType + szDir + szCoord*2; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK4Handler;
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK4Handler {

public :

	// execute packet's handler
	static void execute(GCKnocksTargetBackOK4* pGCKnocksTargetBackOK4, Player* pPlayer) ;

};

#endif
