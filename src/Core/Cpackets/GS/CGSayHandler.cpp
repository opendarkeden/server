//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSayHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSay.h"

#ifdef __GAME_SERVER__
	#include <stdio.h>

	#include "GamePlayer.h"
    #include "ZoneGroupManager.h"
    #include "ZoneInfoManager.h"
    #include "ZonePlayerManager.h"
	#include "DB.h"
    #include "InfoClassManager.h"
    #include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "Monster.h"
	#include "IncomingPlayerManager.h"
	#include "Zone.h"
	#include "ZoneUtil.h"
	#include "EffectShutDown.h"
	#include "NPC.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "PCFinder.h"
	#include "NPCInfo.h"
	#include "VSDateTime.h"
	#include "Guild.h"
	#include "Relic.h"
	#include "RelicUtil.h"
	#include "CombatInfoManager.h"
	#include "ClientManager.h"
	#include "OptionInfo.h"
	#include "ItemUtil.h"
	#include "MonsterManager.h"
	#include "PCManager.h"
	#include <list>
	#include "StringPool.h"
	#include "GoodsInventory.h"
	#include "NicknameBook.h"

	#include "PacketUtil.h"

	#include "skill/Sniping.h"

	#include "Gpackets/GCUpdateInfo.h"
    #include "Gpackets/GCSystemMessage.h"
    #include "Gpackets/GCDeleteObject.h"
    #include "Gpackets/GCAddVampire.h"
    #include "Gpackets/GCAddSlayer.h"
    #include "Gpackets/GCAddOusters.h"
	#include "Gpackets/GCSay.h"
	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCAddEffect.h"
	#include "Gpackets/GCAddEffectToTile.h"
	#include "Gpackets/GCRemoveEffect.h"
	#include "Gpackets/GCModifyNickname.h"

	#include "Mine.h"
	#include "Properties.h"
	#include "VariableManager.h"

	#include "Properties.h"
	#include "GameServerInfoManager.h"
	#include "LoginServerManager.h"
	#include "Gpackets/GGCommand.h"
	#include "ZoneInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "UniqueItemManager.h"
	#include "MasterLairManager.h"
	#include "EffectGhost.h"
	#include "EventManager.h"
	#include "EventReloadInfo.h"
	#include "CreatureUtil.h"
	#include "ShrineInfoManager.h"
	#include "CastleInfoManager.h"
	#include "war/WarSystem.h"
	#include "EffectLoud.h"
	#include "EffectMute.h"
	#include "LevelWarManager.h"

	#include "LogNameManager.h"
	#include "war/RaceWarLimiter.h"
	#include "war/WarScheduler.h"

	#include "PKZoneInfoManager.h"
	#include "PCManager.h"

	#include "SharedServerManager.h"
	#include "GuildManager.h"
	#include "GameServerGroupInfoManager.h"

	#include "BillingPlayerManager.h"

	#include "mission/QuestManager.h"
	#include "mission/MonsterKillQuestStatus.h"

	#include "Gpackets/GSRequestGuildInfo.h"
	#include "Gpackets/GCActiveGuildList.h"
	#include "Gpackets/GCNoticeEvent.h"
	#include "Gpackets/GSModifyGuildMember.h"
	#include "Gpackets/GCStatusCurrentHP.h"
	#include "Gpackets/GCNotifyWin.h"
	#include "Gpackets/GCMiniGameScores.h"
	#include "Gpackets/GCPetStashList.h"

	#include "Cpackets/CGModifyGuildIntro.h"
	#include "Cpackets/CGModifyGuildMemberIntro.h"
	#include "Cpackets/CGSkillToNamed.h"

	#include "item/SlayerPortalItem.h"
	#include "item/OustersSummonItem.h"
	#include "item/PetItem.h"

	#include "ctf/FlagManager.h"
	
	#include "EventZoneInfo.h"
	#include "EffectCastingTrap.h"
	#include "GDRLairManager.h"
	#include "SiegeManager.h"

	#include "gameguard/CSAuth.h"

	#include "GuildUnion.h"
	#include "DynamicZoneManager.h"
	#include "DynamicZoneGroup.h"
	#include "DynamicZone.h"
	#include "GQuestManager.h"
	#include "EffectDeleteItem.h"
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::execute (CGSay* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try {

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

	// ¼­¹ö¿¡¼­ Å¬¶óÀÌ¾ðÆ®·Î Àü¼ÛÇÏ¹Ç·Î GC- ÆÐÅ¶À» »ç¿ëÇØ¾ß ÇÑ´Ù.
	GCSay gcSay;
	
	Creature* pCreature = pGamePlayer->getCreature();

	// Å©¸®Ã³ ÀÌ¸§°ú ¸Þ½ÃÁö¸¦ ÆÐÅ¶¿¡ ´ëÀÔÇÑ´Ù.
	gcSay.setObjectID(pCreature->getObjectID());	
	gcSay.setColor( pPacket->getColor() );

	string msg = pPacket->getMessage();

	gcSay.setMessage(msg);

	bool Success = true;

	uint i = msg.find_first_of('*' , 0);

	if ( i == 0 ) 
	{
		Success = false;

		// ±æµå¿ë ÀÓ½Ã ¸í·Éµé
		if ( msg.substr(i+1, 4) == "zone" && pCreature->isGOD() )
		{
			opzone( msg, i );
		}
		else if ( msg.substr(i+1, 5) == "guild" && pCreature->isGOD() )
		{
			opguild( msg, i, pCreature );
		}
		/////////////////////
		// world¸í·É¾î´Â µµ¿ì¹Ì ÄÉ¸¯ÅÍµµ ¾µ ¼ö ÀÖ´Ù.
		if (msg.substr(i+1 , 5) == "world" && pCreature->isGOD() )
		{
			// ÇöÀç ¼­¹ö	
			uint j = msg.find_first_of(' ' , i+1);
			string command = msg.substr(j+1, msg.size()-j-1).c_str();
			uint k = command.find_first_of('*', 0);
			opExecute(pCreature, pGamePlayer, command, k);

			// ´Ù¸¥ server¿¡µµ º¸³½´Ù. bSameWorldOnly==true
			opworld(pGamePlayer, msg, i, true);
		}
		else if (msg.substr(i+1 , 8) == "allworld" && pCreature->isGOD()) {
			// ÇöÀç ¼­¹ö	
			uint j = msg.find_first_of(' ' , i+1);
			string command = msg.substr(j+1, msg.size()-j-1).c_str();
			uint k = command.find_first_of('*', 0);
			opExecute(pCreature, pGamePlayer, command, k);

			// ´Ù¸¥ server¿¡µµ º¸³½´Ù. bSameWorldOnly==false
			opworld(pGamePlayer, msg, i, false);
		}
		else
		{
			opExecute(pCreature, pGamePlayer, msg, i);
		}

	}

	// Ã¤ÆÃ ·Î±×¸¦ ³²±ä´Ù. by sigi. 2002.10.30
	if (LogNameManager::getInstance().isExist( pCreature->getName() ))
	{
		filelog("chatLog.txt", "[Say] %s> %s", pCreature->getName().c_str(), msg.c_str());
	}

	// invisibility»óÅÂ¸é Ç¬´Ù.
	if (pCreature->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
	{
		Zone* pZone = pCreature->getZone();
		Assert(pZone);
		addVisibleCreature(pZone, pCreature, true);
	}

	if (pCreature->isFlag(Effect::EFFECT_CLASS_SNIPING_MODE)) 
	{
		g_Sniping.checkRevealRatio(pCreature, 20, 10);
	}

	bool isVampire = false;
	// ¹ìÆÄÀÌ¾î°¡ ´Á´ë, ¹ÚÁãÀÌ¸é ¸»ÇÒ¼ö¾ø´Ù.
	if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
		
		if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF) || pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
				|| pVampire->isFlag( Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF ) )
		{
			Success = false;
		}

		isVampire = true;
	}

	if (pGamePlayer->isPenaltyFlag(PENALTY_TYPE_MUTE)) {
		Success = false;
	}

	if (pCreature->isFlag(Effect::EFFECT_CLASS_MUTE)) {
		Success = false;
	}

	if (Success) {
		// ÁÖº¯ PCµé¿¡°Ô ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
//		pCreature->getZone()->broadcastSayPacket(pCreature->getX() , pCreature->getY() , &gcSay , pCreature, isVampire);
		pCreature->getZone()->broadcastPacket(pCreature->getX() , pCreature->getY() , &gcSay , pCreature);
	}

	} catch (Throwable & t) {
		//cout << t.toString() << endl;
	}

#endif
		
	__END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__

void CGSayHandler::opExecute(Creature* pCreature, GamePlayer* pGamePlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	if (msg.substr(i+1 , 4) == "save"
		&& (pCreature->isDM() || pCreature->isGOD() )) {

		opsave(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "wall" && !(pCreature->isPLAYER())) {
		//cout << "==================Operator Order Wall Execute==================" << endl;

		opwall(pGamePlayer, msg, i);

	}

	// halt
	else if (msg.substr(i+1 , 8) == "shutdown" && pCreature->isGOD()) {
		//cout << "==================Operator Order Shutdown Execute==================" << endl;

		opshutdown(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 3) == "pay" && pCreature->isGOD()){
	
		oppay(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1 , 4) == "kick" && !(pCreature->isPLAYER())){
		//cout << "==================Operator Order kick Execute==================" << endl;

		opkick(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "mute" && pCreature->isGOD()){
		//cout << "==================Operator Order mute Execute==================" << endl;

		opmute(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 8) == "denychat" && !pCreature->isPLAYER()){
		//cout << "==================Operator Order denychat Execute==================" << endl;

		opdenychat(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 8) == "freezing" && pCreature->isGOD()){
		//cout << "==================Operator Order freezing Execute==================" << endl;

		opfreezing(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "deny" && !(pCreature->isPLAYER()) ) {
		//cout << "==================Operator Order deny Execute==================" << endl;


		opdeny(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 4) == "info" && pCreature->isGOD()){
		//cout << "==================Operator Order info Execute==================" << endl;

		opinfo(pGamePlayer, msg, i);

	}

	else if (msg.substr(i+1 , 5) == "trace" && !(pCreature->isPLAYER())){
		//cout << "==================Operator Order trace Execute==================" << endl;
		optrace(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1 , 4) == "warp" && !(pCreature->isPLAYER())){
		//cout << "==================Operator Order warp Execute==================" << endl;
		opwarp(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1 , 6) == "create" && pCreature->isGOD()){
		//cout << "==================Operator Order create Execute==================" << endl;
		opcreate(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1 , 6) == "summon" && pCreature->isGOD()){
		//cout << "==================Operator Order create Execute==================" << endl;
		opsummon(pGamePlayer, msg, i);
	}
	
	else if (msg.substr(i+1 , 5) == "grant" && pCreature->isGOD()){
		//cout << "==================Operator Order grant Execute==================" << endl;
		opgrant(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1 , 7) == "command" && pCreature->isGOD()){
		opcommand(pGamePlayer, msg, i);
	}
	
	else if (msg.substr(i+1 , 3) == "fun" && pCreature->isGOD()){
	
		opfun(pGamePlayer, msg, i);
	}

	else if ( msg.substr(i+1, 18) == "billing disconnect" && pCreature->isGOD() )
	{
		#ifdef __CONNECT_BILLING_SYSTEM__
		g_pBillingPlayerManager->setForceDisconnect();
		#endif
	}

	/*
	if (msg.substr(i+1 , 7) == "mrecall" && (pCreature->isGOD() || pCreature->isDM())) {

		Zone* pZone = pCreature->getZone();

		uint j = msg.find_first_of(' ' , i+1);

		BYTE MonsterType = atoi(msg.substr(j+1, msg.size()-j-1).c_str());

		Monster* pMonster = new Monster(MonsterType);

		pZone->addCreature(pMonster, pCreature->getX(), pCreature->getY(), pCreature->getDir(), true);

	}
	*/

	else if (msg.substr(i+1 , 6) == "recall" && pCreature->isGOD()) {
		//cout << "==================Operator Order recall Execute==================" << endl;
		oprecall(pGamePlayer, msg, i);
	}
	else if (msg.substr(i+1 , 4) == "user" && pCreature->isGOD()){
		//cout << "==================Operator Order user Execute==================" << endl;
		opuser(pGamePlayer, msg, i);
	}
	else if (msg.substr(i+1 , 6) == "notice" && pCreature->isGOD()){
		//cout << "==================Operator Order user Execute==================" << endl;
		opnotice(pGamePlayer, msg, i);
	}

	// °¢Á¾ ÇÔ¼ö¿ë °ª ¼¼ÆÃ¿ë ÇÔ¼ö
	// set type value ÇüÅÂ·Î Á¤ÀÇµÈ´Ù.
	// 2002.5.8 º° È®·üÀ» ÀÚÀ²ÀûÀ¸·Î Á¶ÀýÇÏ±â À§ÇØ¼­ ¸¸µë
	else if (msg.substr(i+1, 3) == "set" && pCreature->isGOD()) {
		opset(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1, 4) == "load" && pCreature->isGOD()) {
		opload(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1, 4) == "view" && pCreature->isGOD()) {
		opview(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1, 6) == "combat" && pCreature->isGOD()) {
		opcombat(pGamePlayer, msg, i);
	}
	
	else if (msg.substr(i+1, 4) == "find" || msg.substr(i+1, 4) == "¾îµð" && pCreature->isGOD()) {
		opfind(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1, 6) == "credit" && pCreature->isGOD()) {
		opcredit(pGamePlayer, msg, i);
	}

	else if (msg.substr(i+1, 9) == "soulchain" && pCreature->isGOD() )
	{
		opsoulchain( pGamePlayer, msg, i );
	}

	else if ( msg.substr(i+1, 3) == "log" && pCreature->isGOD() )
	{
		oplog( pGamePlayer, msg, i );
	}
	else if ( msg.substr(i+1, 10) == "bug_report" && pCreature->isGOD() )
	{
		uint j = msg.find_first_of(' ', i+1);
		if ( j == string::npos )
		{
			filelog("bugreport.log", "%s", msg.c_str());
			return;
		}

		string report = msg.substr(j+1, msg.size()-j-1);
		if ( ( j = report.find_first_of('\'') ) != string::npos ) report[j] = '_';
		if ( ( j = report.find_first_of('\\') ) != string::npos ) report[j] = '_';

		Statement* pStmt = NULL;

		try
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("INSERT INTO BugReportLog(PlayerID, Name, ReportTime, ReportLog) VALUES "
									"('%s', '%s', now(), '%s')", pGamePlayer->getID().c_str(), pCreature->getName().c_str(), report.c_str());

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)
				// ´©°¡ ÀÌ»óÇÑ°Å ³¯¸®¸é ¹«½ÃÇÏÀÚ
		} catch(...) { filelog("bugreport.log", "%s", msg.c_str()); }
	}
	else if ( msg.substr(i+1,11) == "CrashReport" && pCreature->isGOD())
	{
		uint j = msg.find_first_of(' ', i+1);
		uint k = msg.find_first_of(' ', j+13);
		uint l = msg.find_first_of(' ', k+1);
		uint m = msg.find_first_of(' ', l+1);
		if ( j == string::npos || k == string::npos || l == string::npos || m == string::npos )
		{
			filelog("CrashReport.log", "[%s] %s", pGamePlayer->getID().c_str(), msg.c_str() );
			return;
		}

		string ExecutableTime = msg.substr(j+1, k-j-1);
		string Version = msg.substr(k+1, l-k-1);
		string Address = msg.substr(l+1, m-l-1);
		string Message = msg.substr(m+1, msg.size()-m-1);

		cout << ExecutableTime << endl;
		cout << Version << endl;
		cout << Address << endl;
		cout << Message << endl;

		Statement* pStmt = NULL;

		try
		{
			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery("INSERT INTO CrashLog (PlayerID, Name, ReportTime, ExecutableTime, Version, Address, Message) VALUES "
									"('%s', '%s', now(), '%s', '%s', '%s', '%s')", pGamePlayer->getID().c_str(), pCreature->getName().c_str(),
									ExecutableTime.c_str(), Version.c_str(), Address.c_str(), Message.c_str() );

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)
				// ´©°¡ ÀÌ»óÇÑ°Å ³¯¸®¸é ¹«½ÃÇÏÀÚ
		} catch(...) { filelog("CrashReport.log", "%s", msg.c_str()); }
	}
	// add by sonic 2006.10.30 Ôö¼ÓÒ»¸öGMÃüÁî  Ö±½Ó´ò¿ª´ò±¦µØÍ¼
	else if ( msg.substr(i+1,10) == "OpenPayMap" || msg.substr(i+1, 12) == "´ò¿ªÊÕ·ÑµØÍ¼" && pCreature->isGOD())
	{
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(1013);
		pZoneInfo->setNoPortalZone(true);
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage("ÊÕ·ÑµØÍ¼ÒÑ¾­´ò¿ª");
		pGamePlayer->sendPacket (&gcSystemMessage);
	}
	else if ( msg.substr(i+1,11) == "ClosePayMap" || msg.substr(i+1, 12) == "¹Ø±ÕÊÕ·ÑµØÍ¼" && pCreature->isGOD())
	{
		ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfo(1013);
		pZoneInfo->setNoPortalZone(false);
		GCSystemMessage gcSystemMessage1;
		gcSystemMessage1.setMessage("ÊÕ·ÑµØÍ¼ÒÑ¾­¹Ø±Õ");
		pGamePlayer->sendPacket (&gcSystemMessage1);
	}


	__END_CATCH
}

