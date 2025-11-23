#include<stdio.h>
#include<string.h>

typedef struct{
	int book_ID;
	int Popularity_score;
}Books;
typedef struct{
	Books book[6];
	int current_index;
	int Entered_id;
	int Entered_Popularity_score;
}shelf;
int checkforrepetition(shelf *s){
	for(int i =0 ; i < s->current_index ; i++){
		if(s->Entered_id == s->book[i].book_ID){
			s->book[i].Popularity_score = s->Entered_Popularity_score;
			return 0;
		}
	}
	return 1;
}
void shiftbooks(shelf *s){
	for(int i = 0 ; i < 6 ; i++){
		if( i == 5 ){
			s->book[i].book_ID =s->Entered_id;
			s->book[i].Popularity_score = s->Entered_Popularity_score;
		}else{
			s->book[i].book_ID =s->book[i+1].book_ID;
			s->book[i].Popularity_score = s->book[i+1].Popularity_score;
		}
	}
}
void Addcommandfunc(shelf *s){
	int check = checkforrepetition(s);
	if(check){
		if(s->current_index < 6){
			s->book[s->current_index].book_ID = s->Entered_id;
			s->book[s->current_index].Popularity_score = s->Entered_Popularity_score;
			s->current_index++;
		}else{
			shiftbooks(s);
		}
	}
}
int Accesscommandfunc(shelf *s){
	if(s->current_index == 0){
		printf("No entered data\n");
		return -1;
	}
	for(int i =0; i < s->current_index ; i++){
		if(s->book[i].book_ID == s->Entered_id){
			return s->book[i].Popularity_score;
		}
	}
	return -1;
}
int main(){
	shelf s;
	char command[10];
	s.current_index = 0;
	printf("This is a shelf with a max capacity of 6 you can add book with the command ADD x y (x being book id and y being its popularity score) or you can access it by ACCESS x You can exit by typing EXIT");
	do{
		printf("\n>");
		scanf("%s",command);
		if(strcasecmp(command , "ADD") == 0){
			printf(" x : ");
			scanf("%d",&s.Entered_id);
			printf(" y : ");
			scanf("%d",&s.Entered_Popularity_score);
			Addcommandfunc(&s);
		}else if(strcasecmp(command , "ACCESS") == 0){
			printf(" x : ");
			scanf("%d",&s.Entered_id);
			printf(" Result : %d\n",Accesscommandfunc(&s));
		}else if(strcasecmp(command , "Exit") == 0){
			printf("Exiting...");
		}else{
			printf("Command not Found\n");
		}
	}while(strcasecmp(command , "Exit") != 0);
}

