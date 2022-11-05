--------------------------------------------------------------------------------
--
-- premiumEventItemCommon.lua
--
--------------------------------------------------------------------------------
-- Input  : 이거는 처음에 초기화를 위한거다.
-- Output : 없당
--------------------------------------------------------------------------------

function selectOne (t)
	return t[ random(1, getn(t)) ]
end


ItemClassInfo = 
{
	["ITEM_CLASS_RING"] 				= 8,
	["ITEM_CLASS_BRACELET"] 			= 9,
	["ITEM_CLASS_NECKLACE"] 			= 10,

	["ITEM_CLASS_VAMPIRE_RING"] 		= 30,
	["ITEM_CLASS_VAMPIRE_BRACELET"] 	= 31,
	["ITEM_CLASS_VAMPIRE_NECKLACE"] 	= 32,
}

OptionInfo =
{
	["STR+2"]	=	2,
	["STR+3"]	=	3,
	["STR+4"]	=	4,
	["DEX+2"]	=	7,
	["DEX+3"]	=	8,
	["DEX+4"]	=	9,
	["INT+2"]	=	12,
	["INT+3"]	=	13,
	["INT+4"]	=	14,
	["HP+6"]	=	17,
	["HP+9"]	=	18,
	["HP+12"]	=	19,
	["MP+5"]	=	21,
	["MP+10"]	=	22,
	["MP+15"]	=	23,
	["VIS+2"]	=	76,
	["VIS+3"]	=	77,

	["DEF+2"]	=   44,
	["DEF+3"]	=   45,
	["PRO+2"]	=	54,
	["DAM+1"]	=	48,
	["DAM+2"]	=	49,
	["DAM+3"]	=	50,
	["DAM+4"]	=	51,
	["HPSTL+2"]	=	27,
	["HPSTL+3"]	=	28,
	["MPSTL+2"]	=	30,
	["MPSTL+3"]	=	31,
	["LUCK+1"]	=	175,
	["LUCK+2"]	=	176,
	["LUCK+3"]	=	177,
	["RES+5"]	=	180,
	["ATTR+1"]	=	183,
	["ATTR+2"]	=	184,
	["ATTR+3"]	=	185,
	["ASPD+10"]	=	79,
	["ASPD+15"]	=	80,
	["ASPD+20"]	=	81
}

OptionInfoSet =
{
	Sum80 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"], OptionInfo["ASPD+5"], OptionInfo["DAM+1"]},
	Sum140 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"], OptionInfo["ASPD+10"], OptionInfo["DAM+2"]},
	Sum170 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+10"], OptionInfo["DAM+2"]},
	Sum200 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+15"], OptionInfo["DAM+3"]},
	Sum225 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+15"], OptionInfo["DAM+3"]},
	Sum250 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+15"], OptionInfo["DAM+3"]},
	Sum275 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["INT+4"], OptionInfo["ASPD+20"], OptionInfo["DAM+3"]},
	Sum300 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["INT+4"], OptionInfo["ASPD+20"], OptionInfo["DAM+4"]},

	Level20 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"], OptionInfo["ASPD+5"], OptionInfo["DAM+1"]},
	Level40 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"], OptionInfo["ASPD+10"], OptionInfo["DAM+2"]},
	Level50 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+10"], OptionInfo["DAM+2"]},
	Level60 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+15"], OptionInfo["DAM+3"]},
	Level70 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+15"], OptionInfo["DAM+3"]},
	Level80 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"], OptionInfo["ASPD+15"], OptionInfo["DAM+3"]},
	Level90 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["INT+4"], OptionInfo["ASPD+20"], OptionInfo["DAM+3"]},
	Level100 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["INT+4"], OptionInfo["ASPD+20"], OptionInfo["DAM+4"]},
}

OptionInfoSet2 =
{
	Sum80 = {OptionInfo["DEF+2"], OptionInfo["VIS+2"], OptionInfo["HP+6"], OptionInfo["MP+5"], OptionInfo["LUCK+1"]},
	Sum140 = {OptionInfo["DEF+2"], OptionInfo["VIS+2"], OptionInfo["HP+6"], OptionInfo["MP+10"], OptionInfo["LUCK+1"]},
	Sum170 = {OptionInfo["ATTR+1"], OptionInfo["VIS+3"], OptionInfo["HP+6"], OptionInfo["MP+10"], OptionInfo["LUCK+1"]},
	Sum200 = {OptionInfo["ATTR+1"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Sum225 = {OptionInfo["ATTR+2"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Sum250 = {OptionInfo["ATTR+2"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Sum275 = {OptionInfo["ATTR+2"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Sum300 = {OptionInfo["ATTR+3"], OptionInfo["VIS+3"], OptionInfo["HP+12"], OptionInfo["MP+15"], OptionInfo["LUCK+3"]},

	Level20 = {OptionInfo["DEF+2"], OptionInfo["VIS+2"], OptionInfo["HP+6"], OptionInfo["MP+10"], OptionInfo["LUCK+1"]},
	Level40 = {OptionInfo["DEF+2"], OptionInfo["VIS+2"], OptionInfo["HP+6"], OptionInfo["MP+10"], OptionInfo["LUCK+1"]},
	Level50 = {OptionInfo["ATTR+1"], OptionInfo["VIS+3"], OptionInfo["HP+6"], OptionInfo["MP+10"], OptionInfo["LUCK+1"]},
	Level60 = {OptionInfo["ATTR+1"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Level70 = {OptionInfo["ATTR+2"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Level80 = {OptionInfo["ATTR+2"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Level90 = {OptionInfo["ATTR+2"], OptionInfo["VIS+3"], OptionInfo["HP+9"], OptionInfo["MP+15"], OptionInfo["LUCK+2"]},
	Level100 = {OptionInfo["ATTR+3"], OptionInfo["VIS+3"], OptionInfo["HP+12"], OptionInfo["MP+15"], OptionInfo["LUCK+3"]},
}

ItemClassSlayerSet = 
{
	ItemClassInfo["ITEM_CLASS_RING"],
	ItemClassInfo["ITEM_CLASS_BRACELET"],
	ItemClassInfo["ITEM_CLASS_NECKLACE"]
}

ItemClassVampireSet = 
{
	ItemClassInfo["ITEM_CLASS_VAMPIRE_RING"],
	ItemClassInfo["ITEM_CLASS_VAMPIRE_BRACELET"],
	ItemClassInfo["ITEM_CLASS_VAMPIRE_NECKLACE"]
}

