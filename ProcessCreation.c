// @Author : Ferhat Kortak - 2015510099

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

/*
    STRUCTURE OF THE PROCESS TREE
             ___P___
            /   |   \
            C1  C2  C3
                |
                C4
*/    

int main() 
{ 
    // Integer variables
    int pid, c1, c2, c3; 
    int input = 0;
    // File Variables
    FILE * fp;
    
    // Main Process ------------------------------------------------------------------------------------------------------------------
    pid = fork();
    if(pid>0) // If there are only pid (NO C1)
    {
        wait(NULL); // Wait for first child
        c1 = fork();
        if(c1 > 0) 
        {
            wait(NULL);
            c2 = fork();
            if(c2 > 0) // PARENT
            {
                wait(NULL);
                printf("parent --> pid = %d\n", getpid()); 
                printf("program finished...\n");
            }
            else if(c2 == 0) // Third child is created (C3)
            {
                printf("3rd child process id %d (parent:%d)\n", getpid(), getppid());  
                fp = fopen ("opSys.txt", "r"); //modes are: r, w, a, r+, w+, a+
                int storedNumber = 0;
                fscanf(fp, "%d", &storedNumber);
                printf("trying key:%d\n",storedNumber);
                (storedNumber == getppid()) ? printf("matched...\n") : printf("not matched...\n") ;
                fclose(fp); 
                
            }
        }
        else if(c1 == 0) // Second child is created (C2) -> Create Child4 then run Child4, wait Child 2
        {
            c3 = fork();
            if(c3 > 0) // C2
            {
                wait(NULL); // Wait for other Grandson()
                // Input Part
                printf("2nd child process id %d (parent:%d)\n", getpid(), getppid());  
                printf("write a key:\n");
                scanf("%d",&input);
                // Output Part
                printf("trying:%d\n",input);
                fp = fopen ("opSys.txt", "w"); //modes are: r, w, a, r+, w+, a+
                fprintf(fp, "%d", input);
                fclose(fp); 
            }
            else if(c3 == 0) // Grandson is created (C4)
            {
                wait(NULL);
                // This will be printed first
                printf("4th child process id %d (parent:%d)\n", getpid(), getppid()); 
                printf("say me password...\n");
            }
        }
    }
    else if(pid == 0) // Leftmost child is created! (C1)
    {
        // First child MUST be run firstly
        fp = fopen ("opSys.txt", "w+"); //modes are: r, w, a, r+, w+, a+
        fclose(fp);
        printf("Parent process id is : %d \n",getppid());
        printf("1st child process id %d (parent:%d)\n", getpid(), getppid()); 
        printf("File was created!\n");
    }
    // ------------------------------------------------------------------------------------------------------------------ Main Process
}