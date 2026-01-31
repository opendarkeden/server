//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeavenGround.cpp
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#include "EffectHeavenGround.h"

#include "DB.h"
#include "EffectTrapTriggered.h"
#include "GCAddEffect.h"
#include "GCDeleteEffectFromTile.h"
#include "GCModifyInformation.h"
#include "GCStatusCurrentHP.h"
#include "GamePlayer.h"
#include "Monster.h"
#include "SkillUtil.h"
#include "Slayer.h"
#include "Tile.h"
#include "Vampire.h"
#include "Zone.h"
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectHeavenGround::EffectHeavenGround(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y)

{
    __BEGIN_TRY

    m_pZone = pZone;
    m_X = X;
    m_Y = Y;
    m_UserObjectID = 0;
    m_bSlayer = false;
    m_Damage = 0;
    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHeavenGround::affect()

{
    __BEGIN_TRY

    Assert(m_pZone != NULL);
    // cout << "UserObejctID:" << (int)m_UserObjectID << endl;
    //  »ñÈ¡Ê¹ÓÃ¼¼ÄÜµÄÈËÎï
    Creature* pCastCreature = m_pZone->getCreature(m_UserObjectID);

    if (pCastCreature == NULL) {
        setNextTime(m_Tick);

        return;
    }
    // Slayer* pSlayer = dynamic_cast<Slayer*>(pSlayer);

    // È¡³öµØÍ¼
    Tile& tile = m_pZone->getTile(m_X, m_Y);

    // »ñÈ¡µØÍ¼ÎïÆ·Á´±í
    const forward_list<Object*>& oList = tile.getObjectList();
    forward_list<Object*>::const_iterator itr = oList.begin();
    for (; itr != oList.end(); itr++) {
        Assert(*itr != NULL);

        Object* pObject = *itr;
        Assert(pObject != NULL);

        if (pObject->getObjectClass() == Object::OBJECT_CLASS_CREATURE) {
            Creature* pCreature = dynamic_cast<Creature*>(pObject);
            Assert(pCreature != NULL);

            // ¼ì²âµ±Ç°¶ÔÏóÊÇ·ñ¿É¹¥»÷
            if (!canAttack(pCastCreature, pCreature) || pCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_ACID) ||
                pCreature->isFlag(Effect::EFFECT_CLASS_COMA)) {
                continue;
            }

            // ¼ì²âµØÍ¼µÈ¼¶
            if (!checkZoneLevelToHitTarget(pCreature))
                continue;
            // ´´½¨ÉËº¦
            int AcidDamage = computeMagicDamage(pCreature, m_Damage, SKILL_HEAVEN_GROUND, m_bSlayer, pCastCreature);
            // ¿ÕÖÐµÄ²»¹¥»÷
            if (pCreature->getMoveMode() != Creature::MOVE_MODE_FLYING) {
                GCModifyInformation gcAttackerMI;
                GCModifyInformation gcDefenderMI;
                // Èç¹ûÊÇÈËÀà,Ôò²»»áÔì³ÉÉËº¦
                if (pCreature->isSlayer()) {
                    continue;
                    // setNextTime(m_Tick);
                    // return;
                } else if (pCreature->isVampire()) {
                    Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

                    ::setDamage(pVampire, AcidDamage, pCastCreature, SKILL_HEAVEN_GROUND, &gcDefenderMI, &gcAttackerMI,
                                false);

                    Player* pPlayer = pVampire->getPlayer();
                    Assert(pPlayer != NULL);
                    pPlayer->sendPacket(&gcDefenderMI);
                } else if (pCreature->isOusters()) {
                    Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

                    ::setDamage(pOusters, AcidDamage, pCastCreature, SKILL_HEAVEN_GROUND, &gcDefenderMI, &gcAttackerMI,
                                false);

                    Player* pPlayer = pOusters->getPlayer();
                    Assert(pPlayer != NULL);
                    pPlayer->sendPacket(&gcDefenderMI);
                } else if (pCreature->isMonster()) {
                    Monster* pMonster = dynamic_cast<Monster*>(pCreature);

                    ::setDamage(pMonster, AcidDamage, pCastCreature, SKILL_HEAVEN_GROUND, NULL, &gcAttackerMI, false);
                }

                bool modifiedAttacker = false;

                // Á×¾úÀ¸¸é °æÇèÄ¡ÁØ´Ù. À½.....
                // 				if ( pCastCreature != NULL )
                // 				{
                // 					if (pCreature->isDead() && pCastCreature->isVampire())
                // 					{
                // 						//computeAlignmentChange(pCreature, AcidDamage, pSlayer, &gcDefenderMI,
                // &gcAttackerMI);
                // 						//decreaseDurability(pSlayer, pCreature, NULL, &gcAttackerMI, &gcDefenderMI);
                //
                // 						// Å¸°ÙÀÌ ½½·¹ÀÌ¾î°¡ ¾Æ´Ñ °æ¿ì¿¡¸¸ °æÇèÄ¡¸¦ ¿Ã·ÁÁØ´Ù.
                // 						if (!pCreature->isSlayer())
                // 						{
                // // 							//shareAttrExp(pSlayer, AcidDamage , 1, 1, 8, _GCSkillToObjectOK1);
                // // 							increaseDomainExp(pSlayer, SKILL_HEAVEN_GROUND, pSkillInfo->getPoint(),
                // gcAttackerMI, pTargetCreature->getLevel());
                // // 							increaseSkillExp(pSlayer, SKILL_HEAVEN_GROUND,  pSkillSlot, pSkillInfo,
                // gcAttackerMI);
                // // 							increaseAlignment(pSlayer, pCreature, gcAttackerMI);
                // 						}
                // 						modifiedAttacker = true;
                // 					}
                // 				}

                // ¼ºÇâ °è»êÇÏ±â
                if (pCastCreature != NULL && pCastCreature->isPC() && pCreature->isPC()) {
                    computeAlignmentChange(pCreature, AcidDamage, pCastCreature, &gcDefenderMI, &gcAttackerMI);
                    modifiedAttacker = true;
                }

                if (modifiedAttacker)
                    pCastCreature->getPlayer()->sendPacket(&gcAttackerMI);
            }
        }
    }

    setNextTime(m_Tick);

    // cout << "EffectAcidSwamp" << "affect END" << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHeavenGround::affect(Zone* pZone, ZoneCoord_t Cx, ZoneCoord_t Cy)

{
    __BEGIN_TRY

    Assert(pZone != NULL);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectHeavenGround::unaffect()

{
    __BEGIN_TRY

    Tile& tile = m_pZone->getTile(m_X, m_Y);
    tile.deleteEffect(m_ObjectID);

    GCDeleteEffectFromTile gcDeleteEffect;
    gcDeleteEffect.setXY(m_X, m_Y);
    gcDeleteEffect.setObjectID(getObjectID());
    gcDeleteEffect.setEffectID(getSendEffectClass());

    m_pZone->broadcastPacket(m_X, m_Y, &gcDeleteEffect);

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectHeavenGround::toString() const throw() {
    __BEGIN_TRY

    StringStream msg;
    msg << "EffectHeavenGround("
        << ")";
    return msg.toString();

    __END_CATCH
}
