FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    gcc \
    build-essential \
    libxerces-c-dev \
    libmysqlclient-dev \
    xutils-dev \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir /home/darkeden
RUN mkdir /home/darkeden/vs
RUN mkdir /home/darkeden/vs/src

COPY libs /home/darkeden/libs/

ENV CPLUS_INCLUDE_PATH=/home/darkeden/libs/lua-4.0.1/include:$CPLUS_INCLUDE_PATH
ENV LIBRARY_PATH=/home/darkeden/libs/lua-4.0.1/lib/:$LIBRARY_PATH

EXPOSE 3306/tcp 3306/udp \
       9999/tcp 9999/udp \
       9998/tcp 9998/udp \
       9997/tcp 9997/udp \
       9996/tcp 9996/udp \
       9977/tcp 9977/udp \
       9900/tcp 9900/udp \
       9876/tcp 9876/udp \
       9800/tcp 9800/udp \
       5001/tcp 5001/udp \
       5000/tcp 5000/udp \
       3001/tcp 3001/udp \
       2999/tcp 2999/udp \
       1111/tcp 1111/udp 

WORKDIR /home/darkeden/vs/src
