//////////////////////////////////////////////////////////////////////////////
// Filename    : Geometry.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Types.h"
#include <list>

uint getPointsFromLine(int x1, int y1, int x2, int y2, list<POINT>& rList);
uint getPointsFromVLine(int y1, int y2, int X, list<POINT>& rList);
uint getPointsFromHLine(int x1, int x2, int Y, list<POINT>& rList);

uint getPointsFromLineEx(int x1, int y1, int x2, int y2, int range, list<POINT>& rList);
uint getPointsFromVLineEx(int y1, int y2, int X, int range, list<POINT>& rList);
uint getPointsFromHLineEx(int x1, int x2, int Y, int range, list<POINT>& rList);

#endif
