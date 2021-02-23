//--------------------------------------------------------------------------------
//
// Filename    : CURequestHandler.cpp
// Written By  : Reiot
//
//--------------------------------------------------------------------------------

// include files
#include "CURequest.h"

#ifdef __UPDATE_SERVER__
	#include <sys/types.h>
	#include <stdio.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/sendfile.h>

	#include "Properties.h"

	#include "UpdateServerPlayer.h"
	#include "Upackets/UCUpdate.h"
	#include "Resource.h"
#endif

//--------------------------------------------------------------------------------
//
// 클라이언트가 요청한 리소스가 존재하는지 체크한 후,
// 존재할 경우, sendfile()을 사용해서 클라이언트로 전송한다.
//
//--------------------------------------------------------------------------------
void CURequestHandler::execute ( CURequest * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
#ifdef __UPDATE_SERVER__

	UpdateServerPlayer * pUpdateServerPlayer = dynamic_cast<UpdateServerPlayer*>(pPlayer);

	Socket * pSocket = pUpdateServerPlayer->getSocket();

	const Resource & resource = pPacket->getResource();

	Version_t ClientVersion = 0;

	if( resource.getVersion() < 2000 ) {
		ClientVersion = 1;
	}

	char filename[ maxFilename + 1 ];
	sprintf( filename , "%s/%s/v%05d/%s" ,
		g_pConfig->getProperty("HomeDir").c_str() ,
		g_pConfig->getProperty("PatchDir").c_str() ,
//		resource.getVersion() , 
		ClientVersion, 
		resource.getFilename().c_str() 
	);

	//cout << "Try to open " << filename << "..." << endl;

	ifstream ifile( filename , ios::in | ios::binary | ios::nocreate );
		
	if ( !ifile ) {
		// 존재하지 않는 파일을 요청한 것은 해킹으로 간주한다.
		// 로그를 한 후, BAN 시켜야 한다.
		throw InvalidProtocolException(filename);
	}

	// 파일 크기를 알아내기 위해서 파일 포인터를 맨 뒤로 움직인다.
	ifile.seekg( 0 , ios::end );
	FileSize_t filesize = ifile.tellg();

	//cout << "Original FileSize  : " << filesize << endl;
	//cout << "Requested FileSize : " << resource.getFileSize() << endl;

	// 클라이언트에서 요청한 파일의 크기와 다를 경우, 해킹 시도로 간주한다.
	if ( resource.getFileSize() != filesize ) {
		throw InvalidProtocolException("invalid filesize");
	}

	//--------------------------------------------------------------------------------
	// CURequest 에 담겨온 리소스를 다시 UCUpdate 에 담아서 먼저 전송한다.
	// 그다음 파일 내용을 전송한다.
	//--------------------------------------------------------------------------------
	UCUpdate ucUpdate;
	ucUpdate.setResource( resource );	

	pUpdateServerPlayer->sendPacket( &ucUpdate );

	//--------------------------------------------------------------------------------
	// write file content
	//--------------------------------------------------------------------------------
	// 파일 포인터를 다시 맨 처음으로 되돌린다.
	ifile.seekg(0);
	long offset = 0;

	//cout << "=======================================================================" << endl;
	//cout << resource.getFilename() << " (" << filesize << "bytes) : ";

	// 파일 내용을 전송한다.
	DWORD nSent = sendfile( pSocket->getSOCKET() , ifile.rdbuf()->fd() , &offset, filesize );

	//cout << nSent << " bytes sent to client." << endl;
	//cout << "=======================================================================" << endl;

	if ( nSent != filesize ) {
		throw Error("파일 전송 오류");
	}

	// 파일을 닫는다.
	ifile.close();

	pUpdateServerPlayer->setPlayerStatus( USPS_AFTER_SENDING_UC_UPDATE );

#endif
		
	__END_CATCH
}
