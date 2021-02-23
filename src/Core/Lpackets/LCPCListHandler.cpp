//----------------------------------------------------------------------
//
// Filename    : LCPCListHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCPCList.h"

#ifdef __GAME_CLIENT__
	#include "ClientPlayer.h"
	#include "Cpackets/CLCreatePC.h"
	#include "Cpackets/CLDeletePC.h"
	#include "Cpackets/CLSelectPC.h"
	#include "Cpackets/CLSelectBoard.h"

#endif

//----------------------------------------------------------------------
// 서버로부터 캐릭터 리스트를 받았다. 
// 이제 캐릭터 관리 인터페이스의 적절한 곳에 전송받은 값을 집어 넣어서
// 출력하자.
//----------------------------------------------------------------------
void LCPCListHandler::execute ( LCPCList * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	#if __LINUX__ || __WIN_CONSOLE__

		ClientPlayer * pClientPlayer = (ClientPlayer*)pPlayer;

		cout << endl
			 << "+----------------------+" << endl
			 << "| CHARACTER MANAGEMENT |" << endl
			 << "+----------------------+" << endl
			 << endl;
	
		uint nPCs = 0;
	
		for ( uint i = 0 ; i < SLOT_MAX ; i ++ ) {
	
			try {
	
				PCInfo * pPCInfo = pPacket->getPCInfo( Slot(i) );
				nPCs ++;
	
				switch ( pPCInfo->getPCType() ) {
	
					case PC_SLAYER :
						{
							PCSlayerInfo * pPCSlayerInfo = dynamic_cast<PCSlayerInfo*>(pPCInfo);							
							cout << pPCSlayerInfo->toString() << endl;
						}
						break;
	
					case PC_VAMPIRE :
						{
							PCVampireInfo * pPCVampireInfo = dynamic_cast<PCVampireInfo*>(pPCInfo);		
							cout << pPCVampireInfo->toString() << endl;
						}
						break;

					case PC_OUSTERS :
						{
							PCOustersInfo * pPCOustersInfo = dynamic_cast<PCOustersInfo*>(pPCInfo);		
							cout << pPCOustersInfo->toString() << endl;
						}
						break;
	
					default :	
						throw InvalidProtocolException("invalid pc type");
				}
	
			} catch ( NoSuchElementException ) {
			}

		}

		if ( nPCs == 0 ) {
			cout << "캐릭터가 하나도 없습니다." << endl;
		}

		char cmd[80+1];

		do {

			cout << endl
				 << "+--------------+" << endl
			  	 << "| 1. Create PC |" << endl
			  	 << "| 2. Delete PC |" << endl
			 	 << "| 3. Select PC |" << endl
			 	 << "| 4. To Board  |" << endl
			 	 << "+--------------|" << endl
			 	 << "select > ";

			cin.getline(cmd,80);

		} while ( strcmp(cmd,"1") != 0 && strcmp(cmd,"2") != 0 && strcmp(cmd,"3") != 0  && strcmp(cmd, "4") !=0);

		if ( strcmp(cmd,"1") == 0 ) {

			cout << endl
				 << "+--------------------+" << endl
				 << "| CHARACTER CREATION |" << endl
				 << "+--------------------+" << endl
				 << endl;

			CLCreatePC clCreatePC;

			cout << "Name : ";
			cin.getline(cmd,80);
			clCreatePC.setName(cmd);

			cout << "Slot (1-3) : ";
			cin.getline(cmd,80);
			Slot slot;
			if ( strcmp(cmd,"1") == 0 ) slot = SLOT1;
			else if ( strcmp(cmd,"2") == 0 ) slot = SLOT2;
			else if ( strcmp(cmd,"3") == 0 ) slot = SLOT3;
			else slot = SLOT1;
			clCreatePC.setSlot(slot);

			cout << "Sex (남/여) : ";
			cin.getline(cmd,80);
			Sex sex = ( strcmp(cmd,"남") == 0 ) ? sex = MALE : sex = FEMALE;
			clCreatePC.setSex(sex);
			cout << "Sex : " << Sex2String[sex] << endl;

			cout << "HairStyle (1-3) : ";
			cin.getline(cmd,80);
			HairStyle hairStyle;
			if ( strcmp(cmd,"1") == 0 ) hairStyle = HAIR_STYLE1;
			else if ( strcmp(cmd,"2") == 0 ) hairStyle = HAIR_STYLE2;
			else if ( strcmp(cmd,"3") == 0 ) hairStyle = HAIR_STYLE3;
			else hairStyle = HAIR_STYLE1;
			clCreatePC.setHairStyle(hairStyle);
			
			cout << "HairColor (0-255) : ";
			cin.getline(cmd,80);
			clCreatePC.setHairColor( atoi( cmd ) );
			
			cout << "SkinColor (0-255) : ";
			cin.getline(cmd,80);			
			clCreatePC.setSkinColor( atoi( cmd ) );

			cout << "ShirtColor (0-255) : ";
			cin.getline(cmd,80);
			clCreatePC.setSkinColor( atoi( cmd ) );

			cout << "JeansColor (0-255) : ";
			cin.getline(cmd,80);
			clCreatePC.setSkinColor( atoi( cmd ) );

			cout << "Try to creating PC : " << clCreatePC.toString() << endl;

			pClientPlayer->sendPacket( &clCreatePC );
			pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_CREATE_PC );

		} else if ( strcmp(cmd,"2") == 0 ) {

			cout << endl
				 << "+------------------+" << endl
				 << "| DELETE CHARACTER |" << endl
				 << "+------------------+" << endl
				 << endl;

			CLDeletePC clDeletePC;

			cout << "Name : ";
			cin.getline(cmd,80);
			clDeletePC.setName(cmd);

			cout << "Slot (1-3) : ";
			cin.getline(cmd,80);
			Slot slot;
			if ( strcmp(cmd,"1") == 0 ) slot = SLOT1;
			else if ( strcmp(cmd,"2") == 0 ) slot = SLOT2;
			else if ( strcmp(cmd,"3") == 0 ) slot = SLOT3;
			else slot = SLOT1;
			clDeletePC.setSlot(slot);

			pClientPlayer->sendPacket( &clDeletePC );
			pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_DELETE_PC );

		} else if ( strcmp(cmd,"3") == 0 ) {

			cout << endl
				 << "+------------------+" << endl
				 << "| SELECT CHARACTER |" << endl
				 << "+------------------+" << endl
				 << endl;

			CLSelectPC clSelectPC;

			cout << "Name : ";
			cin.getline(cmd,80);
			clSelectPC.setPCName(cmd);

			cout << "PCType (S/V) : ";
			cin.getline(cmd,80);
			if ( strcmp(cmd,"S") == 0 || strcmp(cmd,"s") == 0 ) 
				clSelectPC.setPCType(PC_SLAYER);
			else if ( strcmp(cmd,"V") == 0 || strcmp(cmd,"v") == 0 ) 
				clSelectPC.setPCType(PC_VAMPIRE);
			else
				clSelectPC.setPCType(PC_SLAYER);

			// CGConnect 때 사용하려면 여기서 저장해둬야 한다.
			pClientPlayer->setPCType(clSelectPC.getPCType());
			pClientPlayer->setPCName(clSelectPC.getPCName());

			cout << endl << clSelectPC.toString() << endl;
		
			pClientPlayer->sendPacket( &clSelectPC );
			pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_SELECT_PC );
			
		} else if ( strcmp(cmd, "4") == 0 ) {

			cout<< endl;
			cout<<"Choose BBS"				<<endl
				 << "+------------------+" << endl
				 << "|  1. Beta BBS     |" << endl
				 << "|  2. Quit         |" << endl
				 << "|                  |" << endl
				 << "+------------------+" << endl
			 	 << "select > ";

		// 여기에 게시판 관련 처리 부분이 들어가면 된다..
		// CLSelectBBS 패킷을 만들어서 보내면 되겠군...

			cin.getline(cmd,80);
			
			if (strcmp(cmd, "1") == 0 ) {
					
				CLSelectBoard clSelectBoard;

				clSelectBoard.setBoardName("BetaBBS");
				
				cout << clSelectBoard.toString() << endl;

				pClientPlayer->sendPacket( &clSelectBoard );

				pClientPlayer->setPlayerStatus( CPS_AFTER_SENDING_CL_SELECT_BOARD );
				
			}

		}

	#endif

#endif
		
	__END_DEBUG_EX __END_CATCH
}
