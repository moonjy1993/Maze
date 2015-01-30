
#include <stdio.h> 
#include <malloc.h>
#include <windows.h>

typedef struct node{
        int x, y;
        struct node *link;
}stack;

void PUSH(stack **move, int x, int y);
void POP(stack **move);
void ALL_POP(stack **move);
void gotoxy(int x, int y);
void setcolor(int color, int bgcolor);

int main() {
        int i, j;
        int map[10][10] = {
                {1,0,1,0,1,1,1,1,1,1},
                {1,0,1,0,1,1,1,0,1,1},
                {1,0,1,0,1,1,0,0,0,1},
                {1,0,1,0,0,0,1,1,0,1},
                {1,0,1,1,1,0,0,0,0,1},
                {1,0,0,0,1,1,0,1,1,1},
                {1,1,1,0,0,0,0,1,1,1},
                {1,0,0,0,1,0,1,1,0,1},
                {1,0,1,1,0,0,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1}
        };
        stack *move = NULL;

        for(i=0; i<10; i++){                                      //map 
                for(j=0; j<10; j++){
                        if(map[i][j]==1){printf("■");}
                        else{printf("　");}
                }
                printf("\n");
        }

        PUSH(&move, 2, 0);                    // initial starting point
        gotoxy(move->x, move->y);         //move to where the stack position
        setcolor(10, 0);
        printf("Ω");

        while(1){
                Sleep(200);
                gotoxy(move->x, move->y);
                printf("　");
                map[move->y][move->x/2] = 2;                   //change it it already pased it
  
                if(map[0][3]==2){                                       //get off from the maze
                        ALL_POP(&move);                              //pop all
                        gotoxy(12,12);
                        printf("You are Free!\n");
                        system("pause");
                        return;
                }
                else if(map[move->y+1][move->x/2]==0){         //move downward
                        PUSH(&move,move->x,move->y+1);          
                        gotoxy(move->x, move->y);                     
                        printf("Ω");
                }
                else if(map[move->y-1][move->x/2]==0){         //move upward
                        PUSH(&move,move->x,move->y-1);
                        gotoxy(move->x, move->y);
                        printf("Ω");
                }
                else if(map[move->y][move->x/2+1]==0){         //rightward
                        PUSH(&move,move->x+2,move->y);
                        gotoxy(move->x, move->y);
                        printf("Ω");
                }
                else if(map[move->y][move->x/2-1]==0){         //leftward
                        PUSH(&move,move->x-2,move->y);
                        gotoxy(move->x, move->y);
                        printf("Ω");
                }
                else{                                                             //if its blocked
                        POP(&move);                                         //pop current position and move to the one before
                        gotoxy(move->x, move->y);                     
                        printf("Ω");
                }
        }
        return 0;
}
void PUSH(stack **move, int x, int y){
        stack *tmp = *move;
        *move = (stack*)malloc(sizeof(stack));
        (*move)->x = x;
        (*move)->y = y;
        (*move)->link = tmp;
}
void POP(stack **move){
        stack *tmp = *move;
        *move = (*move)->link;
        free(tmp);
}
void ALL_POP(stack **move){
        for(;*move!=NULL;){POP(move);}
}
void gotoxy(int x, int y){
        COORD Pos={x,y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void setcolor(int color, int bgcolor){
        color &= 0xf;
        bgcolor &= 0xf;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
