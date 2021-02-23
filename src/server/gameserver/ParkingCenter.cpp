//////////////////////////////////////////////////////////////////////////////
// Filename    : ParkingCenter.cpp
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "ParkingCenter.h"
#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
// class MotorcycleBox member methods
//////////////////////////////////////////////////////////////////////////////
MotorcycleBox::MotorcycleBox(Motorcycle* pMotorcycle, Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y)
	throw()
{
	__BEGIN_TRY

	m_pMotorcycle = pMotorcycle;
	m_pZone       = pZone;
	m_X           = X;
	m_Y           = Y;
	m_bTransport  = false;

	__END_CATCH
}

MotorcycleBox::~MotorcycleBox()
	throw()
{
	__BEGIN_TRY

	if (m_pMotorcycle != NULL) 
	{
		// m_pZone의 동기화 문제로 인해서 수정했다.
		// by sigi. 2002.5.3
		m_pZone->deleteMotorcycle(m_X, m_Y, m_pMotorcycle);

		/*
		Tile & tile = m_pZone->getTile(m_X, m_Y);

		if (tile.hasItem()) 
		{
			m_pZone->deleteItem(m_pMotorcycle, m_X, m_Y);
		} 
		else 
		{
			//cerr << "그 타일엔 오토바이가 없습니다." << endl;
		}

		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(m_pMotorcycle->getObjectID());

		m_pZone->broadcastPacket(m_X, m_Y, &gcDeleteObject);

		SAFE_DELETE(m_pMotorcycle);
		*/
	}

	m_pZone = NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// class ParkingCenter member methods
//////////////////////////////////////////////////////////////////////////////

ParkingCenter::ParkingCenter()
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName("ParkingCenter");
	m_MutexRemove.setName("ParkingCenterRemove");

	__END_CATCH
}

ParkingCenter::~ParkingCenter()
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< ItemID_t , MotorcycleBox* >::iterator itr = m_Motorcycles.begin();

	for (; itr != m_Motorcycles.end(); itr++)
	{
		MotorcycleBox* pBox = itr->second;
		SAFE_DELETE(pBox);
	}

	m_Motorcycles.clear();

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

void ParkingCenter::addMotorcycleBox (MotorcycleBox* pMotorcycleBox) 
	throw (DuplicatedException , Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)

	Assert(pMotorcycleBox != NULL);

	hash_map< ItemID_t , MotorcycleBox* >::iterator itr = m_Motorcycles.find(pMotorcycleBox->getItemID());

	if (itr != m_Motorcycles.end())
	{
		throw DuplicatedException();
	}

	m_Motorcycles[ pMotorcycleBox->getItemID() ] = pMotorcycleBox;

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

// hash_map에서 열쇠의 TargetID에 해당하는 오토바이를 지우는 함수이다.
// 여기서 오토바이 전체를 삭제하게 됨으로 존에서 오토바이를 지운다음.
// 최종적으로 이 함수를 불러야 할 것이다.
void ParkingCenter::deleteMotorcycleBox (ItemID_t keyTargetID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	MotorcycleBox* pMotorcycleBox = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< ItemID_t , MotorcycleBox* >::iterator itr = m_Motorcycles.find(keyTargetID);

	if (itr == m_Motorcycles.end())
	{
		//cerr << "ParkingCenter::deleteMotorcycleBox() : NoSuchElementException" << endl;
		//throw NoSuchElementException();

		m_Mutex.unlock();
		return;
	}

	pMotorcycleBox = itr->second;

	m_Motorcycles.erase(itr);

	// 데드락 문제로 바로 지우지 않는다.
	//SAFE_DELETE(pMotorcycleBox);

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	// 나중에 heartbeat에서 지워준다.
	if (pMotorcycleBox!=NULL)
	{
		__ENTER_CRITICAL_SECTION(m_MutexRemove)

		m_RemoveMotorcycles.push_back( pMotorcycleBox );

		__LEAVE_CRITICAL_SECTION(m_MutexRemove)
	}


	__END_CATCH
}

// 특정 KeyID를 가진 MotorcycleBox가 있는지 확인한다.
bool ParkingCenter::hasMotorcycleBox (ItemID_t keyTargetID) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY

	bool hasMotor = true;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	hash_map< ItemID_t , MotorcycleBox* >::iterator itr = m_Motorcycles.find(keyTargetID);

	if (itr == m_Motorcycles.end())
	{
		hasMotor = false;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return hasMotor;

	__END_CATCH
}

// 열쇠의 TargetID로 오토바이를 찾아서 Return 해주는 함수이다.
MotorcycleBox* ParkingCenter::getMotorcycleBox (ItemID_t keyTargetID) const 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
	
	MotorcycleBox* pTempBox = NULL;

	try 
	{
		__ENTER_CRITICAL_SECTION(m_Mutex)

		hash_map< ItemID_t , MotorcycleBox* >::const_iterator itr = m_Motorcycles.find(keyTargetID);

		if (itr == m_Motorcycles.end())
		{
			//cerr << "ParkingCenter::getMotorcycleBox() : NoSuchElementException" << endl;
			//throw NoSuchElementException();

			m_Mutex.unlock();
			return NULL;
		}

		pTempBox = itr->second;

		__LEAVE_CRITICAL_SECTION(m_Mutex)

		return pTempBox;
	} 
	catch (Throwable & t) 
	{
		//cerr << "아직 찾지 않았거나, 열쇠가 잘못된 오토바이 입니당." << endl;
		return NULL;
	}

	__END_CATCH
}

// 이건  ClientManager thread에서 돌아간다.
void ParkingCenter::heartbeat()
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexRemove)

	list<MotorcycleBox*>::iterator itr = m_RemoveMotorcycles.begin();
	
	for (; itr!=m_RemoveMotorcycles.end(); itr++)
	{
		MotorcycleBox* pMotorcycleBox = *itr;

		SAFE_DELETE( pMotorcycleBox );
	}

	m_RemoveMotorcycles.clear();

	__LEAVE_CRITICAL_SECTION(m_MutexRemove)

	__END_CATCH
}

// global variable definition
ParkingCenter* g_pParkingCenter = NULL;
