#ifndef __ITEM_GRADE_MANAGER_H__
#define __ITEM_GRADE_MANAGER_H__

#include <vector>

#include "Exception.h"
#include "Types.h"

class ItemGradeManager {
public:
    ItemGradeManager() {
        m_GradeRatios.reserve(10);
    }
    void load();
    Grade_t getRandomGrade() const;
    Grade_t getRandomGambleGrade() const;
    Grade_t getRandomBeadGrade() const;

    static ItemGradeManager& Instance();

private:
    vector<WORD> m_GradeRatios;
    vector<WORD> m_GradeGambleRatios;
    vector<WORD> m_GradeBeadRatios;
};

#endif
