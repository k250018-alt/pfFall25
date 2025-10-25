#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void generateNewMatrix(int matrix[10][10]) {
    for(int y = 0; y < 10; y++) {
        for(int x = 0; x < 10; x++) {
            matrix[y][x] = rand() % 8; 
        }
    }
}

void printMatrixWithCoords(int matrix[10][10]) {
    printf("    "); 
    for(int x = 0; x < 10; x++) {
        printf("X%-2d ", x);
    }
    printf("\n");
    printf("    ");
    for(int x = 0; x < 10; x++) {
        printf("----");
    }
    printf("\n");
    for(int y = 0; y < 10; y++) {
        printf("Y%-2d|", y); 
        for(int x = 0; x < 10; x++) {
            printf(" %d  ", matrix[y][x]);
        }
        printf("\n");
    }
}
void update(int arr[][10]){
	int x;
	int y;
	printf("\nENTER THE COORDINATES YOU WANT TO UPDATE :\n");
	printf("X COORDINATE : ");
	scanf("%d" ,&x);
	printf("Y COORDINATE : ");
	scanf("%d",&y);
	if(x >= 10 || y >= 10){
		printf("INVALID INPUT");
		return;
	}
	int bit0,bit1,bit2;
	do{
	printf("\n1)Update Power Status(0/1) : ");
	scanf("%d",&bit0);
	if(bit0 != 1 && bit0 != 0){
		printf("Invalid\n");
	} 
	}while(bit0 != 1 && bit0 != 0);
	do{         
	printf("\n2)Update Overload Warning Status(0/1) : ");                   
	scanf("%d",&bit1);
	if(bit1 != 1 && bit1 != 0){
		printf("Invalid\n");
	}                    
	}while(bit1 != 1 && bit1 != 0);
	do{
	printf("\n3)Update Maintenance Required Status(0/1) : ");
	scanf("%d",&bit2);       
	if(bit2 != 1 && bit2 != 0){
		printf("Invalid\n");
	} 
	}while(bit2 != 1 && bit2 != 0);
	int temp = (bit2 << 2) | (bit1 << 1) | bit0;
	arr[y][x] = temp;
	printf("\nUpdated grid\n\n");
	printMatrixWithCoords(arr);
}
void query(int grid[][10]){
	int x;
	int y;
	printf("\nENTER THE COORDINATES YOU WANT TO UPDATE :\n");
	printf("X COORDINATE : ");
	scanf("%d" ,&x);
	printf("Y COORDINATE : ");
	scanf("%d",&y);
	if(x >= 10 || y >= 10){
		printf("INVALID INPUT");
		return;
	}
	int flag1 = grid[y][x] & 1;
	int flag2 = (grid[y][x] >> 1) & 1;
	int flag3 = (grid[y][x] >> 2) & 1;
	printf("\nQuery Report\n");
	printf("\nPower Status : ");
	if(flag1){
		printf("On\n");
	}else{
		printf("Off\n");
	}
	printf("Overload Warning Status : ");
	if(flag2){
		printf("Overloaded\n");
	}else{
		printf("Normal\n");
	}
	printf("Maintenance Requirement Status : ");
	if(flag3){
		printf("Maintenance Required\n");
	}else{
		printf("Maintenance is Not Required\n");
	}
}
void report(int matrix[][10]){
	int count1 =0;
	int count2 =0;
	int count3 =0;
	for(int i =0; i < 10 ; i++){
		for(int j = 0 ; j < 10 ; j++){
				int flag2 = (matrix[i][j] >> 1) & 1;
				int flag3 = (matrix[i][j] >> 2) & 1;
				if(flag2 && flag3){
					count1++;
				}if(flag2){
					count2++;
				}if(flag3){
					count3++;
				}
		}
	}
	printf("\nREPORT OF THE GRID\n\nThe number that overload and require mantenance is : %d\nThe number of overload sectors : %d\nThe number of sector that require mantenance : %d\n",count1,count2,count3);
}                          
int main() {
    int grid[10][10];
    srand(time(NULL));
    generateNewMatrix(grid);
	printf("Original grid:\n");
    printMatrixWithCoords(grid);
    int choice;
    do{
    	
    	printf("\nMain Menu\n1)Update Sector Status\n2)Query Sector Status\n3)Run System Diagnostic\n4)Exit\nEnter your choice : ");
    	scanf("%d",&choice);
    	if(choice == 1){
    		update(grid);
		}else if(choice == 2){
			query(grid);
		}else if(choice == 3){
			report(grid);
		}else if(choice == 4){
			printf("\nExting.......");
		}else{
			printf("\nINVALID INPUT\n");
		}
    	
	}while(choice != 4);
}