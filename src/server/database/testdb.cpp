#include <iostream>
#include "Types.h"
#include "Exception.h"
#include "Connection.h"
#include "Statement.h"
#include "Result.h"
#include "LogManager.h"
#include "Properties.h"

int main()
{
	try {

		g_pConfig = new Properties();
		g_pConfig->load("/home/crazydog/Works/VampireSlayers/conf/gameserver.conf");	

		g_pLogManager = new LogManager();
		g_pLogManager->start();

		Connection * pConn = new Connection( "localhost" , "PLAYER", "choon", "choon" , 7777 );
		
		Statement * pStmt = pConn->createStatement();
		
		Result * pResult = pStmt->executeQuery("SELECT PID, ID, Name, Passwd FROM Player");
		cout << "SELECT PID, ID, Name, Passwd FROM Player" << endl;
		
		while( pResult->next() ) {
			cout << "Player(PID:" << pResult->getInt(1) << " ID:" << pResult->getString(2) 
				<< ",Name:" << pResult->getString(3) << ",Password:" << pResult->getString(4) << ")" << endl;
		}

		// Statement 에서 이전 Result 는 자동으로 삭제한다.
		// 괜히 외부에서 지우게 되면 골치아프다. - -;
		pResult = pStmt->executeQuery("SELECT ID, Name, Passwd FROM Player WHERE id = 11");
		cout << "SELECT ID, Name, Passwd FROM Player WHERE id = 11" << endl;
		
		// SELECT 결과 조건을 만족하는 것이 아무것도 없다면, RowCount 가 0 이다.
		cout << "#Rows : " << pResult->getRowCount() << endl;
		cout << "#Cols : " << pResult->getFieldCount() << endl;

		while( pResult->next() ) {
			cout << "Player(PID:" << pResult->getInt(1) << " ID:" << pResult->getString(2) 
				<< ",Name:" << pResult->getString(3) << ",Password:" << pResult->getString(4) << ")" << endl;
		}

		delete pStmt;
		delete pConn;
	
	} catch ( Throwable & t ) {
		cout << t.toString() << endl;
    }
}
