#ifndef __NAME_MANAGER_H__
#define __NAME_MANAGER_H__

#include "Types.h"
#include <map>
#include <string>

template <class T>
class NameManager {
public :
	typedef map<string, T> NameHashMap;

public :
	NameManager() {}
	virtual ~NameManager() {}

	virtual void	init() {}
	virtual void	release() { m_Names.clear(); }

	virtual bool	add(const string& name, const T& data);
	virtual bool	remove(const string& name);
	virtual bool	isExist(const string& name) const;

private :
	NameHashMap		m_Names;	
};

template<class T>
bool	
NameManager<T>::add(const string& name, const T& data)
{
	typename NameHashMap::const_iterator itr = m_Names.find(name);

	if (itr==m_Names.end())
	{
		m_Names[name] = data;

		return true;
	}

	return false;
}

template <class T>
bool	
NameManager<T>::remove(const string& name)
{
	typename NameHashMap::iterator itr = m_Names.find(name);

	if (itr==m_Names.end())
		return false;

	m_Names.erase(itr);

	return true;
}

template<class T>
bool	
NameManager<T>::isExist(const string& name) const
{
	typename NameHashMap::const_iterator itr = m_Names.find(name);

	if (itr==m_Names.end())
		return false;

	return true;
}

#endif
