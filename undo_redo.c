#include<stdio.h>
#include<string.h>

struct data{
	int operation;
	int position;
	char* str;
};

struct stack{
	struct data* d;
	int top;
};

void push(struct stack* stk,int opt,int pos,char* word)
{
	
	stk->top=stk->top+1;
	stk->d[stk->top].str=(char*)malloc(50*sizeof(char));
	stk->d[stk->top].operation=opt;
	stk->d[stk->top].position=pos;
	strcpy(stk->d[stk->top].str,word);
	
}

void printStack(struct stack*s){
	int i;
	for(i=s->top;i>=0;i--){
		printf("i=%d  opt=%d  pos=%d  word=%s\n",i,s->d[i].operation,s->d[i].position,s->d[i].str);
	}
}

void insertion(struct stack* s,int pos,char* word,char* str,int flag)
{
	int count=0,i=0;
	if(pos>0)
	{
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]==' '){
			count++;
		}
		if(count==pos){
			break;
		}
	}
	if(str[i]=='\0')
	{i--;
	}
	}
	
	//printf("i= %c\n",str[i]);
	
	int x=strlen(str)+1;
	int y=x+strlen(word)+1;
	
	while(x>=i)
	{
		str[y--]=str[x--];
	}
	
	if(pos==0)
	{str[y--]=' ';}
	
	int t=strlen(word);
	t--;
	if(str[i+1]=='\0')
	{y++;}
	while(t>=0){
		str[y--]=word[t--];
	}
	if(str[i+1]=='\0')
	{str[y--]=' ';}
	
	printf("string is  ===%s\n",str);
	if(flag==1)
	{
		push(s,1,pos,word);
	}
}

void deletion(struct stack* s,int pos,char* str,int flag)
{
	char word[20];
	int count=0,i=0,j,k=0;
	if(pos==0){
		i=0;	
	}
	else
	{
		for(i=0;str[i]!='\0';i++)
		{
			if(str[i]==' '){
				count++;
			}
			if(count==pos){
				i++;break;
			}
		}
	}
	//printf("i= %c\n",str[i]);
	for(j=i;str[j]!=' '&&str[j]!='\0';j++)
	{
			word[k++]=str[j];
	}
	if(str[j]=='\0' )
	{
		if( pos==count)
			{
				str[i-1]='\0';
			}
		else{
			printf("\nindex out of range\n");
			flag=0;
		}
	}
	else
	{
		j++;
		word[k]='\0';
		printf("word ======%s\n",word);
		for(k=i;str[j]!='\0';)
		{
			str[k++]=str[j++];
		}
		str[k]='\0';
	}
	printf("string is ===%s\n",str);
	if(flag==1)
	{push(s,2,pos,word);
	}
}

void undo(struct stack* s,struct stack* r,char* str)
{
	push(r,s->d[s->top].operation,s->d[s->top].position,s->d[s->top].str);
	if(s->d[s->top].operation==1){
		deletion(s,s->d[s->top].position,str,0);
	}
	if(s->d[s->top].operation==2){
		insertion(s,s->d[s->top].position,s->d[s->top].str,str,0);
	}
	s->top=s->top-1;
}

void redo(struct stack* s,struct stack* r,char* str)
{
	push(r,s->d[s->top].operation,s->d[s->top].position,s->d[s->top].str);
	if(s->d[s->top].operation==2){
		deletion(s,s->d[s->top].position,str,0);
	}
	if(s->d[s->top].operation==1){
		insertion(s,s->d[s->top].position,s->d[s->top].str,str,0);
	}
	s->top=s->top-1;
}

int main(){
	int i=1;
	int pos;
	
	struct stack* s=(struct stack*)calloc(1,sizeof(struct stack));
	s->d=(struct data*)malloc(10*sizeof(struct data));
	s->top=-1;
	
	struct stack* r=(struct stack*)calloc(1,sizeof(struct stack));
	r->d=(struct data*)malloc(10*sizeof(struct data));
	r->top=-1;
	
	char str[100];
	printf("enter the string : ");
	gets(str);
	printf("\n%s\n",str);
	char word[50];
	word[0]='\0';
	printf("1: INSERT \t2: DELETE \t3: UNDO \t4: REDO \t9:EXIT\n");
	while(i!=9)
	{
		printf("ENTER OPERATION : \t");
		scanf("%d",&i);
		switch(i){
			case 1:
				printf("\t\tEnter postion and word :\t");
				scanf("%d",&pos);
				scanf("%s",word);
				insertion(s,pos,word,str,1);
				break;
			case 2:
				printf("\t\tEnter postion to delete :\t");
				scanf("%d",&pos);
				deletion(s,pos,str,1);
				break;
			case 3:
				if(s->top>-1)
				{undo(s,r,str);
				}
				else{
					printf("\nundo stack in empty\n");
				}
				break;
			case 4:
				if(r->top>-1)
				{redo(r,s,str);
				}
				else{
					printf("\nredo stack in empty\n");
				}
				break;
			case 9:
				printf("EXIT\n");
				break;
		}
		printf("\nS UNDO STACK\n");
	printStack(s);
	
		printf("\nR REDO STACK\n");
	printStack(r);
	printf("\n");	
	}
	
	return 0;
}

