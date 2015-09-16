#ifndef __EXP_FWD_H__
#define __EXP_FWD_H__

template <typename T> class SomethingGrowingUp;

class RankExpTable;
typedef SomethingGrowingUp<RankExpTable> Rank;

enum AttrKind
{
	ATTR_KIND_STR = 0,
	ATTR_KIND_DEX,
	ATTR_KIND_INT,

	ATTR_KIND_MAX
};

class SlayerAttrExpTable;
typedef SomethingGrowingUp<SlayerAttrExpTable> Attr;

class AdvancementClassExpTable;
typedef SomethingGrowingUp<AdvancementClassExpTable> AdvancementClass;

#endif