void CGSayHandler::opcombat(GamePlayer* pGamePlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY
	
	if(pGamePlayer==NULL) return;

	Creature* pCreature = pGamePlayer->getCreature();
	if (pCreature==NULL) return;

	filelog("change.txt", "[%s] %s", pCreature->getName().c_str(), msg.c_str());

//	Creature* pCreature = pGamePlayer->getCreature();
	GCSystemMessage gcSystemMessage;

	// ÀÓ½Ã·Î ¸·¾ÆµÐ°Í
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_DO_NOT_SUPPORT_OLD_WAR ) );
		pGamePlayer->sendPacket (&gcSystemMessage);

		return;
	}

	StringStream message;

	uint j = msg.find_first_of(' ', i+1);
	uint z = msg.find_first_of(' ', j+1);

	string set_type = msg.substr(j+1, z-j-1);

	if(set_type == "start")
	{
		if(g_pCombatInfoManager->isCombat()
			|| g_pCombatInfoManager->isSlayerBonus()
			|| g_pCombatInfoManager->isVampireBonus())
		{
			cout << "ÀÌ¹Ì ÀüÀïÁßÀÔ´Ï´Ù" << endl;
//			message << "ÀÌ¹Ì ÀüÀïÁßÀÔ´Ï´Ù";
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_ALEADY_START ) );

			pGamePlayer->sendPacket (&gcSystemMessage);
		}
		else
		{
			cout << "ÀüÀïÀÌ ½ÃÀÛµÇ¾ú½À´Ï´Ù" << endl;
//			message << "ÀüÀïÀÌ ½ÃÀÛµÇ¾ú½À´Ï´Ù";
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_START ) );

			g_pZoneGroupManager->broadcast( &gcSystemMessage );

			// by sigi. 2002.7.5
			for (int i=0; i<maxRelic; i++)
			{
				const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(i));

				int ZoneNum = pRelicInfo->zoneID;

				ZoneInfo* pZoneInfo = NULL;

				try {
					pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZoneNum);
				} catch (NoSuchElementException&) {
					throw Error("Ã»ÓÐÕ½¶·ÇøÓò.");
				}

				ZoneGroup* pZoneGroup = NULL;

				try {
					pZoneGroup = g_pZoneGroupManager->getZoneGroup(pZoneInfo->getZoneGroupID());
				} catch (NoSuchElementException&) {
					throw Error("Ã»ÓÐÕ½¶·ÇøÓò.2");
				}

				Zone* pZone = pZoneGroup->getZone(ZoneNum);

				pZone->addRelicItem( i );
			}

			g_pCombatInfoManager->setCombat( true );
		}
	}
	else if(set_type == "end")
	{
		if(!g_pCombatInfoManager->isCombat()
			&& (g_pCombatInfoManager->isSlayerBonus()
				|| g_pCombatInfoManager->isVampireBonus()))

		{
			cout << "ÀüÀïÀ» Á¾·áÇÕ´Ï´Ù." << endl;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_COMBAT_END ) );
			g_pZoneGroupManager->broadcast( &gcSystemMessage );

			// by sigi. 2002.7.5
			for (int i=0; i<maxRelic; i++)
			{
				const RelicInfo* pRelicInfo = dynamic_cast<RelicInfo*>(g_pRelicInfoManager->getItemInfo(i));

				int ZoneNum = pRelicInfo->zoneID;

				ZoneInfo* pZoneInfo = NULL;

				try {
					pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZoneNum);
				} catch (NoSuchElementException&) {
					throw Error("Ã»ÓÐÕ½¶·ÇøÓò.");
				}

				ZoneGroup* pZoneGroup = NULL;

				try {
					pZoneGroup = g_pZoneGroupManager->getZoneGroup(pZoneInfo->getZoneGroupID());
				} catch (NoSuchElementException&) {
					throw Error("Ã»ÓÐÕ½¶·ÇøÓò.2");
				}

				Zone* pZone = pZoneGroup->getZone(ZoneNum);

				pZone->deleteRelicItem();
				g_pCombatInfoManager->setRelicOwner(i, CombatInfoManager::RELIC_OWNER_NULL);
			}

			g_pCombatInfoManager->computeModify();
			g_pCombatInfoManager->setCombat( false );
		}
		else
		{
			cout << "ÀüÀïÁßÀÌ ¾Æ´Ï°Å³ª Á¾·áÇÒ ¼ö ¾ø½À´Ï´Ù." << endl;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_END_COMBAT ) );
			
			pGamePlayer->sendPacket (&gcSystemMessage);
		}

	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opview(GamePlayer* pGamePlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	if (pGamePlayer==NULL) return;
	
	Creature* pCreature = pGamePlayer->getCreature();
	GCSystemMessage gcSystemMessage;
	StringStream message;

	uint j = msg.find_first_of(' ' , i+1);
	uint z = msg.find_first_of(' ' , j+1);
	
	string set_type = msg.substr(j+1, z-j-1);

	cout << "modifier : " << pCreature->getName() << " set type : " << set_type << endl;

	if(set_type == "star")
	{
	    message << "star : 1/" << g_pVariableManager->getStar();
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "evnet_activate")
	{
		if(g_pVariableManager->getEventActivate() == 1)
			message << "ÊÂ¼þÕýÔÚ½øÐÐÖÐ..." << endl;
		else
			message << "ÊÂ¼þÒÑÍ£Ö¹" << endl;
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "event_ratio")
	{
	    message << "Ê±¼ä¹ÖÎï±¬ÂÊ 1/" << g_pVariableManager->getEventRatio();
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "exp_ratio")
	{
	    message << "¾­ÑéÖµ: " << g_pVariableManager->getExpRatio();
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "item_prob_ratio")
	{
	    message << "ÎïÆ·±¬ÂÊ: " << g_pVariableManager->getItemProbRatio();
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "combat_bonus_time")
	{
	    message << "Õ½¶·Ê¤ÀûÎ¬³ÖÊ±¼ä: " << g_pVariableManager->getCombatBonusTime() << "·Ö";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "combat_bonus_slayer_hp_ratio")
	{
	    message << "ÈËÀàÕ½¶· HP½±ÀøÔö¼ÓÖµ: +" << g_pVariableManager->getCombatSlayerHPBonusRatio() << "%";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "combat_bonus_vampire_hp_ratio")
	{
	    message << "ÎüÑª¹íÕ½¶· HP½±ÀøÔö¼ÓÖµ: +" << g_pVariableManager->getCombatVampireHPBonusRatio() << "%";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "combat_bonus_slayer_damage")
	{
	    message << "ÈËÀàÕ½¶· Damage½±ÀøÔö¼ÓÖµ: +" << g_pVariableManager->getCombatSlayerDamageBonus();
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "combat_bonus_vampire_damage")
	{
	    message << "ÎüÑª¹íÕ½¶· Damage½±ÀøÔö¼ÓÖµ: +" << g_pVariableManager->getCombatVampireDamageBonus();
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "premium_exp_bonus_percent")
	{
	    message << "¸¶·ÑÓÃ»§¾­ÑéÖµ½±Àø: " << g_pVariableManager->getPremiumExpBonusPercent() << "%";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "premium_item_probe_percent")
	{
	    message << "¸¶·ÑµØÍ¼ÎïÆ·±©ÂÊ: " << g_pVariableManager->getPremiumItemProbePercent() << "%";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "zone_group_balancing_minute")
	{
	    message << "ZoneGroupBalancingÊ±¼ä: " << g_pVariableManager->getZoneGroupBalancingMinute() << "·Ö";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "zone_group_next_balancing_time")
	{ 
		const Timeval& tv = g_pClientManager->getBalanceZoneGroupTime();
		Timeval currentTime;
		getCurrentTime(currentTime);
	    message << "ÏÂ´ÎZoneGroupBalancingÊ±¼ä: " << (tv.tv_sec - currentTime.tv_sec)/60 << "·Öºó";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "gamble_item_type_ratio")
	{
	    message << "¶Ä²©ItemType±©ÂÊ: " << g_pVariableManager->getGambleItemTypeRatio() << "%";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "gamble_item_option_ratio")
	{
	    message << "¶Ä²©ItemOption±©ÂÊ: " << g_pVariableManager->getGambleItemOptionRatio() << "%";
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "summon_motorcycle")
	{
	    message << "Ä¦ÍÐ³µÕÙ»½¼¼ÄÜ : " << (g_pVariableManager->isSummonMotorcycle()? "ON":"OFF");
		gcSystemMessage.setMessage(message.toString());
	}
	else if (set_type == "enemy_limit_time")
	{
		message << "¹ÖÎïÓÐÐ§Ê±¼ä: " << g_pVariableManager->getEnemyLimitTime() << "Ãë";
		gcSystemMessage.setMessage(message.toString());
 	}				
	else if (set_type == "rare_item_ratio")
	{
		message << "¸ß¼¶ÎïÆ·±©ÂÊ: " << g_pVariableManager->getRareItemRatio() << "%";
		gcSystemMessage.setMessage(message.toString());
 	}				
	else if (set_type == "unique_item_ratio")
	{
		message << "Ï¡ÊÀÎïÆ·±©ÂÊ: " << g_pVariableManager->getUniqueItemRatio() << "/10000";
		gcSystemMessage.setMessage(message.toString());
 	}				
	else if(set_type == "active_master_lair")
	{
	    message << "ÀÏ¹Ö»î¶¯ : " << (g_pVariableManager->isActiveMasterLair()? "ON":"OFF");
		gcSystemMessage.setMessage(message.toString());
	}
	else if(set_type == "retry_master_lair")
	{
	    message << "±»ÀÏ¹ÖÉ±ËÀºó,ÖØÐÂÌôÕ½ : " << (g_pVariableManager->isRetryMasterLair()? "ON":"OFF");
		gcSystemMessage.setMessage(message.toString());
	}
	else if (set_type == "harvest_festival_item_ratio")
	{
		message << "ÖÐÇï½Ú×£¸£±©ÂÊ: 1/" << g_pVariableManager->getHarvestFestivalItemRatio();
		gcSystemMessage.setMessage(message.toString());
 	}
	else if (set_type == "master_blood_drain_start_hp")
	{
		message << "¿ªÊ¼ÎüÑªÊ±µÄHP: " << g_pVariableManager->getMasterBloodDrainStartHP() << "%";
		gcSystemMessage.setMessage(message.toString());
 	}
	else if (set_type == "master_blood_drain_start_bd")
	{
		message << "¿ªÊ¼ÎüÑªÊ±µÄÎüÑªÂÊ: " << g_pVariableManager->getMasterBloodDrainStartBD() << "%";
		gcSystemMessage.setMessage(message.toString());
 	}
	else if (set_type == "master_blood_drain_end_hp")
	{
		message << "½áÊøÎüÑªÊ±(?)µÄHP: " << g_pVariableManager->getMasterBloodDrainEndHP() << "%";
		gcSystemMessage.setMessage(message.toString());
 	}
	else if (set_type == "master_blood_drain_end_bd")
	{
		message << "½áÊøÎüÑªÊ±(?)ÎüÑªÂÊ: " << g_pVariableManager->getMasterBloodDrainEndBD() << "%";
		gcSystemMessage.setMessage(message.toString());
 	}
	else if(set_type == "chief_monster")
	{
	    message << "Ë¢ÐÂBOSS¹ÖÎï : " << (g_pVariableManager->isActiveChiefMonster()? "ON":"OFF");
		gcSystemMessage.setMessage(message.toString());
	}
	else if (set_type == "chief_monster_rare_item_percent")
	{
		message << "BOSS¹ÖÎï¸ß¼¶ÎïÆ·±©ÂÊ: " << g_pVariableManager->getChiefMonsterRareItemPercent() << "%";
		gcSystemMessage.setMessage(message.toString());
 	}
	else if (set_type == "newbie_transport_to_guild")
	{
		message << "ÒÆ¶¯µ½ÄÜÁ¦ÖµÎª40µÄÐÐ»á:" << (g_pVariableManager->isNewbieTransportToGuild()? "ON":"OFF");
		gcSystemMessage.setMessage(message.toString());
 	}
	else
	{
		// by sigi. 2002.11.19
		VariableType vt = g_pVariableManager->getVariableType( set_type );

		if (vt!=VARIABLE_MAX)
		{
			const string& msg = g_pVariableManager->toString(vt);
			gcSystemMessage.setMessage(msg);
		}
		else
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_WRONG_VARIABLE_NAME ) );
		}
	}

	// ÀÚ½Å¿¡°Ô¸¸ ½Ã½ºÅÛ ¸Þ½ÃÁö º¸³»±â (¼öÁ¤µÇ¾úÀ»½Ã)
	pGamePlayer->sendPacket (&gcSystemMessage);

	__END_CATCH
}
#endif

#ifdef __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opload(GamePlayer* pGamePlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY
	
	GCSystemMessage gcSystemMessage;
	StringStream message;

	uint j = msg.find_first_of(' ' , i+1);
	uint z = msg.find_first_of(' ' , j+1);
	
	string load_type = msg.substr(j+1, z-j-1);
	string load_value = "0";
	
	if (z!=string::npos)
		load_value = msg.substr(z+1);

	if(load_type.length() < 1)
		return;

	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();
		filelog("change.txt", "[LOAD] %s , %s , %s", pCreature->getName().c_str(), load_type.c_str(), load_value.c_str());
	}

	EventReloadInfo* pEvent = NULL;

	if (load_type == "master_lair_info")
	{
		pEvent =  new EventReloadInfo( pGamePlayer,  EventReloadInfo::MASTER_LAIR_INFO );
//		StringStream msg;
//		msg << "¸¶½ºÅÍ ·¹¾î Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_MASTER_LAIR_INFO ) );
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if (load_type == "monster_info")
	{
	//	string MonsterName = load_value;
		string MonsterName = "all";
		int SpriteType = 0;

		// ÀÏ´Ü 'ÀÌ¸§'À¸·Î ¸ó½ºÅÍ SpriteTypeÀ» Ã£¾Æº»´Ù.
//		int SpriteType = g_pMonsterInfoManager->getSpriteTypeByName( MonsterName );

//		if (SpriteType==0)
//		{
			// ÀÌ¸§À¸·Î ¾ø´Ù¸é.. °ª ÀÚÃ¼°¡ ¼ýÀÚ(SpriteType)ÀÎ°¡?
//			SpriteType = atoi( MonsterName.c_str() );
//		}	

		bool bExist = true;
//		try 
//		{
//			g_pMonsterInfoManager->getMonsterTypeBySprite(SpriteType);
//		} catch (Throwable&) {
//			bExist = false;
//		}

//		StringStream msg;
        char msg[100];

		if (bExist || MonsterName=="all")
		{
			// allÀÎ °æ¿ì´Â SpriteTypeÀÌ 0ÀÌ´Ù.
			pEvent =  new EventReloadInfo( pGamePlayer,  EventReloadInfo::MONSTER_INFO, SpriteType );

			if (SpriteType!=0)
			{
                sprintf( msg, g_pStringPool->c_str( STRID_LOAD_MONSTER_INFO ),
                                load_value.c_str() );
//				msg << "¸ó½ºÅÍ Á¤º¸(" << load_value.c_str() << ")¸¦ loadÇÕ´Ï´Ù.";
			}
			else
			{
                sprintf( msg, g_pStringPool->c_str( STRID_LOAD_ALL_MONSTER_INFO ) );
//				msg << "¸ðµç ¸ó½ºÅÍ Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
			}
		}
		else
		{
            sprintf( msg, g_pStringPool->c_str( STRID_LOAD_WRONG_MONSTER_INFO ),
                            load_value.c_str() );
//			msg << "¸ó½ºÅÍ(" << load_value.c_str() << ")°¡ Àß¸ø ÁöÁ¤µÇ¾ú½À´Ï´Ù.";
		}

		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if (load_type == "monster_ai")
	{
		pEvent =  new EventReloadInfo( pGamePlayer,  EventReloadInfo::MONSTER_AI );
//		StringStream msg;
//		msg << "¸ó½ºÅÍ AIÁ¤º¸(DirectiveSet)¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_DIRECTIVESET ) );
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if (load_type == "zone_info")
	{
		pEvent =  new EventReloadInfo( pGamePlayer,  EventReloadInfo::ZONE_INFO );
//		StringStream msg;
//		msg << "Á¸ Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_ZONE ) );
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if (load_type == "zone")
	{
		int zoneID = atoi(load_value.c_str());

		pEvent =  new EventReloadInfo( pGamePlayer,  EventReloadInfo::ZONE, zoneID );

//		StringStream msg;
//		msg << "Á¸À» loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_ZONE ) );
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if (load_type == "log_user")
	{
		pEvent =  new EventReloadInfo( pGamePlayer,  EventReloadInfo::LOG_USER_INFO );
//		StringStream msg;
//		msg << "LogUser Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_LOG_USER ) );
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if (load_type == "item_info")
	{
		Item::ItemClass ItemClass = g_pItemFactoryManager->getItemClassByName( load_value );

		// ItemClass°¡ MAX¶ó¸é ÀÌ¸§À¸·Î´Â ¸ø Ã£¾Ò´Ù´Â ¸»ÀÌ´Ù. 
		// ÀÌ °æ¿ì¿¡´Â ¾ÆÀÌÅÛ Å¬·¡½º°¡ ¼ýÀÚ·Î ¹Ù·Î ¿ÀÁö´Â ¾Ê¾Ò´ÂÁö °Ë»çÇØ¾ß ÇÑ´Ù.
		if (ItemClass == Item::ITEM_CLASS_MAX)
		{
			int temp = atoi(load_value.c_str());
			if (temp < 0 || temp >= Item::ITEM_CLASS_MAX)
			{
				return;
			}
			else
			{
				ItemClass = (Item::ItemClass)(temp);
			}
		}

		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::ITEM_INFO, ItemClass );

//		StringStream msg;
//		msg << load_value << " Info¸¦ loadÇÕ´Ï´Ù.";

        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_LOAD_ITEM_INFO ),
                        load_value.c_str() );
        gcSystemMessage.setMessage( msg );
	}
	else if ( load_type == "option_info" )
	{
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::OPTION_INFO );
	//	StringStream msg;
	//	msg << "OptionInfo Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_OPTION_INFO ) );
	}
	else if ( load_type == "rank_bonus_info" )
	{
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::RANK_BONUS_INFO );
//		StringStream msg;
//		msg << "RankBonusInfo Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_RANK_BONUS_INFO ) );
	}
    else if ( load_type == "string_pool" )
    {
        pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::STRING_POOL );
        gcSystemMessage.setMessage( "reload StringPool" );
    }
	else if ( load_type == "war_schedule_info" )
	{
		ZoneID_t zoneID = atoi( load_value.c_str() );

		// ¼³Á¤ ¾ÈµÈ °æ¿ì´Â ÇöÀç Creature°¡ ÀÖ´Â Á¸
		if (zoneID==0)
		{
			if (pGamePlayer!=NULL)
			{
				Creature* pCreature = pGamePlayer->getCreature();
				Assert(pCreature!=NULL);

				Zone* pZone = pCreature->getZone();
				Assert(pZone!=NULL);

				zoneID = pZone->getZoneID();
			}
		}

		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::WAR_SCHEDULE_INFO, zoneID );

		StringStream msg;
		msg << g_pStringPool->getString( STRID_LOAD_WAR_SCHEDULE_INFO );

		if (!g_pVariableManager->isWarActive())
		{
			msg << g_pStringPool->getString( STRID_WAR_OFF );
		}

		gcSystemMessage.setMessage(msg.toString().c_str());

	}
	else if ( load_type == "blood_bible_owner" )
	{
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::BLOOD_BIBLE_OWNER );

//		StringStream msg;
//		msg << "BloodBibleOwner Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_BLOOD_BIBLE_OWNER_INFO ) );
	}
	else if ( load_type == "sweeper_owner" )
	{
		int level = atoi( load_value.c_str() );
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::SWEEPER_OWNER, level );

//		StringStream msg;
//		msg << "BloodBibleOwner Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_BLOOD_BIBLE_OWNER_INFO ) );
	}
	else if ( load_type == "race_war_pc_limit" )
	{
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::RACE_WAR_PC_LIMIT );

//		StringStream msg;
//		msg << "RaceWarPCLimit Á¤º¸¸¦ loadÇÕ´Ï´Ù.";
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_RACE_WAR_PC_LIMIT_INFO ) );
	}
	else if ( load_type == "npc" )
	{
		ZoneID_t zoneID = (ZoneID_t)(atoi(load_value.c_str()));
		Zone* pZone = getZoneByZoneID( zoneID );
		if ( pZone != NULL)
		{
			// ¼º ¿Ü¿¡´Â NPC °¡ »ç¶óÁö´Â ÀÏÀÌ ¾øÀ¸´Ï -_-a
			CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( zoneID );

			if ( pCastleInfo != NULL)
				pZone->loadNPCs( pCastleInfo->getRace() );
		}

	}
	else if ( load_type == "goods_list_info" )
	{
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::GOODS_LIST_INFO );

		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_GOODS_LIST_INFO ) );
	}
/*	else if ( load_type == "quest_info" )
	{
		pEvent = new EventReloadInfo( pGamePlayer, EventReloadInfo::QUEST_INFO );

		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_LOAD_QUEST_INFO ) );
	}*/
	else
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_WRONG_VARIABLE_NAME ) );
	}

	if (pEvent!=NULL)
	{
		g_pClientManager->addEvent( pEvent );
	}

	// ÀÚ½Å¿¡°Ô¸¸ ½Ã½ºÅÛ ¸Þ½ÃÁö º¸³»±â (¼öÁ¤µÇ¾úÀ»½Ã)
	if (pGamePlayer!=NULL)
	{
		pGamePlayer->sendPacket( &gcSystemMessage );
	}
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opset(GamePlayer* pGamePlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	// [!!!] GGCommand¸¦ ÅëÇØ¼­ ¿©±â°¡ Ã³¸®µÉ¶§¿¡´Â
	// pGamePlayer°¡ NULLÀÏ ¼ö ÀÖÀ¸¹Ç·Î.. ²À Ã¼Å©¸¦ ÇØ¾ßÇÑ´Ù! by sigi.2002.12.23
	
	GCSystemMessage gcSystemMessage;
	StringStream message;

	uint j = msg.find_first_of(' ' , i+1);
	uint z = msg.find_first_of(' ' , j+1);
	
	string set_type = msg.substr(j+1, z-j-1);
	string set_value = msg.substr(z+1);

	if(set_value.length() < 1)
		return;

	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();
		filelog("change.txt", "%s , %s , %s", pCreature->getName().c_str(), set_type.c_str(), set_value.c_str());
	}

	
	if(set_type == "star")
	{
		g_pVariableManager->setStar(atoi(set_value.c_str()));
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_STAR_RATIO ),
                        set_value.c_str() );
//	    message << "º° ÃâÇö È®·üÀÌ 1/" << set_value << "·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "event_activate")
	{
		if(set_value == "start")
		{
			g_pVariableManager->setEventActivate(1);
//	    	message << "ÀÌº¥Æ®°¡ ½ÃÀÛµÇ¾ú½À´Ï´Ù";
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EVENT_START ) );
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else
		{
			g_pVariableManager->setEventActivate(0);
//	    	message << "ÀÌº¥Æ®°¡ ÁßÁöµÇ¾ú½À´Ï´Ù";
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_EVENT_END ) );
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
	}
	else if(set_type == "event_ratio")
	{
		g_pVariableManager->setEventRatio(atoi(set_value.c_str()));
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_EVENT_MONSTER_RATIO ),
                        set_value.c_str() );
//	    message << "ÀÌº¥Æ® ¸ó½ºÅÍ ÃâÇö È®·üÀÌ ÀÇÇØ¼­ 1/" << set_value << "·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "exp_ratio")
	{
		int value = atoi(set_value.c_str());
		if (value < 100)
			return;

		g_pVariableManager->setExpRatio(value);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_EXP_RATIO ),
                        set_value.c_str() );
//	    message << "°æÇèÄ¡ È¹µæ·üÀÌ" << set_value << "%·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "item_prob_ratio")
	{
		int value = atoi(set_value.c_str());
		if(value < value)
			return;

		g_pVariableManager->setItemProbRatio(value);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_ITEM_PROBE_RATIO ),
                        set_value.c_str() );
//	    message << "¾ÆÀÌÅÛ È¹µæ·üÀÌ " << set_value << "%·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "combat_bonus_time")
	{
		int bonusTime = atoi(set_value.c_str());
		if (bonusTime < 1 || bonusTime > 14400)
			return;

		g_pVariableManager->setCombatBonusTime(bonusTime);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_COMBAT_BONUS_TIME ),
                        set_value.c_str() );
//	    message << "ÀüÀï ½Â¸® À¯Áö½Ã°£ÀÌ " << set_value << "ºÐÀ¸·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "combat_bonus_slayer_hp_ratio")
	{
		int bonus= atoi(set_value.c_str());
		if (bonus< 0 || bonus> 100)
			return;

		g_pVariableManager->setCombatSlayerHPBonusRatio(bonus);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_COMBAT_SLAYER_BONUS_HP ),
                        set_value.c_str() );
//	    message << "½½·¹ÀÌ¾î ÀüÀï HPº¸³Ê½º°¡ +" << set_value << "% ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "combat_bonus_vampire_hp_ratio")
	{
		int bonus= atoi(set_value.c_str());
		if (bonus< 0 || bonus> 100)
			return;

		g_pVariableManager->setCombatVampireHPBonusRatio(bonus);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_COMBAT_VAMPIRE_BONUS_HP ),
                        set_value.c_str() );
//	    message << "¹ìÆÄÀÌ¾î ÀüÀï HPº¸³Ê½º°¡ +" << set_value << "% ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "combat_bonus_slayer_damage")
	{
		int bonus= atoi(set_value.c_str());
		if (bonus< 0 || bonus> 20)
			return;

		g_pVariableManager->setCombatSlayerDamageBonus(bonus);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_COMBAT_SLAYER_BONUS_DAMAGE ),
                        set_value.c_str() );
//	    message << "½½·¹ÀÌ¾î ÀüÀï µ¥¹ÌÁöº¸³Ê½º°¡ +" << set_value << " ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "combat_bonus_vampire_damage")
	{
		int bonus= atoi(set_value.c_str());
		if (bonus< 0 || bonus> 20)
			return;

		g_pVariableManager->setCombatVampireDamageBonus(bonus);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_COMBAT_VAMPIRE_BONUS_DAMAGE ),
                        set_value.c_str() );
