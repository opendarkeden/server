//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCureCriticalWounds.cpp
// Written by  : elca
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "EffectCureCriticalWounds.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "ZoneUtil.h"
#include "HitRoll.h"

#include "Gpackets/GCModifyInformation.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCRemoveEffect.h"
#include "EffectBloodDrain.h"
#include "EffectAftermath.h"
#include "SkillInfo.h"
#include "SkillUtil.h"

const uint CriticalBloodDrainLevel = 74;

EffectCureCriticalWounds::EffectCureCriticalWounds(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pCreature);
	m_Range = 0;

	__END_CATCH
}

void EffectCureCriticalWounds::affect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature *>(m_pTarget);
	affect(pCreature);

	__END_CATCH 
}

void EffectCureCriticalWounds::affect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	GCSkillToSelfOK1 _GCSkillToSelfOK1;
	GCSkillToSelfOK2 _GCSkillToSelfOK2;

	int X = pCreature->getX();
	int Y = pCreature->getY();
	Exp_t ExpUp = 0;
	bool bCured = false;

	for(int oY = -2; oY <= 2; oY++)
	for(int oX = -2; oX <= 2; oX++)
	{
		int tileX = X+oX;
		int tileY = Y+oY;

		if (isValidZoneCoord(pZone, tileX, tileY))
		{
			Tile& tile = pZone->getTile(tileX, tileY);

			if ( tile.hasCreature( Creature::MOVE_MODE_WALKING ) ) 
			{
				const slist<Object*>& oList = tile.getObjectList();
				for(slist<Object*>::const_iterator itr = oList.begin(); itr != oList.end(); itr++) 
				{
					Object* pTarget = *itr;
					Creature* pTargetCreature = NULL;
					if (pTarget->getObjectClass() == Object::OBJECT_CLASS_CREATURE 
						&& (pTargetCreature = dynamic_cast<Creature*>(pTarget))->isSlayer()) 
					{
						Assert(pTargetCreature != NULL);
						HP_t RemainHP = 0;

						if (pTargetCreature->isSlayer() && !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) ) 
						{
							Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
							HP_t CurrentHP = pSlayer->getHP(ATTR_CURRENT);
							HP_t MaxHP = pSlayer->getHP(ATTR_MAX);

							if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
							{
								ExpUp++;
								Effect* pEffect = pSlayer->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
								EffectBloodDrain * pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);

								Assert(pEffectBloodDrain != NULL);

								if (pEffectBloodDrain->getLevel() < CriticalBloodDrainLevel ) {

									// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
									if (pSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
									{
										Effect* pEffect = pSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
										EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
										pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
									}
									else
									{
										EffectAftermath* pEffectAftermath = new EffectAftermath(pSlayer);
										pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
										pSlayer->addEffect(pEffectAftermath);
										pSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
										pEffectAftermath->create(pSlayer->getName());
									}

									pEffectBloodDrain->destroy(pSlayer->getName());
									pSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

									bCured = true;

									SLAYER_RECORD prev;
									pSlayer->getSlayerRecord(prev);
									pSlayer->initAllStat();
									pSlayer->sendRealWearingInfo();
									pSlayer->sendModifyInfo(prev);

									GCRemoveEffect gcRemoveEffect;
									gcRemoveEffect.setObjectID(pSlayer->getObjectID());
									gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
									pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);

								}
							}

							if( CurrentHP < MaxHP ) {
								ExpUp++;
								bCured = true;

								RemainHP = min(CurrentHP + m_Point,(int)MaxHP);
								pSlayer->setHP(RemainHP, ATTR_CURRENT);

								GCModifyInformation gcMI;
								gcMI.addShortData(MODIFY_CURRENT_HP, RemainHP);
								pSlayer->getPlayer()->sendPacket(&gcMI);

								_GCSkillToSelfOK1.setSkillType(SKILL_CURE_EFFECT);
								_GCSkillToSelfOK1.setDuration(0);
								pSlayer->getPlayer()->sendPacket(&_GCSkillToSelfOK1);
							
								_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
								_GCSkillToSelfOK2.setSkillType(SKILL_CURE_EFFECT);
								_GCSkillToSelfOK2.setDuration(0);
								pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToSelfOK2, pTargetCreature );

								Zone* pZone = pTargetCreature->getZone();
								GCStatusCurrentHP gcStatusCurrentHP;
								gcStatusCurrentHP.setObjectID(pTargetCreature->getObjectID());
								gcStatusCurrentHP.setCurrentHP(RemainHP);
								pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcStatusCurrentHP );
							}
						} 
					}
				}	
			}
		}	
	}

	SkillInfo * pSkillInfo = g_pSkillInfoManager->getSkillInfo(SKILL_CURE_CRITICAL_WOUNDS );

	if( pSkillInfo != NULL && bCured ) {
		SkillSlot * pSkillSlot = ((Slayer*)pCreature)->hasSkill(SKILL_CURE_CRITICAL_WOUNDS);
		if( pSkillSlot != NULL ) {
			Slayer * pCastSlayer = dynamic_cast<Slayer*>(pCreature);
			GCModifyInformation gcMI;
			SkillDomainType_t DomainType = pSkillInfo->getDomainType();
			// 경험치를 올려준다.
			shareAttrExp(pCastSlayer, ExpUp, 1 , 1 , 8, gcMI);
			increaseDomainExp(pCastSlayer, DomainType, ExpUp, gcMI );
			increaseSkillExp(pCastSlayer, DomainType, pSkillSlot, pSkillInfo, gcMI );
			pCastSlayer->getPlayer()->sendPacket(&gcMI);
		}
	}

	//cout << "EffectCureCriticalWounds " << "affect BEGIN" << endl;
	setNextTime(m_Delay);
	//cout << "EffectCureCriticalWounds " << "affect END" << endl;

	__END_CATCH
}

void EffectCureCriticalWounds::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectCureCriticalWounds::unaffect(Creature* pCreature)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pCreature != NULL);
	pCreature->removeFlag(Effect::EFFECT_CLASS_CURE_CRITICAL_WOUNDS);
	Zone* pZone = pCreature->getZone();
	Assert(pZone!=NULL);

	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pCreature->getObjectID());
	gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_CURE_CRITICAL_WOUNDS);
	pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);


	__END_CATCH
}

void EffectCureCriticalWounds::unaffect()
	throw(Error)
{
	__BEGIN_TRY

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);

	__END_CATCH
}

void EffectCureCriticalWounds::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectCureCriticalWounds::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectCureCriticalWounds("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

