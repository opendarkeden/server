//////////////////////////////////////////////////////////////////////////////
// Filename    : SatelliteBomb.cpp
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "SatelliteBomb.h"

#include "EffectSatelliteBombAim.h"
#include "EffectSatelliteBombPoint.h"
#include "GCAddEffect.h"
#include "GCAddEffectToTile.h"
#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToTileOK6.h"
#include "ItemUtil.h"

//////////////////////////////////////////////////////////////////////////////
// ÈËÀà ÎÀÐÇºä»÷¼¼ÄÜ 180¼¶
//////////////////////////////////////////////////////////////////////////////
void SatelliteBomb::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)

{
    __BEGIN_TRY

    // Êý¾Ý°²È«ÑéÖ¤
    Assert(pSlayer != NULL);
    Assert(pSkillSlot != NULL);

    try {
        // »ñÈ¡µ±Ç°µØÍ¼,²¢½øÐÐ°²È«ÑéÖ¤.¸ù¾ÝÄ¿±êIDÈ¡µÃ¶ÔÏó
        Zone* pZone = pSlayer->getZone();
        Assert(pZone != NULL);

        Creature* pTargetCreature = pZone->getCreature(TargetObjectID);


        // ¼ì²âÄ¿±ê¹¥»÷¿ÉÄÜÐÔ
        if (pTargetCreature == NULL || !canAttack(pSlayer, pTargetCreature) || pTargetCreature->isNPC()) {
            // Í¨Öª¿Í»§¶ËÊ¹ÓÃ¼¼ÄÜÊ§°Ü
            executeSkillFailException(pSlayer, getSkillType());
            return;
        }
        // Ê¹ÓÃ¼¼ÄÜ
        execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
    }
    // ´íÎó´¦Àí
    catch (Throwable& t) {
        // Í¨Öª¿Í»§¶ËÊ¹ÓÃ¼¼ÄÜÊ§°Ü
        executeSkillFailException(pSlayer, getSkillType());
    }
    __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¼¼ÄÜÔËÐÐº¯Êý pSlayer->Ê¹ÓÃ¼¼ÄÜ¶ÔÏó  X,Y->×ø±ê pSkillSlot->¼¼ÄÜÐÅÏ¢  CEffectID->Ð§¹ûID
//////////////////////////////////////////////////////////////////////////////
void SatelliteBomb::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)

