//////////////////////////////////////////////////////////////////////////////
// Filename    : Obstacle.h
// Written by  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "Object.h"

//////////////////////////////////////////////////////////////////////////////
// Obstacle Type
//
// 각 하위 장애물 종류마다 최대 256 가지가 존재한다.
//(문이나 스위치, 함정이 256개를 넘어갈 수 있을까?)
//////////////////////////////////////////////////////////////////////////////
typedef BYTE ObstacleType_t;
const uint szObstacleType = sizeof(ObstacleType_t);

//////////////////////////////////////////////////////////////////////////////
// class Obstacle;
//
// 타일에 종속되는 객체로서,  크리처의 이동을 방해하면서 상태를 갖고
// 있는 Object의 하위 클래스 객체이다. 문이나 함정, 스위치 같은 것들이
// 여기에 속한다.
//////////////////////////////////////////////////////////////////////////////

class Obstacle : public Object 
{
public:
	enum ObstacleClass 
	{
		OBSTACLE_CLASS_DOOR ,
		OBSTACLE_CLASS_SWITCH ,
		OBSTACLE_CLASS_TRAP
	};

public:
	Obstacle(ObjectID_t objectID) throw() : Object(objectID) {}
	virtual ~Obstacle() throw() {}
	
// methods from Object
public:
	virtual ObjectClass getObjectClass() const throw() { return OBJECT_CLASS_OBSTACLE; }
	virtual ObjectPriority getObjectPriority() const throw(Error) { return OBJECT_PRIORITY_OBSTACLE; }
	virtual string toString() const throw() = 0;

// own methods
public:
	virtual ObstacleClass getObstacleClass() const throw() = 0;
	virtual ObstacleType_t getObstacleType() const throw() = 0;
};

#endif
