#!/bin/sh
killall gameserver
killall sharedserver
killall loginserver

sleep 1
cd /home/darkeden/vs/bin

rm -rf loginserver*.out
rm -rf gameserver*.out
rm -rf sharedserver*.out

sleep 3
./login &
echo "login server started"

sleep 1
./share &
echo "shared server started"

sleep 1
./game &
echo "game server started"


echo "ALL - START"
