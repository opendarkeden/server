//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyStorm.cpp
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BloodyStorm.h"

#include "EffectBloodyStorm.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"
#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToTileOK6.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// ¹ìÆÄÀÌ¾î ¿ÀºêÁ§Æ® ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void BloodyStorm::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot,
                          CEffectID_t CEffectID)

{
    __BEGIN_TRY

    // cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

    // Vampire Object Assertion
    Assert(pVampire != NULL);
    Assert(pVampireSkillSlot != NULL);

    try {
        Zone* pZone = pVampire->getZone();
        Assert(pZone != NULL);

        Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
        // Assert(pTargetCreature != NULL);

        // NoSuchÁ¦°Å. by sigi. 2002.5.2
        if (pTargetCreature == NULL || !canAttack(pVampire, pTargetCreature) || pTargetCreature->isNPC()) {
            executeSkillFailException(pVampire, getSkillType());

            return;
        }

        execute(pVampire, pTargetCreature->getX(), pTargetCreature->getY(), pVampireSkillSlot, CEffectID);
    } catch (Throwable& t) {
        executeSkillFailException(pVampire, getSkillType());
        // cout << t.toString() << endl;
    }

    // cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¹ìÆÄÀÌ¾î Å¸ÀÏ ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void BloodyStorm::execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot,
                          CEffectID_t CEffectID)

