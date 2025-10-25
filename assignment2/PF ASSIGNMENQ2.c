#include<stdio.h>
#include<string.h>

int cart_count = 0;
float customer_cart[100][2];
long int customer_id;
char customer_name[50];

void removeZeroQuantity(int product_number[], int quantity[], float price_per_product[], int *count) {
    int newCount = 0;
    
    for(int i = 0; i < *count; i++) {
        if(quantity[i] != 0) {
            if(newCount != i) {
                product_number[newCount] = product_number[i];
                quantity[newCount] = quantity[i];
                price_per_product[newCount] = price_per_product[i];
            }
            newCount++;
        }
    }
    *count = newCount;
}

void addingtostock(int pro_no[], int qty[], float price[], int *count){
    int entered_pro_no;
    int entered_quan;
    int found = 0;
    
    printf("\nEnter the product number: ");
    scanf("%d", &entered_pro_no);
    
    for(int i = 0; i < *count; i++){
        if(pro_no[i] == entered_pro_no){
            found = 1;
            printf("Enter the quantity: ");
            scanf("%d", &entered_quan);
            
            if(entered_quan <= qty[i]){
                customer_cart[cart_count][0] = pro_no[i];
                customer_cart[cart_count][1] = price[i] * (float)entered_quan;
                cart_count++;
                qty[i] -= entered_quan;
                if(qty[i] == 0){
                    removeZeroQuantity(pro_no, qty, price, count);
                }
                printf("Product added to cart successfully!\n");
            } else {
                printf("Invalid Input: Not enough quantity available\n");
            }
            break;
        }
    }
    
    if(!found){
        printf("Invalid Input: Product not found\n");
    }
    
    printf("\nINVENTORY\n");
    printf("=== PRODUCT INVENTORY ===\n");
    printf("Sr.No | Product No | Quantity | Price\n");
    printf("------|------------|----------|-------\n");
    for(int i = 0; i < *count; i++){
        printf("%5d | %10d | %8d | %6.2f\n", 
               i+1, pro_no[i], qty[i], price[i]);
    }
}

void showBill(){
    float total = 0;
    float voucher_discount = 0;
    float promo_discount = 0;
    float total_discount = 0;
    float final_total = 0;
    int choice;
    char promo[50];
    int has_voucher = 0;
    int has_promo = 0;
    
    printf("\n=== CUSTOMER BILL ===\n");
    printf("Customer ID: %ld\n", customer_id);
    printf("Customer Name: %s\n", customer_name);
    printf("\nItems in Cart:\n");
    printf("Product No | Total Price\n");
    printf("-----------|------------\n");
    
    for(int i = 0; i < cart_count; i++){
        printf("%10.0f | %11.2f\n", customer_cart[i][0], customer_cart[i][1]);
        total += customer_cart[i][1];
    }
    
    printf("-----------|------------\n");
    printf("Subtotal: $%.2f\n", total);
    
    printf("\n=== DISCOUNT OPTIONS ===\n");
    do{
    printf("Do you have a voucher? (1 for Yes, 0 for No): ");
    scanf("%d", &has_voucher);
    if(has_voucher != 1 && has_voucher != 0){
    	printf("INVALID INPUT\n");
	}
}while(has_voucher != 1 && has_voucher != 0);
    if(has_voucher == 1){
        voucher_discount = total * 0.25;
        printf("Voucher applied! 25%% discount: -$%.2f\n", voucher_discount);
    }
	do{
    printf("Do you have a promocode? (1 for Yes, 0 for No): ");
    scanf("%d", &has_promo);
    if(has_promo != 1 && has_promo != 0){
    	printf("INVALID INPUT\n");
	}
}while(has_promo != 1 && has_promo != 0);
    if(has_promo ==1){
        printf("Enter the promocode: ");
        scanf("%s", promo);
        if(strcmp(promo, "Eid2025") == 0){
            promo_discount = total * 0.10;
            printf("Promocode applied! 10%% discount: -$%.2f\n", promo_discount);
        } else {
            printf("Invalid promocode!\n");
            has_promo = 0;
        }
    }
    
    total_discount = voucher_discount + promo_discount;
    final_total = total - total_discount;
    
    printf("\n=== FINAL INVOICE ===\n");
    printf("Customer ID: %ld\n", customer_id);
    printf("Customer Name: %s\n", customer_name);
    printf("----------------------------------------\n");
    printf("Product No | Total Price\n");
    printf("-----------|------------\n");
    
    for(int i = 0; i < cart_count; i++){
        printf("%10.0f | %11.2f\n", customer_cart[i][0], customer_cart[i][1]);
    }
    
    printf("-----------|------------\n");
    printf("Subtotal:        $%11.2f\n", total);
    
    if(has_voucher){
        printf("Voucher (25%%):   $%11.2f\n", voucher_discount);
    }
    if(has_promo){
        printf("Promo (10%%):     $%11.2f\n", promo_discount);
    }
    if(!has_voucher && !has_promo){
        printf("Discount:        $%11.2f\n", 0.00);
    }
    
    printf("Total Discount:  $%11.2f\n", total_discount);
    printf("                 ------------\n");
    printf("Final Total:     $%11.2f\n", final_total);
    printf("----------------------------------------\n");
    printf("Thank you for shopping with us!\n");
}

int main(){
    int product_number[20] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120};
    int quantity[20] = {5, 8, 12, 3, 15, 7, 9, 20, 6, 11, 4, 18, 10, 2, 14, 8, 13, 5, 16, 7};
    float price_per_product[20] = {25.50, 12.75, 8.99, 45.25, 5.50, 15.75, 32.99, 7.25, 18.50, 9.99, 22.75, 6.50, 14.25, 55.00, 11.99, 28.50, 16.75, 42.25, 4.99, 19.75};
    int number_of_products = 20;
    
    printf("INVENTORY\n");
    printf("=== PRODUCT INVENTORY ===\n");
    printf("Sr.No | Product No | Quantity | Price\n");
    printf("------|------------|----------|-------\n");
    for(int i = 0; i < number_of_products; i++){
        printf("%5d | %10d | %8d | %6.2f\n", 
               i+1, product_number[i], quantity[i], price_per_product[i]);
    }
    
    printf("\nEnter your ID: ");
    scanf("%ld", &customer_id);
    printf("Enter your Name: ");
    scanf(" %[^\n]", customer_name);
    printf("\nMAIN MENU\n=============\n");
    printf("WELCOME %s\n", customer_name);
    int choice;
    do{
        printf("1) ADD PRODUCTS\n");
        printf("2) SHOW THE BILL\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1){
            addingtostock(product_number, quantity, price_per_product, &number_of_products);
        }
        else if(choice == 2){
            showBill();
        }
        else{
            printf("Invalid choice! Please try again.\n");
        }
        
    } while(choice != 2);

    return 0;
}