//////////////////////////////////////////////////////////////////////////////
// Filename    : Skill.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_H__
#define __SKILL_H__

#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// 스킬 관련 상수들...
//////////////////////////////////////////////////////////////////////////////

const int ATTR_SAVE_DIVIDER        = 100;
const int SKILL_EXP_SAVE_DIVIDER   = 100;
const int DOMAIN_EXP_SAVE_DIVIDER  = 100;
const int VAMPIRE_EXP_SAVE_DIVIDER = 100;
const int FAME_SAVE_DIVIDER        = 100;
const int ALIGNMENT_SAVE_DIVIDER   = 100;

const int VAMPIRE_DAY_FACTOR       = 100;
const int VAMPIRE_DAWN_FACTOR      = 125;
const int VAMPIRE_DUSK_FACTOR      = 125;
const int VAMPIRE_NIGHT_FACTOR     = 150;

const int MONSTER_DAY_FACTOR       =  50;
const int MONSTER_DAWN_FACTOR      =  75;
const int MONSTER_DUSK_FACTOR      =  75;
const int MONSTER_NIGHT_FACTOR     = 100;

const int VampireTimebandFactor[4] = 
{
    125, // 새벽
    100, // 낮
    125, // 저녁
    150  // 밤
};

const int MonsterTimebandFactor[4] = 
{
    75, // 새벽
    50, // 낮
    75, // 저녁
    100 // 밤
};

const int AttrExpTimebandFactor[4] = 
{
    100, // 새벽
    100, // 낮
    100, // 저녁
    150  // 밤
};

const int DomainExpTimebandFactor[4] = 
{
    100, // 새벽
    100, // 낮
    100, // 저녁
    150  // 밤
};

//////////////////////////////////////////////////////////////////////////////
// SkillTypes enumerations
//////////////////////////////////////////////////////////////////////////////

enum SkillTypes 
{
    SKILL_ATTACK_MELEE = 0,						// 0
    SKILL_ATTACK_ARMS,							// 1
    SKILL_SELF,									// 2
    SKILL_TILE,									// 3
    SKILL_OBJECT,	    						// 4
    
    SKILL_DOUBLE_IMPACT,  					  	// 5
    SKILL_TRIPLE_SLASHER,				  	  	// 6
    SKILL_RAINBOW_SLASHER,					  	// 7
    SKILL_THUNDER_SPARK,	   				 	// 8
    SKILL_DANCING_SWORD,						// 9
    SKILL_CROSS_COUNTER,		   			 	// 10
    SKILL_FLASH_SLIDING,		  			  	// 11
    SKILL_LIGHTNING_HAND,	  					// 12
    SKILL_SNAKE_COMBO,	  	 				 	// 13
    SKILL_SWORD_WAVE,		  	 				// 14
    SKILL_DRAGON_RISING,		 			    // 15
    SKILL_FIVE_STORM_CRASH,	 				 	// 16
    SKILL_HEAVENS_SWORD,		  			  	// 17
    
    SKILL_SINGLE_BLOW,						    // 18
    SKILL_SPIRAL_SLAY,						    // 19
    SKILL_TRIPLE_BREAK,						    // 20
    SKILL_WILD_SMASH,						    // 21
    SKILL_GHOST_BLADE,							// 22
    SKILL_POTENTIAL_EXPLOSION,			  		// 23
    SKILL_SHADOW_WALK,			  			  	// 24
    SKILL_CHARGING_POWER,		  			  	// 25
    SKILL_HURRICANE_COMBO,	 				 	// 26
    SKILL_TORNADO_SEVER,		  			  	// 27
    SKILL_ARMAGEDDON_SLASHER,	  				// 28
    SKILL_SOUL_SHOCK,			   				// 29
    SKILL_SAINT_BLADE,			   			  	// 30
    
    SKILL_FAST_RELOAD,						    // 31
    SKILL_QUICK_FIRE,							// 32
    SKILL_SMG_MASTERY,							// 33
    SKILL_MULTI_SHOT,						    // 34
    SKILL_HEAD_SHOT,						    // 35
    SKILL_AR_MASTERY,							// 36
    SKILL_PIERCING,						    	// 37
    SKILL_SNIPING,						    	// 38
    SKILL_SG_MASTERY,							// 39
    SKILL_REVEALER,							    // 40
    SKILL_CREATE_BOMB,		 				    // 41
    SKILL_SR_MASTERY,							// 42
    SKILL_DISARM_MINE,						    // 43
    SKILL_INSTALL_MINE,						    // 44
    SKILL_CREATE_MINE,			  			    // 45
    
    SKILL_CREATE_HOLY_WATER, 			 		// 46
    SKILL_LIGHT,				      			// 47
    SKILL_DETECT_HIDDEN,	   	 				// 48
    SKILL_AURA_BALL,	     		 		 	// 49
    SKILL_BLESS,			       		 		// 50
    SKILL_CONTINUAL_LIGHT,	 			 		// 51
    SKILL_FLARE,								// 52
    SKILL_PURIFY,    							// 53
    SKILL_AURA_RING,		  	  		  		// 54
    SKILL_STRIKING,		      					// 55
    SKILL_DETECT_INVISIBILITY,					// 56
    SKILL_IDENTIFY,								// 57
    SKILL_AURA_SHIELD,	    					// 58
    SKILL_ENCHANT,			    			  	// 59
    SKILL_VISIBLE,			    			  	// 60
    SKILL_CHAIN_AURA,							// 61
    SKILL_SAINT_AURA,							// 62
    
    SKILL_CURE_LIGHT_WOUNDS,					// 63
    SKILL_CURE_POISON,							// 64
    SKILL_PROTECTION_FROM_POISON,				// 65
    SKILL_CAUSE_LIGHT_WOUNDS,					// 66
    SKILL_CURE_SERIOUS_WOUNDS,					// 67
    SKILL_REMOVE_CURSE,							// 68
    SKILL_PROTECTION_FROM_CURSE,				// 69
    SKILL_CAUSE_SERIOUS_WOUNDS,					// 70
    SKILL_CURE_CRITICAL_WOUNDS,					// 71
    SKILL_PROTECTION_FROM_ACID,					// 72
    SKILL_SACRIFICE,							// 73
    SKILL_CAUSE_CRITICAL_WOUNDS,				// 74
    SKILL_CURE_ALL,								// 75
    SKILL_REGENERATION,							// 76
    SKILL_MASS_CURE,							// 77
    SKILL_MASS_HEAL,							// 78
    
