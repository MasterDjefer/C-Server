@echo off
g++ -std=c++11 main.cpp -I "D:\Projects\C\C-Server\server" -L "D:\Projects\C\C-Server\libs" -lserver -lws2_32 -o mainServer

g++ -std=c++11 test.cpp -I "D:\Projects\C\C-Server\tools" -L "D:\Projects\C\C-Server\libs" -ltest -lws2_32 -o mainClient
pause