#include<stdio.h>
#include<string.h>

void swaper(char str[],int len){
	char temp;
	for(int i = 0; i < len/2 ; i++){
		
		temp = str[i];
		str[i] = str[len - 1 -i];
		str[len - 1- i] = temp;
		
	}
	
}

void bit_converter(char str[],int len){
	
	int temp;
	for(int i = 0 ; i < len ; i++){
		
		temp = (int)str[i];
		temp = temp ^ (1 << 1);
		temp = temp ^ (1 << 4);
		str[i] = (char)temp;
		
	}
	
}

void encoder(char str[] ){
	
	getchar();
	printf("\nEnter the string to be encoded : \n");
	scanf("%[^\n]",str);
	int lengthofstr = strlen(str);
	swaper(str,lengthofstr);
	bit_converter(str,lengthofstr);
	printf("\nEncoded string is : \n%s \n",str);
	
}

void decoder(char str[]){
	
	getchar();
	printf("\nEnter the string to be decoded : \n");
	scanf("%[^\n]",str);
	int lengthofstr = strlen(str);
	swaper(str,lengthofstr);
	bit_converter(str,lengthofstr);
	printf("\nDecoded string is : \n%s \n",str);
	
}

int main(){
	char str[100];
	char encoded_str[100];
	printf("\nMain menu\n");
	int choice;
	do{
		
		printf("\n1)Encode the string\n2)Decode the string\n3)Exit\nEnter your choice: ");
		scanf("%d",&choice);
		if(choice == 1){
			encoder(str);
		}else if (choice == 2){
			decoder(str);
		}else if (choice == 3){
			printf("\nExiting...\n");
		}else{
			printf("INVALID INPUT");
		}
	}while( choice != 3);

}