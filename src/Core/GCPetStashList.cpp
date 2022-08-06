//////////////////////////////////////////////////////////////////////////////
// Filename    : GCPetStashList.cpp 
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "GCPetStashList.h"
#include "Assert1.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GCPetStashList::GCPetStashList() 
	
{
	__BEGIN_TRY
	
	m_PetStashItemInfos.reserve(MAX_PET_STASH);
	for (int i=0; i<MAX_PET_STASH; ++i )
	{
		m_PetStashItemInfos.push_back(NULL);
	}
		
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCPetStashList::~GCPetStashList() 
	
{
	__BEGIN_TRY

	for (int i=0; i<MAX_PET_STASH; ++i )
	{
		SAFE_DELETE(m_PetStashItemInfos[i]);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void GCPetStashList::read (SocketInputStream & iStream ) 
	 
{
	__BEGIN_TRY

	for (int i=0; i < MAX_PET_STASH; i++  )
	{
		BYTE isAvailable;
		iStream.read(isAvailable);
		if (isAvailable == 0 ) continue;

		m_PetStashItemInfos[i] = new PetStashItemInfo;
		m_PetStashItemInfos[i]->pPetInfo = new PetInfo;
		m_PetStashItemInfos[i]->pPetInfo->read(iStream);

		iStream.read(m_PetStashItemInfos[i]->KeepDays);
	}
		
		
	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////////////
void GCPetStashList::write (SocketOutputStream & oStream ) const 
     
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	for (int i=0; i < MAX_PET_STASH; i++ )
	{
		BYTE isAvailable;
		if (m_PetStashItemInfos[i] == NULL )
		{
			isAvailable = 0;
			oStream.write(isAvailable);
			continue;
		}
		else
		{
			isAvailable = 1;
			oStream.write(isAvailable);
		}

		m_PetStashItemInfos[i]->pPetInfo->write(oStream);
		oStream.write(m_PetStashItemInfos[i]->KeepDays);
	}
	
	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCPetStashList::execute (Player * pPlayer ) 
	 
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCPetStashListHandler::execute(this , pPlayer);

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
PacketSize_t GCPetStashList::getPacketSize () const 
	
{ 
	__BEGIN_TRY
	__BEGIN_DEBUG

	PacketSize_t ret = 0;

	for (int i=0; i<MAX_PET_STASH; ++i )
	{
		ret += szBYTE;
		if (m_PetStashItemInfos[i] != NULL )
		{
			ret += m_PetStashItemInfos[i]->pPetInfo->getSize();
			ret += szDWORD;
		}
	}

	return ret;

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
string GCPetStashList::toString () const
       
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCPetStashList(";
	for (int i=0; i<MAX_PET_STASH; ++i )
	{
		if (m_PetStashItemInfos[i] == NULL )
		{
			msg << "NULL,";
		}
		else
		{
			msg << "PetItem(" << m_PetStashItemInfos[i]->pPetInfo->toString() << "," << m_PetStashItemInfos[i]->KeepDays << "),";
		}
	}
	msg << ")";
	return msg.toString();
		
	__END_CATCH
}
