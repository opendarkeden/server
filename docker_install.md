# Install using Docker

## Build the server binary files

First, build the docker image:

```bash
docker build -t darkeden:dev . -f Dockerfile.dev
```

Second, run the container

```bash
docker run -v `pwd`:/home/darkeden/vs/ -it darkeden:dev /bin/bash
```

On Windows `pwd` should be changed to %cd%

```
docker run -v %cd%/:/home/darkeden/vs/ -it darkeden:dev /bin/bash
```

Third, build the darkeden server binary files

```
make
```

and you can add `-j 8` to the `make` command.

When the build process finish, you can exit docker, and you can see loginserver/sharedserver/gameserver in the bin/ directory.


## Run the binary (development mode)


TODO















## Standalone version

**NOTE:** standalone version only support deploying server and client on the same machine.

If you want to run server on one machine, and client on the other, you need to modify mysql `DARKEDEN.GameServerInfo` table and restart server.

### Pack the binary/config/data files into docker image

```sh
docker build . -t darkeden:latest -f Dockerfile.pub
```

### Run using docker-compose


```sh
cd docker
docker-compose up -d
```

Login to server container:

```
docker exec -w /home/darkeden/vs/bin -it docker_odk-server_1  /bin/bash
```

Run the server:

```
./start.sh
```


Stop all:

```sh
./stop.sh
docker-compose down
```










## Howto

### Login to the MySQL

```sh
docker exec -it docker_odk-mysql_1 mysql -u elcastle -pelca110
```

```SQL
use DARKEDEN;
update GameServerInfo set IP = '192.168.0.16';
```

### Publish the docker image (memo for me)

```sh
docker tag c0bdad60a1a7(TAG) tiancaiamao/darkeden:latest
docker push tiancaiamao/darkeden:latest
```
