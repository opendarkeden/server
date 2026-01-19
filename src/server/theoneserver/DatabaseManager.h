//////////////////////////////////////////////////////////////////////////////
// Filename    : DatabaseManager.h
// Written By  : elca
// Description : ����Ÿ���̽� �Ŵ���
//////////////////////////////////////////////////////////////////////////////

#ifndef __DATABASE_MANAGER_H__
#define __DATABASE_MANAGER_H__

#include "Connection.h"
#include "Exception.h"
#include "HashMap.h"
#include "Mutex.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class DatabaseManager;
//////////////////////////////////////////////////////////////////////////////

class DatabaseManager {
public:
    DatabaseManager() throw();
    ~DatabaseManager() throw();

public:
    void init() throw(Error);
    void addConnection(int TID, Connection* pConnection) throw(DuplicatedException);

    Connection* getConnection() throw(NoSuchElementException);
    Connection* getConnection(const string& ip) throw(NoSuchElementException);
    void executeDummyQuery(Connection* pConnection) throw(Error);

private:
    // �� �����庰�� �����ϴ� DB ����
    hash_map<int, Connection*> m_Connections;

    // ���� ó�� �����Ǵ� �⺻ DB ����
    Connection* m_pDefaultConnection;

    mutable Mutex m_Mutex;
};

extern DatabaseManager* g_pDatabaseManager;

#endif
