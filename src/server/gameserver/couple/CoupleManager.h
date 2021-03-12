#ifndef __COUPLE_MANAGER_H__
#define __COUPLE_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Assert.h"

class PlayerCreature;

// const 안하면 우예 되는거지?
const string Sex2FieldName[] =
{
	"FemalePartnerName",
	"MalePartnerName",
};

class CoupleManager
{
public:
	CoupleManager() { }

public:
	bool 	isCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 ) ;
	bool	hasCouple( PlayerCreature* pPC ) ;
	bool	getPartnerName( PlayerCreature* pPC, string& partnerName ) ;
	bool 	isCouple( PlayerCreature* pPC1, string name2 ) ;

public:
	static string	getFieldName( Sex sex ) { return Sex2FieldName[(int)sex]; }
	static string	getCounterFieldName( Sex sex ) { return Sex2FieldName[ 1 - (int)sex ]; }

public:
	void	makeCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 ) ;
	void	removeCouple( PlayerCreature* pPC1, PlayerCreature* pPC2 ) ;
	void	removeCoupleForce( PlayerCreature* pPC1, string strPC2 ) ;
	void	removeCoupleForce( PlayerCreature* pPC1 ) ;

};

extern CoupleManager* g_pCoupleManager;

#endif // __COUPLE_MANAGER_H__

