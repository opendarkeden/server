//--------------------------------------------------------------------------------
//
// Filename    : LCQueryResultPlayerIDHandler.cpp
// Written By  : Reiot
// Description : 
//
//--------------------------------------------------------------------------------

// include files
#include "LCQueryResultPlayerID.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLQueryPlayerID.h"
	#include "Cpackets/CLRegisterPlayer.h"
#endif

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void LCQueryResultPlayerIDHandler::execute ( LCQueryResultPlayerID * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_CLIENT__

	ClientPlayer * pClientPlayer = dynamic_cast<ClientPlayer*>(pPlayer);

	#if __LINUX__

		if ( pPacket->isExist() )
			cout << pPacket->getPlayerID() << " is exist" << endl;
		else
			cout << pPacket->getPlayerID() << " is not exist" << endl;

		string cmd;

		do {

			cout << endl
				 << "+------------------------+" << endl
				 << "| 1. query player id     |" << endl
				 << "| 2. register new player |" << endl
				 << "+------------------------+" << endl
				 << endl
				 << "select > ";

	        getline(cin,cmd);

		} while ( cmd != "1" && cmd != "2" );

        if ( cmd == "1" ) {

            //----------------------------------------------------------------------
            // 특정 아이디가 이미 존재하는지 쿼리한다.
            //----------------------------------------------------------------------
            cout << "+----------+" << endl
				 << "| QUERY ID |" << endl
				 << "+----------+" << endl
				 << endl
				 << "Query> ";

            string id;
            getline(cin,id);

            CLQueryPlayerID clQueryPlayerID;
            clQueryPlayerID.setPlayerID(id);

            pClientPlayer->sendPacket( &clQueryPlayerID );

            // 플레이어의 상태를 바꾼다.
            pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_QUERY_PLAYER_ID );

        } else {

            //----------------------------------------------------------------------
            // 새 사용자 등록 입력을 받는다.
            //----------------------------------------------------------------------
            CLRegisterPlayer clRegisterPlayer;

            cout << "+---------------------+" << endl
				 << "| REGISTER NEW PLAYER |" << endl
				 << "+---------------------+" << endl
				 << endl;

            cout << "아이디 : ";
            string id;
            getline(cin,id);
            clRegisterPlayer.setID(id);

            cout << "패스워드 : ";
            string password;
            getline(cin,password);
            clRegisterPlayer.setPassword(password);

            cout << "이름 : ";
            string name;
			getline(cin,name);
            clRegisterPlayer.setName(name);

            cout << "성별 (남/여) : ";
            string _sex;
            getline(cin,_sex);
            Sex sex = ( _sex == "남" ) ? MALE : FEMALE;
            clRegisterPlayer.setSex(sex);

			cout << "주민등록번호 : ";
			string ssn;
			getline(cin,ssn);
            clRegisterPlayer.setSSN(ssn);

            clRegisterPlayer.setTelephone("02-222-3333");
            clRegisterPlayer.setCellular("011-222-3333");
            clRegisterPlayer.setZipCode("700-441");
            clRegisterPlayer.setAddress("서울특별시 영등포구 여의도동 사서함 300번지");
            clRegisterPlayer.setNation( KOREA );
            clRegisterPlayer.setEmail("jhkim@mbc.com");
            clRegisterPlayer.setHomepage("www.jhkim.com");
            clRegisterPlayer.setProfile("테크노의 여왕 전지현");
            clRegisterPlayer.setPublic(false);

            //cout << clRegisterPlayer.toString() << endl;

            // 등록 패킷을 전송한다.
            pClientPlayer->sendPacket( &clRegisterPlayer );

            // 플레이어의 상태를 바꾼다.
            pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_REGISTER_PLAYER );

        }

	#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}
