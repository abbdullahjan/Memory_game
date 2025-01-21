#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#define Total_Rows 6
#define Total_Cols 6
#define players 2

int score[players]={};
int turn; 
int firstTurn;

void RandomlyFilledChar(char memoryarray[Total_Rows][Total_Cols]);
void DisplayGameFrontEnd(char frontdisplay[Total_Rows][Total_Cols]);
void firstTurnFrontEnd(char row,int col,char frontdisplay[Total_Rows][Total_Cols],char backdisplay[Total_Rows][Total_Cols]);
void OneplayerTurn(char frontDisplay[Total_Rows][Total_Cols],char backDisplay[Total_Rows][Total_Cols]);
void SecondTurnFrontEnd(char row,int col,int row1,int col1,char frontdisplay[Total_Rows][Total_Cols],char backdisplay[Total_Rows][Total_Cols]);

void RandomlyFilledChar(char memoryarray[Total_Rows][Total_Cols])
{
    //remember to initialize all array elements to 0 in main
    srand((unsigned) time(NULL));

    int row,col; 


    int alphabetCount = ((Total_Cols * Total_Rows)-2)/2; //change population limit when rows columns are changed
    for(char i='A';i<65 + alphabetCount;)
    {
        label1:
        row = rand() % Total_Rows ;
        col = rand() % Total_Cols ;

        if(memoryarray[row][col] == 0)
        {
            memoryarray[row][col] = i ;
            i = i+32 ; 
        }
        else
        goto label1;
        label2:
        row = rand() % Total_Rows ;
        col = rand() % Total_Cols ;

        if(memoryarray[row][col] == 0)
        {
            memoryarray[row][col] = i ;
            i = i-31 ; 
        }
        else
        goto label2;
    }

    for(int i=0;i<Total_Rows;i++)
    {
        for(int j=0;j<Total_Cols;j++)
        {
            if(memoryarray[i][j] == 0) //true when memoryarray is 0 also equals memoryarray[i][j] == 0
            memoryarray[i][j] = '*';
        }
    }
}


void OneplayerTurn(char frontDisplay[Total_Rows][Total_Cols],char backDisplay[Total_Rows][Total_Cols])
{
    int row,row1; //single index to turn
    char col,col1; //single index to turn
    printf("Player %d score: %d\n",firstTurn,score[firstTurn-1]);//first turn score is always printed first
    printf("Player %d score: %d\n",(firstTurn % players + 1),score[(firstTurn % players )]); //changes 1 to 0 and 0 to 1
    // as index of array starts from 0
    
    label1:
    DisplayGameFrontEnd(frontDisplay);
    printf("Player %d : Enter a coordinate (e.g. B3): ",turn);
    scanf(" %c%d",&col,&row);


    //change lowercase to uppercase if user provide lowercase as column
    if(col>='a' && col<='f') 
    col -= 32;

    //give error for OutOfRange input
    if((col<'A' || col>'F') || (row<0 || row>Total_Rows-1))
    {
        printf("Invalid Input! OutOfRange Input...Try Again!!!\n");
        goto label1;
    }

    //give error if index has already been flipped...
    if(frontDisplay[row][col-65] == ' ')
    {
        printf("Invalid Input! Already Flipped...Try Again!!!\n");
        goto label1;}
    firstTurnFrontEnd(row,col,frontDisplay,backDisplay);

    label2:
    printf("Player %d : Enter a coordinate (e.g. B3): ",turn);
    scanf(" %c%d",&col1,&row1);

    //change lowercase to uppercase if user provide lowercase as column
    if(col1>='a' && col1<='f') 
    col1 -= 32;

    //give error for OutOfRange input
    if((col1<'A' || col1>'F') || (row1<0 || row1>Total_Rows-1 ))
    {
        printf("Invalid Input! OutOfRange Input...Try Again!!!\n");
        goto label2;
    }

    //give error if index has already been flipped...
    if(frontDisplay[row1][col1-65] == ' ')
    {
        printf("Invalid Input! Already Flipped...Try Again!!!\n");
        goto label2;}

    //give error if user provided same index as in previou turn...
    if(row1==row && col1==col)
    {
        printf("Same Input Not Allowed! Try Again...\n");
        goto label2;
    }
    SecondTurnFrontEnd(row,col,row1,col1,frontDisplay,backDisplay);
    
    //increase score by 2 if both stars are selected in one turn 
    
    if(backDisplay[row][col-65] == '*' && (backDisplay[row1][col1-65] == '*'))
    {
    frontDisplay[row][col-65] = ' ';
    frontDisplay[row1][col1-65] = ' ';
    score[turn-1]++;
    score[turn-1]++;
    }
    //if ascii of two selected indexes differs by 32, both are same alphabets  
    else if(backDisplay[row][col-65] == (backDisplay[row1][col1-65]+32) || backDisplay[row][col-65]==(backDisplay[row1][col1-65]-32))
    {
    frontDisplay[row][col-65] = ' ';
    frontDisplay[row1][col1-65] = ' ';
    score[turn-1]++;
    }
    else if(backDisplay[row][col-65] == '*')
    {
        frontDisplay[row][col-65] = ' ';
        for(int i=0;i<Total_Rows;i++)
        {
            for(int j=0;j<Total_Cols;j++)
            {
                if((backDisplay[i][j] == (backDisplay[row1][col1-65]+32)) || (backDisplay[i][j]==(backDisplay[row1][col1-65]-32)))
                {  
                frontDisplay[i][j] = ' ';
                }
            }
        }
        frontDisplay[row1][col1-65] = ' ';
        score[turn -1]++ ; //score of turn 2 is score[1]
        score[turn -1]++ ; //score of turn 1 is score[0]

    }
    else if(backDisplay[row1][col1-65] == '*')
    { 
        frontDisplay[row1][col1-65] = ' ';
        for(int i=0;i<Total_Rows;i++)
        {
            for(int j=0;j<Total_Cols;j++)
            {
                if((backDisplay[i][j] == (backDisplay[row][col-65]+32)) || (backDisplay[i][j]==(backDisplay[row][col-65]-32)))
                {  
                frontDisplay[i][j] = ' ';
                }
            }
        }
        frontDisplay[row][col-65] = ' ';
        score[turn -1]++ ;
        score[turn -1]++ ;

    }
    else //game must only pause when both inouts are not same(case insensitive) 
    {
    turn = (turn % players + 1);
    Sleep(2000);
    system("cls");

    }
   

    
}


