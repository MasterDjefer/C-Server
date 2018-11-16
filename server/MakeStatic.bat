g++ -std=c++11 Request.cpp Response.cpp RequestParser.cpp Server.cpp -c
ar rvs ../libs/libserver.a Request.o Response.o RequestParser.o Server.o
del *.o
pause