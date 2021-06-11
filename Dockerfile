FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    --no-install-recommends \
    gcc \
    build-essential \
    libcppunit-dev \
    zlib1g \
    libxerces-c-dev \
    libmysqlclient-dev \
    locate \
    wget \
    liblua5.1-dev \
    xutils-dev \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir /home/darkeden
RUN mkdir /home/darkeden/vs
RUN mkdir /home/darkeden/vs/src

COPY libs /home/darkeden/libs/

#RUN export CPLUS_INCLUDE_PATH=/home/darkeden/libs/lua-4.0.1/include:$CPLUS_INCLUDE_PATH
#RUN export CPLUS_INCLUDE_PATH=/usr/include/xercesc/:$CPLUS_INCLUDE_PATH
#
#RUN export LIBRARY_PATH=/home/darkeden/libs/lua-4.0.1/lib/:$LIBRARY_PATH
#RUN export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/:$LIBRARY_PATH

WORKDIR /home/darkeden/vs/src