//	    message << "¹ìÆÄÀÌ¾î ÀüÀï µ¥¹ÌÁöº¸³Ê½º°¡ +" << set_value << " ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "premium_exp_bonus_percent")
	{
		int bonus= atoi(set_value.c_str());
		if (bonus< 100 || bonus> 1000)
			return;

		g_pVariableManager->setPremiumExpBonusPercent(bonus);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_PREMIUM_EXP_RATIO ),
                        set_value.c_str() );
//	    message << "ÇÁ¸®¹Ì¾ö »ç¿ëÀÚÀÇ °æÇèÄ¡ º¸³Ê½º°¡ " << set_value << "% ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "premium_item_probe_percent")
	{
		int bonus= atoi(set_value.c_str());
		if (bonus< 100 || bonus> 1000)
			return;

		g_pVariableManager->setPremiumItemProbePercent(bonus);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_PREMIUM_ITEM_PROBE_RATIO ),
                        set_value.c_str() );
//	    message << "ÇÁ¸®¹Ì¾ö Á¸ÀÇ ¾ÆÀÌÅÛ ·çÆÃ È®·üÀÌ " << set_value << "% ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "zone_group_balancing_minute")
	{
		int minute= atoi(set_value.c_str());
		if (minute<=0 || minute>30*24*60)
			return;

		g_pVariableManager->setZoneGroupBalancingMinute(minute);
		g_pClientManager->setBalanceZoneGroup(minute);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_ZONE_GROUP_BALANCING_TIME ),
                        set_value.c_str() );
//	    message << "ZoneGroupBalancing ÁÖ±â°¡ " << set_value << "ºÐÀ¸·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "gamble_item_type_ratio")
	{
		int ratio= atoi(set_value.c_str());
		if (ratio<=10 || ratio>1000)
			return;

		g_pVariableManager->setGambleItemTypeRatio(ratio);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_GAMBLE_ITEM_TYPE_RATIO ),
                        set_value.c_str() );
//	    message << "°·ºí ItemTypeÈ®·üÀÌ " << set_value << "%·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "gamble_item_option_ratio")
	{
		int ratio= atoi(set_value.c_str());
		if (ratio<=10 || ratio>1000)
			return;

		g_pVariableManager->setGambleItemOptionRatio(ratio);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_GAMBLE_ITEM_OPTION_RATIO ),
                        set_value.c_str() );
//	    message << "°·ºí ItemOptionÈ®·üÀÌ " << set_value << "%·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "summon_motorcycle")
	{
		if (set_value=="on")
		{
			g_pVariableManager->setSummonMotorcycle(true);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_SUMMON_MOTORCYCLE ), "ON" );
//			message << "¿ÀÅä¹ÙÀÌ ¼ÒÈ¯ ±â´ÉÀÌ ON µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else if (set_value=="off")
		{
			g_pVariableManager->setSummonMotorcycle(false);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_SUMMON_MOTORCYCLE ), "OFF" );
//			message << "¿ÀÅä¹ÙÀÌ ¼ÒÈ¯ ±â´ÉÀÌ OFF µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
	}
	else if(set_type == "enemy_limit_time")
	{
		int enemy_limit_time = atoi(set_value.c_str());
		if (enemy_limit_time<=180 || enemy_limit_time>=3600)
			return;

		g_pVariableManager->setEnemyLimitTime(enemy_limit_time);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_MONSTER_FORGET_TIME ),
                        set_value.c_str() );
//	    message << "¸ó½ºÅÍÀÇ ¿¬¼Ó Àû ÀÎ½Ä½Ã°£ÀÌ" << set_value << "ÃÊ·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "rare_item_ratio")
	{
		int ratio = atoi(set_value.c_str());
		if (ratio<0 || ratio>100000)
			return;

		g_pVariableManager->setRareItemRatio(ratio);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_RARE_ITEM_RATIO ),
                        set_value.c_str() );
//		message << "·¹¾î ¾ÆÀÌÅÛ ·çÆÃ È®·üÀÌ " << set_value << "%·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "unique_item_ratio")
	{
		int ratio = atoi(set_value.c_str());
		if (ratio<0 || ratio>10000)
			return;

		g_pVariableManager->setUniqueItemRatio(ratio);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_UNIQUE_ITEM_RATIO ),
                        set_value.c_str() );
//		message << "À¯´ÏÅ© ¾ÆÀÌÅÛ ·çÆÃ È®·üÀÌ " << set_value << "/10000 À¸·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "active_master_lair")
	{
		MasterLairManager* pMasterLairManager = NULL;

		if (pGamePlayer!=NULL)
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Zone* pZone = pCreature->getZone();
			pMasterLairManager = pZone->getMasterLairManager();
		}

		if (set_value=="on")
		{
			g_pVariableManager->setActiveMasterLair(true);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_MASTER_LAIR_ACTIVATE ), "ON" );
//			message << "¸¶½ºÅÍ ·¹¾î ÀÌº¥Æ®°¡ ON µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());

			if (pMasterLairManager!=NULL)
			{
				pMasterLairManager->startEvent();
			}
		}
		else if (set_value=="off")
		{
			g_pVariableManager->setActiveMasterLair(false);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_MASTER_LAIR_ACTIVATE ), "OFF" );
//			message << "¸¶½ºÅÍ ·¹¾î ÀÌº¥Æ®°¡ OFF µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());

			if (pMasterLairManager!=NULL)
			{
				pMasterLairManager->stopEvent();
			}
		}
	}
	else if(set_type == "retry_master_lair")
	{
		if (set_value=="on")
		{
			g_pVariableManager->setRetryMasterLair(true);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_RETRY_MASTER_LAIR ), "ON" );
//			message << "¸¶½ºÅÍ ·¹¾î¿¡ Á×°í ´Ù½Ã µé¾î°¡±â°¡ ON µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else if (set_value=="off")
		{
			g_pVariableManager->setRetryMasterLair(false);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_RETRY_MASTER_LAIR ), "OFF" );
//			message << "¸¶½ºÅÍ ·¹¾î¿¡ Á×°í ´Ù½Ã µé¾î°¡±â°¡ OFF µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
	}

	else if(set_type == "harvest_festival_item_ratio")
	{
		int ratio = atoi(set_value.c_str());
		if (ratio<0 || ratio>10000)
			return;

		g_pVariableManager->setHarvestFestivalItemRatio(ratio);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_HARVEST_FESTIVAL_ITEM_RATIO ),
                        set_value.c_str() );
//		message << "Ãß¼® ¼ÛÆí ¾ÆÀÌÅÛ ·çÆÃ È®·üÀÌ 1/" << ratio << "ÀÌ µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "master_blood_drain_start_hp")
	{
		int percent = atoi(set_value.c_str());
		if (percent<0 || percent>100)
			return;

		g_pVariableManager->setMasterBloodDrainStartHP(percent);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_MASTER_BLOOD_DRAIN_START_HP ),
                        set_value.c_str() );
//		message << "¸¶½ºÅÍÀÇ ÈíÇ÷ ½ÃÀÛ HP°¡ " << percent << "%°¡ µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "master_blood_drain_start_bd")
	{
		int percent = atoi(set_value.c_str());
		if (percent<0 || percent>100)
			return;

		g_pVariableManager->setMasterBloodDrainStartBD(percent);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_MASTER_BLOOD_DRAIN_START_BD ),
                        set_value.c_str() );
//		message << "¸¶½ºÅÍÀÇ ÈíÇ÷ ½ÃÀÛ ¶§ÀÇ ÈíÇ÷ È®·üÀÌ " << percent << "%°¡ µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "master_blood_drain_end_hp")
	{
		int percent = atoi(set_value.c_str());
		if (percent<0 || percent>100)
			return;

		g_pVariableManager->setMasterBloodDrainEndHP(percent);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_MASTER_BLOOD_DRAIN_END_HP ),
                        set_value.c_str() );
//		message << "¸¶½ºÅÍÀÇ ÈíÇ÷ ³¡(?) HP°¡ " << percent << "%°¡ µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "master_blood_drain_end_bd")
	{
		int percent = atoi(set_value.c_str());
		if (percent<0 || percent>100)
			return;

		g_pVariableManager->setMasterBloodDrainEndBD(percent);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_MASTER_BLOOD_DRAIN_END_BD ),
                        set_value.c_str() );
//		message << "¸¶½ºÅÍÀÇ ÈíÇ÷ ³¡(?) »óÅÂÀÇ ÈíÇ÷ È®·üÀÌ " << percent << "%°¡ µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "chief_monster")
	{
		if (set_value=="on")
		{
			g_pVariableManager->setActiveChiefMonster(true);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_CHIEF_MONSTER ), "ON" );
//			message << "Ä¡ÇÁ ¸ó½ºÅÍ ±â´ÉÀÌ ON µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else if (set_value=="off")
		{
			g_pVariableManager->setActiveChiefMonster(false);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_CHIEF_MONSTER ), "OFF" );
//			message << "Ä¡ÇÁ ¸ó½ºÅÍ ±â´ÉÀÌ OFF µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
	}
	else if(set_type == "chief_monster_rare_item_percent")
	{
		int ratio = atoi(set_value.c_str());
		if (ratio<0 || ratio>100)
			return;

		g_pVariableManager->setChiefMonsterRareItemPercent(ratio);
        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_SET_CHIEF_MONSTER_RARE_ITEM_RATIO ),
                        set_value.c_str() );
//		message << "Ä¡ÇÁ ¸ó½ºÅÍ ·¹¾î ¾ÆÀÌÅÛ ·çÆÃ È®·üÀÌ " << set_value << "%·Î ¼öÁ¤µÇ¾ú½À´Ï´Ù.";
		gcSystemMessage.setMessage(msg);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
	}
	else if(set_type == "newbie_transport_to_guild")
	{
		if (set_value=="on")
		{
			g_pVariableManager->setNewbieTransportToGuild(true);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_NEWBIE_TRANSPORT_TO_GUILD ), "ON" );
