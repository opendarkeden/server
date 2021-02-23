#ifndef __SLAYER_ATTR_EXP_TABLE_H__
#define __SLAYER_ATTR_EXP_TABLE_H__

#include "Types.h"
#include "Exception.h"
#include "ExpFwd.h"
#include "SomethingGrowingUp.h"

#include <string>

class SlayerAttrExpTable : public ExpTable<Exp_t, Attr_t, 1, 315>
{
public:
	SlayerAttrExpTable( AttrKind kind ) : m_Kind(kind)
	{
	}

	const string getDBTableName() const { return DBTableName[m_Kind]; }
	static const string DBTableName[ATTR_KIND_MAX];

private:
	AttrKind	m_Kind;

public:
	static SlayerAttrExpTable s_SlayerAttrExpTable[ATTR_KIND_MAX];
};

typedef SomethingGrowingUp<SlayerAttrExpTable> Attr;

#endif
