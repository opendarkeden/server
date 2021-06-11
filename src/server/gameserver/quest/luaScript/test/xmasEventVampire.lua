--------------------------------------------------------------------------------
--
-- xmasEventVampire.lua
--
--------------------------------------------------------------------------------
-- 이거 사용하기 전에 xmasEventCommon.lua를 실행해야 한다.
-- Input  : Level
-- Output : ItemClass, ItemType, OptionType
--------------------------------------------------------------------------------

-- select ItemClass
ItemClass 	= selectOne( ItemClassVampireSet )

-- select ItemType, OptionType by Level
ItemType 	= 0
OptionType 	= 0

if Level <= 20 then
	ItemType = 2
	OptionType = selectOne( OptionInfoSet.Level20 )

elseif Level <= 40 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Level40 )

elseif Level <= 60 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Level60 )

elseif Level <= 80 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Level80 )

else -- Level < 100 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Level100 )

end