void DisplayGameFrontEnd(char frontdisplay[Total_Rows][Total_Cols])
{//call array from main funtion
    
    printf("    A   B   C   D   E   F\n");
    for(int i=0;i<Total_Rows;i++)
    {
        printf("  +---+---+---+---+---+---+\n");
        printf(" %d|",i);
        for(int j=0;j<Total_Cols;j++)
        {
            printf(" %c |",frontdisplay[i][j]);
        }
        printf("\n");
    }
    printf("  +---+---+---+---+---+---+\n");
}

void SecondTurnFrontEnd(char row,int col,int row1,int col1,char frontdisplay[Total_Rows][Total_Cols],char backdisplay[Total_Rows][Total_Cols])
{
    int alphabetCount = (Total_Cols * Total_Rows)/4 - 2; 

    printf("\n    A   B   C   D   E   F\n");
    for(int i=0;i<Total_Rows;i++)
    {
        printf("  +---+---+---+---+---+---+\n");
        printf(" %d|",i);
        for(char j='A';j<65 + Total_Cols;j++)
        {
            if(i==row && j==col)
            {printf("|%c||",backdisplay[i][j-65]);}
            else if(i==row1 && j==col1)
            {
                printf("|%c||",backdisplay[i][j-65]);
            }
            else{
            printf(" %c |",frontdisplay[i][j-65]);}
            
        }
        printf("\n");
    }
    printf("  +---+---+---+---+---+---+\n");
}



void firstTurnFrontEnd(char row,int col,char frontdisplay[Total_Rows][Total_Cols],char backdisplay[Total_Rows][Total_Cols])
{
    
    printf("\n    A   B   C   D   E   F\n");
    
    for(int i=0;i<Total_Rows;i++)
    {   
        printf("  +---+---+---+---+---+---+\n");
        printf(" %d|",i);
        for(char j='A';j<65 + Total_Cols;j++)
        {
            if(i==row && j==col)
            {printf("|%c||",backdisplay[i][j-65]);
            continue;}


            printf(" %c |",frontdisplay[i][j-65]);
        }
        printf("\n");
    }
    printf("  +---+---+---+---+---+---+\n");
}

void PrintFinalBackEnd(char backend[Total_Rows][Total_Cols],char frontend[Total_Rows][Total_Cols])
{
    printf("    A   B   C   D   E   F\n");
    for(int i=0;i<Total_Rows;i++)
    {
        printf("  +---+---+---+---+---+---+\n");
        printf(" %d|",i);
        for(int j=0;j<Total_Cols;j++)
        {   if(frontend[i][j] != ' ')
            printf(" %c |",backend[i][j]);
            else
            printf(" %c |",frontend[i][j]);
        }
        printf("\n");
    }
    printf("  +---+---+---+---+---+---+\n");
}





int main()
{
    srand((unsigned) time(NULL));
    turn = rand() % players + 1; // turn is either 1 or 2
    firstTurn = turn ;
    char frontEndArray[Total_Rows][Total_Cols];
    for(int i=0;i<Total_Rows;i++)
    {
        for(int j=0;j<Total_Cols;j++)
        {
            frontEndArray[i][j] = '#' ;
        }
    }
    char backendChar[Total_Rows][Total_Cols]={0};
    RandomlyFilledChar(backendChar);

    for(int i=0 ; i<=5 ; i++)
    {
        for( int j=0;j<=5;j++)
        {
            printf("%c ",backendChar[i][j]);
        }
        printf("\n");
    }


    while(1)
    {
    int counter=0 ; //to check if any card is unturned
    for(int i=0;i<Total_Rows;i++)
    {
        for(int j=0;j<Total_Cols;j++)
        {
            if(frontEndArray[i][j] == '#')
            {counter++;}
        }
    }
    if(counter <= 3){ //To automatically finish if less than three cards are left and give points to current player 
    break; //3 cards are possible if one of the remaining cards is a joker
    }
    OneplayerTurn(frontEndArray,backendChar);
    }

    PrintFinalBackEnd(backendChar,frontEndArray);
    Sleep(2000);
    for(int i=0;i<Total_Rows;i++)
    {
        for(int j=0;j<Total_Cols;j++)
        {
            if(frontEndArray[i][j] != ' ')//for checking remaining cards location
            {
                int static counter=0; //give 1 point if two alphabets are turned
                if(frontEndArray[i][j]=='*')
                {
                    
                    score[turn]=score[turn]+1;
                }
                else if(counter==0)
                {
                    score[turn]=score[turn]+1;
                    counter++;

                }
                frontEndArray[i][j] = ' ';
            }
        }
    }
    DisplayGameFrontEnd(frontEndArray);


    printf("Final Score: \n");
    printf("Player 1: %d\n",score[0]);
    printf("Player 2: %d\n",score[1]);
    
    
    if(score[0] > score[1])
    {
        printf("\nplayer 1 Wins\n");
    }
    else if(score[0] < score[1])
    {
        printf("\nplayer 2 Wins\n");
    }
    else
    printf("\nIts a Draw");
    
}