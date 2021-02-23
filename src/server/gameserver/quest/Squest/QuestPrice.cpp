//--------------------------------------------------------------------------------
// QuestPrice.h
//--------------------------------------------------------------------------------

#include "QuestPrice.h"

//--------------------------------------------------------------------------------
// setPrice
//
// c   a   bc       a   b
// Gold=100, RankExp=100, Fame=100
//--------------------------------------------------------------------------------
void	
QuestPrice::setPrice(const string& text)
	throw (Error)
{
	__BEGIN_TRY

	Gold_t    Gold 		= 0;
	RankExp_t RankExp 	= 0;
	Fame_t    Fame 		= 0;

	uint a=0, b=0, c=0;

	while (c < text.size() - 1)
	{
		a = text.find_first_of('=', c);
		if (a==string::npos) break;

		string attr   = trim(text.substr(c, a-c));


		b = text.find_first_of(',', a+1);
		int value  = atoi( trim(text.substr(a+1, b-a-1)).c_str() );

		if (attr == "Gold")
		{
			Gold = value;
		}
		else if (attr == "RankExp")
		{
			RankExp = value;
		}
		else if (attr == "Fame")
		{
			Fame = value;
		}
		else
		{
			StringStream msg;
			msg << "QuestPrice-setPrice-attrError(" << attr << ")";
			throw Error(msg.toString());
		}

		if (b==string::npos) break;
		c = b+1;
	}

	m_Gold 		= Gold;
	m_RankExp	= RankExp;
	m_Fame		= Fame;

	__END_CATCH
}

string	
QuestPrice::toString() const 
	throw (Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Gold=" << (int)m_Gold
		<< ", RankExp=" << (int)m_RankExp
		<< ", Fame=" << (int)m_Fame;

	return msg.toString().c_str();

	__END_CATCH
}
