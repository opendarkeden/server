# server

# dependency

libmysqlclient-dev 5.7
lua 4.0
xerces-c 3.2.3

# compile

	make


If your head file are not in the standard path, specify the include path like this:

```
export CPLUS_INCLUDE_PATH=/path/to/your/lua-4.0.1/include:$CPLUS_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/path/to/your/xerces-c-3.2.3/xerces-c-3.2.3/src/:$CPLUS_INCLUDE_PATH

export LIBRARY_PATH=/path/to/your/lua-4.0.1/lib/:$LIBRARY_PATH
export LIBRARY_PATH=/path/to/your/xerces-c-3.2.3/xerces-c-3.2.3/src/.libs/:$LIBRARY_PATH
```