//			message << "´É·ÂÄ¡ 40Â¥¸®, ±æµå·Î ÀÌµ¿½ÃÅ°±â ±â´ÉÀÌ ON µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else if (set_value=="off")
		{
			g_pVariableManager->setNewbieTransportToGuild(false);
            char msg[100];
            sprintf( msg, g_pStringPool->c_str( STRID_SET_NEWBIE_TRANSPORT_TO_GUILD ), "OFF" );
//			message << "´É·ÂÄ¡ 40Â¥¸®, ±æµå·Î ÀÌµ¿½ÃÅ°±â ±â´ÉÀÌ OFF µÇ¾ú½À´Ï´Ù.";
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
	}
	else if ( set_type == "xmas_2002" )
	{
		uint l = set_value.find_first_of(' ' , 0);
		uint m = set_value.find_first_of(' ' , l+1);
		
		string value_firecracker	= set_value.substr( 0, l);
		string value_treepart		= set_value.substr( l+1, m-l-1 );
		string value_giftbox		= set_value.substr( m+1 );

		g_pVariableManager->setVariable(CHRISTMAS_FIRE_CRACKER_RATIO, value_firecracker);
		const string& msg1 = g_pVariableManager->toString(CHRISTMAS_FIRE_CRACKER_RATIO);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		gcSystemMessage.setMessage(msg1);
		
		if (pGamePlayer!=NULL)
			pGamePlayer->sendPacket (&gcSystemMessage);

		g_pVariableManager->setVariable(CHRISTMAS_TREE_PART_RATIO, value_treepart);
		const string& msg2 = g_pVariableManager->toString(CHRISTMAS_TREE_PART_RATIO);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		gcSystemMessage.setMessage(msg2);

		if (pGamePlayer!=NULL)
			pGamePlayer->sendPacket (&gcSystemMessage);

		g_pVariableManager->setVariable(CHRISTMAS_GIFT_BOX_RATIO, value_giftbox);
		const string& msg3 = g_pVariableManager->toString(CHRISTMAS_GIFT_BOX_RATIO);
		filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());

		gcSystemMessage.setMessage(msg3);

	}
	else if (set_type =="ItemTaxRatio")
	{
		if (pGamePlayer != NULL) 
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Zone* pZone = pCreature->getZone();
			if (set_value.size() != 0)
			{
				int Tax = atoi(set_value.c_str());
				g_pCastleInfoManager->setItemTaxRatio( pZone, Tax );
			}
			else 
			{
				gcSystemMessage.setMessage( g_pStringPool->getString( STRID_WRONG_ITEM_TAX_RATIO ) );
			}
		}
	}

	else
	{
		// by sigi. 2002.11.19
		VariableType vt = g_pVariableManager->getVariableType( set_type );

		if (vt!=VARIABLE_MAX)
		{
			g_pVariableManager->setVariable(vt, set_value);
			const string& msg = g_pVariableManager->toString(vt);
			gcSystemMessage.setMessage(msg);
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());

			if ( vt == PREMIUM_HALF_EVENT )
			{
				GCNoticeEvent gcNoticeEvent;

				if (g_pVariableManager->getVariable( vt ))
				{
					gcNoticeEvent.setCode( NOTICE_EVENT_PREMIUM_HALF_START );
				}
				else 
				{
					gcNoticeEvent.setCode( NOTICE_EVENT_PREMIUM_HALF_END );
				}

				// À¯·áÁ¸¿¡¸¸ »Ñ¸°´Ù.
				getZoneByZoneID( 61 )->broadcastPacket( &gcNoticeEvent );		// Æä·Î³ªºÏµ¿
				getZoneByZoneID( 64 )->broadcastPacket( &gcNoticeEvent );		// Æä·Î³ª³²¼­
				getZoneByZoneID( 1007 )->broadcastPacket( &gcNoticeEvent );		// ¶ó¼¾¼º³»ºÎ(¹ÙÅä¸®¸¶À»)
			}
			else if ( vt == TODAY_IS_HOLYDAY )
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode( NOTICE_EVENT_HOLYDAY );
				gcNoticeEvent.setParameter( g_pVariableManager->getVariable(vt) );

				g_pZoneGroupManager->broadcast( &gcNoticeEvent );
			}
			else if ( vt == CROWN_PRICE )
			{
				GCNoticeEvent gcNoticeEvent;
				gcNoticeEvent.setCode( NOTICE_EVENT_CROWN_PRICE );
				gcNoticeEvent.setParameter( g_pVariableManager->getVariable(vt) );

				g_pZoneGroupManager->broadcast( &gcNoticeEvent );
			}
		}
		else
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_WRONG_VARIABLE_NAME ) );
		}
	}

	// ÀÚ½Å¿¡°Ô¸¸ ½Ã½ºÅÛ ¸Þ½ÃÁö º¸³»±â (¼öÁ¤µÇ¾úÀ»½Ã)
	if (pGamePlayer!=NULL)
	{
		pGamePlayer->sendPacket (&gcSystemMessage);
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opzone( string msg, int i )
	throw( ProtocolException, Error )
{
	__BEGIN_TRY

	//////////////
	// Zone Info
	//////////////
/*	ZoneInfo* pZoneInfo = new ZoneInfo();
	pZoneInfo->setZoneID( 10001 );
	pZoneInfo->setZoneGroupID( 6 );
	pZoneInfo->setZoneType( "NORMAL_FIELD" );
	pZoneInfo->setZoneLevel( 0 );
	pZoneInfo->setZoneAccessMode( "PUBLIC" );
	pZoneInfo->setZoneOwnerID( "" );
	pZoneInfo->setPayPlay( "" );

	pZoneInfo->setSMPFilename( "team_hdqrs.smp" );
	pZoneInfo->setSSIFilename( "team_hdqrs.ssi" );
	pZoneInfo->setFullName( "team" );
	pZoneInfo->setShortName( "team" );

	g_pZoneInfoManager->addZoneInfo( pZoneInfo );

	/////////
	// Zone
	/////////
	Zone* pZone = new Zone( 10001 );
	Assert( pZone != NULL );

	ZoneGroup* pZoneGroup = g_pZoneGroupManager->getZoneGroup(6);
	Assert( pZoneGroup != NULL );

	pZone->setZoneGroup( pZoneGroup );
	pZoneGroup->addZone( pZone );
	pZone->init();
*/
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opguild( string msg, int i, Creature* pCreature )
	throw( ProtocolException, Error )
{
	__BEGIN_TRY

	i = i + 7;

	uint j = msg.find_first_of( ' ', i );
	string command = msg.substr( i, j - i );
	string variable = trim( msg.substr( j+1 ) );

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pCreature->getPlayer());

	if ( command == "changeGuildMaster" )
	{
		int a = variable.find_first_of( ' ', 0 );
		GuildID_t guildID = atoi( variable.substr( 0, a ).c_str() );
		string master = trim( variable.substr( a+1 ) );

		Guild* pGuild = g_pGuildManager->getGuild( guildID );
		if ( pGuild == NULL ) 
		{
			GCSystemMessage msg;
			msg.setMessage( "No such Guild" );
			pGamePlayer->sendPacket( &msg );

			return;
		}

		GuildMember* pGuildMember = pGuild->getMember( master );
		if ( pGuildMember == NULL )
		{
			GCSystemMessage msg;
			msg.setMessage( "No such Guild Member" );
			pGamePlayer->sendPacket( &msg );

			return;
		}

		if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_NORMAL
		  && pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_SUBMASTER )
		{
			GCSystemMessage msg;
			msg.setMessage( "New Guild Member must be submaster or normal member" );
			pGamePlayer->sendPacket( &msg );

			return;
		}

		Statement* pStmt = NULL;
		Result* pResult = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				pResult = pStmt->executeQuery( "SELECT Fame, BladeLevel, SwordLevel, GunLevel, HealLevel, EnchantLevel FROM Slayer WHERE Name = '%s'", master.c_str() );
				int i = 0;

				if ( !pResult->next() )
				{
					SAFE_DELETE( pStmt );
					return;
				}

				Fame_t			Fame			= pResult->getInt( ++i );
				SkillLevel_t 	BladeLevel		= pResult->getInt( ++i );
				SkillLevel_t 	SwordLevel		= pResult->getInt( ++i );
				SkillLevel_t 	GunLevel		= pResult->getInt( ++i );
				SkillLevel_t 	HealLevel		= pResult->getInt( ++i );
				SkillLevel_t 	EnchantLevel	= pResult->getInt( ++i );

				SkillDomainType_t	highestDomain;
				SkillLevel_t		maxLevel;

				if ( BladeLevel > SwordLevel )
				{
					maxLevel = BladeLevel;
					highestDomain = SKILL_DOMAIN_BLADE;
				}
				else
				{
					maxLevel = SwordLevel;
					highestDomain = SKILL_DOMAIN_SWORD;
				}
				if ( GunLevel > maxLevel )
				{
					maxLevel = GunLevel;
					highestDomain = SKILL_DOMAIN_GUN;
				}
				if ( HealLevel > maxLevel )
				{
					maxLevel = HealLevel;
					highestDomain = SKILL_DOMAIN_HEAL;
				}
				if ( EnchantLevel > maxLevel )
				{
					maxLevel = EnchantLevel;
					highestDomain = SKILL_DOMAIN_ENCHANT;
				}

				if ( maxLevel < REQUIRE_SLAYER_MASTER_SKILL_DOMAIN_LEVEL )
				{
					SAFE_DELETE( pStmt );

					GCSystemMessage msg;
					msg.setMessage( "Master Level Limit Error" );
					pGamePlayer->sendPacket( &msg );

					return;
				}

				if ( Fame < REQUIRE_SLAYER_MASTER_FAME[highestDomain] )
				{
					SAFE_DELETE( pStmt );

					GCSystemMessage msg;
					msg.setMessage( "Master Fame Limit Error" );
					pGamePlayer->sendPacket( &msg );

					return;
				}
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE ) 
			{
				pResult = pStmt->executeQuery( "SELECT Level FROM Vampire WHERE Name = '%s'", master.c_str() );

				if ( !pResult->next() )
				{
					SAFE_DELETE( pStmt );
					return;
				}
				
				Level_t Level = pResult->getInt( 1 );
				if ( Level < REQUIRE_VAMPIRE_MASTER_LEVEL )
				{
					SAFE_DELETE( pStmt );

					GCSystemMessage msg;
					msg.setMessage( "Master Level Limit Error" );
					pGamePlayer->sendPacket( &msg );

					return;
				}
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS ) 
			{
				pResult = pStmt->executeQuery( "SELECT Level FROM Ousters WHERE Name = '%s'", master.c_str() );

				if ( !pResult->next() )
				{
					SAFE_DELETE( pStmt );
					return;
				}

				Level_t Level = pResult->getInt( 1 );
				if ( Level < REQUIRE_OUSTERS_MASTER_LEVEL )
				{
					SAFE_DELETE( pStmt );

					GCSystemMessage msg;
					msg.setMessage( "Master Level Limit Error" );
					pGamePlayer->sendPacket( &msg );

					return;
				}
			}
			else
			{
				SAFE_DELETE( pStmt );
				return;
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)

		GSModifyGuildMember gsPacket;
		gsPacket.setGuildID( pGuild->getID() );
		gsPacket.setName( master );
		gsPacket.setGuildMemberRank( GuildMember::GUILDMEMBER_RANK_MASTER );
		gsPacket.setSender( pCreature->getName() );

		g_pSharedServerManager->sendPacket( &gsPacket );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opsave(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	GCSystemMessage gcSystemMessage;

	gcSystemMessage.setMessage( g_pStringPool->getString( STRID_SAVE_YOUR_DATA ) );

	Statement* pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

	Result* pResult = pStmt->executeQuery("SELECT MAX(ZoneGroupID) FROM ZoneGroupInfo");

	pResult->next();

	BYTE GroupCount = pResult->getInt(1) + 1;

	for (int i = 1; i < GroupCount; i++) 
	{
		ZoneGroup* pZoneGroup = NULL;

		try 
		{
			pZoneGroup = g_pZoneGroupManager->getZoneGroup(i);
		} 
		catch (NoSuchElementException&) 
		{
			SAFE_DELETE(pStmt);
			throw Error("Critical Error : ZoneInfoManager¸ÃÐÐ»á²»´æÔÚ.");
		}

		ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();

		pZonePlayerManager->broadcastPacket(&gcSystemMessage);
		pZonePlayerManager->save();
	}

	SAFE_DELETE(pStmt);

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opwall(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);

	GCSystemMessage gcSystemMessage;

	gcSystemMessage.setType( SYSTEM_MESSAGE_OPERATOR );
	gcSystemMessage.setMessage(msg.substr(j+1, msg.size()-j-1).c_str());

	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();
		filelog("change.txt", "[Wall]%s, %s", pCreature->getName().c_str(), gcSystemMessage.getMessage().c_str());
	}

	g_pZoneGroupManager->broadcast( &gcSystemMessage );

	/*
	Statement* pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

	Result* pResult = pStmt->executeQuery("SELECT MAX(ZoneGroupID) FROM ZoneGroupInfo");

	pResult->next();

	BYTE GroupCount = pResult->getInt(1) + 1;

	for (int i = 1; i < GroupCount; i++) {

		ZoneGroup* pZoneGroup;

		try 
		{
			pZoneGroup = g_pZoneGroupManager->getZoneGroup(i);
		} 
		catch (NoSuchElementException&) 
		{
			SAFE_DELETE(pStmt);
			throw Error("Critical Error : ZoneInfoManager¿¡ ÇØ´ç Á¸±×·ìÀÌ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
		}

		ZonePlayerManager* pZonePlayerManager = pZoneGroup->getZonePlayerManager();

		pZonePlayerManager->broadcastPacket_NOBLOCKED(&gcSystemMessage);

	}

	SAFE_DELETE(pStmt);
	*/

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opshutdown(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	// ¾Æ¹« zone¿¡³ª ºÙÀÌ¸é µÇ´Âµ¥..
	// multithread¶§¸Þ.. lockÀß °É°í effect¸¦ ºÙ¿©¾ß ÇÑ´Ù.
	uint j = msg.find_first_of(' ' , i+1);
	Turn_t dTime = atoi(msg.substr(j+1, msg.size()-j-1).c_str());

	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();
		filelog("change.txt", "[ShutDown]%s, %d", pCreature->getName().c_str(), (int)dTime);
	}

	EffectShutDown* pEffectShutDown = new EffectShutDown();
	pEffectShutDown->setNextTime(100);
	pEffectShutDown->setDelay(100);
	pEffectShutDown->setDeadline(dTime);


	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();

		Zone* pZone = pCreature->getZone();
		(pZone->getObjectRegistry()).registerObject(pEffectShutDown);

		pZone->addEffect(pEffectShutDown);
	}
	else
	{
		int ZoneNum = 1003;

		ZoneInfo* pZoneInfo = NULL;
		try {
			pZoneInfo = g_pZoneInfoManager->getZoneInfo(ZoneNum);
		} catch (NoSuchElementException&) {
			throw Error("ÏëÒª½øÐÐshutdown,µ«Ã»ÓÐzoneID.");
		}

		ZoneGroup* pZoneGroup = NULL;

		try {
			pZoneGroup = g_pZoneGroupManager->getZoneGroup(pZoneInfo->getZoneGroupID());
		} catch (NoSuchElementException&) {
			throw Error("ÏëÒª½øÐÐshutdown,µ«zoneGroupÈ±ÉÙÄÚÈÝ.");
		}

		Zone* pZone = pZoneGroup->getZone(ZoneNum);

		(pZone->getObjectRegistry()).registerObject(pEffectShutDown);

		pZone->addEffect_LOCKING(pEffectShutDown);
	}

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opkick(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	Creature* pTargetCreature = NULL;

	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	pTargetCreature = g_pPCFinder->getCreature_LOCKED(Name);
	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	Player* pTargetPlayer = pTargetCreature->getPlayer();
	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
	pTargetGamePlayer->setPenaltyFlag(PENALTY_TYPE_KICKED);
	pTargetGamePlayer->setItemRatioBonusPoint(1);

	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();
		filelog("change.txt", "[Kick]%s --> %s", pCreature->getName().c_str(), Name.c_str());
	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opmute(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint time = 0;
	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);
	string Name;
	if ( k < msg.size() )
	{
		Name = msg.substr(j+1, k-j-1).c_str();
		time = (uint)atoi(msg.substr(k+1,msg.size()-k-1).c_str());
	}
	else
	{
		Name = msg.substr(j+1, msg.size()-j-1).c_str();
	}

	Creature* pTargetCreature = NULL;
	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	pTargetCreature = g_pPCFinder->getCreature_LOCKED(Name);
	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	Player* pTargetPlayer = pTargetCreature->getPlayer();
	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);

	if ( time == 0 )
	{
		pTargetGamePlayer->setPenaltyFlag(PENALTY_TYPE_MUTE);
	}
	else
	{
		Effect* pEffect = NULL;
		if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_MUTE ) )
		{
			pEffect = pTargetCreature->findEffect( Effect::EFFECT_CLASS_MUTE );

			pEffect->setDeadline(time*600);
			pEffect->save(pTargetCreature->getName());
		}
		else
		{
			pEffect = new EffectMute(pTargetCreature);
			pEffect->setDeadline(time*600);
			pEffect->create(pTargetCreature->getName());
			pTargetCreature->addEffect(pEffect);
			pTargetCreature->setFlag( pEffect->getEffectClass() );
		}

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
		gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
		gcAddEffect.setDuration( time*600 );

		pTargetGamePlayer->sendPacket( &gcAddEffect );

	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opdenychat(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint level = 0;
	uint time = 0;
	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);
	string Name;
	if ( k < msg.size() )
	{
		level = (uint)atoi(msg.substr(j+1,k-j-1).c_str());
		Name = msg.substr(k+1,msg.size()-k-1).c_str();
	}
	else
	{
		return;
	}

	Creature* pTargetCreature = NULL;

	if ( level == 1 )
	{
		// level1 = 1½Ã°£
		time = 1 * 60;
	}
	else if ( level == 2 )
	{
		// level2 = 6½Ã°£
		time = 6 * 60;
	}
	else if ( level == 3 )
	{
		// level3 = 12½Ã°£
		time = 12 * 60;
	}
	else if ( level == 4 )
	{
		// level4 = 24½Ã°£
		time = 24 * 60;
	}
	else if ( level == 5 )
	{
		// level5 = 168½Ã°£
		time = 168 * 60;
	}

	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	pTargetCreature = g_pPCFinder->getCreature_LOCKED(Name);
	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	Player* pTargetPlayer = pTargetCreature->getPlayer();
	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);

	if ( time == 0 )
	{
		pTargetGamePlayer->setPenaltyFlag(PENALTY_TYPE_MUTE);
	}
	else
	{
		Effect* pEffect = NULL;
		if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_MUTE ) )
		{
			pEffect = pTargetCreature->findEffect( Effect::EFFECT_CLASS_MUTE );

			pEffect->setDeadline(time*600);
			pEffect->save(pTargetCreature->getName());
		}
		else
		{
			pEffect = new EffectMute(pTargetCreature);
			pEffect->setDeadline(time*600);
			pEffect->create(pTargetCreature->getName());
			pTargetCreature->addEffect(pEffect);
			pTargetCreature->setFlag( pEffect->getEffectClass() );
		}

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
		gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
		gcAddEffect.setDuration( time*600 );

		pTargetGamePlayer->sendPacket( &gcAddEffect );

	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opfreezing(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	Creature* pTargetCreature = NULL;

	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	pTargetCreature = g_pPCFinder->getCreature_LOCKED(Name);
	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	Player* pTargetPlayer = pTargetCreature->getPlayer();
	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetPlayer);
	pTargetGamePlayer->setPenaltyFlag(PENALTY_TYPE_FREEZING);

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opdeny(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	Statement* pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
	Result* pResult = pStmt->executeQuery("SELECT PlayerID FROM Slayer where Name='%s'", Name.c_str());

	string PlayerID;

	if (pResult->next()) 
	{
		string PlayerID = pResult->getString(1);

		Statement* pStmt2 = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();
		pStmt2->executeQuery("UPDATE Player set Access='DENY' where PlayerID ='%s'", PlayerID.c_str());
		SAFE_DELETE(pStmt2);
	}

	SAFE_DELETE(pStmt);

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opinfo(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;
	
	uint j = msg.find_first_of(' ' , i+1);
	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	Creature* pTargetCreature = NULL;
	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	pTargetCreature = g_pPCFinder->getCreature_LOCKED(Name);
	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	StringStream msg;

	msg << "Name : " << Name
		<< " Host : " << pTargetCreature->getPlayer()->getSocket()->getHost();

	if (pTargetCreature->isSlayer()) {

		Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);

		msg << " STR : " << (int)pSlayer->getSTR() << " / " << pSlayer->getSTR(ATTR_MAX)
			<< " DEX : " << (int)pSlayer->getDEX() << " / " << pSlayer->getDEX(ATTR_MAX)
			<< " INT : " << (int)pSlayer->getINT() << " / " << pSlayer->getINT(ATTR_MAX)
			<< " DAM : " << (int)pSlayer->getDamage() << " / " << pSlayer->getDamage(ATTR_MAX) << " / " << pSlayer->getDamage(ATTR_BASIC)
			<< " Defense  : " << (int)pSlayer->getDefense()
			<< " TOHIT : " << (int)pSlayer->getToHit()
			<< " HP : " << (int)pSlayer->getHP() << " / " << pSlayer->getHP(ATTR_MAX)
			<< " MP : " << (int)pSlayer->getMP() << " / " << pSlayer->getMP(ATTR_MAX)
			<< " Fame : " << (int)pSlayer->getFame()
			<< " Gold : " << (int)pSlayer->getGold()
			<< " StashGold : " << (int)pSlayer->getStashGold();

	} else if (pTargetCreature->isVampire()) {

		Vampire* pVampire= dynamic_cast<Vampire*>(pTargetCreature);

		msg << " STR : " << pVampire->getSTR() << " / " << pVampire->getSTR(ATTR_MAX)
			<< " DEX : " << pVampire->getDEX() << " / " << pVampire->getDEX(ATTR_MAX)
			<< " INT : " << pVampire->getINT() << " / " << pVampire->getINT(ATTR_MAX)
			<< " Defense  : " << (int)pVampire->getDefense()
			<< " TOHIT : " << (int)pVampire->getToHit()
			<< " HP : " << (int)pVampire->getHP() << " / " << pVampire->getHP(ATTR_MAX)
			<< " Fame : " << (int)pVampire->getFame()
			<< " Gold : " << (int)pVampire->getGold()
			<< " StashGold : " << (int)pVampire->getStashGold();

	} else if (pTargetCreature->isOusters()) {

		Ousters* pOusters= dynamic_cast<Ousters*>(pTargetCreature);

		msg << " STR : " << pOusters->getSTR() << " / " << pOusters->getSTR(ATTR_MAX)
			<< " DEX : " << pOusters->getDEX() << " / " << pOusters->getDEX(ATTR_MAX)
			<< " INT : " << pOusters->getINT() << " / " << pOusters->getINT(ATTR_MAX)
			<< " Defense  : " << (int)pOusters->getDefense()
			<< " TOHIT : " << (int)pOusters->getToHit()
			<< " HP : " << (int)pOusters->getHP() << " / " << pOusters->getHP(ATTR_MAX)
			<< " Fame : " << (int)pOusters->getFame()
			<< " Gold : " << (int)pOusters->getGold()
			<< " StashGold : " << (int)pOusters->getStashGold();

	}

	GCSystemMessage gcSystemMessage;

	gcSystemMessage.setMessage(msg.toString());

	pGamePlayer->sendPacket (&gcSystemMessage);

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opfind(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;
	uint j = msg.find_first_of(' ' , i+1);
	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	Statement* pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
	Result* pResult = pStmt->executeQuery("SELECT ServerID FROM UserIPInfo where Name='%s'", Name.c_str() );

	static WorldID_t WorldID = g_pConfig->getPropertyInt("WorldID");

	if( pResult->getRowCount() != 0 ) {

		pResult->next();
		
		ServerID_t ServerID = pResult->getInt(1);

		string ServerName = g_pGameServerGroupInfoManager->getGameServerGroupInfo( ServerID, WorldID )->getGroupName();

        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_PLAYER_IN_GAMESERVER ),
                        Name.c_str(), ServerName.c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg);
		pGamePlayer->sendPacket (&gcSystemMessage);

	} else {
//		StringStream msg;
//		msg <<  Name << " ´ÔÀº ºñÁ¢¼Ó ÁßÀÔ´Ï´Ù.";

        char msg[100];
        sprintf( msg, g_pStringPool->c_str( STRID_PLAYER_NOT_IN_GAMESERVER ),
                        Name.c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(msg);
		pGamePlayer->sendPacket (&gcSystemMessage);
	}


	SAFE_DELETE(pStmt);

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ¿©±â ÀÌ¸§ ³²±â°í.. ¿­½ÉÈ÷~ ÄÉÄÉ.. 
// GCSystemMessage°¡ 256ÀÚ°¡ ÇÑ°è´Ï±î Á¶½ÉÇÏ±æ. by sigi. 2003.3.22
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opcredit(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

	if (pGamePlayer==NULL) return;

	static hash_map<string, string> Credits;

	// ÇÏµåÄÚµùÀ¸·Î À¯ÁöÇÏ±æ... ¤·¤¾¤¾  by sigi.
	if (Credits.empty())
	{
		Credits["ÅÖÐ¡Éß"] = "¿Í»§¶Ë,·þÎñÆ÷(2005~)";
		//Credits["À±Ã¢ÇÊ"] = "¼­¹öÄÚ¾î(1999.9~2000.9), ±âÈ¹(2001.3~2002.3)";
		//Credits["±è°Ç¿ì"] = "¼­¹ö, ±âÈ¹(1999.9~2002.3)";
		//Credits["±èÁøÅÂ"] = "Å¬¶óÀÌ¾ðÆ®UI, Åø(1999.9~2001.1)";
		//Credits["ÀÓÃá±Ù"] = "¼­¹ö, DB(1999.9~2000.?)";
		//Credits["±è¼º¹Î"] = "¼­¹ö, DB(2000.10~2002.3)";
		//Credits["À±¿µ½Ä"] = "Å¬¶óÀÌ¾ðÆ®¸ÞÀÎ(1999.9~2002.3), ¼­¹ö(2002.4~2003.3).¾Æ Ã»ÃáÀÌ¿©~T_T; unuis@hanmail.net";
		//Credits["Áö¼º¿í"] = "Å¬¶óÀÌ¾ðÆ®UI, Åø(2001.2~2002.3), Å¬¶óÀÌ¾ðÆ®¸ÞÀÎ(2002.3~2003.3)";
		//Credits["ÀåÈ«Ã¢"] = "¼­¹ö, DB(2002.1~2002.12)";
		//Credits["¹èÀçÇü"] = "¼­¹ö(2002.4~)";
		//Credits["¼ÕÈñ½Â"] = "Å¬¶óÀÌ¾ðÆ®UI, Åø(2002.6~2003.1), Å¬¶óÀÌ¾ðÆ®¸ÞÀÎ(2003.1~)";
		//Credits["ÀÌÈñ¿ø"] = "DB, ¿î¿µÆÀÁö¿ø(2002.6~)";
		//Credits["¾ç½Â¸í"] = "¼­¹ö(2002.11~)";
		//Credits["È«»ó¹Î"] = "¼­¹ö(2002.12~)";
	}

	uint j = msg.find_first_of(' ' , i+1);
	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	hash_map<string, string>::const_iterator itr = Credits.find( Name );

	if (itr!=Credits.end())
	{
		StringStream msg;
		msg << "[" << itr->first << "] " << itr->second;

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg.toString() );
		pGamePlayer->sendPacket( &gcSystemMessage );
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opuser(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	Statement* pStmt = g_pDatabaseManager->getDistConnection( "PLAYER_DB" )->createStatement();
	//Statement* pStmt = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();
	Result* pResult = pStmt->executeQuery("SELECT Count(*) FROM Player where LogOn='GAME' OR LogOn='LOGON'");

	pResult->next();

	int GroupCount = pResult->getInt(1);

//	StringStream msg;
//	msg << "ÇöÀç µ¿½Ã Á¢¼ÓÀÚ : " << GroupCount << "¸í";

    char msg[100];
    sprintf( msg, g_pStringPool->c_str( STRID_CURRENT_NUMBER_OF_PLAYER ),
                    GroupCount );

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(msg);
	pGamePlayer->sendPacket (&gcSystemMessage);

	SAFE_DELETE(pStmt);

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::optrace(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	Creature* pCreature = pGamePlayer->getCreature();

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);

	bool isNPCTrace = false;

	if (msg.size() > k && !strncasecmp(msg.substr(j+1, k-j-1).c_str(),"NPC",3))
		isNPCTrace = true;

	string Name;

	if (isNPCTrace)
	{
		Name = msg.substr(k+1, msg.size()-k-1);
	}
	else
	{
		Name = msg.substr(j+1, msg.size()-j-1);
	}

	Creature* pTargetCreature = NULL;

	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	__ENTER_CRITICAL_SECTION((*g_pPCFinder))
		
	if (isNPCTrace)
	{
		NPC *pNPC = g_pPCFinder->getNPC_LOCKED(Name);
		pTargetCreature = dynamic_cast<Creature*>(pNPC);
	}
	else 
	{
		pTargetCreature = g_pPCFinder->getCreature_LOCKED(Name);
	}

	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	ZoneID_t ZoneNum = pTargetCreature->getZoneID();
	Coord_t ZoneX = pTargetCreature->getX();
	Coord_t ZoneY = pTargetCreature->getY();

	Assert((int)ZoneX < 256);
	Assert((int)ZoneY < 256);
	Assert(pCreature->isPC());

	transportCreature(pCreature, ZoneNum, ZoneX, ZoneY, false);

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::oppay(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	char str[80];

	if (pGamePlayer->isBillingPlayAvaiable())
	{
		strcpy(str, "[Billing] ÒÑµÇÂ½»áÔ±ÏµÍ³£¬ÕýÔÚ½øÐÐÓÎÏ·ÖÐ....");
	}
	else if (pGamePlayer->isPayPlaying())
	{
		Timeval currentTime;
		getCurrentTime(currentTime);
		Timeval payTime = pGamePlayer->getPayPlayTime(currentTime);

		if (pGamePlayer->getPayPlayType()==PAY_PLAY_TYPE_PERSON)
		{
			strcpy(str, "[Metrotech][¸öÈË] ");
		}
		else
		{
			strcpy(str, "[Metrotech][Íø°É] ");
		}

		if (pGamePlayer->getPayType()==PAY_TYPE_FREE)
		{	
			strcat(str, "Ãâ·ÑÕËºÅ.");
		}
		else if (pGamePlayer->getPayType()==PAY_TYPE_PERIOD)
		{	
			sprintf(str, "¿ÉÒÔÊ¹ÓÃµ½%s%sÎªÖ¹.", str, pGamePlayer->getPayPlayAvailableDateTime().toString().c_str());
		}
		else
		{
			sprintf(str, "%sÊ£ÓàÊ±¼ä : %d / %d ·Ö", str, (int)(payTime.tv_sec/60), (int)pGamePlayer->getPayPlayAvailableHours());
		}
	}
	else
	{	
		strcpy(str, "[Metrotech] Ãâ·Ñ½øÐÐÓÎÏ·.");
	}

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage(str);
	pGamePlayer->sendPacket (&gcSystemMessage);

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opfun(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);
	uint l = msg.find_first_of(' ' , k+1);

	string      FunType		= trim(msg.substr(j+1, k-j-1));
	int 		value1    	= atoi(msg.substr(k+1, l-k-1).c_str());
	int 		value2    	= atoi(msg.substr(l+1, msg.size()-l-1).c_str());


	if (FunType=="mine")
	{
		int ItemType = value1;
		int ItemNum  = value2;

		ItemType = max(0, ItemType);
		ItemType = min((int)g_pMineInfoManager->getInfoCount()-1, ItemType);

		ItemNum = max(1, ItemNum);
		ItemNum = min(36, ItemNum);

		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature!=NULL);

		/*
		if (!pCreature->isSlayer())
		{
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage("slayer ¾Æ´Ï¸é ¾ÈµÈ´Ù~");
			pGamePlayer->sendPacket (&gcSystemMessage);
			return;
		}
		*/

		Zone* pZone = pCreature->getZone();
		Assert(pZone!=NULL);

		ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(Item::ITEM_CLASS_MINE, ItemType);
		if (pItemInfo==NULL) return;

		Damage_t MinDamage = pItemInfo->getMinDamage();
		Damage_t MaxDamage = pItemInfo->getMaxDamage();

		for (int i=0; i<ItemNum; i++)
		{
			Mine * pInstallMine = new Mine();
			Assert( pInstallMine != NULL );

			ObjectRegistry& OR = pZone->getObjectRegistry();
			OR.registerObject(pInstallMine);

			int SkillLevel = 100;
			Damage_t RealDamage = MinDamage + ( max ( 0, ( (int)MaxDamage * (int)SkillLevel / 100 ) - MinDamage ) );

			pInstallMine->setItemType( ItemType );
			pInstallMine->setDir( pCreature->getDir() );
			pInstallMine->setDamage( RealDamage );
			pInstallMine->setInstallerName( pCreature->getName() );
			pInstallMine->setInstallerPartyID( pCreature->getPartyID() );
			pInstallMine->setFlag( Effect::EFFECT_CLASS_INSTALL );

			TPOINT pt = pZone->addItem(pInstallMine, pCreature->getX(), pCreature->getY(), true, 6000);

			addInstalledMine( pZone, pInstallMine, pt.x, pt.y);
		}

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage("ÉèÖÃµØÀ×.");
		pGamePlayer->sendPacket (&gcSystemMessage);
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage("µ½µ×ÔÚ×öÊ²Ã´~!?²»ÄÜºÃºÃ×öÂð!");
		pGamePlayer->sendPacket (&gcSystemMessage);
	}

	__END_DEBUG_EX __END_CATCH
}



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opwarp(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	if (pGamePlayer==NULL)	 return;

	Creature* pCreature = pGamePlayer->getCreature();

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);
	uint l = msg.find_first_of(' ' , k+1);

	string      ZoneName = trim(msg.substr(j+1, k-j-1));
	ZoneCoord_t ZoneX    = atoi(msg.substr(k+1, l-k-1).c_str());
	ZoneCoord_t ZoneY    = atoi(msg.substr(l+1, msg.size()-l-1).c_str());

	int ZoneID = 0;

	// ZoneNameÀº Á¸ÀÇ ÀÌ¸§ÀÏ ¼öµµ ÀÖ°í, Á¸ÀÇ IDÀÏ ¼öµµ ÀÖ´Ù.
	// ZoneInfo°¡ NULLÀÌ ¾Æ´Ï¶ó´Â ¸»Àº ÀÌ ¹®ÀÚ¿­ÀÌ Á¸ÀÇ ÀÌ¸§ÀÌ¶ó´Â ¶æÀÌ°í,
	// Zoneinfo°¡ NULLÀÌ¶ó´Â ¸»Àº ÀÌ ¹®ÀÚ¿­ÀÌ Á¸ÀÇ IDÀÌ¶ó´Â ¸»ÀÌ´Ù.
	// (¹°·Ð »ç¿ëÀÚÀÇ ÀÔ·Â ½Ç¼öµµ ÀÖ°ÚÁö¸¸, ÀÌ´Â ¹«½ÃÇÑ´Ù.)
	ZoneInfo* pZoneInfo = g_pZoneInfoManager->getZoneInfoByName(ZoneName);
	if (pZoneInfo != NULL)
	{
		ZoneID = pZoneInfo->getZoneID();
	}
	else
	{
		ZoneID = atoi(ZoneName.c_str());
	}

	if (pCreature->isPC() && ZoneX < 256 && ZoneY < 256)
	{
		// ½ÃÇè»ï¾Æ¼­ ½ÇÁ¦·Î ±×·± Á¸ÀÌ ÀÖ´ÂÁö¸¦ Ã¼Å©ÇÑ´Ù.
		// ¾ø´Ù¸é ¸®ÅÏÇÑ´Ù.
		try
		{
			Zone* pZone = getZoneByZoneID(ZoneID);
			// evade warning
			pZone = NULL;
		}
		catch (Error)
		{
			return;
		}

		// ±×·± Á¸ÀÌ ÀÖ´Ù´Â °ÍÀÌ È®ÀÎµÇ¾ú´Ù¸é ÀÌµ¿½ÃÅ²´Ù. 
		try
		{
			transportCreature(pCreature, ZoneID, ZoneX, ZoneY, false);
		}
		catch (Throwable & t)
		{
			cerr << t.toString() << endl;
		}
	}

#endif

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opcreate(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	Creature* pCreature = pGamePlayer->getCreature();

	uint j = msg.find_first_of(' ' , i+1);	// class
	uint k = msg.find_first_of(' ' , j+1);	// type
	uint l = msg.find_first_of(' ' , k+1);	// option
	uint lNum = msg.find_first_of('[' , k+1);	// num
	uint rNum = msg.find_first_of(']' , k+1);
	uint lTime = msg.find_first_of('(' , k+1);	// num
	uint rTime = msg.find_first_of(')' , k+1);
	uint lGrade = msg.find_first_of('{' , k+1);	// num
	uint rGrade = msg.find_first_of('}' , k+1);

	string optional;

	if (lNum < rNum)
	{
		optional = msg.substr(lNum+1 ,rNum-lNum-1).c_str();
	}

	ItemType_t ItemType   = 255;
	ItemType_t OptionType = 255;

	string ItemClassName = trim(msg.substr(j+1, k-j-1));
	Item::ItemClass ItemClass = g_pItemFactoryManager->getItemClassByName( ItemClassName );

	// ItemClass°¡ MAX¶ó¸é ÀÌ¸§À¸·Î´Â ¸ø Ã£¾Ò´Ù´Â ¸»ÀÌ´Ù. 
	// ÀÌ °æ¿ì¿¡´Â ¾ÆÀÌÅÛ Å¬·¡½º°¡ ¼ýÀÚ·Î ¹Ù·Î ¿ÀÁö´Â ¾Ê¾Ò´ÂÁö °Ë»çÇØ¾ß ÇÑ´Ù.
	if (ItemClass == Item::ITEM_CLASS_MAX)
	{
		int temp = atoi(ItemClassName.c_str());
		if (temp < 0 || temp >= Item::ITEM_CLASS_MAX)
		{
			return;
		}
		else
		{
			ItemClass = (Item::ItemClass)(temp);
		}
	}

	if (ItemClass == Item::ITEM_CLASS_CORPSE
//		|| ItemClass == Item::ITEM_CLASS_KEY
		|| ItemClass == Item::ITEM_CLASS_MOTORCYCLE
		|| isRelicItem( ItemClass ) && optional != "force"
		)
	{
		// ½ÃÃ¼ ¸¸µéÁö ¸¶¶û~~ by sigi
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CANNOT_CREATE_ITEM ) );

		pGamePlayer->sendPacket( &gcSystemMessage );

		return;
	}

	ItemType   = atoi(msg.substr(k+1, l-k-1).c_str());

	list<OptionType_t> optionTypes;

	
	uint pos = l, previous = l;
	while (previous < string::npos && pos < string::npos)
	{
		pos = msg.find_first_of(' ' , previous+1);
		string optionString = trim( msg.substr(previous+1, pos-previous-1) );

		//cout << "optionString: " << optionString.c_str() << endl;

		if (optionString.size()==0)
			break;

		OptionInfo* pOptionInfo = NULL;

		//try {
			pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionString );

			if (pOptionInfo==NULL)
			{
				pOptionInfo = g_pOptionInfoManager->getOptionInfo( atoi(optionString.c_str()) );

				if (pOptionInfo==NULL)
					break;
			}
				
			/*
		} catch (NoSuchElementException&) {
			try {
				pOptionInfo = g_pOptionInfoManager->getOptionInfo( atoi(optionString.c_str()) );
			} catch (NoSuchElementException&) {
				break;
			}
		}
		*/

		if (pOptionInfo!=NULL)
		{
			OptionType = pOptionInfo->getType();

			if (OptionType!=0)
			{
				//cout << "optionType = " << (int)OptionType << endl;
				optionTypes.push_back( OptionType );
			}
		}

		previous = pos;
	}


	// Á¤»óÀûÀ¸·Î »ý¼ºÇÒ ¼ö ÀÖ´Â ¾ÆÀÌÅÛÀÌ ¾Æ´Ï¶ó¸é ¸®ÅÏÇÑ´Ù.
	if (!g_pItemInfoManager->isPossibleItem(ItemClass, ItemType, optionTypes))
	{
		//cerr << "Cannot create item" << endl;
		StringStream msg;
		msg << g_pStringPool->getString( STRID_CANNOT_CREATE_ITEM_2 )
			<< ItemClass2ShortString[ItemClass]
			<< ", " << (int)ItemType
			<< ", " << getOptionTypeToString(optionTypes);

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( msg.toString().c_str() );

		pGamePlayer->sendPacket( &gcSystemMessage );
	
		return;
	}

	//cout << "createItemOptions : " << getOptionTypeToString(optionTypes) << endl;
	// create·Î »ý¼ºÇÑ À¯´ÏÅ© ¾ÆÀÌÅÛµµ °³¼ö Á¦ÇÑÀ» ½ÃÄÑ¾ßÇÒ±î?
	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( ItemClass, ItemType );
	Assert(pItemInfo!=NULL);

	// À¯´ÏÅ© ¾ÆÀÌÅÛÀÎ °æ¿ì
	/*
	if (pItemInfo->isUnique())
	{
		if (!UniqueItemManager::isPossibleCreate( ItemClass, ItemType )) 
		{
			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage("´õ ÀÌ»ó ¸¸µé ¼ö ¾ø´Â À¯´ÏÅ© ¾ÆÀÌÅÛÀÔ´Ï´Ù.");

			pGamePlayer->sendPacket( &gcSystemMessage );

			return;
		}
	}
	*/

	Item* pItem = g_pItemFactoryManager->createItem((Item::ItemClass)ItemClass, ItemType, optionTypes);
	pItem->setCreateType( Item::CREATE_TYPE_CREATE );
	pItem->setNum(1);

	if ( ItemClass == Item::ITEM_CLASS_PET_ITEM )
	{
		PetInfo* pPetInfo = new PetInfo;
		pPetInfo->setPetType(ItemType);
		pPetInfo->setPetCreatureType( 432 );
		pPetInfo->setPetLevel(1);
		pPetInfo->setPetExp(0);
		pPetInfo->setPetHP(1000);
		pPetInfo->setPetAttr(0xff);
		pPetInfo->setPetOption(0);
		pPetInfo->setFoodType(0);
		pPetInfo->setFeedTime( VSDateTime::currentDateTime() );

		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
		if ( pPetItem != NULL )
		{
			pPetItem->setPetInfo( pPetInfo );
			pPetInfo->setPetItem( pPetItem );
		}
		else 
		{
			cout << "-_-;;;;" << endl;
		}
	}

	//cout << "createItemOptions : " << getOptionTypeToString(pItem->getOptionTypeList()) << endl;

	if (isStackable(pItem->getItemClass())
		&& lNum < rNum)
	{
		int itemNum = atoi(msg.substr(lNum+1 ,rNum-lNum-1).c_str());
	
		itemNum = max(1, min(itemNum, ItemMaxStack[pItem->getItemClass()]));

		pItem->setNum(itemNum);
	}

	Assert(pItem != NULL);

	Zone* pZone = pCreature->getZone();

	ObjectRegistry & objectregistery = pZone->getObjectRegistry();
	objectregistery.registerObject(pItem);

	GCCreateItem gcCreateItem;

	if (pCreature->isPC()) 
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		Inventory* pInventory = pPC->getInventory();

		Assert(pInventory != NULL);

		TPOINT p;

		if (pInventory->getEmptySlot(pItem, p)) 
		{
			pInventory->addItem(p.x, p.y, pItem);
			if ( lGrade < rGrade )
			{
				int grade = atoi(msg.substr(lGrade+1, rGrade-lGrade-1).c_str());
				pItem->setGrade(grade);
			}

			pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
			pItem->whenPCTake( pPC );

			if ( lTime < rTime )
			{
				int time = atoi(msg.substr(lTime+1, rTime-lTime-1).c_str());
				if ( time > 0 )
				{
					pPC->addTimeLimitItem( pItem, time );
					pPC->sendTimeLimitItemInfo();
				}
			}
			else 
			{
				pPC->addTimeLimitItem( pItem, 2592000 );
				pPC->sendTimeLimitItemInfo();
			}

			makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );
			pGamePlayer->sendPacket(&gcCreateItem);
		} 
		else 
		{
			//cerr << "¾ÆÀÌÅÛ Ã¢Á¶¿¡ ½ÇÆÐÇÏ¿´½À´Ï´Ù" << endl;
			SAFE_DELETE(pItem);
		}
	} 
