//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFadeOut.cpp
// Written by  : elca
// Description : 
// 군인기술 Sniping 또는 뱀파이어 기술 Invisibility로 인해서
// 현재 점점 희미해져가고 있는(사라지고 있는) 크리쳐에 붙는 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#include "EffectFadeOut.h"
#include "EffectInvisibility.h"
#include "EffectSnipingMode.h"
#include "Slayer.h"
#include "Vampire.h"
#include "DB.h"
#include "ZoneUtil.h"

#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
EffectFadeOut::EffectFadeOut(Creature* pCreature)
	
{
	__BEGIN_TRY

	setTarget(pCreature);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::affect(Creature* pCreature)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::unaffect(Creature* pCreature)
	
{
	__BEGIN_TRY
	
	//cout << "EffectFadeOut " << "unaffect BEGIN" << endl;

	Assert(pCreature != NULL);

	Zone* pZone = pCreature->getZone();
	Assert(pZone != NULL);

	ZoneCoord_t x = pCreature->getX();
	ZoneCoord_t y = pCreature->getY();
	pCreature->removeFlag(Effect::EFFECT_CLASS_FADE_OUT);

	// 군인기술 Sniping에 의한 것이라면...
	if (m_isSniping) 
	{
		// 슬레이어만이 해당된다.
		Assert(pCreature->isSlayer());
		Assert(pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE) == false);
		Assert(pCreature->findEffect(Effect::EFFECT_CLASS_SNIPING_MODE) == NULL);

		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		
		EffectSnipingMode* pEffect = new EffectSnipingMode(pSlayer);
		pEffect->setDeadline(m_Duration);
		pSlayer->addEffect(pEffect);
		pSlayer->setFlag(Effect::EFFECT_CLASS_SNIPING_MODE);

		// 이펙트를 붙였으니, 능력치를 재계산한다.
		SLAYER_RECORD prev;
		pSlayer->getSlayerRecord(prev);
		pSlayer->initAllStat();
		pSlayer->sendRealWearingInfo();
		pSlayer->sendModifyInfo(prev);

		addSnipingModeCreature(pZone, pCreature, x, y);
	} 
	// 뱀파이어 기술 Invisibility에 의한 것이라면... 
	else 
	{
		// 뱀파이어나 몬스터만이 해당된다.
		Assert(pCreature->isVampire() || pCreature->isMonster());
		Assert(pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY) == false);
		Assert(pCreature->findEffect(Effect::EFFECT_CLASS_INVISIBILITY) == NULL);
		
		EffectInvisibility* pEffect = new EffectInvisibility(pCreature);
		pEffect->setNextTime(10);
		pEffect->setDeadline(99999999); // 무한이다.
		pCreature->addEffect(pEffect);

		addInvisibleCreature(pZone, pCreature, x, y);
	}

	//cout << "EffectFadeOut " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::unaffect()
	
{
	__BEGIN_TRY

	//cout << "EffectFadeOut " << "unaffect BEGIN" << endl;

	Creature* pCreature = dynamic_cast<Creature*>(m_pTarget);
	unaffect(pCreature);
	
	//cout << "EffectFadeOut " << "unaffect END" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EffectFadeOut::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	
{
	__BEGIN_TRY
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string EffectFadeOut::toString() const 
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectFadeOut("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

