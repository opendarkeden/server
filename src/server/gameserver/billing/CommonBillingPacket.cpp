//////////////////////////////////////////////////////////////////////////////
// Filename    : CommonBillingPacket.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CommonBillingPacket.h"
#include "Assert.h"
#include "Properties.h"
#include <netinet/in.h>
#include "DB.h"
#include "VSDateTime.h"

void CommonBillingPacket::test ()
{
	__BEGIN_TRY

	cout << "CommonBillingPacket Test... ";

	Packet_Type = 1;
	Result = 2;
	strcpy(S_KEY, "S_KEY");
	strcpy(Session, "Session");
	strcpy(User_CC, "UCC");
	strcpy(User_No, "User_NO");
	strcpy(User_ID, "User_ID");
	strcpy(User_IP, "User_IP");
	User_Gender = 'M';
	strcpy(User_Status, "ST");
	strcpy(User_PayType, "PT");
	User_Age = 26;
	Game_No = 777;
	strcpy(Bill_PayType, "A");
	strcpy(Bill_Method, "B");
	strcpy(Expire_Date, "20021115120");
	Remain_Time = 500;

	
	char pBuffer[256];

	int len = getPacketSize();

	//---------------------------------------
	// write
	//---------------------------------------
	Packet_Type = htonl(Packet_Type);
	Result 		= htonl(Result);
	User_Age 	= htonl(User_Age);
	Game_No 	= htonl(Game_No);
	Remain_Time = htonl(Remain_Time);

	const BillingInfo* pBillingInfo = this;
	memcpy(pBuffer, (const char*)pBillingInfo, len);

	// 다시 원래대로
	Packet_Type = ntohl(Packet_Type);
	Result 		= ntohl(Result);
	User_Age 	= ntohl(User_Age);
	Game_No 	= ntohl(Game_No);
	Remain_Time = ntohl(Remain_Time);

	// 다 0 으로...
	memset(this, 0, sizeof(this));

	//---------------------------------------
	// read
	//---------------------------------------
	BillingInfo* pBillingInfo2 = this;

	memcpy((char*)pBillingInfo2, pBuffer, len);

	// order
	Packet_Type = ntohl(Packet_Type);
	Result 		= ntohl(Result);
	User_Age 	= ntohl(User_Age);
	Game_No 	= ntohl(Game_No);
	Remain_Time = ntohl(Remain_Time);

	//---------------------------------------
	// assert
	//---------------------------------------
	Assert(Packet_Type==1);
	Assert(Result==2);
	Assert(strcmp(S_KEY, "S_KEY")==0);
	Assert(strcmp(Session, "Session")==0);
	Assert(strcmp(User_CC, "UCC")==0);
	Assert(strcmp(User_No, "User_NO")==0);
	Assert(strcmp(User_ID, "User_ID")==0);
	Assert(strcmp(User_IP, "User_IP")==0);
	Assert(User_Gender=='M');
	Assert(strcmp(User_Status, "ST")==0);
	Assert(strcmp(User_PayType, "PT")==0);
	Assert(User_Age==26);
	Assert(Game_No==777);
	Assert(strcmp(Bill_PayType, "A")==0);
	Assert(strcmp(Bill_Method, "B")==0);
	Assert(strcmp(Expire_Date, "20021115120")==0);
	Assert(Remain_Time==500);


	cout << "OK" << endl;


	__END_CATCH
}

void CommonBillingPacket::setUser_CC() 
	throw (Error)
{ 
	__BEGIN_TRY

	static bool isNetMarble = (g_pConfig->getPropertyInt("IsNetMarble")==1);

	if (isNetMarble)
	{
		strcpy(User_CC, BillingUserCC2String[BILLING_USER_NETMARBLE].c_str()); 
	}
	else
	{
		strcpy(User_CC, BillingUserCC2String[BILLING_USER_METROTECH].c_str());
	}


	__END_CATCH
}