/*	else if ( pCreature->isVampire() )
	{
		Vampire* pVampire= dynamic_cast<Vampire*>(pCreature);

		Inventory* pInventory = pVampire->getInventory();

		Assert(pInventory != NULL);

		TPOINT p;

		if (pInventory->getEmptySlot(pItem, p)) 
		{
			pInventory->addItem(p.x, p.y, pItem);

			makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

			pGamePlayer->sendPacket(&gcCreateItem);

			pItem->create(pVampire->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
		} 
		else 
		{
			//cout << "¾ÆÀÌÅÛ Ã¢Á¶¿¡ ½ÇÆÐÇÏ¿´½À´Ï´Ù" << endl;
			SAFE_DELETE(pItem);
		}
	}
	else if ( pCreature->isOusters() )
	{
		Ousters* pOusters= dynamic_cast<Ousters*>(pCreature);

		Inventory* pInventory = pOusters->getInventory();

		Assert(pInventory != NULL);

		TPOINT p;

		if (pInventory->getEmptySlot(pItem, p)) 
		{
			pInventory->addItem(p.x, p.y, pItem);

			makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

			pGamePlayer->sendPacket(&gcCreateItem);

			pItem->create(pOusters->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
		} 
		else 
		{
			//cout << "¾ÆÀÌÅÛ Ã¢Á¶¿¡ ½ÇÆÐÇÏ¿´½À´Ï´Ù" << endl;
			SAFE_DELETE(pItem);
		}
	}*/

	if (pItem != NULL)
	{
		if (isRelicItem( pItem ))
		{
			addRelicEffect( pCreature, pItem );
		}

		// À¯´ÏÅ© ¾ÆÀÌÅÛÀÎ °æ¿ì °³¼ö Ã¼Å©ÇØÁØ´Ù.
		if (pItemInfo->isUnique())
		{
			pItem->setUnique();
			//UniqueItemManager::createItem( ItemClass, ItemType );
			filelog("uniqueItem.txt", "[OpCreate] %s %s", pCreature->getName().c_str(), pItem->toString().c_str());
		}


		// ·Î±×¸¦ ³²±ä´Ù.
		Statement* pStmt = NULL;
		BEGIN_DB
		{
			StringStream sql;
			sql << "INSERT INTO OpCreate (OpName, DateTime, ItemDesc) VALUES ("
				<< "'" << pCreature->getName() << "',"
				<< "'" << VSDateTime::currentDateTime().toString() << "',"
				<< "'" << pItem->toString() << "'"
				<< ")";

			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pStmt->executeQuery(sql.toString());
			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt);

		if ( pItem != NULL && pItem->isTraceItem() )
		{
			remainTraceLog( pItem, "GOD", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_COMMAND );
		}
	}

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opgrant(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	Creature* pCreature = pGamePlayer->getCreature();

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);

	BYTE Competence = atoi(msg.substr(j+1, k-j-1).c_str());
	
	Zone* pZone = pCreature->getZone();

	string Name = msg.substr(k+1, msg.size()-k-1).c_str();

	Creature* pTargetCreature = NULL;

	//try
	//{
	pTargetCreature = pZone->getCreature(Name);

	// NoSuchÁ¦°Å. by sigi. 2002.5.2
	if (pTargetCreature!=NULL)
	{
		if (pTargetCreature->isSlayer()) 
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
			pSlayer->setCompetence(Competence);
			//cout << "set new Competence : " << (int)pSlayer->getCompetence() << endl;
		} 
		else if (pTargetCreature->isVampire()) 
		{
			Vampire* pVampire= dynamic_cast<Vampire*>(pTargetCreature);
			pVampire->setCompetence(Competence);
			//cout << "set new Competence : " << (int)pVampire->getCompetence() << endl;
		}
		else if (pTargetCreature->isOusters()) 
		{
			Ousters* pOusters= dynamic_cast<Ousters*>(pTargetCreature);
			pOusters->setCompetence(Competence);
			//cout << "set new Competence : " << (int)pOusters->getCompetence() << endl;
		}
	}
	//}
	//catch (NoSuchElementException& nsee)
	//{
		//cout << nsee.toString() << endl;
	//	pTargetCreature = NULL;
	//}

	//cout << "Creature Name : " << Name << endl;

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::oprecall(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	Creature* pCreature = pGamePlayer->getCreature();

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	if ( pPC->isPLAYER() )
	{
		if ( g_pGuildManager->isGuildMaster( pPC->getGuildID(), pPC ) )
		{
			if ( !SiegeManager::Instance().isSiegeZone( pPC->getZoneID() ) )
			{
				return;
			}
		}
		else
		{
			return;
		}
	}


	//Zone* pCallZone = pCreature->getZone();

	/*
	uint j = msg.find_first_of(' ' , i+1);

	string Name = msg.substr(j+1, msg.size()-j-1).c_str();
	*/

	Creature* pTCreature = NULL;

	uint j = msg.find_first_of(' ' , i+1);

	string Name;

	while (j < msg.size()) 
	{
		i = msg.find_first_of(' ' , j+1);

		Name = msg.substr(j+1, i - j -1).c_str();

		//cout << "Name : (" <<  Name << ")" << endl;

		// NoSuchÁ¦°Å. by sigi. 2002.5.2
		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		pTCreature = g_pPCFinder->getCreature_LOCKED(Name);

		if (pTCreature==NULL) 
		{
			g_pPCFinder->unlock();
			return;
		}
			
		//if (pTCreature != NULL) 
		{
			// ºÒÇàÈ÷µµ PCFinder¿¡¼­ Ã£¾Æ¿Â Creature´Â constÀÌ´Ù.
			Zone* pTargetZone = pTCreature->getZone();

			Assert(pTargetZone != NULL);

			Creature* pTargetCreature = NULL;
			//try 
			//{
				// NoSuchÁ¦°Å. by sigi. 2002.5.2
				pTargetCreature = pTargetZone->getCreature(pTCreature->getObjectID());
			//}
			//catch (NoSuchElementException) 
			//{
			//}

			if (pTargetCreature != NULL) 
			{
				// ÇöÀç Á×¾îÀÖ´Â ³ðÀº µ¥¸®°í ¿Ã ¼ö ¾ø´Ù.
				if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_COMA)) 
				{
					g_pPCFinder->unlock();
					return;
				}

				// ¼ÒÈ¯ÀÚÀÇ Á¸°ú ÁÂÇ¥.
				ZoneID_t ZoneNum = pCreature->getZoneID();
				Coord_t ZoneX = pCreature->getX();
				Coord_t ZoneY = pCreature->getY();

				if ( SiegeManager::Instance().isSiegeZone( pPC->getZoneID() ) )
				{
					Effect::EffectClass eClass = Effect::EFFECT_CLASS_MAX;
					if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_DEFENDER ) )
					{
						ZoneX = 172;
						ZoneY = 38;
						eClass = Effect::EFFECT_CLASS_SIEGE_DEFENDER;
					}
					else if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_REINFORCE ) )
					{
						ZoneX = 172;
						ZoneY = 38;
						eClass = Effect::EFFECT_CLASS_SIEGE_REINFORCE;
					}
					else if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_1 ) )
					{
						ZoneX = 20;
						ZoneY = 232;
						eClass = Effect::EFFECT_CLASS_SIEGE_ATTACKER_1;
					}
					else if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_2 ) )
					{
						ZoneX = 20;
						ZoneY = 232;
						eClass = Effect::EFFECT_CLASS_SIEGE_ATTACKER_2;
					}
					else if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_3 ) )
					{
						ZoneX = 20;
						ZoneY = 232;
						eClass = Effect::EFFECT_CLASS_SIEGE_ATTACKER_3;
					}
					else if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_4 ) )
					{
						ZoneX = 20;
						ZoneY = 232;
						eClass = Effect::EFFECT_CLASS_SIEGE_ATTACKER_4;
					}
					else if ( pCreature->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_5 ) )
					{
						ZoneX = 20;
						ZoneY = 232;
						eClass = Effect::EFFECT_CLASS_SIEGE_ATTACKER_5;
					}

					if ( eClass != Effect::EFFECT_CLASS_MAX && !pTargetCreature->isFlag( eClass ) )
					{
						if ( !pTargetCreature->isPC() || dynamic_cast<PlayerCreature*>(pTargetCreature)->getGuildID() != pPC->getGuildID() )
						{
							g_pPCFinder->unlock();
							return;
						}

						addSimpleCreatureEffect( pTargetCreature, eClass, 72000 );
					}
				}

				Assert((int)ZoneX < 256);
				Assert((int)ZoneY < 256);

				Assert(pTargetCreature->isPC());

				transportCreature(pTargetCreature, ZoneNum, ZoneX, ZoneY, false);
			}
		}

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

		j = i;

	}

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opmrecall(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opnotice(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	//Creature* pCreature = pGamePlayer->getCreature();

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);

	string noticemsg = msg.substr(j+1, k-j-1).c_str();

	StringStream sql;

	sql << "INSERT INTO quick1001 (content) VALUES (" << noticemsg << ")";

	Connection* pConnection = new Connection("211.117.52.124", "darkBBS2002", "elcastle", "elca005", 3306);
	Statement* pStmt = pConnection->createStatement();
	pStmt->executeQuery(sql.toString());

	SAFE_DELETE(pStmt);
	SAFE_DELETE(pConnection);
	
	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opsummon(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	if (pGamePlayer==NULL)	 return;

	Creature* pCreature = pGamePlayer->getCreature();

	uint j = msg.find_first_of(' ' , i+1); 
	uint k = msg.find_first_of(' ' , j+1); // j~k : name
	uint l = msg.find_first_of(' ' , k+1); // k~l : num
	uint m = msg.find_first_of(' ' , l+1); // l~m : mad

	uint o = msg.find_first_of('{' , j);
	uint p = msg.find_first_of('}' , j+1);

#ifdef __UNDERWORLD__

	uint e = msg.find_first_of('[', i+1);
	uint v = msg.find_first_of(']', i+1); // e~v : event ¿©ºÎ

	string EventFlag = msg.substr(e+1,v-e-1);
	
	if (strstr(EventFlag.c_str(), "EventAll") != NULL )
	{
		//	ÀÌº¥Æ®¿ë ÄÚµå (¸ó½ºÅÍÅ¸ÀÔµµ ±×³É ÇÏµåÄÚµù -_-;)
		Zone* pZone = pCreature->getZone();
		Coord_t ZoneX = pCreature->getX();
		Coord_t ZoneY = pCreature->getY();

		TPOINT pt;

		pt = findSuitablePosition(pZone, ZoneX, ZoneY, Creature::MOVE_MODE_WALKING);

		if (pt.x == -1 || (pZone->getZoneLevel(pt.x, pt.y) & SAFE_ZONE))
			return;

		Monster *pMonster = NULL;
		Monster *pMonster1 = NULL;
		Monster *pMonster2 = NULL;

		try 
		{
			pMonster = new Monster(599);
			pMonster1 = new Monster(599);
			pMonster2 = new Monster(599);
			
			if (pMonster == NULL) return;

			pMonster->setName("µØÓü");

			pMonster->setTreasure( true );
			pMonster->setUnderworld( true );

			pMonster1->setTreasure( true );
			pMonster2->setTreasure( true );

			pMonster->setClanType( CLAN_VAMPIRE_MONSTER );	
			pMonster1->setClanType( CLAN_VAMPIRE_MONSTER );	
			pMonster2->setClanType( CLAN_VAMPIRE_MONSTER );	

			pZone->addCreature(pMonster , pt.x , pt.y , Directions(rand()%8));
			pZone->addCreature(pMonster1 , pt.x , pt.y , Directions(rand()%8));
			pZone->addCreature(pMonster2 , pt.x , pt.y , Directions(rand()%8));


		}
		catch (...)
		{
			SAFE_DELETE(pMonster);
			return;
		}

		return;
	}
	else if (strstr(EventFlag.c_str(), "Event") != NULL )
	{
		//	ÀÌº¥Æ®¿ë ÄÚµå (¸ó½ºÅÍÅ¸ÀÔµµ ±×³É ÇÏµåÄÚµù -_-;)
		Zone* pZone = pCreature->getZone();
		Coord_t ZoneX = pCreature->getX();
		Coord_t ZoneY = pCreature->getY();

		TPOINT pt;

		pt = findSuitablePosition(pZone, ZoneX, ZoneY, Creature::MOVE_MODE_WALKING);

		if (pt.x == -1 || (pZone->getZoneLevel(pt.x, pt.y) & SAFE_ZONE))
			return;

		Monster *pMonster = NULL;

		try 
		{
			pMonster = new Monster(599);
			
			if (pMonster == NULL) return;

			pMonster->setName("BOSS¹ÖÎï");

			pMonster->setTreasure( true );
			pMonster->setUnderworld( true );

			pMonster->setClanType( CLAN_VAMPIRE_MONSTER );	

			pZone->addCreature(pMonster , pt.x , pt.y , Directions(rand()%8));

		}
		catch (...)
		{
			SAFE_DELETE(pMonster);
			return;
		}

		return;
	}

#endif


	SpriteType_t	SpriteType	= 0;
	MonsterType_t   MonsterType = 0;
	int 			MonsterNum	= 0;

	string MonsterName = msg.substr(j+1, k-j-1);

//	cout << MonsterName << endl;

	// SpriteTypeÀÌ ¾Æ´Ï°í MonsterTypeÀÌ ¼³Á¤µÈ °æ¿ì
	if (o!=string::npos && p!=string::npos)
	{
		MonsterType = atoi(msg.substr(o+1, p-o-1).c_str());
	}
	else if ( strstr(MonsterName.c_str(),"Ä¡ÇÁ") != NULL)
	{
		// Ä¡ÇÁ¸ó½ºÅÍ ¼ÒÈ¯ÇÏ±â ¤Ñ.¤Ñ; by DEW
		MonsterType = g_pMonsterInfoManager->getChiefMonsterTypeByName( MonsterName );
	}
	else
	{
		SpriteType = g_pMonsterInfoManager->getSpriteTypeByName( MonsterName );

		if (SpriteType==0)
		{
			SpriteType = atoi(msg.substr(j+1, k-j-1).c_str());
		}
	}

	MonsterNum = atoi(msg.substr(k+1, msg.size()-k-1).c_str());

	// 1~30 »çÀÌ
	MonsterNum = max( 1, MonsterNum );
	MonsterNum = min( 30, MonsterNum );

	// ClanType
	// "mad" monsters -_-;
	string mad = trim( msg.substr(l+1, m-l-1) );

	SUMMON_INFO summonInfo;
	if (mad=="mad")
	{
		summonInfo.canScanEnemy = true;	
	
		string group = trim( msg.substr(m+1, msg.size()-m-1) );

		if (group=="group")
		{
			summonInfo.clanType = SUMMON_INFO::CLAN_TYPE_RANDOM_GROUP;	
			summonInfo.clanID = rand()%90+2;
		}
		else
		{
			summonInfo.clanType = SUMMON_INFO::CLAN_TYPE_RANDOM_EACH;	
		}
	}
	else
	{
		summonInfo.canScanEnemy = false;	
		summonInfo.clanType = SUMMON_INFO::CLAN_TYPE_DEFAULT;	
	}

	Zone* pZone = pCreature->getZone();
	Coord_t ZoneX = pCreature->getX();
	Coord_t ZoneY = pCreature->getY();

	try 
	{
		// ÀÏ¹Ý Á¸ÀÌ¶ó¸é ¸ó½ºÅÍ¸¦ »ý¼ºÇÑ´Ù.
		if (!(pZone->getZoneLevel() & SAFE_ZONE))
		{
			filelog("summon.txt", "[%s] ZoneID=%d, %s", pCreature->getName().c_str(), pCreature->getZone()->getZoneID(), msg.c_str());

			// monsterInfo¿¡ ÀÖ´Â°ÇÁö ¾ø´Â°ÇÁö Ã¼Å©ÇÏ±â À§ÇØ¼­..
			// ¾øÀ¸¸é NoSuchElementExceptionÀÌ ¶á´Ù.
			if (SpriteType!=0)
			{
				g_pMonsterInfoManager->getMonsterTypeBySprite(SpriteType);
				addMonstersToZone(pZone, ZoneX, ZoneY, SpriteType, MonsterType, MonsterNum, summonInfo);
			}
			else if (MonsterType!=0)
			{
				g_pMonsterInfoManager->getMonsterInfo(MonsterType);
				addMonstersToZone(pZone, ZoneX, ZoneY, SpriteType, MonsterType, MonsterNum, summonInfo);
			}
		}
	} 
	catch (Throwable& t) 
	{
		cout << t.toString() << endl;
		filelog("summon.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), t.toString().c_str());
	}


	__END_DEBUG_EX __END_CATCH

}

static const Effect::EffectClass FirecrackerEffects[] =
{
	Effect::EFFECT_CLASS_FIRE_CRACKER_1,                // 0
	Effect::EFFECT_CLASS_FIRE_CRACKER_2,                // 1
	Effect::EFFECT_CLASS_FIRE_CRACKER_3,                // 2
	Effect::EFFECT_CLASS_DRAGON_FIRE_CRACKER,           // 3
	Effect::EFFECT_CLASS_FIRE_CRACKER_4,                // 4
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_1,         // 5
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_2,         // 6
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_3,         // 7
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_4,         // 8
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_1,    // 9
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_2,    // 10
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_3,    // 11
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_4,    // 12
	Effect::EFFECT_CLASS_FIRE_CRACKER_STORM             // 13
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opcommand(GamePlayer* pGamePlayer , string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);
	string command = trim( msg.substr(j+1, k-j-1) ); 
	string value1 = msg.substr(k+1, msg.size()-k-1).c_str();

	if (pGamePlayer!=NULL)
	{
		Creature* pCreature = pGamePlayer->getCreature();
		filelog("change.txt", "%s , %s , %s", pCreature->getName().c_str(), command.c_str(), value1.c_str());
	}

	GCSystemMessage gcSystemMessage;
	gcSystemMessage.setMessage("nothing");
	bool bSendPacket = true;

	if (command=="balanceZoneGroup")
	{
		bool defaultZoneGroup = false;

		if (value1=="default")
			defaultZoneGroup = true;

		// Áï½Ã~
		g_pClientManager->setBalanceZoneGroup( 0, true, defaultZoneGroup );

		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_ZONE_GROUP_BALANCING ) );
	}
	else if (command=="regenMasterLair")
	{
		if (pGamePlayer==NULL) return;
		Creature* pCreature = pGamePlayer->getCreature();
		if (pCreature==NULL) return;
		Zone* pZone = pCreature->getZone();
		Assert(pZone!=NULL);

		if (pZone->isMasterLair())
		{
			// Áï½Ã~
			MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
			Assert(pMasterLairManager!=NULL);

			pMasterLairManager->startEvent();

			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_MASTER_LAIR_REGEN ) );
		}
		else
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_IN_MASTER_LAIR ) );
		}
	}
	else if (command=="showMasterLairStatus")
	{
		if (pGamePlayer==NULL) return;
		Creature* pCreature = pGamePlayer->getCreature();
		if (pCreature==NULL) return;
		Zone* pZone = pCreature->getZone();
		Assert(pZone!=NULL);

		if (pZone->isMasterLair())
		{
			MasterLairManager* pMasterLairManager = pZone->getMasterLairManager();
			Assert(pMasterLairManager!=NULL);

			gcSystemMessage.setMessage( pMasterLairManager->toString() );
		}
		else
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_IN_MASTER_LAIR ) );
		}
	}
	else if (command=="invincible")
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature!=NULL);

		bool bInvincible = pCreature->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE);

		if (value1=="on")
		{
            char msg[50];
            sprintf( msg, g_pStringPool->c_str( STRID_INVINCIBLE ), "ON" );

			if (bInvincible)
				gcSystemMessage.setMessage( msg );
			else
			{
				pCreature->setFlag(Effect::EFFECT_CLASS_NO_DAMAGE);
				gcSystemMessage.setMessage( msg );
			}
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else if (value1=="off")
		{

            char msg[50];
            sprintf( msg, g_pStringPool->c_str( STRID_INVINCIBLE ), "OFF" );

			StringStream message;
			if (!bInvincible)
				gcSystemMessage.setMessage( msg );
			else
			{
				pCreature->removeFlag(Effect::EFFECT_CLASS_NO_DAMAGE);
				gcSystemMessage.setMessage( msg );
			}
			
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else
		{
			bSendPacket = false;
		}
	}
	else if (command=="ghost")
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature!=NULL);

		bool bGhost = pCreature->isFlag(Effect::EFFECT_CLASS_GHOST);

		if (value1=="on")
		{

            char msg[50];
            sprintf( msg, g_pStringPool->c_str( STRID_GHOST ), "ON" );

			if (bGhost)
				gcSystemMessage.setMessage( msg );
			else
			{
				Zone* pZone = pCreature->getZone();
				Assert(pZone!=NULL);

				Tile& rTile = pZone->getTile(pCreature->getX(), pCreature->getY());	
				if (!rTile.isAirBlocked() && !rTile.hasPortal())
				{
					// ÁÖº¯ÀÇ PCµé¿¡°Ô Å©¸®Ã³°¡ »ç¶óÁ³´Ù´Â »ç½ÇÀ» ºê·ÎµåÄ³½ºÆ®ÇÑ´Ù.
					GCDeleteObject gcDeleteObject(pCreature->getObjectID());
					pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcDeleteObject, pCreature);

					rTile.deleteCreature( pCreature->getObjectID() );
					pCreature->setMoveMode(Creature::MOVE_MODE_FLYING);
					rTile.addCreature( pCreature );

					GCAddEffect gcAddEffect;
					gcAddEffect.setObjectID(pCreature->getObjectID());
					gcAddEffect.setEffectID(Effect::EFFECT_CLASS_GHOST);
					gcAddEffect.setDuration(999999);
					pGamePlayer->sendPacket(&gcAddEffect);

					EffectGhost* pEffect = new EffectGhost(pCreature);
					pCreature->getEffectManager()->addEffect( pEffect );
					pCreature->setFlag(Effect::EFFECT_CLASS_GHOST);

					gcSystemMessage.setMessage( msg );
				}
				else
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_AIR_BLOCKED ) );
				}
			}
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else if (value1=="off")
		{
            char msg[50];
            sprintf( msg, g_pStringPool->c_str( STRID_GHOST ), "OFF" );

			StringStream message;
			if (!bGhost)
				gcSystemMessage.setMessage( msg );
			else
			{
				pCreature->getEffectManager()->deleteEffect( Effect::EFFECT_CLASS_GHOST );
				pCreature->removeFlag(Effect::EFFECT_CLASS_GHOST);
				gcSystemMessage.setMessage( msg );

				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pCreature->getObjectID());
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GHOST);
				pGamePlayer->sendPacket(&gcRemoveEffect);

				Zone* pZone = pCreature->getZone();
				Assert(pZone!=NULL);

				Tile& rTile = pZone->getTile(pCreature->getX(), pCreature->getY());	
				if (!rTile.isGroundBlocked() && !rTile.hasPortal())
				{
					rTile.deleteCreature( pCreature->getObjectID() );
					pCreature->setMoveMode(Creature::MOVE_MODE_WALKING);
					rTile.addCreature( pCreature );

					if (pCreature->isSlayer())
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

						GCAddSlayer gcAddSlayer;
						makeGCAddSlayer(&gcAddSlayer, pSlayer);
						pZone->broadcastPacket(&gcAddSlayer, pCreature);
					}
					else if (pCreature->isVampire())
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

						GCAddVampire gcAddVampire;
						makeGCAddVampire(&gcAddVampire, pVampire);
						pZone->broadcastPacket(&gcAddVampire, pCreature);
					}
					else if (pCreature->isOusters())
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

						GCAddOusters gcAddOusters;
						makeGCAddOusters(&gcAddOusters, pOusters);
						pZone->broadcastPacket(&gcAddOusters, pCreature);
					}
				}
				else
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_GROUND_BLOCKED ) );
				}

			}
			
			filelog("change.txt", "[%s]%s", (pGamePlayer==NULL?"Nobody":pGamePlayer->getCreature()->getName().c_str()), gcSystemMessage.toString().c_str());
		}
		else
		{
			bSendPacket = false;
		}
	}
	/*
	else if (command=="twiceMoney")
	{
		gcSystemMessage.setMessage("µ·À» µÎ¹è·Î ¸¸µì´Ï´Ù.");

		Creature* pCreature = pGamePlayer->getCreature();
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		pPC->setGold( pPC->getGold()*2 );

		// ÆÐÅ¶ ¹¹ º¸³»Áà¾ß ÇÏ´Âµ¥.. -_-;
	}
	*/
	else if (command=="clearInventory")
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_CLEAR_INVENTORY ) );

		Creature* pCreature = pGamePlayer->getCreature();
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Inventory* pInventory = pPC->getInventory();

		int i, j;

		try 
		{
			if (pInventory != NULL)
			{
				for (j = 0 ; j < pInventory->getHeight() ; j++) 
				{
					for (i = 0 ; i < pInventory->getWidth() ; i++) 
					{
						Item* pItem = pInventory->getItem(i, j);

						if (pItem != NULL) 
						{
							// ¿­¼è°¡ ¾Æ´Ï¸é Áö¿î´Ù.
							if (pItem->getItemClass() != Item::ITEM_CLASS_KEY
								&& !isRelicItem( pItem )
								)
							{
								// À¯´ÏÅ© ¾ÆÀÌÅÛÀÎ °æ¿ì °³¼ö¸¦ ÁÙÀÎ´Ù.
								if (pItem->isUnique())
								{
									//UniqueItemManager::deleteItem( pItem->getItemClass(), pItem->getItemType() );
									filelog("uniqueItem.txt", "[ClearInventory] %s", pItem->toString().c_str());
								}

								pInventory->deleteItem(i,j);
								pItem->whenPCLost( pPC );
								pItem->destroy();

								// ItemTrace Log ¸¦ ³²±ä´Ù
								if ( pItem != NULL && pItem->isTraceItem() )
								{
									remainTraceLog( pItem, pCreature->getName(), "GOD", ITEM_LOG_DELETE, DETAIL_OPCLEAR);
								}

								SAFE_DELETE(pItem);
							}
						} // end of if (pItem != NULL)
					} // end of for
				} // end of for
			}

			// inventoryÁ¤¸® ÆÐÅ¶ÀÌ ¾ø¾î¼­.. -_-;
			transportCreature(pCreature, pCreature->getZone()->getZoneID(), pCreature->getX(), pCreature->getY(), false);
		} 
		catch (Throwable & t) 
		{ 
			gcSystemMessage.setMessage(t.toString().c_str());
		}
	
	} else if (command=="clearRankBonus")
	{
		gcSystemMessage.setMessage("Rank Bonus Clear");

		Creature* pCreature = pGamePlayer->getCreature();
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		pPC->clearRankBonus();
		if ( pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			Assert( pSlayer != NULL );
			pSlayer->initAllStat();
		}
		else if ( pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			Assert( pVampire != NULL );
			pVampire->initAllStat();
		}
		else if ( pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			Assert( pOusters != NULL );
			pOusters->initAllStat();
		}
		pPC->sendRankBonusInfo();
	}
	else if (command=="setCastleOwner")
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Zone* pZone = pCreature->getZone();
		const string& Name = value1;

		bSendPacket = false;

		if ( pZone->isCastle() )
		{
			// *command setCastleOwner SlayerCommon ÀÌ ³Ñ¾î¿Â °æ¿ì Slayer °ø¿ë¼º
			if (value1 == "SlayerCommon")
			{
				g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), RACE_SLAYER, 99 );
			}
			// *command setCastleOwner VampireCommon ÀÌ ³Ñ¾î¿Â °æ¿ì Vampire °ø¿ë¼º
			else if (value1 == "VampireCommon")
			{
				g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), RACE_VAMPIRE, 0 );
			}
			else if (value1 == "OustersCommon")
			{
				g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), RACE_OUSTERS, 66 );
			}
			// *command setCastleOwner Ä³¸¯ÅÍÀÌ¸§ ÀÌ ³Ñ¾î¿Â °æ¿ì ±× Ä³¸¯ÅÍÀÇ ±æµå¼º
			else 
			{
				GuildID_t guildID;
				Race_t race;
				if ( getRaceFromDB( Name, race ) )
				{
					if ( getGuildIDFromDB( Name, race, guildID ) )
					{
						g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), race, guildID );
					}
					else 
					{
						gcSystemMessage.setMessage( g_pStringPool->getString( STRID_DO_NOT_BELONG_TO_GUILD ) );
						bSendPacket = true;
					}
				}
				else 
				{
					gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_SUCH_CHARACTOR ) );
					bSendPacket = true;
				}
			}
				
		}
		else 
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_IN_CASTLE ) );
			bSendPacket = true;
		}

	}
	else if (command=="setCastleOwnerGuild")
	{
		uint j = value1.find_first_of(' ' , 0);
		ZoneID_t zoneID = (ZoneID_t)atoi( trim( value1.substr(0, j) ).c_str() );
		GuildID_t guildID = (GuildID_t)atoi( trim( value1.substr(j+1, value1.size()-j-1) ).c_str() );

//		cout << zoneID << endl;
//		cout << guildID << endl;

		bSendPacket = false;

		Zone* pZone = getZoneByZoneID( zoneID );
		Guild* pGuild = g_pGuildManager->getGuild( guildID );

		if ( pZone != NULL && pZone->isCastle() && pGuild != NULL )
		{
			g_pCastleInfoManager->modifyCastleOwner( zoneID, pGuild->getRace(), guildID );
		}
		else if (pZone != NULL && pZone->isCastle() && guildID == 99)
		{
			g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), RACE_SLAYER, 99 );
		}
		// *command setCastleOwner VampireCommon ÀÌ ³Ñ¾î¿Â °æ¿ì Vampire °ø¿ë¼º
		else if (pZone != NULL && pZone->isCastle() && guildID == 0)
		{
			g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), RACE_VAMPIRE, 0 );
		}
		else if (pZone != NULL && pZone->isCastle() && guildID == 66)
		{
			g_pCastleInfoManager->modifyCastleOwner( pZone->getZoneID(), RACE_OUSTERS, 66 );
		}

	}
	else if ( command == "showWarList")
	{
		// ÇöÀç ÁøÇàÁßÀÎ ÀüÀïÀÇ ¸ñ·ÏÀ» º¸¿©ÁØ´Ù.

		g_pWarSystem->broadcastWarList( pGamePlayer );
		bSendPacket = false;
	}
	else if ( command == "startRaceWar")
	{
		if (!g_pVariableManager->isWarActive())
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_WAR_OFF_DO_WAR_ACITIVE_ON ) );
		}
		else if ( g_pWarSystem->startRaceWar() )
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_RACE_WAR_START ) );
		}
		else
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_ALREADY_WAR_STARTED_OF_SERVER_ERROR ) );
		}
		bSendPacket = true;
	}
	else if ( command == "startWar")
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Zone* pZone = pCreature->getZone();

		WarScheduler* pScheduler = pZone->getWarScheduler();
		if ( pScheduler != NULL )
		{
			Schedule* pSchedule = pScheduler->getRecentSchedule();
			if ( pSchedule != NULL ) pSchedule->setScheduledTime( VSDateTime::currentDateTime() );
		}
	}
	else if ( command == "removeWar")
	{
		ZoneID_t zoneID = atoi( value1.c_str() );

		if (zoneID==0)
		{
			if (pGamePlayer!=NULL)
			{
				Creature* pCreature = pGamePlayer->getCreature();
				Zone* pZone = pCreature->getZone();

				zoneID = pZone->getZoneID();
			}
			else
			{
				return;
			}
		}

		if (g_pWarSystem->removeWar( zoneID ))
		{
//			StringStream msg;
//			msg << "[" << (int)zoneID << "] ÀÇ ÀüÀïÀ» Á¦°ÅÇß½À´Ï´Ù.";
			char msg[100];
			sprintf( msg, g_pStringPool->c_str( STRID_GUILD_WAR_REMOVED ),
							(int)zoneID );
			gcSystemMessage.setMessage( msg );
		}
		else
		{
//			StringStream msg;
//			msg << "[" << (int)zoneID << "] ¿¡´Â ÁøÇàÁßÀÎ ÀüÀïÀÌ ¾ø½À´Ï´Ù.";
			char msg[100];
			sprintf( msg, g_pStringPool->c_str( STRID_NO_GUILD_WAR_IN_ACTIVE ),
							(int)zoneID );
			gcSystemMessage.setMessage( msg );
		}
		bSendPacket = true;
	}
	else if ( command == "removeRaceWar" )
	{
		if (g_pWarSystem->removeRaceWar())
		{
//			StringStream msg;
//			msg << "Á¾Á· ÀüÀïÀ» Á¦°ÅÇß½À´Ï´Ù.";
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_RACE_WAR_REMOVED ) );
		}
		else
		{
//			StringStream msg;
//			msg << "ÁøÇàÁßÀÎ Á¾Á· ÀüÀïÀÌ ¾ø½À´Ï´Ù.";
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_RACE_WAR_IN_ACTIVE ) );
		}
		bSendPacket = true;
	}
	else if ( command == "LevelWar" )
	{
		if (!g_pVariableManager->isWarActive())
		{
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_WAR_OFF_DO_WAR_ACITIVE_ON ) );
		}
		if (g_pVariableManager->isActiveLevelWar())
		{
			ZoneID_t zoneID = atoi(value1.c_str());

			if (zoneID != 1131 && zoneID != 1132 && zoneID != 1133 && zoneID != 1134)
				return;

			Zone* pZone = getZoneByZoneID(zoneID);

			Assert(pZone != NULL);

			LevelWarManager* pLevelWarManager = pZone->getLevelWarManager();

			if ( pLevelWarManager != NULL )
			{
				gcSystemMessage.setMessage("LevelWar advanced.");
				pLevelWarManager->manualStart();
			}
		}
	}
	else if ( command == "saveBloodBibleOwner" )
	{
		g_pShrineInfoManager->saveBloodBibleOwner();

		StringStream msg;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_SAVE_BLOOD_BIBLE_OWNER_INFO_IN_DB ) );

		bSendPacket = true;
	}
	else if (command=="killAllMonster")
	{
		if (pGamePlayer!=NULL)
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Zone* pZone = pCreature->getZone();
			MonsterManager* pMM = pZone->getMonsterManager();
			hash_map< ObjectID_t, Creature* > & monsters = pMM->getCreatures();
			hash_map< ObjectID_t, Creature* >::iterator itr = monsters.begin();

			for (; itr!=monsters.end(); itr++)
			{
				Creature* pCreature = itr->second;
				Monster* pMonster = dynamic_cast<Monster*>(pCreature);

				if (!pMonster->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
				{
					pMonster->setHP( 0 );
				}
			}

			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_KILL_ALL_MONSTER_IN_ZONE ) );
		}
	}
	else if (command=="killAllPC")
	{
		if (pGamePlayer!=NULL)
		{
			Creature* pCreature = pGamePlayer->getCreature();
			Zone* pZone = pCreature->getZone();
			PCManager* pPM = (PCManager*)pZone->getPCManager();
			hash_map< ObjectID_t, Creature* > & pcs = pPM->getCreatures();
			hash_map< ObjectID_t, Creature* >::iterator itr = pcs.begin();

			for (; itr!=pcs.end(); itr++)
			{
				Creature* pCreature = itr->second;
				PlayerCreature* pPlayerCreature = dynamic_cast<PlayerCreature*>(pCreature);

				if (!pPlayerCreature->isFlag(Effect::EFFECT_CLASS_NO_DAMAGE))
				{
					if ( pPlayerCreature->isSlayer() )
					{
						dynamic_cast<Slayer*>(pPlayerCreature)->setHP(0);
					}
					if ( pPlayerCreature->isVampire() )
					{
						dynamic_cast<Vampire*>(pPlayerCreature)->setHP(0);
					}
					if ( pPlayerCreature->isOusters() )
					{
						dynamic_cast<Ousters*>(pPlayerCreature)->setHP(0);
					}
				}
			}

			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_KILL_ALL_MONSTER_IN_ZONE ) );
		}
	}
	else if (command=="showZonePCNum")
	{
		if (pGamePlayer!=NULL)
		{
			WORD num = pGamePlayer->getCreature()->getZone()->getPCManager()->getSize();
			char msg[100];
			sprintf( msg, g_pStringPool->getString( STRID_PC_NUM ).c_str(), num );
			gcSystemMessage.setMessage( msg );
		}
	}
	else if (command=="showPKZonePCNum")
	{
		if (pGamePlayer!=NULL)
		{
			ZoneID_t zoneID = pGamePlayer->getCreature()->getZone()->getZoneID();
			if ( g_pPKZoneInfoManager->isPKZone(zoneID) )
			{
				int num = g_pPKZoneInfoManager->getPKZoneInfo(zoneID)->getCurrentPCNum();

				char msg[100];
				sprintf( msg, g_pStringPool->getString( STRID_PC_NUM ).c_str(), num );
				gcSystemMessage.setMessage( msg );
			}
			else
			{
				bSendPacket=false;
			}
		}
	}
	else if (command=="setPKZonePCNum")
	{
		if (pGamePlayer!=NULL)
		{
			ZoneID_t zoneID = pGamePlayer->getCreature()->getZone()->getZoneID();

			uint j = value1.find_first_of(' ' , 0);
			int num = atoi( trim( value1.substr(0, j) ).c_str() );

			if ( g_pPKZoneInfoManager->isPKZone(zoneID) )
			{
				g_pPKZoneInfoManager->getPKZoneInfo(zoneID)->setCurrentPCNum( num );
			}
		}
	}
	else if (command=="suicide")
	{
		Creature* pCreature = pGamePlayer->getCreature();
		if ( pCreature != NULL )
		{
			if ( pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->setHP(0);
			}
			else if (pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->setHP(0);
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->setHP(0);
			}
		}

		bSendPacket=false;
	}
	else if ( command=="heal" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		if ( pCreature != NULL )
		{
			Zone* pZone = pCreature->getZone();

			if ( pCreature->isFlag( Effect::EFFECT_CLASS_COMA ) )
			{
				// Å¸°ÙÀÇ ÀÌÆåÆ® ¸Å´ÏÀú¿¡¼­ ÄÚ¸¶ ÀÌÆåÆ®¸¦ »èÁ¦ÇÑ´Ù.
				pCreature->deleteEffect(Effect::EFFECT_CLASS_COMA);
				pCreature->removeFlag(Effect::EFFECT_CLASS_COMA);

				// ÄÚ¸¶ ÀÌÆåÆ®°¡ ³¯¾Æ°¬´Ù°í ¾Ë·ÁÁØ´Ù.
				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pCreature->getObjectID());
				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_COMA);
				pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcRemoveEffect);

				// ÀÌÆåÆ® Á¤º¸¸¦ ´Ù½Ã º¸³»ÁØ´Ù.
				pCreature->getEffectManager()->sendEffectInfo(pCreature, pZone, pCreature->getX(), pCreature->getY());
			}

			HP_t hp = 0;
			MP_t mp = 0;

			if ( pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				hp = pSlayer->getHP(ATTR_MAX);
				pSlayer->setHP(hp);
				mp = pSlayer->getMP(ATTR_MAX);
				pSlayer->setMP(mp);
			}
			else if (pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				hp = pVampire->getHP(ATTR_MAX);
				pVampire->setHP(hp);

				if ( pVampire->getSilverDamage() != 0 )
				{
					pVampire->setSilverDamage(0);
					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_SILVER_DAMAGE,0);
					pGamePlayer->sendPacket(&gcMI);
				}
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				hp = pOusters->getHP(ATTR_MAX);
				pOusters->setHP(hp);

				if ( pOusters->getSilverDamage() != 0 )
				{
					pOusters->setSilverDamage(0);
					GCModifyInformation gcMI;
					gcMI.addShortData(MODIFY_SILVER_DAMAGE,0);
					pGamePlayer->sendPacket(&gcMI);
				}

				mp = pOusters->getMP(ATTR_MAX) * 2;
				pOusters->setMP(mp);
			}

			if ( hp != 0 )
			{
				// ÁÖÀ§¿¡ Ã¼·ÂÀÌ Ã¤¿öÁ³´Ù´Â »ç½ÇÀ» ¾Ë¸°´Ù.
				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pCreature->getObjectID());
				gcStatusCurrentHP.setCurrentHP(hp);
				pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcStatusCurrentHP);
			}
			
			if ( mp != 0 )
			{
				GCModifyInformation gcMI;
				gcMI.addShortData(MODIFY_CURRENT_MP,mp);
				pGamePlayer->sendPacket(&gcMI);
			}
		}

		bSendPacket=false;
	}
	else if ( command=="setGold" )
	{
		Gold_t gold = atoi( value1.c_str() );
		Creature* pCreature = pGamePlayer->getCreature();

		if ( pCreature != NULL )
		{
			GCModifyInformation gcMI;

			if ( pCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
				pSlayer->setGoldEx(gold);

				gcMI.addLongData( MODIFY_GOLD, pSlayer->getGold() );
			}
			else if (pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				pVampire->setGoldEx(gold);

				gcMI.addLongData( MODIFY_GOLD, pVampire->getGold() );
			}
			else if (pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				pOusters->setGoldEx(gold);

				gcMI.addLongData( MODIFY_GOLD, pOusters->getGold() );
			}

			pGamePlayer->sendPacket( &gcMI );
		}

		// µ··Î±× ³²±æ ¾×¼ö¸é µ··Î±× ³²±ä´Ù
		if ( gold >= g_pVariableManager->getMoneyTraceLogLimit() )
		{
			if ( gold > 2000000000 )
				gold = 2000000000;

			remainMoneyTraceLog( "GOD", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_COMMAND, gold);
		}


		bSendPacket=false;
	}
	else if ( command=="Quest" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		if ( pPC != NULL && value1=="Complete" )
		{
			QuestManager* pQM = pPC->getQuestManager();
			if ( pQM != NULL )
			{
				MonsterKillQuestStatus* pQS = dynamic_cast<MonsterKillQuestStatus*>(pQM->getQuestStatusByQuestClass(QUEST_CLASS_MONSTER_KILL));
				if ( pQS != NULL )
				{
					pQS->completeQuest();
					pPC->sendCurrentQuestInfo();

					bSendPacket=false;
				}
			}
		}
	}
	else if ( command == "QuestEnding" )
	{
		GCNoticeEvent gcNoticeEvent;
		gcNoticeEvent.setCode( NOTICE_EVENT_START_QUEST_ENDING );

		pGamePlayer->sendPacket( &gcNoticeEvent );
		bSendPacket=false;
	}
	else if ( command == "NotifyWin" )
	{
		int j = value1.find_first_of(' ', 0);
		string name = value1.substr(0,j);
		int giftID = atoi( trim( value1.substr(j+1, value1.size()) ).c_str() );

		GCNotifyWin gcNW;
		gcNW.setGiftID( giftID );
		gcNW.setName( name );

		g_pZoneGroupManager->broadcast( &gcNW );
		bSendPacket = false;
	}
	else if ( command == "Horn" )
	{
		GCNoticeEvent gcNE;
		gcNE.setCode( NOTICE_EVENT_RUN_HORN );

		pGamePlayer->sendPacket( &gcNE );
		bSendPacket = false;
	}
	else if ( command == "Loud" )
	{
		Creature* pCreature = pGamePlayer->getCreature();

		int j = value1.find_first_of(' ', 0);
		string name = value1.substr(0,j);
		int time = atoi( trim( value1.substr(j+1, value1.size()) ).c_str() );

		Effect* pEffect = NULL;
		if ( pCreature->isFlag( Effect::EFFECT_CLASS_LOUD ) )
		{
			pEffect = pCreature->findEffect( Effect::EFFECT_CLASS_LOUD );

			pEffect->setDeadline(time*10);
		}
		else
		{
			pEffect = new EffectLoud(pCreature);
			pEffect->setDeadline(time*10);
			pCreature->addEffect(pEffect);
			pCreature->setFlag( pEffect->getEffectClass() );
		}

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID( pCreature->getObjectID() );
		gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
		gcAddEffect.setDuration( time*10 );

		pCreature->getZone()->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect, pCreature );
		pGamePlayer->sendPacket(&gcAddEffect);

		bSendPacket = false;
	}
	else if ( command == "Game" )
	{
		int j = value1.find_first_of(' ', 0);
		string name = value1.substr(0,j);
		
		GCNoticeEvent gcNE;
		gcNE.setCode( NOTICE_EVENT_MINI_GAME );

		if ( name == "Mine" )
		{
			gcNE.setParameter( 0 );
		}
		else if ( name == "Nemo" )
		{
			gcNE.setParameter( 1 );
		}
		else if ( name == "Push" )
		{
			gcNE.setParameter( 2 );
		}
		else if ( name == "Mine" )
		{
			gcNE.setParameter( 3 );
		}
		else if ( name == "Arrow" )
		{
			gcNE.setParameter( 4 );
		}
		else 
		{
			gcNE.setParameter( atoi(name.c_str()) );
		}

/*		if ( gcNE.getParameter() < 3 )
		{
			pGamePlayer->sendPacket(&gcNE);

			GCMiniGameScores gcScores;
			gcScores.setGameType( (GameType)gcNE.getParameter() );

			Statement* pStmt = NULL;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				Result* pResult = pStmt->executeQuery(
						"SELECT Name, Score FROM MiniGameScores WHERE Type = %u ORDER BY Score limit 10",gcScores.getGameType() );

				int i=0;

				if (pResult->next())
				{
					string name = pResult->getString(1);
					WORD score = (WORD)pResult->getInt(2);

					gcScores.setScore(i,name,score);
					i++;
				}

				SAFE_DELETE(pStmt);
			}
			END_DB(pStmt)

			pGamePlayer->sendPacket(&gcScores);
			bSendPacket = false;
		} */
	}
	else if ( command == "changeSex" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);

		if ( pPC != NULL )
		{
			if ( changeSexEx( pPC ) ) bSendPacket = false;
		}
	}
