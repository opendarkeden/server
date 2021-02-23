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
	["ITEM_CLASS_RING"] 				= 8,
	["ITEM_CLASS_BRACELET"] 			= 9,
	["ITEM_CLASS_NECKLACE"] 			= 10,

	["ITEM_CLASS_VAMPIRE_RING"] 		= 30,
	["ITEM_CLASS_VAMPIRE_BRACELET"] 	= 31,
	["ITEM_CLASS_VAMPIRE_NECKLACE"] 	= 32
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
	["HP+12"]	=	19
}

OptionInfoSet =
{
	Sum80 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["HP+6"]},
	Sum140 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["HP+6"]},
	Sum200 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["HP+9"]},
	Sum250 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["HP+9"]},
	Sum300 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["HP+12"]},

	Level20 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"]},
	Level40 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"]},
	Level60 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"]},
	Level80 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["INT+3"]},
	Level100 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["INT+4"]},
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

