#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
struct Snake{
	int x,y;
	char val;
	struct Snake *next;
};

struct Food{
	int x,y;
	char val;
};

void print(char screen [30][30],int SCORE){
	int i,j;
	for( i=0;i<=30;i++)
	printf("+ ");
	printf("\n");
	
	for( i=0;i<30;i++){
	printf("+");
		for( j=0;j<30;j++){
			printf("%c ",screen[i][j]);
		}
	printf("+\n");
	
	}
	
	for( i=0;i<=30;i++)
	printf("+ ");
	printf("\n SCORE : %d\n",SCORE);
	
}

bool createSnake(struct Snake* head){
	head->x=rand()%20 ;
	head->y=rand()%20 ;
	head->val='H';
	head->next=NULL;
	int i;
	for(i=0;i<3;i++){
		struct Snake*t=head;
		while(t->next!=NULL){
			t=t->next;
		}
		struct Snake*n=(struct Snake *) malloc(sizeof(struct Snake));
		n->x=t->x;
		n->y=t->y -1;
		n->val='o';
		n->next=NULL;
		t->next=n;
	}
	
	return true;
	
}

bool createFood(struct Food* f,struct Snake* head){
	f->x=rand()%30;
	f->y=rand()%30;
	f->val='#';
	struct Snake*t=head;
	while(t!=NULL){
		if(t->x==f->x && t->y==f->y)
		return false;
		
		t=t->next;
	}
	return true;
}

bool mapSnake(char screen[30][30],struct Snake* head){
	struct Snake*t=head;
	while(t!=NULL){
		screen[t->x][t->y]=t->val;
		t=t->next;
	}
	return true;
}

bool mapFood(char screen[30][30],struct Food* f){
	screen[f->x][f->y]=f->val;
	return true;
}

bool revSnake(struct Snake**head){
	struct Snake * prev=NULL;
	struct Snake * curr=*head;
	struct Snake * next;
	while(curr!=NULL){
		next=curr->next;
		curr->next=prev;
		prev=curr;
		curr=next;
	}
	*head=prev;
	return true;
}

bool saveGame(struct Snake* head,char *str,struct Food* f){
	struct Snake*t=head;int index=0;
	str[index++]=f->val;
	str[index++]=(char)f->x;
	str[index++]=(char)f->y;
	//index=index+3;
	while(t!=NULL){
		str[index++]=t->val;
		str[index++]=(char)t->x;
		str[index++]=(char)t->y;
		t=t->next;
	//	index+=3;
		
	}
	str[index]='*';
	int j=0;
	while(str[j]!='*')
	{
		printf("%c %d %d\n",str[j],str[j+1],str[j+2]);
		j+=3;
	}
	return true;	
}

bool readSnake(char*str ,struct Food* F,struct Snake* snake){
	int index=0;
	F->val=str[index++];
	F->x=(int)str[index++];
	F->y=(int)str[index++];
	
	snake->val=str[index++];
	snake->x=(int)str[index++];
	snake->y=(int)str[index++];
	snake->next=NULL;
	
	while(str[index]!='*'){
		struct Snake*t=snake;
		while(t->next!=NULL){
			t=t->next;
		}
		struct Snake*n=(struct Snake *) malloc(sizeof(struct Snake));
		n->val=str[index++];
		n->x=(int)str[index++];
		n->y=(int)str[index++];
		n->next=NULL;
		t->next=n;
	}
//	char screen[30][30]={{}};
//	bool statusMapSnake = mapSnake(screen, snake);	//printf("map snake %d\n",statusMapSnake);
//	bool statusMapFood = mapFood(screen,F);		//printf("map food %d\n",statusMapFood);
//	print(screen,10);

	return true;
}

