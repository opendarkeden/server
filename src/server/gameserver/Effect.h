//////////////////////////////////////////////////////////////////////////////
// Filename	: Effect.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Object.h"
#include "Timeval.h"

class Item;
class Creature;
class Zone;

//////////////////////////////////////////////////////////////////////////////
// class Effect;
//
// ���������� ����Ʈ�� ũ��ó, ��, ������ � ���� �ð��Ŀ� �Ͼ��
// ���� ���� ȿ������ �ǹ��Ѵ�.
//
// ����, ��ü�� ���� �ð� �Ŀ� �������� ������� ���̳�, ���� ������
// �ɸ� Ÿ�Ͽ� ũ��ó�� �ö󰡼� �ߵ��� �Ǵ� �� ��� ����Ʈ�� �����ȴ�.
// ����, ���� ������ �����ۿ� �ɷ��ִ� ���� ���� ����Ʈ�� �����ȴ�.
//
// ���� Ŭ�������� affect(), unaffect() �޽�带 �����ؼ� �پ���
// ȿ���� ǥ���ϵ��� �Ѵ�.
//
// *CAUTION*
//
// Ÿ�� ���� ���� �ִ� ����Ʈ�� ��ü�� �پ��ִ� ����Ʈ�� ����� ���� �ٸ���.
// Ÿ�� ���� ����Ʈ�� Ÿ�Ͽ� �Ҽӵ�����, ��ü�� ����Ʈ�� ���� ����
// ����Ʈ �Ŵ������� �Ҽӵȴ�.
//
// void SkillHandler::execute(...)
// {
// 		Effect* pEffect = new Effect(...);
// 		ObjectRegistery & objectRegistery;
// 		objectRegistery.registerObject(pEffect);
// 		pZone->getTile(x,y)->addEffect(pEffect);
// }
//
// void Tile::addEffect(Effect* pEffect)
// {
// 		for(each creature in tile)
// 			pEffect->affect(*itr);
// }
//
// void Tile::deleteEffect(ObjectID_t objectID)
// {
// 		Effect* pEffect = getObject(objectID);
// 		for(each creature in tile)
// 			pEffect->unaffect(*itr);
// }
//
// void EffectManager::deleteExpiredEffects()
// {
// 		for(each effect in effect manager) {
//			if(effect is expired) {
//				if(tile effect)
//					tile.deleteEffect(objectID);
//				delete pEffect;
//			}
//		}
// }
//////////////////////////////////////////////////////////////////////////////

class Effect : public Object 
{
public:
	enum EffectClass 
	  {
	    ////////////////////////////////////////////////////////////
	    // ���� �߰��Ǵ� ����� ���� �ؿ� �־��ּ���!!!!!!!!!!!
	    ////////////////////////////////////////////////////////////
	    EFFECT_CLASS_LIGHT = 0,				   // 0
	    EFFECT_CLASS_DETECT_HIDDEN,			   // 1
	    EFFECT_CLASS_PROTECTION_FROM_POISON,	  // 2
	    EFFECT_CLASS_PROTECTION_FROM_CURSE,	   // 3
	    EFFECT_CLASS_PROTECTION_FROM_ACID,		// 4
	    EFFECT_CLASS_BLESS,					   // 5
	    EFFECT_CLASS_STRIKING,					// 6
	    EFFECT_CLASS_CONTINUAL_LIGHT,			 // 7
	    EFFECT_CLASS_DETECT_INVISIBILITY,		 // 8
	    EFFECT_CLASS_REGENERATION,				// 9
	    EFFECT_CLASS_AURA_SHIELD,				 // 10
	    EFFECT_CLASS_SAINT_AURA,				  // 11
	    EFFECT_CLASS_FLARE,					   // 12
	    EFFECT_CLASS_CROSS_COUNTER,			   // 13
	    EFFECT_CLASS_CHARGING_POWER,			  // 14
	    EFFECT_CLASS_LIGHTNING_HAND,			  // 15
	    EFFECT_CLASS_POTENTIAL_EXPLOSION,		 // 16
	    EFFECT_CLASS_DANCING_SWORD,			   // 17
	    EFFECT_CLASS_GHOST_BLADE,				 // 18
	    EFFECT_CLASS_HIDE,						// 19
	    EFFECT_CLASS_ACID_TOUCH,				  // 20
	    EFFECT_CLASS_POISON,					  // 21
	    EFFECT_CLASS_POISONOUS_HANDS,			 // 22
	    EFFECT_CLASS_BLOOD_DRAIN,				 // 23
	    EFFECT_CLASS_PARALYZE,					// 24
	    EFFECT_CLASS_DOOM,						// 25
	    EFFECT_CLASS_GREEN_POISON,				// 26
	    EFFECT_CLASS_YELLOW_POISON,			   // 27
	    EFFECT_CLASS_YELLOW_POISON_TO_CREATURE,   // 28
	    EFFECT_CLASS_DARKNESS,					// 29
	    EFFECT_CLASS_INVISIBILITY,				// 30
	    EFFECT_CLASS_ACID_SWAMP,				  // 31
	    EFFECT_CLASS_ACID_BALL,				   // 32
	    EFFECT_CLASS_GREEN_STALKER,			   // 33
	    EFFECT_CLASS_DARKBLUE_POISON,			 // 34
	    EFFECT_CLASS_DARKBLUE_POISON_TO_CREATURE, // 35
	    EFFECT_CLASS_TRANSFORM_TO_WOLF,		   // 36
	    EFFECT_CLASS_TRANSFORM_TO_BAT,			// 37
	    EFFECT_CLASS_RELOAD_TIMER,				// 38
	    EFFECT_CLASS_REVEALER,					// 39
	    EFFECT_CLASS_INSTALL,					 // 40
	    EFFECT_CLASS_FADE_OUT,					// 41
	    EFFECT_CLASS_SNIPING_MODE,			   // 42
	    EFFECT_CLASS_DECAY_CORPSE,				// 43
	    EFFECT_CLASS_DEAD_CREATURE,			   // 44
	    EFFECT_CLASS_SHUT_DOWN,				   // 45
	    EFFECT_CLASS_DECAY_ITEM,				  // 46
	    EFFECT_CLASS_HP_RECOVERY,				 // 47
	    EFFECT_CLASS_MP_RECOVERY,				 // 48
	    EFFECT_CLASS_SACRIFICE,				   // 49
	    EFFECT_CLASS_AFTERMATH,				   // 50
	    EFFECT_CLASS_ALIGNMENT_RECOVERY,		  // 51
	    EFFECT_CLASS_ENEMY_ERASE,				 // 52
	    EFFECT_CLASS_VAMPIRE_PORTAL,			  // 53
	    EFFECT_CLASS_SLAYER_PORTAL,			   // 54
	    EFFECT_CLASS_COMA,						// 55
	    EFFECT_CLASS_SEDUCTION,				   // 56
	    EFFECT_CLASS_EXPANSION,				   // 57
	    EFFECT_CLASS_MIRACLE_SHIELD,			  // 58
	    EFFECT_CLASS_BERSERKER,				   // 59
	    EFFECT_CLASS_TYPHOON,					 // 60
	    EFFECT_CLASS_MIND_CONTROL,				// 61
	    EFFECT_CLASS_ACTIVATION,				  // 62
	    EFFECT_CLASS_PEACE,					   // 63
	    EFFECT_CLASS_SANCTUARY,				   // 64
	    EFFECT_CLASS_REFLECTION,				  // 65
	    EFFECT_CLASS_HALLUCINATION,			   // 66
	    EFFECT_CLASS_CASKET,					  // 67
	    EFFECT_CLASS_DEATH,					   // 68
	    EFFECT_CLASS_PRECEDENCE,				  // 69
	    EFFECT_CLASS_RESTORE,					 // 70

