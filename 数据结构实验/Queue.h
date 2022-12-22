/***************************************************************************************
 *	File Name				:	Queue.h
 *	CopyRight				:	2022  lwd 
 *	SYSTEM					:   win10
 *	Create Data				:	2022.11.15
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/ 
#include <stdio.h>
#include <stdlib.h>


/**************************************************************
*	Macro Define Section
**************************************************************/
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef int Status;
/**************************************************************
*	Struct Define Section 
**************************************************************/
typedef struct{
	ElemType *elem;
	int front;
	int rear;
	int maxsize;
}Queue;


/**
 *  @name        : Status InitQueue(Queue &q,int size)
 *	@description : init queue
 *	@param		 : Q,size
 *	@return		 : OK
 *  @notice      : None
 */
Status InitQueue(Queue &Q,int size){
	if(size < 0)return ERROR;
	Q.elem = (ElemType *)malloc(size*sizeof(ElemType));
	if(NULL == Q.elem)return OVERFLOW;
	Q.front = Q.rear = 0;
	Q.maxsize = size;
	return OK;
}

/**
 *  @name        : Status IsEmpty(Queue Q)
 *	@description : judge whether the queue is empty
 *	@param		 : Q
 *	@return		 : OK
 *  @notice      : None
 */
Status IsEmpty(Queue Q){
	if(Q.rear == Q.front)return TRUE;
	return FALSE; 
}



/**
 *  @name        : Status DeQueue(Queue &q,ElemType &e)
 *	@description : DEQUEUE
 *	@param		 : Q,e
 *	@return		 : OK
 *  @notice      : None
 */
Status DeQueue(Queue &Q,ElemType &e){
	if(Q.front == Q.rear)return ERROR;
	e = Q.elem[Q.front];
	Q.front = (Q.front + 1)%(Q.maxsize);
	return OK;
}


/**
 *  @name        : Status DeQueue(Queue &q,ElemType &e)
 *	@description : EnQueue
 *	@param		 : Q,e
 *	@return		 : OK
 *  @notice      : None
 */

Status EnQueue(Queue &Q,ElemType e){
	if((Q.rear + 1)%Q.maxsize == Q.rear)return ERROR;
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear+1)%Q.maxsize;
	return OK;
}
