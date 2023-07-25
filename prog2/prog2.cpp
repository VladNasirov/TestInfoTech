#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void handleData(char* buffer, int size);
int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY; 

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding to port." << std::endl;
        close(sockfd);
        return 1;
    }

    if (listen(sockfd, 5) == -1) {
        std::cerr << "Error listening for connections." << std::endl;
        close(sockfd);
        return 1;
    }

    std::cout << "Server started. Listening for connections..." << std::endl;

    while (true) {
        std::cout<<"Waitng data..."<<std::endl;
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);

        int clientSock = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSock == -1) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }

        char buffer[1024];
        int bytesRead = recv(clientSock, buffer, sizeof(buffer), 0);
        if (bytesRead == -1) {
            std::cerr << "Error receiving data." << std::endl;
            close(clientSock);
            continue;
        }
        handleData(buffer, bytesRead);

        close(clientSock);
    }

    close(sockfd);

    return 0;
}


void handleData(char* buffer, int size)
{
    
    int sum;
    if(size>2)
    {
        sum=std::stoi(buffer);
        if(sum%32==0)
        {

            std::cout<<"Data received!"<<std::endl;
            std::cout<<"Sum = "<<sum<<std::endl;
        }
        else
        {
            std::cerr<<"Sum isn`t a multiple of 32!!"<<std::endl;
        }
    }
    else
        {
            std::cerr<<"Sum isn`t 2 digits or more!"<<std::endl;
        }
}