	    // �̰� �̸� �ٲ��� �Ѵ�.
	    EFFECT_CLASS_CURE_CRITICAL_WOUNDS,		// 70

	    EFFECT_CLASS_EXTREME,					  // 71
	    EFFECT_CLASS_HYPNOSIS,					  // 72
	    EFFECT_CLASS_ARMAGEDDON,				  // 73
	    EFFECT_CLASS_SUMMON_BAT,				  // 74
	    EFFECT_CLASS_CHARM,						  // 75
	    EFFECT_CLASS_MEPHISTO,					  // 76

	    EFFECT_CLASS_ACID_STORM,				  // 77
	    EFFECT_CLASS_POISON_STORM,				// 78
	    EFFECT_CLASS_BLOODY_STORM,				// 79
	    EFFECT_CLASS_STORM_ACID,	   			  // 80
	    EFFECT_CLASS_STORM_POSION,				// 81
	    EFFECT_CLASS_STORM_BLOODY,				// 82

	    EFFECT_CLASS_ENERGY_DROP,					// 83
	    EFFECT_CLASS_ENERGY_DROP_TO_CREATURE,		// 84
	    EFFECT_CLASS_VIGOR_DROP,					// 85	
	    EFFECT_CLASS_VIGOR_DROP_TO_CREATURE,		// 86

	    EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS,			// 87

	    EFFECT_CLASS_TRANSPORT_ITEM,			// 88
	    EFFECT_CLASS_ADD_ITEM,					// 89

	    EFFECT_CLASS_SLAYER_RELIC,			  // 91
	    EFFECT_CLASS_VAMPIRE_RELIC,			 // 92
	    EFFECT_CLASS_HAS_SLAYER_RELIC,		  // 93
	    EFFECT_CLASS_HAS_VAMPIRE_RELIC,		 // 94
	    EFFECT_CLASS_INCRASE_ATTR,			  // 95

	    EFFECT_CLASS_HYMN,						// 96
	    EFFECT_CLASS_GATEWAY_MONSTER,			// 97

	    EFFECT_CLASS_OBSERVING_EYE,				// 98

	    EFFECT_CLASS_DELETE_ITEM,			   // 99
	    EFFECT_CLASS_ADD_MONSTER,			   // 100

	    EFFECT_CLASS_LOGIN_GUILD_MESSAGE,		// 101

	    EFFECT_CLASS_SLAYER_RELIC_TABLE,		// 102
	    EFFECT_CLASS_VAMPIRE_RELIC_TABLE,		// 103
	    EFFECT_CLASS_RELIC_LOCK,   				// 104
	    EFFECT_CLASS_RELIC_POSITION,			// 105

	    EFFECT_CLASS_GUILD_CHAT,				// 106

	    // by sigi. 2002.9.2
	    EFFECT_CLASS_MASTER_LAIR_PASS,			// 107
	    EFFECT_CLASS_NO_DAMAGE,					// 108
	    EFFECT_CLASS_GHOST,						// 109

	    // by sigi. 2002.9.10
	    EFFECT_CLASS_CONTINUAL_GROUND_ATTACK,	// 110
	    EFFECT_CLASS_GROUND_ATTACK,				// 111
	    EFFECT_CLASS_METEOR_STRIKE,				// 112

	    // by sigi. 2002.9.13
	    EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN,		// 113
	    EFFECT_CLASS_IMMUNE_TO_PARALYZE,		// 114
	    EFFECT_CLASS_IMMUNE_TO_POISON,			// 115
	    EFFECT_CLASS_IMMUNE_TO_ACID,			// 116
	    EFFECT_CLASS_IMMUNE_TO_CURSE,			// 117

	    // by sigi. 2002.9.14
	    EFFECT_CLASS_DECREASE_HP,				// 118
	    EFFECT_CLASS_INCREASE_HP,				// 119
		
