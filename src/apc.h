/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 27 / 06 / 2026
 *  FILE        : apc.h
 *  PROJECT     : Arbitrary Precision Calculator
 *  DESCRIPTION : Interface definitions. Defines data structures 
 *                and function prototypes for arithmetic operations
 *                on arbitrarily large numbers using Linked Lists.
 * ================================================================ */ 
#ifndef APC_H
#define APC_H

// * Include header files for standard library functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// * Define constants for success and failure
#define SUCCESS 0
#define FAILURE -1

// * Structure for a node in the doubly linked list
typedef struct apc
{
    char data;          // * Single digit of the number
    struct apc *next;   // * Pointer to the next digit
    struct apc *prev;   // * Pointer to the previous digit
} Dlist;

/* --- Utility Functions --- */
void print_usage(void);
void print_header(char *n1, char *op, char *n2);
int validate_operation(char ch);
int validate_number(char *str);

/* --- List Management --- */
int my_atoi(const char *str1, const char *str2, Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2);
int insert_first(Dlist **head, Dlist **tail, char data);
int insert_last(Dlist **head, Dlist **tail, char data);
int dl_delete_list(Dlist **head, Dlist **tail);
void print_list(Dlist *head);
int list_cmp(Dlist *head1, Dlist *head2);

/* --- Core Arithmetic --- */
void apc_add(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
void apc_sub(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
void apc_mul(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
int apc_div(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

#endif  