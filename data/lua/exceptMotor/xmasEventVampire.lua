--------------------------------------------------------------------------------
--
-- xmasEventVampire.lua
--
--------------------------------------------------------------------------------
-- 이거 사용하기 전에 xmasEventCommon.lua를 실행해야 한다.
-- Input  : Level
-- Output : ItemClass, ItemType, OptionType
--------------------------------------------------------------------------------
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
	["ATTR+2"]	=	184,
	["ASPD+10"]	=	79,
	["ASPD+15"]	=	80
}

OptionInfoSet =
{
	Level40 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["INT+2"], OptionInfo["DEF+3"], OptionInfo["PRO+2"]},
	Level60 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["HPSTL+2"], OptionInfo["DAM+2"], OptionInfo["ASPD+10"]},
	Level80 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["DAM+2"], OptionInfo["LUCK+2"], OptionInfo["ASPD+10"]},
	Level100 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["DAM+3"], OptionInfo["ATTR+2"], OptionInfo["ASPD+15"]},
}


ItemClassVampireSet = 
{
	ItemClassInfo["ITEM_CLASS_VAMPIRE_RING"],
	ItemClassInfo["ITEM_CLASS_VAMPIRE_BRACELET"],
	ItemClassInfo["ITEM_CLASS_VAMPIRE_NECKLACE"]
}

-- select ItemClass
ItemClass 	= selectOne( ItemClassVampireSet )

-- select ItemType, OptionType by Level
ItemType 	= 0
OptionType 	= 0

if Level <= 20 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Level40 )

elseif Level <= 40 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Level40 )

elseif Level <= 50 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Level60 )

elseif Level <= 60 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Level60 )

elseif Level <= 70 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Level80 )

elseif Level <= 80 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Level80 )

elseif Level <= 90 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Level100 )

else -- Level < 100 then
	ItemType = 8
	OptionType = selectOne( OptionInfoSet.Level100 )

end