{
    __BEGIN_TRY

    // cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

    try {
        Player* pPlayer = pVampire->getPlayer();
        Zone* pZone = pVampire->getZone();

        Assert(pPlayer != NULL);
        Assert(pZone != NULL);

        GCSkillToTileOK1 _GCSkillToTileOK1;
        GCSkillToTileOK2 _GCSkillToTileOK2;
        GCSkillToTileOK3 _GCSkillToTileOK3;
        GCSkillToTileOK4 _GCSkillToTileOK4;
        GCSkillToTileOK5 _GCSkillToTileOK5;
        GCSkillToTileOK6 _GCSkillToTileOK6;

        SkillType_t SkillType = pVampireSkillSlot->getSkillType();
        SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

        ZoneCoord_t myX = pVampire->getX();
        ZoneCoord_t myY = pVampire->getY();

        // Knowledge of Blood °¡ ÀÖ´Ù¸é hit bonus 10
        int HitBonus = 0;
        if (pVampire->hasRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD)) {
            RankBonus* pRankBonus = pVampire->getRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD);
            Assert(pRankBonus != NULL);

            HitBonus = pRankBonus->getPoint();
        }

        int RequiredMP = decreaseConsumeMP(pVampire, pSkillInfo);
        bool bManaCheck = hasEnoughMana(pVampire, RequiredMP);
        bool bTimeCheck = verifyRunTime(pVampireSkillSlot);
        bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());
        bool bHitRoll = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot, HitBonus);

        bool bTileCheck = false;

        VSRect rect(0, 0, pZone->getWidth() - 1, pZone->getHeight() - 1);

        if (rect.ptInRect(X, Y)) {
            Tile& tile = pZone->getTile(X, Y);
            if (tile.canAddEffect())
                bTileCheck = true;
        }

        if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bTileCheck) {
            decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

            // calculate damage and duration time
            SkillInput input(pVampire);
            SkillOutput output;
            computeOutput(input, output);

            // Disruption Storm ÀÌ ÀÖ´Ù¸é µ¥¹ÌÁö 20% Áõ°¡
            if (pVampire->hasRankBonus(RankBonus::RANK_BONUS_DISRUPTION_STORM)) {
                RankBonus* pRankBonus = pVampire->getRankBonus(RankBonus::RANK_BONUS_DISRUPTION_STORM);
                Assert(pRankBonus != NULL);

                output.Damage += getPercentValue(output.Damage, pRankBonus->getPoint());
            }

            Range_t Range = 3;

            // ±âÁ¸¿¡ °°Àº ÀÌÆåÆ®°¡ Å¸ÀÏ¿¡ ÀÖ´Ù¸é Áö¿ì°í »õ·Î ¼³Á¤ÇÑ´Ù.
            Tile& tile = pZone->getTile(X, Y);
            Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_BLOODY_STORM);
            if (pOldEffect != NULL) {
                ObjectID_t effectID = pOldEffect->getObjectID();
                pZone->deleteEffect(effectID);
            }

            // ÀÌÆåÆ® ¿ÀºêÁ§Æ®¸¦ »ý¼ºÇØ¼­ Å¸ÀÏ¿¡ ºÙÀÎ´Ù.
            EffectBloodyStorm* pEffect = new EffectBloodyStorm(pZone, X, Y);
            pEffect->setDeadline(output.Duration);
            pEffect->setNextTime(0);
            pEffect->setTick(output.Tick);
            pEffect->setUserObjectID(pVampire->getObjectID());
            pEffect->setDamage(output.Damage);
            pEffect->setLevel(pSkillInfo->getLevel() / 2);
            pEffect->setVampire();

            //
            ObjectRegistry& objectregister = pZone->getObjectRegistry();
            objectregister.registerObject(pEffect);

            //
            //
            pZone->addEffect(pEffect);
            tile.addEffect(pEffect);


            // ÀÌÆåÆ® ¹üÀ§³»ÀÇ ¸ðµç Creature¿¡°Ô effect¸¦ ºÙ¿©ÁØ´Ù.
            // Vampire°¡ ±â¼úÀ» »ç¿ëÇÑ °æ¿ì °°Àº Vampire¿¡°Ô´Â
            // ÇØ´çÇÏÁö ¾Ê´Â´Ù.
            // bool bEffected = false;
            Creature* pTargetCreature;


            list<Creature*> cList;
            cList.push_back(pVampire);

            int oX, oY;

            for (oX = -2; oX <= 2; oX++)
                for (oY = -2; oY <= 2; oY++) {
                    int tileX = X + oX;
                    int tileY = Y + oY;

                    // ¸¸¾à ÀÌÆåÆ®¸¦ Ãß°¡ÇÏ·Á´Â °÷ÀÌ Zone¿¡ ¼ÓÇØ ÀÖÁö ¾Ê´Ù¸é ³Ñ¾î°£´
                    if (!rect.ptInRect(tileX, tileY))
                        continue;

                    Tile& tile = pZone->getTile(tileX, tileY);

                    // ÇØ´ç Å¸ÀÏ¿¡ ÀÌÆåÆ®¸¦ Ãß°¡ÇÒ ¼ö ¾ø´Ù¸é ³Ñ¾î°£´Ù.
                    if (!tile.canAddEffect())
                        continue;

                    pTargetCreature = NULL;
                    if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
                        pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

                    if (pTargetCreature != NULL) {
                        // 2003. 1. 10. Sequoia
                        if (!checkZoneLevelToHitTarget(pTargetCreature))
                            continue;

                        if (pTargetCreature->isSlayer() || pTargetCreature->isOusters()) {
                            if (pEffect->affectCreature(pTargetCreature, false) == true) {
                                Player* pTargetPlayer = pTargetCreature->getPlayer();
                                // bEffected = true;

                                bool bCanSee = canSee(pTargetCreature, pVampire);

                                _GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
                                _GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
                                _GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

                                cList.push_back(pTargetCreature);

                                if (bCanSee) {
                                    // °ø°ÝÀ» ´çÇÑ »ç¶÷¿¡°Ô
                                    _GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
                                    _GCSkillToTileOK2.setSkillType(SkillType);
                                    _GCSkillToTileOK2.setX(X);
                                    _GCSkillToTileOK2.setY(Y);
                                    _GCSkillToTileOK2.setDuration(output.Duration);
                                    _GCSkillToTileOK2.setRange(Range);
                                    pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
                                }
                            }
                        } else if (pTargetCreature->isMonster()) {
                            if (pEffect->affectCreature(pTargetCreature, false) == true) {
                                Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
                                pMonster->addEnemy(pVampire);
                            }
                        }
                    } // if(pTargetCreature!= NULL)
                }

            // ±â¼úÀ» »ç¿ëÇÑ »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK1.setSkillType(SkillType);
            _GCSkillToTileOK1.setCEffectID(CEffectID);
            _GCSkillToTileOK1.setX(X);
            _GCSkillToTileOK1.setY(Y);
            _GCSkillToTileOK1.setDuration(output.Duration);
            _GCSkillToTileOK1.setRange(Range);

            // ±â¼úÀ» ¾´ »ç¶÷¸¸ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK3.setSkillType(SkillType);
            _GCSkillToTileOK3.setX(X);
            _GCSkillToTileOK3.setY(Y);

            // ±â¼úÀ» ´çÇÑ »ç¶÷¸¸ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK4.setSkillType(SkillType);
            _GCSkillToTileOK4.setX(X);
            _GCSkillToTileOK4.setY(Y);
            _GCSkillToTileOK4.setDuration(output.Duration);
            _GCSkillToTileOK4.setRange(Range);

            // ±â¼úÀ» ¾´ »ç¶÷°ú ´çÇÑ »ç¶÷À» ¸ðµÎ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
            _GCSkillToTileOK5.setSkillType(SkillType);
            _GCSkillToTileOK5.setX(X);
            _GCSkillToTileOK5.setY(Y);
            _GCSkillToTileOK5.setDuration(output.Duration);
            _GCSkillToTileOK5.setRange(Range);

            // ±â¼úÀ» »ç¿ëÇÑ »ç¶÷¿¡°Ô packet Àü´Þ
            pPlayer->sendPacket(&_GCSkillToTileOK1);

            // ±â¼úÀ» ¾µ »ç¶÷°ú ´çÇÑ »ç¶÷À» ¸ðµÎ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasing
            cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

            // ±â¼úÀ» ¾´ »ç¶÷À» º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasting
            pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

            // ±â¼úÀ» ´çÇÑ »ç¶÷À» º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasting
            pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

            // ±â¼ú delay setting
            pVampireSkillSlot->setRunTime(output.Delay);
        } else {
            executeSkillFailNormal(pVampire, getSkillType(), NULL);
        }
    } catch (Throwable& t) {
        executeSkillFailException(pVampire, getSkillType());
    }

    // cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¸ó½ºÅÍ Å¸ÀÏ ÇÚµé·¯
