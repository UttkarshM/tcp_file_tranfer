#include<iostream>
#include<dirent.h>
#include<sys/types.h>

using namespace std;

int main(){
    DIR* dr;
    struct dirent *en;
    dr= opendir(".");//open this directory
    // to open all main home directories use opendir(".")
    if(dr==NULL){
        return 0;
    }
    while((en=readdir(dr))!=NULL){
        cout<<en->d_name<<" ";
    }
    closedir(dr);
    return 0;
}