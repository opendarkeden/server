--------------------------------------------------------------------------------
--
-- premiumEventItemSlayer.lua
--
--------------------------------------------------------------------------------
-- 이거 사용하기 전에 premiumEventItemSlayer.lua를 load해야 한다.
-- Input  : SUM
-- Output : ItemClass, ItemType, OptionType
--------------------------------------------------------------------------------
-- select ItemClass
ItemClass 	= selectOne( ItemClassSlayerSet )

-- select ItemType, OptionType by SUM
ItemType 	= 0
OptionType 	= 0
OptionType2	= 0

if SUM <= 80 then

	ItemType = 3
	OptionType = selectOne( OptionInfoSet.Sum80 )
	OptionType2 = selectOne( OptionInfoSet2.Sum80 )

elseif SUM <= 140 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Sum140 )
	OptionType2 = selectOne( OptionInfoSet2.Sum140 )

elseif SUM <= 170 then
	ItemType = 4
	OptionType = selectOne( OptionInfoSet.Sum170 )
	OptionType2 = selectOne( OptionInfoSet2.Sum170 )

elseif SUM <= 200 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Sum200 )
	OptionType2 = selectOne( OptionInfoSet2.Sum200 )

elseif SUM <= 225 then
	ItemType = 5
	OptionType = selectOne( OptionInfoSet.Sum225 )
	OptionType2 = selectOne( OptionInfoSet2.Sum225 )

elseif SUM <= 250 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Sum250 )
	OptionType2 = selectOne( OptionInfoSet2.Sum250 )

elseif SUM <= 275 then
	ItemType = 6
	OptionType = selectOne( OptionInfoSet.Sum275 )
	OptionType2 = selectOne( OptionInfoSet2.Sum275 )

else -- SUM < 300 then
	ItemType = 7
	OptionType = selectOne( OptionInfoSet.Sum300 )
	OptionType2 = selectOne( OptionInfoSet2.Sum300 )

end


