#include<stdio.h>
#include <stdlib.h>
#define MAX_C 50

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

void Add_Customer(Customer customer[MAX_C][MAX_C], int *size, int seq_num);
void print_infos(Customer *customer);
void print_current_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num);
void process_customer(Customer customer[MAX_C][MAX_C], int *size, int temp_seq);
void order_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num);



int main(void)
{
    int size[MAX_C] = {0};
    size[0] = 5;
    size[1] = 4;
    int seq_num = 1;
    // size[2] =
    // {{1,2,3,4,5},{1,2,3,4}}
    //size[2] = {5};
    //seq_num = 0 1
    //seq_num = 0
    //size[seq_num] = 5

    Customer customers[MAX_C][MAX_C] = {
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
        order_seq(customers,size,seq_num);
        print_current_seq(customers,size,seq_num);
        printf("\n");
        printf("1-Add customer\n");
        printf("2-Process customer\n");
        printf("Press 0 to quit\n");
        scanf("%d",&choice);
        if (choice == 1)
        {
            Add_Customer(customers,size,seq_num);
        }
        
        else if (choice == 2)
        {
            int temp_seq = -1;
            for (int i = 0; i <= seq_num; i++)
            {
                if (size[i] != 0)
                {
                    temp_seq = i;
                    break;
                }
            }
            if(temp_seq == -1)
            {
                printf("No customer\n");
            }
            else
            {
                process_customer(customers, size, temp_seq);
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


void Add_Customer(Customer customer[MAX_C][MAX_C], int *size, int seq_num)
{
    int cur_size = size[seq_num];
    size[seq_num]++;
    printf("\nPlease enter the name of the customer:");
    scanf("%s",customer[seq_num][cur_size].name);
    printf("\nPlease enter the age of the customer:");
    scanf(" %d",&customer[seq_num][cur_size].age);
    printf("\nPlease enter the label of the customer:");
    scanf(" %u",&customer[seq_num][cur_size].label);
    //order_seq(customer,size,customer[size].label);
}

void print_infos(Customer *customer)
{
    printf("Name: %s\n",customer->name);
    printf("The age: %d\n",customer->age);
    printf("The label: %u\n",customer->label);
}


void print_current_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num)
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

void process_customer(Customer customer[MAX_C][MAX_C], int *size,int temp_seq)
{
    printf("%s\n",customer[temp_seq][0].name);
    for (int i = 0; i < size[temp_seq]; i++)
    {
        customer[temp_seq][i] = customer[temp_seq][i+1];
    }
    size[temp_seq]--;
}


void order_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num)
{
    Customer temp;

    for ( int k = 0; k <= seq_num; k++)
    {
        for (int i = 0; i < size[k]; i++)
        {
            for (int j = i+1; j < size[k]; j++)
            {
                if (customer[k][i].label > customer[k][j].label)
                {
                    temp = customer[k][i];
                    customer[k][i] = customer[k][j];
                    customer[k][j] = temp;
                } 
            }
        }
    }
}