{
    __BEGIN_TRY

    try {
        // ¸ù¾ÝSlayer È¡µÃPlayer¶ÔÏóÖ¸Õë
        Player* pPlayer = pSlayer->getPlayer();
        // ¸ù¾ÝSlayer È¡µÃµ±Ç°µØÍ¼Ö¸Õë
        Zone* pZone = pSlayer->getZone();
        // ´íÎó´¦Àí
        Assert(pPlayer != NULL);
        Assert(pZone != NULL);

        // ¼ì²âÊÇ·ñÓÐ×°±¸ÎäÆ÷
        Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
        if (pItem == NULL || isArmsWeapon(pItem) == false) {
            // Í¨Öª¿Í»§¶ËÊ¹ÓÃ¼¼ÄÜÊ§°Ü
            executeSkillFailException(pSlayer, getSkillType());
            return;
        }

        GCSkillToTileOK1 _GCSkillToTileOK1;
        GCSkillToTileOK3 _GCSkillToTileOK3;
        GCSkillToTileOK4 _GCSkillToTileOK4;
        GCSkillToTileOK5 _GCSkillToTileOK5;
        GCSkillToTileOK6 _GCSkillToTileOK6;
        // »ñÈ¡µ±Ç°Ê¹ÓÃ¼¼ÄÜÀàÐÍ
        SkillType_t SkillType = pSkillSlot->getSkillType();
        // »ñÈ¡Êý¾Ý¿âµ±Ç°Ê¹ÓÃ¼¼ÄÜÐÅÏ¢
        SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

        // RequiredMP  »ñÈ¡¼¼ÄÜÐèÒªÏûºÄµÄMPÖµ.
        // bManaCheck  ¼ì²âµ±Ç°Ê¹ÓÃ¶ÔÏóÊÇ·ñÓÐ×ã¹»µÄMPÖµÏûºÄ.
        // bTimeCheck  ¼ì²âµ±Ç°¼¼ÄÜÊ¹ÓÃÊ±¼ä¼ä¸ôÊÇ·ñ³¬³ö.
        // bRangeCheck ¼ì²â¼¼ÄÜÊ¹ÓÃ¾àÀë.
        // bEffected   ¼ì²âµ±Ç°¼¼ÄÜÊÇ·ñÔÚÊ¹ÓÃÖÐ.
        // bTileCheck  ¼ì²âµ±Ç°µØÍ¼Ê¹ÓÃ¿ÉÄÜÐÔ
        int RequiredMP = pSkillInfo->getConsumeMP();
        bool bManaCheck = hasEnoughMana(pSlayer, RequiredMP);
        bool bTimeCheck = verifyRunTime(pSkillSlot);
        bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());
        bool bEffected = pSlayer->isFlag(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM);

        bool bTileCheck = false;
        VSRect rect(0, 0, pZone->getWidth() - 1, pZone->getHeight() - 1);
        if (rect.ptInRect(X, Y)) {
            Tile& tile = pZone->getTile(X, Y);
            if (tile.canAddEffect())
                bTileCheck = true;
        }
        bool bUseSkill = false;
        /*
        // È¡³öµ±Ç°Ê¹ÓÃ¼¼ÄÜ½ÇÉ«ËùÊ¹ÓÃµÄÎäÆ÷
        Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
        //Ã»ÓÐÎäÆ÷²»ÄÜÊ¹ÓÃ¼¼ÄÜ
        if (pWeapon != NULL)
        {
            Silver_t silverDamage= pWeapon->getSilver();
            if (silverDamage >50)
            {
                silverDamage-=50;
                pWeapon->setSilver(silverDamage);
                bUseSkill=true;
            }
        }
        */
        bUseSkill = true;
        // Èç¹ûÈ«²¿¼ì²âÍ¨¹ý,ÔòÖ´ÐÐ¼¼ÄÜº¯Êý.
        if (bManaCheck && bTimeCheck && bRangeCheck && !bEffected && bTileCheck && bUseSkill) {
            // ÉèÖÃÊ¹ÓÃ½ÇÉ«MP¼õÉÙ
            decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

            // ´´½¨¼¼ÄÜÊäÈëÊä³ö±äÁ¿,²¢¼ÆËã¼¼ÄÜÉËº¦µÈÐÅÏ¢.
            SkillInput input(pSlayer, pSkillSlot);
            SkillOutput output;
            computeOutput(input, output);

            Tile& tile = pZone->getTile(X, Y);

            // Èç¹ûEFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT¼¼ÄÜÐ§¹ûÔÚÊ¹ÓÃÖÐ,ÒÆ³ýÐ§¹û.
            Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT);
            if (pOldEffect != NULL) {
                ObjectID_t effectID = pOldEffect->getObjectID();
                pZone->deleteEffect(effectID);
            }

            // ´´½¨Ê¹ÓÃ½ÇÉ«Ð§¹û
            EffectSatelliteBombAim* pEffect = new EffectSatelliteBombAim(pSlayer, pZone, X, Y);
            // ÉèÖÃÐ§¹ûÉËº¦
            pEffect->setDamage(output.Damage);
            // ÉèÖÃÐ§¹ûÊ¹ÓÃÊ±¼ä
            pEffect->setDeadline(output.Duration);

            pSlayer->addEffect(pEffect);
            pSlayer->setFlag(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM);

            ZoneCoord_t myX = pSlayer->getX();
            ZoneCoord_t myY = pSlayer->getY();

            _GCSkillToTileOK1.setSkillType(SkillType);
            _GCSkillToTileOK1.setCEffectID(CEffectID);
            _GCSkillToTileOK1.setX(X);
            _GCSkillToTileOK1.setY(Y);
            _GCSkillToTileOK1.setDuration(output.Duration);
            _GCSkillToTileOK1.setRange(output.Range);

            _GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
            _GCSkillToTileOK3.setSkillType(SkillType);
            _GCSkillToTileOK3.setX(X);
            _GCSkillToTileOK3.setY(Y);

            _GCSkillToTileOK4.setSkillType(SkillType);
            _GCSkillToTileOK4.setX(X);
            _GCSkillToTileOK4.setY(Y);
            _GCSkillToTileOK4.setDuration(output.Duration);
            _GCSkillToTileOK4.setRange(output.Range);

            _GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
            _GCSkillToTileOK5.setSkillType(SkillType);
            _GCSkillToTileOK5.setX(X);
            _GCSkillToTileOK5.setY(Y);
            _GCSkillToTileOK5.setDuration(output.Duration);
            _GCSkillToTileOK5.setRange(output.Range);

            pPlayer->sendPacket(&_GCSkillToTileOK1);

            list<Creature*> cList;
            cList.push_back(pSlayer);

            cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

            pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);
            pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

            // SatelliteBombAim ÀÌÆåÆ®¸¦ ºê·ÎµåÄ³½ºÆÃ ÇÑ´Ù.
            GCAddEffect gcAddAimEffect;
            gcAddAimEffect.setObjectID(pSlayer->getObjectID());
            gcAddAimEffect.setEffectID(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM);
            gcAddAimEffect.setDuration(output.Duration);
            pZone->broadcastPacket(myX, myY, &gcAddAimEffect);

            ///////////////////////////////////////////////////////////////////
            // SatelliteBombPoint ÀÌÆåÆ®¸¦ ¸¸µé¾î¼­ ºÙÀÌ°í ºê·ÎµåÄ³½ºÆÃ ÇÑ´Ù.
            ///////////////////////////////////////////////////////////////////
            EffectSatelliteBombPoint* pPointEffect = new EffectSatelliteBombPoint(pZone, X, Y);
            pPointEffect->setDeadline(output.Duration);

            ObjectRegistry& objectRegister = pZone->getObjectRegistry();
            objectRegister.registerObject(pPointEffect);

            pZone->addEffect(pPointEffect);
            tile.addEffect(pPointEffect);

            GCAddEffectToTile gcAddEffectToTile;
            gcAddEffectToTile.setObjectID(pPointEffect->getObjectID());
            gcAddEffectToTile.setEffectID(pPointEffect->getEffectClass());
            gcAddEffectToTile.setXY(X, Y);
            gcAddEffectToTile.setDuration(output.Duration);

            pZone->broadcastPacket(X, Y, &gcAddEffectToTile);

            pSkillSlot->setRunTime(output.Delay);
        } else {
            executeSkillFailNormal(pSlayer, getSkillType(), NULL);
        }
    } catch (Throwable& t) {
        executeSkillFailException(pSlayer, getSkillType());
    }

    __END_CATCH
}

