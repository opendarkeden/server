//////////////////////////////////////////////////////////////////////////////
// Filename    : Shape.h
// Written by  : excel96
// Description : 
// 로그인화면에서 슬레이어의 외양을 보여주는 데 필요한 함수들.
// 아이템 타입에 따른 겉모습 상수를 리턴하는 함수들이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Types.h"
#include "Exception.h"

BYTE getShoulderType(ItemType_t IType) ;
PantsType getPantsType(ItemType_t IType) ;
JacketType getJacketType(ItemType_t IType) ;
HelmetType getHelmetType(ItemType_t IType) ;
ShieldType getShieldType(ItemType_t IType) ;
MotorcycleType getMotorcycleType(ItemType_t IType) ;

// 뱀파이어
VampireCoatType getVampireCoatType(ItemType_t IType) ;

// 아우스터스
OustersCoatType getOustersCoatType(ItemType_t IType) ;
OustersArmType getOustersArmType(ItemType_t IType) ;

#endif
