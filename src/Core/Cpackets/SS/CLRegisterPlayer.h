//--------------------------------------------------------------------------------
// 
// Filename    : CLRegisterPlayer.h 
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

#ifndef __CL_REGISTER_PLAYER_H__
#define __CL_REGISTER_PLAYER_H__

// include files
#include "Packet.h"
#include "PacketFactory.h"

//--------------------------------------------------------------------------------
//
// class CLRegisterPlayer;
//
// 클라이언트가 로그인 서버에게 최초에 전송하는 패킷이다.
// 아이디와 패스워드가 암호화되어 있다. 아직은 아니당..
//
//--------------------------------------------------------------------------------

class CLRegisterPlayer : public Packet {

public:
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_CL_REGISTER_PLAYER; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw()
	{
		// 최적화시 미리 계산된 상수를 사용하도록 한다.
		return    szBYTE + m_ID.size() 			// 아이디
				+ szBYTE + m_Password.size() 	// 암호
				+ szBYTE + m_Name.size() 		// 이름
				+ szBYTE						// 성별
				+ szBYTE + m_SSN.size() 		// 주민등록번호
				+ szBYTE + m_Telephone.size() 	// 전화번호
				+ szBYTE + m_Cellular.size() 	// 휴대폰번호
				+ szBYTE + m_ZipCode.size() 	// 우편번호
				+ szBYTE + m_Address.size() 	// 주소
				+ szBYTE 						// 국가코드
				+ szBYTE + m_Email.size() 		// 전자메일
				+ szBYTE + m_Homepage.size() 	// 홈페이지
				+ szBYTE + m_Profile.size() 	// 자기소개글
				+ szBYTE;						// 공개여부
	}

	// get packet name
	string getPacketName() const throw() { return "CLRegisterPlayer"; }
	
	// get packet's debug string
	string toString() const throw();

public:

	//----------------------------------------------------------------------
	// *CAUTION* 
	// 각 setXXX()들은 최대 길이를 체크해서 truncate 하지만, 최소길이는 
	// 체크하지 않는다. 최소 길이는 read()/write() 에서 체크된다. 
	//----------------------------------------------------------------------

    // get/set player's id
	string getID() const throw() { return m_ID; }
	void setID(string id) throw() { m_ID =(id.size() > maxIDLength) ? id.substr(0,maxIDLength) : id; }

    // get/set player's password
    string getPassword() const throw() { return m_Password; }
    void setPassword(string password) throw() { m_Password =(password.size() > maxPasswordLength) ? password.substr(0,maxPasswordLength) : password; }

    // get/set player's name
    string getName() const throw() { return m_Name; }
    void setName(string name) throw() { m_Name =(name.size() > maxNameLength) ? name.substr(0,maxNameLength) : name; }

    // get/set player's sex
    Sex getSex() const throw() { return m_Sex; }
    void setSex(Sex sex) throw() { m_Sex = sex; }

    // get/set player's ssn
    string getSSN() const throw() { return m_SSN; }
    void setSSN(string ssn) throw() { m_SSN =(ssn.size() > maxSSNLength) ? ssn.substr(0,maxSSNLength) : ssn; }

    // get/set player's telephone
    string getTelephone() const throw() { return m_Telephone; }
    void setTelephone(string telephone) throw() { m_Telephone =(telephone.size() > maxTelephoneLength) ? telephone.substr(0,maxTelephoneLength) : telephone; }

    // get/set player's cellular
    string getCellular() const throw() { return m_Cellular; }
    void setCellular(string cellular) throw() { m_Cellular =(cellular.size() > maxCellularLength) ? cellular.substr(0,maxCellularLength) : cellular; }

    // get/set player's zipcode
    string getZipCode() const throw() { return m_ZipCode; }
    void setZipCode(string zipcode) throw() { m_ZipCode =(zipcode.size() > maxZipCodeLength) ? zipcode.substr(0,maxZipCodeLength) : zipcode; }

