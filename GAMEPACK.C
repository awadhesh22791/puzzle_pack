#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
void rect(int,int,int,int);
char menu();
void splash();
void main(void)
{
char choice;
clrscr();
textmode(C4350);
splash();
while(1){
clrscr();
choice=menu();
switch(choice){
case '1':system("8-brick");
	break;
case '2':system("tower");
	break;
case '3':exit(0);
}
}
}

void rect(int x,int y,int sizex,int sizey){
int i,j;
if(x>0&&y>0&&(x+sizex)<=80&&(y+sizey)<=49&&sizex>0&&sizey>0){
//make horizontal size
for(i=x;i<x+sizex;i++){
gotoxy(i,y);
printf("%c",196);
gotoxy(i,y+sizey);
printf("%c",196);
}
//make vertical size
for(i=y;i<y+sizey;i++){
gotoxy(x,i);
printf("%c",179);
gotoxy(x+sizex,i);
printf("%c",179);
}
//make corners
gotoxy(x,y);
printf("%c",218);
gotoxy(x,y+sizey);
printf("%c",192);
gotoxy(x+sizex,y);
printf("%c",191);
gotoxy(x+sizex,y+sizey);
printf("%c",217);
gotoxy(x+1,y+1);
}
for(j=y+1;j<y+sizey;j++){
for(i=x+1;i<sizex+x;i++){
gotoxy(i,j);
printf(" ");
}
printf("\n");
}
gotoxy(x+1,y+1);
}

void splash()
{
rect(2,2,77,47);
gotoxy(55,43);
printf("Developed By-");
gotoxy(60,45);
printf("Awadhesh Kumar");
//gotoxy(60,20);
//printf("ABC");
//gotoxy(60,21);
//printf("ABC");
//rect(20,10,28,20);
gotoxy(77/3,5);
printf("       PUZZLE PACK");
//gotoxy(77/3-3,5);
//printf("    A project on :-");
//gotoxy(77/3-3,7);
//printf("Software Technology Lab");
//gotoxy(77/3,9);
//printf("   Guided by :-");
//gotoxy(77/3-3,11);
//printf("         ABC");
gotoxy(4,47);
printf("Press any key...");
getch();
}


char menu(){
textmode(C4350);
rect(25,18,25,8);
gotoxy(28,20);
printf("1. 8-brick puzzle");
gotoxy(28,22);
printf("2. Tower of hanoi");
gotoxy(28,24);
printf("3. Exit");
return getch();
}