	    // by sigi. 2002.9.27
	    EFFECT_CLASS_BLOODY_WALL,				// 120
	    EFFECT_CLASS_BLOODY_WALL_BLOCKED,		// 121
	    EFFECT_CLASS_BLOODY_SNAKE,			// 122

	    // by bezz. 2002.10.22
	    EFFECT_CLASS_SOUL_CHAIN,				// 123

	    // by sigi. 2002.11.7
	    EFFECT_CLASS_TRANSPORT_CREATURE,		// 124	- ����� ���� �ȵ�.

	    // by sigi. 2002.11.8
	    EFFECT_CLASS_GRAND_MASTER_SLAYER,		// 125

	    // by sigi. 2002.11.9
	    EFFECT_CLASS_GRAND_MASTER_VAMPIRE,		// 126
	    EFFECT_CLASS_LEVELUP_SLAYER,			// 127
	    EFFECT_CLASS_LEVELUP_VAMPIRE,			// 128

	    // 2002.12.10
	    EFFECT_CLASS_FIRE_CRACKER_1,			// 129
	    EFFECT_CLASS_FIRE_CRACKER_2,			// 130
	    EFFECT_CLASS_FIRE_CRACKER_3,			// 131

	    EFFECT_CLASS_KILL_AFTERMATH,	  		// 132

	    // 2002.12.12
	    EFFECT_CLASS_CLIENT_XMAS_TREE,			// 133

	    // 2002.12.26
	    EFFECT_CLASS_SHARP_SHIELD_1,			// 134
	    EFFECT_CLASS_SHARP_SHIELD_2,			// 135
	    EFFECT_CLASS_SHARP_SHIELD_3,			// 136
	    EFFECT_CLASS_SHARP_SHIELD_4,			// 137

	    EFFECT_CLASS_AIR_SHIELD_1,				// 138
	    EFFECT_CLASS_AIR_SHIELD_2,				// 139
	    EFFECT_CLASS_AIR_SHIELD_3,				// 140
	    EFFECT_CLASS_AIR_SHIELD_4,				// 141

	    EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM,		// 142
	    EFFECT_CLASS_GUN_SHOT_GUIDANCE_FIRE,	// 143
	    EFFECT_CLASS_GUN_SHOT_GUIDANCE_POINT,	// 144

	    EFFECT_CLASS_SLEEP,						// 145

	    EFFECT_CLASS_SPIRIT_GUARD_1,			// 146
	    EFFECT_CLASS_SPIRIT_GUARD_2,			// 147
	    EFFECT_CLASS_SPIRIT_GUARD_3,			// 148
	    EFFECT_CLASS_SPIRIT_GUARD_4,			// 149

	    // 2003. 1. 3
	    EFFECT_CLASS_TILE_STORM,				// 150

	    EFFECT_CLASS_HAS_BLOOD_BIBLE,			// 151
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_2,			// 152
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_3,			// 153
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_4,			// 154
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_5,			// 155
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_6,			// 156
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_7,			// 157
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_8,			// 158
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_9,			// 159
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_10,		// 160
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_11,		// 161
	    EFFECT_CLASS_HAS_BLOOD_BIBLE_12,		// 162

	    EFFECT_CLASS_SHRINE_GUARD,							// 163 
	    EFFECT_CLASS_SHRINE_GUARD_2,							// 164 
	    EFFECT_CLASS_SHRINE_GUARD_3,							// 165 
	    EFFECT_CLASS_SHRINE_GUARD_4,							// 166 
	    EFFECT_CLASS_SHRINE_GUARD_5,							// 167 
	    EFFECT_CLASS_SHRINE_GUARD_6,							// 168 
	    EFFECT_CLASS_SHRINE_GUARD_7,							// 169 
	    EFFECT_CLASS_SHRINE_GUARD_8,							// 170 
	    EFFECT_CLASS_SHRINE_GUARD_9,							// 171 
	    EFFECT_CLASS_SHRINE_GUARD_10,						   // 172 
	    EFFECT_CLASS_SHRINE_GUARD_11,						   // 173 
	    EFFECT_CLASS_SHRINE_GUARD_12,						   // 174 
 
	    EFFECT_CLASS_SHRINE_HOLY,							 // 175 
	    EFFECT_CLASS_SHRINE_HOLY_2,							 // 176 
	    EFFECT_CLASS_SHRINE_HOLY_3,							 // 177 
	    EFFECT_CLASS_SHRINE_HOLY_4,							 // 178 
	    EFFECT_CLASS_SHRINE_HOLY_5,							 // 179 
	    EFFECT_CLASS_SHRINE_HOLY_6,							 // 180 
	    EFFECT_CLASS_SHRINE_HOLY_7,							 // 181 
	    EFFECT_CLASS_SHRINE_HOLY_8,							 // 182 
	    EFFECT_CLASS_SHRINE_HOLY_9,							 // 183 
	    EFFECT_CLASS_SHRINE_HOLY_10,					// 184 
	    EFFECT_CLASS_SHRINE_HOLY_11,					// 185 
	    EFFECT_CLASS_SHRINE_HOLY_12,					// 186 
 
	    EFFECT_CLASS_SHRINE_GUARD_WARP,				 // 187		  ��ȣ���ܿ��� �����ɶ� 
	    EFFECT_CLASS_SHRINE_HOLY_WARP,				  // 188		  �������ܿ��� �����ɶ� 
	    EFFECT_CLASS_CHANGE_CASTLE_CHANGED,			 // 189 

	    EFFECT_CLASS_SHRINE_SHIELD,			 // 190 
	    EFFECT_CLASS_TOWER_SHIELD,			  // 191 

	    EFFECT_CLASS_TRANSPORT_ITEM_TO_CORPSE,			// 192
	    EFFECT_CLASS_ADD_ITEM_TO_CORPSE,				// 193
 
