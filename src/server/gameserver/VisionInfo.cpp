////////////////////////////////////////////////////////////////////////////////
// Filename    : Vision.cpp
// Written By  : Reiot
// Description : 
////////////////////////////////////////////////////////////////////////////////

#include "VisionInfo.h"
#include "Assert.h"
#include "LogClient.h"

////////////////////////////////////////////////////////////////////////////////
// global variable definition
////////////////////////////////////////////////////////////////////////////////
VisionInfoManager* g_pVisionInfoManager = NULL;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
VisionInfo::VisionInfo (Sight_t sight , Dir_t dir) 
	
{
	__BEGIN_TRY

	m_Sight = sight;
	m_Dir   = dir;

	// 임시 시야 영역
	VisionState temp1[maxVisionWidth][maxVisionHeight];
	VisionState temp2[maxVisionWidth][maxVisionHeight];

	//--------------------------------------------------------------------------------
	// temp1, temp2, m_Rect 를 모두 OUT_OF_SIGHT로 초기화한다.
	//--------------------------------------------------------------------------------
	for (int x = 0 ; x < maxVisionWidth ; x ++) {
		for (int y = 0 ; y < maxVisionHeight ; y ++) {
			m_Rect[x][y] = temp1[x][y] = temp2[x][y] = OUT_OF_SIGHT;
		}
	}

	// 중심점은 (10,11)이 된다.
//	int cx = maxViewportWidth + 1;
//	int cy = maxViewportUpperHeight + 1;
	int cx = maxViewportWidth;
	int cy = maxViewportUpperHeight;

	int startx = max(0 , cx - m_Sight);
	int starty = max(0 , cy - m_Sight);
	int endx   = min(maxVisionWidth - 1 , cx + m_Sight);
	int endy   = min(maxVisionHeight - 1 , cy + m_Sight);

	//--------------------------------------------------------------------------------
	// m_Rect 의 IN_SIGHT, OUT_OF_SIGHT 영역을 지정한다.
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			if (x >= startx && x <= endx && y >= starty && y <= endy) {
				int dist = abs(cx - x) + abs(cy - y);
				if (dist <= m_Sight + (m_Sight >> 1)) {
					m_Rect[x][y] = IN_SIGHT;
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	// temp1 = m_Rect << 1
	//--------------------------------------------------------------------------------
	int dx = 0, dy = 0;

	switch (m_Dir) {
		case LEFT : dx--; break;
		case LEFTDOWN : dx--; dy++; break;
		case DOWN : dy++; break;
		case RIGHTDOWN : dx++; dy++; break;
		case RIGHT : dx++; break;
		case RIGHTUP : dx++; dy--; break;
		case UP : dy--; break;
		case LEFTUP : dx--; dy--; break;
	}

	// 시작과 끝좌표를 주의하라. m_Rect 가 기준이다.
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			temp1[x+dx][y+dy] = m_Rect[x][y];
		}
	}

	//--------------------------------------------------------------------------------
	// temp1 = temp1 - m_Rect
	//--------------------------------------------------------------------------------
	for (int x = 0 ; x < maxVisionWidth ; x ++) {
		for (int y = 0 ; y < maxVisionHeight ; y ++) {
			if (temp1[x][y] == m_Rect[x][y] == IN_SIGHT)
				temp1[x][y] = OUT_OF_SIGHT;
		}
	}
	
	//--------------------------------------------------------------------------------
	// temp2 = temp1 >> 1
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			temp2[x][y] = temp1[x+dx][y+dy];
		}
	}

	//--------------------------------------------------------------------------------
	// m_Rect의 ON_SIGHT 영역을 지정한다.
	//
	// IN_SIGHT 영역중에서, 8방향을 체크해서 1개 이상의 OUT_OF_SIGHT 가 존재할 경우
	// ON_SIGHT 로 지정한다.
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			if (m_Rect[x][y] == IN_SIGHT) {
				if (m_Rect[ x ][y-1] == OUT_OF_SIGHT ||	// north
					 m_Rect[x+1][y-1] == OUT_OF_SIGHT || 	// northeast
					 m_Rect[x+1][ y ] == OUT_OF_SIGHT || 	// east
					 m_Rect[x+1][y+1] == OUT_OF_SIGHT || 	// southeast
					 m_Rect[ x ][y+1] == OUT_OF_SIGHT || 	// south
					 m_Rect[x-1][y+1] == OUT_OF_SIGHT || 	// southwest
					 m_Rect[x-1][ y ] == OUT_OF_SIGHT || 	// west
					 m_Rect[x-1][y-1] == OUT_OF_SIGHT) { 	// northwest
					m_Rect[x][y] = ON_SIGHT;
				}
			}
		}
	}

	//--------------------------------------------------------------------------------
	// m_Rect = m_Rect + temp2
	//--------------------------------------------------------------------------------
	for (int x = 1 ; x < maxVisionWidth - 1 ; x ++) {
		for (int y = 1 ; y < maxVisionHeight - 1 ; y ++) {
			if (temp2[x][y] == IN_SIGHT) {
				Assert(m_Rect[x][y] == ON_SIGHT);
				m_Rect[x][y] = NEW_SIGHT;
			}
		}
	}
	
	if ( sight == 13 ) filelog("VisionInfo.log", "%s", toString().c_str());

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// Q(cx,cy)에 있는 크리처가 P(x,y)를 볼 수 있는지, 없는지.. 그 상태값을 리턴함.
//
// O(a,b)   - Vision Rectangle 의 중심
// P(x,y)   - 보고자 하는 오브젝트의 위치
// Q(cx,cy) - 보는 크리처의 위치
//
// Q를 O로 평행이동한 공식을 사용해서, P를 평행이동한 좌표를 P'(x',y') 이라고 할 때, 
//
//		x' = x + a - cx
//		y' = y + b - cy
//
// 가 된다. 그러면, m_Rect[x'][y']의 값을 리턴하면 된다. (당연히 범위체크를 해야쥐)
//
//--------------------------------------------------------------------------------

