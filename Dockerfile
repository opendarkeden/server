FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    gcc \
    build-essential \
    libxerces-c-dev \
    libmysqlclient-dev \
    xutils-dev \
    psmisc \
    && rm -rf /var/lib/apt/lists/*
	
RUN apt install -y psmisc

RUN mkdir /home/darkeden
RUN mkdir /home/darkeden/vs
RUN mkdir /home/darkeden/vs/src

COPY libs /home/darkeden/libs/

ENV CPLUS_INCLUDE_PATH=/home/darkeden/libs/lua-4.0.1/include:$CPLUS_INCLUDE_PATH
ENV LIBRARY_PATH=/home/darkeden/libs/lua-4.0.1/lib/:$LIBRARY_PATH

WORKDIR /home/darkeden/vs/src
