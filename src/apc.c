/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 27 / 06 / 2026
 *  FILE        : apc.c
 *  PROJECT     : Arbitrary Precision Calculator
 *  DESCRIPTION : Implementation of the calculator operations.
 *                Contains doubly linked list manipulation, memory 
 *                management, and large number arithmetic logic.
 *
 *  FUNCTION INDEX:
 *    print_usage()         — Displays the usage guide
 *    print_header()        — Displays the CLI output header
 *    validate_operation()  — Validates the arithmetic operator
 *    validate_number()     — Validates the input number string
 *    my_atoi()             — Converts strings to doubly linked lists
 *    insert_first()        — Inserts a node at the head
 *    insert_last()         — Inserts a node at the tail
 *    print_list()          — Displays the linked list digits
 *    dl_delete_list()      — Frees the linked list memory
 *    apc_add()             — Addition of large numbers
 *    list_cmp()            — Compares two linked lists
 *    apc_sub()             — Subtraction of large numbers
 *    apc_mul()             — Multiplication of large numbers
 *    apc_div()             — Division of large numbers
 * ================================================================ */
#include "apc.h"

// * Function to print the usage of the calculator
void print_usage(void)
{
    printf("\033[1;36m=====================================================\033[0m\n");
    printf("\t\033[1;32mUsage\033[0m\t\n");
    printf("\033[1;36m=====================================================\033[0m\n");
    printf("\033[1;32m\t./apc <num1> <operator> <num2>\n");
    printf("\t+ : Addition\n");
    printf("\t- : Subtraction\n");
    printf("\tx : Multiplication\n");
    printf("\t/ : Division\033[0m\n");
    printf("\033[1;36m=====================================================\033[0m\n");
}

// * Function to print the header of the output
void print_header(char *n1, char *op, char *n2)
{
    printf("\033[1;36m=====================================================\033[0m\n");
    printf("\tArbitary Precision Calculator\t\n");
    printf("\033[1;36m=====================================================\033[0m\n");
    printf("Operand 1 : %s\n",n1);
    printf("Operator  : %s\n",op);
    printf("Operand 2 : %s\n",n2);
    printf("\033[1;36m-----------------------------------------------------\033[0m\n");
    printf("\033[1;32mResult\033[0m : ");
}

// * Function to validate the operator
int validate_operation(char ch)
{
    switch(ch)
    {
        case '+':
            return SUCCESS;
        case '-':
            return SUCCESS;
        case 'x':
            return SUCCESS;
        case '/':
            return SUCCESS;
        default:
            return FAILURE;
    }
}

// * Function to validate the number
int validate_number(char *str)
{
    int i = 0;
    // Checking for the sign of the number
    if(str[0] == '-' || str[0] == '+')
        i = 1;
    
    while(str[i])
    {
        if( !(str[i] >= '0' && str[i] <= '9'))
            return FAILURE;
        i++;
    }
    return SUCCESS;
}

// * Function to convert string to doubly linked list
int my_atoi(const char *str1, const char *str2, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2)
{
    int i = 0;
    char data;
    // Checking for the sign of the number
    if(str1[i] == '-' || str1[i] == '+')
        i = 1;

    while(str1[i])
    {
        data = str1[i] - '0';
        insert_last(&(*head1), &(*tail1), data);
        i++;
    }

    int j = 0;
    if(str2[j] == '-' || str2[j] == '+')
        j = 1;

    while(str2[j])
    {
        data = str2[j] - '0';
        insert_last(&(*head2), &(*tail2), data);
        j++;
    }

    return SUCCESS;
}

// * Function to insert a node at the beginning of the list
int insert_first(Dlist **head, Dlist **tail, char data)
{
    Dlist *new_node = (Dlist *) malloc (sizeof(Dlist));

    if(new_node == NULL)
    {
        printf("New node creation Failed!\n");
        return FAILURE;
    }

    new_node -> data = data;
    new_node -> next = NULL;
    new_node -> prev = NULL;

    if(*head == NULL)
    {
        *head = *tail = new_node;
        return SUCCESS;
    }

    if((*head) -> next == NULL)
    {
        (*head) -> prev = new_node;
        new_node -> next = *head;
        *head = new_node;
        return SUCCESS;
    }

    (*head) -> prev = new_node;
    new_node -> next = *head;
    *head = new_node;
    return SUCCESS;
}

