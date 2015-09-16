SET(LIBDATABASE_SRC Connection.cpp
	Statement.cpp 
	DatabaseManager.cpp
	Result.cpp)
ADD_LIBRARY(Database STATIC ${LIBDATABASE_SRC})
