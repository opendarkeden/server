//---------------------------------------------------------------------------
// Filename   : PaySystem.h
// Written by : sigi
// Description : 
//---------------------------------------------------------------------------
// 아직 구현 안된 것 :
//   PC방 사용 시간 뺄 때.. 남은 사용 시간이 60분*UserLimit보다 적은 경우에
//   그 타이밍에 게임방에서 UserLimit까지 다~ 접속하면
//   최대 60분*(UserLimit-1명)까지의 시간을 더 play할 수 있게 된다.
//   
// 해결 방법 :
//   게임방인 경우는 UserLimit를 고려해서
//   시간이 60분*UserLimit보다 적으면
//   시간 체크 타이밍을 60분/UserLimit로 해야될까? -_-
//   좀 더 효율적인게 없나?
//   일단은 서비스로 남겨둘까?
//
// --> updatePayPlayTime()에서 처리했다.
//---------------------------------------------------------------------------

#include "PaySystem.h"
#include "database/DB.h"
#include "Thread.h"

#include "Properties.h"

//---------------------------------------------------------------------------
// 몇 초마다 체크할 것인가?
//---------------------------------------------------------------------------
const int DELAY_PAY_TIME_UPDATE = 3600;	// 1시간 = 60분
//const int DELAY_PAY_TIME_UPDATE = 10;	// 10초마다 - 테스트용
const int MINUTE_PAY_TIME_DECREASE = DELAY_PAY_TIME_UPDATE/60;
//const int MINUTE_PAY_TIME_DECREASE = 60;

//---------------------------------------------------------------------------
// 정량제인 경우.. '몇 시 까지' 사용가능하다고 할 때.. 
// 몇분을 서비스로 제공한다.
//---------------------------------------------------------------------------
//const int PLUS_DEADLINE_MIN 	= 10;
const int PLUS_DEADLINE_SECOND	= 59;

//---------------------------------------------------------------------------
//
// constructor / destructor
//
//---------------------------------------------------------------------------
PaySystem::PaySystem()
{
	// 개인요금지불체계에 대한 설정..이라고 볼 수 있다. 변수명 바꿔야된당 -_-;
	m_bSetPersonValue = false;

	m_PayPlayType = PAY_PLAY_TYPE_PERSON;        		// 개인/겜방..
	m_PayType = PAY_TYPE_FREE;          		// 무료/시간/기간/기타..
	m_PayIPType = PAY_IP_TYPE_ALL;        		// 게임방인 경우의 IP type

	m_PayPlayStartTime.tv_sec = 0;
	m_PayPlayStartTime.tv_usec = 0;

	m_PayPlayAvailableHours = 0;

	m_PayPlayFlag = 0;
	m_PCRoomID = 0;

	m_UserLimit = 0;
	m_UserMax = 0;

	m_bPremiumPlay = false;
	m_bPCRoomPlay = false;

	m_bFamilyPayAvailable = false;
	m_FamilyPayPartyType = FAMILY_PAY_PARTY_TYPE_NONE;
}

PaySystem::~PaySystem()
{
}

