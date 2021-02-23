#include "LuaSelectItem.h"

LuaSelectItem::LuaSelectItem(LuaState* pState) 
: LuaScript(pState) 
{
	m_ItemClass 	= (Item::ItemClass)0;
	m_ItemType 		= 0;
	m_OptionType 	= 0;
}

int
LuaSelectItem::executeFile(const string& filename)
	throw (Error)
{
	__BEGIN_TRY

	int result = lua_dofile(m_pState->getState(), filename.c_str());

	lua_getglobal(m_pState->getState(), "ItemClass");
	lua_getglobal(m_pState->getState(), "ItemType");
	lua_getglobal(m_pState->getState(), "OptionType");
	lua_getglobal(m_pState->getState(), "OptionType2");	 // -_-; 한개 더 추가되면 list로 바꾸자~

	m_ItemClass 	= (Item::ItemClass)lua_tonumber(m_pState->getState(), 1);
	m_ItemType 		= (ItemType_t)lua_tonumber(m_pState->getState(), 2);
	m_OptionType 	= (OptionType_t)lua_tonumber(m_pState->getState(), 3);
	m_OptionType2 	= (OptionType_t)lua_tonumber(m_pState->getState(), 4);

	//cout << "ItemClass=" << ItemClass
	//	<< ", ItemType=" << ItemType
	//	<< ", OptionType=" << OptionType << endl;

	return result;

	__END_CATCH
}
