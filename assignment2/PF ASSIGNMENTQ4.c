#include<stdio.h>
int count =0 ;
//printing an array
void arrprint(int x[], int y){
    printf("| ");
    for(int i = 0; i < y; i++){
        printf("%d | ", x[i]);
    }
}
//push
void push(int stack[], int *top, int maxSize){
	
	if(*top < maxSize){
		int num;
		printf("\nEnter the element : ");
		scanf("%d",&num);
		stack[*top] = num;
		(*top)++;
	}else{
		printf("\nMax limit of data reached\n");
	}
	
}
//pop
void pop(int stack[], int *top){
	
	if(*top > 0){
		(*top)--;
		printf("\n%d was deleted\n",stack[*top]);
	}else{
		printf("\nNo data is present in the stack\n");
	}
	
}
//peek
void peek(int stack[], int *top){
	
	if(*top > 0){
		printf("\n%d is the Top element\n",stack[*top- 1]);
	}else{
		printf("\nNo data found inside stack\n");
	}
	
}
//display
void display(int stack[], int top){
	
	if(top > 0){
		arrprint(stack,top);
	}else{
		printf("\nNo data found inside stack\n");
	}
	
}

int main(){
	
	int size = 100;
	int arr[size];
	printf("Main Menu\n");
	//main menu
	int choice;
	do{
		
		printf("\n============\n1)PUSH \n2)POP \n3)PEEK \n4)DISPLAY \n5)Exit\nEnter your choice : ");
		scanf("%d",&choice);
		if(choice == 1){
			
			push(arr, &count, size);
			
		}else if(choice == 2){
			
			pop(arr,&count);
			
		}else if(choice == 3){
			
			peek(arr,&count);
			
		}else if(choice == 4){
			
			display(arr,count);
			
		}else if(choice == 5){
			
			printf("Exiting .....");
			
		}else{
			printf("INVALID INPUT\n");
		}
		
	}while(choice != 5);
}