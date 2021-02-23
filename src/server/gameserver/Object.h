//////////////////////////////////////////////////////////////////////////////
// Filename    : Object.h
// Written By  : Elca
// Description : 모든 클래스의 최상위 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Types.h"
#include "Exception.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// Object Priority
//
// 타일의 Object List 에서 각 Object 하위 클래스 객체들간의 우선순위를 
// 나타낸다. 값이 작을 수록 우선순위가 높으며, 타일의 Object List 에서
// 보다 앞쪽에 배치되어야 한다.
//
// 우선순위는 가장 활동적인, 즉 가장 이동성이 높은 객체들이 우선 순위가
// 높게 지정되어야 한다. 이는 타일의 Object List 가 slist 로 구현되며,
// slist 는 앞쪽에서 insert/delete 의 시간이 짧기 때문이다.
//////////////////////////////////////////////////////////////////////////////
enum ObjectPriority 
{
	OBJECT_PRIORITY_WALKING_CREATURE ,
	OBJECT_PRIORITY_FLYING_CREATURE ,
	OBJECT_PRIORITY_BURROWING_CREATURE ,
	OBJECT_PRIORITY_EFFECT ,
	OBJECT_PRIORITY_ITEM ,
	OBJECT_PRIORITY_PORTAL ,
	OBJECT_PRIORITY_OBSTACLE ,
	OBJECT_PRIORITY_NONE					// 타일용 오브젝트가 아닐 경우
};

class Packet;

//////////////////////////////////////////////////////////////////////////////
// class Object
// 모든 게임 클래스의 최상위 클래스이다.
//////////////////////////////////////////////////////////////////////////////

class Object 
{
public:
	// Object Class
	// Object 하위 클래스들의 분류를 나타낸다. Object 를 직접 상속받은 
	// 클래스들에 한해서 ObjectClass 에 추가하면 되겠다.
	enum ObjectClass 
	{
		OBJECT_CLASS_CREATURE,
		OBJECT_CLASS_ITEM,
		OBJECT_CLASS_OBSTACLE,
		OBJECT_CLASS_EFFECT,
		OBJECT_CLASS_PORTAL
	};

public:
	Object(ObjectID_t objectID = 0) throw() : m_ObjectID(objectID) {}
	virtual ~Object() throw() {}
	
public:
	// get/set object id
	//
	// 존 레벨에서 unique 한 객체의 구분자(identifier)로 사용된다.
	// 물론 게임 서버 레벨에서 unique 해도 되긴 하지만, 오랜 시간동안
	// 게임 서버가 reboot 없이 운영될 경우 아무리 4G 라 할지라도 객체의
	// id 가 중복될 우려가 있어서 범위를 존 레벨로 축소했다. 
	// 이렇게 하면 초당 1000 개의 객체가 새로 생긴다고 할지라도 4M 초,
	// 즉 40-50일동안 안전하다는 뜻이다.
	ObjectID_t getObjectID() const throw(Error) { Assert(m_ObjectID != 0); return m_ObjectID; };
	void setObjectID(ObjectID_t objectID) throw(Error) { Assert(objectID != 0); m_ObjectID = objectID; }

	// get object class(virtual)
	// Object* pObject 에 대해서 이 객체가 크리처인지, 아이템인지, 아니면
	// 장애물인지를 살펴볼 때 사용한다. 하위 클래스는 이 메쏘드를 재정의해야한다.
	//
	// *CAUTION*
	// 물론 Object에 m_ObjectClass 데이타 멤버를 둬도 되지만, 이렇게 하면 
	// 컴파일러의 정렬 문제로 인해 모든 Object 하위 클래스의 객체들이 추가적인
	// 바이트를 소모하게 되므로, virtual method 로 해결했다.
	virtual ObjectClass getObjectClass() const throw() = 0;

	// get object priority(virtual)
	virtual ObjectPriority getObjectPriority() const throw(Error) = 0;

	// get debug string
	virtual string toString() const throw() = 0;

	virtual Packet* getAddPacket() const { return NULL; }

protected:
	ObjectID_t m_ObjectID; // Object ID

};

//////////////////////////////////////////////////////////////////////////////
// function object
//////////////////////////////////////////////////////////////////////////////
class isSameObjectID 
{
public:
    isSameObjectID(ObjectID_t objectID) : m_ObjectID(objectID) {}
 
    bool operator()(Object* pObject) throw()
    {
        return pObject->getObjectID() == m_ObjectID;
    }
 
private:
    ObjectID_t m_ObjectID;
};

#endif
