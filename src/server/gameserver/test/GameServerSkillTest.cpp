#include "GameServerSkillTest.h"
//#include "MockPlayer.h"
#include "Slayer.h"
#include "SkillHandlerManager.h"
#include "MockSkillInput.h"

void
GameServerSkillTest::testSharpShieldFormula()
{
	__BEGIN_TEST_CASE

	int SkillType = SKILL_SHARP_SHIELD;

	SkillHandler* pSkillHandler = g_pSkillHandlerManager->getSkillHandler(SkillType);
	Assert(pSkillHandler!=NULL);

	MockSkillInput	input;
	SkillOutput 	output;

	//---------------------------------------------------------------------------
	//
	// MockSkillInput input(SkillLevel, STR, DEX, INTE, IClass, DomainLevel)
	//
	//---------------------------------------------------------------------------
	// Duration = ( 10 + (SkillLevel/2) ) * 10
	// Damage 	= STR/20 + SkillLevel/20
	// Delay 	= ( 5 - (SkillLevel/25) ) * 10
	//---------------------------------------------------------------------------

	//---------------------------------------------------------------------------
	// SkillLevel( 50 ), STR( 50 )
	//---------------------------------------------------------------------------
	input.setSkillLevel( 50 );
	input.setATTR( 50, 50, 50 );
	input.setWeaponClass( Item::ITEM_CLASS_SWORD );
	input.setDomainLevel( 100 );

	pSkillHandler->computeOutput(input, output);

	CPPUNIT_ASSERT( output.Duration==350 ); // 35초
	CPPUNIT_ASSERT( output.Damage==4 );
	CPPUNIT_ASSERT( output.Delay==30 ); // 3초

	//---------------------------------------------------------------------------
	// SkillLevel( 1 ), STR( 100 )
	//---------------------------------------------------------------------------
	input.setSkillLevel( 1 );
	input.setATTR( 100, 50, 50 );
	input.setWeaponClass( Item::ITEM_CLASS_SWORD );
	input.setDomainLevel( 90 );

	pSkillHandler->computeOutput(input, output);

	CPPUNIT_ASSERT( output.Duration==100 ); // 10초
	CPPUNIT_ASSERT( output.Damage==5 );
	CPPUNIT_ASSERT( output.Delay==50 ); // 5초


	__END_TEST_CASE
}


void
GameServerSkillTest::testSharpShieldExecute()
{
	__BEGIN_TEST_CASE

	/*
	ObjectID_t	TargetObjectID	= 111;
	SkillSlot*  pSkillSlot 		= pSlayer->hasSkill(SkillType);
	EffectID_t 	EffectID 		= 0;	// 의미 없다.
	pSkillHandler->execute(pSlayer, TargetObjectID, pSkillSlot, EffectID);

	Damage_t damage = 10;
	CPPUNIT_ASSERT(damage==10);
	*/

	__END_TEST_CASE
}