VisionState VisionInfo::getVisionState (ZoneCoord_t cx , ZoneCoord_t cy , ZoneCoord_t x , ZoneCoord_t y) const
	
{
	__BEGIN_TRY

	int px = x + (maxViewportWidth + 1) - cx;
	int py = y + (maxViewportUpperHeight + 1) - cy;

	// 평행이동한 좌표의 범위를 체크한다.
	if (px >= 0 && px < maxVisionWidth && py >= 0 && py < maxVisionHeight)
		return m_Rect[px][py];

	return OUT_OF_SIGHT;

	__END_CATCH
}



//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VisionInfo::toString () const
	
{

	__BEGIN_TRY

	StringStream msg;

	msg << "VisionInfo("
			<< "Sight:" << (int)m_Sight
			<< ",Dir: " << Dir2String[m_Dir]
			<< "\r\n";

	for (int y = 0; y < maxVisionHeight ; y++) 
	{
		for (int x = 0; x < maxVisionWidth ; x++)
	 	{
			switch (m_Rect[x][y]) 
			{
				case OUT_OF_SIGHT:  msg << ". ";           break;
				case IN_SIGHT:      msg << "[33m:[m "; break;
				case ON_SIGHT:      msg << "[33m#[m "; break;
			 	case NEW_SIGHT:     msg << "[32m#[m "; break;
			}
		}

		msg << "\r\n";
	}

	msg << ")";

	return msg.toString();

	__END_CATCH
}
*/
//--------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------
VisionInfoManager::~VisionInfoManager () 
	
{

	__BEGIN_TRY

/*	if (m_pVisionInfos)
	{
		for (Sight_t sight = 0 ; sight <= maxSight ; sight ++) 
		{
			if (m_pVisionInfos[sight])
			{
				for (Dir_t dir = 0 ; dir < DIR_MAX ; dir ++) 
				{
					SAFE_DELETE(m_pVisionInfos[sight][dir]);
				}

				SAFE_DELETE_ARRAY(m_pVisionInfos[sight]);
			}
		}

		SAFE_DELETE_ARRAY(m_pVisionInfos);
	}*/

	__END_CATCH_NO_RETHROW
}


//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------
void VisionInfoManager::init () 
	
{

	__BEGIN_TRY

/*	m_pVisionInfos = new VisionInfo ** [ maxSight ];
	Assert(m_pVisionInfos != NULL);

	for (Sight_t sight = 0 ; sight <= maxSight ; sight ++) 
	{
		m_pVisionInfos[sight] = new VisionInfo* [8];
		Assert(m_pVisionInfos[sight] != NULL);

		for (Dir_t dir = 0 ; dir < DIR_MAX ; dir ++) 
		{
			m_pVisionInfos[sight][dir] = new VisionInfo(sight,dir);
			Assert(m_pVisionInfos[sight][dir] != NULL);
		}
	}	*/

	__END_CATCH
}


//--------------------------------------------------------------------------------
// get vision info
//--------------------------------------------------------------------------------
/*
VisionInfo* VisionInfoManager::getVisionInfo (Sight_t sight , Dir_t dir) 
{
	__BEGIN_TRY

	if (sight > maxSight) throw OutOfBoundException("sight overflow");

	if (dir >= DIR_MAX) throw OutOfBoundException("dir overflow");

	return m_pVisionInfos[sight][dir];

	__END_CATCH
}
*/


//--------------------------------------------------------------------------------
// get debug string
//--------------------------------------------------------------------------------
string VisionInfoManager::toString () const
	
{
	__BEGIN_TRY

/*	StringStream msg;

	msg << "VisionInfoManager(";

	for (Sight_t sight = 0 ; sight <= maxSight ; sight ++)
 	{
		for (Dir_t dir = LEFT ; dir <= LEFTUP ; dir ++) 
		{
			msg << m_pVisionInfos[sight][dir]->toString();
		}
	}

	msg << ")";

	return msg.toString();*/

	__END_CATCH
}