void CommonBillingPacket::read (SocketInputStream & iStream) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY

	int len = getPacketSize();
	BillingInfo* pBillingInfo = this;

	memset((char*)pBillingInfo, 0, sizeof(BillingInfo));
	iStream.read((char*)pBillingInfo, len);

	// order
	Packet_Type = ntohl(Packet_Type);
	Result 		= ntohl(Result);
	User_Age 	= ntohl(User_Age);
	Game_No 	= ntohl(Game_No);
	Remain_Time = ntohl(Remain_Time);

	/*
	int t;
	char* pBuffer = m_pBuffer;

	memcpy(&t, 			pBuffer,  4); pBuffer+= 4;	Packet_Type = ntohl(t); // Packet_Type
	memcpy(&t,			pBuffer,  4); pBuffer+= 4;	Result = ntohl(t); 		// Result
	memcpy(S_KEY, 		pBuffer, 32); pBuffer+=32;							// S_KEY
	memcpy(Session, 	pBuffer, 32); pBuffer+=32;							// Session
	memcpy(User_CC, 	pBuffer,  4); pBuffer+= 4;							// User_CC
	memcpy(User_No, 	pBuffer, 20); pBuffer+=20;							// User_No
	memcpy(User_ID, 	pBuffer, 40); pBuffer+=40;							// User_ID
	memcpy(User_IP, 	pBuffer, 24); pBuffer+=24;							// User_IP
	memcpy(&User_Gender,pBuffer,  1); pBuffer+= 1;							// User_Gender
	memcpy(User_Status, pBuffer,  3); pBuffer+= 3;							// User_Status
	memcpy(User_PayType,pBuffer,  2); pBuffer+= 2;							// User_PayType
	memcpy(&t,			pBuffer,  4); pBuffer+= 4;	User_Age = ntohl(t); 	// User_Age
	memcpy(&t,			pBuffer,  4); pBuffer+= 4;	Game_No = ntohl(t); 	// Game_No
	memcpy(Bill_PayType,pBuffer,  2); pBuffer+= 2;							// Bill_PayType
	memcpy(Bill_Method, pBuffer,  2); pBuffer+= 2;							// Bill_Method
	memcpy(Expire_Date, pBuffer, 12); pBuffer+=12;							// Expire_Date
	memcpy(&t,			pBuffer,  4); pBuffer+= 4;	Remain_Time = ntohl(t);	// Remain_Time
	*/

#ifdef __COUT_BILLING_SYSTEM__
	cout << "[read] " << toString().c_str() << endl;
#endif

	__END_CATCH
}

void CommonBillingPacket::write (SocketOutputStream & oStream) const
     throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
#ifdef __COUT_BILLING_SYSTEM__
	cout << "[write] " << toString().c_str() << endl;
#endif

	/*
	int t;
	char* pBuffer = (char*)m_pBuffer;

	t = htonl(Packet_Type); memcpy(pBuffer, &t, 		 4); pBuffer+= 4;	// Packet_Type
	t = htonl(Result); 		memcpy(pBuffer, &t, 		 4); pBuffer+= 4;	// Result
							memcpy(pBuffer, S_KEY, 		32); pBuffer+=32;	// S_KEY
							memcpy(pBuffer, Session, 	32); pBuffer+=32;	// Session
							memcpy(pBuffer, User_CC, 	 4); pBuffer+= 4;	// User_CC
							memcpy(pBuffer, User_No, 	20); pBuffer+=20;	// User_No
							memcpy(pBuffer, User_ID, 	40); pBuffer+=40;	// User_ID
							memcpy(pBuffer, User_IP, 	24); pBuffer+=24;	// User_IP
							memcpy(pBuffer, &User_Gender,1); pBuffer+= 1;	// User_Gender
							memcpy(pBuffer, User_Status, 3); pBuffer+= 3;	// User_Status
							memcpy(pBuffer, User_PayType,2); pBuffer+= 2;	// User_PayType
	t = htonl(User_Age); 	memcpy(pBuffer, &t,			 4); pBuffer+= 4;	// User_Age
	t = htonl(Game_No); 	memcpy(pBuffer, &t, 		 4); pBuffer+= 4;	// Game_No
							memcpy(pBuffer, Bill_PayType,2); pBuffer+= 2;	// Bill_PayType
							memcpy(pBuffer, Bill_Method, 2); pBuffer+= 2;	// Bill_Method
							memcpy(pBuffer, Expire_Date,12); pBuffer+=12;	// Expire_Date
	t = htonl(Remain_Time);	memcpy(pBuffer, &t, 		 4); pBuffer+= 4;	// Remain_Time
	*/
	Packet_Type = htonl(Packet_Type);
	Result 		= htonl(Result);
	User_Age 	= htonl(User_Age);
	Game_No 	= htonl(Game_No);
	Remain_Time = htonl(Remain_Time);

	int len = getPacketSize();

	const BillingInfo* pBillingInfo = this;
	oStream.write((const char*)pBillingInfo, len);

	// 다시 원래대로
	Packet_Type = ntohl(Packet_Type);
	Result 		= ntohl(Result);
	User_Age 	= ntohl(User_Age);
	Game_No 	= ntohl(Game_No);
	Remain_Time = ntohl(Remain_Time);


	__END_CATCH
}

void CommonBillingPacket::execute (Player* pPlayer) 
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY
		
	CommonBillingPacketHandler::execute(this , pPlayer);

	__END_CATCH
}

