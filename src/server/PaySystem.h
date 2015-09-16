//////////////////////////////////////////////////////////////////////////////
// Filename   : PaySystem.h
// Written by : sigi
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PAY_SYSTEM_H__
#define __PAY_SYSTEM_H__

#include "Types.h"
#include "Timeval.h"
#include "VSDateTime.h"
#include "Exception.h"

class Statement;


enum PayPlayType {
    PAY_PLAY_TYPE_PERSON,   // 개인 요금
    PAY_PLAY_TYPE_PCROOM,   // 게임방 요금
    PAY_PLAY_TYPE_ETC,      // 기타(뭐지.. 그냥 넣어둠 -_-;)
    PAY_PLAY_TYPE_MAX
};

enum PayType {
    PAY_TYPE_FREE,      // 무료 사용자
    PAY_TYPE_PERIOD,    // 월 사용자
    PAY_TYPE_TIME,      // 시간제 사용자
    PAY_TYPE_POST,      // 후불 시간제 사용자
    PAY_TYPE_MAX
};

enum PayIPType {
    PAY_IP_TYPE_ALL,        // IP전체
    PAY_IP_TYPE_LIMIT,      // 동시접속 사용대수 제한
    PAY_IP_TYPE_ASSIGN,     // 특정IP
    PAY_IP_TYPE_MAX
};

enum FamilyPayPartyType {
    FAMILY_PAY_PARTY_TYPE_NONE,
    FAMILY_PAY_PARTY_TYPE_FREE_PASS,        // 패밀리 요금제 파티 유료존 출입가능
    FAMILY_PAY_PARTY_TYPE_FREE_PASS_END,    // 패밀리 요금제 파티 유료존 출입가능 끝
};

#define PAY_PLAY_FLAG_ALL 0xFFFF
#define PAY_PLAY_FLAG_ZONE 0x0001


#define __PAY_SYSTEM_ZONE__            // Zone 출입여부에 PaySystem을 적용
//#define __PAY_SYSTEM_LOGIN__         // Login여부에 PaySystem을 적용
//#define __PAY_SYSTEM_FREE_LIMIT__    // 게임 불가 사용자인 경우, 자체 무료 서비스로..


class PaySystem {
public:
    PaySystem();
    ~PaySystem() {};

    PayPlayType getPayPlayType() const { return m_PayPlayType; }
    void setPayPlayType(PayPlayType ppt) { m_PayPlayType = ppt; }

    uint getPCRoomID() const { return m_PCRoomID; }
    void setPCRoomID(uint id) { m_PCRoomID = id; }

    PayType getPayType() const { return m_PayType; }
    void setPayType(PayType pt) { m_PayType = pt; }

    PayIPType getPayIPType() const { return m_PayIPType; }
    void setPayIPType(PayIPType pipt) { m_PayIPType = pipt; }

    uint getPayPlayFlag() const { return m_PayPlayFlag; }
    void setPayPlayFlag(uint ppf) { m_PayPlayFlag = ppf; }
    bool hasPayPlayFlag(uint flag) const { return m_PayPlayFlag & flag; }

    void setPayPlayAvailableDateTime(const string& pat) throw(Error);
    const VSDateTime& getPayPlayAvailableDateTime() const { return m_PayPlayAvailableDateTime; }

    void setFamilyPayPlayAvailableDateTime(const string& pat) throw(Error);
    const VSDateTime& getFamilyPayPlayAvailableDateTime() const    { return m_FamilyPayPlayAvailableDateTime; }

    void setPayStartAvailableDateTime(const string& pat) throw(Error);
    const VSDateTime& getPayStartAvailableDateTime() const { return m_PayStartAvailableDateTime; }

    Timeval    getPayPlayTime(const Timeval& currentTime) const { return timediff(m_PayPlayStartTime, currentTime); }
    void setPayPlayStartTime(const Timeval& tv)    { m_PayPlayStartTime = tv; }

    void setPayPlayAvailableHours(int h) { m_PayPlayAvailableHours = h; }
    int getPayPlayAvailableHours() const { return m_PayPlayAvailableHours; }

    bool checkPayPlayAvailable();

    void setPayPlayValue(PayType payType, const string& payPlayDate, int payPlayHours, uint payPlayFlag, const string& familyPayPlayDate = "");
    
    bool loginPayPlay(PayType payType, const string& payPlayDate, int payPlayHours, uint payPlayFlag, const string& ip, const string& playerID) throw(Error);

    bool loginPayPlay(const string& ip, const string& playerID) throw(Error);

    bool updatePayPlayTime(const string& playerID, const VSDateTime& currentDateTime, const Timeval& currentTime) throw(ProtocolException, Error);

    void logoutPayPlay(const string& playerID, bool bClear=false, bool bDecreaseTime=true) throw(Error);

    bool isPayPlaying() const { return m_PayPlayStartTime.tv_sec!=0; }

    void setPremiumPlay(bool bPremium=true)  { m_bPremiumPlay = bPremium; }
    bool isPremiumPlay() const { return m_bPremiumPlay; }

    void setFamilyPayAvailable(bool bFamilyPayAvailable=true) { m_bFamilyPayAvailable = bFamilyPayAvailable; }
    bool isFamilyPayAvailable() const { return m_bFamilyPayAvailable; }

    void setFamilyPayPartyType(FamilyPayPartyType familyPayPartyType) { m_FamilyPayPartyType = familyPayPartyType; }
    bool isFamilyFreePass() const { return m_FamilyPayPartyType == FAMILY_PAY_PARTY_TYPE_FREE_PASS; }
    bool isFamilyFreePassEnd() const { return m_FamilyPayPartyType == FAMILY_PAY_PARTY_TYPE_FREE_PASS_END; }

    void setPCRoomPlay(bool bPCRoom = true) { m_bPCRoomPlay = bPCRoom; }
    bool isPCRoomPlay() const { return m_bPCRoomPlay; }

    static bool isPayPlayingPeriodPersonal(const string& PlayerID) throw(Error);

    bool isPlayInPayPCRoom(const string& ip, const string& playerID ) throw(Error);

protected :
    bool loginPayPlayPCRoom(const string& ip, const string& playerID) throw(Error);
    void logoutPayPlayPCRoom(const string& playerID) throw(Error);

    void decreasePayPlayTime(const string& playerID, uint mm) throw(Error);
    void decreasePayPlayTimePCRoom(uint mm) throw(Error);

    void increasePayPlayTimePCRoom(uint mm) throw(Error);

    void clearPayPlayDateTime(const string& playerID) throw(Error);

    bool m_bSetPersonValue;

    PayPlayType m_PayPlayType;
    ObjectID_t m_PCRoomID;
    uint m_UserLimit;
    uint m_UserMax;
    
    PayType m_PayType;
    PayIPType m_PayIPType;

    VSDateTime m_PayStartAvailableDateTime;
    VSDateTime m_PayPlayAvailableDateTime;
    int m_PayPlayAvailableHours;
    Timeval m_PayPlayStartTime;
    VSDateTime m_FamilyPayPlayAvailableDateTime;

    uint m_PayPlayFlag;

    bool m_bPremiumPlay;
    bool m_bPCRoomPlay;

    bool m_bFamilyPayAvailable;
    FamilyPayPartyType m_FamilyPayPartyType;
};

#endif
