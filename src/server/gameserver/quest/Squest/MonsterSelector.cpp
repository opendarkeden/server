#include "MonsterSelector.h"
#include "Assert.h"


// 012345678
// b    a  bc
// MType=11, SType=33, Num=10
void        
MonsterSelector::setMonster(const string& text) 
	throw (Error)
{
	__BEGIN_TRY

	int MType = 0;
	int SType = 0;
	int Num   = 1;

	uint a=0, b=0, c=0;

	while (c < text.size() - 1)
	{
		a = text.find_first_of('=', c);
		if (a==string::npos) break;

		string attr   = trim(text.substr(c, a-c));


		b = text.find_first_of(',', a+1);
		int value  = atoi( trim(text.substr(a+1, b-a-1)).c_str() );

		if (attr == "MType")
		{
			MType = value;
		}
		else if (attr == "SType")
		{
			SType = value;
		}
		else if (attr == "Num")
		{
			Num = value;
		}
		else
		{
			StringStream msg;
			msg << "MonsterKillQuest-setObjective-attrError(" << attr << ")";
			throw Error(msg.toString());
		}

		if (b==string::npos) break;
		c = b+1;
	}

	Assert( MType!=0 || SType!=0 );

	setMonsterType( MType );
	setSpriteType( SType );
	setNumber( Num );

	__END_CATCH
}

string
MonsterSelector::toString() const
    throw (Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "MType=" << (int)getMonsterType()
		<< ", SType=" << (int)getSpriteType()
		<< ", Num=" << (int)getNumber();

	return msg.toString();

	__END_CATCH
}

