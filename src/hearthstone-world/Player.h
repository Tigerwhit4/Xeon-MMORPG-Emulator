/*
 * Aspire Hearthstone
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _PLAYER_H
#define _PLAYER_H
struct BGScore;
class Channel;
class Creature;
class Battleground;
class TaxiPath;
class GameObject;
class Transporter;
class Corpse;
class Guild;
struct GuildRank;
class Pet;
class Charter;
class LFGMatch;
struct LevelInfo;
#define MAX_PET_NO 3
#define PLAYER_NORMAL_RUN_SPEED 7.0f
#define PLAYER_NORMAL_SWIM_SPEED 4.722222f
#define PLAYER_NORMAL_FLIGHT_SPEED 7.0f
#define PLAYER_HONORLESS_TARGET_SPELL 2479
#define MONSTER_NORMAL_RUN_SPEED 8.0f
/* action button defines */
#define PLAYER_ACTION_BUTTON_COUNT 132
#define PLAYER_ACTION_BUTTON_SIZE PLAYER_ACTION_BUTTON_COUNT * sizeof(ActionButton)
#define MAX_SPEC_COUNT 2
#define GLYPHS_COUNT 6

// gold cap
#define PLAYER_MAX_GOLD 0x7FFFFFFF

//====================================================================
//  Inventory
//  Holds the display id and item type id for objects in
//  a character's inventory
//====================================================================

enum Classes
{
	WARRIOR = 1,
	PALADIN = 2,
	HUNTER = 3,
	ROGUE = 4,
	PRIEST = 5,
	DEATHKNIGHT = 6,
	SHAMAN = 7,
	MAGE = 8,
	WARLOCK = 9,
	DRUID = 11,
};

enum Races
{
	RACE_HUMAN = 1,
	RACE_ORC = 2,
	RACE_DWARF = 3,
	RACE_NIGHTELF = 4,
	RACE_UNDEAD = 5,
	RACE_TAUREN = 6,
	RACE_GNOME = 7,
	RACE_TROLL = 8,
	RACE_BLOODELF = 10,
	RACE_DRAENEI = 11,
};

enum PlayerStatus
{
	NONE			 = 0,
	TRANSFER_PENDING = 1,
};

enum RankTitles
{
	PVPTITLE_NONE					= 0,
	PVPTITLE_PRIVATE				= 1,
	PVPTITLE_CORPORAL				= 2,
	PVPTITLE_SERGEANT				= 3,
	PVPTITLE_MASTER_SERGEANT		= 4,
	PVPTITLE_SERGEANT_MAJOR			= 5,
	PVPTITLE_KNIGHT					= 6,
	PVPTITLE_KNIGHT_LIEUTENANT		= 7,
	PVPTITLE_KNIGHT_CAPTAIN			= 8,
	PVPTITLE_KNIGHT_CHAMPION		= 9,
	PVPTITLE_LIEUTENANT_COMMANDER	= 10,
	PVPTITLE_COMMANDER				= 11,
	PVPTITLE_MARSHAL				= 12,
	PVPTITLE_FIELD_MARSHAL			= 13,
	PVPTITLE_GRAND_MARSHAL			= 14,
	PVPTITLE_SCOUT					= 15,
	PVPTITLE_GRUNT					= 16,
	PVPTITLE_HSERGEANT				= 17,
	PVPTITLE_SENIOR_SERGEANT		= 18,
	PVPTITLE_FIRST_SERGEANT			= 19,
	PVPTITLE_STONE_GUARD			= 20,
	PVPTITLE_BLOOD_GUARD			= 21,
	PVPTITLE_LEGIONNAIRE			= 22,
	PVPTITLE_CENTURION				= 23,
	PVPTITLE_CHAMPION				= 24,
	PVPTITLE_LIEUTENANT_GENERAL		= 25,
	PVPTITLE_GENERAL				= 26,
	PVPTITLE_WARLORD				= 27,
	PVPTITLE_HIGH_WARLORD			= 28,
	PVPTITLE_GLADIATOR				= 29,
	PVPTITLE_DUELIST				= 30,
	PVPTITLE_RIVAL					= 31,
	PVPTITLE_CHALLENGER				= 32,
	PVPTITLE_SCARAB_LORD			= 33,
	PVPTITLE_CONQUEROR				= 34,
	PVPTITLE_JUSTICAR				= 35,
	PVPTITLE_CHAMPION_OF_THE_NAARU	= 36,
	PVPTITLE_MERCILESS_GLADIATOR	= 37,
	PVPTITLE_OF_THE_SHATTERED_SUN	= 38,
	PVPTITLE_HAND_OF_ADAL			= 39,
	PVPTITLE_VENGEFUL_GLADIATOR		= 40,
	TITLE_BATTLEMASTER				= 41,
	TITLE_ELDER						= 42,
	TITLE_FLAME_WARDEN				= 43,
	TITLE_FLAME_KEEPER				= 44,
	TITLE_THE_EXALTED				= 45,
	TITLE_THE_EXPLORER				= 46,
	TITLE_THE_DIPLOMAT				= 47,
	TITLE_BRUTAL_GLADIATOR			= 48,
	TITLE_SEEKER					= 49,
	TITLE_ARENA_MASTER				= 50,
	TITLE_SALTY						= 51,
	TITLE_CHEF						= 52,
	TITLE_THE_SUPREME				= 53,
	TITLE_OF_THE_TEN_STORMS			= 54,
	TITLE_ARCH_DRUID				= 55,
	TITLE_CRUSADER					= 56,
	TITLE_PROPHET					= 57,
	TITLE_THE_MALEFIC				= 58,
	TITLE_STALKER					= 59,
	TITLE_OF_THE_EBON_BLADE			= 60,
	TITLE_ARCHMAGE					= 61,
	TITLE_WARBRINGER				= 62,
	TITLE_ASSASSIN					= 63,
	TITLE_GRND_MSTR_ALCHEMIST		= 64,
	TITLE_GRND_MSTR_BLACKSMITH		= 65,
	TITLE_IRON_CHEF					= 66,
	TITLE_GRND_MSTR_ENCHANTER		= 67,
	TITLE_GRND_MSTR_ENGINEER		= 68,
	TITLE_DOCTOR					= 69,
	TITLE_GRND_MSTR_ANGLER			= 70,
	TITLE_GRND_MSTR_HERBALIST		= 71,
	TITLE_GRND_MSTR_SCRIBE			= 72,
	TITLE_GRND_MSTR_JEWELCRAFT		= 73,
	TITLE_GRND_MSTR_LEATHERWORK		= 74,
	TITLE_GRND_MSTR_MINER			= 75,
	TITLE_GRND_MSTR_SKINNER			= 76,
	TITLE_GRND_MSTR_TAILOR			= 77,
	TITLE_OF_QUEL_THALAS			= 78,
	TITLE_OF_ARGUS					= 79,
	TITLE_OF_KHAZ_MODAN				= 80,
	TITLE_GNOMEREGAN				= 81,
	TITLE_LION_HEARTED				= 82,
	TITLE_CHAMPION_OF_ELUNE			= 83,
	TITLE_HERO_OF_ORGRIMMAR			= 84,
	TITLE_PLAINSRUNNER				= 85,
	TITLE_OF_THE_DARKSPEAR			= 86,
	TITLE_THE_FORSAKEN				= 87,
	TITLE_THE_MAGIC_SEEKER			= 88,
	TITLE_TWILIGHT_VANQUISHER		= 89,
	TITLE_CONQUEROR_OF_NAXXRAMA		= 90,
	TITLE_HERO_OF_NORTHREND			= 91,
	TITLE_THE_HALLOWED				= 92,
	TITLE_LOREMASTER				= 93,
	TITLE_OF_THE_ALLIANCE			= 94,
	TITLE_OF_THE_HORDE				= 95,
	TITLE_THE_FLAWLESS_VICTOR		= 96,
	TITLE_CHAMP_OF_FROZEN_WASTE		= 97,
	TITLE_AMBASSADOR				= 98,
	TITLE_THE_ARGENT_CHAMPION		= 99,
	TITLE_GUARDIAN_OF_CENARIUS		= 100,
	TITLE_BREWMASTER				= 101,
	TITLE_MERRYMAKER				= 102,
	TITLE_THE_LOVE_FOOL				= 103,
	TITLE_MATRON					= 104,
	TITLE_PATRON					= 105,
	TITLE_OBSIDIAN_SLAYER			= 106,
	TITLE_OF_THE_NIGHTFALL			= 107,
	TITLE_THE_IMMORTAL				= 108,
	TITLE_THE_UNDYING				= 109,
	TITLE_JENKINS					= 110,
	TITLE_BLOODSAIL_ADMIRAL			= 111,
	TITLE_END						= 112,
};

enum PvPAreaStatus
{
    AREA_ALLIANCE = 1,
    AREA_HORDE = 2,
    AREA_CONTESTED = 3,
    AREA_PVPARENA = 4,
};

enum PlayerMovementType
{
    MOVE_ROOT	    = 1,
    MOVE_UNROOT	    = 2,
    MOVE_WATER_WALK = 3,
    MOVE_LAND_WALK  = 4,
};

enum PlayerSpeedType
{
    RUN	            = 1,
    RUNBACK         = 2,
    SWIM	        = 3,
    SWIMBACK        = 4,
    WALK	        = 5,
    FLY	            = 6,
};

enum Standing
{
    STANDING_HATED,
    STANDING_HOSTILE,
    STANDING_UNFRIENDLY,
    STANDING_NEUTRAL,
    STANDING_FRIENDLY,
    STANDING_HONORED,
    STANDING_REVERED,
    STANDING_EXALTED
};

enum PlayerFlags
{
    PLAYER_FLAG_PARTY_LEADER		= 0x01,
    PLAYER_FLAG_AFK					= 0x02,
    PLAYER_FLAG_DND					= 0x04,
    PLAYER_FLAG_GM					= 0x08,
    PLAYER_FLAG_DEATH_WORLD_ENABLE  = 0x10,
    PLAYER_FLAG_RESTING				= 0x20,
    PLAYER_FLAG_UNKNOWN1            = 0x40,
    PLAYER_FLAG_FREE_FOR_ALL_PVP	= 0x80,
    PLAYER_FLAG_UNKNOWN2            = 0x100,
    PLAYER_FLAG_PVP_TOGGLE			= 0x200,
    PLAYER_FLAG_NOHELM				= 0x400,
    PLAYER_FLAG_NOCLOAK				= 0x800,
    PLAYER_FLAG_NEED_REST_3_HOURS	= 0x1000,
    PLAYER_FLAG_NEED_REST_5_HOURS	= 0x2000,
	PLAYER_FLAG_PVP_TIMER			= 0x40000,
};

enum CharterTypes
{
	CHARTER_TYPE_GUILD			= 0,
	CHARTER_TYPE_ARENA_2V2		= 1,
	CHARTER_TYPE_ARENA_3V3		= 2,
	CHARTER_TYPE_ARENA_5V5		= 3,
	NUM_CHARTER_TYPES			= 4,
};

enum ArenaTeamTypes
{
	ARENA_TEAM_TYPE_2V2			= 0,
	ARENA_TEAM_TYPE_3V3			= 1,
	ARENA_TEAM_TYPE_5V5			= 2,
	NUM_ARENA_TEAM_TYPES		= 3,
};

