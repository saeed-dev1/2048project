#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int i = 1 ;
int authentication = 0 ;
FILE * fp ;


typedef struct user
{
    char name[50] ;
    char password[50] ; 
} User ;


User SignUp(User u1)
{   
    scanf("%s" , u1.name) ;
    scanf("%s" , u1.password) ;
    if(access(u1.name , F_OK) == 0)
    { 
        printf("username already exists!\n") ;
        exit(0);
    }
    else
    {
        fp = fopen(u1.name , "w") ;
        fwrite(&u1 , sizeof(User) , 1 , fp) ;
        fclose(fp) ;
        authentication = 1 ;                               
        return u1 ;
    }
}

void Login(User u1)
{
    User usr ;
    scanf("%s" , u1.name) ;
    scanf("%s" , u1.password) ;

    if(access(u1.name , F_OK))
    {
        printf("username not found!") ;
        fclose(fp) ;
        exit(0) ;
    }

    else
    {
        FILE * fphelp = fopen(u1.name , "r");
        fread(&usr , sizeof(usr) , 1 , fphelp) ;

        if(strcmp(usr.password , u1.password) == 0)
        {
            authentication = 1 ;
        }
        else
        {   
            printf("password incorrect!\n") ;
            exit(0) ;
        }
        
    }


}



int main()
{      
    User u1 ;
    char option[20] ;

    scanf("%s" , option) ;

    if(!strcmp(option , "signup"))
        SignUp(u1) ;
    else if(!strcmp(option , "login"))
        Login(u1) ;
    else if(!strcmp(option , "guest"))
    {

    }
    else
    {
        printf("invalid command") ;
        exit(0) ;
    }

    return 0 ; 
}