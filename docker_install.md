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
