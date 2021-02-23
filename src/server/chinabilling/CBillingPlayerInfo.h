///////////////////////////////////////////////////////////////
//
// filename		: CBillingPlayerInfo.h
//
///////////////////////////////////////////////////////////////

#ifndef __CBILLING_PLAYER_INFO_H__
#define __CBILLING_PLAYER_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "CBillingInfo.h"
#include "VSDateTime.h"

////////////////////////////////////////////////
// class CBillingPlayerInfo
////////////////////////////////////////////////
class CBillingPlayerInfo
{
public:
	// constructor
	CBillingPlayerInfo() throw ( Error );

	// destructor
	virtual ~CBillingPlayerInfo() throw ( Error );

	// get debug string
	virtual string toString() const throw ( Error );

public:
	// get / set CBillingVerified;
	bool isCBillingVerified() const { return m_bCBillingVerified; }
	void setCBillingVerified( bool bVerified = true ) { m_bCBillingVerified = true; }

	// get / set PayPlayer
	bool isPayPlayer() const { return m_bPayPlayer; }
	void setPayPlayer( bool bPayPlayer = true ) { m_bPayPlayer = bPayPlayer; }

	// get / set show pay info
	bool isCBShowPayInfo() const { return m_bShowPayInfo; }
	void setCBShowPayInfo( bool bShowPayInfo = true ) { m_bShowPayInfo = bShowPayInfo; }

	// get /set CBPlayerType
	int getCBPlayerType() const { return m_CBPlayerType; }
	void setCBPlayerType( int cbPlayerType ) { m_CBPlayerType = cbPlayerType; }

	// get /set CBPayType
	int getCBPayType() const { return m_CBPayType; }
	void setCBPayType( int cbPayType ) { m_CBPayType = cbPayType; }

	// get and increase SendID and RecvID
	int increaseSendID() { return ++m_SendID; }
	int increaseRecvID() { return ++m_RecvID; }

	// get SendID and RecvID
	int getSendID() const { return m_SendID; }
	int getRecvID() const { return m_RecvID; }

	// has missed minus point packet
	bool hasMissedMinusPointPacket() const { return m_MissedMinusPointPacket > 0; }
	void decreaseMissedMinusPointPacket() { m_MissedMinusPointPacket--; }
	void increaseMissedMinusPointPacket() { m_MissedMinusPointPacket++; }
	int	getMissedMinusPointPacket() const { return m_MissedMinusPointPacket; }

	// get / set last show left Point 
	int getCBLastShowLeftTime() const { return m_CBLastShowLeftTime; }
	void setCBLastShowLeftTime( int lastShowLeftTime ) { m_CBLastShowLeftTime = lastShowLeftTime; }

	// get / set EndDateTime
	VSDateTime getCBEndDateTime() const { return m_CBEndDateTime; }
	void setCBEndDateTime( VSDateTime endDateTime ) { m_CBEndDateTime = endDateTime; }

	// get / set Left point
	int getCBLeftTime() const { return m_CBLeftTime; }
	void setCBLeftTime( int leftTime ) { m_CBLeftTime = leftTime; }

protected:
	bool	m_bCBillingVerified;
	bool	m_bPayPlayer;
	bool	m_bShowPayInfo;
	int		m_CBPlayerType;
	int		m_CBPayType;

	VSDateTime	m_CBEndDateTime;
	int			m_CBLeftTime;

	int		m_SendID;
	int		m_RecvID;

	int		m_MissedMinusPointPacket;
	int		m_CBLastShowLeftTime;
};

#endif

