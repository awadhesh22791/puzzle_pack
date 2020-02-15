#include<stdio.h>
#include<alloc.h>
#include<graphics.h>
#include<conio.h>

#define diskWidth 7
#define diskHeight 25
#define maxLevel 2+10

/* Global variables */
int ox,oy,level;
char*blank;
typedef struct Stack stack;
typedef struct Disc disc;
stack A,B,C;


/* Function declaration */
void drawInterface(int level);
disc*createNewNode(int val,char*img);
void rect(int,int,int,int);
void splash();
char menu();
void instruction();
void push(stack*stk,disc*dis);
void createStackA();
int pop(stack*stk);
void freeMem();
void traverse(stack*stk);
void transDisc(stack*src,stack*target);
char getInput();
void gameTower();
int isGameOver(stack*stk);
int isWin(stack*stk1,stack*stk2);
void winMsg();
void gameOverMsg();


/* Main function */
void main(){
char ch;
textmode(C4350);
clrscr();
splash();
while(1){
clrscr();
switch(menu()){
	case '1':gameTower();
		break;
	case '2':instruction();
		break;
	case '3':exit(0);
}
}
}

/* Main Game Function */
void gameTower(){
int gd=VGA,gm=2,errorcode;
int choice,gameOver,win;
stack*src=NULL,*target=NULL;
char next;
level=2;
initgraph(&gd,&gm,"c:\\tc\\bgi");
 errorcode = graphresult();

if (errorcode != grOk)  /* an error occurred */
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);             /* return with error code */
}
ox=getmaxx()/2;
oy=getmaxy()-80;
setviewport(0,0,ox*2,oy*2,0);
while(1){gameOver=0,win=0;
	level++;freeMem();
	clearviewport();
	drawInterface(level);createStackA();
	while(1){
		fflush(stdin);
		gotoxy(30,29);
		printf("From which peg(1/2/3)");
		choice=getInput();
		switch(choice){
		case '1': src=&A;break;
		case '2': src=&B;break;
		case '3': src=&C;break;
		}
		if(choice=='e'||choice=='E')break;
		gotoxy(30,29);
		printf("To which peg(1/2/3)  ");
		choice=getInput();
		switch(choice){
		case '1':target=&A;break;
		case '2': target=&B;break;
		case '3': target=&C;
		}
		if(choice=='e'||choice=='E')break;
		transDisc(src,target);
		gameOver=0;
		win=0;
		gameOver=isGameOver(target);
		win=isWin(&A,&B);
		if(gameOver==1||win==1){
		gotoxy(30,29);
		printf("Please wait...       ");
		delay(1000);
		break;
		}
	} // end of inner while
	if(choice=='e'||choice=='E')break;
	if(gameOver==1){
	gameOverMsg();
	break;
	}
	if(win==1)winMsg();
	if(level<maxLevel){
	gotoxy(26,16);
	printf("Want to proceed next level (Y/N): ");
	fflush(stdin);
	next=getch();
	}
	if(next=='y'||next=='Y')
	;
	else break;
	if(level==maxLevel)break;
}//end of outer while
freeMem();
free(blank);
closegraph();
}



/* Data defination */

struct Disc{
char*imgDisc;
int value;
disc*next;
};

struct Stack{
disc*top;
int topx;
int topy;
};


/* Function defination */

/* Winner message */
void winMsg(){
cleardevice();
setcolor(LIGHTGREEN);
settextstyle(7, HORIZ_DIR,7);
outtextxy(80,90,"Congratulation!");
if(level<maxLevel){
setcolor(YELLOW);
settextstyle(0, HORIZ_DIR,2);
outtextxy(150,250,"Puzzle solved");
}else{
setcolor(YELLOW);
settextstyle(0, HORIZ_DIR,2);
outtextxy(30,250,"Game completed successfully!");
}
setcolor(WHITE);
settextstyle(0, HORIZ_DIR,0);
outtextxy(450,getmaxy()-30,"Press any key...");
getch();
cleardevice();
}

/* Game Over message */
void gameOverMsg(){
cleardevice();
setcolor(RED);
settextstyle(0, HORIZ_DIR,7);
outtextxy(50,getmaxy()/2-30,"Game Over!");
setcolor(WHITE);
settextstyle(0, HORIZ_DIR,0);
outtextxy(450,getmaxy()-30,"Press any key...");
getch();
cleardevice();
}

/* Function to check win condition */
int isWin(stack*stk1,stack*stk2){
if((*stk1).top==NULL&&(*stk2).top==NULL) return 1;
else
return 0;
}

/* Function to check condition of game over */
int isGameOver(stack*stk){
disc*temp=(*stk).top;
temp=temp->next;
if((*stk).top->value<temp->value) return 1;
else
return 0;
}

/* Function to get input from user */
char getInput(){
char ch;
while(1){
ch=' ';
ch=getch();
if(ch=='1'||ch=='2'||ch=='3'||ch=='e'||ch=='E')
return ch;
}
}

/* Function to transfer disk from source peg to target peg */
void transDisc(stack*src,stack*target){
disc*temp;
if((*src).top!=NULL){
temp=(*src).top;
(*src).top=(*src).top->next;
push(target,temp);
putimage((*src).topx,(*src).topy,blank,COPY_PUT);
(*src).topy+=diskHeight;
(*target).topy-=diskHeight;
putimage((*target).topx,(*target).topy,temp->imgDisc,COPY_PUT);
}
}