//////////////////////////////////////////////////////////////////////////////
void BloodyStorm::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y)

{
    __BEGIN_TRY

    // cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

    try {
        Zone* pZone = pMonster->getZone();

        Assert(pZone != NULL);

        GCSkillToTileOK1 _GCSkillToTileOK1;
        GCSkillToTileOK2 _GCSkillToTileOK2;
        GCSkillToTileOK3 _GCSkillToTileOK3;
        GCSkillToTileOK4 _GCSkillToTileOK4;
        GCSkillToTileOK5 _GCSkillToTileOK5;
        GCSkillToTileOK6 _GCSkillToTileOK6;

        SkillType_t SkillType = SKILL_BLOODY_STORM;
        SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

        ZoneCoord_t myX = pMonster->getX();
        ZoneCoord_t myY = pMonster->getY();


        bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());
        bool bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);

        bool bTileCheck = false;

        VSRect rect(0, 0, pZone->getWidth() - 1, pZone->getHeight() - 1);

        if (rect.ptInRect(X, Y)) {
            Tile& tile = pZone->getTile(X, Y);
            if (tile.canAddEffect())
                bTileCheck = true;
        }

        if (bRangeCheck && bHitRoll && bTileCheck) {
            // calculate damage and duration time
            SkillInput input(pMonster);
            SkillOutput output;
            computeOutput(input, output);

            Range_t Range = 3;

            // ±âÁ¸¿¡ °°Àº ÀÌÆåÆ®°¡ Å¸ÀÏ¿¡ ÀÖ´Ù¸é Áö¿ì°í »õ·Î ¼³Á¤ÇÑ´Ù.
            Tile& tile = pZone->getTile(X, Y);
            Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_BLOODY_STORM);
            if (pOldEffect != NULL) {
                ObjectID_t effectID = pOldEffect->getObjectID();
                pZone->deleteEffect(effectID);
            }

            // ÀÌÆåÆ® ¿ÀºêÁ§Æ®¸¦ »ý¼ºÇØ¼­ Å¸ÀÏ¿¡ ºÙÀÎ´Ù.
            EffectBloodyStorm* pEffect = new EffectBloodyStorm(pZone, X, Y);
            pEffect->setDeadline(output.Duration);
            pEffect->setNextTime(0);
            pEffect->setTick(output.Tick);
            pEffect->setDamage(output.Damage);
            pEffect->setUserObjectID(pMonster->getObjectID());
            pEffect->setLevel(pSkillInfo->getLevel() / 2);

            //
            ObjectRegistry& objectregister = pZone->getObjectRegistry();
            objectregister.registerObject(pEffect);

            //
            //
            pZone->addEffect(pEffect);
            tile.addEffect(pEffect);


            // ÀÌÆåÆ® ¹üÀ§³»ÀÇ ¸ðµç Creature¿¡°Ô effect¸¦ ºÙ¿©ÁØ´Ù.
            // Vampire°¡ ±â¼úÀ» »ç¿ëÇÑ °æ¿ì °°Àº Vampire¿¡°Ô´Â
            // ÇØ´çÇÏÁö ¾Ê´Â´Ù.
            // bool bEffected = false;
            Creature* pTargetCreature;


            list<Creature*> cList;
            cList.push_back(pMonster);

            int oX, oY;

            int range = 2;

            if (pMonster->isMaster()) {
                range = 4;
            }

            for (oX = -range; oX <= range; oX++)
                for (oY = -range; oY <= range; oY++) {
                    int tileX = X + oX;
                    int tileY = Y + oY;

                    // °Å¸®¸¦ ¹þ¾î³ª¸é Damage/2¸¸ Àû¿ëÇÑ´Ù.
                    if (oX <= -2 || oY <= -2 || oX >= 2 || oY >= 2)
                        pEffect->setDamage(output.Damage / 2);
                    else
                        pEffect->setDamage(output.Damage);

                    if (!rect.ptInRect(tileX, tileY))
                        continue;

                    Tile& tile = pZone->getTile(tileX, tileY);

                    if (!tile.canAddEffect())
                        continue;

                    pTargetCreature = NULL;
                    if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
                        pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

                    if (pTargetCreature != NULL
                        // °ø°Ý ´ë»óÀÌ ¸Â´ÂÁö È®ÀÎÇÑ´Ù.
                        && pMonster->isEnemyToAttack(pTargetCreature)) {
                        // 2003. 1. 10. Sequoia
                        if (!checkZoneLevelToHitTarget(pTargetCreature))
                            continue;

                        if (pTargetCreature->isPC()) {
                            if (pEffect->affectCreature(pTargetCreature, false) == true) {
                                Player* pTargetPlayer = pTargetCreature->getPlayer();
                                // bEffected = true;

                                bool bCanSee = canSee(pTargetCreature, pMonster);

                                _GCSkillToTileOK1.addCListElement(pTargetCreature->getObjectID());
                                _GCSkillToTileOK4.addCListElement(pTargetCreature->getObjectID());
                                _GCSkillToTileOK5.addCListElement(pTargetCreature->getObjectID());

                                cList.push_back(pTargetCreature);

                                if (bCanSee) {
                                    // °ø°ÝÀ» ´çÇÑ »ç¶÷¿¡°Ô
                                    _GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
                                    _GCSkillToTileOK2.setSkillType(SkillType);
                                    _GCSkillToTileOK2.setX(X);
                                    _GCSkillToTileOK2.setY(Y);
                                    _GCSkillToTileOK2.setDuration(output.Duration);
                                    _GCSkillToTileOK2.setRange(Range);
                                    pTargetPlayer->sendPacket(&_GCSkillToTileOK2);
                                }
                            }
                        } else if (pTargetCreature->isMonster()) {
                            if (pEffect->affectCreature(pTargetCreature, false) == true) {
                                Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
                                pMonster->addEnemy(pMonster);
                            }
                        }
                    } // if(pTargetCreature!= NULL)
                }

            // ±â¼úÀ» ¾´ »ç¶÷¸¸ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK3.setSkillType(SkillType);
            _GCSkillToTileOK3.setX(myX);
            _GCSkillToTileOK3.setY(myY);

            // ±â¼úÀ» ´çÇÑ »ç¶÷¸¸ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK4.setSkillType(SkillType);
            _GCSkillToTileOK4.setX(X);
            _GCSkillToTileOK4.setY(Y);
            _GCSkillToTileOK4.setDuration(output.Duration);
            _GCSkillToTileOK4.setRange(Range);

            // ±â¼úÀ» ¾´ »ç¶÷°ú ´çÇÑ »ç¶÷À» ¸ðµÎ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô
            _GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
            _GCSkillToTileOK5.setSkillType(SkillType);
            _GCSkillToTileOK5.setX(X);
            _GCSkillToTileOK5.setY(Y);
            _GCSkillToTileOK5.setDuration(output.Duration);
            _GCSkillToTileOK5.setRange(Range);

            // ±â¼úÀ» ¾µ »ç¶÷°ú ´çÇÑ »ç¶÷À» ¸ðµÎ º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasing
            cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

            // ±â¼úÀ» ¾´ »ç¶÷À» º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasting
            pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);

            // ±â¼úÀ» ´çÇÑ »ç¶÷À» º¼ ¼ö ÀÖ´Â »ç¶÷µé¿¡°Ô broadcasting
            pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

        } else {
            executeSkillFailNormal(pMonster, getSkillType(), NULL);
        }
    } catch (Throwable& t) {
        executeSkillFailException(pMonster, getSkillType());
    }


    // cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}
BloodyStorm g_BloodyStorm;
