--------------------------------------------------------------------------------
--
-- premiumEventItemVampire.lua
--
--------------------------------------------------------------------------------
-- 이거 사용하기 전에 premiumEventItemVampire.lua를 실행해야 한다.
-- Input  : Level
-- Output : ItemClass, ItemType, OptionType
--------------------------------------------------------------------------------
-- select ItemClass
ItemClass 	= selectOne( ItemClassVampireSet )

-- select ItemType, OptionType by Level
ItemType 	= 0
OptionType 	= 0
OptionType2	= 0

if Level <= 20 then
	ItemType = 3
	OptionType = selectOne( OptionInfoSet.Level20 )
	OptionType2 = selectOne( OptionInfoSet2.Level20 )

elseif Level <= 40 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Level40 )
	OptionType2 = selectOne( OptionInfoSet2.Level40 )

elseif Level <= 50 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Level50 )
	OptionType2 = selectOne( OptionInfoSet2.Level50 )

elseif Level <= 60 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Level60 )
	OptionType2 = selectOne( OptionInfoSet2.Level60 )

elseif Level <= 70 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Level70 )
	OptionType2 = selectOne( OptionInfoSet2.Level70 )

elseif Level <= 80 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Level80 )
	OptionType2 = selectOne( OptionInfoSet2.Level80 )

elseif Level <= 90 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Level90 )
	OptionType2 = selectOne( OptionInfoSet2.Level90 )

else -- Level < 100 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Level100 )
	OptionType2 = selectOne( OptionInfoSet2.Level100 )

end


