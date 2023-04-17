#include<iostream>
#include<cstdlib>
#include<string.h>
#include<fstream>

using namespace std;

int main(){
    int n=0;
    string cd="cd ";
    string path="/home/uttkarsh/c++_programming/socket/Tcp_single_client/tcp_file/";
    string _and="&& ls -l";
    //-l gives time and sizes also.
    //only ls gives only the names
    //string _and="&& ls"
    string final_command=cd+path+_and;
    char buff[100];
    char data[100];
    strcpy(buff,final_command.c_str());
    system(buff);//system takes only const char* commands
    //while((buff[n++]=,system(buff)))
    char file_list[1000]="";
    /*fstream fo;
    if(!fo){//if file doesnt exit;
    fstream create_file;
    create_file.open("test.txt",ios::out);
    }
    fo.open("test.txt",ios::app);//app means append
    while(getline(fo,system(buff))!=EOF);
    */
    cout<<data;
    return 0;
}