    // get/set player's address
    string getAddress() const throw() { return m_Address; }
    void setAddress(string address) throw() { m_Address =(address.size() > maxAddressLength) ? address.substr(0,maxAddressLength) : address; }

    // get/set player's nation
    Nation getNation() const throw() { return m_Nation; }
    void setNation(Nation nation) throw() { m_Nation = nation; }

    // get/set player's email
    string getEmail() const throw() { return m_Email; }
    void setEmail(string email) throw() { m_Email =(email.size() > maxEmailLength) ? email.substr(0,maxEmailLength) : email; }

    // get/set player's homepage
    string getHomepage() const throw() { return m_Homepage; }
    void setHomepage(string homepage) throw() { m_Homepage =(homepage.size() > maxHomepageLength) ? homepage.substr(0,maxHomepageLength) : homepage; }

    // get/set player's profile
    string getProfile() const throw() { return m_Profile; }
    void setProfile(string profile) throw() { m_Profile =(profile.size() > maxProfileLength) ? profile.substr(0,maxProfileLength) : profile; }

	// get/set player info's publicability(?) 
	bool getPublic() const throw() { return m_bPublic; }
	void setPublic(bool bPublic) throw() { m_bPublic = bPublic; }

private :

	//--------------------------------------------------
	// 플레이어 기본 정보
	//--------------------------------------------------
    string m_ID; 			// 아이디
    string m_Password; 		// 패스워드
	//--------------------------------------------------
	// 플레이어 개인 정보
	//--------------------------------------------------
    string m_Name; 			// 이름
    Sex m_Sex; 				// 성별
    string m_SSN; 			// 주민등록번호
	//--------------------------------------------------
	// 플레이어 연락처/주소
	//--------------------------------------------------
    string m_Telephone; 	// 전화번호
    string m_Cellular; 		// 핸드폰
    string m_ZipCode; 		// 우편번호
    string m_Address; 		// 주소
    Nation m_Nation; 		// 국가 코드
	//--------------------------------------------------
	// 플레이어 전자정보
	//--------------------------------------------------
    string m_Email; 		// 전자메일
    string m_Homepage; 		// 홈페이지
	//--------------------------------------------------
	// 기타 
	//--------------------------------------------------
    string m_Profile; 		// 하고픈말
	bool m_bPublic; 		// 공개 여부

};


//--------------------------------------------------------------------------------
//
// class CLRegisterPlayerFactory;
//
// Factory for CLRegisterPlayer
//
//--------------------------------------------------------------------------------

class CLRegisterPlayerFactory : public PacketFactory {

public:
	
	// create packet
	Packet* createPacket() throw() { return new CLRegisterPlayer(); }

	// get packet name
	string getPacketName() const throw() { return "CLRegisterPlayer"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CL_REGISTER_PLAYER; }

	// get packet's max body size
	PacketSize_t getPacketMaxSize() const throw()
	{
		// 최적화시 미리 계산된 상수를 사용하도록 한다.
		return    szBYTE + maxIDLength 			// 아이디
				+ szBYTE + maxPasswordLength 	// 패스워드
				+ szBYTE + maxNameLength 		// 이름
				+ szBYTE									// 성별
				+ szBYTE + maxSSNLength 		// 주민등록번호
				+ szBYTE + maxTelephoneLength 	// 전화번호
				+ szBYTE + maxCellularLength 	// 휴대폰번호
				+ szBYTE + maxZipCodeLength 	// 우편번호
				+ szBYTE + maxAddressLength 	// 주소
				+ szBYTE 									// 국가코드
				+ szBYTE + maxEmailLength 		// 전자메일
				+ szBYTE + maxHomepageLength 	// 홈페이지
				+ szBYTE + maxProfileLength 	// 자기소개
				+ szBYTE;									// 공개여부
	}


};


//--------------------------------------------------------------------------------
//
// class CLRegisterPlayerHandler;
//
//--------------------------------------------------------------------------------

class CLRegisterPlayerHandler {

public:

	// execute packet's handler
	static void execute(CLRegisterPlayer* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
