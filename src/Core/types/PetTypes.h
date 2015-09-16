#ifndef __PET_TYPES_H__
#define __PET_TYPES_H__

#include "SystemTypes.h"

enum PetType
{
	PET_NONE = 0,
	PET_COMMON,
	PET_PACKAGE,
	PET_CENTAURO,
	PET_STIRGE,
	PET_PIXIE
};
typedef BYTE PetType_t;
const uint szPetType = szBYTE;

typedef BYTE PetLevel_t;
const uint szPetLevel = szBYTE;

typedef DWORD PetExp_t;
const uint szPetExp = szDWORD;

typedef WORD PetHP_t;
const uint szPetHP = szWORD;

typedef BYTE PetAttr_t;
const uint szPetAttr = szBYTE;

typedef BYTE PetAttrLevel_t;
const uint szPetAttrLevel = szBYTE;

#endif
