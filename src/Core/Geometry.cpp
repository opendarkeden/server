//////////////////////////////////////////////////////////////////////////////
// Filename    : Geometry.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Geometry.h"
#include <stdlib.h>

uint getPointsFromLine(int x1, int y1, int x2, int y2, list<POINT>& rList)
{
// Draw line in surface 

	double xStep, yStep, X, Y;
	int xLength, yLength, xCount, yCount, tmp;
	xLength = abs(x2 - x1);
	yLength = abs(y2 - y1);

	if (xLength == 0)
	{
		return getPointsFromVLine(y1, y2, x1, rList);
	}
	else if (yLength == 0)
	{
		return getPointsFromHLine(x1, x2, y1, rList);
	}
	else if (xLength > yLength)
	{
		if(x1 > x2)
		{
			SWAP(x1, x2, tmp);
			SWAP(y1, y2, tmp);
		}
		yStep = (double)(y2 - y1) / (double)(x2 - x1);
		Y = y1;
		for (xCount = x1; xCount <= x2; xCount++)
		{
			// 마지막 점이라면 기울기를 무시하고,
			// 강제로 마지막 좌표를 집어넣는다.
			if (xCount == x2)
			{
				rList.push_front(POINT(x2, y2));
			}
			else
			{
				rList.push_front( POINT(xCount, (int)Y) );
				Y += yStep;
			}
		}
	}
	else
	{
		if (y1 > y2)
		{
			SWAP(x1, x2, tmp);
			SWAP(y1, y2, tmp);
		}
		xStep = (double)(x2 - x1) / (double)(y2 - y1);
		X = x1;
		for (yCount = y1; yCount <= y2; yCount++)
		{
			if (yCount == y2)
			{
				rList.push_back(POINT(x2, y2));
			}
			else
			{
				rList.push_front( POINT((int)X, yCount) );
				X += xStep;
			}
		}
	}

	return rList.size();
}

uint getPointsFromVLine(int y1, int y2, int X, list<POINT>& rList)
{
	int temp;
	if (y1 > y2) SWAP(y1, y2, temp);

	for (int i=y1; i <= y2; i++) rList.push_front(POINT(X, i));
	return rList.size();
}

uint getPointsFromHLine(int x1, int x2, int Y, list<POINT>& rList)
{
	int temp;
	if (x1 > x2) SWAP(x1, x2, temp);

	for(int i = x1; i <= x2; i++) rList.push_front(POINT(i, Y));
	return rList.size();
}

uint getPointsFromLineEx(int x1, int y1, int x2, int y2, int range, list<POINT>& rList)
{
	int xLength, yLength, nx2, ny2;
	xLength = abs(x2 - x1);
	yLength = abs(y2 - y1);

	if (xLength == 0)
	{
		return getPointsFromVLineEx(y1, y2, x1, range, rList);
	}
	else if (yLength == 0)
	{
		return getPointsFromHLineEx(x1, x2, y1, range, rList);
	}
	else if (xLength > yLength)
	{
		//cout << "xLength:" << xLength << endl;

		// 현재의 X 길이가 사정거리보다 길다면 그냥 선을 그어서 리턴한다. 
		if (xLength >= range) return getPointsFromLine(x1, y1, x2, y2, rList);

		// 모자란 길이를 구한다.
		int xoffset = range - xLength;

		//cout << "xOffset:" << xoffset << endl;

		if (x1 < x2) nx2 = x2 + xoffset;
		else         nx2 = x2 - xoffset;

		//cout << "nx2:" << nx2 << endl;

		double yoffset = (double)(y2 - y1) / (double)(x2 - x1) * (double)xoffset;

		//cout << "yOffset:" << yoffset << endl;

		if (y1 < y2) ny2 = y2 + abs((int)yoffset);
		else         ny2 = y2 - abs((int)yoffset);

		//ny2 = y2 - (int)yoffset;

		//cout << "ny2:" << ny2 << endl;

		getPointsFromLine(x1, y1, nx2, ny2, rList);
	}
	else
	{
		//cout << "yLength:" << yLength << endl;

		// 현재의 Y 길이가 사정거리보다 길다면 그냥 선을 그어서 리턴한다. 
		if (yLength >= range) return getPointsFromLine(x1, y1, x2, y2, rList);

		// 모자란 길이를 구한다.
		int yoffset = range - yLength;

		//cout << "yOffset:" << yoffset << endl;

		if (y1 < y2) ny2 = y2 + yoffset;
		else         ny2 = y2 - yoffset;

		//cout << "ny2:" << ny2 << endl;

		double xoffset = (double)(x2 - x1) / (double)(y2 - y1) * (double)yoffset;

		//cout << "xOffset:" << xoffset << endl;

		if (x1 < x2) nx2 = x2 + abs((int)xoffset);
		else         nx2 = x2 - abs((int)xoffset);
		//nx2 = x2 - (int)xoffset;

		//cout << "nx2:" << nx2 << endl;

		getPointsFromLine(x1, y1, nx2, ny2, rList);
	}

	// getPointsFromLineEx()는 x^2 + y^2 = r^2과 y = ax의 교점을 찾아서,
	// 원점에서 교점까지의 좌표들을 리스트로 리턴하는 함수인데,
	// 알고리즘 상에서의 문제로 인해 (x2,y2), 즉 처음에 목표로 했던 
	// 좌표가 빠지는 경우가 생길 수 있다.
	// 이런 경우를 방지하기 위해서 리스트에 원래 목표 좌표가 없다면,
	// 집어넣어 준다.
	bool bAdd = true;
	list<POINT>::iterator itr = rList.begin();
	for (; itr != rList.end(); itr++)
	{
		if (((*itr).x == x2) && ((*itr).y == y2))
		{
			bAdd = false;
			break;
		}
	}

	if (bAdd)
	{
		rList.push_front(POINT(x2, y2));
	}

	return rList.size();
}

uint getPointsFromVLineEx(int y1, int y2, int X, int range, list<POINT>& rList)
{
	int yLength = abs(y2 - y1);
	if (yLength < range)
	{
		if (y2 > y1) y2 = y2 + range - yLength;
		else         y2 = y2 - range + yLength;
	}

	return getPointsFromVLine(y1, y2, X, rList);
}

uint getPointsFromHLineEx(int x1, int x2, int Y, int range, list<POINT>& rList)
{
	int xLength = abs(x2 - x1);
	if (xLength < range)
	{
		if (x2 > x1) x2 = x2 + range - xLength;
		else         x2 = x2 - range + xLength;
	}

	return getPointsFromHLine(x1, x2, Y, rList);
}