/*	else if ( command == "createBulletin" )
	{
		int bulletinLevel = atoi( value1.c_str() );

		string createMessage = "*create EventTree ";
		switch (bulletinLevel)
		{
			case 1:
				createMessage = createMessage + "26";
				break;
			case 2:
				createMessage = createMessage + "27";
				break;
			case 3:
				createMessage = createMessage + "28";
				break;
			default:
				createMessage = createMessage + "26";
				break;
		}
		opcreate(pGamePlayer, createMessage, 0);
		bSendPacket = false;
	}
	else if ( command == "createFirecraker" )
	{
		string createMessage = "*create EventETC " + value1;
		opcreate(pGamePlayer, createMessage, 0);
		bSendPacket = false;
	} */ 
	else if ( command == "Firecraker" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		if ( pCreature != NULL )
		{
			Zone* pZone = pCreature->getZone();
			
			if ( !isAbleToUseTileSkill( pCreature )
				|| (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & COMPLETE_SAFE_ZONE)
				|| atoi( value1.c_str() ) < 0 || atoi(value1.c_str() ) > 13
			   )
			{
				// À½ -_-a
			}
			else 
			{
				Effect::EffectClass effectClass = FirecrackerEffects[ atoi( value1.c_str() ) ];
				// ¿¡ÆåÆ®¸¦ ¸¸µé¾î¼­ ºê·ÎµåÄ³½ºÆÃ ÇÑ´Ù.
				GCAddEffectToTile gcAddEffectToTile;
				gcAddEffectToTile.setObjectID( pCreature->getObjectID() );
				gcAddEffectToTile.setEffectID( effectClass );
				gcAddEffectToTile.setXY( pCreature->getX(), pCreature->getY() );
				gcAddEffectToTile.setDuration( 10 );  // º° ÀÇ¹Ì ¾ø´Ù ±×³É 1ÃÊ

				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffectToTile );
				bSendPacket = false;
			}
		}
	} 
	else if ( command == "Bulletin" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		if ( pCreature != NULL )
		{
			Zone* pZone = pCreature->getZone();

			uint l = value1.find_first_of(' ' , 0);

			int bulletinLevel = atoi( value1.substr(0, l).c_str() );
			string bulletinMessage = value1.substr(l+1, value1.size()-l-1) + "%" + pCreature->getName();

			MonsterType_t MType = 0;
			int time 			= 0;

			switch (bulletinLevel)
			{
//				case 0:
//					MType = 482;
//					time = g_pVariableManager->getVariable( CHRISTMAS_TREE_DECAY_TIME ) / 10;
//					break;
				case 1:
					MType = 650;
					time = 21600;
					break;
				case 2:
					MType = 650;
					time = 43200;
					break;
				case 3:
					MType = 650;
					time = 86400;
					break;
				default:
					break;
			}

			if ( MType != 0 && l <= value1.size() ) 
			{
				if (createBulletinBoard( pZone, pCreature->getX(), pCreature->getY(), MType, bulletinMessage, VSDateTime::currentDateTime().addSecs( time ) ) )
				{
					bSendPacket = false;
				}

			}
		}
	}
	else if ( command == "SetHP" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		if ( pCreature != NULL )
		{
			Zone* pZone = pCreature->getZone();

			HP_t hp = (HP_t)atoi(value1.c_str());
			if ( pCreature->isSlayer() )
			{
				dynamic_cast<Slayer*>(pCreature)->setHP( hp );
			}
			else if ( pCreature->isVampire() )
			{
				dynamic_cast<Vampire*>(pCreature)->setHP( hp );
			}
			else if ( pCreature->isOusters() )
			{
				dynamic_cast<Ousters*>(pCreature)->setHP( hp );
			}

			GCStatusCurrentHP gcHP;
			gcHP.setObjectID( pCreature->getObjectID() );
			gcHP.setCurrentHP( hp );

			pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcHP);
			bSendPacket = false;
		}
	}
	else if ( command == "ResetAttr" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		char buffer[100];

		if ( pCreature != NULL )
		{
			if ( pCreature->isSlayer() )
			{
				gcSystemMessage.setMessage("ÈËÀà²»ÄÜ³õÊ¼»¯ÊôÐÔ.");
			}
			else if ( pCreature->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
				if ( pVampire != NULL );
				{
					VAMPIRE_RECORD prev;
					pVampire->getVampireRecord( prev );

					pVampire->setSTR(20, ATTR_BASIC);
					pVampire->setDEX(20, ATTR_BASIC);
					pVampire->setINT(20, ATTR_BASIC);

					pVampire->setBonus( 3 * (pVampire->getLevel()-1) );

					pVampire->initAllStat();
					pVampire->sendModifyInfo( prev );

					sprintf(buffer, "STR=20, DEX=20, INTE=20, Bonus=%d", pVampire->getBonus());
					pVampire->tinysave(buffer);
				}
			}
			else if ( pCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
				if ( pOusters != NULL );
				{
					OUSTERS_RECORD prev;
					pOusters->getOustersRecord( prev );

					pOusters->setSTR(10, ATTR_BASIC);
					pOusters->setDEX(10, ATTR_BASIC);
					pOusters->setINT(10, ATTR_BASIC);

					pOusters->setBonus( 3 * (pOusters->getLevel()-1) + 15 );

					pOusters->initAllStat();
					pOusters->sendModifyInfo( prev );

					sprintf(buffer, "STR=10, DEX=10, INTE=10, Bonus=%d", pOusters->getBonus());
					pOusters->tinysave(buffer);
				}
			}
		}
	}
	else if ( command == "CTF" )
	{
		g_pFlagManager->manualStart();
		gcSystemMessage.setMessage("CTF advanced.");
	}
	else if ( command == "ViewDamage" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature!=NULL);

		bool bViewDamage = pCreature->isFlag(Effect::EFFECT_CLASS_VIEW_HP);

		if ( value1 == "on" )
		{
			if ( !bViewDamage )
			{
				addSimpleCreatureEffect( pCreature, Effect::EFFECT_CLASS_VIEW_HP, -1, false );

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID( pCreature->getObjectID() );
				gcAddEffect.setEffectID( Effect::EFFECT_CLASS_VIEW_HP );
				gcAddEffect.setDuration( 65535 );

				pGamePlayer->sendPacket( &gcAddEffect );
			}
		}
		else if ( value1 == "off" )
		{
			if ( bViewDamage )
			{
				Effect* pEffect = pCreature->findEffect(Effect::EFFECT_CLASS_VIEW_HP);
				if ( pEffect != NULL ) pEffect->setDeadline(0);
			}
		}
	}
	else if ( command == "GoodsReload" )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
		if ( pPC != NULL )
		{
			pPC->loadGoods();
			pPC->registerGoodsInventory( pPC->getZone()->getObjectRegistry() );
			gcSystemMessage.setMessage("Goods relading..");
		}
	}
	else if ( command == "PetStash" )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
		if ( pPC != NULL )
		{
			GCPetStashList gcPetStashList;
			makeGCPetStashList( &gcPetStashList, pPC );

			gcPetStashList.setCode(0);
			pGamePlayer->sendPacket( &gcPetStashList );
			bSendPacket = false;
		}
	}
	else if ( command == "ZoneEvent" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		EventZoneInfo* pEventZoneInfo = EventZoneInfoManager::Instance().getEventZoneInfo( pCreature->getZone()->getZoneID() );
		if ( pEventZoneInfo == NULL ) 
		{
			gcSystemMessage.setMessage("²»ÊÇ»î¶¯µØÍ¼.");
		}
		else if ( value1 == "on" )
		{
			WORD	EventID = pEventZoneInfo->getEventID();
			ZoneEventInfo* pZoneEventInfo = EventZoneInfoManager::Instance().getZoneEventInfo( EventID );
			EventZoneInfo* pCurrentEventZoneInfo = pZoneEventInfo->getCurrentEventZoneInfo();

			if ( pCurrentEventZoneInfo != NULL && pCurrentEventZoneInfo != pEventZoneInfo )
			{
				gcSystemMessage.setMessage("ÒÑ¼¤»îÆäËû»î¶¯.");
			}
			else if ( pCurrentEventZoneInfo == NULL )
			{
				pEventZoneInfo->turnOn();
				gcSystemMessage.setMessage("¿ªÊ¼»î¶¯.");
			}
			else gcSystemMessage.setMessage("ÒÑ¼¤»îÆäËû»î¶¯.");
		}
		else if ( value1 == "off" )
		{
			if ( pEventZoneInfo->isEventOn() )
			{
				pEventZoneInfo->turnOff();
				gcSystemMessage.setMessage("¹Ø±Õ»î¶¯.");
			}
			else gcSystemMessage.setMessage("»î¶¯»¹Ã»ÓÐÆô¶¯.");
		}
	}
	else if ( command == "EventZonePCLimit" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		EventZoneInfo* pEventZoneInfo = EventZoneInfoManager::Instance().getEventZoneInfo( pCreature->getZone()->getZoneID() );
		if ( pEventZoneInfo == NULL ) 
		{
			gcSystemMessage.setMessage("²»ÊÇ»î¶¯µØÍ¼.");
		}
		else
		{
			WORD lim = (WORD)atoi(value1.c_str());
			pEventZoneInfo->setPCLimit( lim );
			char buffer[100];
			sprintf(buffer, "ÈËÊýÏÞÖÆ : %u", lim );
			gcSystemMessage.setMessage( buffer );
		}
	}
	else if ( command == "KickOutAll" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		PCManager* pPCManager = (PCManager*)pCreature->getZone()->getPCManager();
		pPCManager->transportAllCreatures( 1303, 46, 49 );
		gcSystemMessage.setMessage("°ÑËùÓÐÍæ¼ÒÒÆ¶¯µ½°ÍÄÇÍÐ.");
	}
	else if ( command == "StartTrap" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		if ( pCreature->getZoneID() == 1410 )
		{
			Zone* pZone = pCreature->getZone();

			EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_DROP, pZone );
			pZone->registerObject( pEffect );

			pEffect->setStartXY( 116, 66 );
			pEffect->setLength( 48 );
			pEffect->setTick( 5 );
			pEffect->setUnit( 10 );
			pEffect->setDir( 7 );
			pEffect->setNextTime(0);
			pEffect->setDeadline(6000);
			pZone->addEffect( pEffect );

			{
				EffectCastingIceWall* pEffect = new EffectCastingIceWall( pZone );

				pEffect->setStartXY( 63, 19 );
				pEffect->setLength( 48 );
				pEffect->setWallLength( 5 );
				pEffect->setTick( 15 );
				pEffect->setDir( 1 );
				pEffect->setNextTime(0);
				pEffect->setDeadline(6000);
				pZone->addEffect( pEffect );
			}

			pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, pZone );

			pEffect->setStartXY( 15, 72 );
			pEffect->setLength( 47 );
			pEffect->setTick( 10 );
			pEffect->setUnit( 15 );
			pEffect->setDir( 3 );
			pEffect->setLarge(true);
			pEffect->setNextTime(0);
			pEffect->setDeadline(6000);
			pZone->addEffect( pEffect );

			{
				EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pZone );

				pEffect->setStartXY( 68, 119 );
				pEffect->setLength( 27 );
				pEffect->setTick( 10 );
				pEffect->setUnit( 5 );
				pEffect->setDir( 5 );
				pEffect->setNextTime(0);
				pEffect->setDeadline(6000);
				pZone->addEffect( pEffect );
			}

			gcSystemMessage.setMessage( "ÉèÖÃÏÝÚå." );
		}
		else
		{
			gcSystemMessage.setMessage( "´ËµØÍ¼ÎÞ·¨ÉèÖÃÏÝÚå." );
		}

	}
	else if ( command == "SMSTest" )
	{
		GCNoticeEvent gcNE;
		gcNE.setCode( NOTICE_EVENT_SEND_SMS );
		pGamePlayer->sendPacket( &gcNE );
	}
	else if ( command == "ForceNick" )
	{
		int j = value1.find_first_of(' ', 0);
		string name = trim( value1.substr(0,j) );
		string nick = trim( value1.substr(j+1, value1.size()) );

		cout << "ForceNick " << name << " : " << nick << endl;;

		Creature* pTargetCreature;
		Creature* pCreature = pGamePlayer->getCreature();

		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		pTargetCreature = g_pPCFinder->getCreature_LOCKED(name);

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

		if ( pTargetCreature == NULL || pTargetCreature->getZone() != pCreature->getZone() || !pTargetCreature->isPC() )
		{
			gcSystemMessage.setMessage( "µØÍ¼ÉÏ£¬ÎÞ·¨ÕÒµ½¸Ã½ÇÉ«." );
		}
		else
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pTargetCreature);
			Statement* pStmt;

			BEGIN_DB
			{
				pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
				pStmt->executeQuery( "REPLACE INTO NicknameBook (nID, OwnerID, NickType, Nickname, NickIndex, Time) VALUES "
						"(100, '%s', %u, '%s', 0, now())", pPC->getName().c_str(), NicknameInfo::NICK_CUSTOM_FORCED, nick.c_str() );
				SAFE_DELETE( pStmt );
			}
			END_DB( pStmt )

			NicknameBook* pNickbook = pPC->getNicknameBook();
			NicknameInfo* pNick = pNickbook->getNicknameInfo( 100 );
			SAFE_DELETE( pNick );

			pNick = new NicknameInfo;
			pNick->setNicknameID(100);
			pNick->setNicknameType(NicknameInfo::NICK_CUSTOM_FORCED);
			pNick->setNickname(nick);
			pNickbook->setNicknameInfo( 100, pNick );

			pPC->setNickname( pNick );
			GCModifyNickname gcMN;
			gcMN.setObjectID( pPC->getObjectID() );
			gcMN.setNicknameInfo(pNick);

			pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcMN );
			pPC->getPlayer()->sendPacket( pNickbook->getNicknameBookListPacket() );
		}
	}
	else if ( command == "RemoveNick" )
	{
		string name = trim( value1 );
		cout << "RemoveNick " << name << endl;

		Creature* pTargetCreature;
		Creature* pCreature = pGamePlayer->getCreature();

		__ENTER_CRITICAL_SECTION((*g_pPCFinder))

		pTargetCreature = g_pPCFinder->getCreature_LOCKED(name);

		__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

		if ( pTargetCreature == NULL || pTargetCreature->getZone() != pCreature->getZone() || !pTargetCreature->isPC() )
		{
			gcSystemMessage.setMessage( "µØÍ¼ÉÏ£¬ÎÞ·¨ÕÒµ½¸Ã½ÇÉ«." );
		}
		else
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pTargetCreature);

			NicknameBook* pNickbook = pPC->getNicknameBook();
			NicknameInfo* pNick = pNickbook->getNicknameInfo( 100 );

			if ( pNick == NULL )
			{
				gcSystemMessage.setMessage( "Ã»ÓÐ½øÐÐÉ¾³ýµÄÇ¿ÖÆÄ£Ê½." );
			}
			else
			{
				Statement* pStmt;

				BEGIN_DB
				{
					pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
					pStmt->executeQuery( "DELETE FROM NicknameBook WHERE OwnerID='%s' AND nID=100",
							pPC->getName().c_str() );
					SAFE_DELETE( pStmt );
				}
				END_DB( pStmt )

				if ( pPC->getNickname() == pNick )
				{
					pPC->setNickname(NULL);
					GCModifyNickname gcMN;
					gcMN.setObjectID( pPC->getObjectID() );

					NicknameInfo noNick;
					noNick.setNicknameType( NicknameInfo::NICK_NONE );
					gcMN.setNicknameInfo( &noNick );

					pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcMN );
				}

				pNickbook->setNicknameInfo( 100, NULL );
				SAFE_DELETE( pNick );
				pPC->getPlayer()->sendPacket( pNickbook->getNicknameBookListPacket() );
			}
		}
	}
	else if ( command == "StartGDRLair" )
	{
		if ( GDRLairManager::Instance().getCurrentState() == GDR_LAIR_IDLE )
		{
			GDRLairIdle* pState = dynamic_cast<GDRLairIdle*>(GDRLairManager::Instance().getCurrentState_Object());
			if ( pState != NULL )
			{
				pState->expire();
				gcSystemMessage.setMessage("¿ªÊ¼ÒôÀÖlair.");
			}
		}
		else if ( GDRLairManager::Instance().getCurrentState() == GDR_LAIR_ENTRANCE )
		{
			GDRLairEntrance* pState = dynamic_cast<GDRLairEntrance*>(GDRLairManager::Instance().getCurrentState_Object());
			if ( pState != NULL )
			{
				pState->expire();
				gcSystemMessage.setMessage("Æô¶¯ÒôÀÖlair.");
			}
		}
	}
	else if ( command == "ResetGDRLair" )
	{
		if ( GDRLairManager::Instance().getCurrentState() != GDR_LAIR_IDLE )
		{
			GDRLairManager::Instance().reset();
			gcSystemMessage.setMessage("³õÊ¼»¯ÒôÀÖlair.");
		}
	}
	else if ( command == "GuildRecall" && pGamePlayer != NULL )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert( pCreature != NULL );

		int j = value1.find_first_of(' ', 0);
		int k = value1.find_first_of(' ', j+1);

		if ( k == string::npos ) k = value1.size();
		GuildID_t gid = atoi(trim( value1.substr(0,j) ).c_str());
		int num = atoi(trim( value1.substr(j+1, k) ).c_str());
		int side = 0;

		if ( k != value1.size() )
		{
			string sidestr = trim(value1.substr( k+1, value1.size() ));
			side = atoi( sidestr.c_str() );
			if ( side == 0 )
			{
				if ( sidestr == "defense" )
				{
					side = 1;
				}
				else if ( sidestr == "reinforce" )
				{
					side = 2;
				}
				else if ( sidestr == "attack1" )
				{
					side = 3;
				}
				else if ( sidestr == "attack2" )
				{
					side = 4;
				}
				else if ( sidestr == "attack3" )
				{
					side = 5;
				}
				else if ( sidestr == "attack4" )
				{
					side = 6;
				}
				else if ( sidestr == "attack5" )
				{
					side = 7;
				}
			}
		}

		__ENTER_CRITICAL_SECTION( (*g_pPCFinder) )

		list<Creature*> clist = g_pPCFinder->getGuildCreatures(gid, 200);

		for ( list<Creature*>::const_iterator itr = clist.begin(); itr != clist.end(); ++itr )
		{
			Creature* pTargetCreature = *itr;
			if ( pTargetCreature == NULL ) continue;
			
			// ¼ÒÈ¯ÀÚÀÇ Á¸°ú ÁÂÇ¥.
			ZoneID_t ZoneNum = pCreature->getZoneID();
			Coord_t ZoneX = pCreature->getX();
			Coord_t ZoneY = pCreature->getY();

			if ( pCreature->getZoneID() != pTargetCreature->getZoneID() )
			{
				pTargetCreature->getZone()->lock();
			}

			for ( int i=0; i<7; ++i )
			{
				deleteCreatureEffect( pTargetCreature, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + i) );
			}

			if ( side < 8 && side > 0 )
			{
				cout << "side : " << side << endl;
				addSimpleCreatureEffect( pTargetCreature, (Effect::EffectClass)(Effect::EFFECT_CLASS_SIEGE_DEFENDER + side - 1) );
			}

			if ( pCreature->getZoneID() != pTargetCreature->getZoneID() )
			{
				pTargetCreature->getZone()->unlock();
			}


			transportCreature(pTargetCreature, ZoneNum, ZoneX, ZoneY, false);
			num--;
			if ( num <= 0 ) break;
		}

		__LEAVE_CRITICAL_SECTION( (*g_pPCFinder) )
	}
	else if ( command == "ResetSiege" )
	{
		SiegeManager::Instance().reset(pGamePlayer->getCreature()->getZoneID());
	}
	else if ( command == "InitSiege" )
	{
		SiegeManager::Instance().start(pGamePlayer->getCreature()->getZoneID());
	}
	else if ( command == "ReloadAuthTable" )
	{
		LoadAuthTable( (g_pConfig->getProperty("HomePath") + "/data/CSAuth.tab").c_str() );
		LoadAuthIndex( (g_pConfig->getProperty("HomePath") + "/data/CSAuth.idx").c_str() );
		gcSystemMessage.setMessage("Æô¶¯ÈÏÖ¤³ÌÐò.");
	}
	else if ( command == "SetAuthIndex" )
	{
		DWORD index = atoi(trim(value1).c_str());
		SetAuthIndex(index);
		char buffer[100];
		sprintf(buffer, "°ÑÈÏÖ¤Ë÷ÒýÉèÖÃÎª%u.", index);
		gcSystemMessage.setMessage( buffer );
	}
	else if ( command == "IAmAttacker" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert( pCreature != NULL );

		addSimpleCreatureEffect( pCreature, Effect::EFFECT_CLASS_SIEGE_ATTACKER_1, 600 );
		gcSystemMessage.setMessage( "¹¥³ÇÕ½ 1ºÅ¹¥»÷·½±äÉíÒ»·ÖÖÓ." );
	}
	else if ( command == "IAmDefender" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert( pCreature != NULL );

		addSimpleCreatureEffect( pCreature, Effect::EFFECT_CLASS_SIEGE_DEFENDER, 600 );
		gcSystemMessage.setMessage( "¹¥³ÇÕ½ ·ÀÊØ·½±äÉíÒ»·ÖÖÓ." );
	}
	else if ( command == "IAmReinforce" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert( pCreature != NULL );

		addSimpleCreatureEffect( pCreature, Effect::EFFECT_CLASS_SIEGE_REINFORCE, 600 );
		gcSystemMessage.setMessage( "¹¥³ÇÕ½ ·ÀÊØ·½Ô®¾ü±äÉíÒ»·ÖÖÓ." );
	}
	else if ( command == "showpcstat" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert( pCreature != NULL );
		vector<uint> num = pCreature->getZone()->getPCManager()->getPCNumByRace();
		char buffer[200];
		sprintf(buffer, "ÈËÀà %uÃû, ÎüÑª¹í %uÃû, Ä§Áé %uÃû", num[RACE_SLAYER], num[RACE_VAMPIRE], num[RACE_OUSTERS]);
		gcSystemMessage.setMessage(buffer);
	}
	else if ( command == "advanceclass" )
	{
		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
		Assert( pPC != NULL );

		pPC->increaseAdvancementClassExp(1);
		GCModifyInformation gcMI;
		gcMI.addShortData(MODIFY_ADVANCEMENT_CLASS_LEVEL, pPC->getAdvancementClassLevel());
		pGamePlayer->sendPacket( &gcMI );
	}
	else if ( command == "addDynamicZone" )
	{
		int DynamicZoneType = atoi(trim(value1).c_str());

		DynamicZone* pDynamicZone = g_pDynamicZoneManager->getDynamicZoneGroup( DynamicZoneType )->getAvailableDynamicZone();

		char zoneID[32];
		sprintf( zoneID, "%u - %u", pDynamicZone->getTemplateZoneID(), pDynamicZone->getZoneID() );

		gcSystemMessage.setMessage( zoneID );
	}
	else if ( command == "enterDynamicZone" )
	{
		ZoneID_t DynamicZoneType = atoi(trim(value1).c_str());

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
		Assert( pPC != NULL );

		pPC->getGQuestManager()->enterDynamicZone( DynamicZoneType );
	}
	else if ( command == "clearDynamicZone" )
	{
		ZoneID_t DynamicZoneType = atoi(trim(value1).c_str());

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
		Assert( pPC != NULL );

		pPC->getGQuestManager()->clearDynamicZone( DynamicZoneType );
	}
	else if ( command == "setTimeOutAllZoneEffect" )
	{
		Creature* pCreature = pGamePlayer->getCreature();
		Assert( pCreature != NULL );
		pCreature->getZone()->getEffectManager()->setTimeOutAllEffect();
		gcSystemMessage.setMessage( "¹Ø±ÕµØÍ¼±³¾°ÒôÀÖ" );
	}
	else if ( command == "printTile" )
	{
		Zone* pZone = pGamePlayer->getCreature()->getZone();

		for ( int y=0; y<pZone->getHeight(); ++y )
		{
			for ( int x=0; x<pZone->getWidth(); ++x )
			{
				if ( pZone->getTile(x,y).getEffect(Effect::EFFECT_CLASS_DELETE_TILE)  != NULL )
				{
					cout << "#";
				}
				else
				{
					cout << ".";
				}
			}
			cout << endl;
		}
	}
	else 
	{
		bSendPacket = false;
	}

	if (pGamePlayer!=NULL && bSendPacket)
	{
		pGamePlayer->sendPacket( &gcSystemMessage );
		filelog("change.txt", "[%s] %s", pGamePlayer->getCreature()->getName().c_str(), gcSystemMessage.getMessage().c_str());  
	}

	__END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSayHandler::opworld(GamePlayer* pGamePlayer , string msg, int i, bool bSameWorldOnly)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	string command = msg.substr(j+1, msg.size()-j-1).c_str();

	// packet
	GGCommand ggCommand;
	ggCommand.setCommand( command );


	// °¢ server·Î º¸³½´Ù.
	HashMapGameServerInfo** pGameServerInfos = g_pGameServerInfoManager->getGameServerInfos();


	static int myWorldID = g_pConfig->getPropertyInt("WorldID");
	static int myServerID = g_pConfig->getPropertyInt("ServerID");

	int maxWorldID = g_pGameServerInfoManager->getMaxWorldID();
	int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();


	for (int worldID=1; worldID<maxWorldID; worldID++)
	{
		for (int groupID=0; groupID<maxServerGroupID; groupID++)
		{
			HashMapGameServerInfo& gameServerInfo = pGameServerInfos[worldID][groupID];

			if (!gameServerInfo.empty())
			{
				HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
				for (; itr != gameServerInfo.end(); itr++)
				{
					GameServerInfo* pGameServerInfo = itr->second;

					if (pGameServerInfo->getWorldID()==myWorldID)
					{
						// ÇöÀç ¼­¹ö°¡ ¾Æ´Ñ °æ¿ì¿¡¸¸..(À§¿¡¼­ Ã³¸®ÇßÀ¸¹Ç·Î)
						if (pGameServerInfo->getGroupID()==myServerID)
						{
						}
						else
						{
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );
						}
					}
					// ´Ù¸¥ WorldÀÎ °æ¿ì. °°Àº world¿¡¸¸ »Ñ¸®´Â°Ô ¾Æ´Ï¶ó¸é..
					else if (!bSameWorldOnly)
					{
						g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );

					}
				}
			}
		}
	}

	__END_DEBUG_EX __END_CATCH
}

