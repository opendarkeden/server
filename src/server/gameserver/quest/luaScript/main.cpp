#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LuaTradeEventSlayerItem.h"
#include "LuaTradeEventVampireItem.h"

void executeSelectItem(LuaSelectItem& luaSelectItem, const char* pFilename)
{
	luaSelectItem.prepare();
	luaSelectItem.executeFile( pFilename );

	int ItemClass 	= luaSelectItem.getItemClass();
	int ItemType 	= luaSelectItem.getItemType();
	int OptionType 	= luaSelectItem.getOptionType();

	cout << "ItemClass=" << ItemClass
		<< ", ItemType=" << ItemType
		<< ", OptionType=" << OptionType << endl << endl;

	luaSelectItem.clear();
}

void executeVampire()
{
	LuaState L;
	L.init();
	L.dofile( "xmasEventCommon.lua" );

	LuaTradeEventVampireItem luaVampireItem(&L);

	while (1)
	{
		cout << "Input Level(0 to exit): ";
		int Level; cin >> Level;

		if (Level==0) break;

		luaVampireItem.setLevel( Level );

		executeSelectItem(luaVampireItem, "xmasEventVampire.lua" );
	}
}

void executeSlayer()
{
	LuaState L;
	L.init();
	L.dofile( "xmasEventCommon.lua" );

	LuaTradeEventSlayerItem luaSlayerItem(&L);

	while (1)
	{
		cout << "Input SUM(0 to exit): ";
		int SUM; cin >> SUM;

		if (SUM==0) break;

		luaSlayerItem.setSum( SUM );

		executeSelectItem(luaSlayerItem, "xmasEventSlayer.lua" );
	}
}

int main()
{

	cout << "1=slayer, 0=vampire > ";
	int isSlayer; cin >> isSlayer;

	if (isSlayer)
	{
		executeSlayer();
	}
	else
	{
		executeVampire();
	}



	return 0;
}
