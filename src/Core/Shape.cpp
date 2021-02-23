//////////////////////////////////////////////////////////////////////////////
// Filename    : Shape.cpp
// Written by  : excel96
// Description : 
// 로그인 화면에서 슬레이어의 외양을 보여주는 데 필요한 함수들.
// 아이템 타입에 따른 겉모습 상수를 리턴하는 함수들이다.
//////////////////////////////////////////////////////////////////////////////

#include "Shape.h"

BYTE getShoulderType(ItemType_t IType)
	throw()
{
	return 1;
}

PantsType getPantsType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return PANTS1;
		case 4:
		case 5:
		case 6:
		case 7:
			return PANTS2;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		default:
//			throw ("getPantsType() : unknown pants type");
			return PANTS3;
			break;
	}

	return PANTS_BASIC;
}

JacketType getJacketType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return JACKET1;
		case 4:
		case 5:
		case 6:
		case 7:
			return JACKET2;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		default:
//			throw ("getJacketType() : unknown jacket type");
			return JACKET3;
			break;
	}

	return JACKET_BASIC;
}

HelmetType getHelmetType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
			return HELMET1;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		default:
//			throw ("getHelmetType() : unknown helmet type");
			return HELMET2;
			break;
	}

	return HELMET_NONE;
}

ShieldType getShieldType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			return SHIELD1;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		default:
//			throw ("getShieldType() : unknown shield type");
			return SHIELD2;
			break;
	}

	return SHIELD_NONE;
}

VampireCoatType getVampireCoatType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 0:
		case 1:
		case 2:
		case 3:
			return VAMPIRE_COAT1;
		case 4:
		case 5:
		case 6:
		case 7:
			return VAMPIRE_COAT2;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:

		default:
//			throw ("getVampireCoatType() : unknown VampireCoat type");
			return VAMPIRE_COAT3;
			break;
	}

	return VAMPIRE_COAT_BASIC;
}

MotorcycleType getMotorcycleType(ItemType_t IType)
	throw()
{
	switch (IType)
	{
		case 6:
			return MOTORCYCLE2;
		case 7:
			return MOTORCYCLE3;
		case 0:
		case 5:
		default:
			return MOTORCYCLE1;
			break;
	}

	return MOTORCYCLE_NONE;
}

OustersCoatType getOustersCoatType(ItemType_t IType)
	throw()
{
	switch ( IType )
	{
		case 0:
		case 1:
		case 2:
			return OUSTERS_COAT1;
		case 3:
		case 4:
		case 5:
			return OUSTERS_COAT2;
		case 6:
		case 7:
		case 8:
		case 9:
		default:
			return OUSTERS_COAT3;
	}

	return OUSTERS_COAT_BASIC;
}

OustersArmType getOustersArmType(ItemType_t IType)
	throw()
{
	switch ( IType )
	{
		case 0:
			return OUSTERS_ARM_GAUNTLET;
	}

	return OUSTERS_ARM_GAUNTLET;
}

