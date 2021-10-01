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

// LS is used to iterate a file and the statbuf is used to print details about the file
void  statfunc (const char *dir, int op_a, int op_l,char path[4096]) {
       // a flag for all files - Include Hidden
    // l flag for list all files in separate line
     // "dirent" object provides us with an internal function

    struct dirent *d;
    DIR *dh =opendir(path);
    // char currentPath[FILENAME_MAX];
    // System call stat
    struct stat statbuf;
    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */
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
    // Ls call only stat used to print stuff
    while ((d= readdir(dh))!= NULL)
    {
        if (!op_a &&  d->d_name[0]=='.'){
            continue;
        }
        // printf("%s\n",d->d_name);
            stat(d->d_name,&statbuf);
            printf("\n");
            printf("%s\n",d->d_name);
            // Prints the file names
            // Prints all info for that particular file    
            printf("Size %d\n",(int)statbuf.st_size);
            printf("User ID %d\n",statbuf.st_uid);
            printf("Device Id %d\n",statbuf.st_dev);
            printf("INode %d\n",statbuf.st_ino);
            printf("Blocks %d\n",statbuf.st_blocks);
            printf("Status Change TIme: %ld\n",statbuf.st_ctime);
            printf("Last access time %d\n",statbuf.st_atim);
            printf("Last Modification Time: %ld\n",statbuf.st_mtime);
            
       
        if((int)d->d_type==4){
            char str[4096]="";
            strcat(str,path);
            //  Concatenate the subsequent paths of sub directories
            strcat(str,"/");
            strcat(str,d->d_name);
            printf("SUB directory %s\n",str);
          
            statfunc(d->d_name,op_a,op_l,str);
        }
        if (op_l){
            // NL
            printf("\n");
        }
    }
    printf("Dir %s ke All files and SUB Dirs Printed\n",dir);
    printf("Recursive Call for %s Completed",dir);
    
}
// Main same as the ls

int main(int argc,const char *argv[]){
    if (argc==1){
        statfunc(".",0,0,".");
    }
    else if(argc==2){
        if(argv[1][0]== '-'){
            int op_a =0;
            int op_l=0;
            char *p=(char*)(argv[1]+1);
            while(*p){
                if (*p == 'a'){
                    op_a=1;
                }
                else if(*p== 'l'){
                    op_l=1;

                }
                else{
                    perror("Option Not available");
                    exit(EXIT_FAILURE);
                }
                p++;
            }
            statfunc(".",op_a,op_l,".");
        }
    }
    else{
        printf("Enter valid command\n");
    }
    return 0;
}
/*
Input
1) ./stat
Output
SIze
User ID
Device ID
Inode
Blocks
Last access time
Last status Change Time
Last Modified time
Ref:https://man7.org/linux/man-pages/man2/lstat.2.html
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
