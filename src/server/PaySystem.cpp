//---------------------------------------------------------------------------
// Filename   : PaySystem.h
// Written by : sigi
// Description : 
//---------------------------------------------------------------------------
// Pending item:
//   When deducting PC-room usage, if remaining time is below 60min*UserLimit
//   and everyone connects up to UserLimit at that moment,
//   they can effectively gain up to 60min*(UserLimit-1) extra play time.
//
// Ideas:
//   For PC rooms, consider UserLimit.
//   If remaining time is under 60min*UserLimit,
//   maybe shorten the check interval to 60min/UserLimit? (not ideal)
//   Is there a better approach? Maybe just leave it as service time.
//
// --> Handled in updatePayPlayTime().
//---------------------------------------------------------------------------

#include "PaySystem.h"
#include "database/DB.h"
#include "Thread.h"

#include "Properties.h"

//---------------------------------------------------------------------------
// How often should we check (seconds)?
//---------------------------------------------------------------------------
const int DELAY_PAY_TIME_UPDATE = 3600;	// 1 hour = 60 minutes
//const int DELAY_PAY_TIME_UPDATE = 10;	// every 10 seconds - for testing
const int MINUTE_PAY_TIME_DECREASE = DELAY_PAY_TIME_UPDATE/60;
//const int MINUTE_PAY_TIME_DECREASE = 60;

//---------------------------------------------------------------------------
// For period billing: when we say "usable until HH:MM",
// we allow a small grace window.
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
	// Defaults for personal billing; the variable names could be clearer.
	m_bSetPersonValue = false;

	m_PayPlayType = PAY_PLAY_TYPE_PERSON;        		// personal or PC-room
	m_PayType = PAY_TYPE_FREE;          		// free / time / period / other
	m_PayIPType = PAY_IP_TYPE_ALL;        		// IP type for PC-room billing

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

		// Set the latest playable datetime.
		m_PayPlayAvailableDateTime.setDate( VSDate(year, month, day) );
		m_PayPlayAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// Mark as not allowed to connect.
		m_PayPlayAvailableDateTime.setDate( VSDate(2002, 1, 1) );
		m_PayPlayAvailableDateTime.setTime( VSTime(12, 10, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// set Family Pay PlayAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setFamilyPayPlayAvailableDateTime(const string& pat) 
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

		// Set the latest playable datetime for family billing.
		m_FamilyPayPlayAvailableDateTime.setDate( VSDate(year, month, day) );
		m_FamilyPayPlayAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// Mark as not allowed to connect.
		m_FamilyPayPlayAvailableDateTime.setDate( VSDate(2002, 1, 1) );
		m_FamilyPayPlayAvailableDateTime.setTime( VSTime(12, 10, 0) );
	}

	__END_CATCH
}