    SKILL_BLOOD_DRAIN,							// 79
    
    SKILL_POISONOUS_HANDS,						// 80
    SKILL_GREEN_POISON,							// 81
    SKILL_YELLOW_POISON,						// 82
    SKILL_DARKBLUE_POISON,						// 83
    SKILL_GREEN_STALKER,						// 84
    
    SKILL_ACID_TOUCH,							// 85
    SKILL_ACID_BOLT,							// 86
    SKILL_ACID_BALL,							// 87
    SKILL_ACID_SWAMP,							// 88
    
    SKILL_PARALYZE,								// 89
    SKILL_DOOM,									// 90
    SKILL_HALLUCINATION,						// 91
    SKILL_DEATH,								// 92
    
    SKILL_BLOODY_NAIL,							// 93
    SKILL_BLOODY_KNIFE,							// 94
    SKILL_BLOODY_BALL,							// 95
    SKILL_BLOODY_WALL,							// 96
    SKILL_BLOODY_SPEAR,							// 97
    
    SKILL_HIDE,									// 98
    SKILL_DARKNESS,								// 99
    SKILL_INVISIBILITY,							// 100
    SKILL_TRANSFORM_TO_WOLF,					// 101
    SKILL_TRANSFORM_TO_BAT,						// 102
    
    SKILL_SUMMON_WOLF,							// 103
    SKILL_SUMMON_CASKET,						// 104
    SKILL_RAISING_DEAD,							// 105
    SKILL_SUMMON_SERVANT,						// 106
    
    SKILL_UN_BURROW,							// 107
    SKILL_UN_TRANSFORM,							// 108
    SKILL_UN_INVISIBILITY,						// 109
    SKILL_THROW_HOLY_WATER,						// 110
    
    SKILL_EAT_CORPSE,							// 111
    SKILL_HOWL,									// 112
    
    SKILL_RESTORE,								// 113
    
    SKILL_BLOODY_MARKER,                        // 114
    SKILL_BLOODY_TUNNEL,                        // 115
    
    SKILL_SEDUCTION,							// 116
    SKILL_WIND_DIVIDER,							// 117
    SKILL_EARTHQUAKE,							// 118
    
    SKILL_RESURRECT,                            // 119
    SKILL_PRAYER,                               // 120
    SKILL_MEDITATION,                           // 121
    
    SKILL_THUNDER_BOLT,							// 122
    SKILL_EXPANSION, 							// 123
    SKILL_MIRACLE_SHIELD, 						// 124
    SKILL_THUNDER_FLASH,						// 125
    SKILL_MASSACRE,								// 126
    SKILL_INVINCIBLE,							// 127
    
    SKILL_BERSERKER,							// 128
    SKILL_MOONLIGHT_SEVER,						// 129
    SKILL_SHADOW_DANCING,						// 130
    SKILL_TYPHOON,								// 131
    SKILL_PSYCHOKINESIS,						// 132
    SKILL_EXTERMINATION,						// 133
    
    SKILL_MIND_CONTROL,							// 134
    SKILL_REVOLVING,							// 135
    SKILL_FATALITY,								// 136
    SKILL_BLITZ,								// 137
    
    SKILL_ACTIVATION,							// 138
    SKILL_PEACE,								// 139
    SKILL_ENERGY_DROP,							// 140
    SKILL_EXORCISM,								// 141
    
    SKILL_SANCTUARY,							// 142
    SKILL_REFLECTION,							// 143
    SKILL_ARMAGEDDON,							// 144
    
    SKILL_POISON_STRIKE,						// 145
    SKILL_POISON_STORM,							// 146
    SKILL_ACID_STRIKE,							// 147
    SKILL_ACID_STORM,							// 148
    SKILL_BLOODY_STRIKE,						// 149
    SKILL_BLOODY_STORM,							// 150
    
    // 임시로 추가 2002.2.22
    SKILL_SUMMON_BAT,							// 151
    SKILL_CHARM,								// 152
    SKILL_POLYMORPH,							// 153
    SKILL_MEPHISTO,								// 154
    SKILL_HYPNOSIS,								// 155
    SKILL_TRANSFUSION,							// 156
    SKILL_EXTREME,								// 157
    SKILL_BLOODY_WAVE,							// 158
    SKILL_THROW_BOMB,							// 159
    
    SKILL_DOUBLE_SHOT,							// 160
    SKILL_TRIPLE_SHOT,							// 161
    SKILL_CURE_EFFECT,							// 162
    SKILL_CRITICAL_EFFECT,						// 163
    SKILL_CRITICAL_GROUND,						// 164
    SKILL_VIGOR_DROP,							// 165
    
    // by sigi. 2002.6.7
    SKILL_SWORD_MASTERY,						// 166
    SKILL_SHIELD_MASTERY,						// 167
    SKILL_THUNDER_STORM,						// 168
    SKILL_CONCENTRATION,						// 169
    SKILL_EVASION,								// 170
    SKILL_HOLY_BLAST,							// 171
    SKILL_HYMN,									// 172
    SKILL_MENTAL_SWORD,							// 173
    SKILL_OBSERVING_EYE,						// 174
    SKILL_REFLECTION_EFFECT,					// 175
    
    // 2002.6.21
    SKILL_TEMP,									// 176
    SKILL_OPEN_CASKET,							// 177
    
    // 2002.9.2
    SKILL_SUMMON_MONSTERS,						// 178
    SKILL_GROUND_ATTACK,						// 179
    
    // 2002.9.13
    SKILL_METEOR_STRIKE,						// 180
    
    // 2002.9.23
    SKILL_DUPLICATE_SELF,						// 181
    
