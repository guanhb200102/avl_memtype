#include "avl_memtype.h"

void updataHeigth_AVLmemtype(AVLmemtype_node* pself){
	int LChild_H, RChild_H;
	
	if(pself->L_ChildNode==NULL)LChild_H=0;
	else LChild_H=pself->L_ChildNode->heigth;
	
	if(pself->R_ChildNode==NULL)RChild_H=0;
	else RChild_H=pself->R_ChildNode->heigth;
	
	if(LChild_H>=RChild_H) pself->heigth=LChild_H+1;
	else pself->heigth=RChild_H+1;
}

void updataBF_AVLmemtype(AVLmemtype_node* pself){
	int LChild_H,RChild_H;
	if(pself->L_ChildNode==NULL)LChild_H=0;
	else LChild_H=pself->L_ChildNode->heigth;
	if(pself->R_ChildNode==NULL)RChild_H=0;
	else RChild_H=pself->R_ChildNode->heigth;
	pself->balance_factor = LChild_H-RChild_H;
}

void RRotation_AVLmemtype(AVLmemtype_node** ppself){
	AVLmemtype_node* LChild=(*ppself)->L_ChildNode;
	(*ppself)->L_ChildNode=LChild->R_ChildNode;
	
	LChild->R_ChildNode=(*ppself);
	(*ppself)=LChild;
	
	updataHeigth_AVLmemtype((*ppself)->R_ChildNode);
	updataBF_AVLmemtype((*ppself)->R_ChildNode);
	updataHeigth_AVLmemtype(*ppself);
	updataBF_AVLmemtype(*ppself);
	
//	printf("RR run\n");
	return ;
}

void LRotation_AVLmemtype(AVLmemtype_node** ppself){
	AVLmemtype_node* RChild=(*ppself)->R_ChildNode;
	(*ppself)->R_ChildNode=RChild->L_ChildNode;
	
	RChild->L_ChildNode=(*ppself);
	(*ppself)=RChild;
	
	updataHeigth_AVLmemtype((*ppself)->L_ChildNode);
	updataBF_AVLmemtype((*ppself)->L_ChildNode);
	updataHeigth_AVLmemtype(*ppself);
	updataBF_AVLmemtype(*ppself);

//	printf("LR run\n");
	return ;
}

//func: BFmaintain_AVLmemtype(AVLmemtype_node** ppself)
//	desc: update the BF of node, and make node's rotation.
//	return:
//		-3: the p of the node is NULL
//		0: work
int BFmaintain_AVLmemtype(AVLmemtype_node** ppself){
	if(*ppself==NULL)return -3;
//	int resultof_recursion=-1;
	updataHeigth_AVLmemtype(*ppself);
	updataBF_AVLmemtype(*ppself);
	
	if((*ppself)->balance_factor>1){
		if((*ppself)->L_ChildNode->balance_factor>=0)
			RRotation_AVLmemtype(ppself);
		else if((*ppself)->L_ChildNode->balance_factor<0){
			LRotation_AVLmemtype(&((*ppself)->L_ChildNode));
			RRotation_AVLmemtype(ppself);
		}
		return 0;
	}
	
	if((*ppself)->balance_factor<-1){
		if((*ppself)->R_ChildNode->balance_factor<=0)
			LRotation_AVLmemtype(ppself);
		else if((*ppself)->R_ChildNode->balance_factor>0){
			RRotation_AVLmemtype(&((*ppself)->R_ChildNode));
			LRotation_AVLmemtype(ppself);
		}
		return 0;
	}
}


