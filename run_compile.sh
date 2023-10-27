#!/bin/bash
while getopts s:a:p: flag
do
    # shellcheck disable=SC2220
    case "${flag}" in
        s) isServer=${OPTARG};;
        a) address=${OPTARG};;
        p) port=${OPTARG};;
    esac
done
echo "Server: $isServer";
echo "Address: $address";
echo "Port: $port";

if [ "$isServer" = true ]
then
  g++ main.cpp -o server && ./server "$address" "$port" 1
else
  g++ main.cpp -o client && ./client "$address" "$port" 0
fi