	    EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_ME,			// 194 ���� �������ִ� ���Ǽ����� �����ɶ� �Ӹ��� ����ִ�-_- ����Ʈ
	    EFFECT_CLASS_WARP_BLOOD_BIBLE_FROM_TILE,		// 195 ���� �������ִ� ���Ǽ����� �����ɶ� �� Ÿ�Ͽ� ����ִ� ����Ʈ

	    EFFECT_CLASS_WARP_HOLY_LAND_VAMPIRE,			// 196 �����̾ ��Ż�� �̵��Ҷ�
	    EFFECT_CLASS_WARP_HOLY_LAND_SLAYER,				// 197 �����̾ ��Ż�� �̵��Ҷ�

	    EFFECT_CLASS_HAS_CASTLE_SYMBOL,		 		// 198 
	    EFFECT_CLASS_HAS_CASTLE_SYMBOL_2,		 		// 199 
	    EFFECT_CLASS_HAS_CASTLE_SYMBOL_3,		 		// 200 
	    EFFECT_CLASS_HAS_CASTLE_SYMBOL_4,		 		// 201 

	    EFFECT_CLASS_INIT_ALL_STAT,		 			// 202 

	    EFFECT_CLASS_CASTLE_SHRINE_GUARD,		 		// 203 
	    EFFECT_CLASS_CASTLE_SHRINE_HOLY,		 		// 204 

	    EFFECT_CLASS_CASTLE_SHRINE_SLAYER_WARP,			// 205
	    EFFECT_CLASS_CASTLE_SHRINE_VAMPIRE_WARP,		// 206

	    EFFECT_CLASS_RACE_WAR_JOIN_TICKET,				// 207

	    EFFECT_CLASS_LOVE_CHAIN,						// 208

	    EFFECT_CLASS_PK_ZONE_REGEN,						// 209
	    EFFECT_CLASS_PK_ZONE_RESURRECTION,				// 210

	    EFFECT_CLASS_MAGIC_ELUSION,						// 211	��Ÿ�ν�
	    EFFECT_CLASS_POISON_MESH,						// 212	�׸�Ƽ�콺
	    EFFECT_CLASS_ILLUSION_OF_AVENGE,				// 213	��Ƽ����
	    EFFECT_CLASS_WILL_OF_LIFE,						// 214	��Ƹ�����

	    // �ű� ��ų Effect �߰�
	    EFFECT_CLASS_DENIAL_MAGIC,						// 215
	    EFFECT_CLASS_DENIAL_MAGIC_DAMAGED,				// 216
	    EFFECT_CLASS_REQUITAL,							// 217
	    EFFECT_CLASS_CONCEALMENT,						// 218

	    EFFECT_CLASS_DRAGON_FIRE_CRACKER,				// 219

	    EFFECT_CLASS_GRAND_MASTER_OUSTERS,				// 220

	    EFFECT_CLASS_FIRE_CRACKER_4,					// 221
	    EFFECT_CLASS_FIRE_CRACKER_VOLLEY_1,				// 222
	    EFFECT_CLASS_FIRE_CRACKER_VOLLEY_2,				// 223
	    EFFECT_CLASS_FIRE_CRACKER_VOLLEY_3,				// 224
	    EFFECT_CLASS_FIRE_CRACKER_VOLLEY_4,				// 225

	    EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_1,		// 226
	    EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_2,		// 227
	    EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_3,		// 228
	    EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_4,		// 229

	    EFFECT_CLASS_FIRE_CRACKER_STORM,				// 230
	    EFFECT_CLASS_TRANSLATION,						// 231

	    EFFECT_CLASS_LIGHTNESS,							// 232

	    EFFECT_CLASS_EVADE,								// 233
	    EFFECT_CLASS_BLUNTING,							// 234
	    EFFECT_CLASS_CROSS_GUARD,						// 235
	    EFFECT_CLASS_HANDS_OF_FIRE,						// 236
	    EFFECT_CLASS_PROMINENCE,						// 237
	    EFFECT_CLASS_RING_OF_FLARE,						// 238
	    EFFECT_CLASS_WATER_BARRIER,						// 239
	    EFFECT_CLASS_TENDRIL,							// 240
	    EFFECT_CLASS_GNOMES_WHISPER,					// 241

	    EFFECT_CLASS_ICE_FIELD,							// 242
	    EFFECT_CLASS_ICE_FIELD_TO_CREATURE,				// 243

	    EFFECT_CLASS_CANNOT_ABSORB_SOUL,				// 244
	    EFFECT_CLASS_SUMMON_SYLPH,						// 245

	    EFFECT_CLASS_LEVELUP_OUSTERS,					// 246
	    EFFECT_CLASS_BACK_STAB,							// 247

	    EFFECT_CLASS_PROMINENCE_2,						// 248
	    EFFECT_CLASS_PROMINENCE_3,						// 249

	    EFFECT_CLASS_RING_OF_FLARE_2,					// 250
	    EFFECT_CLASS_RING_OF_FLARE_3,					// 251

	    EFFECT_CLASS_BACK_STAB_2,						// 252
	    EFFECT_CLASS_BACK_STAB_3,						// 253

	    EFFECT_CLASS_FIRE_OF_SOUL_STONE,				// 254
	    EFFECT_CLASS_ICE_OF_SOUL_STONE,					// 255
	    EFFECT_CLASS_SAND_OF_SOUL_STONE,				// 256
	    EFFECT_CLASS_BLOCK_HEAD,						// 257

	    EFFECT_CLASS_LOUD,								// 258

	    EFFECT_CLASS_DIVINE_SPIRITS,					// 259
	    EFFECT_CLASS_REFINIUM_TICKET,					// 260

	    EFFECT_CLASS_CONTINUAL_BLOODY_WALL,				// 261
	    EFFECT_CLASS_DIVINE_GUIDANCE,					// 262

