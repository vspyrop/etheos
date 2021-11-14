
/* $Id$
 * EOSERV is released under the zlib license.
 * See LICENSE.txt for more info.
 */

#include "eoserv_config.hpp"

#include "config.hpp"

#include "console.hpp"

#include <algorithm>
#include <cstdlib>
#include <string>

static std::string eoserv_config_fromenv(const char* key)
{
	std::string envKey("etheos_");
	envKey += key;
	std::transform(envKey.begin(), envKey.end(), envKey.begin(), ::toupper);

	auto envVal = getenv(envKey.c_str());
	return std::string(envVal ? envVal : "");
}

template <typename T>
static void eoserv_config_default(Config& config, const char* key, T value)
{
	std::string envVal = eoserv_config_fromenv(key);
	if (envVal.length() != 0)
	{
		config[key] = util::variant(envVal);
		Console::Wrn("Overriding config value '%s' with value from environment variable (%s)", key, config[key].GetString().c_str());
	}
	else if (config.find(key) == config.end())
	{
		config[key] = util::variant(value);
		Console::Wrn("Could not load config value '%s' - using default (%s)", key, std::string(config[key]).c_str());
	}
}

void eoserv_config_validate_config(Config& config)
{
	eoserv_config_default(config, "LogOut"             , "-");
	eoserv_config_default(config, "LogErr"             , "error.log");
	eoserv_config_default(config, "StyleConsole"       , true);
	eoserv_config_default(config, "LogCommands"        , true);
	eoserv_config_default(config, "LogConnection"      , 0);
	eoserv_config_default(config, "Host"               , "0.0.0.0");
	eoserv_config_default(config, "Port"               , 8078);
	eoserv_config_default(config, "MaxConnections"     , 300);
	eoserv_config_default(config, "ListenBacklog"      , 50);
	eoserv_config_default(config, "MaxPlayers"         , 200);
	eoserv_config_default(config, "MaxConnectionsPerIP", 3);
	eoserv_config_default(config, "IPReconnectLimit"   , 10);
	eoserv_config_default(config, "MaxConnectionsPerPC", 1);
	eoserv_config_default(config, "MaxLoginAttempts"   , 3);
	eoserv_config_default(config, "LoginQueueSize"     , 10);
	eoserv_config_default(config, "CheckVersion"       , true);
	eoserv_config_default(config, "MinVersion"         , 0);
	eoserv_config_default(config, "MaxVersion"         , 0);
	eoserv_config_default(config, "OldVersionCompat"   , false);
	eoserv_config_default(config, "TimedSave"          , "5m");
	eoserv_config_default(config, "IgnoreHDID"         , false);
	eoserv_config_default(config, "ServerLanguage"     , "./lang/en.ini");
	eoserv_config_default(config, "PacketQueueMax"     , 40);
	eoserv_config_default(config, "PingRate"           , 60.0);
	eoserv_config_default(config, "EnforceSequence"    , true);
	eoserv_config_default(config, "EnforceTimestamps"  , true);
	eoserv_config_default(config, "EnforceSessions"    , true);
	eoserv_config_default(config, "PasswordSalt"       , "ChangeMe");
	eoserv_config_default(config, "PasswordCurrentVersion", 2);
	eoserv_config_default(config, "BcryptWorkload"     , 12);
	eoserv_config_default(config, "SeoseCompat"        , "ChangeMe");
	eoserv_config_default(config, "SeoseCompatKey"     , "D4q9_f30da%#q02#)8");
	eoserv_config_default(config, "DBType"             , "mysql");
	eoserv_config_default(config, "DBHost"             , "localhost");
	eoserv_config_default(config, "DBUser"             , "eoserv");
	eoserv_config_default(config, "DBPass"             , "eoserv");
	eoserv_config_default(config, "DBPassFile"         , "");
	eoserv_config_default(config, "DBName"             , "eoserv");
	eoserv_config_default(config, "DBPort"             , 0);
	eoserv_config_default(config, "EIF"                , "./data/pub/dat001.eif");
	eoserv_config_default(config, "ENF"                , "./data/pub/dtn001.enf");
	eoserv_config_default(config, "ESF"                , "./data/pub/dsl001.esf");
	eoserv_config_default(config, "ECF"                , "./data/pub/dat001.ecf");
	eoserv_config_default(config, "NewsFile"           , "./data/news.txt");
	eoserv_config_default(config, "DropsFile"          , "./data/drops.ini");
	eoserv_config_default(config, "ShopsFile"          , "./data/shops.ini");
	eoserv_config_default(config, "ArenasFile"         , "./data/arenas.ini");
	eoserv_config_default(config, "FormulasFile"       , "./data/formulas.ini");
	eoserv_config_default(config, "HomeFile"           , "./data/home.ini");
	eoserv_config_default(config, "SkillsFile"         , "./data/skills.ini");
	eoserv_config_default(config, "SpeechFile"          , "./data/speech.ini");
	eoserv_config_default(config, "MapDir"             , "./data/maps/");
	eoserv_config_default(config, "Maps"               , 278);
	eoserv_config_default(config, "QuestDir"           , "./data/quests/");
	eoserv_config_default(config, "Quests"             , 0);
	eoserv_config_default(config, "SLN"                , true);
	eoserv_config_default(config, "SLNURL"             , "http://eoserv.net/SLN/");
	eoserv_config_default(config, "SLNSite"            , "");
	eoserv_config_default(config, "ServerName"         , "Untitled Server");
	eoserv_config_default(config, "SLNPeriod"          , 600);
	eoserv_config_default(config, "SLNZone"            , "");
	eoserv_config_default(config, "SLNBind"            , "1");
	eoserv_config_default(config, "SLNClient"          , "");
	eoserv_config_default(config, "BotCharacters"      , "");
	eoserv_config_default(config, "GuildPrice"         , 50000);
	eoserv_config_default(config, "RecruitCost"        , 1000);
	eoserv_config_default(config, "GuildMaxMembers"    , 5000);
	eoserv_config_default(config, "GuildCreateMembers" , 9);
	eoserv_config_default(config, "GuildBankMax"       , 2000000000);
	eoserv_config_default(config, "GuildDefaultRanks"  , "Leader,Recruiter,,,,,,,New Member");
	eoserv_config_default(config, "GuildShowRecruiters", true);
	eoserv_config_default(config, "GuildCustomRanks"   , false);
	eoserv_config_default(config, "GuildEditRank"      , 1);
	eoserv_config_default(config, "GuildKickRank"      , 1);
	eoserv_config_default(config, "GuildPromoteRank"   , 1);
	eoserv_config_default(config, "GuildPromoteSameRank", 1);
	eoserv_config_default(config, "GuildDemoteRank"    , 1);
	eoserv_config_default(config, "GuildRecruitRank"   , 2);
	eoserv_config_default(config, "GuildDisbandRank"   , 0);
	eoserv_config_default(config, "GuildMultipleFounders", true);
	eoserv_config_default(config, "GuildAnnounce"      , true);
	eoserv_config_default(config, "GuildDateFormat"    , "%Y/%m/%d");
	eoserv_config_default(config, "GuildMinDeposit"    , 1000);
	eoserv_config_default(config, "GuildMaxNameLength" , 24);
	eoserv_config_default(config, "GuildMaxDescLength" , 240);
	eoserv_config_default(config, "GuildMaxRankLength" , 16);
	eoserv_config_default(config, "GuildMaxWidth"      , 180);
	eoserv_config_default(config, "GlobalPK"           , false);
	eoserv_config_default(config, "PKExcept"           , "");
	eoserv_config_default(config, "NPCChaseMode"       , 0);
	eoserv_config_default(config, "NPCChaseDistance"   , 18);
	eoserv_config_default(config, "NPCBoredTimer"      , 30);
	eoserv_config_default(config, "NPCAdjustMaxDam"    , 3);
	eoserv_config_default(config, "BoardMaxPosts"      , 20);
	eoserv_config_default(config, "BoardMaxUserPosts"  , 6);
	eoserv_config_default(config, "BoardMaxRecentPosts", 2);
	eoserv_config_default(config, "BoardRecentPostTime", 1800);
	eoserv_config_default(config, "BoardMaxSubjectLength", 32);
	eoserv_config_default(config, "BoardMaxPostLength" , 2048);
	eoserv_config_default(config, "BoardDatePosts"     , true);
	eoserv_config_default(config, "AdminBoard"         , 8);
	eoserv_config_default(config, "AdminBoardLimit"    , 100);
	eoserv_config_default(config, "FirstCharacterAdmin", true);
	eoserv_config_default(config, "ShowLevel"          , false);
	eoserv_config_default(config, "WarpBubbles"        , true);
	eoserv_config_default(config, "HideGlobal"         , false);
	eoserv_config_default(config, "GlobalBuffer"       , 0);
	eoserv_config_default(config, "AdminPrefix"        , "$");
	eoserv_config_default(config, "StatPerLevel"       , 3);
	eoserv_config_default(config, "SkillPerLevel"      , 3);
	eoserv_config_default(config, "EnforceWeight"      , 2);
	eoserv_config_default(config, "MaxWeight"          , 250);
	eoserv_config_default(config, "MaxLevel"           , 250);
	eoserv_config_default(config, "MaxExp"             , 2000000000);
	eoserv_config_default(config, "MaxStat"            , 10000);
	eoserv_config_default(config, "MaxSkillLevel"      , 100);
	eoserv_config_default(config, "MaxSkills"          , 48);
	eoserv_config_default(config, "MaxCharacters"      , 3);
	eoserv_config_default(config, "MaxShopBuy"         , 4);
	eoserv_config_default(config, "GhostTimer"         , 4);
	eoserv_config_default(config, "SpellCastCooldown"  , 0.6);
	eoserv_config_default(config, "DropTimer"          , 120);
	eoserv_config_default(config, "DropAmount"         , 15);
	eoserv_config_default(config, "ProtectPlayerDrop"  , 5);
	eoserv_config_default(config, "ProtectNPCDrop"     , 30);
	eoserv_config_default(config, "ProtectPKDrop"      , 60);
	eoserv_config_default(config, "ProtectDeathDrop"   , 300);
	eoserv_config_default(config, "SeeDistance"        , 11);
	eoserv_config_default(config, "DropDistance"       , 2);
	eoserv_config_default(config, "RangedDistance"     , 5);
	eoserv_config_default(config, "ItemDespawn"        , false);
	eoserv_config_default(config, "ItemDespawnCheck"   , 60);
	eoserv_config_default(config, "ItemDespawnRate"    , 600);
	eoserv_config_default(config, "RecoverSpeed"       , 90);
	eoserv_config_default(config, "NPCRecoverSpeed"    , 105);
	eoserv_config_default(config, "HPRecoverRate"      , 0.1);
	eoserv_config_default(config, "SitHPRecoverRate"   , 0.2);
	eoserv_config_default(config, "TPRecoverRate"      , 0.1);
	eoserv_config_default(config, "SitTPRecoverRate"   , 0.2);
	eoserv_config_default(config, "NPCRecoverRate"     , 0.1);
	eoserv_config_default(config, "SpikeTime"          , 1.5);
	eoserv_config_default(config, "SpikeDamage"        , 0.2);
	eoserv_config_default(config, "DrainTime"          , 15);
	eoserv_config_default(config, "DrainHPDamage"      , 0.2);
	eoserv_config_default(config, "DrainTPDamage"      , 0.1);
	eoserv_config_default(config, "QuakeRate"          , 5);
	eoserv_config_default(config, "Quake1"             , "4,12,0,1");
	eoserv_config_default(config, "Quake2"             , "6,12,0,2");
	eoserv_config_default(config, "Quake3"             , "2,10,3,5");
	eoserv_config_default(config, "Quake4"             , "1,4,6,8");
	eoserv_config_default(config, "ChatLength"         , 128);
	eoserv_config_default(config, "ShareMode"          , 2);
	eoserv_config_default(config, "PartyShareMode"     , 2);
	eoserv_config_default(config, "DropRateMode"       , 3);
	eoserv_config_default(config, "GhostNPC"           , false);
	eoserv_config_default(config, "GhostArena"         , false);
	eoserv_config_default(config, "AllowStats"         , true);
	eoserv_config_default(config, "StartMap"           , 0);
	eoserv_config_default(config, "StartX"             , 0);
	eoserv_config_default(config, "StartY"             , 0);
	eoserv_config_default(config, "JailMap"            , 76);
	eoserv_config_default(config, "JailX"              , 6);
	eoserv_config_default(config, "JailY"              , 7);
	eoserv_config_default(config, "UnJailX"            , 8);
	eoserv_config_default(config, "UnJailY"            , 11);
	eoserv_config_default(config, "StartItems"         , "");
	eoserv_config_default(config, "StartSpells"        , "");
	eoserv_config_default(config, "StartEquipMale"     , "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,");
	eoserv_config_default(config, "StartEquipFemale"   , "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,");
	eoserv_config_default(config, "MaxHairStyle"       , 20);
	eoserv_config_default(config, "MaxHairColor"       , 9);
	eoserv_config_default(config, "MaxSkin"            , 6);
	eoserv_config_default(config, "CreateMinHairStyle" , 1);
	eoserv_config_default(config, "CreateMaxHairStyle" , 20);
	eoserv_config_default(config, "CreateMinHairColor" , 0);
	eoserv_config_default(config, "CreateMaxHairColor" , 9);
	eoserv_config_default(config, "CreateMinSkin"      , 0);
	eoserv_config_default(config, "CreateMaxSkin"      , 3);
	eoserv_config_default(config, "DefaultBanLength"   , "2h");
	eoserv_config_default(config, "LimitDamage"        , true);
	eoserv_config_default(config, "DeathRecover"       , 0.5);
	eoserv_config_default(config, "Deadly"             , false);
	eoserv_config_default(config, "ExpRate"            , 1.0);
	eoserv_config_default(config, "DropRate"           , 1.0);
	eoserv_config_default(config, "MobRate"            , 1.0);
	eoserv_config_default(config, "PKRate"             , 0.75);
	eoserv_config_default(config, "CriticalRate"       , 0.00);
	eoserv_config_default(config, "CriticalFirstHit"   , false);
	eoserv_config_default(config, "SpawnRate"          , 1.0);
	eoserv_config_default(config, "BarberBase"         , 0);
	eoserv_config_default(config, "BarberStep"         , 200);
	eoserv_config_default(config, "BankUpgradeBase"    , 1000);
	eoserv_config_default(config, "BankUpgradeStep"    , 1000);
	eoserv_config_default(config, "JukeboxSongs"       , 20);
	eoserv_config_default(config, "JukeboxPrice"       , 25);
	eoserv_config_default(config, "JukeboxTimer"       , 90);
	eoserv_config_default(config, "RespawnBossChildren", true);
	eoserv_config_default(config, "OldReports"         , false);
	eoserv_config_default(config, "WarpSuck"           , 15);
	eoserv_config_default(config, "EvacuateSound"      , 51);
	eoserv_config_default(config, "EvacuateLength"     , 30.0);
	eoserv_config_default(config, "EvacuateStep"       , 10.0);
	eoserv_config_default(config, "EvacuateTick"       , 2.0);
	eoserv_config_default(config, "UseClassFormulas"   , false);
	eoserv_config_default(config, "UseAdjustedStats"   , true);
	eoserv_config_default(config, "BaseMinDamage"      , 0);
	eoserv_config_default(config, "BaseMaxDamage"      , 1);
	eoserv_config_default(config, "BaseDamageAtZero"   , true);
	eoserv_config_default(config, "SilentMute"         , true);
	eoserv_config_default(config, "CitizenSubscribeAnytime", false);
	eoserv_config_default(config, "CitizenUnsubscribeAnywhere", false);
	eoserv_config_default(config, "ClockMaxDelta"      , 1000);
	eoserv_config_default(config, "TradeAddQuantity"   , false);
	eoserv_config_default(config, "LogReports"         , false);
	eoserv_config_default(config, "ReportChatLogSize"  , 25);
	eoserv_config_default(config, "UseDutyAdmin"       , false);
	eoserv_config_default(config, "NoInteractDefault"  , 0);
	eoserv_config_default(config, "NoInteractDefaultAdmin", 2);
	eoserv_config_default(config, "NPCMovementRate"    , "0.9, 0.6, 1.3, 1.9, 3.7, 7.5, 15.0");
	eoserv_config_default(config, "SpawnNPCSpeed"      , "0");
	eoserv_config_default(config, "DoorTimer"          , 3.0);
	eoserv_config_default(config, "ChatMaxWidth"       , 1400);
	eoserv_config_default(config, "AccountMinLength"   , 4);
	eoserv_config_default(config, "AccountMaxLength"   , 16);
	eoserv_config_default(config, "PasswordMinLength"  , 6);
	eoserv_config_default(config, "PasswordMaxLength"  , 12);
	eoserv_config_default(config, "RealNameMaxLength"  , 64);
	eoserv_config_default(config, "LocationMaxLength"  , 64);
	eoserv_config_default(config, "EmailMaxLength"     , 64);
	eoserv_config_default(config, "ComputerNameLength" , 64);
	eoserv_config_default(config, "LimitAttack"        , 251);
	eoserv_config_default(config, "MuteLength"         , 90);
	eoserv_config_default(config, "InstrumentItems"    , "49, 50");
	eoserv_config_default(config, "MaxBankGold"        , 2000000000);
	eoserv_config_default(config, "MaxItem"            , 2000000000);
	eoserv_config_default(config, "MaxDrop"            , 10000000);
	eoserv_config_default(config, "MaxChest"           , 10000000);
	eoserv_config_default(config, "ChestSlots"         , 5);
	eoserv_config_default(config, "MaxBank"            , 200);
	eoserv_config_default(config, "BaseBankSize"       , 25);
	eoserv_config_default(config, "BankSizeStep"       , 5);
	eoserv_config_default(config, "MaxBankUpgrades"    , 7);
	eoserv_config_default(config, "PacketRateFace"     , 0.09);
	eoserv_config_default(config, "PacketRateWalk"     , 0.46);
	eoserv_config_default(config, "PacketRateAttack"   , 0.58);
	eoserv_config_default(config, "MaxTile"            , 8);
	eoserv_config_default(config, "MaxMap"             , 400);
	eoserv_config_default(config, "MaxTrade"           , 2000000000);
	eoserv_config_default(config, "IgnorePacketFamilies", "*");
	eoserv_config_default(config, "InitLoginBan"       , true);
	eoserv_config_default(config, "ThreadPoolThreads"  , 0);
	eoserv_config_default(config, "AutoCreateDatabase" , false);
	eoserv_config_default(config, "WorldDumpFile"      , "./world.bak.json");
}

