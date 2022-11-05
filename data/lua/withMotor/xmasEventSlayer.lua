--------------------------------------------------------------------------------
--
-- xmasEventSlayer.lua
--
--------------------------------------------------------------------------------
-- 이거 사용하기 전에 xmasEventCommon.lua를 load해야 한다.
-- Input  : SUM
-- Output : ItemClass, ItemType, OptionType
--------------------------------------------------------------------------------
-- select ItemClass
ItemClass 	= selectOne( ItemClassSlayerSet )

-- select ItemType, OptionType by SUM
ItemType 	= 0
OptionType 	= 0

if SUM <= 80 then
	ItemClass 	= selectOne( ItemClassSlayerSet80 )

	-- 오토바이이면.. 
	if ItemClass==ItemClassInfo["ITEM_CLASS_KEY"] then
		ItemType = 2
	else
		ItemType = 4
		OptionType = selectOne( OptionInfoSet.Sum140 )
	end

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


