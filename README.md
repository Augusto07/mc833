
# Description

This repo contains the client and server modules (UDP and TCP versions). You must run one of them in one computer, and the other in another. Also, the json-c lib is added to repo to not require the user to install it (but in some OSs you must to).


# How to run client and server:

## Server

run at `./server` folder to compile:
~~~ 
gcc -o server server.c -ljson-c
~~~~

Then, run:

~~~ 
./server
~~~~

## Client

run at `./client` folder to compile:
~~~ 
gcc -o client client.c
~~~~

Then, run to connect:

~~~ 
./client <ip_to_connect>
~~~~

## TROUBLESHOOTING

If your code doesn't compile because of json-c lib, you can try:

* Follow instalation steps from https://github.com/json-c/json-c
* Just run the binary (server or client) that is already compiled inside `/server` and `/client` (was compiled in Ubuntu OS).




