#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define SIZE 50

struct ticket{
	char id[20];
	char name[20];
	int age;
	char ticketClass[20];
	int day;
	int price;
	
	ticket *next;
}*head[SIZE];

int sum = 1;

ticket *newTicket(char id[], char name[], int age, char ticketClass[], int day, int price){
	ticket *curr = (ticket*)malloc(sizeof(ticket));
	strcpy(curr->id, id);
	strcpy(curr->name, name);
	curr->age = age;
	strcpy(curr->ticketClass, ticketClass);
	curr->day = day;
	curr->price = price;
	
	curr->next = NULL;
	return curr;
}

int getKey(char x[]){
	int key = 0;
	key = x[strlen(x)-3] + x[strlen(x)-2] + x[strlen(x)-1] - 1;
	
	key = key%SIZE;
	return key;
}

void push(int key, ticket *curr){
	if(head[key] == NULL){
		head[key] = curr;
	}else{
		curr->next = head[key];
		head[key] = curr;
	}
}

void addTicket(){
	char id[20];
	char idrand[20];
	char name[20];
	int age;
	char ticketClass[20];
	int day;
	int price;
	
	do{
		printf("Input your name : ");
		scanf("%[^\n]", name);getchar();
	}while(strlen(name) < 5 || strlen(name) > 20);
	
	do{
		printf("Input your age : ");
		scanf("%d", &age);getchar();
	}while(age < 0 || age > 100);
	
	do{
		printf("Input your ticket class : ");
		scanf("%[^\n]", ticketClass);getchar();
	}while(strcmp(ticketClass, "First Class") != 0 && strcmp(ticketClass, "Business Class") != 0 && strcmp(ticketClass, "Economy Class") != 0);
	
	do{
		printf("Input days : ");
		scanf("%d", &day);getchar();
	}while(day < 1 || day > 15);
	
	if(strcmp(ticketClass, "First Class") == 0){
		strcpy(id, "FC");
		price = 500 * day;
	}
	if(strcmp(ticketClass, "Business Class") == 0){
		strcpy(id, "BC");
		price = 200 * day;
	}
	if(strcmp(ticketClass, "Economy Class") == 0){
		strcpy(id, "EC");
		price = 300 * day;
	}
	sprintf(idrand, "%d%d%d",rand()%10,rand()%10,rand()%10);
	strcat(id, idrand);
	
	printf("\nSuccesfully Inserted\n");
	printf("====================\n");
	printf("Ticket ID	:	%s\n", id);
	printf("Todal Price	:	$%d\n", price);
	
	ticket *curr = newTicket(id, name, age, ticketClass, day, price);
	int key = getKey(id);
	push(key, curr);
}

void viewTicket(){
	int sum = 0;
	for(int i=0; i<SIZE; i++){
		if (head[i] == NULL){
			sum = sum+1;
		}
	}
	if(sum != SIZE){
		for(int i=0; i<SIZE; i++){
			if(head[i] == NULL){
				continue;
			}else{
				ticket *temp = head[i];
				while(temp != NULL){
					printf("Bluejack Cruise Tickets\n");
					printf("==========================\n");
					printf("          %s\n", temp->id);
					printf("==========================\n");
					printf("Name	: %s\n", temp->name);
					printf("Age	: %d\n", temp->age);
					printf("Class	: %s\n", temp->ticketClass);
					printf("Days	: %d\n", temp->day);
					printf("Price	: $%d\n", temp->price);
					printf("==========================\n\n");
					
					temp = temp->next;
				}
			}
		}
	}else{
		printf("\nThere is no ticket !\n");
	}	
}

void deleteTicket(char id[]){
	int key = getKey(id);
	
	if(head[key] != NULL){
		if(strcmp(head[key]->id, id) == 0){
			ticket *temp = head[key];
			
			head[key] = head[key]->next;
			temp->next = NULL;
			temp = NULL;
			free(temp);
			printf("Succesfully Delete %s\n", id);
			return;
		}else{
			ticket *temp2 = head[key];
			while(temp2->next != NULL && strcmp(temp2->next->id, id) != 0){
				temp2 = temp2->next;
			}
			if(temp2->next == NULL){
				printf("Failed to delete because The Data doens't exists\n");
				return;
			}
			ticket *temp = temp2->next;
			
			free(temp);
			temp = NULL;
			printf("Succesfully Delete %s\n", id);
			return;
		}
	}else{
		printf("There is no ticket!\n");
	}
}

int main(){
	int choose = 0;
	menu:
		system("cls");
	do{
		printf("Welcome To Bluejack Cruise\n");
		printf("==========================\n");
		printf("1. Buy Cruise Ticket\n");
		printf("2. View All Cruise Ticket\n");
		printf("3. Delete Cruise Ticket\n");
		printf("4. Exit\n");
		printf("Choose : \n");
		scanf("%d", &choose);getchar();
		
		switch(choose){
			case 1:
				addTicket();
				printf("Press any to continue . . .");getchar();
				goto menu;
				break;
			case 2:
				viewTicket();
				printf("Press any to continue . . .");getchar();
				goto menu;
				break;
			case 3:
				viewTicket();
				char del[20];
				printf("Input Ticket ID to delete: ");
				scanf(" %[^\n]", del);getchar();
				deleteTicket(del);
				printf("Press any to continue . . .");getchar();
				goto menu;
				break;
			case 4:
				system("cls");
				break;	
		}
	}while(choose != 4);
	return 0;
}