// * Function to insert a node at the end of the list
int insert_last(Dlist **head, Dlist **tail, char data)
{
    Dlist *new_node = (Dlist *) malloc(sizeof(Dlist));

    if(new_node == NULL)
    {
        printf("New Node creation Failed!\n");
        return FAILURE;
    }

    new_node -> data = data;
    new_node -> next = NULL;
    new_node -> prev = NULL;

    if(*tail == NULL)
    {
        *head = *tail = new_node;
        return SUCCESS;
    }

    if((*tail) -> prev == NULL)
    {
        new_node -> prev = *tail;
        (*tail) -> next = new_node;
        *tail = new_node;
        return SUCCESS;
    }

    (*tail) -> next = new_node;
    new_node -> prev = *tail;
    *tail = new_node;
    return SUCCESS;
}

// * Function to print the list
void print_list(Dlist *head)
{
    if(head == NULL)
        return;

    while(head != NULL)
    {
        printf("%d",head -> data);
        head = head -> next;
    }
    printf("\n");
    return;
}

// * Function to delete the list
int dl_delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
        return FAILURE;
        
    if((*head) -> next == NULL)
    {
        free(*head);
        *head = *tail = NULL;
        return SUCCESS;
    }
    Dlist *temp = *head;
    while(*head)
    {
        *head = (*head) -> next;
        free(temp);
        temp = *head;
    }
    *head = *tail = NULL;
    return SUCCESS;
}

// * Function to add two numbers
void apc_add(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int data, carry = 0;
    Dlist *tt1 = *tail1, *tt2 = *tail2;
    // Adding the numbers from tail to head
    while(tt1 || tt2)
    {
        // If the first number is greater than the second number
        if(tt1 && tt2 == NULL)
        {
            data = tt1 -> data + carry;
            tt1 = tt1 -> prev;
        }
        // If the second number is greater than the first number
        else if(tt1 == NULL && tt2)
        {
            data = tt2 -> data + carry;
            tt2 = tt2 -> prev;
        }
        // If both numbers are equal
        else
        {
            data = tt1 -> data + tt2 -> data + carry;
            tt1 = tt1 -> prev;
            tt2 = tt2 -> prev;
        }
        // Finding the carry
        carry = data >= 10 ? 1 : 0;
        // Finding the last digit
        data %= 10;
        // Inserting the data into the result list
        insert_first(&(*headR), &(*tailR), data);
    }
    // If the carry is 1
    if(carry)
        insert_first(&(*headR), &(*tailR), carry);

    return;
}

// * Function to compare two numbers
int list_cmp(Dlist *head1, Dlist *head2)
{
    int l1_c = 0, l2_c = 0;
    Dlist *l1 = head1, *l2 = head2;
    
    // Counting the number of digits in both numbers
    while(head1)
    {
        l1_c++;
        head1 = head1 -> next;
    }
    while(head2)
    {
        l2_c++;
        head2 = head2 -> next;
    }
    // Comparing the number of digits
    if(l1_c > l2_c)
        return 1;
    else if(l1_c < l2_c)
        return -1;
    else
    {
        // Comparing the numbers from head to tail
        while(l1)
        {
            // If the first number is greater than the second number
            if(l1 -> data > l2 -> data)
                return 1;
            // If the second number is greater than the first number
            else if(l1 -> data < l2 -> data)
                return -1;
            l1 = l1 -> next;
            l2 = l2 -> next;
        }
        // If both numbers are equal
        return 0;
    }
}

