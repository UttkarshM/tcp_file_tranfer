#include<iostream>
#include<fstream>
using namespace std;

void fstreamm(char* buffer){
    fstream file;
    string std;
    file.open(buffer,ios::in);
    while(getline(file,std)){
        cout<<std<<endl;
    }
}

int main(){
    char buffer[]="server.cpp";
    fstreamm(buffer);
    return 0;
}