    // 2002.9.24
    SKILL_BLOODY_MASTER_WAVE,				    // 182
    
    // 2002.10.1
    SKILL_BLOODY_WARP,				    		// 183
    SKILL_BLOODY_SNAKE,				    		// 184
    
    // 2002.10.22
    SKILL_SOUL_CHAIN,							// 185
    
    // 2002.11.18
    SKILL_LIVENESS,								// 186
    
    // 2002.11.20
    SKILL_DARKNESS_WIDE,						// 187
    SKILL_POISON_STORM_WIDE,					// 188
    SKILL_ACID_STORM_WIDE,						// 189
    
    // 2002.12.26
    SKILL_SHARP_SHIELD,							// 190
    SKILL_WIDE_LIGHTNING,						// 191
    SKILL_AIR_SHIELD,							// 192
    SKILL_POWER_OF_LAND,						// 193
    SKILL_BULLET_OF_LIGHT,						// 194
    SKILL_GUN_SHOT_GUIDANCE,					// 195
    SKILL_REBUKE,								// 196
    SKILL_SPIRIT_GUARD,							// 197
    SKILL_TURN_UNDEAD,							// 198
    
    SKILL_HANDS_OF_WISDOM,						// 199
    SKILL_LIGHT_BALL,							// 200
    SKILL_HOLY_ARROW,							// 201
    
    // 2003.02.26
    SKILL_BLOODY_BREAKER,						// 202
    SKILL_RAPID_GLIDING,						// 203
    
    SKILL_MAGIC_ELUSION,						// 204
    SKILL_POISON_MESH,							// 205
    SKILL_ILLUSION_OF_AVENGE,					// 206
    SKILL_WILL_OF_LIFE,							// 207
    
    SKILL_DENIAL_MAGIC,							// 208
    SKILL_REQUITAL,								// 209
    SKILL_CONCEALMENT,							// 210
    SKILL_SWORD_RAY,							// 211
    SKILL_MULTI_AMPUTATE,						// 212
    SKILL_NAIL_MASTERY,							// 213

    SKILL_HIT_CONVERT,							// 214
    SKILL_WILD_TYPHOON,							// 215
    SKILL_ULTIMATE_BLOW,						// 216
    SKILL_ILLENDUE,								// 217
    SKILL_LIGHTNESS,							// 218
    
    SKILL_FLOURISH,								// 219
    SKILL_EVADE,								// 220
    SKILL_SHARP_ROUND,							// 221
    SKILL_HIDE_SIGHT,							// 222
    SKILL_BACK_STAB,							// 223
    SKILL_BLUNTING,								// 224
    SKILL_GAMMA_CHOP,							// 225
    SKILL_CROSS_GUARD,							// 226
    SKILL_FIRE_OF_SOUL_STONE,					// 227
    SKILL_ICE_OF_SOUL_STONE,					// 228
    SKILL_SAND_OF_SOUL_STONE,					// 229
    SKILL_BLOCK_HEAD,							// 230
    SKILL_KASAS_ARROW,							// 231
    SKILL_HANDS_OF_FIRE,						// 232
    SKILL_PROMINENCE,							// 233
    SKILL_RING_OF_FLARE,						// 234
    SKILL_BLAZE_BOLT,							// 235
    SKILL_ICE_FIELD,							// 236
    SKILL_WATER_BARRIER,						// 237
    SKILL_HANDS_OF_NIZIE,						// 238
    SKILL_NYMPH_RECOVERY,						// 239
    SKILL_LIBERTY,								// 240
    SKILL_TENDRIL,								// 241
    SKILL_GNOMES_WHISPER,						// 242
    SKILL_STONE_AUGER,							// 243
    SKILL_REFUSAL_ETHER,						// 244
    SKILL_EARTHS_TEETH,							// 245
    SKILL_ABSORB_SOUL,							// 246
    SKILL_SUMMON_SYLPH,							// 247
    SKILL_DRIFTING_SOUL,						// 248
    SKILL_CRITICAL_MAGIC,						// 249
    
    SKILL_EMISSION_WATER,						// 250
    SKILL_BEAT_HEAD,							// 251
    
    SKILL_DIVINE_SPIRITS,						// 252
    
    SKILL_BLITZ_SLIDING,						// 253
    SKILL_BLAZE_WALK,							// 254
    SKILL_JABBING_VEIN,							// 255
    SKILL_GREAT_HEAL,							// 256
    SKILL_DIVINE_GUIDANCE,						// 257
    SKILL_BLOODY_ZENITH,						// 258
    
    SKILL_REDIANCE,								// 259
    SKILL_LAR_SLASH,							// 260

    SKILL_HEART_CATALYST,						// 261
    SKILL_ARMS_MASTERY_1,						// 262
    SKILL_VIVID_MAGAZINE,						// 263
    SKILL_TRIDENT,								// 264
    SKILL_ARMS_MASTERY_2,						// 265
    SKILL_MOLE_SHOT,							// 266
    SKILL_ETERNITY,								// 267
    SKILL_PROTECTION_FROM_BLOOD,				// 268
    
    SKILL_INSTALL_TRAP,							// 269
    SKILL_CREATE_HOLY_POTION,					// 270
    SKILL_MERCY_GROUND,							// 271
    SKILL_HOLY_ARMOR,							// 272
    
    SKILL_TRANSFORM_TO_WERWOLF,					// 273
    SKILL_STONE_SKIN,							// 274
    SKILL_ACID_ERUPTION,						// 275
    SKILL_TALON_OF_CROW,						// 276
    SKILL_GRAY_DARKNESS,						// 277
    SKILL_BITE_OF_DEATH,						// 278
    
    SKILL_WIDE_GRAY_DARKNESS,					// 279
    
    SKILL_TELEPORT,								// 280
    
    SKILL_FIRE_PIERCING,						// 281
    SKILL_SUMMON_FIRE_ELEMENTAL,				// 282
    SKILL_MAGNUM_SPEAR,							// 283
    SKILL_HELLFIRE,								// 284
    