enum CooldownTypes
{
	COOLDOWN_TYPE_SPELL			= 0,
	COOLDOWN_TYPE_CATEGORY		= 1,
	NUM_COOLDOWN_TYPES,
};

enum LootType
{
	LOOT_CORPSE                 = 1,
	LOOT_SKINNING               = 2,
	LOOT_FISHING                = 3,
	LOOT_PICKPOCKETING          = 2,                        // 4 unsupported by client, sending LOOT_SKINNING instead
	LOOT_DISENCHANTING          = 2,                        // 5 unsupported by client, sending LOOT_SKINNING instead
	LOOT_PROSPECTING            = 2,                        // 6 unsupported by client, sending LOOT_SKINNING instead
	LOOT_INSIGNIA               = 2,                        // 7 unsupported by client, sending LOOT_SKINNING instead
	LOOT_MILLING				= 2                         // 7 unsupported by client, sending LOOT_SKINNING instead
};

struct spells
{
	uint16  spellId;
	uint16  slotId;
};

#pragma pack(push,1)
struct ActionButton
{
	uint16  Action;
	uint8   Misc;
	uint8   Type;
};
#pragma pack(pop)

struct CreateInfo_ItemStruct
{
	uint32  protoid;
	uint8   slot;
	uint32  amount;
};

struct CreateInfo_SkillStruct
{
	uint32  skillid;
	uint32  currentval;
	uint32  maxval;
};

struct CreateInfo_ActionBarStruct
{
	uint32  button;
	uint32  action;
	uint32  type;
	uint32  misc;
};

struct PlayerCreateInfo{
	uint8   index;
	uint8   race;
	uint32  factiontemplate;
	uint8   class_;
	uint32  mapId;
	uint32  zoneId;
	float   positionX;
	float   positionY;
	float   positionZ;
	uint16  displayId;
	uint8   strength;
	uint8   ability;
	uint8   stamina;
	uint8   intellect;
	uint8   spirit;
	uint32  health;
	uint32  mana;
	uint32  rage;
	uint32  focus;
	uint32  energy;
	uint32  runic;
	uint32  attackpower;
	float   mindmg;
	float   maxdmg;
	std::list<CreateInfo_ItemStruct> items;
	std::list<CreateInfo_SkillStruct> skills;
	std::list<CreateInfo_ActionBarStruct> actionbars;
	std::set<uint32> spell_list;
	//uint32 item[10];
	//uint8 item_slot[10];
	//uint16 spell[10];
};

struct DamageSplit
{
	PlayerPointer caster;
	AuraPointer   aura;
	uint32  miscVal;
	union
	{
		uint32 damage;
		float damagePCT;
	};
};

struct LoginAura
{
    uint32 id;
    uint32 dur;
};

static const uint32 TalentTreesPerClass[DRUID+1][3] =  {
	{ 0, 0, 0 },		// NONE
	{ 161, 163, 164 },	// WARRIOR
	{ 382, 383, 381 },	// PALADIN
	{ 361, 363, 362 },	// HUNTER
	{ 182, 181, 183 },	// ROGUE
	{ 201, 202, 203 },	// PRIEST
	{ 398, 399, 400 },	// DEATH KNIGHT
	{ 261, 263, 262 },	// SHAMAN
	{ 81, 41, 61 },		// MAGE
	{ 302, 303, 301 },	// WARLOCK
	{ 0, 0, 0 },		// NONE
	{ 283, 281, 282 },	// DRUID
};

// Dodge ( class base ) - UNUSED, Warrior, Paladin, Hunter, Rogue,   Priest, Death Knight, Shaman, Mage, Warlock, UNUSED, Druid
const float baseDodge[12] = { 0.0f, 3.4636f, 3.2685f, -5.45f, -0.5900f, 3.1830f, 3.4636f, 1.6750f, 3.4575f, 2.0350f, 0.0f, 4.951f };

