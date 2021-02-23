#include "PetInfo.h"

PetInfo::PetInfo()
{
	m_PetType=PET_NONE;
	m_PetLevel=0;
	m_PetLevel=0;
	m_PetExp=0;
	m_PetHP=0;
	m_PetAttr=0;
	m_PetOption=0;
	m_IsSummonInfo = 0;

	m_CanCutHead = 0;
	m_CanAttack = 0;
	m_CanGamble = 0;

//#ifdef __GAME_SERVER__
	m_FeedTurn = 1;
	m_CurrentFeedTurn = 0;
//#endif
}

void PetInfo::read(SocketInputStream& iStream) throw(ProtocolException, Error)
{
	__BEGIN_TRY

	iStream.read( m_PetType );

	if ( m_PetType == PET_NONE ) return;

	iStream.read( m_PetCreatureType );
	iStream.read( m_PetLevel );
	iStream.read( m_PetExp );

	iStream.read( m_PetHP );
	iStream.read( m_PetAttr );
	iStream.read( m_PetAttrLevel );
	iStream.read( m_PetOption );
	iStream.read( m_PetFoodType );

	iStream.read( m_CanGamble );
	iStream.read( m_CanCutHead );
	iStream.read( m_CanAttack );

	iStream.read( m_IsSummonInfo );
	
	BYTE szSTR;
	iStream.read( szSTR );
	if ( szSTR != 0 ) iStream.read( m_Nickname, szSTR );

	ObjectID_t ItemObjectID;
	iStream.read( ItemObjectID );

	__END_CATCH
}

void PetInfo::write(SocketOutputStream& oStream) const throw(ProtocolException, Error)
{
	__BEGIN_TRY

	oStream.write( m_PetType );

	if ( m_PetType == PET_NONE ) return;

	oStream.write( m_PetCreatureType );
	oStream.write( m_PetLevel );
	oStream.write( m_PetExp );

	oStream.write( m_PetHP );
	oStream.write( m_PetAttr );
	oStream.write( m_PetAttrLevel );
	oStream.write( m_PetOption );
	oStream.write( m_PetFoodType );

	oStream.write( m_CanGamble );
	oStream.write( m_CanCutHead );
	oStream.write( m_CanAttack );

	oStream.write( m_IsSummonInfo );

	BYTE szSTR = m_Nickname.size();
	oStream.write( szSTR );
	if ( szSTR != 0 ) oStream.write( m_Nickname );

	ObjectID_t ItemObjectID = getItemObjectID();
	oStream.write( ItemObjectID );

	__END_CATCH
}

string PetInfo::toString() const
{
	StringStream msg;
	
	msg << "PetInfo("
		<< "PetType : " << (int)m_PetType
		<< ", PetLevel : " << (int)m_PetLevel
		<< ", PetExp : " << (int)m_PetExp
		<< ", PetHP : " << (int)m_PetHP
		<< ", PetAttr : " << (int)m_PetAttr
		<< ", PetOption : " << (int)m_PetOption
		<< ", PetFoodType : " << (int)m_PetFoodType
		<< ")";

	return msg.toString();
}
