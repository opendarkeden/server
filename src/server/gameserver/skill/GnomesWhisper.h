//////////////////////////////////////////////////////////////////////////////
// Filename    : GnomesWhisper.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GNOMES_WHISPER_HANDLER_H__
#define __SKILL_GNOMES_WHISPER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GnomesWhisper;
//////////////////////////////////////////////////////////////////////////////

class GnomesWhisper : public SkillHandler 
{
public:
	GnomesWhisper() throw() {}
	~GnomesWhisper() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GnomesWhisper"; }
	SkillType_t getSkillType() const throw() { return SKILL_GNOMES_WHISPER; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GnomesWhisper g_GnomesWhisper;

#endif // __SKILL_GNOMES_WHISPER_HANDLER_H__
