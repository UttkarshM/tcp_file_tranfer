#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<chrono>
#define port 8080
#define size 1024
#define max_clients 20

struct TIMER{ // for checking the performance of each function
    std::string process;
    std::chrono::time_point<std::chrono::system_clock> start,end;
    TIMER(const std::string process1){//constructor gets activated when the scope of the function or like the function starts
        process=process1;
        start=std::chrono::high_resolution_clock::now();
    }
    ~TIMER(){ //deconstructer gets activated when the scope of the function also ends
        end=std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        auto dur=duration.count();//we used auto as the time takes is very small and not in the range of double or float so we are using this so that it can automatically decide the data type of the time.
        std::cout<<"time take for the "<<process<<":"<<dur<<std::endl;
    }
};
void ep(std::string arr){
    std::cout<<"error in "<<arr<<std::endl;
    exit(1);
}

void SOCKET(int& sockfd){
    TIMER time("socket");
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        ep("socket");
    }
    std::cout<<"socket created successfully"<<std::endl;
}
void CONNECT(int& sockfd,struct sockaddr_in& client){
    TIMER time("connection");
    memset(&client,'\0',sizeof(client));
    client.sin_family=AF_INET;
    client.sin_port=htons(port);
    client.sin_addr.s_addr=inet_addr("127.0.0.1");//converts newtwork address(generally) into readable string from ipv4;
    if(connect(sockfd,(struct sockaddr*)&client,sizeof(client))<0)
    {
        ep("connecting");
    }
    std::cout<<"connection has been established successfully"<<std::endl;
}

void CHAT(int& sockfd){
    char buffer[size];
    int n=0;
    while(1){   
    memset(&buffer,'\0',sizeof(buffer));
    read(sockfd,&buffer,sizeof(buffer));
    if(strncmp(buffer,"exit.",4)==0){
        break;
    }
    std::cout<<buffer<<"\n";
    }
    memset(&buffer,'\0',sizeof(buffer));
    std::cout<<"enter the file to be sent:";
    //while((buffer[n++]=getchar())!='\n');//this is not givin correct as it has \n in the end
    std::string std;
    std::cin>>std;
    strcpy(buffer,std.c_str());
    write(sockfd,buffer,sizeof(buffer));//sends the file required.
    
    std::cout<<"\n";
    std::cout<<"\n";
    std::cout<<"\n";
    std::cout<<"\n";
    std::cout<<"\n";
    std::cout<<"\n"; // spacing the outputs in the output terminal.

    while(1){//the msg sent now is the file.   
    memset(&buffer,'\0',sizeof(buffer));
    read(sockfd,&buffer,sizeof(buffer));
    if(strncmp(buffer,"exit.",4)==0){
        break;
    }
    std::cout<<buffer<<"\n";
    }
    std::cout<<"connection has ended"<<std::endl;
}


int main(){
    using namespace std::literals::chrono_literals;
    int sockfd;
    struct sockaddr_in client;
    SOCKET(sockfd);
    CONNECT(sockfd,client);
    CHAT(sockfd);
    close(sockfd);
return 0;
}