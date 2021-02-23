//--------------------------------------------------------------------------------
//
// Filename   : Update.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __UPDATE_H__
#define __UPDATE_H__

// include files
#include "Types.h"
#include "UpdateDef.h"
#include "Exception.h"
#include "Assert.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"

// forward declaration
class Socket;


//--------------------------------------------------------------------------------
// update types
//--------------------------------------------------------------------------------
enum UPDATETYPE {
	UPDATETYPE_CREATE_DIRECTORY ,
	UPDATETYPE_DELETE_DIRECTORY ,
	UPDATETYPE_RENAME_DIRECTORY ,
	UPDATETYPE_CREATE_FILE,
	UPDATETYPE_DELETE_FILE,
	UPDATETYPE_RENAME_FILE,
	UPDATETYPE_APPEND_SPRITE_PACK ,
	UPDATETYPE_DELETE_SPRITE_PACK ,
	UPDATETYPE_UPDATE_SPRITE_PACK ,
	UPDATETYPE_APPEND_FRAME_PACK ,
	UPDATETYPE_APPEND_INFO,
	UPDATETYPE_VERIFY,
	UPDATETYPE_MAX	
};


const string UPDATETYPE2String[] = {
	"UPDATETYPE_CREATE_DIRECTORY" ,
	"UPDATETYPE_DELETE_DIRECTORY" ,
	"UPDATETYPE_RENAME_DIRECTORY" ,
	"UPDATETYPE_CREATE_FILE",
	"UPDATETYPE_DELETE_FILE",
	"UPDATETYPE_RENAME_FILE",
	"UPDATETYPE_APPEND_SPRITE_PACK" ,
	"UPDATETYPE_DELETE_SPRITE_PACK" ,
	"UPDATETYPE_UPDATE_SPRITE_PACK" ,
	"UPDATETYPE_APPEND_FRAME_PACK" ,
	"UPDATETYPE_APPEND_INFO" ,
	"UPDATETYPE_VERIFY"
};


//--------------------------------------------------------------------------------
//
// class Update;
//
// 특정 버전의 Smart Update 명령 하나와 대응되는 클래스이다.
// 
//--------------------------------------------------------------------------------
class Update {

public :

	// load from file
	void load (ifstream & ifile) throw (IOException, Error);

	// save to file
	void save (ofstream & ofile) const throw (IOException, Error);

	// read from socket input stream
	void read (SocketInputStream & iStream) throw (ProtocolException, Error);

	// read from socket directly
	void read (Socket* pSocket) throw (IOException, Error);

	// write to socket output stream
	void write (SocketOutputStream & oStream) const throw (ProtocolException, Error);

	// write to socket directly
	void write (Socket* pSocket) const throw (IOException, Error);

	// get size
	uint getSize () const throw ();

	// get max size
	static uint getMaxSize () throw ();

	// execute update
	void execute () throw (Error);


public :

	// get/set update type
	Version_t getVersion () const throw () { return m_Version; }
	void setVersion (Version_t version) throw () { m_Version = version; }

	// get update type
	UPDATETYPE getUpdateType () const 
		throw (Error) 
	{ 
		Assert(m_UpdateType < UPDATETYPE_MAX); 
		return m_UpdateType; 
	}

	// set update type
	void setUpdateType (UPDATETYPE updateType) 
		throw (Error) 
	{ 
		Assert(updateType < UPDATETYPE_MAX); 
		m_UpdateType = updateType; 
	}

	// get parameter
	string getParam (uint i) const 
		throw (Error) 
	{ 
		Assert(i < maxParams); 
		return m_Params[i]; 
	}

	// set parameter
	void setParam (uint i, const string & param) 
		throw (Error) 
	{ 
		Assert(i < maxParams); 
		Assert(param.size() < maxParameterLen);
		m_Params[i] = param; 
	}

	// get debug string
	string toString () const throw ();


private :

	// Client Version
	Version_t m_Version;

	// update type
	UPDATETYPE m_UpdateType;

	// parameters
	string m_Params[maxParams];

};

#endif