//---------------------------------------------------------------------------
// set Pay StartAvailable DateTime
//---------------------------------------------------------------------------
void PaySystem::setPayStartAvailableDateTime(const string& pat) 
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

		// Set the earliest playable datetime for PC rooms.
		m_PayStartAvailableDateTime.setDate( VSDate(year, month, day) );
		m_PayStartAvailableDateTime.setTime( VSTime(hour, min, PLUS_DEADLINE_SECOND) );
	}
	else
	{
		// Mark as not allowed to start.
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

		// Check whether the family plan applies.
		if ( m_PayPlayAvailableDateTime != m_FamilyPayPlayAvailableDateTime
			&& currentDateTime <= m_FamilyPayPlayAvailableDateTime )
		{
			m_PayPlayAvailableDateTime = m_FamilyPayPlayAvailableDateTime;
			m_bFamilyPayAvailable = true;
		}

		// Only PC rooms check the start date.
		bool bAvailable = (m_PayPlayType!=PAY_PLAY_TYPE_PCROOM || currentDateTime >= m_PayStartAvailableDateTime)
							&& currentDateTime <= m_PayPlayAvailableDateTime;

		//cout << "checkPayPlay: " << currentDateTime.toString() << " <= " << m_PayPlayAvailableDateTime.toString() << endl;

		// Period billing
		if (bAvailable)
		{
			m_PayType = PAY_TYPE_PERIOD;
		}
		else
		{ 
			bAvailable = m_PayPlayAvailableHours > 0;

			// Time billing
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
{
	__BEGIN_TRY

	switch (m_PayType)
	{
		//-----------------------------------------
		// Period-plan user
		//-----------------------------------------
		case PAY_TYPE_PERIOD :
		{
			// Check roughly once an hour; a one-hour grace window is acceptable for period plans.
			if (currentTime.tv_sec >= m_PayPlayStartTime.tv_sec + DELAY_PAY_TIME_UPDATE)
			{
				m_PayPlayStartTime.tv_sec = currentTime.tv_sec;

				//cout << "[PAY_TYPE_PERIOD] " << endl;
				//cout << "CurrentDateTime = " << currentDateTime.toString().c_str() << endl;
				//cout << "PayPlayAvaiable = " << m_PayPlayAvailableDateTime.toString().c_str() << endl << endl;

				// If expired, cut off.
				if (currentDateTime > m_PayPlayAvailableDateTime)
				{
					//throw ProtocolException("Play time exhausted.");
					m_PayPlayStartTime.tv_sec = 0;
					m_bPremiumPlay = false;
					return false;
				}
			}
		}
		break;

		//-----------------------------------------
		// Time-plan user
		//-----------------------------------------
		case PAY_TYPE_TIME :
		{
			int elapsedSec = currentTime.tv_sec - m_PayPlayStartTime.tv_sec;
			int remainSec = m_PayPlayAvailableHours*60;
			int UserMax = m_UserMax;


			// When reducing remaining time..
			if (m_PayPlayStartTime.tv_sec != 0
					// [1] Update DB every hour.
				&& (currentTime.tv_sec >= m_PayPlayStartTime.tv_sec + DELAY_PAY_TIME_UPDATE
					// [2] If less than an hour remains, check immediately.
					|| m_PayPlayAvailableHours < MINUTE_PAY_TIME_DECREASE
						&& elapsedSec > remainSec
					// [3] PC-room billing: remaining time is under 1h*UserMax and
					//     elapsed*UserMax exceeds remaining (UserMax limited 1~12 to avoid too many checks),
					//     or remaining minutes are fewer than users, so check each minute.
					|| m_PayPlayType==PAY_PLAY_TYPE_PCROOM 
						//&& elapsedSec <= DELAY_PAY_TIME_UPDATE
						&& m_PayPlayAvailableHours < MINUTE_PAY_TIME_DECREASE*UserMax
						&& (elapsedSec * (min(12, max(1, (int)m_UserMax))) > remainSec
							|| elapsedSec>=60 && m_PayPlayAvailableHours <= UserMax)
					)
				)
			{
				// Convert to minutes.
				int decreaseMin = (currentTime.tv_sec - m_PayPlayStartTime.tv_sec)/60;

				// After updating, wait for the next hour window.
				if (decreaseMin > 0)
				{
					m_PayPlayStartTime.tv_sec = currentTime.tv_sec;
			
					switch (m_PayPlayType)
					{
						case PAY_PLAY_TYPE_PERSON :
							// Subtract user minutes in DB.
							decreasePayPlayTime(playerID, decreaseMin);//MINUTE_PAY_TIME_DECREASE);
						break;

						case PAY_PLAY_TYPE_PCROOM :
							// Subtract PC-room minutes in DB; refresh because many can play.
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
// If the IP exists in PCRoomIPInfo, load the matching PCRoomInfo row
// and read its settings.
//---------------------------------------------------------------------------
bool PaySystem::loginPayPlayPCRoom(const string& ip, const string& playerID)
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

			// Legacy post-pay logic
			if ( m_PayType == PAY_TYPE_POST )
			{
				VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

				// Do not allow usage after the limited date.
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
			m_UserMax = 15;	// Max 15 people per PC room

			pResult = pStmt->executeQuery(
				"SELECT count(*) from PCRoomUserInfo WHERE ID=%d", m_PCRoomID );

			if (pResult->next())
			{
				uint users = pResult->getInt(1);

				setPayPlayType( PAY_PLAY_TYPE_PCROOM );
				bool bAvailable = checkPayPlayAvailable();

				//
				// [PC-room user limits]
				//
				// Period: must stay under UserLimit.
				// Time: must stay under UserMax (rough safeguard).
				//
				if (m_PayType==PAY_TYPE_PERIOD && users >= m_UserLimit
					|| m_PayType==PAY_TYPE_TIME && users >= m_UserMax)
				{
					//cout << "[PayPCRoom] User Limit Exceed!" << endl;
					SAFE_DELETE(pStmt);

					return false;
				}

				// If available..
				if (bAvailable)
				{
					// Tentatively insert the user.
					try {
						pStmt->executeQuery(
							"INSERT IGNORE INTO PCRoomUserInfo(ID, PlayerID) VALUES(%d, '%s')",
							m_PCRoomID, playerID.c_str());
					} catch (SQLQueryException& se) {
						filelog("paySystem.txt", "%s", se.toString().c_str());
						// 그냥 넘어갈까
					}

					// Check the user count after insertion.
					pResult = pStmt->executeQuery(
						"SELECT count(*) from PCRoomUserInfo WHERE ID=%d", m_PCRoomID );
					
					if (pResult->next())
					{
						users = pResult->getInt(1);

						// If PC-room user limits are exceeded...
						if (m_PayType==PAY_TYPE_PERIOD && users >= m_UserLimit
							|| m_PayType==PAY_TYPE_TIME && users >= m_UserMax)
						{
							// Remove the row we just inserted.
							pStmt->executeQuery(
								"DELETE FROM PCRoomUserInfo WHERE PlayerID='%s'",
									playerID.c_str());

							//cout << "[PayPCRoom] User Limit Exceed2!" << endl;

							// Not allowed.
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
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	if (m_PayPlayType==PAY_PLAY_TYPE_PCROOM)
	{
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

			// Remove the row we inserted earlier.
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
{
	__BEGIN_TRY

	// If already logged in, reuse the session.
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

	// Billing (sigi, 2002-05-31): FREE, PERIOD, TIME, PART
	setPayType(payType);

	//--------------------------------------------------
	// Check personal billing first
	//--------------------------------------------------
	if (payType!=PAY_TYPE_FREE)
	{
		setPayPlayType( PAY_PLAY_TYPE_PERSON );

		setPayPlayAvailableDateTime( payPlayDate );
		setPayPlayAvailableHours( payPlayHours );
		setPayPlayFlag( payPlayFlag );

		if ( !checkPayPlayAvailable() || m_PayType == PAY_TYPE_TIME )
		{
			// Try PC-room billing first.
			if ( !loginPayPlayPCRoom(ip, playerID) )
			{
				// loginPayPlayPCRoom mutates values, so restore personal info.
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayType( payType );
				setPayPlayAvailableDateTime( payPlayDate );
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );

				// Personal billing check
				if (!checkPayPlayAvailable())
				{
					return false;
				}
			}
			else
			{
				// Need to reload personal billing next time.
				m_bSetPersonValue = false;
			}
		}
		// Apply PC-room bonus even for personal period users.
		else if ( m_PayType == PAY_TYPE_PERIOD )
		{
			// If PC-room login works,
			if ( loginPayPlayPCRoom(ip, playerID) )
			{
				// Logout from PC room
				logoutPayPlayPCRoom( playerID );
				// Restore personal values
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
{

	Statement* pStmt = NULL;

	__BEGIN_TRY

	// If already logged in, reuse the session.
	if (m_PayPlayStartTime.tv_sec != 0)
	{
		return true;
	}

	m_PayPlayStartTime.tv_sec = 0;


	if (!m_bSetPersonValue)
	{

		BEGIN_DB
		{
			//pStmt = g_pDatabaseManager->getConnection((int)(long)Thread::self())->createStatement();
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

	// Billing (sigi, 2002-05-31): FREE, PERIOD, TIME, PART

	//--------------------------------------------------
	// Check personal billing first
	//--------------------------------------------------
	if (m_PayType!=PAY_TYPE_FREE)
	{
		// First check whether this is a personal period plan.
		setPayPlayType( PAY_PLAY_TYPE_PERSON );
		if (!checkPayPlayAvailable() || m_PayType != PAY_TYPE_PERIOD)
		{
			// loginPayPlayPCRoom mutates values, so save/restore.
			PayType 	payType 	= m_PayType;
			VSDateTime 	payPlayDate = m_PayPlayAvailableDateTime;
			int 		payPlayHours = m_PayPlayAvailableHours;
			uint 		payPlayFlag = m_PayPlayFlag;

			// Try PC-room first
			if (!loginPayPlayPCRoom(ip, playerID))
			{
				// Restore personal billing info
				setPayPlayType( PAY_PLAY_TYPE_PERSON );

				setPayType( payType );
				m_PayPlayAvailableDateTime = payPlayDate;
				setPayPlayAvailableHours( payPlayHours );
				setPayPlayFlag( payPlayFlag );

				// Personal billing check
				if (!checkPayPlayAvailable())
				{
					//cout << "No PayPlay" << endl;

					return false;
				}
			}
			else
			{
				// Need to reload personal billing on next login.
				m_bSetPersonValue = false;
			}
		}
		// Apply PC-room bonus even for personal period users.
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
{
	__BEGIN_TRY

	// When kicked for time-out, m_PayPlayStartTime.tv_sec is set to 0.

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
			// Clear all pay info and switch to free user. (sigi, 2002-11-18)
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
// Remove play time from DB.
void PaySystem::clearPayPlayDateTime(const string& playerID)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours = 0;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)(long)Thread::self())->createStatement();
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
// Subtract play time in DB.
void PaySystem::decreasePayPlayTime(const string& playerID, uint mm)
{
	__BEGIN_TRY

	m_PayPlayAvailableHours -= mm;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)(long)Thread::self())->createStatement();
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
{
	__BEGIN_TRY

	m_PayPlayAvailableHours -= mm;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)(long)Thread::self())->createStatement();
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
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	bool isPayPlay = false;

	BEGIN_DB
	{
		//pStmt = g_pDatabaseManager->getConnection((int)(long)Thread::self())->createStatement();
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		Result* pResult = pStmt->executeQuery("SELECT PayType=0 or PayPlayDate > now() FROM Player WHERE PlayerID='%s'",
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
// If the IP exists in PCRoomIPInfo, load the matching PCRoomInfo row.
// Check whether the player is playing in a paid PC room.
// Personal period-plan users skip loginPayPlayPCRoom(), so verify separately.
//---------------------------------------------------------------------------
bool PaySystem::isPlayInPayPCRoom(const string& ip, const string& playerID)
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

			// Legacy post-pay logic
			if ( payType == PAY_TYPE_POST )
			{
				VSDateTime currentDateTime(VSDate::currentDate(), VSTime::currentTime());

				// Do not allow after the limited date.
				if ( currentDateTime <= payPlayAvailableDateTime )
					return true;

				return false;
			}

			// Determine if this PC room is allowed for paid use.
			bool bAvailable = ( payType == PAY_TYPE_FREE )
								|| ( ( currentDateTime >= payStartAvailableDateTime ) 
									&& ( currentDateTime <= payPlayAvailableDateTime ) )
								|| ( payPlayAvailableHours > 0 );

			// If allowed, record the PC-room ID.
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

