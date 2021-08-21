#!/bin/sh
killall loginserver
killall sharedserver
killall gameserver

sleep 1
cd /home/darkeden/vs/bin

rm -rf loginserver*.out
rm -rf gameserver*.out
rm -rf sharedserver*.out

sleep 3
./login &

sleep 1
./game &

sleep 1
./share &

echo "DKL - START"
