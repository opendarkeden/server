#ifndef __FLAG_WAR_MANAGER_H__
#define __FLAG_WAR_MANAGER_H__

#include <vector>

class FlagManager;

class FlagWarManager
{
public:
	FlagWarManager() { m_FlagManagers.clear(); }
	~FlagWarManager();



private:
	vector<FlagManager*>	m_FlagManagers;
};

#endif