// * Function to subtract two numbers
void apc_sub(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int val1, val2, borrow = 0;
    char data;
    Dlist *tt1 = *tail1, *tt2 = *tail2;
    // Subtracting the numbers from tail to head
    while(tt1)
    {
        // Subtracting the borrow from the first number
        val1 = tt1 -> data - borrow;
        // Getting the second number
        val2 = (tt2 != NULL) ? tt2 -> data : 0;

        // Checking if the first number is smaller than the second number
        if(val1 < val2)
        {
            // Adding 10 to the first number
            data = val1 + 10 - val2;
            // Setting the borrow to 1
            borrow = 1;
        }
        // If the first number is greater than the second number
        else
        {
            // Subtracting the second number from the first number
            data = val1 - val2;
            // Setting the borrow to 0
            borrow = 0;
        }
        // Moving to the next node and verify if tt2 is not NULL
        if(tt2)
            tt2 = tt2 -> prev;
        tt1 = tt1 -> prev;
        // Inserting the data into the result list
        insert_first(&(*headR),&(*tailR), data);
    }
    // Removing leading zeros
    Dlist *temp = *headR;
    while(temp != NULL && temp -> data == 0 && temp -> next != NULL)
    {
        *headR = temp -> next;
        (*headR) -> prev = NULL;
        free(temp);
        temp = *headR;
    }
    return;
}

// * Function to multiply two numbers
void apc_mul(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // Initializing the pointers for the result list
    Dlist *acc_head = NULL, *acc_tail = NULL;
    Dlist *res_head = NULL, *res_tail = NULL;
    Dlist *temp_head , *temp_tail;
    
    // Declaring the variables
    int count = 0;
    char mul = 0, sum = 0, carry;
    Dlist *t1, *t2 = *tail2;
    
    // Multiplying the numbers from tail to head
    while(t2)
    {
        // Initializing the carry
        carry = 0;
        t1 = *tail1;
        temp_head = NULL;
        temp_tail = NULL;
        // Adding leading zeros based on the position of the digit
        for(int i = 0; i < count; i++)
        {
            insert_first(&temp_head, &temp_tail, 0);
        }
        // Multiplying the numbers from tail to head
        while(t1)
        {
            mul = t1 -> data * t2 -> data + carry;
            sum = mul >= 10 ? (mul % 10) : mul;
            carry = mul >= 10 ? (mul / 10) : 0;
            insert_first(&temp_head, &temp_tail, sum);
            t1 = t1 -> prev;
        }
        if(carry)
            insert_first(&temp_head, &temp_tail, carry);
        // Adding the result to the accumulator
        if(acc_head == NULL)
        {
            acc_head = temp_head;
            acc_tail = temp_tail;
        }
        else
        {
            // Adding the result to the accumulator
            apc_add(&acc_tail, &temp_tail, &res_head, &res_tail);
            dl_delete_list(&acc_head, &acc_tail);
            dl_delete_list(&temp_head, &temp_tail);
            acc_head = res_head;
            acc_tail = res_tail;
            res_head = res_tail = NULL;
        }
        count++;
        t2 = t2 -> prev;
    }
    // Assigning the result to the result list
    *headR = acc_head;
    *tailR = acc_tail;
    return;
}

// * Function to divide two numbers
int apc_div(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // Checking if the divisor is zero
    if(*head2 == *tail2 && (*head2) -> data == 0)
        return 0;
    // Checking if the dividend is smaller than the divisor
    if(list_cmp(*head1, *head2) == -1)
        return 0;
    
    int count = 0;
    // Making a copy of the dividend
    Dlist *cur_head = *head1, *cur_tail = *tail1;
    Dlist *next_head = NULL, *next_tail = NULL;
    // Subtracting the divisor from the dividend until the dividend becomes smaller than the divisor
    while(list_cmp(cur_head, *head2) != -1)
    {
        // Subtracting the divisor from the current dividend
        apc_sub(&cur_tail, tail2, &next_head, &next_tail);
        // Incrementing the quotient count
        count++;
        // Deleting the current dividend if it is not the original dividend
        if(cur_head != *head1)
            dl_delete_list(&cur_head, &cur_tail);
        
        // Making the next dividend as the current dividend
        cur_head = next_head;
        cur_tail = next_tail;
        next_head = next_tail = NULL;
    }
    // Deleting the current dividend if it is not the original dividend
    if(cur_head != *head1)
        dl_delete_list(&cur_head, &cur_tail);
    
    return count;   // Returning the quotient count
}