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

//func: insert_AVLmemtype(AVLmemtype_node** ppself, void* psrc_data, int siz)
//return:
//	0: normal
//	-1: value conflied
//	-2: memery fail
int insert_AVLmemtype(AVLmemtype_node**, void*, int siz);

//func: delete_AVLmemtype
//return:
//	-1: value not present
//	0: work
int delete_AVLmemtype(AVLmemtype_node**, void*, int siz);

//func: search_AVLmemtype
//return:
//	0: cant found
//	!0: work
AVLmemtype_node* search_AVLmemtype(AVLmemtype_node*, void*, int siz);


//private func:
//	avl_memtype.c
/* */
#endif
