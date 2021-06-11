#include "SlayerAttrExpTable.h"

const string SlayerAttrExpTable::DBTableName[ATTR_KIND_MAX] = { "STRBalanceInfo", "DEXBalanceInfo", "INTBalanceInfo" };
SlayerAttrExpTable SlayerAttrExpTable::s_SlayerAttrExpTable[ATTR_KIND_MAX] = { ATTR_KIND_STR, ATTR_KIND_DEX, ATTR_KIND_INT };
