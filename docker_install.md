
docker create odk-network

## Install using Docker


First, build the docker image:

```bash
docker build -t darkeden .
```


Second, run the container

```bash
docker run -v `pwd`:/home/darkeden/vs/ -it darkeden /bin/bash
```
docker run --name odk-server --network odk-network -v `pwd`:/home/darkeden/vs/ -it darkeden /bin/bash


-p 9999:9999/tcp -p 9999:9999/udp -p 9998:9998/tcp -p 9998:9998/udp -p 9997:9997/tcp -p 9997:9997/udp -p 9996:9996/tcp -p 9996:9996/udp -p 9977:9977/tcp -p 9977:9977/udp -p 9900:9900/tcp -p 9900:9900/udp -p 9876:9876/tcp -p 9876:9876/udp -p 9800:9800/tcp -p 9800:9800/udp -p 5001:5001/tcp -p 5001:5001/udp -p 5000:5000/tcp -p 5000:5000/udp -p 3306:3306/tcp -p 3306:3306/udp -p 3001:3001/tcp -p 3001:3001/udp -p 2999:2999/tcp -p 2999:2999/udp -p 1111:1111/tcp -p 1111:1111/udp

On Windows `pwd` should be changed to %cd%

```
docker run -v %cd%/:/home/darkeden/vs/ -it darkeden /bin/bash
```

Third, build the darkeden server binary files

```
make
```

and you can add `-j 8` to the `make` command.

--------------------


### Install the Database

docker run --name odk-mysql \
	--network odk-network \
	-v `pwd`/initdb/:/home/ \
	-d mysql/mysql-server:5.7 \
	--sql-mode='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION'
