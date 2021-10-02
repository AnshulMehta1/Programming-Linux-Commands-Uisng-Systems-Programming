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
// File Size Function
int findSize(const char *file_name){
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");
  
    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    int res = ftell(fp);
  
    // closing the file
    fclose(fp);
  
    return res;
}
void  _ls (const char *dir, int op_a, int op_l,char path[4096]) {
      
    // a flag for all files - Include Hidden
    // l flag for list all files in separate line

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
      // Traversal of Opened Directory 

    while ((d= readdir(dh))!= NULL)
    {
        if (!op_a &&  d->d_name[0]=='.'){
            continue;
        }
        printf("%s\n",d->d_name);
     
     
        if((int)d->d_type==4){
            char str[4096]="";
             // Concatenate the subsequent paths of sub directories
            strcat(str,path);
            strcat(str,"/");
            strcat(str,d->d_name);
           
            printf("SUB directory %s\n",str);
            // Recursive Call
            _ls(d->d_name,op_a,op_l,str);
        }

        else{
            _wc(d->d_name);
        }
        if (op_l){
            printf("\n");
        }
    }
    printf("Dir %s All files and SUB Dirs Printed\n",dir);
    printf("Recursive Call for %s Completed",dir);
    
}


void _wc(const char *fileName){

    int lineC=0;
    int wordC=0;
    long int n;
    char buf[26214]; //  Array of chars
    // Initializing buffer
    int fd1=open(fileName,O_RDONLY);
    // Read Only Mode 
    if(fd1==-1){
        return ;
        // File Does not Exist
    }
    // WHile reading the file till buffer is empty
    while((n = read(fd1, buf, sizeof(buf)))!=0){
       
        for (int i=0; i<n; i++){
           
            if (buf[i] == '\n'){ // new line prompt increase the Line Count
                lineC++;
                wordC++;
            }
            else if( buf[i]==' '||buf[i]=='\t'){ // If a blank space delimeter or tab esc seq then increase wc
                wordC++;
            }
        }
    }
    // FInding the Size
    int size=findSize(fileName);
    printf("Lines %d\n",lineC);
    printf("Words %d\n",wordC);
    printf("Bytes %d\n",size);
   
    return ;
}






// Main Function


int main(int argc,const char *argv[]){
    if (argc==1){
        _ls(".",0,0,".");

    }
    else{
        printf("Enter valid command\n");
    }

    return 0;
}
