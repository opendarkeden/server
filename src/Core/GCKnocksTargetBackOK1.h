//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCKnocksTargetBackOK1.h 
// Written By  : elca@ewestsoft.com
// Description : 기술이 성공했을때 보내는 패킷을 위한 클래스 정의
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_KNOCKS_TARGET_BACK_OK_1_H__
#define __GC_KNOCKS_TARGET_BACK_OK_1_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ModifyInfo.h"
#include "PacketFactory.h"
#include "ModifyItemInfo.h"

//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1;
//
// 게임서버에서 클라이언트로 자신의 기술이 성공을 알려주기 위한 클래스
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1 : public ModifyInfo {

public :
	
	// constructor
	GCKnocksTargetBackOK1() ;
	
	// destructor
	~GCKnocksTargetBackOK1() ;

	
public :
	
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) ;
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const ;

	// execute packet's handler
	void execute(Player* pPlayer) ;

	// get packet id
	PacketID_t getPacketID() const  { return PACKET_GC_KNOCKS_TARGET_BACK_OK_1; }
	
	// get packet's body size
	// 최적화시, 미리 계산된 정수를 사용한다.
	PacketSize_t getPacketSize() const  { return szSkillType + szDir + szCoord*2 + szObjectID + szBullet + szbool + ModifyInfo::getPacketSize() ;}

	// get packet's name
	string getPacketName() const  { return "GCKnocksTargetBackOK1"; }
	
	// get packet's debug string
	string toString() const ;

	// get / set ObjectID
	ObjectID_t getObjectID() const  { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID)  { m_ObjectID = ObjectID; }

	// get / set Success
	bool getSkillSuccess() const  { return m_bSuccess; }
	void setSkillSuccess(bool Success)  { m_bSuccess = Success; }
	
	// get / set Bullet Num
	Bullet_t getBullet() const  { return m_BulletNum; }
	void setBulletNum(Bullet_t BulletNum) { m_BulletNum = BulletNum; }

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
	ObjectID_t m_ObjectID;

	// Bullet Num
	Bullet_t m_BulletNum;

	bool m_bSuccess;
	
	Coord_t m_X, m_Y;	// 이동된 좌표.
	Dir_t m_dir;		// 밀려난 방향.
	SkillType_t m_SkillType;
};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1Factory;
//
// Factory for GCKnocksTargetBackOK1
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1Factory : public PacketFactory {

public :
	
	// constructor
	GCKnocksTargetBackOK1Factory()  {}
	
	// destructor
	virtual ~GCKnocksTargetBackOK1Factory()  {}

	
public :
	
	// create packet
	Packet* createPacket()  { return new GCKnocksTargetBackOK1(); }

	// get packet name
	string getPacketName() const  { return "GCKnocksTargetBackOK1"; }
	
	// get packet id
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_KNOCKS_TARGET_BACK_OK_1; }

	// get Packet Max Size
	PacketSize_t getPacketMaxSize() const  { return szSkillType + szDir + szCoord*2 + szObjectID + szBullet + szbool + ModifyInfo::getPacketMaxSize(); }

};


//////////////////////////////////////////////////////////////////////
//
// class GCKnocksTargetBackOK1Handler;
//
//////////////////////////////////////////////////////////////////////

class GCKnocksTargetBackOK1Handler {

public :

	// execute packet's handler
	static void execute(GCKnocksTargetBackOK1* pGCKnocksTargetBackOK1, Player* pPlayer) ;

};

#endif