	    EFFECT_CLASS_JABBING_VEIN,						// 263
	    EFFECT_CLASS_BLAZE_WALK,						// 264

	    EFFECT_CLASS_HAS_FLAG,							// 265
	    EFFECT_CLASS_FLAG_INSERT,						// 266

	    EFFECT_CLASS_MUTE,								// 267

	    EFFECT_CLASS_DROP_FORCE,						// 268

	    EFFECT_CLASS_SLAYER_ONLY,						// 269
	    EFFECT_CLASS_VAMPIRE_ONLY,						// 270
	    EFFECT_CLASS_OUSTERS_ONLY,						// 271

	    EFFECT_CLASS_REDIANCE,							// 272
	    EFFECT_CLASS_HEART_CATALYST,					// 273

	    EFFECT_CLASS_WARP_HOLY_LAND_OUSTERS,			// 274 �ƿ콺��� ��Ż�� �̵��Ҷ�
	    EFFECT_CLASS_FAMILY_BONUS,						// 275 �йи� ����� ���ʽ�

	    EFFECT_CLASS_PROTECTION_FROM_BLOOD,				// 276
	    EFFECT_CLASS_ETERNITY,							// 277
	    EFFECT_CLASS_HAS_PET,							// 278

	    EFFECT_CLASS_ETERNITY_PAUSE,					// 279

	    EFFECT_CLASS_TRAP_INSTALLED,					// 280
	    EFFECT_CLASS_TRAP_TRIGGERED,					// 281 Ʈ���� �ɷ��� �� ����������(?) ����Ʈ
	    EFFECT_CLASS_TRAPPED,							// 282 ũ���İ� Ʈ���� �ɷ��ִ� ����Ʈ
	    EFFECT_CLASS_MERCY_GROUND,						// 283
	    EFFECT_CLASS_HOLY_ARMOR,						// 284

	    EFFECT_CLASS_TRANSFORM_TO_WERWOLF,				// 285
	    EFFECT_CLASS_HOWL,								// 286
	    EFFECT_CLASS_STONE_SKIN,						// 287

	    EFFECT_CLASS_GRAY_DARKNESS,							// 288
	    EFFECT_CLASS_STONE_SKIN_DAMAGED,				// 289

	    EFFECT_CLASS_ACID_ERUPTION,						// 290
	    EFFECT_CLASS_JUST_LOGIN,						// 291

	    EFFECT_CLASS_HAS_SWEEPER,						// 292
	    EFFECT_CLASS_HAS_SWEEPER_2,						// 293
	    EFFECT_CLASS_HAS_SWEEPER_3,						// 294
	    EFFECT_CLASS_HAS_SWEEPER_4,						// 295
	    EFFECT_CLASS_HAS_SWEEPER_5,						// 296
	    EFFECT_CLASS_HAS_SWEEPER_6,						// 297
	    EFFECT_CLASS_HAS_SWEEPER_7,						// 298
	    EFFECT_CLASS_HAS_SWEEPER_8,						// 299
	    EFFECT_CLASS_HAS_SWEEPER_9,						// 300
	    EFFECT_CLASS_HAS_SWEEPER_10,					// 301
	    EFFECT_CLASS_HAS_SWEEPER_11,					// 302
	    EFFECT_CLASS_HAS_SWEEPER_12,					// 303

	    EFFECT_CLASS_KEEP_SWEEPER,						// 304
	    EFFECT_CLASS_KEEP_SWEEPER_2,					// 305
	    EFFECT_CLASS_KEEP_SWEEPER_3,					// 306
	    EFFECT_CLASS_KEEP_SWEEPER_4,					// 307
	    EFFECT_CLASS_KEEP_SWEEPER_5,					// 308
	    EFFECT_CLASS_KEEP_SWEEPER_6,					// 309
	    EFFECT_CLASS_KEEP_SWEEPER_7,					// 310
	    EFFECT_CLASS_KEEP_SWEEPER_8,					// 311
	    EFFECT_CLASS_KEEP_SWEEPER_9,					// 312
	    EFFECT_CLASS_KEEP_SWEEPER_10,					// 313
	    EFFECT_CLASS_KEEP_SWEEPER_11,					// 314
	    EFFECT_CLASS_KEEP_SWEEPER_12,					// 315

	    EFFECT_CLASS_SLAYER_REGEN_ZONE,					// 316
	    EFFECT_CLASS_VAMPIRE_REGEN_ZONE,				// 317
	    EFFECT_CLASS_OUSTERS_REGEN_ZONE,				// 318
	    EFFECT_CLASS_DEFAULT_REGEN_ZONE,				// 319

	    EFFECT_CLASS_SLAYER_TRYING_1,					// 320
	    EFFECT_CLASS_SLAYER_TRYING_2,					// 321
	    EFFECT_CLASS_SLAYER_TRYING_3,					// 322

	    EFFECT_CLASS_VAMPIRE_TRYING_1,					// 323
	    EFFECT_CLASS_VAMPIRE_TRYING_2,					// 324
	    EFFECT_CLASS_VAMPIRE_TRYING_3,					// 325

	    EFFECT_CLASS_OUSTERS_TRYING_1,					// 326
	    EFFECT_CLASS_OUSTERS_TRYING_2,					// 327
	    EFFECT_CLASS_OUSTERS_TRYING_3,					// 328

	    EFFECT_CLASS_TRYING_POSITION,					// 329
	    EFFECT_CLASS_TRYING,							// 330

	    EFFECT_CLASS_CAPTURE_REGEN_ZONE,				// 331
	    EFFECT_CLASS_ON_BRIDGE,							// 332

