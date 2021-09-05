//////////////////////////////////////////////////////////////////////////////
// Filename    : InstallTrap.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "InstallTrap.h"
#include "EffectTrapInstalled.h"

#include "ItemUtil.h"
#include "Zone.h"
#include "Tile.h"

#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCStatusCurrentHP.h"
#include "GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// �����̾� ����
//////////////////////////////////////////////////////////////////////////////
void InstallTrap::execute(Slayer * pSlayer, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// �����ϰ� �ִ� ���Ⱑ ���̰ų�, ���� �ƴ϶�� ����� �� �� ����.
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pWeapon == NULL || !isArmsWeapon(pWeapon))
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		// SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();
		Tile& rTile = pZone->getTile(X,Y);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = rTile.getEffect(Effect::EFFECT_CLASS_TRAP_INSTALLED) != NULL
						|| rTile.getEffect( Effect::EFFECT_CLASS_TRYING_POSITION ) != NULL;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// ����Ʈ Ŭ������ ����� ���δ�.
			EffectTrapInstalled* pEffect = new EffectTrapInstalled(pZone, X, Y);
			pEffect->setDeadline(output.Duration);
			pEffect->setUserOID( pSlayer->getObjectID() );
			pEffect->setTick(output.Tick);

			pZone->registerObject(pEffect);
			pZone->addEffect(pEffect);
			rTile.addEffect(pEffect);

			// ����ġ�� �ø���.
/*			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);
			if ( bIncreaseDomainExp )
			{
				shareAttrExp(pSlayer, ExpUp, 1, 8, 1, _GCSkillToSelfOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);
			}*/

			// ��Ŷ�� ����� ������.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);

			GCAddEffectToTile gcAddEffect;
			gcAddEffect.setXY(X, Y);
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_TRAP_INSTALLED);
			gcAddEffect.setObjectID(pEffect->getObjectID());
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(X, Y, &gcAddEffect);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(X, Y, &_GCSkillToSelfOK2, pSlayer);
		
			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
		//cout << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

InstallTrap g_InstallTrap;
