#pragma once
#include <iostream>
#include "buffer.h"
class UserInput
{
public:
    std::string getString();
    void setString(std::string s);
    bool isValid();
    void sortByDescending();
    void input();
    void print();
    void start();
    UserInput(std::shared_ptr<Buffer> b);
private:
    std::string str;
    std::shared_ptr<Buffer> buf;
};