	    EFFECT_CLASS_SUMMON_SYLPH_GREEN,				// 333
	    EFFECT_CLASS_SUMMON_SYLPH_ORANGE,				// 334
	    EFFECT_CLASS_SUMMON_SYLPH_RED,					// 335
	    EFFECT_CLASS_SUMMON_SYLPH_YELLOW,				// 336
	    EFFECT_CLASS_SUMMON_SYLPH_WHITE,				// 337
	    EFFECT_CLASS_SUMMON_SYLPH_BROWN,				// 338
	    EFFECT_CLASS_SUMMON_SYLPH_LILAC,				// 339
	    EFFECT_CLASS_SUMMON_SYLPH_BLACK,				// 340

	    EFFECT_CLASS_IMMUNE_TO_HALLUCINATION,			// 341
	    EFFECT_CLASS_PET_DISSECT,						// 342

	    EFFECT_CLASS_EXPLOSION_WATER,					// 343
	    EFFECT_CLASS_FROZEN_ARMOR,						// 344
	    EFFECT_CLASS_FROZEN_ARMOR_TO_ENEMY,				// 345

	    EFFECT_CLASS_REACTIVE_ARMOR,					// 346

	    EFFECT_CLASS_MAGNUM_SPEAR,						// 347
	    EFFECT_CLASS_HELLFIRE,							// 348
	    EFFECT_CLASS_HELLFIRE_TO_ENEMY,					// 349
	    EFFECT_CLASS_GROUND_BLESS,						// 350

	    EFFECT_CLASS_SHARP_CHAKRAM,						// 351
	    EFFECT_CLASS_DESTRUCTION_SPEAR,					// 352
	    EFFECT_CLASS_BLESS_FIRE,						// 353
	    EFFECT_CLASS_WATER_SHIELD,						// 354
	    EFFECT_CLASS_SAND_CROSS,						// 355

	    EFFECT_CLASS_GROUND_ELEMENTAL_AURA,				// 356
	    EFFECT_CLASS_FIRE_ELEMENTAL,					// 357
	    EFFECT_CLASS_WATER_ELEMENTAL,					// 358
	    EFFECT_CLASS_DISTANCE_BLITZ,					// 359

	    EFFECT_CLASS_GROUND_ELEMENTAL_CENTER,			// 360
	    EFFECT_CLASS_FIRE_ELEMENTAL_ATTACK,				// 361
	    EFFECT_CLASS_FIRE_ELEMENTAL_DAMAGED,			// 362

	    EFFECT_CLASS_WATER_ELEMENTAL_HEAL,				// 363
	    EFFECT_CLASS_WATER_ELEMENTAL_HEALED,			// 364

	    EFFECT_CLASS_DARKNESS_FORBIDDEN,				// 365
	    EFFECT_CLASS_VIEW_HP,							// 366

	    EFFECTSTATUS_BLACK_LARGE_SMOKE,				 // 367
	    EFFECTSTATUS_BLACK_HALL,						// 368
	    EFFECTSTATUS_BLACK_SMALL_SMOKE_1,			   // 369
	    EFFECTSTATUS_BLACK_SMALL_SMOKE_2,			   // 370
	    EFFECTSTATUS_BLACK_SMALL_SMOKE_3,			   // 371
	    EFFECTSTATUS_ELECTRIC_POST,						// 372

	    EFFECTSTATUS_GHOST_1,						   // 373
	    EFFECTSTATUS_GHOST_2,						   // 374

	    EFFECT_CLASS_LUCKY,								// 375
	    EFFECT_CLASS_MISFORTUNE,						// 376

	    EFFECT_CLASS_HAS_CASTLE_SYMBOL_5,				// 377
	    EFFECT_CLASS_HAS_CASTLE_SYMBOL_6,				// 378

	    EFFECT_CLASS_ICICLE_DROP,					   // 379
	    EFFECT_CLASS_ICICLE_DROP_SIGN,				  // 380

	    EFFECT_CLASS_ICICLE_AUGER,					  // 381
	    EFFECT_CLASS_ICICLE_AUGER_SIGN,				 // 382

	    EFFECT_CLASS_ICE_STICK_SW,					  // 383
	    EFFECT_CLASS_ICE_STICK_SW_SIGN,				 // 384

	    EFFECT_CLASS_ICE_STICK_SE,					  // 385
	    EFFECT_CLASS_ICE_STICK_SE_SIGN,				 // 386

	    EFFECT_CLASS_ICE_STICK_NE,					  // 387
	    EFFECT_CLASS_ICE_STICK_NE_SIGN,				 // 388

	    EFFECT_CLASS_ICE_STICK_NW,					  // 389
	    EFFECT_CLASS_ICE_STICK_NW_SIGN,				 // 390

	    EFFECT_CLASS_ICICLE_AUGER_LARGE,			  // 391
	    EFFECT_CLASS_ICICLE_AUGER_LARGE_SIGN,		 // 392

	    EFFECT_CLASS_WHITE_BLESS,					// 393
	    EFFECT_CLASS_BLINDNESS,						// 394
	    EFFECT_CLASS_CAN_ENTER_GDR_LAIR,			// 395

	    EFFECT_CLASS_SUMMON_GDR,					// 396
	    EFFECT_CLASS_GDR_SATELLITE,					// 397
	    EFFECT_CLASS_GDR_FLOATING,					// 398

	    EFFECT_CLASS_GRAND_MASTER_SLAYER_130,		// 399
	    EFFECT_CLASS_GRAND_MASTER_SLAYER_150,		// 400
	    EFFECT_CLASS_GRAND_MASTER_VAMPIRE_130,		// 401
	    EFFECT_CLASS_GRAND_MASTER_VAMPIRE_150,		// 402
	    EFFECT_CLASS_GRAND_MASTER_OUSTERS_130,		// 403
	    EFFECT_CLASS_GRAND_MASTER_OUSTERS_150,		// 404

	    EFFECT_CLASS_CAN_MODIFY_NICKNAME_0,			// 405
	    EFFECT_CLASS_CAN_MODIFY_PET_NICKNAME,		// 406

