#ifndef __SIEGE_MANAGER_H__
#define __SIEGE_MANAGER_H__

#include "Types.h"
#include "Exception.h"

class PlayerCreature;
class MonsterCorpse;
class Item;

class SiegeManager
{
public:
	void	init();
	void	init(ZoneID_t zoneID);
	void	start(ZoneID_t zoneID);
	void	reset(ZoneID_t zoneID);

	ZoneID_t	getSiegeZoneID(ZoneID_t castleZoneID);

	static SiegeManager&	Instance()
	{
		static SiegeManager theInstance;
		return theInstance;
	}

	void	putItem( PlayerCreature* pPC, MonsterCorpse* pCorpse, Item* pItem );
	void	recallGuild( ZoneID_t currentZoneID, ZoneID_t siegeZoneID, GuildID_t guildID, int side, int num );

	bool	isSiegeZone( ZoneID_t zID );

private:
};

#endif
