#ifndef __LOG_DEF__
#define __LOG_DEF__

#include "VariableManager.h"

#define FILELOG_INCOMING_CONNECTION		\
		if (g_pVariableManager->getVariable(LOG_INCOMING_CONNECTION)) filelog

#endif
