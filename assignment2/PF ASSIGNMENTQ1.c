#include<stdio.h>
#include<string.h>

//function to remove unnecessary rows
void removeZeroQuantity(int isbn[], char books[][50], float prices[], int quan[], int *count) {
    int newCount = 0;
    
    for(int i = 0; i < *count; i++) {
        if(quan[i] != 0) {
            if(newCount != i) {
                isbn[newCount] = isbn[i];
                strcpy(books[newCount], books[i]);
                prices[newCount] = prices[i];
                quan[newCount] = quan[i];
            }
            newCount++;
        }
    }
    *count = newCount;
}
//function to add data
void enteringdata(int isbn[], char books[][50], float prices[], int quan[], int *count) {
    int x;
    printf("Enter the ISBN: ");
    scanf("%d", &x);
    
    if(x <= 0) {
        printf("Invalid ISBN\n");
        return;
    }
    
    for(int i = 0; i < *count; i++) {
        if(isbn[i] == x) {
            printf("ISBN Repeated Invalid Input\n");
            return;
        }
    }
    
    char entered_book[50];
    printf("Enter the book title: ");
    scanf(" %[^\n]", entered_book);
    
    for(int i = 0; i < *count; i++) {
        if(strcasecmp(books[i], entered_book) == 0) {
            printf("Book title Repeated Invalid Input\n");
            return;
        }
    }
    
    float entered_price;
    printf("Enter the price: ");
    scanf("%f", &entered_price);
    if(entered_price <= 0){
    	printf("INVALID PRICE");
    	return;
	}
    int entered_quantity;
    printf("Enter the quantity: ");
    scanf("%d", &entered_quantity);
    if(entered_price <= 0){
    	printf("INVALID QUANTITY");
    	return;
	}
    isbn[*count] = x;
    strcpy(books[*count], entered_book);
    prices[*count] = entered_price;
    quan[*count] = entered_quantity;
    
    (*count)++;  
    
    printf("\n%-10s %-20s %-12s %-10s\n", "ISBN", "BOOK TITLE", "PRICE", "QUANTITY");
    printf("---------- -------------------- ------------ ----------\n");
    for(int i = 0; i < *count; i++) {
        printf("%-10d %-20s $%-11.2f %-10d\n", isbn[i], books[i], prices[i], quan[i]);
    }
}

//function to process sales
void processingdata(int isbn[], char books[][50], float prices[], int quan[], int *count){
	int x;
	int Entered_quan;
	printf("Enter a the ISBN : ");
	scanf("%d",&x);
	for(int i = 0; i < *count; i++) {
        if(isbn[i] == x) {
            printf("Enter the quantity of the books sold : ");
            scanf("%d",&Entered_quan);
            if( Entered_quan > quan[i]){
            	printf("INVALID QUANTITY \n");
            	return;
			}else{
				quan[i] -= Entered_quan;
				if(quan[i] == 0){
					removeZeroQuantity(isbn, books, prices, quan, count);
				}
				printf("\n%-10s %-20s %-12s %-10s\n", "ISBN", "BOOK TITLE", "PRICE", "QUANTITY");
    			printf("---------- -------------------- ------------ ----------\n");
    			for(int i = 0; i < *count; i++) {
        		printf("%-10d %-20s $%-11.2f %-10d\n", isbn[i], books[i], prices[i], quan[i]);
			}
			}
        }else{
        	printf("INVALID ISBN\n");
        	return;
		}
    }
	
}
//functions to generate a report
void generaterep(int isbn[], char books[][50], float prices[], int quan[], int *count) {
    printf("\nSTOCK STATUS REPORT\n");
    printf("===================\n");
    
    printf("%-10s %-25s %-10s %-10s %-10s\n", "ISBN", "BOOK TITLE", "PRICE", "QUANTITY", "STATUS");
    printf("---------- ------------------------- ---------- ---------- ----------\n");
    
    for(int i = 0; i < *count; i++) {
        char status[20];
        if(quan[i] > 5) {
            strcpy(status, "HIGH");
        } else {
            strcpy(status, "LOW");
        }
        
        printf("%-10d %-25s $%-8.2f %-10d %-10s\n", 
               isbn[i], books[i], prices[i], quan[i], status);
    }
    
    printf("===================\n");
}
int main() {
    //Original data
    int isbn[100] = {123456, 234567, 345678, 456789, 567890, 678901, 789012, 890123, 901234, 112233};
    char book_titles[100][50] = {"The Silent Forest", "Echoes of Time", "Beyond the Horizon", "Shadows of Yesterday", "The Last Promise", "Whispers in the Dark", "Chronicles of Fire", "The Hidden City", "River of Dreams", "Mountain of Secrets"};
    float prices[100] = {24.99, 15.50, 32.75, 19.99, 27.25, 21.99, 18.75, 29.50, 16.25, 35.99};
    int quantity[100] = {15, 8, 23, 12, 5, 18, 7, 14, 9, 11};
    
    int isbn_count = 10;  
    
    // Showing the original data
    printf("Original data:\n");
    printf("%-10s %-20s %-12s %-10s\n", "ISBN", "BOOK TITLE", "PRICE", "QUANTITY");
    printf("---------- -------------------- ------------ ----------\n");
    for(int i = 0; i < isbn_count; i++) {
        printf("%-10d %-20s $%-11.2f %-10d\n", isbn[i], book_titles[i], prices[i], quantity[i]);
    }
    printf("---------- -------------------- ------------ ----------\n");
    
    // Main menu
    int choice;
    printf("\nWELCOME\nPlease enter your choice via 1,2,3 and 4\n");
    do {
        printf("\n1) ADD PRODUCT\n");
        printf("2) PROCESS A SALE\n");
        printf("3) GENERATE A REPORT FOR LOW QUANTITY\n");
        printf("4) EXIT\n");
        printf("YOUR CHOICE: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
        	printf("ENTERING THE DATA :\n");
            enteringdata(isbn, book_titles, prices, quantity, &isbn_count);
        }
        if(choice == 2){
        	printf("PROCESSING THE SALE :\n");
        	processingdata(isbn, book_titles, prices, quantity, &isbn_count);
		}
        if(choice == 3){
        	printf("GENERATING THE REPORT :\n");
        	generaterep(isbn, book_titles, prices, quantity, &isbn_count);
		}
    } while(choice != 4);
    
    return 0;
}