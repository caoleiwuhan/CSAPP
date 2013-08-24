/*
 * CS:APP Binary Bomb
 *
 * Copyright (c) 2002, R. Bryant and D. O'Hallaron, All rights reserved.
 * May not be used, modified, or copied without permission.
 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phases.h"
#include "support.h"

/* Global bomb ID */
int bomb_id = 2;

/* Global lab ID */
char lab_id[1024] = "csapp2007";

/* 
 * phase1b.c - The user's input must match the specified string 
 */
void phase_1(char *input)
{
#if defined(PROBLEM)
    if (strings_not_equal(input, "When I get angry, Mr. Bigglesworth gets upset.") != 0)
	explode_bomb();
#elif defined(SOLUTION)
    printf("When I get angry, Mr. Bigglesworth gets upset.\n");
#else
    invalid_phase("1b");
#endif
}

/* 
 * phase2b.c - To defeat this stage the user must enter arithmetic 
 * sequence of length 6 and delta = 5. 
 */
void phase_2(char *input)
{
#if defined(PROBLEM)
    int ii;
    int numbers[6];
    
    read_six_numbers(input, numbers);
    
    for(ii = 1; ii < 6; ii++) {
	if (numbers[ii] != numbers[ii-1] + 5)
	    explode_bomb();
    }
#elif defined(SOLUTION)
    printf("1 6 11 16 21 26\n");
#else
    invalid_phase("2b");
#endif
}
/* 
 * phase3c.c - A long switch statement that the compiler should implement
 * with a jump table. The user has to enter both an index into the table
 * and the character stored at that position in the table as well
 * as a number to be compared. 
 */
void phase_3(char *input) 
{
#if defined(PROBLEM)
    int index, num, numScanned = 0;
    char x, letter;
  
    numScanned = sscanf(input, "%d %c %d", &index, &letter, &num);
  
    if (numScanned < 3) {
	explode_bomb();
    }

    switch(index) {
    case 0:
	x = 't';
	if(num != 830) {
	    explode_bomb();
	}
	break;
    case 1:
	x = 'z';
	if(num != 836) {
	    explode_bomb();
	}
	break;
    case 2:
	x = 'h';
	if(num != 379) {
	    explode_bomb();
	}
	break;
    case 3:
	x = 'y';
	if(num != 837) {
	    explode_bomb();
	}
	break;
    case 4:
	x = 'z';
	if(num != 441) {
	    explode_bomb();
	}
	break;
    case 5:
	x = 'c';
	if(num != 784) {
	    explode_bomb();
	}
	break;
    case 6:
	x = 'p';
	if(num != 853) {
	    explode_bomb();
	}
	break;
    case 7:
	x = 'i';
	if(num != 540) {
	    explode_bomb();
	}
	break;
    default:
	x = 'q'; /* keep gcc happy */
	explode_bomb();
    }
  
    if (x != letter) {
	explode_bomb();
    }
#elif defined(SOLUTION)
    printf("4 z 441\n");
#else
    invalid_phase("3c");
#endif
}

/* 
 * phase4c.c - A recursive function to sort out.  
 * Computes the factorial number of their input, must match the factorial
 * number randomly generated. 
*/
#if defined(PROBLEM)
int func4(int i) {
    if (i <= 1) {
	return 1;
    }
    return i * func4(i - 1);
}
#elif defined(SOLUTION)
/* given y=x!, return x */
int func4_inverse(int y) {
    switch (y) {
    case 24: return 4;
    case 120: return 5;
    case 720: return 6;
    case 5040: return 7;
    case 40320: return 8;
    case 362880: return 9;
    case 3628800: return 10;
    default:
	fprintf(stderr, "ERROR: bad input in phase4c\n");
	exit(8);
    }
}
#endif

void phase_4(char *input) {
#if defined(PROBLEM)
    int result, val, numScanned = sscanf(input, "%d", &val);

    if((numScanned != 1) || (val < 1)) {
	explode_bomb();
    }

    result = func4(val);

    if(result != 120) {
	explode_bomb();
    }
#elif defined(SOLUTION)
    printf("%d %s\n", func4_inverse(120), SECRET_PHRASE);
#else
    invalid_phase("4c");
#endif
}
/* 
 * phase5a.c - Just to be hairy, this traverses a loop of pointers and 
 * counts its length.  The input determines where in the loop we begin. 
 * Just to make sure the user isn't guessing, we make them input the sum of
 * the pointers encountered along the path, too.
 */
void phase_5(char *input)
{
#if defined(PROBLEM)
    static int array[] = {
      10,
      2,
      14,
      7,
      8,
      12,
      15,
      11,
      0,
      4,
      1,
      13,
      3,
      9,
      6,
      5
    };

    int count, sum;
    int start;
    int p, result;
    int numScanned;

    numScanned = sscanf(input, "%d %d", &p, &result);
    
    if (numScanned < 2)
      explode_bomb();

    p = p & 0x0f;
    start = p; /* debug */

    count = 0;
    sum = 0;
    while(p != 15) {
	count++;
	p = array[p];
	sum += p;
    }

    if ((count != 11) || (sum != result))
	explode_bomb();
#elif defined(SOLUTION)
    switch (11) {
    case 1: printf("6 15"); break;
    case 2: printf("14 21"); break;
    case 3: printf("2 35"); break;
    case 4: printf("1 37"); break;
    case 5: printf("10 38"); break;
    case 6: printf("0 48"); break;
    case 7: printf("8 48"); break;
    case 8: printf("4 56"); break;
    case 9: printf("9 60"); break;
    case 10: printf("13 69"); break;
    case 11: printf("11 82"); break;
    case 12: printf("7 93"); break;
    case 13: printf("3 100"); break;
    case 14: printf("12 103"); break;
    case 15: printf("5 115"); break;
    default:
	printf("ERROR: bad count value in phase5a\n");
	exit(8);
    }
    printf("\n");
#else
    invalid_phase("5a");
#endif
}

