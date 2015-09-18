#ifndef __NEWBIE_FLAG_WAR_H__
#define __NEWBIE_FLAG_WAR_H__

#include "FlagWar.h"

class NewbieFlagWar : public FlagWar
{
public:
	virtual int getWarTime() const { return 3600; }
protected:
	virtual void executeEnd() throw(Error);
	virtual VSDateTime getNextFlagWarTime();
	virtual void addFlags();
};

#endif
