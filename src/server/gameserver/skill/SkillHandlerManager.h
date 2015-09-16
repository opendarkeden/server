//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillHandlerManager.h 
// Wrrtten by  : elca@ewestsoft.com
// Description : 스킬 핸들러를 관리하는 Manager이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HANDLER_MANAGER_H__
#define __SKILL_HANDLER_MANAGER_H__

#include "Skill.h"
#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SkillHandlerManager
//////////////////////////////////////////////////////////////////////////////

class SkillHandlerManager 
{
public :
	SkillHandlerManager() throw();
	~SkillHandlerManager() throw();
	
public:
	// 게임서버객체의 init()에서 호출된다.
	void init() throw(Error);
	
	// 스킬 핸들러 객체를 초기화한다.
	void addSkillHandler(SkillHandler* pSkillHandler) throw(Error);

	// 스킬 핸들러를 얻어낸다.
	SkillHandler* getSkillHandler(SkillType_t SkillType) throw(Error);

	// toString
	string toString() const throw();
	
private:
	SkillHandler** m_SkillHandlers;  // 스킬 핸들러 배열
	ushort         m_Size;           // 스킬 핸들러 배열의 크기

};

extern SkillHandlerManager* g_pSkillHandlerManager;

#endif
