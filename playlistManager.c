#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

struct song{
	int songID;
	struct song *next;
	int played;
};

struct playlist{
	int playlistID;
	int playmode;
	int songcount;
	struct song *songhead;
	struct playlist *next;
};

struct Hash{
	int total;
	struct song* songArr [60];
	int filled[60];
};

int getindex(int i,int ind){
	return (ind*10)+i;
}

void updateAddhash(struct Hash** hash,struct song* s,int ind)
{
	(*hash)->songArr[getindex(s->songID,ind)]=s;
	(*hash)->filled[getindex(s->songID,ind)]=1;
	(*hash)->total++;

}

void updateDelhash(struct Hash** hash,int n,int ind)
{
	(*hash)->filled[getindex(n,ind)]=0;
	(*hash)->total--;
}

void showhash(struct Hash*hash)
{
	int i=0;
	for(i=0;i<60;i++){
		if(hash->filled[i]==1){
			printf("song = %d\n",hash->songArr[i]->songID);
		}
	}
}

void shuffle(struct song *head,int total_songs_in_active_playlist,struct Hash*hash,int plID)
{
	int runNO=0;
	int opt;
	printf("you want to shuffle all songs(0) or current playlist only(1)?\n");
	scanf("%d",&opt);
	printf("playing shuffle:\n");
	int i=0;
	int count=0;
	srand(time(NULL));
	if(opt==0)
	{
		while(count!=hash->total && runNO<65)
		{
			i=rand()%60;
			//printf("\noh no%d\n",hash->total);
			if(hash->filled[i]==1){
				printf("%d\n",hash->songArr[i]->songID);
				hash->filled[i]=100;
				count++;
			}
			runNO++;
		}
		if(count<hash->total)
		{
			int i=0;
			for(i=0;i<60;i++)
			{
				if(hash->filled[i]==1)
				{
					printf("%d\n",hash->songArr[i]->songID);
					hash->filled[i]=100;
					count++;
				}
			}
		}
	
		for(i=0;i<60;i++){
			if(hash->filled[i]==100)
			{
				hash->filled[i]=1;
			}
		}
	}
	else if (opt==1){
		while(count!=total_songs_in_active_playlist)
		{
			i=rand()%10;
			i=i+(plID)*10;
			//printf("\noh no%d\n",hash->total);
			if(hash->filled[i]==1){
				printf("%d\n",hash->songArr[i]->songID);
				hash->filled[i]=100;
				count++;
			}
		}
	
		if(count<total_songs_in_active_playlist)
		{
			int i=0;
			for(i=0;i<60;i++)
			{
				if(hash->filled[i]==1)
				{
					printf("%d\n",hash->songArr[i]->songID);
					hash->filled[i]=100;
					count++;
				}
			}
		}
		for(i=0;i<60;i++){
			if(hash->filled[i]==100)
			{
				hash->filled[i]=1;
			}
		}
	}
	else
	{printf("INVALID option\n");
	}	
	
}

void showPL(struct playlist* plhead,struct Hash* hash)
{	
	int i;
	if(plhead->playmode==1)
	{
		struct playlist* t=plhead;
			printf("pl id = %d :\n",t->playlistID);
			struct song* s=t->songhead;
			while(s!=NULL)
			{
				printf("song id= %d\n",s->songID);
				s=s->next;
			}
	}
	else if(plhead->playmode==2){
		printf("enter song to be played\t");
		scanf("%d",&i);
		struct playlist* t=plhead;
			printf("pl id = %d :\n",t->playlistID);
			struct song* s=t->songhead;
			while(s!=NULL)
			{
				if(s->songID==i)
				{	printf("song id= %d\n",s->songID);
					break;
				}
				s=s->next;
			}
		}	
	
	else if(plhead->playmode==3){
		
		struct playlist* t=plhead;
			printf("pl id = %d :\n",t->playlistID);
			struct song* s=t->songhead;
			while(!kbhit())
			{
				while(s!=NULL)
				{
					printf("song id= %d\n",s->songID);
					s=s->next;
				}
				s=t->songhead;
			}
	}
	else if(plhead->playmode==4){
		shuffle(plhead->songhead,plhead->songcount,hash,plhead->playlistID);
	}
	else{
		printf("\ninvalid option\n");
	}
}

