#pragma once
#include <iostream>
#include "buffer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class buffHandler
{
public:
    void printData();
    void printSum();
    void countSum();
    void sendData();
    void getDataFromBuf();
    void start();
    buffHandler(std::shared_ptr<Buffer> b);
private:
  std::string str;
  int sum;
  std::shared_ptr<Buffer> buf;
};