// Dodge ( class ratio ) - UNUSED, Warrior, Paladin, Hunter, Rogue, Priest, Death Knight, Shaman, Mage, Warlock, UNUSED, Druid
// TODO: get proper ratios for all levels, we only have values for level 70 currently
const float dodgeRatio[80][12] = {
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 1
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 2
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 3
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 4
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 5
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 6
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 7
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 8
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 9
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 10
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 11
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 12
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 13
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 14
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 15
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 16
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 17
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 18
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 19
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 20
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 21
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 22
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 23
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 24
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 25
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 26
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 27
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 28
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 29
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 30
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 31
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 32
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 33
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 34
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 35
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 36
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 37
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 38
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 39
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 40
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 41
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 42
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 43
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 44
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 45
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 46
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 47
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 48
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 49
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 50
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 51
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 52
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 53										 { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 54
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 55
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 56
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 57
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 58
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 59
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 60
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 61
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 62
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 63
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 64
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 65
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 66
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 67
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 68
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 69
{ 0.0f, 30.0f, 25.0f, 25.0f, 20.0f, 25.0f, 25.0f, 25.0f, 25.0f, 25.0f, 0.0f, 14.7059f },// Level 70
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 71
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 72
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 73
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 74
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 75
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 76
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 77
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 78
{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },// Level 79
{ 0.0f, 73.5294f, 52.0833f, 75.1879f, 41.4937f, 52.0833f, 73.5294f, 52.0833f, 51.282f, 52.0833f, 0.0f, 41.6666f } // Level 80
};

/*
Exalted	        1,000	 Access to racial mounts. Capped at 999.7
Revered	        21,000	 Heroic mode keys for Outland dungeons
Honored	        12,000	 10% discount from faction vendors
Friendly	    6,000
Neutral	        3,000
Unfriendly	    3,000	 Cannot buy, sell or interact.
Hostile	        3,000	 You will always be attacked on sight
Hated	        36,000 
*/
enum FactionRating
{
	HATED,
	HOSTILE,
	UNFRIENDLY,
	NEUTRAL,
	FRIENDLY,
	HONORED,
	REVERED,
	EXALTED
};
enum RuneTypes
{
	RUNE_TYPE_BLOOD			= 0,
	RUNE_TYPE_FROST			= 1,
	RUNE_TYPE_UNHOLY		= 2,
	RUNE_TYPE_DEATH			= 3,
	RUNE_TYPE_RECHARGING	= 4
};
struct FactionReputation
{
	int32 standing;
	uint8 flag;
	int32 baseStanding;
	HEARTHSTONE_INLINE int32 CalcStanding() { return standing - baseStanding; }
	HEARTHSTONE_INLINE bool Positive() { return standing >= 0; }
};

struct PlayerInfo
{
	~PlayerInfo();
	uint32 guid;
	uint32 acct;
	char * name;
	uint32 race;
	uint32 gender;
	uint32 cl;
	uint32 team;
	
	time_t lastOnline;
	uint32 lastZone;
	uint32 lastLevel;
	Group * m_Group;
	int8 subGroup;
#ifdef VOICE_CHAT
	int8 groupVoiceId;
#endif

	PlayerPointer m_loggedInPlayer;
	Guild * guild;
	GuildRank * guildRank;
	GuildMember * guildMember;
	ArenaTeam * arenaTeam[NUM_ARENA_TEAM_TYPES];
	uint32 charterId[NUM_CHARTER_TYPES];
};
struct PlayerPet
{
	string name;
	uint32 entry;
	string fields;
	uint32 xp;
	bool active;
	char stablestate;
	uint32 number;
	uint32 level;
	uint32 loyaltyxp;
	uint32 happinessupdate;
	string actionbar;
	bool summon;
	uint32 loyaltypts;
	uint32 loyaltyupdate;
	char loyaltylvl;
};
enum MeetingStoneQueueStatus
{
	MEETINGSTONE_STATUS_NONE								= 0,
	MEETINGSTONE_STATUS_JOINED_MEETINGSTONE_QUEUE_FOR	   = 1,
	MEETINGSTONE_STATUS_PARTY_MEMBER_LEFT_LFG			   = 2,
	MEETINGSTONE_STATUS_PARTY_MEMBER_REMOVED_PARTY_REMOVED  = 3,
	MEETINGSTONE_STATUS_LOOKING_FOR_NEW_PARTY_IN_QUEUE	  = 4,
	MEETINGSTONE_STATUS_NONE_UNK							= 5,
};
enum ItemPushResultTypes
{
	ITEM_PUSH_TYPE_LOOT			 = 0x00000000,
	ITEM_PUSH_TYPE_RECEIVE		  = 0x00000001,
	ITEM_PUSH_TYPE_CREATE		   = 0x00000002,
};
struct WeaponModifier
{
	uint32 wclass;
	uint32 subclass;
	float value;
};
struct PetActionBar
{
	uint32 spell[10];
};
struct classScriptOverride
{
	uint32 id;
	uint32 effect;
	uint32 aura;
	uint32 damage;
	bool percent;
};
class Spell;
class Item;
class Container;
class WorldSession;
class ItemInterface;
class GossipMenu;
class AchievementInterface;
struct TaxiPathNode;

#define RESTSTATE_RESTED			 1
#define RESTSTATE_NORMAL			 2
#define RESTSTATE_TIRED100		     3
#define RESTSTATE_TIRED50			 4
#define RESTSTATE_EXHAUSTED		     5
#define UNDERWATERSTATE_NONE		 0
#define UNDERWATERSTATE_SWIMMING	 1
#define UNDERWATERSTATE_UNDERWATER   2
#define UNDERWATERSTATE_RECOVERING   4
#define UNDERWATERSTATE_TAKINGDAMAGE 8
#define UNDERWATERSTATE_FATIGUE	     16
#define UNDERWATERSTATE_LAVA		 32
#define UNDERWATERSTATE_SLIME		 64

enum TRADE_STATUS
{
	TRADE_STATUS_PLAYER_BUSY	    = 0x00,
	TRADE_STATUS_PROPOSED		    = 0x01,
	TRADE_STATUS_INITIATED		    = 0x02,
	TRADE_STATUS_CANCELLED		    = 0x03,
	TRADE_STATUS_ACCEPTED		    = 0x04,
	TRADE_STATUS_ALREADY_TRADING    = 0x05,
	TRADE_STATUS_PLAYER_NOT_FOUND   = 0x06,
	TRADE_STATUS_STATE_CHANGED	    = 0x07,
	TRADE_STATUS_COMPLETE		    = 0x08,
	TRADE_STATUS_UNACCEPTED		    = 0x09,
	TRADE_STATUS_TOO_FAR_AWAY	    = 0x0A,
	TRADE_STATUS_WRONG_FACTION	    = 0x0B,
	TRADE_STATUS_FAILED			    = 0x0C,
	TRADE_STATUS_UNK2			    = 0x0D,
	TRADE_STATUS_PLAYER_IGNORED	    = 0x0E,
	TRADE_STATUS_YOU_STUNNED		= 0x0F,
	TRADE_STATUS_TARGET_STUNNED		= 0x10,
	TRADE_STATUS_DEAD				= 0x11,
	TRADE_STATUS_TARGET_DEAD		= 0x12,
	TRADE_STATUS_YOU_LOGOUT			= 0x13,
	TRADE_STATUS_TARGET_LOGOUT		= 0x14,
	TRADE_STATUS_TRIAL_ACCOUNT		= 0x15,
	TRADE_STATUS_ONLY_CONJURED		= 0x16,
};
enum TRADE_DATA
{
	TRADE_GIVE		= 0x00,
	TRADE_RECEIVE	 = 0x01,
};
enum DUEL_STATUS
{
	DUEL_STATUS_OUTOFBOUNDS,
	DUEL_STATUS_INBOUNDS
};
enum DUEL_STATE
{
	DUEL_STATE_REQUESTED,
	DUEL_STATE_STARTED,
	DUEL_STATE_FINISHED
};
enum DUEL_WINNER
{
	DUEL_WINNER_KNOCKOUT,
	DUEL_WINNER_RETREAT,
};
#define PLAYER_ATTACK_TIMEOUT_INTERVAL	5000
#define PLAYER_FORCED_RESURECT_INTERVAL	360000 // 1000*60*6= 6 minutes 

struct PlayerSkill
{
	skilllineentry * Skill;
	uint32 CurrentValue;
	uint32 MaximumValue;
	uint32 BonusValue;
	float GetSkillUpChance();
	void Reset(uint32 Id);
};

enum SPELL_INDEX
{
	SPELL_TYPE_INDEX_MARK			= 1,
	SPELL_TYPE_INDEX_POLYMORPH		= 2,
	SPELL_TYPE_INDEX_FEAR			= 3,
	SPELL_TYPE_INDEX_SAP			= 4,
	SPELL_TYPE_INDEX_SCARE_BEAST	= 5,
	SPELL_TYPE_INDEX_HIBERNATE		= 6,
	SPELL_TYPE_INDEX_EARTH_SHIELD	= 7,
	SPELL_TYPE_INDEX_CYCLONE		= 8,
	SPELL_TYPE_INDEX_BANISH			= 9,
	SPELL_TYPE_INDEX_JUDGEMENT		= 10,	
	SPELL_TYPE_INDEX_REPENTANCE		= 11,
	SPELL_TYPE_INDEX_SLOW			= 12,
	NUM_SPELL_TYPE_INDEX			= 13,
};

#define PLAYER_RATING_MODIFIER_RANGED_SKILL						PLAYER_FIELD_COMBAT_RATING_1
#define PLAYER_RATING_MODIFIER_DEFENCE							PLAYER_FIELD_COMBAT_RATING_1_1
#define PLAYER_RATING_MODIFIER_DODGE							PLAYER_FIELD_COMBAT_RATING_1_2
#define PLAYER_RATING_MODIFIER_PARRY							PLAYER_FIELD_COMBAT_RATING_1_3
#define PLAYER_RATING_MODIFIER_BLOCK							PLAYER_FIELD_COMBAT_RATING_1_4
#define PLAYER_RATING_MODIFIER_MELEE_HIT						PLAYER_FIELD_COMBAT_RATING_1_5
#define PLAYER_RATING_MODIFIER_RANGED_HIT						PLAYER_FIELD_COMBAT_RATING_1_6
#define PLAYER_RATING_MODIFIER_SPELL_HIT						PLAYER_FIELD_COMBAT_RATING_1_7
#define PLAYER_RATING_MODIFIER_MELEE_CRIT						PLAYER_FIELD_COMBAT_RATING_1_8
#define PLAYER_RATING_MODIFIER_RANGED_CRIT						PLAYER_FIELD_COMBAT_RATING_1_9
#define PLAYER_RATING_MODIFIER_SPELL_CRIT						PLAYER_FIELD_COMBAT_RATING_1_10
#define PLAYER_RATING_MODIFIER_MELEE_HIT_AVOIDANCE				PLAYER_FIELD_COMBAT_RATING_1_11 // GUESSED
#define PLAYER_RATING_MODIFIER_RANGED_HIT_AVOIDANCE				PLAYER_FIELD_COMBAT_RATING_1_12 // GUESSED
#define PLAYER_RATING_MODIFIER_SPELL_HIT_AVOIDANCE				PLAYER_FIELD_COMBAT_RATING_1_13 // GUESSED
#define PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE			PLAYER_FIELD_COMBAT_RATING_1_14
#define PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE			PLAYER_FIELD_COMBAT_RATING_1_15
#define PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE			PLAYER_FIELD_COMBAT_RATING_1_16
#define PLAYER_RATING_MODIFIER_MELEE_HASTE						PLAYER_FIELD_COMBAT_RATING_1_17
#define PLAYER_RATING_MODIFIER_RANGED_HASTE						PLAYER_FIELD_COMBAT_RATING_1_18
#define PLAYER_RATING_MODIFIER_SPELL_HASTE						PLAYER_FIELD_COMBAT_RATING_1_19
#define PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL			PLAYER_FIELD_COMBAT_RATING_1_20
#define PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL				PLAYER_FIELD_COMBAT_RATING_1_21
#define PLAYER_RATING_MODIFIER_HIT_AVOIDANCE_RATING				PLAYER_FIELD_COMBAT_RATING_1_22
#define PLAYER_RATING_MODIFIER_EXPERTISE						PLAYER_FIELD_COMBAT_RATING_1_23
#define PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING			PLAYER_FIELD_COMBAT_RATING_1_24

class ArenaTeam;
struct PlayerCooldown
{
	uint32 ExpireTime;
	uint32 ItemId;
	uint32 SpellId;
};

//====================================================================
//  Player
//  Class that holds every created character on the server.
//
//  TODO:  Attach characters to user accounts
//====================================================================
typedef std::set<uint32>	                        SpellSet;
typedef std::list<classScriptOverride*>             ScriptOverrideList;
typedef std::set<uint32>                            SaveSet;
typedef std::map<uint64, ByteBuffer*>               SplineMap;
typedef std::map<uint32, ScriptOverrideList* >      SpellOverrideMap;
typedef std::map<uint32, uint32>                    SpellOverrideExtraAuraMap;
typedef std::map<uint32, FactionReputation*>        ReputationMap;
typedef std::map<uint32, uint64>                    SoloSpells;
typedef std::map<SpellEntry*, pair<uint32, uint32> >StrikeSpellMap;
typedef std::map<uint32, OnHitSpell >               StrikeSpellDmgMap;
typedef std::map<uint32, PlayerSkill>				SkillMap;
typedef std::set<PlayerPointer *>					ReferenceSet;
typedef std::map<uint32, PlayerCooldown>			PlayerCooldownMap;

//#define OPTIMIZED_PLAYER_SAVING

class SERVER_DECL Player : public Unit
{
	friend class WorldSession;
	friend class Pet;
	friend class SkillIterator;

public:

	Player ( uint32 guid );
	~Player ( );
	virtual void Destructor();
	virtual void Init();

	HEARTHSTONE_INLINE Guild * GetGuild() { return m_playerInfo->guild; }
	HEARTHSTONE_INLINE GuildMember * GetGuildMember() { return m_playerInfo->guildMember; }
	HEARTHSTONE_INLINE GuildRank * GetGuildRankS() { return m_playerInfo->guildRank; }

	void EventGroupFullUpdate();
	void GroupUninvite(PlayerPointer player, PlayerInfo *info);

	/************************************************************************/
	/* Skill System															*/
	/************************************************************************/

	void _AdvanceSkillLine(uint32 SkillLine, uint32 Count = 1);
	void _AddSkillLine(uint32 SkillLine, uint32 Current, uint32 Max);
	uint32 _GetSkillLineMax(uint32 SkillLine);
	uint32 _GetSkillLineCurrent(uint32 SkillLine, bool IncludeBonus = true);
	void _RemoveSkillLine(uint32 SkillLine);
	void _UpdateMaxSkillCounts();
	void _ModifySkillBonus(uint32 SkillLine, int32 Delta);
	void _ModifySkillBonusByType(uint32 SkillType, int32 Delta);
	bool _HasSkillLine(uint32 SkillLine);
	void RemoveSpellsFromLine(uint32 skill_line);
	void _RemoveAllSkills();
	void _RemoveLanguages();
	void _AddLanguages(bool All);
	void _AdvanceAllSkills(uint32 count);
	void _ModifySkillMaximum(uint32 SkillLine, uint32 NewMax);


	void RecalculateHonor();

	LfgMatch * m_lfgMatch;
	uint32 m_lfgInviterGuid;

	void EventTimeoutLfgInviter();

protected:

	void _UpdateSkillFields();

	SkillMap m_skills;


	// COOLDOWNS
	PlayerCooldownMap m_cooldownMap[NUM_COOLDOWN_TYPES];
	uint32 m_globalCooldown;
	
public:
	void Cooldown_OnCancel(SpellEntry *pSpell);
	void Cooldown_AddStart(SpellEntry * pSpell);
	void Cooldown_Add(SpellEntry * pSpell, ItemPointer pItemCaster);
	void Cooldown_AddItem(ItemPrototype * pProto, uint32 x);
	bool Cooldown_CanCast(SpellEntry * pSpell);
	bool Cooldown_CanCast(ItemPrototype * pProto, uint32 x);

protected:
	void _Cooldown_Add(uint32 Type, uint32 Misc, uint32 Time, uint32 SpellId, uint32 ItemId);
	void _LoadPlayerCooldowns(QueryResult * result);
	void _SavePlayerCooldowns(QueryBuffer * buf);

	// END COOLDOWNS

public:

	bool ok_to_remove;
	uint64 m_spellIndexTypeTargets[NUM_SPELL_TYPE_INDEX];
	void OnLogin();//custom stuff on player login.
	void EquipInit(PlayerCreateInfo *EquipInfo);
	void RemoveSpellTargets(uint32 Type);
	void RemoveSpellIndexReferences(uint32 Type);
	void SetSpellTargetType(uint32 Type, UnitPointer target);
	void SendMeetingStoneQueue(uint32 DungeonId, uint8 Status);

	void AddToWorld();
	void AddToWorld(MapMgrPointer pMapMgr);
	void RemoveFromWorld();
	bool Create ( WorldPacket &data );
	
	void Update( uint32 time );
	
    void BuildFlagUpdateForNonGroupSet(uint32 index, uint32 flag);
	std::string m_afk_reason;
	void SetAFKReason(std::string reason) { m_afk_reason = reason; };
	HEARTHSTONE_INLINE const char* GetName() { return m_name.c_str(); }
	HEARTHSTONE_INLINE std::string* GetNameString() { return &m_name; }

	//void KilledMonster(uint32 entry, const uint64 &guid);
	void GiveXP(uint32 xp, const uint64 &guid, bool allowbonus);   // to stop rest xp being given
	void ModifyBonuses(uint32 type,int32 val);
	std::map<uint32, uint32> m_wratings;

    /************************************************************************/
    /* Taxi                                                                 */
    /************************************************************************/
    HEARTHSTONE_INLINE TaxiPath*    GetTaxiPath() { return m_CurrentTaxiPath; }
    HEARTHSTONE_INLINE bool         GetTaxiState() { return m_onTaxi; }
    const uint32&       GetTaximask( uint8 index ) const { return m_taximask[index]; }
    void                LoadTaxiMask(const char* data);
    void                TaxiStart(TaxiPath* path, uint32 modelid, uint32 start_node);
    void                JumpToEndTaxiNode(TaxiPath * path);
    void                EventDismount(uint32 money, float x, float y, float z);
    void                EventTaxiInterpolate();

    HEARTHSTONE_INLINE void         SetTaxiState    (bool state) { m_onTaxi = state; }
    HEARTHSTONE_INLINE void         SetTaximask     (uint8 index, uint32 value ) { m_taximask[index] = value; }
    HEARTHSTONE_INLINE void         SetTaxiPath     (TaxiPath *path) { m_CurrentTaxiPath = path; }
    HEARTHSTONE_INLINE void         SetTaxiPos()	{m_taxi_pos_x = m_position.x; m_taxi_pos_y = m_position.y; m_taxi_pos_z = m_position.z;}
    HEARTHSTONE_INLINE void         UnSetTaxiPos()	{m_taxi_pos_x = 0; m_taxi_pos_y = 0; m_taxi_pos_z = 0; }
 
	// Taxi related variables
	vector<TaxiPath*>   m_taxiPaths;
    TaxiPath*           m_CurrentTaxiPath;
    uint32              taxi_model_id;
	uint32              lastNode;
    uint32              m_taxi_ride_time;
    uint32              m_taximask[12];
    float               m_taxi_pos_x;
    float               m_taxi_pos_y;
    float               m_taxi_pos_z;
    bool                m_onTaxi;
	uint32				m_taxiMapChangeNode;

    /************************************************************************/
    /* Quests                                                               */
    /************************************************************************/
	bool HasQuests() 
	{
		for(int i = 0; i < 25; ++i)
		{
			if(m_questlog[i] != 0)
				return true;
		}
		return false;
	}

	bool HasQuest(uint32 qid)
	{
		return GetQuestLogForEntry(qid) != NULL;
	}

	int32                GetOpenQuestSlot();
	QuestLogEntry*       GetQuestLogForEntry(uint32 quest);
	HEARTHSTONE_INLINE QuestLogEntry*GetQuestLogInSlot(uint32 slot)  { return m_questlog[slot]; }
    HEARTHSTONE_INLINE uint32        GetQuestSharer()                { return m_questSharer; }
    
    HEARTHSTONE_INLINE void         SetQuestSharer(uint32 guid)     { m_questSharer = guid; }
    void                SetQuestLogSlot(QuestLogEntry *entry, uint32 slot);
    
    HEARTHSTONE_INLINE void         PushToRemovedQuests(uint32 questid)	{ m_removequests.insert(questid);}
	HEARTHSTONE_INLINE uint32		GetFinishedDailiesCount() { return (uint32)m_finishedDailyQuests.size(); }
    void                AddToFinishedQuests(uint32 quest_id);
	void				AddToFinishedDailyQuests(uint32 quest_id);
	void				EventTimedQuestExpire(Quest *qst, QuestLogEntry *qle, uint32 log_slot, uint32 interval);
	
	bool                HasFinishedQuest(uint32 quest_id);
	bool				HasFinishedDailyQuest(uint32 quest_id);
	bool                HasQuestForItem(uint32 itemid);
    bool                CanFinishQuest(Quest* qst);
	bool                HasQuestSpell(uint32 spellid);
	void                RemoveQuestSpell(uint32 spellid);
	bool                HasQuestMob(uint32 entry);
	void                RemoveQuestMob(uint32 entry);
	void                RemoveQuestsFromLine(int skill_line);

	//Quest related variables
	uint32 m_questbarrier1[25];
	QuestLogEntry*		m_questlog[25];
	uint32 m_questbarrier2[25];
	std::set<uint32>	m_QuestGOInProgress;
	std::set<uint32>	m_removequests;
	std::set<uint32>	m_finishedQuests;
	std::set<uint32>	m_finishedDailyQuests;
	uint32				m_questSharer;
	std::set<uint32>	quest_spells;
	std::set<uint32>	quest_mobs;
	Mutex				DailyMutex;

	void EventPortToGM(uint32 guid);
	HEARTHSTONE_INLINE uint32 GetTeam() { return m_team; }
	HEARTHSTONE_INLINE void SetTeam(uint32 t) { m_team = t; m_bgTeam=t; }
	HEARTHSTONE_INLINE void ResetTeam() { m_team = myRace->team_id==7 ? 0 : 1; m_bgTeam=m_team; }

	HEARTHSTONE_INLINE bool IsInFeralForm()
	{
		int s = GetShapeShift();
		if( s <= 0 )
			return false;

		//Fight forms that do not use player's weapon
		return ( s == 1 || s == 5 || s == 8 );
	}
	void CalcDamage();
	uint32 GetMainMeleeDamage(uint32 AP_owerride); //i need this for windfury

    const uint64& GetSelection( ) const { return m_curSelection; }
	void SetSelection(const uint64 &guid) { m_curSelection = guid; }
	
    /************************************************************************/
    /* Spells                                                               */
    /************************************************************************/
	bool HasSpell(uint32 spell);
	bool HasDeletedSpell(uint32 spell);
	void smsg_InitialSpells();
	void smsg_TalentsInfo(bool update, uint32 newTalentId, uint8 newTalentRank);
	void BuildFullTalentsInfo(WorldPacket *data, bool self);
	void addSpell(uint32 spell_idy);
	void removeSpellByHashName(uint32 hash);
	bool removeSpell(uint32 SpellID, bool MoveToDeleted, bool SupercededSpell, uint32 SupercededSpellID);

    // PLEASE DO NOT INLINE!
    void AddOnStrikeSpell(SpellEntry* sp, uint32 delay)
    {
        m_onStrikeSpells.insert( map< SpellEntry*, pair<uint32, uint32> >::value_type( sp, make_pair( delay, 0 ) ) );
    }
    void RemoveOnStrikeSpell(SpellEntry *sp)
    {
        m_onStrikeSpells.erase(sp);
    }
    void AddOnStrikeSpellDamage(uint32 spellid, uint32 mindmg, uint32 maxdmg)
    {
        OnHitSpell sp;
        sp.spellid = spellid;
        sp.mindmg = mindmg;
        sp.maxdmg = maxdmg;
        m_onStrikeSpellDmg[spellid] = sp;
    }
    void RemoveOnStrikeSpellDamage(uint32 spellid)
    {
        m_onStrikeSpellDmg.erase(spellid);
    }

    //Spells variables
    StrikeSpellMap      m_onStrikeSpells;
    StrikeSpellDmgMap   m_onStrikeSpellDmg;
    SpellOverrideMap    mSpellOverrideMap;
    SpellSet            mSpells;
    SpellSet            mDeletedSpells;
	SpellSet			mShapeShiftSpells;
	map_t				mSpellsUniqueTargets;

	void AddShapeShiftSpell(uint32 id);
	void RemoveShapeShiftSpell(uint32 id);
	void CheckSpellUniqueTargets(SpellEntry *sp, uint64 guid);


    /************************************************************************/
    /* Actionbar                                                            */
    /************************************************************************/
	void                setAction(uint8 button, uint16 action, uint8 type, uint8 misc);
	void                SendInitialActions();
    bool                m_actionsDirty;
	
    /************************************************************************/
    /* Reputation                                                           */
    /************************************************************************/
	void                ModStanding(uint32 Faction, int32 Value);
	int32               GetStanding(uint32 Faction);
	int32               GetBaseStanding(uint32 Faction);
	void                SetStanding(uint32 Faction, int32 Value);
	void                SetAtWar(uint32 Faction, bool Set);
	bool                IsAtWar(uint32 Faction);
	Standing            GetStandingRank(uint32 Faction);
	bool                IsHostileBasedOnReputation(FactionDBC * dbc);
	void                UpdateInrangeSetsBasedOnReputation();
	void                Reputation_OnKilledUnit(UnitPointer pUnit, bool InnerLoop);
	void                Reputation_OnTalk(FactionDBC * dbc);
	static Standing     GetReputationRankFromStanding(int32 Standing_);
	
	bool titanGrip;
	void ResetTitansGrip();
	
    /************************************************************************/
    /* Factions                                                             */
    /************************************************************************/
	void smsg_InitialFactions();
	uint32 GetFactionId();
    // factions variables
    int32 pctReputationMod;

    /************************************************************************/
    /* PVP                                                                  */
    /************************************************************************/
	HEARTHSTONE_INLINE uint8 GetPVPRank()
	{
		return (uint8)((GetUInt32Value(PLAYER_BYTES_3) >> 24) & 0xFF);
	}
	HEARTHSTONE_INLINE void SetPVPRank(int newrank)
	{
		SetUInt32Value(PLAYER_BYTES_3, ((GetUInt32Value(PLAYER_BYTES_3) & 0x00FFFFFF) | (uint8(newrank) << 24)));
	}
	uint32 GetMaxPersonalRating();


    /************************************************************************/
    /* Groups                                                               */
    /************************************************************************/
	void                SetInviter(uint32 pInviter) { m_GroupInviter = pInviter; }
	HEARTHSTONE_INLINE uint32       GetInviter() { return m_GroupInviter; }
	HEARTHSTONE_INLINE bool         InGroup() { return (m_playerInfo->m_Group != NULL && !m_GroupInviter); }
	bool                IsGroupLeader()
	{
		if(m_playerInfo->m_Group != NULL)
		{
			if(m_playerInfo->m_Group->GetLeader() == m_playerInfo)
				return true;
		}
		return false;
	}
	HEARTHSTONE_INLINE int          HasBeenInvited() { return m_GroupInviter != 0; }
	HEARTHSTONE_INLINE Group*       GetGroup() { return m_playerInfo ? m_playerInfo->m_Group : NULL; }
	HEARTHSTONE_INLINE int8		   GetSubGroup() { return m_playerInfo->subGroup; }
    bool                IsGroupMember(PlayerPointer plyr);
	HEARTHSTONE_INLINE bool         IsBanned()
	{
		if(m_banned)
		{
			if(m_banned < 100 || (uint32)UNIXTIME < m_banned)
				return true;
		}
		return false;
	}
    HEARTHSTONE_INLINE void         SetBanned() { m_banned = 4;}
	HEARTHSTONE_INLINE void         SetBanned(string Reason) { m_banned = 4; m_banreason = Reason;}
	HEARTHSTONE_INLINE void         SetBanned(uint32 timestamp, string& Reason) { m_banned = timestamp; m_banreason = Reason; }
	HEARTHSTONE_INLINE void         UnSetBanned() { m_banned = 0; }
	HEARTHSTONE_INLINE string       GetBanReason() {return m_banreason;}

	void SetGuardHostileFlag(bool val) { if(val) SetFlag(PLAYER_FLAGS, PLAYER_FLAG_UNKNOWN2); else RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_UNKNOWN2); UpdateOppFactionSet(); }
	void CreateResetGuardHostileFlagEvent()
	{
		event_RemoveEvents( EVENT_GUARD_HOSTILE );
		sEventMgr.AddEvent(TO_PLAYER(shared_from_this()), &Player::SetGuardHostileFlag, false, EVENT_GUARD_HOSTILE, 10000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);	
	}

	uint32 m_hasInRangeGuards;

    /************************************************************************/
    /* Guilds                                                               */
    /************************************************************************/
	HEARTHSTONE_INLINE  bool        IsInGuild() {return (m_uint32Values[PLAYER_GUILDID] != 0) ? true : false;}
	HEARTHSTONE_INLINE uint32       GetGuildId() { return m_uint32Values[PLAYER_GUILDID]; }
	void                SetGuildId(uint32 guildId);
	HEARTHSTONE_INLINE uint32       GetGuildRank() { return m_uint32Values[PLAYER_GUILDRANK]; }
	void                SetGuildRank(uint32 guildRank);
	uint32              GetGuildInvitersGuid() { return m_invitersGuid; }
	void                SetGuildInvitersGuid( uint32 guid ) { m_invitersGuid = guid; }
	void                UnSetGuildInvitersGuid() { m_invitersGuid = 0; }
  
    /************************************************************************/
    /* Duel                                                                 */
    /************************************************************************/
    void                RequestDuel(PlayerPointer pTarget);
	void                DuelBoundaryTest();
	void                EndDuel(uint8 WinCondition);
	void                DuelCountdown();
	void                SetDuelStatus(uint8 status) { m_duelStatus = status; }
	HEARTHSTONE_INLINE uint8        GetDuelStatus() { return m_duelStatus; }
	void                SetDuelState(uint8 state) { m_duelState = state; }
	HEARTHSTONE_INLINE uint8        GetDuelState() { return m_duelState; }
    // duel variables
    PlayerPointer             DuelingWith;

    /************************************************************************/
    /* Trade                                                                */
    /************************************************************************/
	void                SendTradeUpdate(void);
	void         ResetTradeVariables()
	{
		mTradeGold = 0;
		for(uint8 i = 0; i < 7; ++i)
			mTradeItems[i] = NULLITEM;

		mTradeStatus = 0;
		mTradeTarget = 0;
		m_tradeSequence = 2;
	}
	
    /************************************************************************/
    /* Pets                                                                 */
    /************************************************************************/
	HEARTHSTONE_INLINE void			SetSummon(PetPointer pet) { m_Summon = pet; }
	HEARTHSTONE_INLINE PetPointer			GetSummon(void) { return m_Summon; }
	uint32						GeneratePetNumber(void);
	void						RemovePlayerPet(uint32 pet_number);
	HEARTHSTONE_INLINE void			AddPlayerPet(PlayerPet* pet, uint32 index) { m_Pets[index] = pet; }
	HEARTHSTONE_INLINE PlayerPet*	GetPlayerPet(uint32 idx)
	{
		std::map<uint32, PlayerPet*>::iterator itr = m_Pets.find(idx);
		if(itr != m_Pets.end()) return itr->second;
		else
			return NULL;
	}
	void						SpawnPet(uint32 pet_number);
	void						DespawnPet();
	uint32						GetFirstPetNumber(void)
	{
		if(m_Pets.size() == 0) return 0;
		std::map<uint32, PlayerPet*>::iterator itr = m_Pets.begin();
		return itr->first;
	}
	HEARTHSTONE_INLINE PlayerPet*	GetFirstPet(void) { return GetPlayerPet(GetFirstPetNumber()); }
	HEARTHSTONE_INLINE void			SetStableSlotCount(uint8 count) { m_StableSlotCount = count; }
	HEARTHSTONE_INLINE uint8			GetStableSlotCount(void) { return m_StableSlotCount; }
	uint32						GetUnstabledPetNumber(void)
	{
		if(m_Pets.size() == 0) return 0;
		std::map<uint32, PlayerPet*>::iterator itr = m_Pets.begin();
		for(;itr != m_Pets.end();itr++)
			if(itr->second->stablestate == STABLE_STATE_ACTIVE)
				return itr->first;
		return 0;
	}
	void						EventSummonPet(PetPointer new_pet); //if we charmed or simply summoned a pet, this function should get called
	void						EventDismissPet(); //if pet/charm died or whatever happned we should call this function

    /************************************************************************/
    /* Item Interface                                                       */
    /************************************************************************/
	HEARTHSTONE_INLINE ItemInterface* GetItemInterface() { return m_ItemInterface; } // Player Inventory Item storage
	HEARTHSTONE_INLINE void         ApplyItemMods(ItemPointer item, int8 slot, bool apply,bool justdrokedown=false) {  _ApplyItemMods(item, slot, apply,justdrokedown); }
    // item interface variables
    ItemInterface *     m_ItemInterface;

	HEARTHSTONE_INLINE AchievementInterface* GetAchievementInterface() { return m_achievementInterface; }
	AchievementInterface * m_achievementInterface;
	
    /************************************************************************/
    /* Loot                                                                 */
    /************************************************************************/
	HEARTHSTONE_INLINE const uint64& GetLootGUID() const { return m_lootGuid; }
	HEARTHSTONE_INLINE void         SetLootGUID(const uint64 &guid) { m_lootGuid = guid; }
	void                SendLoot(uint64 guid,uint8 loot_type);
    // loot variables
    uint64              m_lootGuid;
    uint64              m_currentLoot;
    bool                m_insigniaTaken;

    /************************************************************************/
    /* World Session                                                        */
    /************************************************************************/
	HEARTHSTONE_INLINE WorldSession* GetSession() const { return m_session; }
	void SetSession(WorldSession *s) { m_session = s; }
	void SetBindPoint(float x, float y, float z, uint32 m, uint32 v) { m_bind_pos_x = x; m_bind_pos_y = y; m_bind_pos_z = z; m_bind_mapid = m; m_bind_zoneid = v;}
	void SendDelayedPacket(WorldPacket *data, bool bDeleteOnSend)
	{
		if(data == NULL) return;
		if(GetSession() != NULL) GetSession()->SendPacket(data);
		if(bDeleteOnSend) delete data;
	}
	float offhand_dmg_mod;
	float GetSpellTimeMod(uint32 id);
	int GetSpellDamageMod(uint32 id);
	int32 GetSpellManaMod(uint32 id);
	
	// Talents
	// These functions build a specific type of A9 packet
	uint32 __fastcall BuildCreateUpdateBlockForPlayer( ByteBuffer *data, PlayerPointer target );
	void DestroyForPlayer( PlayerPointer target ) const;
	void SetTalentHearthOfWildPCT(int value){hearth_of_wild_pct=value;}
	void EventTalentHearthOfWildChange(bool apply);
	void SendDualSpecPurchase();
	
	std::list<LoginAura> loginauras;

    std::set<uint32> OnMeleeAuras;

    /************************************************************************/
    /* Player loading and savings                                           */
    /* Serialize character to db                                            */
    /************************************************************************/
	void SaveToDB(bool bNewCharacter);
	void SaveAuras(stringstream&);
	bool LoadFromDB(uint32 guid);
	void LoadFromDBProc(QueryResultVector & results);

	void LoadNamesFromDB(uint32 guid);
	bool m_FirstLogin;

    /************************************************************************/
    /* Death system                                                         */
    /************************************************************************/
	void SpawnCorpseBones();
	CorpsePointer CreateCorpse();
	void KillPlayer();
	void ResurrectPlayer(PlayerPointer pResurrector);
	void BuildPlayerRepop();
	CorpsePointer RepopRequestedPlayer();
	
	// silly event handler
	void EventRepopRequestedPlayer() { RepopRequestedPlayer(); }
	
	void DeathDurabilityLoss(double percent);
	void RepopAtGraveyard(float ox, float oy, float oz, uint32 mapid);
	
    /************************************************************************/
    /* Movement system                                                      */
    /************************************************************************/
	void SetMovement(uint8 pType, uint32 flag);
	void SetPlayerSpeed(uint8 SpeedType, float value);
	float GetPlayerSpeed(){return m_runSpeed;}
	uint8 m_currentMovement;
	bool m_isMoving;
	uint8 m_isWaterWalking;
	//Invisibility stuff
	bool m_isGmInvisible;
	
    /************************************************************************/
    /* Channel stuff                                                        */
    /************************************************************************/
	void JoinedChannel(Channel *c);
	void LeftChannel(Channel *c);
	void CleanupChannels();
	//Attack stuff
	void EventAttackStart();
	void EventAttackStop();
	void EventAttackUpdateSpeed() { }
	void EventDeath();
	//Note:ModSkillLine -> value+=amt;ModSkillMax -->value=amt; --wierd
	float GetSkillUpChance(uint32 id);
	//HEARTHSTONE_INLINE std::list<struct skilllines>getSkillLines() { return m_skilllines; }
	float SpellCrtiticalStrikeRatingBonus;
	float SpellHasteRatingBonus;
	void UpdateAttackSpeed();
	void UpdateChances();
	void UpdateStats();
	void UpdateHit(int32 hit);
   
	bool canCast(SpellEntry *m_spellInfo);
	HEARTHSTONE_INLINE float GetBlockFromSpell() { return m_blockfromspell; }
	HEARTHSTONE_INLINE float GetSpellCritFromSpell() { return m_spellcritfromspell; }
	HEARTHSTONE_INLINE float GetHitFromMeleeSpell() { return m_hitfrommeleespell; }
	HEARTHSTONE_INLINE float GetHitFromSpell() { return m_hitfromspell; }
	HEARTHSTONE_INLINE float GetParryFromSpell() { return m_parryfromspell; }
	HEARTHSTONE_INLINE float GetDodgeFromSpell() { return m_dodgefromspell; }
	void SetBlockFromSpell(float value) { m_blockfromspell = value; }
	void SetSpellCritFromSpell(float value) { m_spellcritfromspell = value; }
	void SetParryFromSpell(float value) { m_parryfromspell = value; }
	void SetDodgeFromSpell(float value) { m_dodgefromspell = value; }
	void SetHitFromMeleeSpell(float value) { m_hitfrommeleespell = value; }
	void SetHitFromSpell(float value) { m_hitfromspell = value; }
	HEARTHSTONE_INLINE int32 GetHealthFromSpell() { return m_healthfromspell; }
	HEARTHSTONE_INLINE uint32 GetManaFromSpell() { return m_manafromspell; }
	void SetHealthFromSpell(int32 value) { m_healthfromspell = value;}
	void SetManaFromSpell(uint32 value) { m_manafromspell = value;}
	uint32 CalcTalentResetCost(uint32 resetnum);
	void SendTalentResetConfirm();
	void SendPetUntrainConfirm();
	uint32 GetTalentResetTimes() { return m_talentresettimes; }
	HEARTHSTONE_INLINE void SetTalentResetTimes(uint32 value) { m_talentresettimes = value; }
	void SetPlayerStatus(uint8 pStatus) { m_status = pStatus; }
	HEARTHSTONE_INLINE uint8 GetPlayerStatus() { return m_status; }
	const float& GetBindPositionX( ) const { return m_bind_pos_x; }
	const float& GetBindPositionY( ) const { return m_bind_pos_y; }
	const float& GetBindPositionZ( ) const { return m_bind_pos_z; }
	const uint32& GetBindMapId( ) const { return m_bind_mapid; }
	const uint32& GetBindZoneId( ) const { return m_bind_zoneid; }
	HEARTHSTONE_INLINE uint8 GetShapeShift()
	{
		return GetByte(UNIT_FIELD_BYTES_2,3);
	}

	
	void delayAttackTimer(int32 delay)
	{
		if(!delay)
			return;

		m_attackTimer += delay;
		m_attackTimer_1 += delay;
	}
	
	void SetShapeShift(uint8 ss);

	uint32 m_furorChance;

    //Showing Units WayPoints
	AIInterface* waypointunit;
	
	uint32 m_nextSave;
	//Tutorials
	uint32 GetTutorialInt(uint32 intId );
	void SetTutorialInt(uint32 intId, uint32 value);
	//Base stats calculations
	//void CalcBaseStats();
	// Rest
	uint32 SubtractRestXP(uint32 amount);
	void AddCalculatedRestXP(uint32 seconds);
	void ApplyPlayerRestState(bool apply);
	void UpdateRestState();

	bool m_noFallDamage;
	float z_axisposition;
	int32 m_safeFall;
	// Gossip
	GossipMenu* CurrentGossipMenu;
	void CleanupGossipMenu();
	void Gossip_Complete();
	int m_lifetapbonus;
	uint32 m_lastShotTime;
	
	bool m_bUnlimitedBreath;
	uint32 m_UnderwaterTime;
	uint32 m_UnderwaterState;
	uint32 m_SwimmingTime;
	uint32 m_BreathDamageTimer;
	// Visible objects
	bool CanSee(ObjectPointer obj);
	HEARTHSTONE_INLINE bool IsVisible(ObjectPointer pObj) { return !(m_visibleObjects.find(pObj) == m_visibleObjects.end()); }
	void AddInRangeObject(ObjectPointer pObj);
	void OnRemoveInRangeObject(ObjectPointer pObj);
	void ClearInRangeSet();
	HEARTHSTONE_INLINE void AddVisibleObject(ObjectPointer pObj) { m_visibleObjects.insert(pObj); }
	HEARTHSTONE_INLINE void RemoveVisibleObject(ObjectPointer pObj) { m_visibleObjects.erase(pObj); }
	HEARTHSTONE_INLINE void RemoveVisibleObject(InRangeSet::iterator itr) { m_visibleObjects.erase(itr); }
	HEARTHSTONE_INLINE InRangeSet::iterator FindVisible(ObjectPointer obj) { return m_visibleObjects.find(obj); }
	HEARTHSTONE_INLINE void RemoveIfVisible(ObjectPointer obj)
	{
		InRangeSet::iterator itr = m_visibleObjects.find(obj);
		if(itr == m_visibleObjects.end())
			return;

		m_visibleObjects.erase(obj);
		PushOutOfRange(obj->GetNewGUID());
	}

	HEARTHSTONE_INLINE bool GetVisibility(ObjectPointer obj, InRangeSet::iterator *itr)
	{
		*itr = m_visibleObjects.find(obj);
		return ((*itr) != m_visibleObjects.end());
	}

	HEARTHSTONE_INLINE InRangeSet::iterator GetVisibleSetBegin() { return m_visibleObjects.begin(); }
	HEARTHSTONE_INLINE InRangeSet::iterator GetVisibleSetEnd() { return m_visibleObjects.end(); }
	
	//Transporters
	bool m_lockTransportVariables;
	uint64 m_TransporterGUID;
	float m_TransporterX;
	float m_TransporterY;
	float m_TransporterZ;
	float m_TransporterO;
	float m_TransporterUnk;
	// Misc
	void EventReduceDrunk(bool full);
	bool m_AllowAreaTriggerPort;
	void EventAllowTiggerPort(bool enable);
	float m_rangedattackspeedmod;
	float m_meleeattackspeedmod;
	uint32 m_modblockabsorbvalue;
	uint32 m_modblockvaluefromspells;
	void SendInitialLogonPackets();
	void Reset_Spells();
	void LearnTalent(uint32 talent_id, uint32 requested_rank);
	void Reset_Talents();
	void Reset_ToLevel1();
	void RetroactiveCompleteQuests();

	uint32 GetBGQueueSlotByBGType(uint32 type);
	uint32 HasBGQueueSlotOfType(uint32 type);

	// Battlegrounds xD
	BattlegroundPointer m_bg;
	BattlegroundPointer m_pendingBattleground[3];
	uint32 m_bgSlot;
	bool m_bgRatedQueue;
	uint32 m_bgEntryPointMap;
	float m_bgEntryPointX;	
	float m_bgEntryPointY;
	float m_bgEntryPointZ;
	float m_bgEntryPointO;
	int32 m_bgEntryPointInstance;
	bool m_bgHasFlag;
	bool m_bgIsQueued[3];
	uint32 m_bgQueueType[3];
	uint32 m_bgQueueInstanceId[3];
	uint32 m_bgQueueTime[3];
	uint32 m_bgFlagIneligible;

	bool HasBattlegroundQueueSlot();

	uint32 GetBGQueueSlot();

	void EventRepeatSpell();
	void EventCastRepeatedSpell(uint32 spellid, UnitPointer target);
	int32 CanShootRangedWeapon(uint32 spellid, UnitPointer target, bool autoshot);
	uint32 m_AutoShotDuration;
	uint32 m_AutoShotAttackTimer;
	bool m_onAutoShot;
	uint64 m_AutoShotTarget;
	SpellEntry *m_AutoShotSpell;
	void _InitialReputation();
	void UpdateNearbyGameObjects();
	void EventMassSummonReset() { m_massSummonEnabled = false; }

	bool m_massSummonEnabled;

	uint32 m_moltenFuryDamageIncreasePct;
	
	void CalcResistance(uint32 type);
	HEARTHSTONE_INLINE float res_M_crit_get(){return m_resist_critical[0];}
	HEARTHSTONE_INLINE void res_M_crit_set(float newvalue){m_resist_critical[0]=newvalue;}
	HEARTHSTONE_INLINE float res_R_crit_get(){return m_resist_critical[1];}
	HEARTHSTONE_INLINE void res_R_crit_set(float newvalue){m_resist_critical[1]=newvalue;}
	uint32 FlatResistanceModifierPos[7];
	uint32 FlatResistanceModifierNeg[7];
	uint32 BaseResistanceModPctPos[7];
	uint32 BaseResistanceModPctNeg[7];
	uint32 ResistanceModPctPos[7];
	uint32 ResistanceModPctNeg[7];
	float m_resist_critical[2];//when we are a victim we can have talents to decrease chance for critical hit. This is a negative value and it's added to critchances
	float m_resist_hit[3]; // 0 = melee; 1= ranged; 2=spells
	float SpellDmgDoneByAttribute[5][7];
	float SpellHealDoneByAttribute[5][7];
	uint32 m_modphyscritdmgPCT;
	uint32 m_RootedCritChanceBonus; // Class Script Override: Shatter

	uint32 m_ModInterrMRegenPCT;
	int32 m_ModInterrMRegen;
	float m_RegenManaOnSpellResist;
	uint32 m_casted_amount[7]; //Last casted spells amounts. Need for some spells. Like Ignite etc. DOesn't count HoTs and DoTs. Only directs
	
	uint32 FlatStatModPos[5];
	uint32 FlatStatModNeg[5];
	uint32 StatModPctPos[5];
	uint32 StatModPctNeg[5];
	uint32 TotalStatModPctPos[5];
	uint32 TotalStatModPctNeg[5];
	int32 IncreaseDamageByType[12]; //mod dmg by creature type
	float IncreaseDamageByTypePCT[12];
	float IncreaseCricticalByTypePCT[12];
	int32 DetectedRange;
	float PctIgnoreRegenModifier;
	uint32 m_retainedrage;
/*	
	union {
		float mRatingToPct[37];
		uint32 mRatingToPoint[37]; //block, skill.. cant be decimal values
	};
*/
	HEARTHSTONE_INLINE uint32* GetPlayedtime() { return m_playedtime; };
	void CalcStat(uint32 t);
	HEARTHSTONE_INLINE float CalcRating(uint32 index) { return CalcPercentForRating(index, m_uint32Values[index]); };
	float CalcPercentForRating(uint32 index, uint32 rating);
	void RecalcAllRatings();
	void RegenerateMana(bool is_interrupted);
	void RegenerateHealth(bool inCombat);
	void RegenerateEnergy();
	void LoseRage(int32 value);
	void LooseRunic(int32 value);
	void LoosePower(uint32 powerField, int32 value);
	
    uint32 SoulStone;
	uint32 SoulStoneReceiver;
	void removeSoulStone();

    HEARTHSTONE_INLINE uint32 GetSoulStoneReceiver(){return SoulStoneReceiver;}
    HEARTHSTONE_INLINE void SetSoulStoneReceiver(uint32 StoneGUID){SoulStoneReceiver = StoneGUID;}
    HEARTHSTONE_INLINE uint32 GetSoulStone(){return SoulStone;}
    HEARTHSTONE_INLINE void SetSoulStone(uint32 StoneID){SoulStone = StoneID;}

	bool bReincarnation;

	map<uint32, WeaponModifier> damagedone;
	map<uint32, WeaponModifier> tocritchance;
	uint32 Seal;
	uint32 judgespell;
	int32 rageFromDamageDealt;
	// GameObject commands
	GameObjectPointer m_GM_SelectedGO;
	
#ifndef CLUSTERING
	void _Relocate(uint32 mapid,const LocationVector & v, bool sendpending, bool force_new_world, uint32 instance_id);
#else
	void RelocateCallback(uint32 instance_were_going_to);
#endif
	void AddItemsToWorld();
	void RemoveItemsFromWorld();
	
	uint32 m_ShapeShifted;
	uint32 m_MountSpellId;

	HEARTHSTONE_INLINE bool IsMounted() {return (m_MountSpellId!=0 ? true : false); }
	
	bool bHasBindDialogOpen;
	bool bGMTagOn;
	uint32 TrackingSpell;
	void _EventCharmAttack();
	void _Warn(const char *message);
	void _Kick();
	void _Disconnect();
	void Kick(uint32 delay = 0);
	void SoftDisconnect();
	uint32 m_KickDelay;
	UnitPointer m_CurrentCharm;
	TransporterPointer m_CurrentTransporter;
	
	ObjectPointer GetSummonedObject () {return m_SummonedObject;};
	void SetSummonedObject (ObjectPointer t_SummonedObject) {m_SummonedObject = t_SummonedObject;};
	uint32 roll;

	void ClearCooldownsOnLine(uint32 skill_line, uint32 called_from);
	void ResetAllCooldowns();
	void ClearCooldownForSpell(uint32 spell_id);

	bool bProcessPending;
	Mutex _bufferS;
	void PushUpdateData(ByteBuffer *data, uint32 updatecount);
	void PushUpdateData(StackBuffer *data, uint32 updatecount);
    void PushCreationData(ByteBuffer *data, uint32 updatecount);
	void PushOutOfRange(const WoWGuid & guid);
	void ProcessPendingUpdates(ByteBuffer *pBuildBuffer, ByteBuffer *pCompressionBuffer);
	bool __fastcall CompressAndSendUpdateBuffer(uint32 size, const uint8* update_buffer, ByteBuffer *pCompressionBuffer);
	void ClearAllPendingUpdates();
	
	uint32 GetArmorProficiency() { return armor_proficiency; }
	uint32 GetWeaponProficiency() { return weapon_proficiency; }

	void ResetHeartbeatCoords();

	// speedhack buster!
	LocationVector						m_lastHeartbeatPosition;
	float								m_lastHeartbeatV; // velocity
	uint32								m_startMoveTime;	// time
	uint32								m_lastMovementPacketTimestamp;
	int32								m_heartbeatDisable;
	uint32								m_lastMoveTime;
	bool 								m_speedChangeInProgress;
	uint32								m_flyHackChances;

	void AddSplinePacket(uint64 guid, ByteBuffer* packet);
	ByteBuffer* GetAndRemoveSplinePacket(uint64 guid);
	void ClearSplinePackets();
	bool ExitInstance();
	void SaveEntryPoint(uint32 mapId);
	bool CooldownCheat;
	bool CastTimeCheat;
	bool GodModeCheat;
	bool PowerCheat;
	bool FlyCheat;
	void ZoneUpdate(uint32 ZoneId);
	HEARTHSTONE_INLINE uint32 GetAreaID() { return m_AreaID; }
	void SetAreaID(uint32 area) { m_AreaID = area; m_areaDBC = dbcArea.LookupEntryForced(m_AreaID); }
	HEARTHSTONE_INLINE AreaTable *GetAreaDBC() { return m_areaDBC; }
	
	
	std::string Lfgcomment;
	uint16 LfgDungeonId[3];
	uint8 LfgType[3];
	uint16 LfmDungeonId;
	uint8 LfmType;
	bool m_Autojoin;
	bool m_AutoAddMem;
	void StopMirrorTimer(uint32 Type);
	BGScore m_bgScore;
	uint32 m_bgTeam;
	void UpdateChanceFields();
	//Honor Variables
	time_t m_fallDisabledUntil;
	uint32 m_honorToday;
	uint32 m_honorYesterday;
	
	void RolloverHonor();
	uint32 m_honorPoints;
	uint32 m_honorRolloverTime;
	uint32 m_killsToday;
	uint32 m_killsYesterday;
	uint32 m_killsLifetime;
	uint32 m_arenaPoints;
	bool m_honorless;
	uint32 m_lastSeenWeather;
	unordered_set<ObjectPointer > m_visibleFarsightObjects;
	void EventTeleport(uint32 mapid, float x, float y, float z, float o);
	void EventTeleport(uint32 mapid, float x, float y, float z)
	{
		EventTeleport(mapid, x, y, z, 0.0f);
	}
	void ApplyLevelInfo(LevelInfo* Info, uint32 Level);
	void BroadcastMessage(const char* Format, ...);
	map<uint32, set<uint32> > SummonSpells;
	map<uint32, PetSpellMap*> PetSpells;
	void AddSummonSpell(uint32 Entry, uint32 SpellID);
	void RemoveSummonSpell(uint32 Entry, uint32 SpellID);
	set<uint32>* GetSummonSpells(uint32 Entry);
	LockedQueue<WorldPacket*> delayedPackets;
	set<PlayerPointer  > gmTargets;
	uint32 m_UnderwaterMaxTime;
	uint32 m_UnderwaterLastDmg;
	HEARTHSTONE_INLINE void setMyCorpse(CorpsePointer corpse) { myCorpse = corpse; }
	HEARTHSTONE_INLINE CorpsePointer getMyCorpse() { return myCorpse; }

	uint32 m_resurrectHealth, m_resurrectMana;
	uint32 resurrector;
	LocationVector m_resurrectLoction;
	bool blinked;
	uint16 m_speedhackChances;
	uint16 m_cheatEngineChances;
	uint32 m_explorationTimer;
	// DBC stuff
	CharRaceEntry * myRace;
	CharClassEntry * myClass;
	UnitPointer linkTarget;
	bool stack_cheat;
	bool triggerpass_cheat;
	bool SafeTeleport(uint32 MapID, uint32 InstanceID, float X, float Y, float Z, float O);
	bool SafeTeleport(uint32 MapID, uint32 InstanceID, LocationVector vec);
	void SafeTeleport(MapMgrPointer mgr, LocationVector vec);
	void EjectFromInstance();
	bool raidgrouponlysent;
	
	void EventSafeTeleport(uint32 MapID, uint32 InstanceID, LocationVector vec)
	{
		SafeTeleport(MapID, InstanceID, vec);
	}

	/*****************
	  PVP Stuff
	******************/
	uint32 m_pvpTimer;

	//! Do this on /pvp off
	HEARTHSTONE_INLINE void ResetPvPTimer();
	//! Stop the timer for pvp off
	HEARTHSTONE_INLINE void StopPvPTimer() { RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_PVP_TIMER); m_pvpTimer = 0; }
	
	//! Called at login to add the honorless buff, etc.
	void LoginPvPSetup();
	//! Update our pvp area (called when zone changes)
	void UpdatePvPArea();
	//! PvP Toggle (called on /pvp)
	void PvPToggle();

	HEARTHSTONE_INLINE uint32 LastHonorResetTime() const { return m_lastHonorResetTime; }
	HEARTHSTONE_INLINE void LastHonorResetTime(uint32 val) { m_lastHonorResetTime = val; }
	uint32 OnlineTime;
	bool tutorialsDirty;
	LevelInfo * lvlinfo;
	void CalculateBaseStats();
	uint32 load_health;
	uint32 load_mana;
	void CompleteLoading();
	set<SpellEntry *> castSpellAtLogin;
	void OnPushToWorld();
	void OnPrePushToWorld();
	void OnWorldPortAck();
	uint32 m_TeleportState;
	set<UnitPointer > visiblityChangableSet;
	bool m_beingPushed;
	bool CanSignCharter(Charter * charter, PlayerPointer requester);
	uint32 m_FlyingAura;
	stringstream LoadAuras;
	bool resend_speed;
	bool rename_pending;
	uint32 iInstanceType;
	HEARTHSTONE_INLINE void SetName(string& name) { m_name = name; }
	// spell to (delay, last time)
	
	FactionReputation * reputationByListId[128];
	
	uint64 m_comboTarget;
	int8 m_comboPoints;
	bool m_retainComboPoints;
	int8 m_spellcomboPoints; // rogue talent Ruthlessness will change combopoints while consuming them. solutions 1) add post cast prochandling, 2) delay adding the CP
	void UpdateComboPoints();

	HEARTHSTONE_INLINE void AddComboPoints(uint64 target, uint8 count)
	{
        if(m_comboTarget == target)
			m_comboPoints += count;
		else
		{
			m_comboTarget = target;
			m_comboPoints = count;
		}
		UpdateComboPoints();
	}

	HEARTHSTONE_INLINE void NullComboPoints() { if(!m_retainComboPoints) { m_comboTarget = 0; m_comboPoints = 0; m_spellcomboPoints=0; } UpdateComboPoints(); }
	uint32 m_speedChangeCounter;

	// HACKKKKK
	uint32 m_lastCheatDeath;
	uint32 m_cheatDeathRank;

	void SendAreaTriggerMessage(const char * message, ...);
        
	// Trade Target
	//PlayerPointer getTradeTarget() {return mTradeTarget;};

	HEARTHSTONE_INLINE PlayerPointer GetTradeTarget()
	{
		if(!IsInWorld()) return NULLPLR;
		return m_mapMgr->GetPlayer((uint32)mTradeTarget);
	}

	ItemPointer getTradeItem(uint32 slot) {return mTradeItems[slot];};
        
	// Water level related stuff (they are public because they need to be accessed fast)
	// Nose level of the character (needed for proper breathing)
	float m_noseLevel;

	/* Mind Control */
	void Possess(UnitPointer pTarget);
	void UnPossess();

	/* Last Speeds */
	HEARTHSTONE_INLINE void UpdateLastSpeeds()
	{
		m_lastRunSpeed = m_runSpeed;
		m_lastRunBackSpeed = m_backWalkSpeed;
		m_lastSwimSpeed = m_swimSpeed;
		m_lastRunBackSpeed = m_backSwimSpeed;
		m_lastFlySpeed = m_flySpeed;
	}

	void RemoteRevive()
	{
		ResurrectPlayer(NULLPLR);
		SetMovement(MOVE_UNROOT, 5);
		SetPlayerSpeed(RUN, (float)7);
		SetPlayerSpeed(SWIM, (float)4.9);
		SetMovement(MOVE_LAND_WALK, 8);
		SetUInt32Value(UNIT_FIELD_HEALTH, GetUInt32Value(UNIT_FIELD_MAXHEALTH) );
	}

	void ResetSpeedHack();
	void DelaySpeedHack(uint32 ms);

	float m_WeaponSubClassDamagePct[21];

	LocationVector m_last_group_position;
	int32 m_rap_mod_pct;
	void SummonRequest(uint32 Requestor, uint32 ZoneID, uint32 MapID, uint32 InstanceID, const LocationVector & Position);
	uint8 m_lastMoveType;
