/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 27 / 06 / 2026
 *  FILE        : main.c
 *  PROJECT     : Arbitrary Precision Calculator
 *  DESCRIPTION : Main execution entry point. Handles Command Line 
 *                Arguments parsing, input validation, sign routing, 
 *                and orchestration of core arithmetic functions.
 * ================================================================ */
#include "apc.h"

int main(int argc, char *argv[])
{
    // Checking for valid number of arguments
    if(argc != 4)
    {
        printf("\033[1;31m=====================================================\n");
        printf("\tERROR : Please Enter Valid No. of Inputs.\n");
        printf("\033[1;31m=====================================================\033[0m\n");
        print_usage();
        return FAILURE;
    }
    
    // Checking for valid operator
    char len = strlen(argv[2]);
    if((len != 1) || (validate_operation(argv[2][0]) == FAILURE))
    {
        printf("\033[1;31m=====================================================\n");
        printf("\tERROR : Please Enter Valid Operation.\n");
        printf("\033[1;31m=====================================================\033[0m\n");
        printf("\n");
        print_usage();
        return FAILURE;
    }

    // Checking the sign of the input numbers
    char sign1 = (argv[1][0] == '-') ? -1 : 1;
    char sign2 = (argv[3][0] == '-') ? -1 : 1;
    char big;

    // Checking for valid numbers without any alphabets or special characters other than +/- at the beginning
    if(validate_number(argv[1]) == FAILURE || validate_number(argv[3]) == FAILURE)
    {
        printf("\033[1;31m=====================================================\n");
        printf("\tERROR : Please Enter Valid Number.\n");
        printf("\033[1;31m=====================================================\033[0m\n");
        printf("\n");
        print_usage();
        return FAILURE;
    }

    // Declaring head and tail pointers for the input and result linked lists
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    // Converting the input numbers into doubly linked list
    my_atoi(argv[1],argv[3],&head1,&tail1, &head2, &tail2);

    // Printing the header and the input numbers
    print_header(argv[1],argv[2],argv[3]);
    
    int count = 0;
    // Performing the operation based on the operator
    switch(argv[2][0])
    {
        case '+':
            // If both numbers have same sign
            if(sign1 == sign2)
            {
                apc_add(&tail1, &tail2, &headR, &tailR);
                // Printing the negative sign if the numbers are negative
                if(sign1 == -1)
                    printf("-");
            }
            // If the numbers have different signs
            else
            {
                // Checking which number is greater if 1 then num1 is greater
                // and if -1 then num2 is greater
                big = list_cmp(head1, head2);
                if(big == 1)
                {
                    apc_sub(&tail1, &tail2, &headR, &tailR);
                    if(sign1 == -1)
                        printf("-");
                }
                else if(big == -1)  // Number 2 is greater
                {
                    apc_sub(&tail2, &tail1, &headR, &tailR);
                    if(sign2 == -1)
                        printf("-");
                }
                else
                {
                    printf("0\n");  // Both numbers are equal
                    break;
                }
            }
            print_list(headR);
        break;
        
        case '-':
            // If both numbers have same sign
            if(sign1 == sign2)
            {
                big = list_cmp(head1, head2);
                // Checking which number is greater if 1 then num1 is greater
                // and if -1 then num2 is greater
                if(big == 1)
                {
                    apc_sub(&tail1, &tail2, &headR, &tailR);
                    if(sign1 == -1)
                        printf("-");
                }
                else if(big == -1)  // Number 2 is greater
                {
                    apc_sub(&tail2, &tail1, &headR, &tailR);
                    if(sign1 == 1)
                        printf("-");
                }
                else
                {
                    printf("0\n");  // Both numbers are equal
                    break;
                }
            }
            // If the numbers have different signs
            else
            {
                apc_add(&tail1, &tail2, &headR, &tailR);
                if(sign1 == -1)
                    printf("-");
            }
            print_list(headR);
        break;
        
        case 'x':   // Multiplication
            apc_mul(&tail1, &tail2, &headR, &tailR);
            // Checking if the result is negative
            if(sign1 != sign2)
            {
                if(headR -> data != 0)
                    printf("-");
            }
            print_list(headR);
        break;

        case '/':
            count = apc_div(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            // Checking if the result is negative
            if(sign1 != sign2)
            {
                if(count != 0)
                    printf("-");
            }
            printf("%d\n",count);
        break;
    }
    printf("\033[1;36m=====================================================\033[0m\n");
    
    // Freeing the memory
    dl_delete_list(&head1, &tail1);
    dl_delete_list(&head2, &tail2);
    dl_delete_list(&headR, &tailR);
    
    return 0;
}