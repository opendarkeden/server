INCLUDE_DIRECTORIES(/usr/local/include/mysql)

SET(LIBCBilling_SRC 
	CBillingPacketErrorBody.cpp
	CBillingPacketHeader.cpp
	CBillingPacketRequestIntervalValidationBody.cpp
	CBillingPacketRequestLoginBody.cpp
	CBillingPacketRequestLogoutBody.cpp
	CBillingPacketRequestMinusMinuteBody.cpp
	CBillingPacketRequestMinusPointBody.cpp
	CBillingPacketResponseIntervalValidationBody.cpp
	CBillingPacketResponseLoginBody.cpp
	CBillingPacketResponseLogoutBody.cpp
	CBillingPacketResponseMinusMinuteBody.cpp
	CBillingPacketResponseMinusPointBody.cpp
	CBillingPlayer.cpp
	CBillingPlayerInfo.cpp
	CBillingPlayerManager.cpp
	)
ADD_LIBRARY(CBilling STATIC ${LIBCBilling_SRC})
