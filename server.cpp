#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<cstring>
#include<string.h>
#include<chrono>
#define port 2100
#define size 1024
#define max_clients 20

struct TIMER{ // for checking the performance of each function
    std::string process;
    std::chrono::time_point<std::chrono::system_clock> start,end;
    TIMER(std::string process1){//constructor gets activated when the scope of the function or like the function starts
        process=process1;
        start=std::chrono::high_resolution_clock::now();
    }
    ~TIMER(){ //deconstructer gets activated when the scope of the function also ends
        end=std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::time_t dur=duration.count()*1000;//we multiplied it by 1000 cause we want in milli seconds.
        std::cout<<"time take for the "<<process<<":"<<dur<< "ms"<<std::endl;
    }
};
void ep(std::string arr){
    std::cout<<"error in "<<arr<<std::endl;
    exit(1);
}
void SOCKET(int& sockfd){
    TIMER timer("socket");
    sockfd=socket(AF_INET,SOCK_STREAM,0);//tcp  connection
    if(sockfd<0){
        ep("socket");
    }
    std::cout<<"socket created successfully"<<std::endl;
}

void REUSESOCK(int& sockfd,int opt){
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))<0){
        ep("socket resuablitily");
    }
}
void BIND(int& sockfd,struct sockaddr_in& server){
    TIMER timer("bind");
    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server)<0)){
        ep("bind");
    }
    std::cout<<"binding was successfull"<<std::endl;
}
void LISTEN(int& sockfd){
    if(listen(sockfd,max_clients)<0){
        ep("listening");
    }
    std::cout<<"device found..."<<std::endl;
}
void ACCEPT(int& sockfd,struct sockaddr_in& server,int& newsockfd,socklen_t siz){
    siz=sizeof(server);
    newsockfd=accept(sockfd,(struct sockaddr*)&server,&siz);
    if(newsockfd<0){
        ep("Accepting");
    }
    std::cout<<"accepted the client..."<<std::endl;
}

void CHAT(){}
int main(){
    using namespace std::literals::chrono_literals;
    int sockfd,newsocfd,opt=1;
    socklen_t siz;
    struct sockaddr_in server;

    SOCKET(sockfd);
}