#ifndef __PET_TYPE_INFO_H__
#define __PET_TYPE_INFO_H__

#include "Types.h"
#include "types/PetTypes.h"
#include "Exception.h"

#include <vector>

const uint PetTypeNum = 5;
class PetTypeInfoManager;

class PetTypeInfo
{
public:
	PetTypeInfo( PetType_t PetType ) : m_PetType(PetType) { }

	PetType_t		getPetType() const { return m_PetType; }
	MonsterType_t	getOriginalMonsterType() const { return m_OriginalMonsterType; }
	MonsterType_t	getPetCreatureTypeByIndex(uint index) const { return m_PetCreatureType[index]; }
	MonsterType_t	getPetCreatureType(PetLevel_t petLevel) const;
	int				getFoodType() const { return m_FoodType; }
private:
	PetType_t		m_PetType;
	MonsterType_t	m_OriginalMonsterType;
	MonsterType_t	m_PetCreatureType[PetTypeNum];

	int				m_FoodType;

	friend class PetTypeInfoManager;
};

class PetTypeInfoManager
{
public:
	PetTypeInfoManager() { m_PetTypeInfos.clear(); }
	~PetTypeInfoManager() { clear(); }

	void clear();
	void load();

	void addPetTypeInfo( PetTypeInfo* pPetTypeInfo );
	PetTypeInfo* getPetTypeInfo( PetType_t PetType );

	static PetTypeInfoManager* getInstance()
	{
		static PetTypeInfoManager theInstance;
		return &theInstance;
	}

private:
	vector<PetTypeInfo*>	m_PetTypeInfos;
};

#endif
