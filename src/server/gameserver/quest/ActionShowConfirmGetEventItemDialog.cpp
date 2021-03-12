////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowConfirmGetEventItemDialog.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionShowConfirmGetEventItemDialog.h"
#include "Creature.h"
#include "Player.h"

#include "Cpackets/CGGetEventItem.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
// read from property buffer
////////////////////////////////////////////////////////////////////////////////
void ActionShowConfirmGetEventItemDialog::read (PropertyBuffer & propertyBuffer)
    
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
void ActionShowConfirmGetEventItemDialog::execute (Creature * pCreature1, Creature * pCreature2) 
	
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	Player* pPlayer = pCreature2->getPlayer();
	Assert(pPlayer != NULL);

	GCNPCResponse response;
	response.setCode( NPC_RESPONSE_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG );
	if ( m_Type == "ComebackItem" )
		response.setParameter( EVENT_TYPE_200501_COMBACK_ITEM );
	else if ( m_Type == "ComebackPremiumItem" )
		response.setParameter( EVENT_TYPE_200501_COMBACK_PREMIUM_ITEM );
	else if ( m_Type == "ComebackRecommendItem" )
		response.setParameter( EVENT_TYPE_200501_COMBACK_RECOMMEND_ITEM );
	else
		return;

	pPlayer->sendPacket( &response );

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionShowConfirmGetEventItemDialog::toString () const
	
{
	__BEGIN_TRY

	string str = "ActionShowConfirmGetEventItemDialog";

	return str;

	__END_CATCH
}
