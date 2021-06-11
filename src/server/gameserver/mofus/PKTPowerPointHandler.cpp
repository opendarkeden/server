/////////////////////////////////////////////////////////////////////////////
// Filename : PKTPowerPointHandler.cpp
// Desc		: 
/////////////////////////////////////////////////////////////////////////////

// include files
#include "Mofus.h"
#include "PKTPowerPointHandler.h"
#include "PKTPowerPoint.h"
#include "PKTError.h"
#include "PKTSError.h"
#include "MPlayer.h"
#include "MJob.h"
#include "Properties.h"
#include "Assert.h"

// 실행 함수
void PKTPowerPointHandler::execute( MPlayer* pPlayer, MPacket* pPacket )
{
	PKTPowerPoint* pPowerPoint = dynamic_cast<PKTPowerPoint*>(pPacket);
	Assert( pPowerPoint != NULL );

	cout << "--------------------------------------------------" << endl;
	cout << "RECV [" << pPlayer->getJob()->getName() << "] PowerPoint (name:" << pPowerPoint->sCharName
		 << ",point:" << pPowerPoint->nPowerPoint << ")" << endl;
	cout << "--------------------------------------------------" << endl;

	filelog( MOFUS_LOG_FILE, "RECV [%s] PowerPoint (name:%s,point:%d)", pPlayer->getJob()->getName().c_str(), pPowerPoint->sCharName, pPowerPoint->nPowerPoint );
	filelog( MOFUS_PACKET_FILE, "RECV : [%s] %s", pPlayer->getJob()->getName().c_str(), pPacket->toString().c_str() );

	//////////////////////////////////////////////////////////////////////
	// 받은 패킷 확인.
	//////////////////////////////////////////////////////////////////////
	static int MofusServerCode = g_pConfig->getPropertyInt( "MofusServerCode" );
	// 게임 코드 확인
	bool bCheckGameCode = ( pPowerPoint->getGameCode() == 1 );
	// 서버 코드 확인
	bool bCheckGameServerCode = ( pPowerPoint->getGameServerCode() == MofusServerCode );
	// 캐릭터 이름 확인
	bool bCheckCharacterName = ( strcasecmp( pPlayer->getJob()->getName().c_str(), pPowerPoint->getCharacterName() ) == 0 );

	if ( !bCheckGameCode || !bCheckGameServerCode || !bCheckCharacterName )
	{
		cout << "--------------------------------------------------" << endl;
		cout << "ERROR CHECK (name:" << pPlayer->getJob()->getName()
			 << ",mofusname:" << pPowerPoint->getCharacterName()
			 << ",gameservercode:" << MofusServerCode
			 << ",mofusgameservercode:" << pPowerPoint->getGameServerCode()
			 << ",gamecode:" << pPowerPoint->getGameCode()
			 << ")" << endl;
		cout << "--------------------------------------------------" << endl;

		filelog( MOFUS_LOG_FILE, "ERROR (name:%s,mofusname:%s,gameservercode:%d,mofusgameservercode:%d)",
									pPlayer->getJob()->getName().c_str(),
									pPowerPoint->getCharacterName(),
									MofusServerCode,
									pPowerPoint->getGameServerCode() );

		// 매칭 정보 확인 실패
		// 파워짱 서버로 확인 실패를 알린다.
		pPlayer->sendSError( MSERR_MATCH );

		// 사용자에게는 매칭 정보 오류로 알린다.
		pPlayer->setErrorCode( MERR_MATCHING );

		// 작업 끝
		pPlayer->setEnd();

		return;
	}
	//////////////////////////////////////////////////////////////////////

	// 파워 포인트 저장
	// 1회 전송시 적용할 최대 파워짱 포인트.
	// 만일 파워짱 서버에 60 포인트가 쌓여 있고 60 포인트를 모두 받았고
	// 1회 전송시 적용할 최대 파워짱 포인트가 20 일 경우
	// 20 만 적용하여 누적하고 나머지 40 은 버린다.
	// 결과적으로 사용자는 파워짱 서버에 있는 60 포인트는 모두 없어지고
	// 다크에덴 DB 에는 20 포인트만 누적되어 있다.
	static int MaxPowerPoint = 40;

	// 1회 전송시 적용할 최대 파워짱 포인트 적용
	int savepowerpoint = min( pPowerPoint->getPowerPoint(), MaxPowerPoint );

	// 가져온 파워 포인트를 DB에 누적하여 저장
	savePowerPoint( pPlayer->getJob()->getName(), savepowerpoint );

	// 파일 로그
	filelog( MOFUS_LOG_FILE, "SAVE PowerPoint (name:%s,savepoint:%d,recvpoint:%d)",
									pPlayer->getJob()->getName().c_str(),
									savepowerpoint,
									pPowerPoint->getPowerPoint() );

	logPowerPoint( pPlayer->getJob()->getName(), pPowerPoint->getPowerPoint(), savepowerpoint );

	// 받은 파워 포인트를 누적
	pPlayer->addPowerPoint( savepowerpoint );

	// 처리 했다는 결과를 파워짱 서버에 알린다.
	if ( pPowerPoint->isContinue() )
	{
		// 작업이 더 있다.
		pPlayer->sendReceiveOK();
	}
	else
	{
		pPlayer->sendResult();
		pPlayer->sendLogout();

		// 작업 끝이다.
		pPlayer->setEnd();
	}
}