#ifdef OPTIMIZED_PLAYER_SAVING
	void save_LevelXP();
	void save_Skills();
	void save_ExploreData();
	void save_Gold();
	void save_Misc();
	void save_PositionHP();
	void save_BindPosition();
	void save_Honor();
	void save_EntryPoint();
	void save_Taxi();
	void save_Transporter();
	void save_Spells();
	void save_Actions();
	void save_Reputation();
	void save_Auras();
	void save_InstanceType();
	void save_Zone();
	void save_PVP();
#endif

#ifdef CLUSTERING
	void EventRemoveAndDelete();
	void PackPlayerData(ByteBuffer & data);
	bool UnpackPlayerData(ByteBuffer & data);
#endif

	CreaturePointer m_tempSummon;
	bool m_deathVision;
	SpellEntry * last_heal_spell;
	LocationVector m_sentTeleportPosition;

	void RemoveFromBattlegroundQueue(uint32 queueSlot, bool forced = false);
	void FullHPMP();
	uint32 m_arenateaminviteguid;

    /************************************************************************/
    /* Spell Packet wrapper Please keep this separated                      */
    /************************************************************************/
    void SendLevelupInfo(uint32 level, uint32 Hp, uint32 Mana, uint32 Stat0, uint32 Stat1, uint32 Stat2, uint32 Stat3, uint32 Stat4);
    void SendLogXPGain(uint64 guid, uint32 NormalXP, uint32 RestedXP, bool type);
    void SendEnvironmentalDamageLog(const uint64 & guid, uint8 type, uint32 damage);
	void SendWorldStateUpdate(uint32 WorldState, uint32 Value);
	void SendCastResult(uint32 SpellId, uint8 ErrorMessage, uint8 MultiCast, uint32 Extra);
	void Gossip_SendPOI(float X, float Y, uint32 Icon, uint32 Flags, uint32 Data, const char* Name);
    /************************************************************************/
    /* End of SpellPacket wrapper                                           */
    /************************************************************************/

	Mailbox* m_mailBox;
	bool m_waterwalk;
	bool m_setwaterwalk;
	bool m_setflycheat;
	uint64 m_areaSpiritHealer_guid;
	bool m_finishingmovesdodge;

	HEARTHSTONE_INLINE bool IsAttacking() {return m_attacking; }

	static void InitVisibleUpdateBits();
	static UpdateMask m_visibleUpdateMask;

	void CopyAndSendDelayedPacket(WorldPacket * data);
	void PartLFGChannel();

	uint32 GetLastLoginTime() { return 	m_timeLogoff; };

	//Current value of Feral Attack Power from items
	int32 m_feralAP;

