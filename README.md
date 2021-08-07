![](https://user-images.githubusercontent.com/1420062/121156821-a0d86180-c87b-11eb-9b41-4d75940f2d88.png)


If you're using Windows or Docker environment, skip the following content and see [install using docker](./docker_install.md).


## Compile

The development environment is Ubuntu 20.04, other linux release should also work.

### dependency

- libmysqlclient-dev 5.7
- lua 4.0
- xerces-c 3.2.3

lua 4.0 has to be download from the internet, other dependencies can be installed using `apt`.

### compile

If your head file are not in the standard path, specify the include path like this:

```
export CPLUS_INCLUDE_PATH=/path/to/your/lua-4.0.1/include:$CPLUS_INCLUDE_PATH
// export CPLUS_INCLUDE_PATH=/path/to/your/xerces-c-3.2.3/xerces-c-3.2.3/src/:$CPLUS_INCLUDE_PATH

export LIBRARY_PATH=/path/to/your/lua-4.0.1/lib/:$LIBRARY_PATH
// export LIBRARY_PATH=/path/to/your/xerces-c-3.2.3/xerces-c-3.2.3/src/.libs/:$LIBRARY_PATH
```

And then compile is easy, just call:

	make

or `make -j 8` if you have a 8 cores CPU computor to accelerate the compilation.

## Setup the Database

MySQL8 is tested, MySQL5.7 might also work.


Create a user 'elcastle'@'%' with password 'elca110'

Create the `DARKEDEN` and `USERINFO` database:

```
create database DARKEDEN;
create database USERINFO;
```

Make sure the `sql_mode` allow [zero date time](https://github.com/opendarkeden/server/issues/5), remove the `NO_ZERO_DATE` from the `sql_mode`:

```
mysql> select @@global.sql_mode;
+-------------------------------------------------------------------------------------------------------------------------------------------+
| @@global.sql_mode                                                                                                                         |
+-------------------------------------------------------------------------------------------------------------------------------------------+
| ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION |
+-------------------------------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)

mysql> set @@global.sql_mode = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';
Query OK, 0 rows affected (0.02 sec)
```

Then load the SQL file `data/DARKEDEN.sql` and `data/USERINFO.sql`:

```
mysql -h 127.0.0.1 -u elcastle -D 'DARKEDEN' -p < initdb/DARKEDEN.sql
mysql -h 127.0.0.1 -u elcastle -D 'USERINFO' -p < initdb/USERINFO.sql
```

Update the `DARKEDEN.WorldDBInfo` and `DARKEDEN.GameServerInfo` table to set the correct IP/PORT().

## Modify Configure

You need to change the configure files in the `conf/` directory.
`HomePath` should be the repository directory path.

The `DB_HOST` should be you database IP address, `LoginServerIP` should also be changed accordingly.

**DON'T forget the `DARKEDEN.WorldDBInfo` and `DARKEDEN.GameServerInfo` tables in the database**, they are not in the configure files, but the data should match, otherwise you can't login.

## Start the server

Start the loginserver, sharedserver, gameserver in order:

```
./bin/loginserver -f ./conf/loginserver.conf
./bin/sharedserver -f ./conf/sharedserver.conf
./bin/gameserver -f ./conf/gameserver.conf
```

