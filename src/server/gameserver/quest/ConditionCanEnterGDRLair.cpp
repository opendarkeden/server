////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterGDRLair.cpp
// Written By  :
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ConditionCanEnterGDRLair.h"

#include "Effect.h"
#include "GCSystemMessage.h"
#include "GDRLairManager.h"
#include "Player.h"

////////////////////////////////////////////////////////////////////////////////
// is satisfied?
////////////////////////////////////////////////////////////////////////////////
bool ConditionCanEnterGDRLair::isSatisfied(Creature* pCreature1, Creature* pCreature2, void* pParam) const

{
    Assert(pCreature2 != NULL);
    Assert(pCreature2->isPC());

    //	return false;

    /*	if ( GDRLairManager::Instance().getTotalPCs() > 36 )
        {
            GCSystemMessage gcSystemMessage;
            gcSystemMessage.setMessage( "제한 인원이 초과되어 들어갈 수 없습니다." );
            pCreature2->getPlayer()->sendPacket (&gcSystemMessage);
            return false;
        }*/

    if (!GDRLairManager::Instance().canEnter()) {
        GCSystemMessage gcSystemMessage;
        gcSystemMessage.setMessage("훑댐흩契묵뻘청역폘.");
        pCreature2->getPlayer()->sendPacket(&gcSystemMessage);
        return false;
    }

    if (!pCreature2->isFlag(Effect::EFFECT_CLASS_CAN_ENTER_GDR_LAIR)) {
        GCSystemMessage gcSystemMessage;
        gcSystemMessage.setMessage("극伎돕呵쭝裂檢2꿔팎뻐謳찝薑채훙柯獗.");
        pCreature2->getPlayer()->sendPacket(&gcSystemMessage);
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void ConditionCanEnterGDRLair::read(PropertyBuffer& propertyBuffer)

{}

////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ConditionCanEnterGDRLair::toString() const

{
    __BEGIN_TRY

    StringStream msg;
    msg << "ConditionCanEnterGDRLair("
        << ")";
    return msg.toString();

    __END_CATCH
}