void eoserv_config_validate_admin(Config& config)
{
	eoserv_config_default(config, "item"          , 1);
	eoserv_config_default(config, "npc"           , 1);
	eoserv_config_default(config, "spell"         , 1);
	eoserv_config_default(config, "class"         , 1);
	eoserv_config_default(config, "info"          , 1);
	eoserv_config_default(config, "paperdoll"     , 1);
	eoserv_config_default(config, "book"          , 1);
	eoserv_config_default(config, "inventory"     , 1);
	eoserv_config_default(config, "uptime"        , 1);
	eoserv_config_default(config, "kick"          , 1);
	eoserv_config_default(config, "skick"         , 3);
	eoserv_config_default(config, "jail"          , 1);
	eoserv_config_default(config, "unjail"        , 1);
	eoserv_config_default(config, "sjail"         , 3);
	eoserv_config_default(config, "ban"           , 2);
	eoserv_config_default(config, "sban"          , 3);
	eoserv_config_default(config, "mute"          , 1);
	eoserv_config_default(config, "smute"         , 3);
	eoserv_config_default(config, "warp"          , 2);
	eoserv_config_default(config, "warptome"      , 2);
	eoserv_config_default(config, "warpmeto"      , 2);
	eoserv_config_default(config, "hide"          , 2);
	eoserv_config_default(config, "show"          , 2);
	eoserv_config_default(config, "evacuate"      , 3);
	eoserv_config_default(config, "remap"         , 4);
	eoserv_config_default(config, "arena"         , 1);
	eoserv_config_default(config, "board"         , 1);
	eoserv_config_default(config, "shutdown"      , 4);
	eoserv_config_default(config, "rehash"        , 4);
	eoserv_config_default(config, "repub"         , 4);
	eoserv_config_default(config, "request"       , 4);
	eoserv_config_default(config, "sitem"         , 3);
	eoserv_config_default(config, "ditem"         , 3);
	eoserv_config_default(config, "snpc"          , 3);
	eoserv_config_default(config, "dnpc"          , 3);
	eoserv_config_default(config, "learn"         , 3);
	eoserv_config_default(config, "qstate"        , 3);
	eoserv_config_default(config, "quake"         , 2);
	eoserv_config_default(config, "setlevel"      , 3);
	eoserv_config_default(config, "setexp"        , 3);
	eoserv_config_default(config, "setstr"        , 3);
	eoserv_config_default(config, "setint"        , 3);
	eoserv_config_default(config, "setwis"        , 3);
	eoserv_config_default(config, "setagi"        , 3);
	eoserv_config_default(config, "setcon"        , 3);
	eoserv_config_default(config, "setcha"        , 3);
	eoserv_config_default(config, "setstatpoints" , 3);
	eoserv_config_default(config, "setskillpoints", 3);
	eoserv_config_default(config, "setadmin"      , 3);
	eoserv_config_default(config, "setfiance"     , 3);
	eoserv_config_default(config, "setpartner"    , 3);
	eoserv_config_default(config, "sethome"       , 3);
	eoserv_config_default(config, "setgender"     , 3);
	eoserv_config_default(config, "sethairstyle"  , 3);
	eoserv_config_default(config, "sethaircolor"  , 3);
	eoserv_config_default(config, "setrace"       , 3);
	eoserv_config_default(config, "setguild"      , 3);
	eoserv_config_default(config, "setguildrank"  , 3);
	eoserv_config_default(config, "setkarma"      , 3);
	eoserv_config_default(config, "setclass"      , 3);
	eoserv_config_default(config, "settitle"      , 2);
	eoserv_config_default(config, "strip"         , 3);
	eoserv_config_default(config, "dress"         , 2);
	eoserv_config_default(config, "undress"       , 2);
	eoserv_config_default(config, "dress2"        , 3);
	eoserv_config_default(config, "duty"          , 3);
	eoserv_config_default(config, "killnpc"       , 4);
	eoserv_config_default(config, "boardmod"      , 1);
	eoserv_config_default(config, "reports"       , 1);
	eoserv_config_default(config, "nowall"        , 2);
	eoserv_config_default(config, "seehide"       , 3);
	eoserv_config_default(config, "cmdprotect"    , 3);
	eoserv_config_default(config, "unlimitedweight", 3);
}
