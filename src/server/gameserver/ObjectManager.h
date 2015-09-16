//////////////////////////////////////////////////////////////////////////////
// Filename    : ObjectManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////////////
// class ObjectManager;
// 하위 게임 객체들의 매니저를 관리하는 상위 관리 클래스이다.
//////////////////////////////////////////////////////////////////////////////

class ObjectManager 
{
public:
	ObjectManager() throw(Error);
	~ObjectManager() throw(Error);

public:
	void init() throw(Error);
	void load() throw(Error);
	void save() throw(Error);
};

// global variable declaration
extern ObjectManager* g_pObjectManager;

#endif
