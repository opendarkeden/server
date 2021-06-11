//////////////////////////////////////////////////////////////////////////////
// Filename    : GCNPCAskVariable.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_NPC_ASK_VARIABLE_H__
#define __GC_NPC_ASK_VARIABLE_H__

#include <map>
#include "Packet.h"
#include "PacketFactory.h"
#include "ScriptParameter.h"

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskVariable;
// NPC 의 대사를 주변의 PC 들에게 전송한다.
//////////////////////////////////////////////////////////////////////////////

typedef map<string,ScriptParameter*>		HashMapScriptParameter;
typedef HashMapScriptParameter::iterator		HashMapScriptParameterItor;
typedef HashMapScriptParameter::const_iterator	HashMapScriptParameterConstItor;

class GCNPCAskVariable : public Packet
{
public:
	GCNPCAskVariable() ;
	virtual ~GCNPCAskVariable() ;

public:
	void read(SocketInputStream & iStream) ;
	void write(SocketOutputStream & oStream) const ;
	void execute(Player* pPlayer) ;
	PacketID_t getPacketID() const  { return PACKET_GC_NPC_ASK_VARIABLE; }
	PacketSize_t getPacketSize() const ;
	string getPacketName() const  { return "GCNPCAskVariable"; }
	string toString() const ;

public:
	ObjectID_t getObjectID(void) const  { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID)  { m_ObjectID = creatureID; }

	ScriptID_t getScriptID(void) const  { return m_ScriptID; }
	void setScriptID(ScriptID_t id)  { m_ScriptID = id; }

	void addScriptParameter(ScriptParameter* pParam ) throw(DuplicatedException);
	void clearScriptParameters() ;
	HashMapScriptParameter& getScriptParameters() { return m_ScriptParameters; }
	string getValue(const string& name ) const throw(NoSuchElementException);

private:
	ObjectID_t m_ObjectID; // NPC's object id
	ScriptID_t m_ScriptID; // script id
	HashMapScriptParameter m_ScriptParameters; // 스크립트의 변수 파라미터들
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskVariableFactory;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskVariableFactory : public PacketFactory 
{
public:
	Packet* createPacket()  { return new GCNPCAskVariable(); }
	string getPacketName() const  { return "GCNPCAskVariable"; }
	PacketID_t getPacketID() const  { return Packet::PACKET_GC_NPC_ASK_VARIABLE; }
	PacketSize_t getPacketMaxSize() const 
	{
		return szObjectID
			 + szScriptID
			 + szBYTE
			 + ScriptParameter::getMaxSize() * 255;
	}
};

//////////////////////////////////////////////////////////////////////////////
// class GCNPCAskVariableHandler;
//////////////////////////////////////////////////////////////////////////////

class GCNPCAskVariableHandler 
{
public:
	static void execute(GCNPCAskVariable* pPacket, Player* pPlayer) ;
};

#endif
