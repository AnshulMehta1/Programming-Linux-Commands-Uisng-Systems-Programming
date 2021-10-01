//  Touch command
//  Create a new file inside each directory and sub directory recursively
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#define MAX_PATH 1024

void  touch (const char *dir,const char *fileName, char path[4096]) {
     // "dirent" object provides us with an internal function
    struct dirent *d;
    DIR *dh =opendir(path);
    // Error Handling Block
    if (!dh){
        return ;
        if (errno== ENOENT){
            perror("Directory does not exist");
        }
        else{
            perror("Unable to read the  filel");
        }
        exit(EXIT_FAILURE);
    }
    // Char array for newpath
    // ls same logic 
    char newpath[4096]="";
    strcat(newpath,path);
    strcat(newpath,"/");
    strcat(newpath,fileName);
    printf("%s\n",newpath);

    // Creating file on the specified path
    
    int f2= open(newpath, O_CREAT | S_IRUSR | S_IWUSR);
    
    while ((d= readdir(dh))!= NULL)
    {
        if (d->d_name[0]=='.'){
            //cwd
            continue;
        }
        printf("%s\n",d->d_name);
       // Just calling LS to show that the file has been created
      

    }
    
}

int main(int argc,const char *argv[]){
   
    // Two args --> ./touch , filename [to be created]
    if(argc==2){
        touch(".",argv[1],".");
    }
    else{
       
        perror("Enter valid Command");
    }
    return 0;
}


/*
1)Input
./touch filename
The file that needs to be created
2) Output
The specified filename is created in all dirs and all sub dirs present 
That is illustrated by calling all the files and sub dirs and the filename is present everywhere
Ref:
Source for  if((int)d->d_type==4){
    Dirent Header Files
#define DT_UNKNOWN       0
#define DT_FIFO          1
#define DT_CHR           2
#define DT_DIR           4
#define DT_BLK           6
#define DT_REG           8
#define DT_LNK          10
#define DT_SOCK         12
#define DT_WHT          14
*/
