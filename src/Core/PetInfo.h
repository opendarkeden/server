#ifndef __PET_INFO_H__
#define __PET_INFO_H__

#include "Types.h"
#include "types/PetTypes.h"
#include "Exception.h"

#include "Packet.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#include "VSDateTime.h"

class PetItem;

class PetInfo
{
public:
	PetInfo();
	virtual ~PetInfo() { }

	virtual void read(SocketInputStream& iStream) throw(ProtocolException, Error);
	virtual void write(SocketOutputStream& oStream) const throw(ProtocolException, Error);

	virtual PacketSize_t getSize() const
	{
		if ( m_PetType == PET_NONE ) return szPetType;

//		if ( type == MY_INFO )
			return szPetType + szMonsterType + szPetLevel + szPetExp + szPetHP + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szBYTE + szBYTE + szBYTE + szBYTE + szObjectID + szBYTE + m_Nickname.size();
//		else
//			return szPetType + szMonsterType + szPetLevel + szPetExp + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szObjectID;
	}
	static PacketSize_t getMaxSize()
	{
//		if ( type == MY_INFO )
			return szPetType + szMonsterType + szPetLevel + szPetExp + szPetHP + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szBYTE + szBYTE + szBYTE + szBYTE + szObjectID + szBYTE + 22;
//		else
//			return szPetType + szMonsterType + szPetLevel + szPetExp + szPetAttr + szPetAttrLevel + szOptionType + szItemType + szObjectID;
	}

public:
	void		setPetType(PetType_t PetType) { m_PetType = PetType; }
	PetType_t	getPetType() const { return m_PetType; }

	void			setPetCreatureType(MonsterType_t CreatureType) { m_PetCreatureType = CreatureType; }
	MonsterType_t	getPetCreatureType() const { return m_PetCreatureType; }

	void		setPetLevel(PetLevel_t PetLevel) { m_PetLevel = PetLevel; }
	PetLevel_t	getPetLevel() const { return m_PetLevel; }

	void		setPetExp(PetExp_t PetExp) { m_PetExp = PetExp; }
	PetExp_t	getPetExp() const { return m_PetExp; }

	void		setPetHP(PetHP_t PetHP) { m_PetHP = PetHP; }
	PetHP_t		getPetHP() const { return m_PetHP; }

	void		setPetAttr(PetAttr_t PetAttr) { m_PetAttr = PetAttr; }
	PetAttr_t	getPetAttr() const { return m_PetAttr; }

	void		setPetAttrLevel(PetAttrLevel_t PetAttrLevel) { m_PetAttrLevel = PetAttrLevel; }
	PetAttrLevel_t	getPetAttrLevel() const { return m_PetAttrLevel; }

	void			setPetOption(OptionType_t PetOption) { m_PetOption = PetOption; }
	OptionType_t	getPetOption() const { return m_PetOption; }

	void		setFoodType(ItemType_t FoodType) { m_PetFoodType = FoodType; }
	ItemType_t	getFoodType() const { return m_PetFoodType; }

	BYTE		canGamble() const { return m_CanGamble; }
	void		setGamble(BYTE bGamble) { m_CanGamble = bGamble; }

	BYTE		canCutHead() const { return m_CanCutHead; }
	void		setCutHead(BYTE bCutHead) { m_CanCutHead = bCutHead; }

	BYTE		canAttack() const { return m_CanAttack; }
	void		setAttack(BYTE bAttack) { m_CanAttack = bAttack; }

	void		setPetItem(PetItem* pPetItem) { m_pPetItem = pPetItem; }
	PetItem*	getPetItem() const { return m_pPetItem; }

	BYTE		isSummonInfo() const { return m_IsSummonInfo; }
	void		setSummonInfo( BYTE isSummon ) { m_IsSummonInfo = isSummon; }

	// -_- 게임서버쪽에 정의해야쥐 PetItem.cpp 에 있음
	ObjectID_t	getItemObjectID() const;

	VSDateTime&	getLastFeedTime() { return m_LastFeedTime; }
	void		setFeedTime(const VSDateTime& time) { m_LastFeedTime = time; }

//#ifdef __GAME_SERVER__
	BYTE		getFeedTurn() const { return m_FeedTurn; }
	void		setFeedTurn(BYTE turn) { m_FeedTurn = turn; }

	BYTE		getCurrentFeedTurn() const { return m_CurrentFeedTurn; }
	void		setCurrentFeedTurn(BYTE turn) { m_CurrentFeedTurn = turn; }
//#endif

	string		getNickname() const { return m_Nickname; }
	void		setNickname(const string& name) { m_Nickname = name; }

	string		toString() const;

private:
	PetType_t		m_PetType;
	MonsterType_t	m_PetCreatureType;
	PetLevel_t		m_PetLevel;
	PetExp_t		m_PetExp;
	PetHP_t			m_PetHP;
	PetAttr_t		m_PetAttr;
	PetAttrLevel_t	m_PetAttrLevel;
	OptionType_t	m_PetOption;
	ItemType_t		m_PetFoodType;
	BYTE			m_CanGamble;
	BYTE			m_CanCutHead;
	BYTE			m_CanAttack;

	BYTE			m_IsSummonInfo;
	VSDateTime		m_LastFeedTime;

//#ifdef __GAME_SERVER__
	BYTE			m_FeedTurn;
	BYTE			m_CurrentFeedTurn;
	string			m_Nickname;
//#endif

	PetItem*		m_pPetItem;
};

#endif
