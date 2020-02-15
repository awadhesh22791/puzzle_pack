#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
char a[3][3]={' ',' ',' ',
		' ',' ',' ',
		' ',' ',' '};
void dispArray();
void instruction();
void splash();
char chgChar(int);
int chgCharToInt(char);
int check();
int checkAvail(char*,int,int);
void rect(int,int,int,int);
void swap(char*,char*);
void initializeArr(char*,int);
void getInput(char,int*,int*);
void congMsg();
void dispInst();
void gamePuz();
void moveSpace(int,int);
char menu();
void main(){
char ch;
textmode(C4350);
clrscr();
splash();
while(1){
clrscr();
switch(menu()){
	case '1':gamePuz();
		break;
	case '2':instruction();
		break;
	case '3':exit(0);
}
}
}

/* Move tile with space */
void moveSpace(int row,int col){
if(a[row][col]!=' '){
	if(row-1>=0){
	if(a[row-1][col]==' '){
	swap(&a[row-1][col],&a[row][col]); return;
	}
	}
	if(row+1<=2){
	if(a[row+1][col]==' '){
	swap(&a[row+1][col],&a[row][col]); return;
	}
	}
	if(col-1>=0){
	if(a[row][col-1]==' '){
	swap(&a[row][col-1],&a[row][col]); return;
	}
	}
	if(col+1<=2){
	if(a[row][col+1]==' '){
	swap(&a[row][col+1],&a[row][col]); return;
	}
	}
}
}

/* Congratulation message */
void congMsg(){
rect(25,20,30,5);
gotoxy(33,21);
printf("Congratulation !");
gotoxy(27,23);
printf("You have solved the puzzle.");
gotoxy(60,47);
printf("Press any key...");
getch();
}

/* Check the solution of puzzle */
int check(){
int x=1,y=5,result=0,i;
for(i=0;i<3;i++){
if(a[0][i]==chgChar(x)){
result++;
x++;
}
if(a[2][2-i]==chgChar(y)){
result++;
y++;
}
}
if(a[1][2]==chgChar(x))
result++;
if(a[1][0]==chgChar(y))
result++;
if(a[1][1]==' ')
result++;
return result;
}

/* Main game function */
void gamePuz(){
char resp;
int result,row,col;
char choice='n';
clrscr();
do{
result=0;
resp=' ';
initializeArr((char*)&a,8);
clrscr();
while(1){
dispArray();
result=check();
if(resp=='e'||resp=='E'||result==9){
if(result==9)
congMsg();
break;
}else{
resp=getch();
getInput(resp,&row,&col);
moveSpace(row,col);
}
}
clrscr();
rect(20,20,40,4);
gotoxy(22,22);
printf("Want to solve next puzzle (Y/N) ?: ");
choice=getche();
}while(choice=='y'||choice=='Y');
clrscr();
rect(30,20,15,4);
gotoxy(33,22);
printf("Game end !");
gotoxy(60,47);
printf("Press any key...");
getch();
}

/* Function to select row and column on the basis of user input */
void getInput(char resp,int*row,int*col){
int ch=chgCharToInt(resp);
switch(ch){
case 1:
case 2:
case 3:*row=2;*col=ch-1;
	break;
case 4:
case 5:
case 6:*row=1;*col=ch-4;
	break;
case 7:
case 8:
case 9:*row=0;*col=ch-7;
	break;
}
}

/* Function to swap values between two variable */
void swap(char*char1,char*char2){
char temp;
temp=*char1;
*char1=*char2;
*char2=temp;
}

/* Function to convert the Integer into respective character */
char chgChar(int num){
switch(num){
	case 1:	return '1';
	case 2:	return '2';
	case 3:	return '3';
	case 4: return '4';
	case 5:	return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	default:return ' ';
	}
}

/* Function to convert Character into respective integer */
int chgCharToInt(char ch){
switch(ch){
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default : return 0;
	}
}

/* Function to initialize the array */
void initializeArr(char*arr,int len){
int element=len;
int num;
int i;
int assign=0;
char*temp=arr;
for(i=len;i>=0;i--){
*temp=' ';
temp++;
}
clrscr();
rect(25,20,30,6);
gotoxy(33,23);
printf("Initializing...");
rect(1,47,79,2);
gotoxy(2,48);
while(len){
len--;
do{
assign=0;
randomize();
num=rand()%10;
if(num>0&&num<9){
if(checkAvail((char*)&a,element,num)==0){
*arr=chgChar(num);
assign=1;
for(i=0;i<10;i++){
if(len==1&&i==8)
break;
printf("%c",219);
}
}
}
}while(assign==0);
arr++;
}
}

/* Function to check the availability of generated number into array */
int checkAvail(char*a,int len,int num){
while(len){
len--;
if(*a==chgChar(num))
return 1;
a++;
}
return 0;
}

/* Display the array */
void dispArray(){
int i,j,k,count=2,y=5,bcount=2;
gotoxy(34,4);
printf("%c%c%c%c%c%c%c",218,196,194,196,194,196,191);
for(i=0;i<3;i++){
  gotoxy(34,y);
  printf("%c",179);
	for(j=0;j<3;j++){
	printf("%c",a[i][j]);
		if(count!=0){
		printf("%c",179);
		count--;
		}
	}
	printf("%c",179);
	y++;
	if(bcount!=0){
	gotoxy(34,y);
	printf("%c%c%c%c%c%c%c",195,196,197,196,197,196,180);
	bcount--;
	}
	y++;
	count=2;
	}
	gotoxy(34,y-1);
	printf("%c%c%c%c%c%c%c",192,196,193,196,193,196,217);
}


/* Draw specified rectangle */
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
printf("       8-BRICKS PUZZLE");
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
/* Function to show Instructions of game */
void instruction()
{
rect(2,2,77,47);
gotoxy(5,5);
printf("1. Instructions: For shifting space use numbers on numberpad as follows");
gotoxy(35,8);
printf("7%c8%c9",179,179);
gotoxy(35,9);
printf("%c%c%c%c%c",196,197,196,197,196);
gotoxy(35,10);
printf("4%c5%c6",179,179);
gotoxy(35,11);
printf("%c%c%c%c%c",196,197,196,197,196);
gotoxy(35,12);
printf("1%c2%c3",179,179);
gotoxy(5,15);
printf("2. Your target is to arrange tiles as follows");
gotoxy(34,17);
printf("%c%c%c%c%c%c%c",218,196,194,196,194,196,191);
gotoxy(34,18);
printf("%c1%c2%c3%c",179,179,179,179);
gotoxy(34,19);
printf("%c%c%c%c%c%c%c",195,196,197,196,197,196,180);
gotoxy(34,20);
printf("%c8%c %c4%c",179,179,179,179);
gotoxy(34,21);
printf("%c%c%c%c%c%c%c",195,196,197,196,197,196,180);
gotoxy(34,22);
printf("%c7%c6%c5%c",179,179,179,179);
gotoxy(34,23);
printf("%c%c%c%c%c%c%c",192,196,193,196,193,196,217);
gotoxy(5,25);
printf("3. Press key 'e' any time during game to end the game.");
gotoxy(5,47);
printf("Press any key...");
getch();
}

/* show menu */
char menu(){
rect(30,15,20,8);
gotoxy(33,17);
printf("1. Start Game");
gotoxy(33,19);
printf("2. Instructions");
gotoxy(33,21);
printf("3. Back");
return getch();
}