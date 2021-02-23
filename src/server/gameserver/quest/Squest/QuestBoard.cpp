//--------------------------------------------------------------------------------
// QuestBoard.cpp
//--------------------------------------------------------------------------------
#include "Quest.h"
#include "QuestUtil.h"
#include "QuestBoard.h"
#include "QuestFactoryManager.h"
#include "Gpackets/GCNPCAskDynamic.h"
#include "Script.h"
#include "Assert.h"

//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
QuestBoard::QuestBoard()
: m_pNPC(NULL)
{
	__BEGIN_TRY
	__END_CATCH
}

//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
QuestBoard::~QuestBoard()
{
	__BEGIN_TRY

	release();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// init
//--------------------------------------------------------------------------------
void		
QuestBoard::init(int num) 
	throw (Error)
{
	__BEGIN_TRY

	regenerate(num);

	__END_CATCH
}

//--------------------------------------------------------------------------------
// release
//--------------------------------------------------------------------------------
void		
QuestBoard::release() 
	throw (Error)
{
	__BEGIN_TRY

	QUESTS::iterator itr = m_Quests.begin();

	while (itr!=m_Quests.end())
	{
		Quest* pQuest = itr->second;

		SAFE_DELETE(pQuest);

		itr ++;
	}
	m_Quests.clear();

	__END_CATCH
}

//--------------------------------------------------------------------------------
// regenerate
//--------------------------------------------------------------------------------
void		
QuestBoard::regenerate(int num) 
	throw (Error)
{
	__BEGIN_TRY

	release();

	QuestCreateInfo qcInfo;


	for (int i=0; i<num; i++)
	{
		int level = 10 + i*20 + rand()%10; // 10~99
		qcInfo.setLevel( level );

		Quest* pQuest = QuestFactoryManager::getInstance()->create(Quest::QUEST_MONSTER_KILL, &qcInfo);
		Assert(pQuest!=NULL);

		if (!add( pQuest ))
		{
			SAFE_DELETE(pQuest);
		}
		else
		{
			//cout << "[QuestBoard] add: " << pQuest->toString().c_str() << endl;
		}
	}
	

	__END_CATCH
}

//--------------------------------------------------------------------------------
// add( pQuest )
//--------------------------------------------------------------------------------
// questID를 추가한다.
// ID가 duplicate인 경우는 return false
//--------------------------------------------------------------------------------
bool        
QuestBoard::add(Quest* pQuest) 
	throw (Error)
{
	__BEGIN_TRY

	QuestID_t qid = pQuest->getQuestID();

	QUESTS::const_iterator itr = m_Quests.find( qid );

	if (itr!=m_Quests.end())
	{
		return false;
	}

	m_Quests[qid] = pQuest;

	__END_CATCH

	return true;
}

//--------------------------------------------------------------------------------
// remove( questID )
//--------------------------------------------------------------------------------
// questID의 Quest*를 찾아서 return한다.
// 없으면 NULL
//--------------------------------------------------------------------------------
Quest*		
QuestBoard::remove(QuestID_t qid) 
	throw (Error)
{
	__BEGIN_TRY

	QUESTS::iterator itr = m_Quests.find( qid );

	if (itr!=m_Quests.end())
	{
		Quest* pQuest = itr->second;
		m_Quests.erase( itr );

		return pQuest;
	}

	__END_CATCH

	return NULL;
}

//--------------------------------------------------------------------------------
// makeNPCAskPacket( GCNPCAskDynamic& )
//--------------------------------------------------------------------------------
// QuestBoard에 들어있는 모든 Quest들의 내용을 GCNPCAskDynamic packet으로 만든다.
//--------------------------------------------------------------------------------
void		
QuestBoard::setScript(Script* pScript) const 
	throw (Error)
{
	__BEGIN_TRY

	pScript->clearContents();

	QUESTS::const_iterator itr = m_Quests.begin();

	while (itr!=m_Quests.end())
	{
		Quest* pQuest = itr->second;

		DWORD code = pQuest->getQuestID();

		pScript->addContent( pQuest->toString(), code );

		itr++;
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
// makeNPCAskPacket( GCNPCAskDynamic& )
//--------------------------------------------------------------------------------
// QuestBoard에 들어있는 모든 Quest들의 내용을 GCNPCAskDynamic packet으로 만든다.
//--------------------------------------------------------------------------------
/*
void		
QuestBoard::makeNPCAskPacket(GCNPCAskDynamic& gcNPCAskDynamic) const 
	throw (Error)
{
	__BEGIN_TRY

	//gcNPCAskDynamic.setObjectID(pCreature1->getObjectID());
	//gcNPCAskDynamic.setScriptID(10000);
	gcNPCAskDynamic.setSubject(pScript->getSubject(0));

	for (uint c=0; c<pScript->getContentCount(); c++)
	{
		gcNPCAskDynamic.addContent(pScript->getContent(c));
	}

	__END_CATCH
}
*/

