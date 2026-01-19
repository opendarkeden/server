#ifndef __ADVANCEMENT_CLASS_EXP_TABLE_H__
#define __ADVANCEMENT_CLASS_EXP_TABLE_H__

#include <cstdio>

#include "Exception.h"
#include "SomethingGrowingUp.h"
#include "Types.h"

class AdvancementClassExpTable : public ExpTable<Exp_t, Level_t, 0, 100> {
public:
    const string getDBTableName() const {
        return "AdvancementClassEXPInfo";
    }

public:
    static AdvancementClassExpTable s_AdvancementClassExpTable;
};

typedef SomethingGrowingUp<AdvancementClassExpTable> AdvancementClass;

#endif