protected:
	uint32 m_timeLogoff;
	LocationVector m_summonPos;
	uint32 m_summonInstanceId;
	uint32 m_summonMapId;
	uint32 m_summoner;

	uint32 iActivePet;
	void _SetCreateBits(UpdateMask *updateMask, PlayerPointer target) const;
	void _SetUpdateBits(UpdateMask *updateMask, PlayerPointer target) const;

	/* Update system components */
	ByteBuffer bUpdateBuffer;
    ByteBuffer bCreationBuffer;
	uint32 mUpdateCount;
    uint32 mCreationCount;
	uint32 mOutOfRangeIdCount;
	ByteBuffer mOutOfRangeIds;
	SplineMap _splineMap;
	/* End update system */

	void _LoadTutorials(QueryResult * result);
	void _SaveTutorials(QueryBuffer * buf);

	void _SaveInventory(bool firstsave);

	void _SaveQuestLogEntry(QueryBuffer * buf);
	void _LoadQuestLogEntry(QueryResult * result);

	void _LoadSkills(QueryResult * result);
	void _SaveSkillsToDB(QueryBuffer * buf);

	void _LoadSpells(QueryResult * result);
	void _SaveSpellsToDB(QueryBuffer * buf);

	void _LoadTalents(QueryResult * result);
	void _SaveTalentsToDB(QueryBuffer * buf);

	void _LoadGlyphs(QueryResult * result);
	void _SaveGlyphsToDB(QueryBuffer * buf);

	void _LoadPet(QueryResult * result);
	void _LoadPetNo();
	void _LoadPetSpells(QueryResult * result);
	void _SavePet(QueryBuffer * buf);
	void _SavePetSpells(QueryBuffer * buf);
	void _ApplyItemMods( ItemPointer item, int8 slot, bool apply, bool justdrokedown = false, bool skip_stat_apply = false );
	void _EventAttack( bool offhand );
	void _EventExploration();

	// Water level related stuff
	void SetNoseLevel();

	/************************************************************************/
	/* Trade																*/
	/************************************************************************/
	ItemPointer mTradeItems[7];
	uint32 mTradeGold;
	uint32 mTradeTarget;
	uint32 mTradeStatus;
	uint32 m_tradeSequence;

    /************************************************************************/
    /* Player Class systems, info and misc things                           */
    /************************************************************************/
    PlayerCreateInfo *info;
	uint32      m_AttackMsgTimer;	// "too far away" and "wrong facing" timer
	bool        m_attacking;
	std::string m_name;	// max 21 character name
	uint32      m_Tutorials[8];

    // Character Ban
	uint32      m_banned;
	string      m_banreason;
	uint32      m_AreaID;
	AreaTable  *m_areaDBC;
	PetPointer        m_Summon;
	uint32      m_PetNumberMax;
	std::map<uint32, PlayerPet*> m_Pets;
	
    uint32      m_invitersGuid; // It is guild inviters guid ,0 when its not used
    

    // bind
	float m_bind_pos_x;
	float m_bind_pos_y;
	float m_bind_pos_z;
	uint32 m_bind_mapid;
	uint32 m_bind_zoneid;
	std::list<ItemSet> m_itemsets;
	//Duel
	uint32 m_duelCountdownTimer;
	uint8 m_duelStatus;
	uint8 m_duelState;
	// Played time
	uint32 m_playedtime[3];
	uint8 m_isResting;
	uint8 m_restState;
	uint32 m_restAmount;
	//combat mods
	float m_blockfromspell;
	float m_blockfromspellPCT;
	float m_critfromspell;
	float m_spellcritfromspell;
	float m_dodgefromspell;
	float m_parryfromspell;
	float m_hitfromspell;
	float m_hitfrommeleespell;
	//stats mods
	int32 m_healthfromspell;
	uint32 m_manafromspell;
	uint32 m_healthfromitems;
	uint32 m_manafromitems;
	
	uint32 armor_proficiency;
	uint32 weapon_proficiency;
	// Talents
	uint32 m_talentresettimes;
	// STATUS
	uint8 m_status;
	// guid of current selection
	uint64 m_curSelection;
	// Raid
	uint8 m_targetIcon;
	//Player Action Bar
	ActionButton mActions[PLAYER_ACTION_BUTTON_SIZE];
	// Player Reputation
	ReputationMap m_reputation;
	// Pointer to this char's game client
	WorldSession *m_session;
	// Channels
	std::set<uint32> m_channels;
	// Visible objects
	unordered_set<ObjectPointer > m_visibleObjects;
	// Groups/Raids
	uint32 m_GroupInviter;
	uint8 m_StableSlotCount;

    // Fishing related
	ObjectPointer m_SummonedObject;

    // other system
	CorpsePointer    myCorpse;

	uint32      m_lastHonorResetTime;
	uint32      _fields[PLAYER_END];
	uint32	    trigger_on_stun;        //bah, warrior talent but this will not get triggered on triggered spells if used on proc so i'm forced to used a special variable
	uint32	    trigger_on_stun_chance; //also using this for mage "Frostbite" talent
	int			hearth_of_wild_pct;		//druid hearth of wild talent used on shapeshifting. We eighter know what is last talent level or memo on learn

	uint32 m_team;
	float       m_lastRunSpeed;
	float       m_lastRunBackSpeed;
	float       m_lastSwimSpeed;
	float       m_lastBackSwimSpeed;
	float       m_lastFlySpeed;

	uint32 m_mountCheckTimer;
	void RemovePendingPlayer();