    SKILL_ICE_LANCE,							// 285
    SKILL_FROZEN_ARMOR,							// 286
    SKILL_SUMMON_WATER_ELEMENTAL,			// 287
    SKILL_EXPLOSION_WATER,						// 288
    SKILL_SOUL_REBIRTH,							// 289
    SKILL_SOUL_REBIRTH_MASTERY,					// 290
    
    SKILL_REACTIVE_ARMOR,						// 291
    SKILL_GROUND_BLESS,							// 292
    SKILL_SUMMON_GROUND_ELEMENTAL,			// 293
    SKILL_METEOR_STORM,							// 294
    
    SKILL_SHARP_CHAKRAM,						// 295
    SKILL_SHIFT_BREAK,							// 296
    SKILL_WATER_SHIELD,							// 297
    SKILL_DESTRUCTION_SPEAR,					// 298
    SKILL_BLESS_FIRE,							// 299
    SKILL_FATAL_SNICK,							// 300
    SKILL_SAND_CROSS,							// 301
    SKILL_DUCKING_WALLOP,						// 302
    SKILL_CHARGING_ATTACK,						// 303
    SKILL_DISTANCE_BLITZ,						// 304
    
    SKILL_FABULOUS_SOUL,						// 305
    SKILL_WILL_OF_IRON,							// 306
    
    // 질드레 스킬
    SKILL_WIDE_ICE_FIELD,						// 307
    SKILL_GLACIER_1,							// 308
    SKILL_GLACIER_2,							// 309
    SKILL_ICE_AUGER,							// 310
    SKILL_ICE_HAIL,								// 311
    SKILL_WIDE_ICE_HAIL,						// 312
    SKILL_ICE_WAVE,								// 313
    
    SKILL_LAND_MINE_EXPLOSION,					// 314
    SKILL_CLAYMORE_EXPLOSION,					// 315
    SKILL_PLEASURE_EXPLOSION,					// 316
    
    SKILL_DELEO_EFFICIO,						// 317	// DELETE EFFECT
    SKILL_REPUTO_FACTUM,						// 318
    
    SKILL_SWORD_OF_THOR,						// 319
    SKILL_BURNING_SOL_CHARGING,					// 320
    SKILL_BURNING_SOL_LAUNCH,					// 321
    SKILL_INSTALL_TURRET,						// 322
    SKILL_TURRET_FIRE,							// 323
    SKILL_SWEEP_VICE_1,							// 324
    SKILL_SWEEP_VICE_3,							// 325
    SKILL_SWEEP_VICE_5,							// 326
    SKILL_WHITSUNTIDE,							// 327
    SKILL_VIOLENT_PHANTOM,						// 328
    SKILL_SUMMON_GORE_GLAND,					// 329
    SKILL_GORE_GLAND_FIRE,						// 330
    SKILL_DESTRUCTION_SPEAR_MASTERY,			// 331
    SKILL_FATAL_SNICK_MASTERY,					// 332
    SKILL_MAGNUM_SPEAR_MASTERY,					// 333
    SKILL_ICE_LANCE_MASTERY,					// 334
    SKILL_REACTIVE_ARMOR_MASTERY,				// 335
    
    SKILL_THROWING_AXE,							// 336
    SKILL_CHOPPING_FIREWOOD,					// 337 장작패기
    SKILL_CHAIN_THROWING_AXE,					// 338 도끼 세개 던지기
    SKILL_MULTI_THROWING_AXE,					// 339 도끼  ""
    SKILL_PLAYING_WITH_FIRE,					// 340 불장난
    
    SKILL_INFINITY_THUNDERBOLT,					// 341
    SKILL_SPIT_STREAM,							// 342
    SKILL_PLASMA_ROCKET_LAUNCHER,				// 343
    SKILL_INTIMATE_GRAIL,						// 344
    SKILL_BOMBING_STAR,							// 345
    SKILL_SET_AFIRE,							// 346
    SKILL_NOOSE_OF_WRAITH,						// 347
    
    SKILL_SHARP_HAIL,							// 348
    SKILL_SUMMON_MIGA,							// 349	// 아우스터즈가 쓰는 스킬
    SKILL_SUMMON_MIGA_ATTACK,					// 350	// 소환된놈이 쓰는 스킬
    SKILL_ICE_HORIZON,							// 351
    SKILL_FURY_OF_GNOME,						// 352
    
    SKILL_CANNONADE,							// 353	// 포격
    SKILL_SELF_DESTRUCTION,						// 354	// 자폭공격
    
    SKILL_AR_ATTACK,							// 355	// 몬스터용
    SKILL_SMG_ATTACK,							// 356	// 몬스터용
    SKILL_GRENADE_ATTACK,						// 357	// 몬스터용
    
    SKILL_DRAGON_TORNADO,						// 358
    SKILL_BIKE_CRASH,							// 359
    SKILL_HARPOON_BOMB,							// 360
    SKILL_PASSING_HEAL,							// 361
    SKILL_ROTTEN_APPLE,							// 362
    SKILL_WILD_WOLF,							// 363
    SKILL_ABERRATION,							// 364
    SKILL_HALO,									// 365
    SKILL_DESTINIES,							// 366
    SKILL_FIERCE_FLAME,							// 367
    SKILL_SHADOW_OF_STORM,						// 368
    SKILL_HEAL_PASS,							// 369 // 옮겨가는 힐
    
    SKILL_TRASLA_ATTACK,						// 370
    SKILL_PUSCA_ATTACK,							// 371
    SKILL_NOD_COPILA_ATTACK,					// 372
    SKILL_NOD_COPILA_ATTACK_2,					// 373
    
    SKILL_UNTERFELDWEBEL_FIRE,					// 374
    SKILL_FELDWEBEL_FIRE,						// 375