void CGSayHandler::opsoulchain(GamePlayer* pPlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);

	string Name = msg.substr(j+1, msg.size()-j-1).c_str();

	CGSkillToNamed packet;
	packet.setSkillType( SKILL_SOUL_CHAIN );
	packet.setTargetName( Name );

	packet.execute( pPlayer );

	__END_DEBUG_EX __END_CATCH
}

void CGSayHandler::oplog(GamePlayer* pPlayer, string msg, int i)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	uint k = msg.find_first_of(' ' , j+1);
	uint sec = 0;
	string name;

	if ( k == string::npos )
	{
		name = msg.substr( j+1, msg.size()-j-1 ).c_str();
	}
	else
	{
		name = trim( msg.substr(j+1, k-j-1) ); 
		sec = (uint)atoi(msg.substr(k+1, msg.size()-k-1).c_str());
	}

	Creature* pTargetCreature = NULL;

	__ENTER_CRITICAL_SECTION((*g_pPCFinder))

	pTargetCreature = g_pPCFinder->getCreature_LOCKED(name);
	if (pTargetCreature==NULL) 
	{
		g_pPCFinder->unlock();
		return;
	}

	GamePlayer* pTargetGamePlayer = dynamic_cast<GamePlayer*>(pTargetCreature->getPlayer());

	if ( pTargetGamePlayer == NULL )
	{
		g_pPCFinder->unlock();
		return;
	}

	if ( sec == 0 )
		sec = 600;

	if ( pTargetGamePlayer->startPacketLog( sec ) )
	{
		char msg[100];
		sprintf( msg, "%sÄÚ¼ÇÂ¼PacketLog(%uÃë)", name.c_str(), sec );

		GCSystemMessage gcMsg;
		gcMsg.setMessage( msg );
		pPlayer->sendPacket( &gcMsg );
	}

	__LEAVE_CRITICAL_SECTION((*g_pPCFinder))

	__END_DEBUG_EX __END_CATCH
}