	    EFFECT_CLASS_GLACIER,						// 407
	    EFFECT_CLASS_ICE_HAIL,						// 408

	    EFFECT_CLASS_GOLD_MEDAL,					// 409

	    EFFECT_CLASS_PK_COUNTED,					// 410
	    EFFECT_CLASS_PUNISH_COUNTED,				// 411

	    EFFECT_CLASS_SIEGE_DEFENDER,				// 412	// ������ �����
	    EFFECT_CLASS_SIEGE_REINFORCE,				// 413	// ������ ����� ����

	    EFFECT_CLASS_SIEGE_ATTACKER_1,				// 414	// ������ ������ 1��
	    EFFECT_CLASS_SIEGE_ATTACKER_2,				// 415	// ������ ������ 2��
	    EFFECT_CLASS_SIEGE_ATTACKER_3,				// 416	// ������ ������ 3��
	    EFFECT_CLASS_SIEGE_ATTACKER_4,				// 417	// ������ ������ 4��
	    EFFECT_CLASS_SIEGE_ATTACKER_5,				// 418	// ������ ������ 5��

	    EFFECT_CLASS_SHARE_HP,						// 419	// HP �����ϱ�~

	    EFFECT_CLASS_LAND_MINE_EXPLOSION,			// 420	// ���帶�� ������ ����Ʈ
	    EFFECT_CLASS_CLAYMORE_EXPLOTION,			// 421	// ũ����� ������ ����Ʈ
	    EFFECT_CLASS_PLEASURE_EXPLOSION,			// 422	// �÷��� �����̼� ������ ����Ʈ
	    EFFECT_CLASS_TURRET_LASER,					// 423	// �ͷ� ������ 1Ÿ��
	    EFFECT_CLASS_TURRET_LASER_ATTACK,			// 424	// �ͷ� ������ ���� 1Ÿ�� (���������� ����)
	    EFFECT_CLASS_AUTO_TURRET,					// 425	// ���� �ͷ� ���ִ°�

	    EFFECT_CLASS_HIDE_TO_ATTACKER,				// 426	// ���� ���������� �� ���δ�.

	    EFFECT_CLASS_REPUTO_FACTUM,					// 427
	    EFFECT_CLASS_REPUTO_FACTUM_LAST,			// 428	// ��������Ʈ

	    EFFECT_CLASS_SWORD_OF_THOR,					// 429	// Ÿ�Ͽ� �پ ������ Į

	    EFFECT_CLASS_BURNING_SOL_CHARGE_1,			// 430
	    EFFECT_CLASS_BURNING_SOL_CHARGE_2,			// 431
	    EFFECT_CLASS_BURNING_SOL_CHARGE_3,			// 432
	    EFFECT_CLASS_BURNING_SOL_CHARGE_4,			// 433

	    EFFECT_CLASS_INSTALL_TURRET,				// 434
	    EFFECT_CLASS_WHITSUNTIDE,					// 435

	    EFFECT_CLASS_DRAGON_EYE,					// 436
	    EFFECT_CLASS_ROCKET_LAUNCHER,				// 437	// Ŭ���̾�Ʈ�� ����
	    EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER,		// 438
	    EFFECT_CLASS_INTIMATE_GRAIL,				// 439

	    EFFECT_CLASS_ICE_HORIZON,					// 440
	    EFEECT_CLASS_SET_AFIRE_ATTACK,				// 441
	    EFFECT_CLASS_FURY_OF_GNOME,					// 442
	    EFFECT_CLASS_FURY_OF_GNOME_MARK,			// 443
	    EFFECT_CLASS_SUMMON_MIGA_FIRE,				// 444	

	    EFFECT_CLASS_DRAGON_TORNADO,				// 445
	    EFFECT_CLASS_DRAGON_TORNADO_CHILD,			// 446
	    EFFECT_CLASS_HARPOON_BOMB,					// 447
	    EFFECT_CLASS_PASSING_HEAL,					// 448
	    EFFECT_CLASS_ABERRATION,					// 449
	    EFFECT_CLASS_HALO,							// 450
	    EFFECT_CLASS_FIERCE_FLAME,					// 451
	    EFFECT_CLASS_SHADOW,						// 452
	    EFFECT_CLASS_SHADOW_OF_STORM,				// 453

	    EFFECT_CLASS_BIKE_CRASH,					// 454
	    EFFECT_CLASS_DONATION_200501,				// 455
	    EFFECT_CLASS_BONUS_EXP,						// 456

	    EFFECT_CLASS_ADVANCEMENT_MASTSER_EFFECT_SLAYER,	// 457
	    EFFECT_CLASS_ADVANCEMENT_MASTSER_EFFECT_VAMPIRE,// 458
	    EFFECT_CLASS_ADVANCEMENT_MASTSER_EFFECT_OUSTERS,// 459

	    EFFECT_CLASS_DELETE_TILE,					// 460

	    EFFECT_CLASS_CAN_ENTER_SLAYER_PORTAL,		// 461
	    EFFECT_CLASS_CAN_ENTER_VAMPIRE_PORTAL,		// 462
	    EFFECT_CLASS_CAN_ENTER_OUSTERS_PORTAL,		// 463

