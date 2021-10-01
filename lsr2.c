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
void  _ls (const char *dir, int op_a, int op_l) {
    // "dirent" object provides us with an internal function
    struct dirent *d;
    // Directory Traversing maate
    DIR *dh =opendir(dir);
    // This is error Handling block
    if (!dh){
        if (errno== ENOENT){ // Error no Entry
            perror("Directory does not exist");
        }
        else{
            perror("Unable to read the  filel");
        }
        return;
    }
    // This needs to be done recursively
    while ((d= readdir(dh))!= NULL) // Traversal of Opened Directory
    {
        // Hidden files have a . so they can be skipped
        if (!op_a && d->d_name[0]=='.'){
            continue;
        }
        else{
            printf("%s\n",d->d_name);
            // Prints the file names
        }
        
        // If it is a directory then we will again call new DIR dh  and open it for d->d_name
        DIR *dhnested =opendir(d->d_name);
        if(dhnested){
            printf("Sub Directory  %s\n",d->d_name);
            _ls(d->d_name,op_a,op_l); // Recursive Call for the nested sub dirs

        }
        // Prints the name of the file / Dir
        if (op_l){
            printf("\n");
        }

    }
    
}

// op_a --> All FIles (Inclusive of Hidden)
// op_L List all files in a separate line
int main(int argc,const char *argv[]){
    if (argc==1){
        _ls(".",0,0);

    }
    else if(argc==2){
        if(argv[1][0]== "-"){
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
            _ls(".",op_a,op_l);
            
        }

    }

    return 0;
}
// Reason Behind Output
// FIles printed before recursive call, then contents of sub dir printed then remaining files printed after recursive stack emptied
