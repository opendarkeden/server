#ifndef __ADVANCEMENT_CLASS_EXP_TABLE_H__
#define __ADVANCEMENT_CLASS_EXP_TABLE_H__

#include "Types.h"
#include "Exception.h"
#include "SomethingGrowingUp.h"

#include <cstdio>

class AdvancementClassExpTable : public ExpTable<Exp_t, Level_t, 0, 100>
{
public:
	const string getDBTableName() const { return "AdvancementClassEXPInfo"; }

public:
	static AdvancementClassExpTable s_AdvancementClassExpTable;
};

typedef SomethingGrowingUp<AdvancementClassExpTable> AdvancementClass;

#endif
