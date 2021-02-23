//////////////////////////////////////////////////////////////////////////////
// Filename    : ClaymoreExplosion.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CLAYMORE_EXPLOSION_HANDLER_H__
#define __SKILL_CLAYMORE_EXPLOSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ClaymoreExplosion;
//////////////////////////////////////////////////////////////////////////////

class ClaymoreExplosion: public SkillHandler 
{
public:
	ClaymoreExplosion() throw();
	~ClaymoreExplosion() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ClaymoreExplosion"; }
	SkillType_t getSkillType() const throw() { return SKILL_CLAYMORE_EXPLOSION; }

	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	POINT	m_pClaymoreExplosionMask[15];
};

// global variable declaration
extern ClaymoreExplosion g_ClaymoreExplosion;

#endif // __SKILL_HIDE_HANDLER_H__
