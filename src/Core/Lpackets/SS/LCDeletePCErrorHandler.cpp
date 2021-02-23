//----------------------------------------------------------------------
//
// Filename    : LCDeletePCErrorHandler.cpp
// Written By  : Reiot
// Description : 
//
//----------------------------------------------------------------------

// include files
#include "LCDeletePCError.h"

//----------------------------------------------------------------------
// 캐릭터의 삭제가 실패했다는 뜻이다.
// 가만히 생각해보니, 삭제 실패는 크래킹 시도가 아닌가?? - -;
//----------------------------------------------------------------------
void LCDeletePCErrorHandler::execute ( LCDeletePCError * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_CLIENT__

	cout << "Fail to deletePC... (" << pPacket->toString() << ")" << endl;
	throw ProtocolException("DeletePC Failed!");

#endif
		
	__END_DEBUG_EX __END_CATCH
}
