#pragma once
#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>

class Buffer
{
public:
    void setBuffer(std::string s);
    std::string getStringFromBuffer();
    void clearBuffer();
private:
    std::string str;
    bool isFull = false; // Переменная, указывающая, что буфер заполнен
    std::mutex mutex;
    std::condition_variable cvProducer;
    std::condition_variable cvConsumer;
};