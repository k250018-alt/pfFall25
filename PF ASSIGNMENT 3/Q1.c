#include<stdio.h>

typedef struct {
	int current_year;
	int toatl_years;
}Year;
typedef struct{
	int loan;
	int interest_rate;
	int installment;	
}Money;
typedef struct{
	Money m;
	Year y;
}Bank;

void calc_Repayment(Bank* b){
	if(b->m.loan <= 0){
		printf("YOU PAID YOUR LOAN");
		return;
	}else if(b->y.current_year == b->y.toatl_years){
		printf("YOU COUDNT PAY YOUR LOAN BACK");
		return;
	}else{
		b->m.loan = b->m.loan * (1+ (b->m.interest_rate/100));
		b->m.loan = b->m.loan - b->m.installment;
		b->y.current_year++;
		printf("You have %d loan remaining and %d years left \n",b->m.loan,b->y.toatl_years-b->y.current_year);
		calc_Repayment(b);
	}
}

int main(){

	Bank b;
	b.y.current_year = 1;
	printf("Enter your loan :");
	scanf("%d", &b.m.loan);
	printf("Enter years left to pay the loan :");
	scanf("%d", &b.y.toatl_years);
	printf("Enter the interest rate :");
	scanf("%d", &b.m.interest_rate);
	printf("Enter your installment amount :");
	scanf("%d", &b.m.installment);
	
	if(b.m.installment >= b.m.loan){
		printf("YOU PAID YOUR LOAN");
	}else{
		calc_Repayment(&b);
	}
	
}