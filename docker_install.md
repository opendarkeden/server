## Install using Docker

### Build the server binary files

First, build the docker image:

```bash
docker build -t darkeden .
```

Second, run the container

```bash
docker run -v `pwd`:/home/darkeden/vs/ -it darkeden /bin/bash
```

On Windows `pwd` should be changed to %cd%

```
docker run -v %cd%/:/home/darkeden/vs/ -it darkeden /bin/bash
```

Third, build the darkeden server binary files

```
make
```

and you can add `-j 8` to the `make` command.


## Prepare the MySQL database

Pull the docker image.

```sh
docker pull mysql/mysql-server:5.7
```

Create a docker network for the server and database container to reach to each other later.

```sh
docker network create odk-network
```

Build the container.

```sh
docker run --name odk-mysql \
	--network odk-network \
	-v `pwd`/initdb/:/home/ \
	-d mysql/mysql-server:5.7 \
	--sql-mode='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION'
```

Several things to notice here:

- the container name is `odk-mysql`
- the container specify the network `odk-network`
- `NO_ZERO_DATE` is not in the sql mode 
- Directory `/initdb/` is mount to `/home/`, On windows, `pwd` should be %cd%

Load the database

You have to change the password before you can continue, follow the MySQL guildline [here](https://dev.mysql.com/doc/mysql-installation-excerpt/8.0/en/docker-mysql-getting-started.html)

```
docker exec -it odk-mysql bash
cd /home/
```

Setup the database follow [those steps](https://github.com/opendarkeden/server/blob/master/README.md#setup-the-database)


### Run the server

```
docker run --name odk-server --network odk-network -v `pwd`:/home/darkeden/vs/ -it darkeden /bin/bash
```

In another terminal:

```
docker exec -it odk-server /bin/bash
```

Run the server:

```
cd ../bin;
./bin/loginserver -f conf/loginserver-docker.conf
./bin/shardserver -f conf/sharedserver-docker.conf
./bin/gameserver -f conf/gameserver-docker.conf
```
