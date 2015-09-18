/////////////////////////////////////////////////////////////////////
// Filename        : NetmarbleGuildRegisterThread.h
// Written by    : bezz@darkeden.com
// Description    :
/////////////////////////////////////////////////////////////////////

#ifndef __NETMARBLE_GUILD_REGISTER_THREAD_H__
#define __NETMARBLE_GUILD_REGISTER_THREAD_H__

#include "Thread.h"
#include "Types.h"
#include "Exception.h"
#include "Mutex.h"

#include <queue>

class NetmarbleGuildRegisterThread: public Thread {
public:
    typedef queue<GuildID_t> QueueGuildID;

    NetmarbleGuildRegisterThread() throw(Error);
    ~NetmarbleGuildRegisterThread() throw(Error) {};

    void init() throw(Error) {};
    void run() throw(Error);

    void pushGuildID(GuildID_t guildID);

    void registerGuild();

private:
    // Guild ID list for register
    QueueGuildID    m_GuildIDs;

    mutable Mutex m_Mutex;
};

extern NetmarbleGuildRegisterThread* g_pNetmarbleGuildRegisterThread;
#endif