void addSong(struct song **head,struct Hash**hash,int ind)
{
	struct song *s=(struct song*) malloc(sizeof(struct song));
	s->next=NULL;
	if(*head==NULL)
	{
		s->songID=0;
		*head=s;
	}
	else
	{
		struct song *t=*head;
		while(t->next!=NULL){
			t=t->next;
		}
		s->songID=t->songID+1;
		s->next=NULL;
		t->next=s;
	}
		updateAddhash(hash,s,ind);
}

struct playlist* createPL(struct playlist** plhead,struct Hash**hash)
{
	struct playlist*pl=(struct playlist*) malloc(sizeof(struct playlist));
	pl->songcount=1;
	pl->playmode=1;
	pl->songhead=NULL;
	pl->next=NULL;
	if((*plhead)==NULL)
	{
		pl->playlistID=0;
		*plhead=pl;
	}
	else
	{
		struct playlist* t=*plhead;
		while(t->next!=NULL){
			t=t->next;	
		}
		pl->playlistID=t->playlistID+1;
		t->next=pl;
	}
	addSong(&(pl->songhead),hash,pl->playlistID);
	return pl;
}

struct playlist* deleteSong(struct playlist *head,struct Hash**hash)
{
	printf("enter song to be deleted\t");
	int n,flag=0;
	struct song* prev;
	scanf("%d",&n);
	struct song *t=head->songhead;
	struct song *ptr;	
	if(head->songhead->songID==n)
	{
		ptr=head->songhead;
		head->songhead=head->songhead->next;
		head->songcount--;
		updateDelhash(hash,n,head->playlistID);
	}
	else
	{
		while(t!=NULL)
		{
			if(t->songID==n)
			{flag=1;break;
			}
			prev=t;
			t=t->next;
		}
		if(flag==1)
		{
		ptr=t;
		prev->next=t->next;
		head->songcount--;
		updateDelhash(hash,n,head->playlistID);
		}
		else
		{printf("INVALID song\n");
		return head;
		}
	}
	free(ptr);
	return head;
	
}

struct playlist* change_playlist(struct playlist** plhead,struct Hash** hash)
{
	printf("enter \n1 to create a new playlist\n\t2 to select from already created playlists\n");
	int opt;
	struct playlist*t=*plhead;
	scanf("%d",&opt);
	if(opt==1){
		return createPL(plhead,hash);
	}
	else if(opt==2){
		printf("Enter playlist to be selected\n");
		scanf("%d",&opt);
		while(t!=NULL){
			if(t->playlistID==opt){
				return t;
			}
			t=t->next;
		}
		printf("INVALID playlist");
		return *plhead;
	}
	printf("INVALID option");
}

int main()
{
	int option;
	struct playlist* plhead=NULL;
	struct Hash* hash=(struct Hash*)malloc(sizeof(struct Hash));
	struct playlist* active_playlist=createPL(&plhead,&hash);
	
	printf("current play list: \n");
	showPL(active_playlist,hash);
	
	printf("enter \n\t1 to add song\t2 to delete song\n\t4 to play\t5 to exit\n\t6 to view hash\t7 to change active playlist \n");
	scanf("%d",&option);
	int plModOpt;
	
	while(option!=5){
		
		switch(option){
			case 1:
				addSong(&(active_playlist->songhead),&hash,active_playlist->playlistID);
				active_playlist->songcount++;
				break;
			case 2:
				deleteSong(active_playlist,&hash);
				break;
			case 3:
				break;
			case 4:
				printf("do u dant to play in previous playmode(0) or want to select new mode(1)?\n");
				scanf("%d",&plModOpt);
				if(plModOpt==1)
				{
				printf("enter \n\t1 to play all songs once\n\t2 to play current song\n\t3 to play all songs in repeat\n\t4 to shuffle \n");
				scanf("%d",&active_playlist->playmode);
				}
				printf("current play list: \n");
				showPL(active_playlist,hash);
				break;
			case 6:
				printf("current hash status is : \n");
				showhash(hash);
				break;
			case 7:
				active_playlist=change_playlist(&plhead,&hash);
				break;
		}
		printf("enter \n\t1 to add song\t2 to delete song\n\t4 to play\t5 to exit\n\t6 to view hash\t7 to change active playlist \n");
		scanf("%d",&option);
	}
	return 0;
}
