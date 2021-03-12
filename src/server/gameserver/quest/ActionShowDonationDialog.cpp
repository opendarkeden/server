////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowDonationDialog.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionShowDonationDialog.h"
#include "Creature.h"
#include "Player.h"

#include "Cpackets/CGDonationMoney.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionShowDonationDialog::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY

	try
	{
		m_Type = propertyBuffer.getProperty("Type");
	}
	catch (NoSuchElementException & nsee)
	{
		throw Error(nsee.toString());
	}

    __END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionShowDonationDialog::execute (Creature * pCreature1, Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_SHOW_DONATION_DIALOG );
	if ( m_Type == "Personal" )
		response.setParameter( DONATION_TYPE_200501_PERSONAL );
	else if ( m_Type == "Guild" )
		response.setParameter( DONATION_TYPE_200501_GUILD );

	pPlayer->sendPacket( &response );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionShowDonationDialog::toString () const
	
{
	__BEGIN_TRY

	string str = "ActionShowDonationDialog";

	return str;

	__END_CATCH
}