void CGSayHandler::opmodifyunioninfo(GamePlayer* pGamePlayer , string msg, int i, bool bSameWorldOnly = true)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	uint gID = (uint)atoi(msg.substr(j+1, msg.size()-j-1).c_str());


	cout << "ModifyunionInfo->sharedserver() : " << (int)gID <<  endl;

	sendGCOtherModifyInfoGuildUnionByGuildID(gID);
	
		
	__END_DEBUG_EX __END_CATCH
	
}

void CGSayHandler::oprefreshguildunion(GamePlayer* pGamePlayer , string msg, int i, bool bSameWorldOnly = true)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

	uint j = msg.find_first_of(' ' , i+1);
	string command = msg.substr(j+1, msg.size()-j-1).c_str();

	cout << "GuildUnionManager->reload()" << endl;

	GuildUnionManager::Instance().reload();	
	
	
/*
	// packet
	GGCommand ggCommand;
	ggCommand.setCommand( command );


	// °¢ server·Î º¸³½´Ù.
	HashMapGameServerInfo** pGameServerInfos = g_pGameServerInfoManager->getGameServerInfos();


	static int myWorldID = g_pConfig->getPropertyInt("WorldID");
	static int myServerID = g_pConfig->getPropertyInt("ServerID");

	int maxWorldID = g_pGameServerInfoManager->getMaxWorldID();
	int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();


	for (int worldID=1; worldID<maxWorldID; worldID++)
	{
		for (int groupID=0; groupID<maxServerGroupID; groupID++)
		{
			HashMapGameServerInfo& gameServerInfo = pGameServerInfos[worldID][groupID];

			if (!gameServerInfo.empty())
			{
				HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
				for (; itr != gameServerInfo.end(); itr++)
				{
					GameServerInfo* pGameServerInfo = itr->second;

					if (pGameServerInfo->getWorldID()==myWorldID)
					{
						// ÇöÀç ¼­¹ö°¡ ¾Æ´Ñ °æ¿ì¿¡¸¸..(À§¿¡¼­ Ã³¸®ÇßÀ¸¹Ç·Î)
						if (pGameServerInfo->getGroupID()==myServerID)
						{
						}
						else
						{
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );
						}
					}
					// ´Ù¸¥ WorldÀÎ °æ¿ì. °°Àº world¿¡¸¸ »Ñ¸®´Â°Ô ¾Æ´Ï¶ó¸é..
					else if (!bSameWorldOnly)
					{
						g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );

					}
				}
			}
		}
	}
*/
	__END_DEBUG_EX __END_CATCH
}


#endif