//func: insert_AVLmemtype(AVLmemtype_node** ppself, void* psrc_data, int siz)
//return:
//	0: normal
//	-1: value conflied
//	-2: memery fail
int insert_AVLmemtype(AVLmemtype_node** ppself, void* psrc_data, int siz){
	
	if((*ppself)==NULL){
		*ppself=(AVLmemtype_node*)malloc(sizeof(AVLmemtype_node));
		(*ppself)->L_ChildNode=(*ppself)->R_ChildNode=NULL;
		if(*ppself == NULL)return -2;
		(*ppself)->pdata=malloc(siz);
		if((*ppself)->pdata == NULL)return -2;
		(*ppself)->heigth=1;
		(*ppself)->balance_factor=0;
		
		memcpy((*ppself)->pdata, psrc_data, siz);
//		if insert an node to th tree successly, return 0 here.
		return 0; 
	}
	int cmp=memcmp(psrc_data, (*ppself)->pdata, siz);
	int resultof_recursion=-1;
	if(cmp==0) return -1;
	else if(cmp>0)
		resultof_recursion=insert_AVLmemtype(&((*ppself)->R_ChildNode), psrc_data, siz);
	else if(cmp<0)
		resultof_recursion=insert_AVLmemtype(&((*ppself)->L_ChildNode), psrc_data, siz);
	BFmaintain_AVLmemtype(ppself);
	return resultof_recursion;
}


int ReplaceNode_AVLmemtype(AVLmemtype_node** ppself, AVLmemtype_node* TargetNode, int siz){
	int runresult=-1;
	if((*ppself)->L_ChildNode!=NULL){
		runresult=ReplaceNode_AVLmemtype(&((*ppself)->L_ChildNode), TargetNode, siz);	
	}
	else if ((*ppself)->L_ChildNode==NULL){
		AVLmemtype_node* RChild=(*ppself)->R_ChildNode;
		memcpy(TargetNode->pdata, (*ppself)->pdata, siz);
		free((*ppself)->pdata);
		free(*ppself);
		(*ppself)=RChild;
		runresult=0;
	}
	BFmaintain_AVLmemtype(ppself);
	return runresult;
}

int node_delete_AVLmemtype(AVLmemtype_node** ppself, int siz){
	int runresult=-1;
	if((*ppself)->L_ChildNode!=NULL && (*ppself)->R_ChildNode!=NULL ){
//		replace the node:
		ReplaceNode_AVLmemtype( &((*ppself)->R_ChildNode), *ppself, siz); 
		runresult=0;
	}
	else if((*ppself)->L_ChildNode!=NULL && (*ppself)->R_ChildNode==NULL ){
		AVLmemtype_node* LChild=(*ppself)->L_ChildNode;
		free((*ppself)->pdata);
		free(*ppself);
		*ppself=LChild;
		runresult=0;
	}
	else if((*ppself)->L_ChildNode==NULL && (*ppself)->R_ChildNode!=NULL ){
		AVLmemtype_node* RChild=(*ppself)->R_ChildNode;
		free((*ppself)->pdata);
		free(*ppself);
		*ppself=RChild;
		runresult=0;
	}
	else if((*ppself)->L_ChildNode==NULL && (*ppself)->R_ChildNode==NULL ){
		free((*ppself)->pdata);
		free(*ppself);
		*ppself=NULL;
		runresult=0;
	}
	BFmaintain_AVLmemtype(ppself);
	return runresult;
}

//func: delete_AVLmemtype
//return:
//	-1: value not present
//	0: work
int delete_AVLmemtype(AVLmemtype_node** ppself, void* pdata, int siz){
	AVLmemtype_node* search_result= 
		search_AVLmemtype(*ppself, pdata, siz);
	if(search_result == NULL)return -1;
	if(*ppself==NULL)return -1;
	
	int run_result=-1;
	int cmp=memcmp(pdata, (*ppself)->pdata,siz);
	if(cmp>0) 
		run_result=delete_AVLmemtype(&((*ppself)->R_ChildNode), pdata,siz);
	else if(cmp<0) 
		run_result=delete_AVLmemtype(&((*ppself)->L_ChildNode), pdata,siz);
	else if(cmp==0){
		run_result=node_delete_AVLmemtype(ppself, siz);
	}
	BFmaintain_AVLmemtype(ppself);
	return run_result;
}


AVLmemtype_node* search_AVLmemtype(AVLmemtype_node* pself, void* psearch_data, int siz){
	if(pself==NULL)return NULL;
	int cmp=memcmp(psearch_data, pself->pdata, siz);
	if(cmp==0)return pself;
	else if(cmp>0)return search_AVLmemtype(pself->R_ChildNode, psearch_data, siz);
	else if(cmp<0)return search_AVLmemtype(pself->L_ChildNode, psearch_data, siz);
}