/* Function to traverse specified stack */
void traverse(stack*stk){
disc*temp=(*stk).top;
while(temp!=NULL){
printf("valeu=%d \n",temp->value);
temp=temp->next;
}
printf("topx=%d topy=%d ",(*stk).topx,(*stk).topy);
}

/* Function to free memory */
void freeMem(){
while(pop(&A)==0);
while(pop(&B)==0);
while(pop(&C)==0);
}

/* Function to pop one node */
int pop(stack*stk){
disc*temp;
if((*stk).top==NULL) return 1;
else{
temp=(*stk).top;
(*stk).top=(*stk).top->next;
free(temp->imgDisc);
free(temp);
return 0;
}
}

/* push created disc onto specified stack */
void push(stack*stk,disc*dis){
disc*temp;
if((*stk).top==NULL){
dis->next=(*stk).top;
(*stk).top=dis;
}else{
temp=(*stk).top;
(*stk).top=dis;
(*stk).top->next=temp;
}
}

/* create new node */
disc*createNewNode(int val,char*img){
disc*ptr;
ptr=(disc*)malloc(sizeof(disc));
if(ptr==NULL){
printf("Memory allocation error");
printf("\n Press any key...");
getch();
exit(1);
}
ptr->value=val;
ptr->imgDisc=img;
ptr->next=NULL;
return ptr;
}

/* Draw interface */
void drawInterface(int numDisc){
int i;
int ox1,oy1;
int area;
char*imgSize;
ox1=1*ox/3;
oy1=oy;
i=1;
gotoxy(37,2);
printf("Level-%d",level-2);
line(ox*2/6,30,ox*2/6,oy);
line(ox-1,30,ox-1,oy);
line(ox*10/6,30,ox*10/6,oy);
for(i=0;i<numDisc;i++){
setcolor(i+1);
//rectangle(ox1-diskWidth*(numDisc-i),oy1-diskHeight*(i+1),ox1+diskWidth*(numDisc-i),oy1-diskHeight*i-2);
line(ox1-diskWidth*(numDisc-i),oy1-diskHeight*(i+1),ox1+diskWidth*(numDisc-i),oy1-diskHeight*(i+1));
line(ox1-diskWidth*(numDisc-i),oy1-diskHeight*i-2,ox1+diskWidth*(numDisc-i),oy1-diskHeight*i-2);
arc(ox1-diskWidth*(numDisc-i)+1,oy1-diskHeight*(i+1)+diskHeight/2-1,90,270,diskHeight/2-1);
arc(ox1+diskWidth*(numDisc-i),oy1-diskHeight*i-2-diskHeight/2+1,270,90,diskHeight/2-1);
setfillstyle(SOLID_FILL, i+1);
floodfill(ox1-diskWidth*(numDisc-i)+5,oy1-diskHeight*(i+1)+5,i+1);
setcolor(WHITE);
line(ox1-diskWidth*(numDisc-i),oy1-diskHeight*i-4,ox1+diskWidth*(numDisc-i),oy1-diskHeight*i-4);
arc(ox1+diskWidth*(numDisc-i)-1,oy1-diskHeight*i-2-diskHeight/2+1-2,270,0,diskHeight/2-1);
}
A.topx=0;
A.topy=oy1-diskHeight*(i);
B.topx=2*ox/3;
B.topy=oy;
C.topx=4*ox/3;
C.topy=oy;
setcolor(15);
rectangle(0,oy+1,ox*2,oy+25);
setcolor(RED);
settextstyle(0,0,3);
outtextxy(ox/3-10,oy+3,"1");
outtextxy(ox-10,oy+3,"2");
outtextxy(5*ox/3-10,oy+3,"3");
setcolor(15);
}

/* Create stack A */
void createStackA(){
char*img;
disc*newDisc;
int area;
int i;
A.topy=oy-1;
freeMem();
for(i=0;i<level;i++){
area=imagesize(0,A.topy,2*ox/3,A.topy-diskHeight);
img=(char*)malloc(area);
if(img==NULL){
printf("Error1: memory allocation");
printf("\nPress any key...");
getch();
closegraph();
exit(1);
}
getimage(0,A.topy,2*ox/3,A.topy-diskHeight,img);
newDisc=createNewNode(i,img);
push(&A,newDisc);
A.topy-=diskHeight;
}
/* get blank space */
if(level==3){
area=imagesize(0,30,ox*4/6,30+diskHeight);
blank=(char*)malloc(area);
if(blank==NULL){
printf("Error2: memory allocation");
printf("\nPress any key...");
getch();
closegraph();
exit(1);
}
getimage(0,30,ox*4/6,30+diskHeight,blank);
}
B.top=NULL;
C.top=NULL;
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
printf("       TOWER OF HANOI");
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
printf("1. Your goal is to transfer all the discs from peg-1 to peg-3 in same");
gotoxy(5,7);
printf("   order.");
gotoxy(5,9);
printf("2. Condition: You can't place bigger disc on smaller one.");
gotoxy(5,11);
printf("2. Condition: Only one disc at a time can move.");
gotoxy(5,13);
printf("3. Press key 'e' any time during game to end the game.");
gotoxy(5,47);
printf("Press any key...");
getch();
}

/* show menu */
char menu(){
textmode(C4350);
rect(30,15,20,8);
gotoxy(33,17);
printf("1. Start Game");
gotoxy(33,19);
printf("2. Instructions");
gotoxy(33,21);
printf("3. Back");
return getch();
}