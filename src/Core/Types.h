//////////////////////////////////////////////////////////////////////////////
// Filename    : Types.h
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __TYPES_H__
#define __TYPES_H__

#include "types/SystemTypes.h"
#include "types/PlayerTypes.h"
#include "types/ObjectTypes.h"
#include "types/CreatureTypes.h"
#include "types/ItemTypes.h"
#include "types/ZoneTypes.h"
#include "types/QuestTypes.h"
#include "types/ShopTypes.h"
#include "types/GuildTypes.h"
#include "types/WarTypes.h"
#include "types/ServerType.h"

#ifndef __GAME_CLIENT__
	#include "Utility.h"
#endif

#ifndef __XMAS_EVENT_CODE__
	#define __XMAS_EVENT_CODE__
#endif

//#define __UNDERWORLD__

//#ifdef __NETMARBLE_SERVER__
//	#define __OLD_GUILD_WAR__
//#endif

#endif