void SatelliteBomb::execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) {
    __BEGIN_TRY

    try {
        cout << pMonster->getName() << " use gunshotguiadance" << endl;
        Zone* pZone = pMonster->getZone();
        Assert(pZone != NULL);

        GCSkillToTileOK2 _GCSkillToTileOK2;
        GCSkillToTileOK3 _GCSkillToTileOK3;
        GCSkillToTileOK4 _GCSkillToTileOK4;
        GCSkillToTileOK5 _GCSkillToTileOK5;
        GCSkillToTileOK6 _GCSkillToTileOK6;

        SkillType_t SkillType = getSkillType();
        bool bTileCheck = false;
        VSRect rect(0, 0, pZone->getWidth() - 1, pZone->getHeight() - 1);
        if (rect.ptInRect(X, Y)) {
            Tile& tile = pZone->getTile(X, Y);
            if (tile.canAddEffect())
                bTileCheck = true;
        }

        if (bTileCheck) {
            Tile& tile = pZone->getTile(X, Y);

            ZoneCoord_t myX = pMonster->getX();
            ZoneCoord_t myY = pMonster->getY();

            // °°Àº ÀÌÆåÆ®°¡ ÀÌ¹Ì Á¸ÀçÇÑ´Ù¸é »èÁ¦ÇÑ´Ù.
            Effect* pOldEffect = tile.getEffect(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT);
            if (pOldEffect != NULL) {
                ObjectID_t effectID = pOldEffect->getObjectID();
                pZone->deleteEffect(effectID);
            }

            // µ¥¹ÌÁö¿Í Áö¼Ó ½Ã°£À» °è»êÇÑ´Ù.
            SkillInput input(pMonster);
            SkillOutput output;
            computeOutput(input, output);

            // ÀÌÆåÆ® ¿ÀºêÁ§Æ®¸¦ »ý¼ºÇÑ´Ù.
            EffectSatelliteBombAim* pEffect = new EffectSatelliteBombAim(pMonster, pZone, X, Y);
            pEffect->setDeadline(output.Duration);
            pEffect->setDamage(output.Damage);

            pMonster->setFlag(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM);
            pMonster->addEffect(pEffect);

            _GCSkillToTileOK3.setObjectID(pMonster->getObjectID());
            _GCSkillToTileOK3.setSkillType(SkillType);
            _GCSkillToTileOK3.setX(X);
            _GCSkillToTileOK3.setY(Y);

            _GCSkillToTileOK4.setSkillType(SkillType);
            _GCSkillToTileOK4.setX(X);
            _GCSkillToTileOK4.setY(Y);
            _GCSkillToTileOK4.setDuration(output.Duration);
            _GCSkillToTileOK4.setRange(1);

            _GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
            _GCSkillToTileOK5.setSkillType(SkillType);
            _GCSkillToTileOK5.setX(X);
            _GCSkillToTileOK5.setY(Y);
            _GCSkillToTileOK5.setDuration(output.Duration);
            _GCSkillToTileOK5.setRange(1);

            list<Creature*> cList;
            cList.push_back(pMonster);

            cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

            pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);
            pZone->broadcastPacket(X, Y, &_GCSkillToTileOK4, cList);

            // SatelliteBombAim ÀÌÆåÆ®¸¦ ºê·ÎµåÄ³½ºÆÃ ÇÑ´Ù.
            GCAddEffect gcAddAimEffect;
            gcAddAimEffect.setObjectID(pMonster->getObjectID());
            gcAddAimEffect.setEffectID(Effect::EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM);
            gcAddAimEffect.setDuration(output.Duration);
            pZone->broadcastPacket(myX, myY, &gcAddAimEffect);

            EffectSatelliteBombPoint* pPointEffect = new EffectSatelliteBombPoint(pZone, X, Y);
            pPointEffect->setDeadline(output.Duration);

            ObjectRegistry& objectRegister = pZone->getObjectRegistry();
            objectRegister.registerObject(pPointEffect);

            pZone->addEffect(pPointEffect);
            tile.addEffect(pPointEffect);

            GCAddEffectToTile gcAddEffectToTile;
            gcAddEffectToTile.setObjectID(pPointEffect->getObjectID());
            gcAddEffectToTile.setEffectID(pPointEffect->getEffectClass());
            gcAddEffectToTile.setXY(X, Y);
            gcAddEffectToTile.setDuration(output.Duration);

            pZone->broadcastPacket(X, Y, &gcAddEffectToTile);
        } else {
            executeSkillFailNormal(pMonster, getSkillType(), NULL);
        }
    } catch (Throwable& t) {
        executeSkillFailException(pMonster, getSkillType());
    }

    __END_CATCH
}

SatelliteBomb g_SatelliteBomb;
