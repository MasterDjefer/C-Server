@echo off
g++ -std=c++11 main.cpp Request.cpp Response.cpp RequestParser.cpp Server.cpp -lws2_32  -o main
main
pause