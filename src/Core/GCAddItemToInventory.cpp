//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCAddItemToInventory.cpp 
// Written By  : elca@ewestsoft.com
// Description : �ڽſ��� ���� ����� ������ �˸��� ���� ��Ŷ Ŭ������
//               ��� ����.
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "GCAddItemToInventory.h"



//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCAddItemToInventory::GCAddItemToInventory () 
     
{
	__BEGIN_TRY
	m_ObjectID = 0;
	m_X = 0;
	m_Y = 0;
	m_ItemClass = 0;
	m_ItemType = 0;
	m_ItemNum = 0;
	m_Durability = 0;

	
//	m_ListNum = 0;
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
GCAddItemToInventory::~GCAddItemToInventory () noexcept = default;


//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCAddItemToInventory::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

    iStream.read(m_ObjectID);
    iStream.read(m_X);
    iStream.read(m_Y);
    iStream.read(m_ItemClass);
    iStream.read(m_ItemType);

	BYTE optionSize;
    iStream.read(optionSize);
	for (int i=0; i<optionSize; i++)
	{
		OptionType_t optionType;
		iStream.read(optionType);
		addOptionType(optionType);
	}

    iStream.read(m_Durability);
    iStream.read(m_ItemNum);
/*
    iStream.read(m_ListNum);
    for(int i = 0; i < m_ListNum; i++ ) {
        SubItemInfo * pSubItemInfo = new SubItemInfo();
        pSubItemInfo->read(iStream);
        m_SubItemInfoList.push_back(pSubItemInfo);
    }
*/


	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCAddItemToInventory::write (SocketOutputStream & oStream ) 
     const 
{
	__BEGIN_TRY

	oStream.write(m_ObjectID);
    oStream.write(m_X);
    oStream.write(m_Y);
    oStream.write(m_ItemClass);
    oStream.write(m_ItemType);

	BYTE optionSize = m_OptionType.size();
   	oStream.write(optionSize);

	list<OptionType_t>::const_iterator itr = m_OptionType.begin();
   	oStream.write(optionSize);
	for (; itr!=m_OptionType.end(); itr++)
	{
		OptionType_t optionType = *itr;
    	oStream.write(optionType);
	}

    oStream.write(m_Durability);
    oStream.write(m_ItemNum);
/*
    oStream.write(m_ListNum);

    for (list<SubItemInfo*>:: const_iterator itr = m_SubItemInfoList.begin(); itr!= m_SubItemInfoLi
        Assert(*itr != NULL);
        (*itr)->write(oStream);
    }
 
*/
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string GCAddItemToInventory::toString () 
	const 
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCAddItemToInventory("
        << "ObjectID:" << m_ObjectID
        << ",X:" << (int)m_X
        << ",Y:" << (int)m_Y
        << ",ItemClass:" << (int)m_ItemClass
        << ",ItemType:" << (int)m_ItemType
        << ",OptionTypeSize:" << (int)m_OptionType.size()
        << ",Durability:" << (int)m_Durability
        << ",ItemNum: " << (int)m_ItemNum
		<<")";
	return msg.toString();

	__END_CATCH
}