public:
#ifdef ENABLE_COMPRESSED_MOVEMENT
	void EventDumpCompressedMovement();
	void AppendMovementData(uint32 op, uint32 sz, const uint8* data);
	Mutex m_movementBufferLock;
	ByteBuffer m_movementBuffer;
#endif

	void addDeletedSpell(uint32 id) { mDeletedSpells.insert( id ); }

	map<uint32, uint32> m_forcedReactions;

	uint32 m_speedhackCheckTimer;
	void _SpeedhackCheck();		// save a call to getMSTime() yes i am a stingy bastard

	uint32 m_flyhackCheckTimer;
	bool IsFlyHackEligible();
	void _FlyhackCheck();

	bool m_passOnLoot;
	bool m_changingMaps;

	/************************************************************************/
	/* SOCIAL                                                               */
	/************************************************************************/
private:
	/* we may have multiple threads on this(chat) - burlex */
	Mutex m_socialLock;
	map<uint32, char*> m_friends;
	set<uint32> m_ignores;
	set<uint32> m_hasFriendList;

	void Social_SendFriendList(uint32 flag);
	
	void Social_AddFriend(const char * name, const char * note);
	void Social_RemoveFriend(uint32 guid);
	
	void Social_AddIgnore(const char * name);
	void Social_RemoveIgnore(uint32 guid);

	void Social_SetNote(uint32 guid, const char * note);

