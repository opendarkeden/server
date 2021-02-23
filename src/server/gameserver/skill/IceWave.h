//////////////////////////////////////////////////////////////////////////////
// Filename    : IceWave.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ICE_WAVE_HANDLER_H__
#define __SKILL_ICE_WAVE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IceWave;
//////////////////////////////////////////////////////////////////////////////

class IceWave: public SkillHandler 
{
public:
	IceWave() throw();
	~IceWave() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "IceWave"; }
	SkillType_t getSkillType() const throw() { return SKILL_ICE_WAVE; }

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
	POINT	m_pIceWaveMask[193];
};

// global variable declaration
extern IceWave g_IceWave;

#endif // __SKILL_HIDE_HANDLER_H__