void  CommonBillingPacket::setExpire_Date(const string& PlayerID)
	throw (Error)
{
	__BEGIN_TRY
	
	// BillingInfo에도 Result가 있으니까 ::를 붙여야 한다.
	::Result* 	pResult	= NULL;
	Statement* 	pStmt 	= NULL;

	int year=0, month, day, hour, min;//, sec;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getDistConnection("PLAYER_DB")->createStatement();

		pResult = pStmt->executeQuery(
				"SELECT LastLogoutDate FROM Player WHERE PlayerID='%s'", PlayerID.c_str());

		if (pResult->next())
		{
			string pat = pResult->getString(1);

			// 0123456789012345678
			// YYYY-MM-DD HH:MM:SS
			if (pat.size()==19)
			{
				year  = atoi( pat.substr(0,4).c_str() );
				month = atoi( pat.substr(5,2).c_str() );
				day   = atoi( pat.substr(8,2).c_str() );
				hour  = atoi( pat.substr(11,2).c_str() );
				min   = atoi( pat.substr(14,2).c_str() );
				//sec   = atoi( pat.substr(16,2).c_str() );
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	// 값이 제대로 안 들어간 경우는 현재값
	if (year==0)
	{
		VSDate	currentDate(VSDate::currentDate());
		VSTime	currentTime(VSTime::currentTime());

		year 	= currentDate.year();
		month 	= currentDate.month();
		day 	= currentDate.day();
		hour 	= currentTime.hour();
		min 	= currentTime.minute();
		//sec 	= currentTime.second();
	}


	char str[20];
	sprintf(str, "%04d%02d%02d%02d%02d", year, month, day, hour, min);

	memcpy(Expire_Date, str, 12);

	__END_CATCH
}

string  CommonBillingPacket::getExpire_DateToString() const
{
	// 012345678
	// 20021120 을 "2002년 11월 20일 24시"로 바꿔준다.
	//int len = strlen(Expire_Date);
	if (Expire_Date[0]=='2')
	{
		char YYYY[5], MM[3], DD[3];
		YYYY[0] = Expire_Date[0];
		YYYY[1] = Expire_Date[1];
		YYYY[2] = Expire_Date[2];
		YYYY[3] = Expire_Date[3];
		YYYY[4] = '\0';

		MM[0] = Expire_Date[4];
		MM[1] = Expire_Date[5];
		MM[2] = '\0';

		DD[0] = Expire_Date[6];
		DD[1] = Expire_Date[7];
		DD[2] = '\0';

		char str[80];
		sprintf(str, "%s-%s-%s 23:59:59", YYYY, MM, DD);

		return str;
	}

	return "None";
}

string CommonBillingPacket::toString () const
       throw ()
{
	__BEGIN_TRY
		
	/*
	StringStream msg;
	msg << "CommonBillingPacket("
		<< "Packet_Type=" << Packet_Type
		<< ",Result=" << Result
		<< ",S_KEY=" << S_KEY
		<< ",Session=" << Session
		<< ",User_CC=" << User_CC
		<< ",User_No=" << User_No
		<< ",User_ID=" << User_ID
		<< ",User_IP=" << User_IP
		<< ",Gender=" << (int)User_Gender
		<< ",User_Status=" << User_Status
		<< ",User_PayType=" << User_PayType
		<< ",User_Age=" << User_Age
		<< ",Game_No=" << Game_No
		<< ",Bill_PayType=" << (int)Bill_PayType[0]
		<< ",Bill_Method=" << (int)Bill_Method[0]
		<< ",Expire_Date=" << Expire_Date
		<< ",Remain_Time=" << (int)Remain_Time
		<< ")";
	*/


	char str[80];
	StringStream msg;
	msg << "CommonBillingPacket("
		<< "Packet_Type=" << Packet_Type
		<< ",Result=" << Result;

	memcpy(str, S_KEY, 32); str[32]='\0';
	msg << ",S_KEY=" << str;

	memcpy(str, Session, 32); str[32]='\0';
	msg	<< ",Session=" << str;

	memcpy(str, User_CC, 4); str[4]='\0';
	msg	<< ",User_CC=" << str;

	memcpy(str, User_No, 20); str[20]='\0';
	msg	<< ",User_No=" << str;

	memcpy(str, User_ID, 40); str[40]='\0';
	msg	<< ",User_ID=" << str;

	memcpy(str, User_IP, 24); str[24]='\0';
	msg	<< ",User_IP=" << str;

	msg	<< ",Gender=" << (int)User_Gender;

	memcpy(str, User_Status, 3); str[3]='\0';
	msg	<< ",User_Status=" << str;

	memcpy(str, User_PayType, 2); str[2]='\0';
	msg	<< ",User_PayType=" << str;

	msg	<< ",User_Age=" << User_Age
		<< ",Game_No=" << Game_No;

	memcpy(str, Bill_PayType, 2); str[2]='\0';
	msg	<< ",Bill_PayType=" << str;

	memcpy(str, Bill_Method, 2); str[2]='\0';
	msg	<< ",Bill_Method=" << str;

	memcpy(str, Expire_Date, 12); str[12]='\0';
	msg	<< ",Expire_Date=" << str;

	msg	<< ",Remain_Time=" << (int)Remain_Time
		<< ")";

	return msg.toString();

	__END_CATCH
}
