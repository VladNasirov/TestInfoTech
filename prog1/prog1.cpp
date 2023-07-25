#include "userinput.h"
#include "buffHandler.h"
int main()
{
    std::shared_ptr<Buffer> buf= std::make_shared<Buffer>();

    UserInput producer(buf);
    buffHandler consumer(buf);

    std::thread producerThread(&UserInput::start, &producer);
    std::thread consumerThread(&buffHandler::start, &consumer);
    producerThread.join();
    consumerThread.join();
}