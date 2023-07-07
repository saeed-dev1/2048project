#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<windows.h>

//initializes for login :
int i = 1 ;
int authentication = 0 ;
FILE * fp ;

//initializes for game : 
int board[4][4] ;
int dirLine[] = {1 , 0 , -1 , 0} ;
int dirColumn[] = {0 , 1 , 0 , -1} ;
int currentDirection ;

// functions for login :
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
// functions for game : 

typedef struct pair
{
    int line ; 
    int column ;
} Pair ;


Pair generateUnoccupiedPlace()
{
    int occupied = 1 ;
    Pair p1 ;
    while (occupied)
    {
        p1.line = rand() % 4 ;
        p1.column = rand() % 4 ;
        if (board[p1.line][p1.column] == 0)
            occupied = 0 ; 
    }
    return p1 ;
}

void add2()
{
    Pair pos = generateUnoccupiedPlace() ;
    board[pos.line][pos.column] = 2 ;
}

void newGame()
{
    for(int i = 0 ; i < 4 ; ++i)
        for(int j = 0 ; j < 4 ; ++j)
            board[i][j] = 0 ;       
        add2() ;
}

void printUI()
{
    for(int i = 0 ; i < 4 ; ++i)
    {
        for(int j = 0 ; j < 4 ; ++j){
            if(board[i][j] == 0)
            {
                printf("   -") ;
            }
            else
            {
                if(board[i][j] >= 2 && board[i][j] < 16)
                    printf("   %d" , board[i][j]) ;
                else if(board[i][j] >= 16 && board[i][j] < 128)
                    printf("  %d" , board[i][j]) ;
                else if(board[i][j] >=128 && board[i][j] < 1024)
                    printf(" %d" , board[i][j]) ;
                else if(board[i][j] > 1024)
                    printf("%d" , board[i][j]) ;
            }
        }
    printf("\n") ;
    }
    printf("n: new game , w : up , s : dowm , d : right , a : left , q : quit") ;
}

int canDoMove(int line , int column , int nextLine , int nextColumn)
{
    if(nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 || ((board[line][column] != board[nextLine][nextColumn]) && board[nextLine][nextColumn] != 0))
        return 0 ; 
    return 1 ; 
}

void applyMove(int direction)
{
    int startLine = 0 , startColumn = 0 ,  lineStep = 1 , columnStep = 1 ;
    if(direction == 0)
    {
        startLine = 3 ;
        lineStep = -1 ;
    }
    else if(direction == 1)
    {
        startColumn = 3 ;
        columnStep = -1 ;
    }
    int movePossible , canAddpiece = 0 ;
    do{
    movePossible = 0 ;
    for(int i = startLine ; i >= 0 && i < 4 ; i += lineStep)
    {
        for(int j = startColumn ; j >= 0 && j < 4 ; j += columnStep)
        {
            int nextI = i + dirLine[direction] , nextJ = j + dirColumn[direction] ;
            if(board[i][j] && canDoMove(i , j , nextI , nextJ))
            {
                board[nextI][nextJ] += board[i][j] ;
                board[i][j] = 0 ; 
                movePossible = 1 ;
                canAddpiece = 1 ; 
            }
        }
    }
    printUI() ;
    }while(movePossible) ;
    if(canAddpiece)
        add2() ;
}

//a function that helps to run the game : 

void runGame()
{
    srand(time(0)) ;
    char commandToDir[128] ;
    commandToDir['s'] = 0 ; 
    commandToDir['d'] = 1 ; 
    commandToDir['w'] = 2 ;
    commandToDir['a'] = 3 ;
    newGame() ;

    while (1)
    {   
        system("cls") ;
        printUI() ;
        char command ;
        scanf(" %c" , &command) ;
        if(command == 'n')
            newGame() ;
        else if(command == 'q')
            break;
        else if(command == 'w' || command == 'd' || command == 'a' || command == 's')
        {
            currentDirection = commandToDir[command] ;
            applyMove(currentDirection) ;
        }
        else
            continue;   
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
        authentication = 1 ;
    }
    else
    {
        printf("invalid comand") ;
        exit(0) ;
    }
//part2.
    if(authentication == 1)
        {
            system("cls") ;
            printf("\t\t\t\t\t\t>>>>>>welcome!<<<<<<\t\t\t\t\n") ;
            printf("write : start / scoreboard / myrank / logout :") ;
            char instruction[40] ;
            scanf("%s" , instruction) ;

            if(!strcmp(instruction , "start"))
            {
                runGame() ;
                //int size ; scanf("%d" , &size) ;
                //start(size) ;
            }
            /*else if(!strcmp(instruction , "scoreboard"))
            {

            }*/

        }

    return 0 ; 
}