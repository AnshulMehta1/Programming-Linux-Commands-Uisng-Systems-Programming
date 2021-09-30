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

void  _ls (const char *dir, int op_a, int op_l,char path[4096]) {

    // a flag for all files - Include Hidden
    // l flag for list all files in separate line

    // "dirent" object provides us with an internal function
    struct dirent *d;
    // Directory Traversing maate
    DIR *dh =opendir(path);
    // Error Handling Block
    if (!dh){
        return ;
        if (errno== ENOENT){
            // Error NO ENTRY
            perror("Directory does not exist");
        }
        else{
            
            perror("Unable to read the  filel");
            // Not reachable 
        }
        exit(EXIT_FAILURE);

    }
    // Traversal of Opened Directory 
    while ((d= readdir(dh))!= NULL)
    {
        // Hidden File then continue 
        if (!op_a &&  d->d_name[0]=='.'){
            continue;
        }
        // Print File name
        printf("%s\n",d->d_name);
        // Nested not required in this approach
        //  DIR *dhnested =opendir(d->d_name);
        // if(dhnested){
        //     printf("Sub Directory ----> %s\n",d->d_name);
        //     _ls(d->d_name,op_a,op_l); // Recursive Call for the nested sub dirs

        // }
        if((int)d->d_type==4){
            char str[4096]="";
             // Concatenate the subsequent paths
            strcat(str,path);
            strcat(str,"/");
            strcat(str,d->d_name);
            printf("SUB directory %s\n",str);
            // Recursive Call
            _ls(d->d_name,op_a,op_l,str);
        }
        if (op_l){
            printf("\n");
        }
    }
    printf("Dir %s All files and SUB Dirs Printed\n",dir);
    printf("Recursive Call for %s Completed",dir);
    
}
// Main Funnction
int main(int argc,const char *argv[]){
    if (argc==1){
        _ls(".",0,0,".");
        // if only ls called
    }
    else if(argc==2){
        // if flags given --> ./ls -a or ./ls -o
        if(argv[1][0]== '-'){
            int op_a =0;
            int op_l=0;
            char *p=(char*)(argv[1]+1);
            // Input for the args
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

            _ls(".",op_a,op_l,".");
        }
    }
    else{
        printf("Enter valid Commands\n");
    }
    return 0;
}
/*
Input Options
1) ./ls (Normal Mode)
2)./ls -a (INclude Hidden FIles)
3) ./ls -l (New Line Print for Files --> Exclude Hidden Files)
Directory Structure
Lab-4-FInal (with files)
     |
   Nested (SUb DIR with N1.txt)
     |
   Nested-Nested (Sub Dir with N2.txt)
     |
   Nested Nested-Nested (Sub Dir with N3.txt)
Output
stat.c
ls
mv1.c
mv
stat
touch.c
wc
mv.c
mv1
wc.c
Nested
SUB directory ./Nested
Nested-Nested
SUB directory ./Nested/Nested-Nested
Nested-Nested-Nested
SUB directory ./Nested/Nested-Nested/Nested-Nested-Nested
N3.txt
Dir Nested-Nested-Nested All files and SUB Dirs Printed
Recursive Call for Nested-Nested-Nested Completed
N2.txt
Dir Nested-Nested All files and SUB Dirs Printed
Recursive Call for Nested-Nested Completed
N1.txt
Dir Nested All files and SUB Dirs Printed
Recursive Call for Nested Completed
touch
ls.c
Dir . All files and SUB Dirs Printed
Recursive Call for . Completed
Ref: https://stackoverflow.com/questions/4989431/how-to-use-s-isreg-and-s-isdir-posix-macros
*/
