## Install using Docker


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