public:
	bool Social_IsIgnoring(PlayerInfo * m_info);
	bool Social_IsIgnoring(uint32 guid);

	void Social_TellFriendsOnline();
	void Social_TellFriendsOffline();

	/************************************************************************/
	/* end social                                                           */
	/************************************************************************/

	PlayerInfo * m_playerInfo;
	uint32 m_skipCastCheck[3];  // spell group relation of spell types that should ignore some cancast checks
	bool m_castFilterEnabled;
	uint32 m_castFilter[3];	// spell group relation of only spells that player can currently cast 
	uint32 m_outStealthDamageBonusPct;
	uint32 m_outStealthDamageBonusPeriod;
	uint32 m_outStealthDamageBonusTimer;

	uint32 m_vampiricEmbrace;
	uint32 m_vampiricTouch;
	void VampiricSpell(uint32 dmg, UnitPointer pTarget);

	// grounding totem
	AuraPointer m_magnetAura;

	// spirit of redemption
	bool m_canCastSpellsWhileDead;

	// area update for worldstates, etc.
	void ForceAreaUpdate();

	// mage invisibility
	bool m_mageInvisibility;

	HEARTHSTONE_INLINE bool HasKnownTitle( int32 title )
	{
		if(title < 1 || title > TITLE_END)
			return false;  // Title doesn't exist
		if(title < 64)
			return ( GetUInt64Value( PLAYER__FIELD_KNOWN_TITLES ) & uint64(1) << title ) != (uint64) 0;
		else
			return ( GetUInt64Value( PLAYER__FIELD_KNOWN_TITLES1 ) & uint64(1) << (title - 64) ) != (uint64) 0;
	}

	void SetKnownTitle( int32 title, bool set );

	// debuffs
	bool mWeakenedSoul;
	bool mForbearance;
	bool mHypothermia;

	// Talent Specs
	uint16 m_maxTalentPoints;
	uint16 GetMaxTalentPoints();
	void ApplySpec(uint8 spec, bool init);
	void ApplyTalent(uint32 spellId);
	void RemoveTalent(uint32 spellid);
	uint8 m_talentSpecsCount;
	uint8 m_talentActiveSpec;
	struct PlayerSpec
	{
		std::map<uint32, uint8> talents;	// map of <talentId, talentRank>
		uint16  glyphs[GLYPHS_COUNT];
	};
	PlayerSpec m_specs[MAX_SPEC_COUNT];

	// Glyphs
	void UnapplyGlyph(uint32 slot);
	uint8 SetGlyph(uint32 slot, uint32 glyphId);
	void InitGlyphSlots();
	void InitGlyphsForLevel();
	// Runes
	uint8 m_runes[6];
	uint8 m_runemask;

	void ConvertRune(uint8 index, uint8 value);
	void ScheduleRuneRefresh(uint8 index, bool forceDeathRune = false);

	bool CanUseRunes(uint8 blood, uint8 frost, uint8 unholy);
	void UseRunes(uint8 blood, uint8 frost, uint8 unholy, SpellEntry * pSpell = NULL);
	uint8 TheoreticalUseRunes(uint8 blood, uint8 frost, uint8 unholy);

	uint32 m_deathRuneMasteryChance;

