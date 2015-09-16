#ifndef __PET_ATTR_INFO_H__
#define __PET_ATTR_INFO_H__

#include "Types.h"
#include "types/PetTypes.h"
#include "Exception.h"
#include <vector>
#include <map>
#include "PetExpInfo.h"

class PetInfo;

class PetAttrInfo
{
public:
	PetAttrInfo(PetAttr_t PetAttr) : m_PetAttr(PetAttr) { m_PetAttrLevels.reserve(PetMaxLevel); m_PetAttrLevels.clear(); m_EnchantRatio=0; }
	PetAttr_t getPetAttr() const { return m_PetAttr; }

	PetAttrLevel_t getPetAttrLevel(PetLevel_t PetLevel ) { return m_PetAttrLevels[PetLevel]; }
	void setPetAttrLevel(PetLevel_t PetLevel, PetAttrLevel_t PetAttrLevel ) { m_PetAttrLevels[PetLevel] = PetAttrLevel; }

	int getEnchantRatio() { return m_EnchantRatio; }
	void setEnchantRatio(int EnchantRatio ) { m_EnchantRatio = EnchantRatio; }

private:
	PetAttr_t m_PetAttr;
	int m_EnchantRatio;
	vector<PetAttrLevel_t> m_PetAttrLevels;
};

class PetAttrInfoManager
{
public:
	PetAttrInfoManager() { m_PetAttrInfoMap.clear(); }
	~PetAttrInfoManager() { clear(); }

	void clear();
	void load();

	PetAttrInfo* getPetAttrInfo(PetAttr_t PetAttr ) const;

	static PetAttrInfoManager& Instance() { static PetAttrInfoManager theInstance; return theInstance; }

	bool enchantRandomAttr(PetInfo* pPetInfo, int ratio);
	bool enchantSpecAttr(PetInfo* pPetInfo, PetAttr_t PetAttr);
private:
	map<PetAttr_t, PetAttrInfo*> m_PetAttrInfoMap;
};

#endif
