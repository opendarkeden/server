--------------------------------------------------------------------------------
--
-- xmasEventCommon.lua
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
	["ITEM_CLASS_KEY"]					= 7,

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

	["DEF+3"]	=   45,
	["PRO+2"]	=	54,
	["DAM+1"]	=	48,
	["DAM+2"]	=	49,
	["DAM+3"]	=	50,
	["HPSTL+2"]	=	27,
	["HPSTL+3"]	=	28,
	["MPSTL+2"]	=	30,
	["MPSTL+3"]	=	31,
	["LUCK+2"]	=	176,
	["LUCK+3"]	=	177,
	["RES+5"]	=	180,
	["ATTR+1"]	=	183,
	["ATTR+2"]	=	184,
	["ASPD+10"]	=	79,
	["ASPD+15"]	=	80
}

OptionInfoSet =
{
	Sum140 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["DAM+1"], OptionInfo["ASPD+10"], OptionInfo["HP+6"]},
	Sum200 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["DAM+2"], OptionInfo["ASPD+15"], OptionInfo["HP+9"]},
	Sum250 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["DAM+2"], OptionInfo["LUCK+2"], OptionInfo["HP+9"]},
	Sum300 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["DAM+3"], OptionInfo["RES+5"], OptionInfo["ATTR+2"]},

	Level40 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"], OptionInfo["DEF+3"], OptionInfo["PRO+2"]},
	Level60 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["ATTR+1"], OptionInfo["DAM+2"], OptionInfo["ASPD+10"]},
	Level80 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["DAM+2"], OptionInfo["LUCK+2"], OptionInfo["ASPD+10"]},
	Level100 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["DAM+3"], OptionInfo["ATTR+2"], OptionInfo["ASPD+15"]},
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

