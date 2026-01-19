//
// Filename    : BloodBibleBonusInfo.cpp
// Written By  :
// Description :
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////////////////////////
#include "BloodBibleBonusInfo.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
BloodBibleBonusInfo::BloodBibleBonusInfo() {
    __BEGIN_TRY

    m_Type = 0;
    m_Race = 0;

    __END_CATCH
}


//////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////
BloodBibleBonusInfo::~BloodBibleBonusInfo() noexcept {
    try {
        clearOptionTypeList();
    } catch (...) {
        // swallow errors during destruction
    }
}


//////////////////////////////////////////////////////////////////////
// Initialize the packet by reading data from the input stream.
//////////////////////////////////////////////////////////////////////
void BloodBibleBonusInfo::read(SocketInputStream& iStream) {
    __BEGIN_TRY

    //	BYTE szOptionList;

    //	iStream.read( m_Type );
    iStream.read(m_Race);

    /*	iStream.read( szOptionList );
        for ( int i = 0 ; i < szOptionList; i++ )
        {
            OptionType_t optionType;
            iStream.read( optionType );
            m_OptionTypeList.push_back( optionType );
        }
    */
    __END_CATCH
}

//////////////////////////////////////////////////////////////////////
// Serialize the packet into the output stream.
//////////////////////////////////////////////////////////////////////
void BloodBibleBonusInfo::write(SocketOutputStream& oStream) const {
    __BEGIN_TRY

    //	oStream.write( m_Type );
    oStream.write(m_Race);

    /*	BYTE szOptionList = m_OptionTypeList.size();
        oStream.write( szOptionList );

        OptionTypeListConstItor itr = m_OptionTypeList.begin();
        for ( ; itr != m_OptionTypeList.end(); itr++ )
        {
            OptionType_t optionType = *itr;
            oStream.write( optionType );
        }
    */
    __END_CATCH
}

/////////////////////////////////////////////////////////////////////
//
// get packet's debug string
//
//////////////////////////////////////////////////////////////////////
string BloodBibleBonusInfo::toString() const {
    __BEGIN_TRY

    StringStream msg;

    msg << "BloodBibleBonusInfo( "
        //		<< "Type:" << (int)m_Type
        << "Race:"
        << (int)m_Race
        //		<< "OptionTypeListSize:" << (int)m_OptionTypeList.size()
        << ")";

    return msg.toString();

    __END_CATCH
}
