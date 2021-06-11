//--------------------------------------------------------------------------------
//
// Filename   : DB.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __DB_H__
#define __DB_H__

#include "DatabaseManager.h"
#include "Connection.h"
#include "Statement.h"
#include "Result.h"

#define BEGIN_DB try 
#define BEGIN_DB_EX try 

#define END_DB(STMT)         catch(SQLQueryException& sqe) { delete STMT; string msg; msg += string(__PRETTY_FUNCTION__); msg += " : "; msg += string(sqe.toString()); filelog("DBError.log", "%s", msg.c_str()); throw(msg.c_str()); } 
#define END_DB_EX(STMT, MSG) catch(SQLQueryException& sqe) { delete STMT; string msg; msg += string(__PRETTY_FUNCTION__); msg += string(" : "); msg += string(sqe.toString()); msg += string(" : "); msg += string(MSG); filelog("DBError.log", "%s", msg.c_str()); throw(msg.c_str()); } 

#define NEW_STMT g_pDatabaseManager->getConnection("DARKEDEN")->createStatement()

#endif
