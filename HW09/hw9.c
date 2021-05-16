#include<stdio.h>
#include <stdlib.h>
#define MAX_CUSTOMER 50

//void print_current_seq
//void create_updated_seq
// process_customer

typedef enum
{
    employee,
    retired,
    student,
    unemployed,
    other
}labels;

typedef struct 
{
    char name[20];
    int age;
    labels label;
}Customer;

void Add_Customer(Customer *customer,int size);
void print_infos(Customer *customer);
void print_current_seq(Customer *customer, int customer_num);
void process_customer(Customer *customer, int size);

int main(void)
{
    int cur_size = 5;
    Customer customers[MAX_CUSTOMER] = {{"Jack",26,1},
                                        {"Henry",36,2},
                                        {"Muhammed",22,3},
                                        {"Aysegul",21,4},
                                        {"Huseyin",22,0}};
    while (1)
    {
        int choice;
        printf("**********Banking System**********\n");
        printf("Current Sequence:");
        print_current_seq(customers,cur_size);
        printf("\n");
        printf("1-Add customer\n");
        printf("2-Process customer\n");
        printf("Press 0 to quit\n");
        scanf("%d",&choice);
        if (choice == 1)
        {
            Add_Customer(customers,cur_size);
            cur_size++;
        }
        
        else if (choice == 2)
        {
            if(cur_size == 0)
            {
                printf("No customer\n");
            }
            else
            {
                process_customer(customers,cur_size);
                cur_size--;
            }
        }
        else if (choice == 0)
        {
            printf("Goodbye\n");
            exit(1);
        }
        else
            printf("INVALID\n");
    }
}


void Add_Customer(Customer *customer, int size)
{
    printf("\nPlease enter the name of the customer:");
    scanf("%s",customer[size].name);
    printf("\nPlease enter the age of the customer:");
    scanf(" %d",&customer[size].age);
    printf("\nPlease enter the label of the customer:");
    scanf(" %u",&customer[size].label);
}

void print_infos(Customer *customer)
{
    printf("Name: %s\n",customer->name);
    printf("The age: %d\n",customer->age);
    printf("The label: %u\n",customer->label);
}

void print_current_seq(Customer *customer, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d-",customer[i].label);
    }
    printf("\n");
    
}

void process_customer(Customer *customer, int size)
{
    printf("%s\n",customer[0].name);
    for (int i = 0; i < size; i++)
    {
        customer[i] = customer[i+1];
    }
}