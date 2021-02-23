#include "RewardInfo.h"
#include "StringStream.h"

RewardInfo::RewardInfo( RewardID_t rID, RewardClass_t rClass )
{
	m_RewardID = rID;
	m_RewardClass = rClass;
}

RewardInfo::~RewardInfo()
{
}

string RewardInfo::toString() const throw()
{
	StringStream msg;

	msg << "RewardInfo("
		<< ", RewardID : " << m_RewardID
		<< ")";

	return msg.toString();
}
