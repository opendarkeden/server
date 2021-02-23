////////////////////////////////////////////////////////////////////////////////
// Filename    : VisionInfo.h
// Written By  : Reiot
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __VISIONINFO_H__
#define __VISIONINFO_H__

#include "Types.h"
#include "Exception.h"

const Coord_t maxViewportWidth  = 10;
const Coord_t maxViewportUpperHeight = 14;
const Coord_t maxViewportLowerHeight = 14;
const Coord_t maxVisionWidth = maxViewportWidth * 2 + 1;
const Coord_t maxVisionHeight = maxViewportUpperHeight + maxViewportLowerHeight + 1;

////////////////////////////////////////////////////////////////////////////////
// class VisionInfo;
// P(x,y) 가 시야 레벨이 Sight 이며, 특정 방향(dir)을 바라보는 O(cx,cy) 위치의 
// 크리처가 볼 수 있는지의 여부를 런타임에 계산하지 않고, 이미 계산된 값을 시야 
// 레벨과 방향별 시야 사각형에 저장해두면 시야 체크를 보다 빨리 할 수 있게 된다.
// 이 클래스는, 이 때 사용되는 시야 사각형을 나타낸다.
////////////////////////////////////////////////////////////////////////////////

/*class VisionInfo 
{
public:
	VisionState getVisionState(ZoneCoord_t cx, ZoneCoord_t cy, ZoneCoord_t x, ZoneCoord_t y) const throw()
	{
		// inline for speed. by sigi. 2002.11.8
//		int px = x + (maxViewportWidth + 1) - cx;
//		int py = y + (maxViewportUpperHeight + 1) - cy;
		int px = x + (maxViewportWidth) - cx;
		int py = y + (maxViewportUpperHeight) - cy;

		// 평행이동한 좌표의 범위를 체크한다.
		if (px >= 0 && px < maxVisionWidth && py >= 0 && py < maxVisionHeight)
			return m_Rect[px][py];

		return OUT_OF_SIGHT;
	}
	string toString() const throw();
		
private:
	// 시야 레벨(0 - 13)
	Sight_t m_Sight;

	// 바라보는 방향
	Dir_t m_Dir;

	// viewport rectangle
	VisionState m_Rect[maxVisionWidth][maxVisionHeight];
	// deprecated. 이 클래스는 더이상 안 쓴다.
	VisionInfo(Sight_t sight, Dir_t dir) throw();
	~VisionInfo();
};
*/

////////////////////////////////////////////////////////////////////////////////
// class VisionInfoManager;
// 시야 정보를 관리하며, 시야 레벨과 방향을 주면 그에 해당하는 시야 정보를 리턴한다.
////////////////////////////////////////////////////////////////////////////////

class VisionInfoManager 
{
public:
	VisionInfoManager() throw() {}
	~VisionInfoManager() throw();

public:

	// init vision info
	void init() throw();

	// get vision info
/*	VisionInfo* getVisionInfo(Sight_t sight, Dir_t dir) //throw(OutOfBoundException)
	{
		// for speed. by sigi. 2002.11.8
		//__BEGIN_TRY
		//if (sight > maxSight) throw OutOfBoundException("sight overflow");
		//if (dir >= DIR_MAX) throw OutOfBoundException("dir overflow");

		return m_pVisionInfos[sight][dir];

		//__END_CATCH
	}*/

	static VisionState getVisionState( ZoneCoord_t SourceX, ZoneCoord_t SourceY, ZoneCoord_t TargetX, ZoneCoord_t TargetY )
	{
		int diffX = abs( TargetX-SourceX );
		int diffY = (int)TargetY-(int)SourceY;

		bool isInX = diffX <= maxViewportWidth;
		bool isInY = (diffY<0)?
			((-diffY)<=maxViewportUpperHeight):
			(diffY<=maxViewportLowerHeight);

		return (isInX&&isInY)?IN_SIGHT:OUT_OF_SIGHT;
	}

	// get debug string
	string toString() const throw();

private:

	// VisionInfo의 이차원 배열
//	VisionInfo *** m_pVisionInfos;

};

// global variable declaration
extern VisionInfoManager* g_pVisionInfoManager;

#endif

