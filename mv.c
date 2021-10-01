#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <errno.h>
#include <dirent.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>


extern int errno;

// Normal Iterative Version 
int main(int argc,const char *argv[]){
    // args 3 --> ./mv fname1 fname2
    // args 4 --> ./mv fname1 fname2 -t flag 
    if(argc!=3 && argc !=4){
        printf("Enter a valid Command with Proper Arguments!\n");
        exit(EXIT_FAILURE);
    }

    else{
        // File TBC - R Only
        int f1=open(argv[1],O_RDONLY); 
        // FIle TBW - Requires Permissions Flags OCREAT - Create if ne, S_IRUSR - Read 400, S_IWUSR - Write 400, 

        int f2= open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        long int n1;
        char buffer[4096];
        // Does not exist 

        if(f1==-1){
            
            printf("Error Number % d\n", errno);
            close(f1);
            
            printf("Source file does not exist\n"); 
            exit(1);
        }
      
       
        // Move Block
        if(argc==3){
            char buf;
            int src,dest,n;
            int nread;
            src=open(argv[1],O_RDONLY);  // Open src File
            dest=open(argv[2],O_WRONLY | O_CREAT , sizeof(src));// Open dest File
            if(f2==-1){
                printf("Error Number % d\n", errno);
                close(f2);
                printf("Destination file does not exist\n");
                exit(1);
            }
            while((n=read(src,&buf,1)) != 0){
                write( dest, &buf, 1 );
                // Overwritng from the 1st bit ...
            }
            unlink(argv[1]); // Deleting the src file as contents have been moved
            close(src);
            close(dest); 
            printf("File Moved Successfully\n");
            close(f1);
            close(f2);
        }
    }    
    return 0;
}
/*
Input
1) ./mv filename1 filename2 --> Moves the contnents
Output Case 1
File Moved Successfully and source file deleted and destination file overwritten
Output Case 2
File Renamed Successfully 
*/
