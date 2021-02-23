//--------------------------------------------------------------------------------
//
// Filename    : LCRegisterPlayerErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "LCRegisterPlayerError.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLRegisterPlayer.h"
#endif

//--------------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------------
void LCRegisterPlayerErrorHandler::execute ( LCRegisterPlayerError * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	cout << endl
		<< "+-------------------------+" << endl
		<< "| FAIL TO REGISTER PLAYER |" << endl
		<< "+-------------------------+" << endl
		<< endl
		<< pPacket->getMessage() << endl;

	cout << endl
		<< "+-----------------+" << endl
		<< "| REGISTER PLAYER |" << endl
		<< "+-----------------+" << endl
		<< endl;

	CLRegisterPlayer clRegisterPlayer;
	char cmd[80];

	cout << "아이디 : ";
	cin.getline(cmd,80);
	clRegisterPlayer.setID(cmd);

	cout << "패스워드 : ";
	cin.getline(cmd,80);
	clRegisterPlayer.setPassword(cmd);

	cout << "이름 : ";
	cin.getline(cmd,80);
	clRegisterPlayer.setName(cmd);

	cout << "성별 (남/여) : ";
	cin.getline(cmd,80);
	Sex sex;
	if ( strcmp(cmd,"남") == 0 ) sex = MALE;
	if ( strcmp(cmd,"여") == 0 ) sex = FEMALE;
	else sex = MALE;
	cout << "Sex : " << Sex2String[sex] << endl;
	clRegisterPlayer.setSex(sex);

	clRegisterPlayer.setSSN("800101-2000111");
	clRegisterPlayer.setTelephone("02-222-3333");
	clRegisterPlayer.setCellular("011-222-3333");
	clRegisterPlayer.setZipCode("700-441");
	clRegisterPlayer.setAddress("서울특별시 영등포구 여의도동 사서함 300번지");
	clRegisterPlayer.setNation( KOREA );
	clRegisterPlayer.setEmail("jhkim@mbc.com");
	clRegisterPlayer.setHomepage("www.jhkim.com");
	clRegisterPlayer.setProfile("테크노의 여왕 전지현");
	clRegisterPlayer.setPublic(false);

	cout << clRegisterPlayer.toString() << endl;

	// 등록 패킷을 전송한다.
	pClientPlayer->sendPacket( &clRegisterPlayer );

	// 플레이어의 상태를 바꾼다.
	pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_REGISTER_PLAYER );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
