#ifndef __NICKNAME_BOOK_H__
#define __NICKNAME_BOOK_H__

#include "Types.h"
#include "NicknameInfo.h"

#include <hash_map>

class PlayerCreature;
class Packet;

class NicknameBook
{
public:
	NicknameBook(PlayerCreature* pOwner) : m_pOwner(pOwner) { }

	NicknameInfo*	getNicknameInfo(WORD id) { return m_Nicknames[id]; }
	void			setNicknameInfo(WORD id, NicknameInfo* pInfo) { m_Nicknames[id] = pInfo; }

	Packet*			getNicknameBookListPacket() const;
	WORD			popNicknameID() { return m_NextNicknameID++; }

	void load() throw(Error);
	void addNewNickname(const string& nick) throw(Error);

private:
	PlayerCreature*					m_pOwner;
	hash_map<WORD, NicknameInfo*>	m_Nicknames;
	WORD							m_NextNicknameID;
};

#endif
