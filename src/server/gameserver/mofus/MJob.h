/////////////////////////////////////////////////////////////////////////////
// filename	: MJob.h
// desc		: 모퍼스에 연결해서 파워포인트를 가져오는 하나의 작업 단위
/////////////////////////////////////////////////////////////////////////////

#ifndef __MJOB_H__
#define __MJOB_H__

class MJob
{
public:
	MJob( const string& userID, const string& name, const string& cellnum )
		: m_UserID(userID), m_Name(name), m_CellNum(cellnum),
		m_PowerPoint(0), m_ErrorCode(0), m_bEnd(false)
	{
	}

public:
	// 포인트 누적
	void addPowerPoint( int point ) { m_PowerPoint += point; }

	// get
	int getPowerPoint() const { return m_PowerPoint; }
	const string& getUserID() const { return m_UserID; }
	const string& getName() const { return m_Name; }
	const string& getCellNum() const { return m_CellNum; }

	// get/set errorcode
	int getErrorCode() const { return m_ErrorCode; }
	void setErrorCode( int errorCode ) { m_ErrorCode = errorCode; }

	// get/set end job
	bool isEnd() const { return m_bEnd; }
	void setEnd( bool bEnd = true ) { m_bEnd = bEnd; }

private:
	// 사용자 ID 
	string m_UserID;

	// 캐릭터 명
	string m_Name;

	// 핸드폰 번호
	string m_CellNum;

	// 가져온 포인트
	int m_PowerPoint;

	// 에러 코드
	int m_ErrorCode;

	// 작업이 끝났나?
	bool m_bEnd;
};

#endif