//---------------------------------------------------------------------------
// set Pay PlayAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setPayPlayAvailableDateTime(const string& pat) 
	throw (Error)
{
	__BEGIN_TRY

	
	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if (pat.size()==19)
	{
		int year  = atoi( pat.substr(0,4).c_str() );
		int month = atoi( pat.substr(5,2).c_str() );
		int day   = atoi( pat.substr(8,2).c_str() );
		int hour  = atoi( pat.substr(11,2).c_str() );
		int min   = atoi( pat.substr(14,2).c_str() );
		//int sec   = atoi( pat.substr(10,2).c_str() );

		// play가능한 한계 시간을 지정해둔다.
		m_PayPlayAvailableDateTime.setDate( VSDate(year, month, day) );
		m_PayPlayAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// 접속 불가 상태로 설정
		m_PayPlayAvailableDateTime.setDate( VSDate(2002, 1, 1) );
		m_PayPlayAvailableDateTime.setTime( VSTime(12, 10, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// set Family Pay PlayAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setFamilyPayPlayAvailableDateTime(const string& pat) 
	throw (Error)
{
	__BEGIN_TRY

	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if (pat.size()==19)
	{
		int year  = atoi( pat.substr(0,4).c_str() );
		int month = atoi( pat.substr(5,2).c_str() );
		int day   = atoi( pat.substr(8,2).c_str() );
		int hour  = atoi( pat.substr(11,2).c_str() );
		int min   = atoi( pat.substr(14,2).c_str() );
		//int sec   = atoi( pat.substr(10,2).c_str() );

		// play가능한 한계 시간을 지정해둔다.
		m_FamilyPayPlayAvailableDateTime.setDate( VSDate(year, month, day) );
		m_FamilyPayPlayAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// 접속 불가 상태로 설정
		m_FamilyPayPlayAvailableDateTime.setDate( VSDate(2002, 1, 1) );
		m_FamilyPayPlayAvailableDateTime.setTime( VSTime(12, 10, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// set Pay StartAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setPayStartAvailableDateTime(const string& pat) 
	throw (Error)
{
	__BEGIN_TRY

	
	// 0123456789012345678
	// YYYY-MM-DD HH:MM:SS
	if (pat.size()==19)
	{
		int year  = atoi( pat.substr(0,4).c_str() );
		int month = atoi( pat.substr(5,2).c_str() );
		int day   = atoi( pat.substr(8,2).c_str() );
		int hour  = atoi( pat.substr(11,2).c_str() );
		int min   = atoi( pat.substr(14,2).c_str() );
		//int sec   = atoi( pat.substr(10,2).c_str() );

		// play가능한 한계 시간을 지정해둔다.
		m_PayStartAvailableDateTime.setDate( VSDate(year, month, day) );
		m_PayStartAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// 시작 불가 상태로 설정
		m_PayStartAvailableDateTime.setDate( VSDate(2099, 1, 1) );
		m_PayStartAvailableDateTime.setTime( VSTime(0, 0, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// is Pay PlayAvailable
//---------------------------------------------------------------------------
bool PaySystem::checkPayPlayAvailable()
{
	if (m_PayType!=PAY_TYPE_FREE && m_PayType!=PAY_TYPE_POST)
	{
		VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

		// 패밀리 요금제 사용가능한지 체크한다.
		if ( m_PayPlayAvailableDateTime != m_FamilyPayPlayAvailableDateTime
			&& currentDateTime <= m_FamilyPayPlayAvailableDateTime )
		{
			m_PayPlayAvailableDateTime = m_FamilyPayPlayAvailableDateTime;
			m_bFamilyPayAvailable = true;
		}

		// PC방인 경우만 StartDate를 체크한다.
		bool bAvailable = (m_PayPlayType!=PAY_PLAY_TYPE_PCROOM || currentDateTime >= m_PayStartAvailableDateTime)
							&& currentDateTime <= m_PayPlayAvailableDateTime;

		//cout << "checkPayPlay: " << currentDateTime.toString() << " <= " << m_PayPlayAvailableDateTime.toString() << endl;

		// 정량제 요금
		if (bAvailable)
		{
			m_PayType = PAY_TYPE_PERIOD;
		}
		else
		{ 
			bAvailable = m_PayPlayAvailableHours > 0;

			// 종량제 요금
			if (bAvailable)
			{
				m_PayType = PAY_TYPE_TIME;
			}
		}

		return bAvailable;
	}
	else if (m_PayType == PAY_TYPE_POST)
	{
		VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

		if (currentDateTime <= m_PayPlayAvailableDateTime)
			return true;
		else
			return false;
	}

	/*
	switch (m_PayType)
	{
		case PAY_TYPE_PERIOD :
		{
			VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());
			return currentDateTime <= m_PayPlayAvailableDateTime;
		}

		case PAY_TYPE_TIME :
		{
			return m_PayPlayAvailableHours > 0;
		}

		default : break;
	}
	*/

	return true;
}

//---------------------------------------------------------------------------
// set PayPlayValue
//---------------------------------------------------------------------------
void PaySystem::setPayPlayValue(PayType payType,
								const string& payPlayDate, int payPlayHours, uint payPlayFlag, const string& familyPayPlayDate)
{
	setPayType( payType );
	setPayPlayAvailableDateTime( payPlayDate );
	setPayPlayAvailableHours( payPlayHours );
	setPayPlayFlag( payPlayFlag );
	setFamilyPayPlayAvailableDateTime( familyPayPlayDate );

	m_bSetPersonValue = true;
}


//---------------------------------------------------------------------------
// update Pay PlayTime
//---------------------------------------------------------------------------
bool PaySystem::updatePayPlayTime(const string& playerID, const VSDateTime& currentDateTime, const Timeval& currentTime)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY

	switch (m_PayType)
	{
		//-----------------------------------------
		// 기간제 사용자인 경우
		//-----------------------------------------
		case PAY_TYPE_PERIOD :
		{
			// 한 시간 정도에 한 번씩 체크한다.
			// 기간제 사용자인 경우는 1시간 정도 서비스되어도 문제 없다고 본다
			if (currentTime.tv_sec >= m_PayPlayStartTime.tv_sec + DELAY_PAY_TIME_UPDATE)
			{
				m_PayPlayStartTime.tv_sec = currentTime.tv_sec;

				//cout << "[PAY_TYPE_PERIOD] " << endl;
				//cout << "CurrentDateTime = " << currentDateTime.toString().c_str() << endl;
				//cout << "PayPlayAvaiable = " << m_PayPlayAvailableDateTime.toString().c_str() << endl << endl;

				// 시간이 지났으면.. 짜른다.
				if (currentDateTime > m_PayPlayAvailableDateTime)
				{
					//throw ProtocolException("사용시간이 다됐다.");
					m_PayPlayStartTime.tv_sec = 0;
					m_bPremiumPlay = false;
					return false;
				}
			}
		}
		break;

		//-----------------------------------------
		// 시간제 사용자인 경우
		//-----------------------------------------
		case PAY_TYPE_TIME :
		{
			int elapsedSec = currentTime.tv_sec - m_PayPlayStartTime.tv_sec;
			int remainSec = m_PayPlayAvailableHours*60;
			int UserMax = m_UserMax;


			// 요금을 줄이는 경우..
			if (m_PayPlayStartTime.tv_sec != 0
					// [1] 1시간마다 DB를 update 시킨다.
				&& (currentTime.tv_sec >= m_PayPlayStartTime.tv_sec + DELAY_PAY_TIME_UPDATE
					// [2] 사용시간이 1시간도 안 남았다면.. 바로 체크..
					|| m_PayPlayAvailableHours < MINUTE_PAY_TIME_DECREASE
						&& elapsedSec > remainSec
					// [3] PC방 요금이고 
					//      남은 시간이 1시간*UserMax 보다 적고, 
					// 		사용시간*UserMax가 남은 시간보다 크면.. (UserMax는 1~12로 제한:너무 자주 체크하지 않게하기 위해서)
					//        또는, 남은 minute가 사용자수보다 작으면(1분씩도 못 쓴다면), 1분마다 체크한다.
					|| m_PayPlayType==PAY_PLAY_TYPE_PCROOM 
						//&& elapsedSec <= DELAY_PAY_TIME_UPDATE
						&& m_PayPlayAvailableHours < MINUTE_PAY_TIME_DECREASE*UserMax
						&& (elapsedSec * (min(12, max(1, (int)m_UserMax))) > remainSec
							|| elapsedSec>=60 && m_PayPlayAvailableHours <= UserMax)
					)
				)
			{
				// 분단위로 바꾼다.
				int decreaseMin = (currentTime.tv_sec - m_PayPlayStartTime.tv_sec)/60;

				// 다쉬 1시간을 기다륀다.
				if (decreaseMin > 0)
				{
					m_PayPlayStartTime.tv_sec = currentTime.tv_sec;
			
					switch (m_PayPlayType)
					{
						case PAY_PLAY_TYPE_PERSON :
							// DB에서 사용자 시간을 1시간 빼준다.
							//m_PayPlayAvailableHours -= 60;

							// DB에 저장해야한다.
							decreasePayPlayTime(playerID, decreaseMin);//MINUTE_PAY_TIME_DECREASE);
						break;

						case PAY_PLAY_TYPE_PCROOM :
							// DB에서 게임방 시간을 1시간 빼준다.
							//m_PayPlayAvailableHours -= 60;

							// 여러명이서 할 수 있으므로.. 
							// 다시 DB에서 남은 시간을 읽어온다.
							decreasePayPlayTimePCRoom(decreaseMin);//MINUTE_PAY_TIME_DECREASE);
						break;

						default : break;
					}
				}

				if (m_PayPlayAvailableHours <= 0)
				{
					//throw ProtocolException("사용시간이 다됐다.");
					m_PayPlayStartTime.tv_sec = 0;
					m_bPremiumPlay = false;
					return false;
				}
			}
		}
		break;

		default : break;
	}

	return true;

	__END_CATCH
}

//---------------------------------------------------------------------------
// login Pay PlayPCRoom IP
//---------------------------------------------------------------------------
// ip가 PCRoomIPInfo에 있다면 그 ID를 가진 PCRoom을 PCRoomInfo에서 찾아서
// 그 정보를 읽어들인다.
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlayPCRoom(const string& ip, const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	//Statement* pStmt = NULL;
	//cout << "[loginPayPlayPCRoom] from = " << ip.c_str() << ", " << playerID.c_str() << endl;

	BEGIN_DB
	{
		try {
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		try {
			pResult = pStmt->executeQuery( 
				"SELECT r.ID, r.PayType, r.PayStartDate, r.PayPlayDate, r.PayPlayHours, r.PayPlayFlag, r.UserLimit, r.UserMax FROM PCRoomInfo r, PCRoomIPInfo p WHERE p.IP='%s' AND p.ID=r.ID",
					ip.c_str());
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		if (pResult!=NULL && pResult->next())
		{
			uint i = 0;

			setPCRoomID( pResult->getInt(++i) );
			setPayType( (PayType)pResult->getInt(++i) );
			setPayStartAvailableDateTime( pResult->getString(++i) );
			setPayPlayAvailableDateTime( pResult->getString(++i) );
			setPayPlayAvailableHours( pResult->getInt(++i) );
			setPayPlayFlag( pResult->getInt(++i) );
			m_UserLimit 	= pResult->getInt(++i);
			m_UserMax 		= pResult->getInt(++i);

			// 이상한 종량제 관련 코드
			if ( m_PayType == PAY_TYPE_POST )
			{
				VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

				// 제한된 날짜 이후면 적용 안되야 하므로
				if ( currentDateTime <= m_PayPlayAvailableDateTime )
				{
					setPayPlayType( PAY_PLAY_TYPE_PCROOM );
					m_bPCRoomPlay = true;
					return true;
				}

				return false;
			}

			//m_UserMax = max((unsigned int)5, m_UserMax);
			//m_UserMax = min((unsigned int)12, m_UserMax);
			m_UserMax = 15;	// 한 겜방 최대 15명

			pResult = pStmt->executeQuery(
				"SELECT count(*) from PCRoomUserInfo WHERE ID=%d", m_PCRoomID );

			if (pResult->next())
			{
				uint users = pResult->getInt(1);

				setPayPlayType( PAY_PLAY_TYPE_PCROOM );
				bool bAvailable = checkPayPlayAvailable();

				//
				// [PC방 사용자수 제한]
				//
				// 정액제 : UserLimit 넘어가면 안된다.
				// 종량제 : UserMax 넘어가면 안된다 <-- 사실 큰 의미는 없다. 
				//
				if (m_PayType==PAY_TYPE_PERIOD && users >= m_UserLimit
					|| m_PayType==PAY_TYPE_TIME && users >= m_UserMax)
				{
					//cout << "[PayPCRoom] User Limit Exceed!" << endl;
					SAFE_DELETE(pStmt);

					return false;
				}

				// 사용가능하다면..
				if (bAvailable)
				{
					// 일단 사용자를 추가해보는데..
					try {
						pStmt->executeQuery(
							"INSERT IGNORE INTO PCRoomUserInfo(ID, PlayerID) VALUES(%d, '%s')",
							m_PCRoomID, playerID.c_str());
					} catch (SQLQueryException& se) {
						filelog("paySystem.txt", "%s", se.toString().c_str());
						// 그냥 넘어갈까
					}

					// 추가한 뒤의 사용자 숫자를 확인해보고..
					pResult = pStmt->executeQuery(
						"SELECT count(*) from PCRoomUserInfo WHERE ID=%d", m_PCRoomID );
					
					if (pResult->next())
					{
						users = pResult->getInt(1);

						// PC방 사용자수 제한을 넘어가면...
						if (m_PayType==PAY_TYPE_PERIOD && users >= m_UserLimit
							|| m_PayType==PAY_TYPE_TIME && users >= m_UserMax)
						{
							// 추가했던걸 다시 지우고..
							pStmt->executeQuery(
								"DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
									playerID.c_str());

							//cout << "[PayPCRoom] User Limit Exceed2!" << endl;

							// 사용 불가..
							SAFE_DELETE(pStmt);

							return false;
						}
						else
						{
							// 정상적인 경우
							SAFE_DELETE(pStmt);

							m_bPCRoomPlay = true;

							return true;
						}
					}
				}
			}
		}

		SAFE_DELETE(pStmt);

	} catch(SQLQueryException& sqe) { 
		SAFE_DELETE(pStmt);

		filelog("paySystem.txt", "%s", sqe.toString().c_str());
		throw;
	}

	return false;

	__END_CATCH
}

//---------------------------------------------------------------------------
// logout Pay PlayPCRoomIP
//---------------------------------------------------------------------------
void PaySystem::logoutPayPlayPCRoom(const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	if (m_PayPlayType==PAY_PLAY_TYPE_PCROOM)
	{
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

			// 추가했던걸 다시 지우고..
			pStmt->executeQuery( "DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
											playerID.c_str());

			SAFE_DELETE(pStmt);
		//} END_DB(pStmt);
		} catch(SQLQueryException& sqe) { 
			SAFE_DELETE(pStmt);
			filelog("paySystem.txt", "%s", sqe.toString().c_str());
			throw;
		}

	
	}

	__END_CATCH
}


//---------------------------------------------------------------------------
// login PayPlay
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlay(PayType payType, 
							const string& payPlayDate, int payPlayHours, uint payPlayFlag,
							const string& ip, const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	// 아직 logout이 된 상태가 아니면..
	if (m_PayPlayStartTime.tv_sec != 0)
	{
		return true;
	}

	m_PayPlayStartTime.tv_sec = 0;

	/*
	cout << "[PaySystem::loginPayPlay] "
		<< "PlayerID = " << playerID.c_str() << ", "
		<< "PayType = " << (int)payType << endl
		<< "payPlayDate = " << payPlayDate.c_str() << endl
		<< "payPlayHours = " << (int)payPlayHours << endl
		<< "payPlayFlag = " << (int)payPlayFlag << endl;
	*/

//	if ( g_pConfig->getPropertyInt( "IsNetMarble" ) )
//	{
//		payType = PAY_TYPE_FREE;
//	}

	// 빌링 by sigi. 2002.5.31
	// FREE, PERIOD, TIME, PART
	setPayType(payType);

	//--------------------------------------------------
	// 개인 사용자 요금체계에 대한 체크
	//--------------------------------------------------
	if (payType!=PAY_TYPE_FREE)
	{
		setPayPlayType( PAY_PLAY_TYPE_PERSON );

		setPayPlayAvailableDateTime( payPlayDate );
		setPayPlayAvailableHours( payPlayHours );
		setPayPlayFlag( payPlayFlag );

		if ( !checkPayPlayAvailable() || m_PayType == PAY_TYPE_TIME )
		{
			// 게임방 먼저 체크
			if ( !loginPayPlayPCRoom(ip, playerID) )
			{
				// loginPayPlayPCRoom에서 값이 바뀌므로.. -_-;
				// 개인 사용자 정보 설정
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayType( payType );
				setPayPlayAvailableDateTime( payPlayDate );
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );

				// 개인 사용자 체크
				if (!checkPayPlayAvailable())
				{
					return false;
				}
			}
			else
			{
				// 다음에 개인요금지불체계 정보를 읽어야 하므로..
				m_bSetPersonValue = false;
			}
		}
		// 개인 정액 사용자도 PC 방 보너스를 적용시켜주기 위해서
		else if ( m_PayType == PAY_TYPE_PERIOD )
		{
			// PC 방 로긴해보고 되면 -_-;;
			if ( loginPayPlayPCRoom(ip, playerID) )
			{
				// PC 방 로그 아웃 하고
				logoutPayPlayPCRoom( playerID );
				// 값 다시 원래대로 돌려주기
				setPayType(payType);
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayPlayAvailableDateTime( payPlayDate );
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );
			}
		}
	}

	__END_CATCH

	getCurrentTime(m_PayPlayStartTime);

	// PayType을 설정한다.
	checkPayPlayAvailable();
	m_bPremiumPlay = true;

	return true;
}

//---------------------------------------------------------------------------
// login PayPlay
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlay(const string& ip, const string& playerID)
	throw (Error)
{

	Statement* pStmt = NULL;

	__BEGIN_TRY

	// 아직 logout이 된 상태가 아니면..
	if (m_PayPlayStartTime.tv_sec != 0)
	{
		return true;
	}

	m_PayPlayStartTime.tv_sec = 0;


	if (!m_bSetPersonValue)
	{

		BEGIN_DB
		{
			//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

			Result* pResult = pStmt->executeQuery( "SELECT PayType, PayPlayDate, PayPlayHours, PayPlayFlag, FamilyPayPlayDate FROM Player WHERE PlayerID='%s'", playerID.c_str());

			if (pResult->getRowCount() == 0)
			{
				SAFE_DELETE(pStmt);

				//cout << "No PlayerID" << endl;
				return false;
			}

			pResult->next();

			setPayType( (PayType)pResult->getInt(1) );

			setPayPlayAvailableDateTime( pResult->getString(2) );
			setPayPlayAvailableHours( pResult->getInt(3) );
			setPayPlayFlag( pResult->getInt(4) );

			setFamilyPayPlayAvailableDateTime( pResult->getString(5) );

			SAFE_DELETE(pStmt);

		//} END_DB(pStmt)
		} catch(SQLQueryException& sqe) { 

			SAFE_DELETE(pStmt);

			filelog("paySystem.txt", "%s", sqe.toString().c_str());
			throw;
		}


	}

	/*
	cout << "[PaySystem::loginPayPlay] "
		<< "PlayerID = " << playerID.c_str() << ", "
		<< "PayType = " << (int)m_PayType << endl
		<< "payPlayDate = " << m_PayPlayAvailableDateTime.toString() << endl
		<< "payPlayHours = " << (int)m_PayPlayAvailableHours << endl
		<< "payPlayFlag = " << (int)m_PayPlayFlag << endl;
	*/

//	if ( g_pConfig->getPropertyInt( "IsNetMarble" ) )
//	{
//		setPayType( PAY_TYPE_FREE );
//	}

	// 빌링 by sigi. 2002.5.31
	// FREE, PERIOD, TIME, PART

	//--------------------------------------------------
	// 개인 사용자 요금체계에 대한 체크
	//--------------------------------------------------
	if (m_PayType!=PAY_TYPE_FREE)
	{
		// 개인 정액제 사용자인지 먼저 체크한다.
		setPayPlayType( PAY_PLAY_TYPE_PERSON );
		if (!checkPayPlayAvailable() || m_PayType != PAY_TYPE_PERIOD)
		{
			// loginPayPlayPCRoom에서 값이 바뀌므로.. -_-;
			PayType 	payType 	= m_PayType;
			VSDateTime 	payPlayDate = m_PayPlayAvailableDateTime;
			int 		payPlayHours = m_PayPlayAvailableHours;
			uint 		payPlayFlag = m_PayPlayFlag;

			// 게임방 먼저 체크
			if (!loginPayPlayPCRoom(ip, playerID))
			{
				// 개인 사용자 정보 설정
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayType( payType );
				m_PayPlayAvailableDateTime = payPlayDate;
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );

				// 개인 사용자 체크
				if (!checkPayPlayAvailable())
				{
					//cout << "No PayPlay" << endl;

					return false;
				}
			}
			else
			{
				// 다음에 개인요금지불체계 정보를 읽어야 하므로..
				m_bSetPersonValue = false;
			}
		}
		// 개인 정액 사용자도 PC 방 보너스를 적용시켜주기 위해서
		else if ( m_PayType == PAY_TYPE_PERIOD )
		{
			m_bPCRoomPlay = isPlayInPayPCRoom( ip, playerID );
		}
	}

	__END_CATCH

	getCurrentTime(m_PayPlayStartTime);

	// PayType을 설정한다.
	checkPayPlayAvailable();

	m_bPremiumPlay = true;

	//cout << "PayPlay Available : " << m_PayPlayAvailableDateTime.toString() << ", " << (int)m_PayPlayAvailableHours << endl;

	return true;
}


//---------------------------------------------------------------------------
// logout PayPlay
//---------------------------------------------------------------------------
void PaySystem::logoutPayPlay(const string& playerID, bool bClear, bool bDecreaseTime)
	throw (Error)
{
	__BEGIN_TRY

	// 시간이 다 돼서 짤리는 경우의 처리가 될 때
	// m_PayPlayStartTime.tv_sec = 0 으로 설정해놓은 상태이다.

	//if (m_PayPlayStartTime.tv_sec == 0)
	//	return;

	if (m_PayPlayType==PAY_PLAY_TYPE_PCROOM)
	{
		logoutPayPlayPCRoom(playerID);

		Timeval currentTime;
		getCurrentTime(currentTime);

		if (bDecreaseTime && m_PayType==PAY_TYPE_TIME)
		{

			int usedMin = (currentTime.tv_sec-m_PayPlayStartTime.tv_sec)/60;
			//usedMin = max(1, usedMin);

			if (usedMin > 0)
			{
				decreasePayPlayTimePCRoom(usedMin);
			}
		}
		else if (bDecreaseTime && m_PayType==PAY_TYPE_POST)
		{
			int usedMin = (currentTime.tv_sec-m_PayPlayStartTime.tv_sec)/60;

			if (usedMin > 0)
			{
				increasePayPlayTimePCRoom(usedMin);
			}
		}
	}
	else if (m_PayPlayType==PAY_PLAY_TYPE_PERSON)
	{
		if (bClear)
		{
			// 모든 Pay정보를 제거하고 무료사용자로 바꾼다. by sigi. 2002.11.18
			clearPayPlayDateTime(playerID);
		}
		else if (bDecreaseTime 
				&& m_PayType==PAY_TYPE_TIME
				&& m_PayPlayStartTime.tv_sec!=0)
		{
			Timeval currentTime;
			getCurrentTime(currentTime);

			int usedMin = (currentTime.tv_sec-m_PayPlayStartTime.tv_sec)/60;
			//usedMin = max(1, usedMin);

			if (usedMin > 0)
			{
				decreasePayPlayTime(playerID, usedMin);
			}
		}
	}

	m_PayPlayStartTime.tv_sec = 0;
	m_bPremiumPlay = false;

	__END_CATCH
}

//---------------------------------------------------------------------------
// clear PayPlayTime 
//---------------------------------------------------------------------------
// DB에서 사용시간을 제거한다.
void PaySystem::clearPayPlayDateTime(const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours = 0;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pStmt->executeQuery( 
				"UPDATE Player SET PayPlayHours=0, PayPlayDate='2002-11-18 00:00:00' WHERE PlayerID='%s'",
							playerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		
	__END_CATCH
}

//---------------------------------------------------------------------------
// decrease PayPlayTime 
//---------------------------------------------------------------------------
// DB에서 사용시간을 빼준다. 
void PaySystem::decreasePayPlayTime(const string& playerID, uint mm)
	throw (Error)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours -= mm;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pStmt->executeQuery( 
				"UPDATE Player SET PayPlayHours=PayPlayHours-%d WHERE PlayerID='%s'",
							mm, playerID.c_str());

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		
	__END_CATCH
}

//---------------------------------------------------------------------------
// decrease PayPlayTime PCRoom
//---------------------------------------------------------------------------
void PaySystem::decreasePayPlayTimePCRoom(uint mm)
	throw (Error)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours -= mm;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pStmt->executeQuery( 
			"UPDATE PCRoomInfo SET PayPlayHours=PayPlayHours-%d WHERE ID=%d",
							mm, m_PCRoomID);

		Result* pResult = pStmt->executeQuery(
			"SELECT PayPlayHours FROM PCRoomInfo WHERE ID=%d", m_PCRoomID);
							
		if (pResult->next())
		{
			m_PayPlayAvailableHours = pResult->getInt(1);
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		

	__END_CATCH
}

//---------------------------------------------------------------------------
// increase PayPlayTime PCRoom
//---------------------------------------------------------------------------
void PaySystem::increasePayPlayTimePCRoom(uint mm)
	throw (Error)
{
	__BEGIN_TRY

	VSDate vsDate = VSDate::currentDate();

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pResult = pStmt->executeQuery( 
			"SELECT PayPlayMinute FROM PCRoomPayList WHERE PCRoomID=%d AND Year=%d AND Month=%d" ,
							m_PCRoomID, vsDate.year(), vsDate.month() );
		
		if ( pResult->next() )
		{
			pStmt->executeQuery( 
				"UPDATE PCRoomPayList SET PayPlayMinute=PayPlayMinute+%d WHERE PCRoomID=%d AND Year=%d AND Month=%d" ,
								mm, m_PCRoomID, vsDate.year(), vsDate.month() );
		}
		else
		{
			pStmt->executeQuery( 
				"INSERT INTO PCRoomPayList (PCRoomID, Year, Month, PayPlayMinute) VALUES (%d, %d, %d, %d)",
								m_PCRoomID, vsDate.year(), vsDate.month(), mm );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
		

	__END_CATCH
}

bool PaySystem::isPayPlayingPeriodPersonal(const string& PlayerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	bool isPayPlay = false;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		Result* pResult = pStmt->executeQuery( "
			SELECT PayType=0 or PayPlayDate > now() FROM Player WHERE PlayerID='%s'",
			PlayerID.c_str());

		if (pResult->next())
		{
			isPayPlay = pResult->getInt(1)==1;
		}

		SAFE_DELETE(pStmt);

	//} END_DB(pStmt)
	} catch(SQLQueryException& sqe) { 

		SAFE_DELETE(pStmt);

		filelog("paySystem.txt", "%s", sqe.toString().c_str());
		throw;
	}

	return isPayPlay;

	__END_CATCH
}

//---------------------------------------------------------------------------
// ip가 PCRoomIPInfo에 있다면 그 ID를 가진 PCRoom을 PCRoomInfo에서 찾아서
// 그 정보를 읽어들인다.
// 유료 사용중인 피씨방에서 플레이 하고 있는지 확인하는 함수
// 개인 정액제일 경우 loginPayPlayPCRoom() 을 호출하지 않기 때문에 따로 확인을 한다.
//---------------------------------------------------------------------------
bool PaySystem::isPlayInPayPCRoom(const string& ip, const string& playerID)
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult = NULL;

	BEGIN_DB
	{
		try {
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		try {
			pResult = pStmt->executeQuery( 
				"SELECT r.ID, r.PayType, r.PayStartDate, r.PayPlayDate, r.PayPlayHours FROM PCRoomInfo r, PCRoomIPInfo p WHERE p.IP='%s' AND p.ID=r.ID",
					ip.c_str());
		} catch (Throwable& t) {
			filelog("paySystem.txt", "%s", t.toString().c_str());
			throw;
		}

		if (pResult!=NULL && pResult->next())
		{
			uint i = 0;

			ObjectID_t	pcRoomID = (ObjectID_t)pResult->getInt(++i);
			PayType		payType = (PayType)pResult->getInt(++i);
			VSDateTime	payStartAvailableDateTime( pResult->getString(++i) );
			VSDateTime	payPlayAvailableDateTime( pResult->getString(++i) );
			int			payPlayAvailableHours = pResult->getInt(++i);

			VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

			// 이상한 종량제 관련 코드
			if ( payType == PAY_TYPE_POST )
			{
				VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

				// 제한된 날짜 이후면 적용 안되야 하므로
				if ( currentDateTime <= payPlayAvailableDateTime )
					return true;

				return false;
			}

			// 유료 사용 가능한 PC 방인지 확인한다.
			bool bAvailable = ( payType == PAY_TYPE_FREE )
								|| ( ( currentDateTime >= payStartAvailableDateTime ) 
									&& ( currentDateTime <= payPlayAvailableDateTime ) )
								|| ( payPlayAvailableHours > 0 );

			// 유료 사용 가능한 PC 방일경우 PC 방 ID 를 세팅한다.
			if ( bAvailable )
				m_PCRoomID = pcRoomID;

			return bAvailable;
		}

		SAFE_DELETE(pStmt);

	} catch(SQLQueryException& sqe) { 
		SAFE_DELETE(pStmt);

		filelog("paySystem.txt", "%s", sqe.toString().c_str());
		throw;
	}

	return false;

	__END_CATCH
}