bool input(struct Snake* head,bool *gameOver,char* str,struct Food*f){
	static char inp='d';
	bool statusRevSnake;
	int X,Y,save=0;
	do
	{
	X=head->x;Y=head->y;
	if(kbhit())
	inp=getch();
	
	switch(inp){
		case 'w':
			if(head->x>0)
			X =head->x -1;
			else
			X =29;
			break;
		case 'a':
			if(head->y>0)
			Y =head->y -1;
			else
			Y =29;
			break;
		case 'd':
			if(head->y <29)
			Y =head->y +1;
			else
			Y =0;
			break;
		case 's':
			if(head->x <29)
			X =head->x +1;
			else
			X =0;
			break;   
		case 'r': 
			statusRevSnake=revSnake(&head);
			return true;
			break;
		case 'x':
			printf("enter 1 to save ur game\t");
			scanf("%d",&save);
			if(save==1){
				bool statusSaveGame=saveGame(head,str,f);
				if(statusSaveGame==1)
				{
					printf("game saved !!\n");                          
					bool statusReadSnake=readSnake(str,f,head);
				}
			}
			*gameOver=true;                   
			break;     
	}
	}while( X==head->next->x && Y==head->next->y );
	
	head->x=X;
	head->y=Y;
	return true;
}

bool eat(struct Snake* head,int PX,int PY){
	struct Snake* t=head;
	struct Snake* n=(struct Snake *)malloc(sizeof(struct Snake));
	n->x=PX; n->y=PY; n->val='o';
	n->next=head->next;
	head->next=n;
	return true;
}

bool moveSnake(struct Snake* head,int PX,int PY){
	int PXX,PYY;
	struct Snake* t=head->next;
	while(t!=NULL){
		PXX=t->x;
		PYY=t->y;
		t->x=PX;
		t->y=PY;
		PX=PXX;
		PY=PYY;
		t=t->next;
	}
	return true;
}

bool check(struct Snake* head,bool*gameOver){
	struct Snake*t=head->next;
	while(t!=NULL){
		if(head->x==t->x && head->y==t->y)
		{*gameOver=true;
		break;}
		t=t->next;
	}
	return true;
}

bool saveSnake(char * str){
	int index=0;
	str[index++]='#';
	str[index++]=(char)1;
	str[index++]=(char)2;
	str[index++]='H';
	str[index++]=(char)3;
	str[index++]=(char)6;
	str[index++]='o';
	str[index++]=(char)3;
	str[index++]=(char)7;
	str[index++]='o';
	str[index++]=(char)3;
	str[index++]=(char)8;
	str[index++]='o';
	str[index++]=(char)3;
	str[index++]=(char)9;
	str[index]='*';
	return true;
}

bool setUp(struct Snake* head,struct Food* f,char* str){
	int c;
	printf("enter \n1 to start a new game \n2 to load the saved game\n\t: ");
	scanf("%d",&c);
	
	if(c==1){
		bool statusSnake = createSnake(head);	//printf("create snake %d\n",statusSnake);
		bool statusFood = false;
		while(statusFood != true )
		{	statusFood = createFood(f,head);		//printf("create food %d\n",statusFood);
		}
	
	}
	
	else if(c==2){
		saveSnake(str);
		readSnake(str,f,head);
	}
	
	return true;
}

int main(){	
	bool statusFood;
	struct Snake* head=(struct Snake *) malloc(sizeof(struct Snake));
	struct Food* f=(struct Food*) malloc (sizeof(struct Food));
	char* str=(char *) malloc(500*sizeof(char));
	bool gameOver;
	int SCORE=0;
	char screen[30][30]={{}};
	
	setUp(head,f,str);

	while(!gameOver)
	{
	system("@cls||clear");
	bool statusMapSnake = mapSnake(screen, head);	//printf("map snake %d\n",statusMapSnake);
	bool statusMapFood = mapFood(screen,f);		//printf("map food %d\n",statusMapFood);
	print(screen,SCORE);
	
	int PX=head->x,PY=head->y;
	bool statusInput=input(head,&gameOver,str,f);		//printf("\ninput %d\n",statusInput);
	
	if(head->x==f->x && head->y==f->y){
		bool statusEat=eat(head,PX,PY);
		SCORE++;
		 statusFood = false;
	while(statusFood != true )
	{	statusFood = createFood(f,head);			//printf("create food %d\n",statusFood);
	}
		
	}
	else{
		bool statusMoveSnake = moveSnake(head,PX,PY);	//printf("\nmove snake %d\n",statusMoveSnake);
	}
	
	bool statusCheck=check(head,&gameOver);
		
	int i=0,j=0;
	for(i=0;i<30;i++)
	for(j=0;j<30;j++)
	screen[i][j]='\0';
	Sleep(180);
	}
	return 0;
}



