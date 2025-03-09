#ifndef AVL_MEMTYPE_H
#define AVL_MEMTYPE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLmemtype_node {
    void* pdata;
    int heigth;
    int balance_factor;
    struct AVLmemtype_node* L_ChildNode;
    struct AVLmemtype_node* R_ChildNode;
} AVLmemtype_node;

//user api fun:
int insert_AVLmemtype(AVLmemtype_node**, void*, int siz);
int delete_AVLmemtype(AVLmemtype_node**, void*, int siz);
AVLmemtype_node* search_AVLmemtype(AVLmemtype_node*, void*, int siz);


//private func:
//	avl_memtype.c
/* */
#endif
