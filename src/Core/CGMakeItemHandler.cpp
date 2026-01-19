//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMakeItemHandler.cc
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGMakeItem.h"

#ifdef __GAME_SERVER__
#include "GCDeleteObject.h"
#include "GCDeleteandPickUpOK.h"
#include "GCSkillFailed1.h"
#include "GamePlayer.h"
#include "Item.h"
#include "SkillHandler.h"
#include "SkillHandlerManager.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "item/Money.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGMakeItemHandler::execute(CGMakeItem* pPacket, Player* pPlayer)

{
    __BEGIN_TRY __BEGIN_DEBUG_EX __BEGIN_DEBUG

#ifdef __GAME_SERVER__

    /*

    Assert(pPacket != NULL);
    Assert(pPlayer != NULL);

    ItemClass_t itemClass   = pPacket->getItemClass();

    SkillType_t SkillType = 0;
    switch(itemClass)
    {
        case Item::ITEM_CLASS_MINE:
            SkillType = SKILL_MAKE_MINE;
            break;

        case Item::ITEM_CLASS_BOMB:
            SkillType = SKILL_MAKE_BOMB;
            break;

        default:
            Assert(false);
    }

    try
    {
        GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
        Creature*   pPC         = pGamePlayer->getCreature();
        ItemType_t  itemType    = pPacket->getItemType();

        Zone* pZone = pPC->getZone();
        Assert(pZone != NULL);

        if (pPC->isSlayer())
        {
            Slayer*    pSlayer    = dynamic_cast<Slayer*>(pPC);
            SkillSlot* pSkillSlot = pSlayer->hasSkill(SkillType);
            bool       bSuccess   = true;

            if (pSkillSlot == NULL) bSuccess = false;
            if (pSlayer->isFlag(Effect::EFFECT_CLASS_PARALYZE)) bSuccess = false;
            if (pSlayer->isFlag(Effect::EFFECT_CLASS_HIDE)) bSuccess = false;

            if (pSlayer->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE))
            {
                addUnSnipingModeCreature(pZone, pSlayer, true);
            }

            if (bSuccess)
            {
                SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
                Assert(pSkillHandler != NULL);
                pSkillHandler->execute(pSlayer, pSkillSlot, itemType);
            }
            else
            {
                GCSkillFailed1 _GCSkillFailed1;
                _GCSkillFailed1.setSkillType(SkillType);
                pPlayer->sendPacket(&_GCSkillFailed1);
            }
        }
        else
        {
            GCSkillFailed1 _GCSkillFailed1;
            _GCSkillFailed1.setSkillType(SkillType);
            pPlayer->sendPacket(&_GCSkillFailed1);
        }
    }
    catch (Throwable & t)
    {
        //cout << t.toString() << endl;
    }
    */

#endif // __GAME_SERVER__

        __END_DEBUG __END_DEBUG_EX __END_CATCH
}
