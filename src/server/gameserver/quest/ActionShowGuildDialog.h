//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowGuildDialog.h
// Written By  : 
// Description :
// Creature가 주어진 대사를 말한다. 이 대사는 크리처의 머리 위의 말풍선으로
// 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_GUILD_DIALOG_H__
#define __ACTION_SHOW_GUILD_DIALOG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

typedef BYTE GuildDialog_t;
const int szGuildDialog = sizeof(GuildDialog_t);


//////////////////////////////////////////////////////////////////////////////
// class ActionShowGuildDialog;
//////////////////////////////////////////////////////////////////////////////

class ActionShowGuildDialog : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_SHOW_GUILD_DIALOG; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

	enum GUILDDIALOG
	{
		GUILD_DIALOG_REGIST = 0,		// 길드 등록 창
		GUILD_DIALOG_WAIT_LIST,			// 길드 등록 대기 리스트
		GUILD_DIALOG_LIST,				// 길드 리스트
		GUILD_DIALOG_QUIT,				// 길드 탈퇴 창

		GUILD_DIALOG_MAX
	};

private:
	GuildDialog_t m_Type;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionShowGuildDialogFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowGuildDialogFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_SHOW_GUILD_DIALOG; }
	virtual string getActionName() const  { return "ShowGuildDialog"; }
    virtual Action* createAction() const  { return new ActionShowGuildDialog(); }
};

#endif
