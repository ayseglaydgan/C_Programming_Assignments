#include<stdio.h>
/* max 50 customer holds at the same time*/
#define MAX_C 50
/*struct definition*/
typedef struct 
{
    char name[20];
    int age;
    int label;
}Customer;
/*Declaration of helper functions*/
/*Adds new  customer*/
void Add_Customer(Customer customer[MAX_C][MAX_C], int *size, int *seq_num, int *max_label);
/*Finds the appropriate sequence for new customer*/
int find_seq(Customer customer[MAX_C][MAX_C], int *size, int *seq_num, int *max_label, int cur_label);
/*prints the current sequence*/
void print_current_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num);
/*Remove function*/
void process_customer(Customer customer[MAX_C][MAX_C], int *size, int temp_seq);
/*Always order the current sequence smallest to bigger*/
void order_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num);

int main(void)
{
    /*Holds the size of every sequence*/
    int size[MAX_C] = {0};
    /*Holds the number of sequence*/
    int seq_num = 0;
    /*Example: seq_num = 0, size[seq_num] = 5
    That means size of the first sequence equals to 5*/

    /*Holds the max number of place for each label for each sequence*/
    int max_labels[5] = {5,3,3,2,2};

    Customer customers[MAX_C][MAX_C];
    while(1)
    {
        int choice,i;
        int temp_seq;
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
            Add_Customer(customers,size,&seq_num,max_labels);
        }
        
        else if (choice == 2)
        {
            temp_seq = -1;
            for (i = 0; i <= seq_num; i++)
            {
                if (size[i] != 0)
                {
                    /*Always removes the customer from the beginnig of the sequence*/
                    temp_seq = i;
                    break;
                }
            }
            /*If the temp_seq still -1, it means no customer*/
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
            return 0;
        }
        else
            printf("INVALID\n");
    }
}


void Add_Customer(Customer customer[MAX_C][MAX_C], int *size, int *seq_num, int *max_label)
{
    /*Define to compare the added label and the sequence*/
    Customer temp;
    int cur_seq;
    int cur_size;
    printf("\nPlease enter the name of the customer:");
    scanf("%s",temp.name);
    printf("\nPlease enter the age of the customer:");
    scanf(" %d",&temp.age);
    printf("\nPlease enter the label of the customer:");
    scanf(" %d",&temp.label);

    if (temp.label != 0 && temp.label != 1 && temp.label != 2 && temp.label != 3 && temp.label != 4 )
    {
        printf("INVALID LABEL\n");
        return;
    }
    /*Decide the sequence to be added*/
    cur_seq = find_seq(customer, size, seq_num, max_label,temp.label);
    cur_size = size[cur_seq];
    /*assign the whole temp struct to customer*/
    customer[cur_seq][cur_size] = temp;
    /*increase the size of sequence which the customer added*/
    size[cur_seq]++;
}

int find_seq(Customer customer[MAX_C][MAX_C], int *size, int *seq_num, int *max_label, int cur_label)
{
    int temp_seq = -1;
    int i,j;
    for (i = 0; i <= *seq_num; i++)
    {
        int count = 0;
        for (j = 0; j < size[i]; j++)
        {
            /*if current label equals to any label in sequence, increase the counter*/
            if (customer[i][j].label == cur_label)
            {
                count++;
            }
        }
        /*increased the counter to check the number of label is max or not*/
        if (max_label[cur_label] != count)
        {
            /*if it is not max, say to add function you can add this sequence*/
            temp_seq = i;
            break;
        }
    }
    /*if temp_seq is still -1, create new sequence*/
    if (temp_seq == -1) 
    {
        *seq_num += 1;
        temp_seq = *seq_num;
    }
    return temp_seq;
}

void print_current_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num)
{
    int i,j;
    for (i = 0; i <= seq_num; i++)
    {
        for (j = 0; j < size[i]; j++)
        {
            printf("%d-",customer[i][j].label);
        }
    }
    printf("\n");
}

void process_customer(Customer customer[MAX_C][MAX_C], int *size,int temp_seq)
{
    int i;
    printf("Proceed customer is %s\n",customer[temp_seq][0].name);
    for (i = 0; i < size[temp_seq]; i++)
    {
        /*shift the sequence to left*/
        customer[temp_seq][i] = customer[temp_seq][i+1];
    }
    /*Decrease the size of sequence after remove*/
    size[temp_seq]--;
}


void order_seq(Customer customer[MAX_C][MAX_C], int *size, int seq_num)
{
    Customer temp;
    int i,j,k;
    /*for each sequence*/
    for (k = 0; k <= seq_num; k++)
    {
        /*linear search/sort algorithm*/
        for (i = 0; i < size[k]; i++)
        {
            for (j = i+1; j < size[k]; j++)
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