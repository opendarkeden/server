#include "HolyLandRaceBonus.h"
#include "CastleInfoManager.h"

HolyLandRaceBonus* g_pHolyLandRaceBonus = NULL;

HolyLandRaceBonus::HolyLandRaceBonus()
{
	refresh();
}

HolyLandRaceBonus::~HolyLandRaceBonus()
{
}

void	
HolyLandRaceBonus::refresh()
	throw (Error)
{
	__BEGIN_TRY

	// 기존꺼는 지우고..
	clear();

	const hash_map<ZoneID_t, CastleInfo*>& castleInfos = g_pCastleInfoManager->getCastleInfos();
	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = castleInfos.begin();


	// 현재 성의 소유종족에 따라서 보너스를 설정한다.
	for (; itr!=castleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;

		if (pCastleInfo->getRace()==RACE_SLAYER)
		{
			const list<OptionType_t>& optionTypes = pCastleInfo->getOptionTypeList();
			m_SlayerOptionTypes.insert( m_SlayerOptionTypes.begin(), optionTypes.begin(), optionTypes.end() );
		}
		else if (pCastleInfo->getRace()==RACE_VAMPIRE)
		{
			const list<OptionType_t>& optionTypes = pCastleInfo->getOptionTypeList();
			m_VampireOptionTypes.insert( m_VampireOptionTypes.begin(), optionTypes.begin(), optionTypes.end() );
		}
		else
		{
			// 무시
		}
	}

	__END_CATCH
}


