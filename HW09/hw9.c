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
void print_current_seq(Customer customer[MAX_CUSTOMER][MAX_CUSTOMER], int *size, int seq_num);
void process_customer(Customer *customer, int size);
void order_seq(Customer *customer, int size, int last_label);



int main(void)
{
    int size[MAX_CUSTOMER] = {0};
    size[0] = 5;
    size[1] = 4;
    int seq_num = 1;
    // size[2] =
    // {{1,2,3,4,5},{1,2,3,4}}
    //size[2] = {5};
    //seq_num = 0 1
    //seq_num = 0
    //size[seq_num] = 5

    Customer customers[MAX_CUSTOMER][MAX_CUSTOMER] = {
                                       {{"Jack",26,1},
                                        {"Henry",36,2},
                                        {"Muhammed",22,3},
                                        {"Aysegul",21,4},
                                        {"Huseyin",22,0}}
                                        ,
                                        {{"Jack",26,0},
                                        {"Henry",36,3},
                                        {"Muhammed",22,2},
                                        {"Aysegul",21,4}
                                        }};
    while (1)
    {
        int choice;
        printf("**********Banking System**********\n");
        printf("Current Sequence:");
        print_current_seq(customers,size,seq_num);
        printf("\n");
        printf("1-Add customer\n");
        printf("2-Process customer\n");
        printf("Press 0 to quit\n");
        scanf("%d",&choice);
        if (choice == 1)
        {
            // Add_Customer(customers,cur_size);
            // cur_size++;
        }
        
        else if (choice == 2)
        {
            if(size == 0)
            {
                printf("No customer\n");
            }
            else
            {
                // process_customer(customers,cur_size);
                // cur_size--;
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
    order_seq(customer,size,customer[size].label);
}

void print_infos(Customer *customer)
{
    printf("Name: %s\n",customer->name);
    printf("The age: %d\n",customer->age);
    printf("The label: %u\n",customer->label);
}


void print_current_seq(Customer customer[MAX_CUSTOMER][MAX_CUSTOMER], int *size, int seq_num)
{
    for (int i = 0; i <= seq_num; i++)
    {
        for (int j = 0; j < size[i]; j++)
        {
            printf("%d-",customer[i][j].label);
        }
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
void order_seq(Customer *customer, int size, int last_label)
{
    Customer temp;
    int num_label = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (customer[i].label > customer[j].label)
            {
                temp = customer[i];
                customer[i] = customer[j];
                customer[j] = temp;
            } 
        }
        if(last_label == customer[i].label)
        {
            num_label++;
        }
    }
    if(last_label == 0 && num_label == 5)
    {
        
    }

}