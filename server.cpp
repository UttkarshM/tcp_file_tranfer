#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<cstring>
#include<string.h>
#include<chrono>
#define port 9000
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
        auto dur=duration.count();//we use auto bcs neither double nor float has the range of the time which will be written(in the form of e).
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
    TIMER timer("binding");
    memset(&server,'\0',sizeof(server));//allocating memory for the server 
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    
    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0){
        ep("bind");
    }
    std::cout<<"binding was successfull"<<std::endl;
}
void LISTEN(int& sockfd){
    TIMER timer("listening");
    if(listen(sockfd,max_clients)<0){
        ep("listening");
    }
    std::cout<<"device found..."<<std::endl;
}
void ACCEPT(int& sockfd,struct sockaddr_in& server,int& newsockfd,socklen_t siz){
    TIMER timer("accepting");
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
    int sockfd,newsockfd,opt=1;
    socklen_t siz;
    struct sockaddr_in server1;

    SOCKET(sockfd);
    REUSESOCK(sockfd,opt);
    BIND(sockfd,server1);
    LISTEN(sockfd);
    ACCEPT(sockfd,server1,newsockfd,siz);
    close(newsockfd);
    shutdown(sockfd,SHUT_RDWR);
    return 0;
}