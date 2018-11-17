@echo off
g++ -std=c++11 main.cpp -I "..\..\server" -L "..\..\libs" -lserver -lws2_32 -o mainServer

g++ -std=c++11 test.cpp -I "..\..\tools" -L "..\..\libs" -ltest -lws2_32 -o mainClient
pause