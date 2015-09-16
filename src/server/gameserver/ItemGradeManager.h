#ifndef __ITEM_GRADE_MANAGER_H__
#define __ITEM_GRADE_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <vector>

class ItemGradeManager
{
public:
	ItemGradeManager() { m_GradeRatios.reserve(10); }
	void load() throw(Error);
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