	    EFFECT_CLASS_TILE_PORTAL,						// 464
	    // add by Coffee 2007-5-20
	    EFFECT_CLASS_BLOOD_BLLODY_SCARIFY,			// Ѫ֮��ӡ(��Ѫ��)
	    EFFECT_CLASS_BLOOD_CURSE,					// Ѫ֮�{��(��Ѫ��)
	    EFFECT_CLASS_SKILL_BOMB_CRASH_WALK_TO_ENEMY,  //465
	    EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM,		  // ���Ǻ�� Ч������ (����)
	    EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT,      // ���Ǻ�� Ч������ (����)
	    EFFECT_CLASS_SKILL_SATELLITE_BOMB_FIRE,          // ��ǹЧ��
	    EFFECT_CLASS_HEAVEN_GROUND,					 // ��ʦ������
	    EFFECT_CLASS_DUMMY_DRAKE,					 // ���׿˿���(ħ��)
	    EFFECT_CLASS_HYDRO_CONVERGENCE,				//  ����ˮ��
	    EFFECT_CLASS_SUMMON_CLAY,				//  Summon Clay  ճ���ٻ�    (ħ���¼��� ����)
	    EFFECT_CLASS_HETER_CHAKRAM,				//  Heter Chakram �Ĳ�������  (ħ���¼���  սʿ)


	    //add by viva
	    EFFECT_CLASS_XRL_Missile,	//XRL ը�ѵ���
	    EFFECTSTATUS_UNKOWN_VIVA2,
	    EFFECTSTATUS_UNKOWN_VIVA3,
	    EFFECTSTATUS_UNKOWN_VIVA4,

	    EFFECT_CLASS_Bramble_Halo,//Original Action:390 //�����⻷ //ף��
	    EFFECTSTATUS_UNKOWN_VIVA5, //EffectSpriteType:1134
	    EFFECT_CLASS_Rapid_Freeze,	//Original Action:396
	    EFFECT_CLASS_Penetrate_Wheel,	//Orginal Action : 393
	    EFFECTSTATUS_UNKOWN_VIVA6,
	    EFFECTSTATUS_VAMPIRE_TRANSFORM_TO_D_BAT,//Original Action : 409
	    EFFECTSTATUS_VAMPIRE_TRANSFORM_TO_D_ANGEL,//Original Action : 410
	    EFFECTSTATUS_SUMMON_SYLPH1,//�ٻ�����//ousters//Original Action : 247
	    EFFECTSTATUS_SUMMON_SYLPH2,
	    EFFECTSTATUS_UNKOWN_VIVA7,

	    EFFECT_CLASS_Fire_Meteor,
	    EFFECT_CLASS_MAX,
	    //end
	    // EFFECTSTATUS_MAX,

	    // EFFECT_CLASS_Bramble_Halo,
	    // EFFECT_CLASS_Fire_Meteor,
	    // EFFECT_CLASS_Penetrate_Wheel,
	    // EFFECT_CLASS_Rapid_Freeze,
	    // EFFECT_CLASS_XRL_Missile,	
	    // EFFECT_CLASS_MAX
	  };


// constructor/destructor
public:
	Effect() ;
	Effect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget, Turn_t delay) ;
	virtual ~Effect() ;
			

// methods from Object
public:
	virtual ObjectClass getObjectClass() const  { return OBJECT_CLASS_EFFECT; }
	virtual ObjectPriority getObjectPriority() const  { return OBJECT_PRIORITY_EFFECT; }
	virtual string toString() const  = 0;


// own methods
public:
	virtual EffectClass getEffectClass() const  = 0;
	virtual EffectClass getSendEffectClass() const  { return getEffectClass(); }

	// Client�� �ѷ�����ϴ� Effect�ΰ�? by sigi. 2002.11.14
	bool isBroadcastingEffect() { return m_bBroadcastingEffect; }
	void setBroadcastingEffect(bool bBroadcasting=true) { m_bBroadcastingEffect = bBroadcasting; }

	virtual void affect()  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Creature* pCreature)  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget)  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void affect(Item* pItem)  { throw UnsupportedError(__PRETTY_FUNCTION__);}
	
	virtual void unaffect(Item* pItem)  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	virtual void unaffect()  = 0;
	virtual void unaffect(Creature* pCreature)  { throw UnsupportedError(__PRETTY_FUNCTION__); } // ������ pure virtual�̾��µ� EffectRelicTable���� �ٲ��. by sigi
	virtual void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pTarget)  { throw UnsupportedError(__PRETTY_FUNCTION__); }
	

// get/set methods
public:
	Zone* getZone() const  { return m_pZone; }
	void setZone(Zone* pZone)  { m_pZone = pZone; }

	ZoneCoord_t getX() const  { return m_X; }
	ZoneCoord_t getY() const  { return m_Y; }
	void setX(ZoneCoord_t x)  { m_X = x; }
	void setY(ZoneCoord_t y)  { m_Y = y; }
	void setXY(ZoneCoord_t x, ZoneCoord_t y)  { m_X = x; m_Y = y; }

	Object* getTarget() const  { return m_pTarget; }
	void setTarget(Object* pTarget)  { m_pTarget = pTarget; }

	Timeval getNextTime() const  { return m_NextTime; }
	void setNextTime(Timeval tv)  { m_NextTime = tv; }
	void setNextTime(Turn_t delay) ;

	Timeval getDeadline() const  { return m_Deadline; }
	void setDeadline(Turn_t delay) ;

	Duration_t getRemainDuration() ;


// save/load members
public:
	virtual void create(const string & ownerID)  {}
	virtual void save(const string & ownerID)  {}
	virtual void destroy(const string & ownerID)  {}


////////////////////////////////////////////////////////////
// data members
////////////////////////////////////////////////////////////
protected:
	Zone*		m_pZone;	// target object�� ��ġ
	ZoneCoord_t  m_X;
	ZoneCoord_t  m_Y;
	Object*	  m_pTarget;  // target object - � ��ü�� �ɷ� �ִ°�? 
	Timeval	  m_NextTime; // ���� ���� �����ؾ� �ϴ� �ð�
	Timeval	  m_Deadline; // ���� �� ��ü�� �����ؾ� �ϴ°�?�� ��Ÿ���� �ð�
	
	// Client�� �ѷ�����ϴ� Effect�ΰ�? by sigi. 2002.11.14
	bool 		m_bBroadcastingEffect;
};

#endif
