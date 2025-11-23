#include<stdio.h>

typedef struct {
	int EmplyID;
	char Name[40];
	char desgnation[40];
	int salary;
}Employee;

int isDuplicateID(Employee *table, int count) {
   for (int i = 0; i < count; i++) {
        if (table[i].EmplyID == table[count].EmplyID)
            return 1;
    }
    return 0;
}
void EnterData(Employee *table){
	for(int i = 0 ; i < 5 ; i++){
		while (1) {
            printf("Enter Employee ID for employee %d: ", i+1);
            scanf("%d", &table[i].EmplyID);
            if (isDuplicateID(table, i)) {
                printf("? ID already exists! Please enter a unique ID.\n");
            } else {
                break; 
            }
        }
		printf("Enter the employee name: ");
        scanf(" %39[^\n]", table[i].Name);
        printf("Enter the employee designation: ");
        scanf(" %39[^\n]", table[i].desgnation);
		printf("Enter the salary of employee : ");
		scanf("%d",&table[i].salary);
		
	}
	
}
void DisplayData(Employee *table){
	for(int i =0 ; i< 5 ; i++){
		printf("| %d  |  %d  |   %-15s   |   %-15s  |   %d  |\n",i,table[i].EmplyID,table[i].Name,table[i].desgnation,table[i].salary);
	}
}
void searchEmployee(Employee *table){
	int searched_emplyid ;
	printf("Enter the id you want to search : ");
	scanf("%d",&searched_emplyid );
	int found =0;
	int pointer = -1;
	for(int i = 0 ; i < 5 ; i++){
		if(searched_emplyid == table[i].EmplyID){
			found =1;
			pointer = i;
			break;
		}
	}
	if(found){
		printf("| %d  |  %d  |   %-15s   |   %-15s  |   %d  |\n",pointer,table[pointer].EmplyID,table[pointer].Name,table[pointer].desgnation,table[pointer].salary);
	}else{
		printf("INVALID ID");
	}
}
void FindHighestSalary(Employee *table){
	int highestSalary = table[0].salary;
	int pointer = 0;
	for(int i = 1 ; i< 5 ;i++){
		if(highestSalary < table[i].salary){
			highestSalary = table[i].salary;
			pointer = i;
		}
	}
	printf("| %d  |  %d  |   %-15s   |   %-15s  |   %d  |\n",pointer,table[pointer].EmplyID,table[pointer].Name,table[pointer].desgnation,table[pointer].salary);
}
void Givebonus(Employee *table){
	int thereshold;
	int bonus;
	printf("Enter a thereshold of salary you want to increase of : ");
	scanf("%d",&thereshold);
	printf("Enter the bonus percentage : ");
	scanf("%d",&bonus);
	for(int i =0 ; i < 5 ; i++){
		if(table[i].salary <= thereshold){
			table[i].salary = table[i].salary * (1 + (bonus/100.0));
		}
	}
}
int main(){
	
	Employee table[5];
	EnterData(table);
	int choice;
	do{
		printf("\n1)Display Employee data \n2)Search for employee \n3)Find highest Salary \n4)Give bonus to employee with certain salary threshold \n5)Exit\n Enter your choice : ");
		scanf("%d",&choice);
		if(choice == 1){
			DisplayData(table);
		}else if(choice == 2){
			searchEmployee(table);
		}else if(choice == 3){
			FindHighestSalary(table);
		}else if(choice == 4){
			Givebonus(table);
		}else if(choice == 5){
			printf("Exiting....");
		}else{
			printf("INVALID INPUT");
		}
	}while(choice != 5);
	
	
}