    SKILL_NOT_IMPL1,          // 376
    SKILL_NOT_IMPL2,          // 377
    SKILL_NOT_IMPL3,          // 378
    SKILL_NOT_IMPL4,          // 379
    SKILL_NOT_IMPL5,          // 380
    SKILL_NOT_IMPL6,          // 381
    SKILL_NOT_IMPL7,          // 382
    SKILL_NOT_IMPL8,          // 383
    SKILL_NOT_IMPL9,          // 384
    SKILL_NOT_IMPL10,          // 385
    SKILL_NOT_IMPL11,          // 386
    SKILL_NOT_IMPL12,          // 387
    SKILL_NOT_IMPL13,          // 388
    SKILL_NOT_IMPL14,          // 389
    SKILL_NOT_IMPL15,          // 390
    SKILL_MAX
};

const string SkillTypes2String[] = 
{
    "SKILL_ATTACK_MELEE",						// 0
    "SKILL_ATTACK_ARMS",						// 1
    "SKILL_SELF",								// 2
    "SKILL_TILE",								// 3
    "SKILL_OBJECT",	    						// 4
    
    "SKILL_DOUBLE_IMPACT",  				  	// 5
    "SKILL_TRIPLE_SLASHER",				  	  	// 6
    "SKILL_RAINBOW_SLASHER",				  	// 7
    "SKILL_THUNDER_SPARK",	   				 	// 8
    "SKILL_DANCING_SWORD",						// 9
    "SKILL_CROSS_COUNTER",		   			 	// 10
    "SKILL_FLASH_SLIDING",		  			  	// 11
    "SKILL_LIGHTNING_HAND",	  					// 12
    "SKILL_SNAKE_COMBO",	  				 	// 13
    "SKILL_SWORD_WAVE",		  	 				// 14
    "SKILL_DRAGON_RISING",						// 15
    "SKILL_FIVE_STORM_CRASH",	 			 	// 16
    "SKILL_HEAVENS_SWORD",		  			  	// 17
    
    "SKILL_SINGLE_BLOW",					    // 18
    "SKILL_SPIRAL_SLAY",					    // 19
    "SKILL_TRIPLE_BREAK",					    // 20
    "SKILL_WILD_SMASH",						    // 21
    "SKILL_GHOST_BLADE",						// 22
    "SKILL_POTENTIAL_EXPLOSION",			 	// 23
    "SKILL_SHADOW_WALK",			  		  	// 24
    "SKILL_CHARGING_POWER",		  			  	// 25
    "SKILL_HURRICANE_COMBO",	 			 	// 26
    "SKILL_TORNADO_SEVER",		  			  	// 27
    "SKILL_ARMAGEDDON_SLASHER",	  				// 28
    "SKILL_SOUL_SHOCK",			   				// 29
    "SKILL_SAINT_BLADE",			   		  	// 30
    
    "SKILL_FAST_RELOAD",					    // 31
    "SKILL_QUICK_FIRE",							// 32
    "SKILL_SMG_MASTERY",						// 33
    "SKILL_MULTI_SHOT",						    // 34
    "SKILL_HEAD_SHOT",						    // 35
    "SKILL_AR_MASTERY",							// 36
    "SKILL_PIERCING",						   	// 37
    "SKILL_SNIPING",						   	// 38
    "SKILL_SG_MASTERY",							// 39
    "SKILL_DETECT_MINE",					    // 40
    "SKILL_CREATE_BOMB", 					    // 41
    "SKILL_SR_MASTERY",							// 42
    "SKILL_DISARM_MINE",					    // 43
    "SKILL_INSTALL_MINE",					    // 44
    "SKILL_CREATE_MINE",		  			    // 45
    
    "SKILL_CREATE_HOLY_WATER", 			 		// 46
    "SKILL_LIGHT",				      			// 47
    "SKILL_DETECT_HIDDEN",	   	 				// 48
    "SKILL_AURA_BALL",	     		 		 	// 49
    "SKILL_BLESS",			       		 		// 50
    "SKILL_CONTINUAL_LIGHT",	 			 	// 51
    "SKILL_FLARE",								// 52
    "SKILL_PURIFY",    							// 53
    "SKILL_AURA_RING",		  	  		  		// 54
    "SKILL_STRIKING",		      				// 55
    "SKILL_DETECT_INVISIBILITY",				// 56
    "SKILL_IDENTIFY",							// 57
    "SKILL_AURA_SHIELD",	    				// 58
    "SKILL_ENCHANT",			    		  	// 59
    "SKILL_VISIBLE",			    		  	// 60
    "SKILL_CHAIN_AURA",							// 61
    "SKILL_SAINT_AURA",							// 62
    
    "SKILL_CURE_LIGHT_WOUNDS",					// 63
    "SKILL_CURE_POISON",						// 64
    "SKILL_PROTECTION_FROM_POISON",				// 65
    "SKILL_CAUSE_LIGHT_WOUNDS",					// 66
    "SKILL_CURE_SERIOUS_WOUNDS",				// 67
    "SKILL_REMOVE_CURSE",						// 68
    "SKILL_PROTECTION_FROM_CURSE",				// 69
    "SKILL_CAUSE_SERIOUS_WOUNDS",				// 70
    "SKILL_CURE_CRITICAL_WOUNDS",				// 71
    "SKILL_PROTECTION_FROM_ACID",				// 72
    "SKILL_SACRIFICE",							// 73
    "SKILL_CAUSE_CRITICAL_WOUNDS",				// 74
    "SKILL_CURE_ALL",							// 75
    "SKILL_REGENERATION",						// 76
    "SKILL_MASS_CURE",							// 77
    "SKILL_MASS_HEAL",							// 78
    
    "SKILL_BLOOD_DRAIN",						// 79
    
    "SKILL_POISONOUS_HANDS",					// 80
    "SKILL_GREEN_POISON",						// 81
    "SKILL_YELLOW_POISON",						// 82
    "SKILL_DARKBLUE_POISON",					// 83
    "SKILL_GREEN_STALKER",						// 84
    
    "SKILL_ACID_TOUCH",							// 85
    "SKILL_ACID_BOLT",							// 86
    "SKILL_ACID_BALL",							// 87
    "SKILL_ACID_SWAMP",							// 88
    
    "SKILL_PARALYZE",							// 89
    "SKILL_DOOM",								// 90
    "SKILL_HALLUCINATION",						// 91
    "SKILL_DEATH",								// 92
    
    "SKILL_BLOODY_NAIL",						// 93
    "SKILL_BLOODY_KNIFE",						// 94
    "SKILL_BLOODY_BALL",						// 95
    "SKILL_BLOODY_WALL",						// 96
    "SKILL_BLOODY_SPEAR",						// 97
    
    "SKILL_HIDE",								// 98
    "SKILL_DARKNESS",							// 99
    "SKILL_INVISIBILITY",						// 100
    "SKILL_TRANSFORM_TO_WOLF",					// 101
    "SKILL_TRANSFORM_TO_BAT",					// 102
    
    "SKILL_SUMMON_WOLF",						// 103
    "SKILL_SUMMON_CASKET",						// 104
    "SKILL_RAISING_DEAD",						// 105
    "SKILL_SUMMON_SERVANT",						// 106
    
    "SKILL_UN_BURROW",							// 107
    "SKILL_UN_TRANSFORM",						// 108
    "SKILL_UN_INVISIBILITY",					// 109
    "SKILL_THROW_HOLY_WATER",					// 110
    
    "SKILL_EAT_CORPSE",							// 111
    "SKILL_HOWL",								// 112
    
    "SKILL_RESTORE",							// 113
    
    "SKILL_BLOODY_MARKER",						// 114
    "SKILL_BLOODY_TUNNEL",						// 115
    
    "SKILL_SEDUCTION",							// 116
    "SKILL_WIND_DIVIDER",						// 117
    "SKILL_EARTHQUAKE",							// 118
    
    "SKILL_RESURRECT",							// 119
    "SKILL_PRAYER",								// 120
    "SKILL_MEDITATION",							// 121
    
    "SKILL_THUNDER_BOLT",						// 122
    "SKILL_EXPANSION", 							// 123
    "SKILL_MIRACLE_SHIELD", 					// 124
    "SKILL_THUNDER_FLASH",						// 125
    "SKILL_MASSACRE",							// 126
    "SKILL_INVINCIBLE",							// 127
    
    "SKILL_BERSERKER",							// 128
    "SKILL_MOONLIGHT_SEVER",					// 129
    "SKILL_SHADOW_DANCING",						// 130
    "SKILL_TYPHOON",							// 131
    "SKILL_PSYCHOKINESIS",						// 132
    "SKILL_EXTERMINATION",						// 133
    
    "SKILL_MIND_CONTROL",						// 134
    "SKILL_REVOLVING",							// 135
    "SKILL_FATALITY",							// 136
    "SKILL_BLITZ",								// 137
    
    "SKILL_ACTIVATION",							// 138
    "SKILL_PEACE",								// 139
    "SKILL_ENERGY_DROP",						// 140
    "SKILL_EXORCISM",							// 141
    
    "SKILL_SANCTUARY",							// 142
    "SKILL_REFLECTION",							// 143
    "SKILL_ARMAGEDDON",							// 144
    
    "SKILL_POISON_STRIKE",						// 145
    "SKILL_POISON_STORM",						// 146
    "SKILL_ACID_STRIKE",						// 147
    "SKILL_ACID_STORM",							// 148
    "SKILL_BLOODY_STRIKE",						// 149
    "SKILL_BLOODY_STORM",						// 150
    
    "SKILL_SUMMON_BAT",							// 151
    "SKILL_CHARM",								// 152
    "SKILL_POLYMORPH",							// 153
    "SKILL_MEPHISTO",							// 154
    "SKILL_HYPNOSIS",							// 155
    "SKILL_TRANSFUSION",						// 156
    "SKILL_EXTREME",							// 157
    "SKILL_BLOODY_WAVE",						// 158
    "SKILL_THROW_BOMB",							// 159
    
    "SKILL_DOUBLE_SHOT",						// 160
    "SKILL_TRIPLE_SHOT",						// 161
    "SKILL_CURE_EFFECT",						// 162
    "SKILL_CRITICAL_EFFECT",					// 163
    "SKILL_CRITICAL_GROUND",					// 164
    "SKILL_VIGOR_DROP",							// 165
    
    // by sigi. 2002.6.7
    "SKILL_SWORD_MASTERY",						// 166
    "SKILL_SHIELD_MASTERY",						// 167
    "SKILL_THUNDER_STORM",						// 168
    "SKILL_CONCENTRATION",						// 169
    "SKILL_EVASION",							// 170
    "SKILL_HOLY_BLAST",							// 171
    "SKILL_HYMN",								// 172
    "SKILL_MENTAL_SWORD",						// 173
    "SKILL_OBSERVING_EYE",						// 174
    "SKILL_REFLECTION_EFFECT",					// 175
    
    // 2002.6.21
    "SKILL_TEMP",								// 176
    "SKILL_OPEN_CASKET",						// 177
    
    // 2002.9.2
    "SKILL_SUMMON_MONSTERS",					// 178
    "SKILL_GROUND_ATTACK",						// 179
    
    // 2002.9.13
    "SKILL_METEOR_STRIKE",						// 180
    
    // 2002.9.23
    "SKILL_DUPLICATE_SELF",						// 181
    
    // 2002.9.24
    "SKILL_BLOODY_MASTER_WAVE",					// 182

    // 2002.10.1
    "SKILL_BLOODY_WARP",                        // 183
    "SKILL_BLOODY_SNAKE",                       // 184
    
    "SKILL_SOUL_CHAIN", 						// 185
    
    "SKILL_LIVENESS",	 						// 186
    
    "SKILL_DARKNESS_WIDE",						// 187
    "SKILL_POISON_STORM_WIDE",					// 188
    "SKILL_ACID_STORM_WIDE",					// 189
    
    // 2002.12.26
    "SKILL_SHARP_SHIELD",						// 190
    "SKILL_WIDE_LIGHTNING",						// 191
    "SKILL_AIR_SHIELD",							// 192
    "SKILL_POWER_OF_LAND",						// 193
    "SKILL_BULLET_OF_LIGHT",					// 194
    "SKILL_GUN_SHOT_GUIDANCE",					// 195
    "SKILL_REBUKE",								// 196
    "SKILL_SPIRIT_GUARD",						// 197
    "SKILL_TURN_UNDEAD",						// 198
    
    "SKILL_HANDS_OF_WISDOM",					// 199
    "SKILL_LIGHT_BALL",							// 200
    "SKILL_HOLY_ARROW",							// 201
    
    "SKILL_BLOODY_BREAKER",						// 202
    "SKILL_RAPID_GLIDING",						// 203
    
    "SKILL_MAGIC_ELUSION",						// 204
    "SKILL_POISON_MESH",						// 205
    "SKILL_ILLUSION_OF_AVENGE",					// 206
    "SKILL_WILL_OF_LIFE",						// 207
    
    "SKILL_DENIAL_MAGIC",						// 208
    "SKILL_REQUITAL",							// 209
    "SKILL_CONCEALMENT",						// 210
    "SKILL_SWORD_RAY",							// 211
    "SKILL_MULTI_AMPUTATE",						// 212
    "SKILL_NAIL_MASTERY",						// 213
    
    "SKILL_HIT_CONVERT",						// 214
    "SKILL_WILD_TYPHOON",						// 215
    "SKILL_ULTIMATE_BLOW",						// 216
    "SKILL_ILLENDUE",							// 217
    "SKILL_LIGHTNESS",							// 218
    
    "SKILL_FLOURISH",							// 219
    "SKILL_EVADE",								// 220
    "SKILL_SHARP_ROUND",						// 221
    "SKILL_HIDE_SIGHT",							// 222
    "SKILL_BACK_STAB",							// 223
    "SKILL_BLUNTING",							// 224
    "SKILL_GAMMA_CHOP",							// 225
    "SKILL_CROSS_GUARD",						// 226
    "SKILL_FIRE_OF_SOUL_STONE",					// 227
    "SKILL_ICE_OF_SOUL_STONE",					// 228
    "SKILL_SAND_OF_SOUL_STONE",					// 229
    "SKILL_BLOCK_HEAD",							// 230
    "SKILL_KASAS_ARROW",						// 231
    "SKILL_HANDS_OF_FIRE",						// 232
    "SKILL_PROMINENCE",							// 233
    "SKILL_RING_OF_FLARE",						// 234
    "SKILL_BLAZE_BOLT",							// 235
    "SKILL_ICE_FIELD",							// 236
    "SKILL_WATER_BARRIER",						// 237
    "SKILL_HANDS_OF_NIZIE",						// 238
    "SKILL_NYMPH_RECOVERY",						// 239
    "SKILL_LIBERTY",							// 240
    "SKILL_TENDRIL",							// 241
    "SKILL_GNOMES_WHISPER",						// 242
    "SKILL_STONE_AUGER",						// 243
    "SKILL_REFUSAL_ETHER",						// 244
    "SKILL_EARTHS_TEETH",						// 245
    "SKILL_ABSORB_SOUL",						// 246
    "SKILL_SUMMON_SYLPH",						// 247
    "SKILL_DRIFTING_SOUL",						// 248
    "SKILL_CRITICAL_MAGIC",						// 249
    
    "SKILL_EMISSION_WATER",						// 250
    "SKILL_BEAT_HEAD",							// 251
    
    "SKILL_DIVINE_SPIRITS",						// 252
    
    "SKILL_BLITZ_SLIDING",						// 253
    "SKILL_BLAZE_WALK",							// 254
    "SKILL_JABBING_VEIN",						// 255
    "SKILL_GREAT_HEAL",						// 256
    "SKILL_DIVINE_GUIDANCE",						// 257
    "SKILL_BLOODY_ZENITH",						// 258
    
    "SKILL_REDIANCE",								// 259
    "SKILL_LAR_SLASH",							// 260

    "SKILL_HEART_CATALYST",						// 261
    "SKILL_ARMS_MASTERY_1",						// 262
    "SKILL_VIVID_MAGAZINE",						// 263
    "SKILL_TRIDENT",								// 264
    "SKILL_ARMS_MASTERY_2",						// 265
    "SKILL_MOLE_SHOT",							// 266
    
    "SKILL_ETERNITY",								// 267
    "SKILL_PROTECTION_FROM_BLOOD",				// 268
    
    "SKILL_INSTALL_TRAP",							// 269
    "SKILL_CREATE_HOLY_POTION",					// 270
    "SKILL_MERCY_GROUND",							// 271
    "SKILL_HOLY_ARMOR",							// 272
    
    "SKILL_TRANSFORM_TO_WERWOLF",					// 273
    "SKILL_STONE_SKIN",							// 274
    "SKILL_ACID_ERUPTION",						// 275
    "SKILL_TALON_OF_CROW",						// 276
    "SKILL_GRAY_DARKNESS",						// 277
    "SKILL_BITE_OF_DEATH",						// 278
    
    "SKILL_WIDE_GRAY_DARKNESS",						// 279
    "SKILL_TELEPORT",								// 280
    
    "SKILL_FIRE_PIERCING",							// 281
    "SKILL_SUMMON_FIRE_ELEMENTAL",				// 282
    "SKILL_MAGNUM_SPEAR",							// 283
    "SKILL_HELLFIRE",								// 284
    
    "SKILL_ICE_LANCE",							// 285
    "SKILL_FROZEN_ARMOR",							// 286
    "SKILL_SUMMON_WATER_ELEMENTAL",			// 287
    "SKILL_EXPLOSION_WATER",						// 288
    "SKILL_SOUL_REBIRTH",							// 289
    "SKILL_SOUL_REBIRTH_MASTERY",					// 290
    
    "SKILL_REACTIVE_ARMOR",						// 291
    "SKILL_GROUND_BLESS",							// 292
    "SKILL_SUMMON_GROUND_ELEMENTAL",			// 293
    "SKILL_METEOR_STORM",							// 294
    
    "SKILL_SHARP_CHAKRAM",						// 295
    "SKILL_SHIFT_BREAK",						// 296
    "SKILL_WATER_SHIELD",						// 297
    "SKILL_DESTRUCTION_SPEAR",					// 298
    "SKILL_BLESS_FIRE",							// 299
    "SKILL_FATAL_SNICK",						// 300
    "SKILL_SAND_CROSS",							// 301
    "SKILL_DUCKING_WALLOP",						// 302
    "SKILL_CHARGING_ATTACK",					// 303
    "SKILL_DISTANCE_BLITZ",						// 304
    
    "SKILL_FABULOUS_SOUL",						// 305
    "SKILL_WILL_OF_IRON",						// 306
    
    "SKILL_WIDE_ICE_FIELD",						// 307
    "SKILL_GLACIER_1",							// 308
    "SKILL_GLACIER_2",							// 309
    "SKILL_ICE_AUGER",							// 310
    "SKILL_ICE_HAIL",							// 311
    "SKILL_WIDE_ICE_HAIL",						// 312
    "SKILL_ICE_WAVE",							// 313
    
    "SKILL_LAND_MINE_EXPLOSION",				// 314
    "SKILL_CLAYMORE_EXPLOSION",					// 315
    "SKILL_PLEASURE_EXPLOSION",					// 316
    
    "SKILL_DELEO_EFFICIO",						// 317	// DELETE EFFECT
    "SKILL_REPUTO_FACTUM",						// 318
    
    "SKILL_SWORD_OF_THOR",						// 319
    "SKILL_BURNING_SOL_CHARGING",				// 320
    "SKILL_BURNING_SOL_LAUNCH",					// 321
    "SKILL_INSTALL_TURRET",						// 322
    "SKILL_TURRET_FIRE",						// 323
    "SKILL_SWEEP_VICE_1",						// 324
    "SKILL_SWEEP_VICE_3",						// 325
    "SKILL_SWEEP_VICE_5",						// 326
    "SKILL_WHITSUNTIDE",						// 327
    "SKILL_VIOLENT_PHANTOM",					// 328
    "SKILL_SUMMON_GORE_GLAND",					// 329
    "SKILL_GORE_GLAND_FIRE",					// 330
    "SKILL_DESTRUCTION_SPEAR_MASTERY",			// 331
    "SKILL_FATAL_SNICK_MASTERY",				// 332
    "SKILL_MAGNUM_SPEAR_MASTERY",				// 333
    "SKILL_ICE_LANCE_MASTERY",					// 334
    "SKILL_REACTIVE_ARMOR_MASTERY",				// 335
    
    "SKILL_THROWING_AXE",						// 336
    "SKILL_CHOPPING_FIREWOOD",					// 337 장작패기
    "SKILL_CHAIN_THROWING_AXE",					// 338
    "SKILL_MULTI_THROWING_AXE",					// 339
    "SKILL_PLAYING_WITH_FIRE",					// 340 불장난
    
    "SKILL_INFINITY_THUNDERBOLT",				// 341
    "SKILL_SPIT_STREAM",						// 342
    "SKILL_PLASMA_ROCKET_LAUNCHER",				// 343
    "SKILL_INTIMATE_GRAIL",						// 344
    "SKILL_BOMBING_STAR",						// 345
    "SKILL_SET_AFIRE",							// 346
    "SKILL_NOOSE_OF_WRAITH",					// 347
    
    "SKILL_SHARP_HAIL",							// 348
    "SKILL_SUMMON_MIGA",						// 349	// 아우스터즈가 쓰는 스킬
    "SKILL_SUMMON_MIGA_ATTACK",					// 350	// 소환된놈이 쓰는 스킬
    "SKILL_ICE_HORIZON",						// 351
    "SKILL_FURY_OF_GNOME",						// 352
    
    "SKILL_CANNONADE",							// 353	// 포격
    "SKILL_SELF_DESTRUCTION",					// 354	// 자폭공격
    
    "SKILL_AR_ATTACK",							// 355	// 몬스터용
    "SKILL_SMG_ATTACK",							// 356	// 몬스터용
    "SKILL_GRENADE_ATTACK",						// 357	// 몬스터용
    
    "SKILL_DRAGON_TORNADO",						// 358
    "SKILL_BIKE_CRASH",							// 359
    "SKILL_HARPOON_BOMB",							// 360
    "SKILL_PASSING_HEAL",							// 361
    "SKILL_ROTTEN_APPLE",							// 362
    "SKILL_WILD_WOLF",							// 363
    "SKILL_ABERRATION",							// 364
    "SKILL_HALO",									// 365
    "SKILL_DESTINIES",							// 366
    "SKILL_FIERCE_FLAME",							// 367
    "SKILL_SHADOW_OF_STORM",						// 368
    "SKILL_HEAL_PASS",							// 369 // 옮겨가는 힐
    
    "SKILL_TRASLA_ATTACK",						// 370
    "SKILL_PUSCA_ATTACK",							// 371
    "SKILL_NOD_COPILA_ATTACK",					// 372
    "SKILL_NOD_COPILA_ATTACK_2",					// 373
    
    "SKILL_UNTERFELDWEBEL_FIRE",				// 374
    "SKILL_FELDWEBEL_FIRE",						// 375

    "SKILL_NOT_IMPL1",   //376
    "SKILL_NOT_IMPL2",   //377
    "SKILL_NOT_IMPL3",   //378
    "SKILL_NOT_IMPL4",   //379
    "SKILL_NOT_IMPL5",   //380
    "SKILL_NOT_IMPL6",   //381
    "SKILL_NOT_IMPL7",   //382
    "SKILL_NOT_IMPL8",   //383
    "SKILL_NOT_IMPL9",   //384
    "SKILL_NOT_IMPL10",   //385
    "SKILL_NOT_IMPL11",   //386
    "SKILL_NOT_IMPL12",   //387
    "SKILL_NOT_IMPL13",   //388
    "SKILL_NOT_IMPL14",   //389
    "SKILL_NOT_IMPL15",   //390
    "SKILL_MAX"
};


#endif	// __SKILL_H__
