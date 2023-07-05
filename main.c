#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int i = 1 ;
FILE * fp ;
typedef struct user
{
    char name[50] ;
    char password[50] ;
    //struct user * next ; 
} User ;

/*User create_new_user(char u_name[50] , char pswd[50])
{
    User u1 ;
    strcpy(u1.name , u_name) ;
    strcpy(u1.password , pswd);
    u1.next = NULL ;
    return u1 ;
}*/


User SignUp(User u1)
{   
    scanf("%s" , &u1.name) ;
    scanf("%s" , &u1.password) ;
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
        return u1 ;
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