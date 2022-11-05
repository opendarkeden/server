--------------------------------------------------------------------------------
--
-- xmasEventSlayer.lua
--
--------------------------------------------------------------------------------
-- 이거 사용하기 전에 xmasEventCommon.lua를 load해야 한다.
-- Input  : SUM
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
	Sum140 = {OptionInfo["STR+2"], OptionInfo["DEX+2"], OptionInfo["DAM+1"], OptionInfo["DEF+3"], OptionInfo["PRO+2"]},
	Sum200 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["HPSTL+2"], OptionInfo["MPSTL+2"], OptionInfo["DAM+2"]},
	Sum250 = {OptionInfo["STR+3"], OptionInfo["DEX+3"], OptionInfo["DAM+2"], OptionInfo["LUCK+2"], OptionInfo["HP+9"]},
	Sum300 = {OptionInfo["STR+4"], OptionInfo["DEX+4"], OptionInfo["DAM+3"], OptionInfo["RES+5"], OptionInfo["ATTR+2"]},
}


ItemClassSlayerSet = 
{
	ItemClassInfo["ITEM_CLASS_RING"],
	ItemClassInfo["ITEM_CLASS_BRACELET"],
	ItemClassInfo["ITEM_CLASS_NECKLACE"]
}


-- select ItemClass
ItemClass 	= selectOne( ItemClassSlayerSet )

-- select ItemType, OptionType by SUM
ItemType 	= 0
OptionType 	= 0

if SUM <= 80 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Sum140 )

elseif SUM <= 140 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Sum140 )

elseif SUM <= 170 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Sum200 )

elseif SUM <= 200 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Sum200 )

elseif SUM <= 225 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Sum250 )

elseif SUM <= 250 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Sum250 )

elseif SUM <= 275 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Sum300 )

else -- SUM < 300 then
	ItemType = 8
	OptionType = selectOne( OptionInfoSet.Sum300 )

end


