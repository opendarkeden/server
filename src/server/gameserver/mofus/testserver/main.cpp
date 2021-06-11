#include <iostream.h>
#include "GameServerManager.h"
#include "MPacketManager.h"
#include "Properties.h"
#include "StringParser.h"
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>


int main( int argc, char* argv[] )
{
	if ( argc < 3 )
	{
		cout << "mofusserver -f conf" << endl;
		return 1;
	}

	struct rlimit rl;
	rl.rlim_cur = RLIM_INFINITY;
	rl.rlim_max = RLIM_INFINITY;
	setrlimit(RLIMIT_CORE,&rl);

	string* Argv = new string[argc];
	for ( int i = 0; i < argc; ++i )
	{
		Argv[i] = argv[i];
	}

	try
	{
		g_pConfig = new Properties();
		g_pConfig->load(Argv[2]);
	}
	catch ( Error& e )
	{
		return 1;
	}

	g_pMPacketManager = new MPacketManager();
	g_pMPacketManager->init();

	g_pGameServerManager = new GameServerManager();
	g_pGameServerManager->init();
	g_pGameServerManager->start();

	while ( 1 )
	{
		usleep( 1000000 );
	}
}