private:
	// Stuff for "Talent Inspect"
	#define TALENT_INSPECT_BYTES 71
	uint8 m_talentInspectBuffer[TALENT_INSPECT_BYTES];

public:
	HEARTHSTONE_INLINE const uint8 *GetTalentInspectBuffer() { return m_talentInspectBuffer; }
	void UpdateTalentInspectBuffer();
	static void InitializeTalentInspectSupport();

	// loooooot
	void GenerateLoot(CorpsePointer pCorpse);
};

class SkillIterator
{
	SkillMap::iterator m_itr;
	SkillMap::iterator m_endItr;
	bool m_searchInProgress;
	PlayerPointer m_target;
public:
	SkillIterator(PlayerPointer target) : m_searchInProgress(false),m_target(target) {}
	~SkillIterator() { if(m_searchInProgress) { EndSearch(); } if(m_target) { m_target = NULLPLR; } }

	void BeginSearch()
	{
		// iteminterface doesn't use mutexes, maybe it should :P
		ASSERT(!m_searchInProgress);
		m_itr = m_target->m_skills.begin();
		m_endItr = m_target->m_skills.end();
		m_searchInProgress=true;
	}

	void EndSearch()
	{
		// nothing here either
		ASSERT(m_searchInProgress);
		m_searchInProgress=false;
	}

	PlayerSkill* operator*() const
	{
		return &m_itr->second;
	}

	PlayerSkill* operator->() const
	{
		return &m_itr->second;
	}

	void Increment()
	{
		if(!m_searchInProgress)
			BeginSearch();

		if(m_itr==m_endItr)
			return;

		++m_itr;
	}

	HEARTHSTONE_INLINE PlayerSkill* Grab() { return &m_itr->second; }
	HEARTHSTONE_INLINE bool End() { return (m_itr==m_endItr)?true:false; }
};

#ifdef ENABLE_COMPRESSED_MOVEMENT

class CMovementCompressorThread : public ThreadContext
{
	bool running;
	Mutex m_listLock;
	set<PlayerPointer  > m_players;
public:
	CMovementCompressorThread() { running = true; }

	void AddPlayer(PlayerPointer pPlayer);
	void RemovePlayer(PlayerPointer pPlayer);

	void OnShutdown() { running = false; }
	bool run();
};

extern CMovementCompressorThread * MovementCompressor;

#endif

#endif
