#!/bin/bash

while true
do
	a=$(leaks 21sh > /tmp/leakout.txt)
	wait $!
	clear
	cat /tmp/leakout.txt
	sleep 0.5
done
