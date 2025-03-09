
#include <string.h>
//#include "avltree_voidtype.h" 
#include "avl_memtype.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void intnodeshow(AVLmemtype_node* tree, int search){
	
	AVLmemtype_node* found = search_AVLmemtype(tree, &search, sizeof(int));
	if(found == NULL) printf("NULL of %d\n", search);
	else printf("value: %d, hei: %d, bal: %d, add: %d, l_add: %d, r_add: %d\n",
			*(int*)found->pdata, found->heigth, found->balance_factor, found, found->L_ChildNode, found->R_ChildNode );
}


int main(int argc, char *argv[]) {
	
	AVLmemtype_node* tree = NULL;
	
	int i;
	int siz=sizeof(int); 
	int deleteerr;
	
	int j=200;
	while(j<20240){
		insert_AVLmemtype(&tree, &j, siz);
		j++;
	}
	intnodeshow(tree, *(int*)(tree->pdata));
//	while(1){
//		i=0;
//		printf("flag\n");
//		while(i<409600){
//			insert_AVLmemtype(&tree, &i, siz);
//			i++;
//		}
//		intnodeshow(tree, *(int*)(tree->pdata));
//		
//		i=1;
//		while(i<409600){
//			delete_AVLmemtype(&tree, &i, siz);
//				
//			i++;
//		}
//		intnodeshow(tree, *(int*)(tree->pdata));
//		sleep(1);
//	}
	
	
//	AVLmemtype_node* fres=NULL;
//	i=2000;
//	while(i<4096){
//		fres=search_AVLmemtype(tree, &i, siz);
//		if(fres==NULL)printf("ERR\n");
//		i++;
//	}
	
	printf("end-------------------\n");
	
}
