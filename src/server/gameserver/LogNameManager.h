#ifndef __LOG_NAME_MANAGER_H__
#define __LOG_NAME_MANAGER_H__

#include "NameManager.h"

class LogNameManager : public NameManager<int> {
public :
	virtual void	init();

	static LogNameManager& getInstance()
	{
		static LogNameManager LNM;
		return LNM;
	}
};

#endif

