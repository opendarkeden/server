#ifndef __HOLY_LAND_RACE_BONUS_INFO_H__
#define __HOLY_LAND_RACE_BONUS_INFO_H__

#include "Types.h"
#include "Exception.h"

class HolyLandRaceBonus {
public :
	HolyLandRaceBonus();
	~HolyLandRaceBonus();

	void 	clear()		{ m_SlayerOptionTypes.clear(); m_VampireOptionTypes.clear(); }

	// 아담의 성지에서의 종족보너스를 다시 설정한다.
	void	refresh() throw (Error);

	const list<OptionType_t>&	getSlayerOptionTypeList() const	{ return m_SlayerOptionTypes; }
	const list<OptionType_t>&	getVampireOptionTypeList() const { return m_VampireOptionTypes; }

public :
	list<OptionType_t> m_SlayerOptionTypes;
	list<OptionType_t> m_VampireOptionTypes;
};

extern HolyLandRaceBonus* g_pHolyLandRaceBonus;

#endif

