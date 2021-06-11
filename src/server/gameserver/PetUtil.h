#ifndef __PET_UTIL_H__
#define __PET_UTIL_H__

#include "Types.h"
#include "types/PetTypes.h"

class PetInfo;
class ModifyInfo;
class GamePlayer;

bool increasePetExp( PetInfo* pPetInfo, PetExp_t exp, ModifyInfo* pMI = NULL );
PetExp_t computePetExp( Level_t myLevel, Level_t monsterLevel, PetInfo* pPetInfo, GamePlayer* pGamePlayer );
void refreshHP( PetInfo* pPetInfo, uint ratio = 100 );

#endif
