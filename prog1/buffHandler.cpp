#include "buffHandler.h"

buffHandler::buffHandler(std::shared_ptr<Buffer> b)
{
    buf=b;
    sum=0;
}

void buffHandler::printData()
{
    std::cout<<"Thread №"<<std::this_thread::get_id()<< " received data: "<<std::endl;
    std::cout<<str<<std::endl;
}
 void buffHandler::printSum()
 {
    std::cout<<"Sum of received digits: "<<sum<<std::endl;
 }
void buffHandler::countSum()
{
    sum=0;
     for (char ch : str) {
        if (std::isdigit(ch)) {
            int intValue = ch - '0';
            sum+=intValue;
        }
    }
}
void buffHandler::sendData()
{
    while(true)
    {
        std::cout<<"Trying to establish connection..."<<std::endl;
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd==-1)
        {
            std::cerr<<"Error creating a socket!"<<std::endl;
             std::cout << std::endl;
            
        }
        sockaddr_in serverAddr;
        serverAddr.sin_family=AF_INET;
        serverAddr.sin_port=htons(8080);
        inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
        
        if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
        {
            std::cerr << "Error connecting to the server." << std::endl;
             std::cout << std::endl;
            close(sockfd);
        }
        else
        {
            std::cout<<"Connection successful!"<<std::endl;
            std::string message =std::to_string(sum);
            if (send(sockfd, message.c_str(), message.length(), 0) == -1) 
            {
                std::cerr << "Error sending message." << std::endl;
                 std::cout << std::endl;
            } 
            else 
            {
                std::cout << "Message sent successfully. You can type the next message: " << std::endl;
                std::cout << std::endl;
            }
            close(sockfd);
            break;
        }
    }
}
void buffHandler::getDataFromBuf()
{
    str=buf->getStringFromBuffer();
}

void buffHandler::start()
{
    do
    {
    getDataFromBuf();
    printData();
    countSum();
    printSum();
    sendData();
    }while(true);
}