/* 
 * phase6b.c - The user has to enter the node numbers (from 1 to 6) in 
 * the order that they will occur when the list is sorted.
 */
listNode node6 = {254, 6, NULL};
listNode node5 = {90, 5, &node6};
listNode node4 = {932, 4, &node5};
listNode node3 = {274, 3, &node4};
listNode node2 = {966, 2, &node3};
listNode node1 = {951, 1, &node2};

#if defined(SOLUTION)
/* Sort list */
listNode *fun6(listNode *start)
{
    listNode *head = start;
    listNode *p, *q, *r;

    head = start;
    p = start->next;
    head->next = NULL;

    while (p != NULL) {
	r = head;
	q = head;

	while ((r != NULL) && (r->value > p->value)) {
	    q = r;
	    r = r->next;
	}

	if (q != r)
	    q->next = p;
	else
	    head = p;

	q = p->next;
	p->next = r;

	p = q;
    }

    return head;
}
#endif

void phase_6(char *input)
{
#if defined(PROBLEM)
    listNode *start = &node1;
    listNode *p;
    int indices[6];
    listNode *pointers[6];
    int i, j;

    read_six_numbers(input, indices);

    /* Check the range of the indices and whether or not any repeat */
    for (i = 0; i < 6; i++) {
	if ((indices[i] < 1) || (indices[i] > 6))
	    explode_bomb();
	
	for (j = i + 1; j < 6; j++) {
	    if (indices[i] == indices[j])
		explode_bomb();
	}
    }

    /* Rearrange the list according to the user input */
    for (i = 0; i < 6; i++) {
	p = start;
	for (j = 1; j < indices[i]; j++)
	    p = p -> next;
	pointers[i] = p;
    }

    start = pointers[0];
    p = start;

    for (i = 1; i < 6; i++) {
	p->next = pointers[i];
	p = p->next;
    }
    p->next = NULL;

    /* Now see if the list is sorted */
    p = start;
    for (i = 0; i < 5; i++) {
	if (p->value < p->next->value)
	    explode_bomb();
	
	p = p->next;
    }
#elif defined(SOLUTION)
    listNode *start = &node1;
    listNode *p;

    /* sort */
    start = fun6(start);

    /* emit the node indices of the sorted list */
    p = start;
    while (p) {
	printf("%d ", p->index);
	p = p->next;
    }
    printf("\n");
#else
    invalid_phase("6b");
#endif
}



/* 
 * phase7.c - The infamous secret stage! 
 * The user has to find leaf value given path in a binary tree.
 */

typedef struct treeNodeStruct
{
    int value;
    struct treeNodeStruct *left, *right;
} treeNode;

/* balanced binary tree containing randomly chosen values */
treeNode n48 = {1001, NULL, NULL};
treeNode n46 = {47, NULL, NULL};
treeNode n43 = {20, NULL, NULL};
treeNode n42 = {7, NULL, NULL};
treeNode n44 = {35, NULL, NULL};
treeNode n47 = {99, NULL, NULL};
treeNode n41 = {1, NULL, NULL};
treeNode n45 = {40, NULL, NULL};
treeNode n34 = {107, &n47, &n48};
treeNode n31 = {6, &n41, &n42};
treeNode n33 = {45, &n45, &n46};
treeNode n32 = {22, &n43, &n44};
treeNode n22 = {50, &n33, &n34};
treeNode n21 = {8, &n31, &n32};
treeNode n1 = {36, &n21, &n22};

/* 
 * Searches for a node in a binary tree and returns path value.
 * 0 bit denotes left branch, 1 bit denotes right branch
 * Example: the path to leaf value "35" is left, then right,
 * then right, and thus the path value is 110(base 2) = 6.
 */

int fun7(treeNode* node, int val)
{
    if (node == NULL) 
	return -1;
  
    if (val < node->value) 
	return fun7(node->left, val) << 1;
    else if (val == node->value) 
	return 0;
    else 
	return (fun7(node->right, val) << 1) + 1;
}
     
void secret_phase()
{

#if defined(PROBLEM)
    char *input = read_line();
    int target = atoi(input);
    int path;

    /* Make sure target is in the right range */
    if ((target < 1) || (target > 1001))
	explode_bomb();

    /* Determine the path to the given target */
    path = fun7(&n1, target);

    /* Compare the retrieved path to a random path */
    if (path != 4)
	explode_bomb();
  
    printf("Wow! You've defused the secret stage!\n");

    phase_defused();
#elif defined(SOLUTION)
    int path = 4;
    treeNode *node = &n1;
    
    node = (path    & 0x1) ? node->right : node->left;
    node = (path>>1 & 0x1) ? node->right : node->left;
    node = (path>>2 & 0x1) ? node->right : node->left;
    printf("%d\n", node->value);
#else
    invalid_phase("7");
#endif
}


