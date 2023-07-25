#include "buffer.h"

void Buffer::setBuffer(std::string s)
{
    std::unique_lock<std::mutex> lock(mutex); // Захватываем мьютекс перед доступом к буферу
    cvProducer.wait(lock, [this] { return !isFull; }); // Ожидаем, пока буфер не освободится
    str = s;
    isFull = true; // Указываем, что буфер заполнен
    cvConsumer.notify_one(); // Оповещаем потребителя
}

std::string Buffer::getStringFromBuffer()
{
    std::unique_lock<std::mutex> lock(mutex); // Захватываем мьютекс перед доступом к буферу
    cvConsumer.wait(lock, [this] { return isFull; }); // Ожидаем, пока буфер не заполнится
    std::string tmp = str;
    clearBuffer();
    return tmp;
}


void Buffer::clearBuffer()
{
    str.clear();
    isFull = false; // Указываем, что буфер пуст
    cvProducer.notify_one(); // Оповещаем производителя
}
