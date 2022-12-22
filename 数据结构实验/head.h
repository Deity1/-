/***************************************************************************************
 *	File Name				:	head.h
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
#include "./Queue.h"

/**************************************************************
*	Macro Define Section
**************************************************************/
#define UNVISITED 0
#define VISITED 1
#define INFINITY MAXINT

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW 0
#define SUCCESS 1	
#define SIZE 20

/**************************************************************
*	Struct Define Section 
**************************************************************/

typedef enum{
	DG,DN
}GraphKind;

typedef char VexType;
typedef int Status; 


/* 邻接数组的存储结构类型 */
typedef struct{
	VexType *vexs;  // 顶点数组，默认为char类型
	int **arcs;   // 关系数组
	int n,e;   // 顶点数和边数
	int *tags;  // 标志数组，可以用于在图的遍历中标记访问与否 
}MGraph;

typedef struct{
	VexType v,w;  // 边（弧）的端点
	int info; 
}ArcInfo;



/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : int LocateVex_UDG(MGraph G,VexType v)
 *	@description : find the vex's locations
 *	@param		 : MGraph G , VexType v
 *	@return		 : loc
 *  @notice      : None
 */
 int LocateVex_UDG(MGraph G,VexType v){
 	int loc;
 	for(loc = 0;loc<G.n;loc++)
 		if(v == G.vexs[loc])return loc;
 	return ERROR;
 }


/**
 *  @name        : Status InitGraph_UDG(MGraph &G,GraphKind kind,VexType *vexs,int n);
 *	@description : initialize an empty graph with only the head node
 *	@param		 : G,kind,vexs,n
 *	@return		 : OK
 *  @notice      : None
 */

Status InitGraph_UDG(MGraph &G,VexType *vexs,int n){
 	int i,j,info;
 	if(n<0 || (n>0 && NULL == vexs)) return ERROR;
 	// 因为初始化的是无向图
	info = 0;
	G.n = n;
	G.e = 0;
	if( 0 == n)return OK; // 空图
	if(NULL == (G.vexs = (VexType*)malloc(n*sizeof(VexType))))
		return OVERFLOW; 
 	for(i=0;i<n;i++)G.vexs[i] = vexs[i]; // 对顶点数组进行赋值
	if(NULL == (G.arcs = (int **)malloc(n*sizeof(int *))))
		return OVERFLOW;
	for(i = 0;i<n;i++){
		if(NULL == (G.arcs[i] = (int *)malloc(n*sizeof(n))))
			return OVERFLOW;
		}
 	if(NULL == (G.tags = (int *)malloc(n*sizeof(int))))return OVERFLOW;
 	for(i=0;i<n;i++){
 		G.tags[i] = UNVISITED;
 		for(j=0;j<n;j++)
		   G.arcs[i][j] = info;
	 }
	return OK; 
}

/**
 *  @name        : Status CreateGraph_UDG(MGraph &G,VexType *vexs,int n,ArcInfo *arcs,int e)
 *	@description : initialize an empty graph with only the head node
 *	@param		 : G,kind,vexs,n
 *	@return		 : OK
 *  @notice      : None
 */


Status CreateGraph_UDG(MGraph &G,VexType *vexs,int n,ArcInfo *arcs,int e){
	int i,j,k;
	VexType v,w;
	if(InitGraph_UDG(G,vexs,n)!=OK)return ERROR;
	G.e = e;
	for(k = 0;k<e;k++){
		v = arcs[k].v;w=arcs[k].w;  // 读入边的信息
		i = LocateVex_UDG(G,v);
		j = LocateVex_UDG(G,w);  // 确定位序
		
		if(i<0 || j<0)return ERROR;
		G.arcs[i][j] = G.arcs[j][i] = 1; // 赋值为1 
	}
	return OK;
}

/**
 *  @name        : Status GetVex_UDG(MGraph G,int k, VexType &w)
 *	@description : get the value of vex k to w
 *	@param		 : G,k,w
 *	@return		 : OK
 *  @notice      : None
 */
 
Status GetVex_UDG(MGraph G,int k, VexType &w){
	if(k<0 || k>G.n)return ERROR;
	w = G.vexs[k];
	return OK;
}

/**
 *  @name        : Status PutVex_UDG(MGraph G,int k,VexType v)
 *	@description : change the value of vex k with w
 *	@param		 : G,k,w
 *	@return		 : OK
 *  @notice      : None
 */
Status PutVex_UDG(MGraph G,int k,VexType w){
	if(k<0 || k>G.n)return ERROR;
	int i;
	//  如果该顶点已经存在的情况 
	for(i = 0;i<G.n;i++){
		if(G.vexs[i] == w)return ERROR;
	}
	G.vexs[k] = w;
	return OK;
}  



/**
 *  @name        : int FirstAdjVex_UDG(MGraph G,int k)
 *	@description : found the first adj vex 
 *	@param		 : G,k
 *	@return		 : loc
 *  @notice      : None
 */

int FirstAdjVex_UDG(MGraph G,int k){
	if(k<0 || k>G.n)return ERROR;
	int loc;
	for(loc=0;loc < G.n;loc++){
		if(G.arcs[k][loc] == 1)return loc;
	}
	return ERROR;
}


/**
 *  @name        : int NextAdjVex_UDG(MGraph G,int k,int m)
 *	@description : found the k to the m location
 *	@param		 : G,k,m
 *	@return		 : loc
 *  @notice      : None
 */
int NextAdjVex_UDG(MGraph G,int k,int m){
	if( k<0 || m>0 || k>G.n || m>G.n)return ERROR;
	if(G.n < 1)return 0;
	int loc = m+1;
	for(;loc < G.n;loc++){
		if(G.arcs[k][loc] == 1)return loc;
	}
	return ERROR;
} 

/**
 *  @name        : Status AddArc_UDG(MGraph &G,int k,int m)
 *	@description : add arcs between the k & m vexs
 *	@param		 : G,k,m
 *	@return		 : OK
 *  @notice      : None
 */
Status AddArc_UDG(MGraph &G,int k,int m){
	if(k<0 || k>G.n || m<0 || m>G.n)return ERROR;
	int i=k,j=m;
	if(G.arcs[i][j] == 1 || G.arcs[j][i] == 1){
		printf("该图已存在这条边\n");
		return ERROR;
	}
	G.arcs[i][j] = G.arcs[j][i] = 1;
	G.e++;
	return OK;   
}

/**
 *  @name        : Status RemoveArc_UDG(MGraph &G,int k,int m)
 *	@description : remove arcs between the k & m vexs
 *	@param		 : G,k,m
 *	@return		 : OK
 *  @notice      : None
 */
Status RemoveArc_UDG(MGraph &G,int k,int m){
	if(k<0 || k>G.n || m<0 || m>G.n)return ERROR;
	int i = k,j = m;
	if(G.arcs[i][j] == 0 || G.arcs[j][i] == 0){
		printf("该图不存在这条边\n");
		return ERROR;
	}
	G.arcs[i][j] = G.arcs[j][i] = 0;
	G.e--;
	return OK; 
}

/**
 *  @name        : Status print(VexType top)
 *	@description : print the value
 *	@param		 : value
 *	@return		 : OK
 *  @notice      : None
 */
 
Status visit(VexType top){
	if(top == '\0')return ERROR;
	printf("%c",top);
	return OK;
}
 

/**
 *  @name        : Status DFSTraverse_UDG(MGraph,Status(*visit)(VexType))
 *	@description : DFS search
 *	@param		 : G,visit function
 *	@return		 : OK
 *  @notice      : None
 */
Status DFS_UDG(MGraph G,int k,Status(*visit)(VexType)){
	 // 从第k个顶点出发进行深度搜索
	 int i;
	 if(k>=G.n || k<0)return ERROR;
	 if(ERROR == visit(G.vexs[k]))return ERROR;
	 G.tags[k] = VISITED; 
	 for(i = FirstAdjVex_UDG(G,k);i!=ERROR;i=NextAdjVex_UDG(G,k,i)){
	 	if(UNVISITED == G.tags[i])
	 		if(ERROR == DFS_UDG(G,i,visit))return ERROR;
	 }
	 return OK;
}



/**
 *  @name        : Status DFSTraverse_UDG(MGraph G,Status(*visit)(VexType))
 *	@description : DFS search
 *	@param		 : G,visit function
 *	@return		 : OK
 *  @notice      : None
 */

Status DFSTraverse_UDG(MGraph G,Status(*visit)(VexType)){
	// 深度优先遍历
	int i;
	for(i=0;i<G.n;i++)G.tags[i] = UNVISITED;
	for(i=0;i<G.n;i++)
		if(G.tags[i] == UNVISITED)
			if(ERROR == DFS_UDG(G,i,visit))return ERROR;
	return OK; 
}



/**
 *  @name        : Status BFSTraverse_UDG(MGrapg G,Status(*visit)(VexType))
 *	@description : BFS search
 *	@param		 : G,visit function
 *	@return		 : OK
 *  @notice      : None
 */
Status BFSTraverse_UDG(MGraph G,Status(*visit)(VexType)){
	int i,j,loc;
   	int e;
	int n=G.n;
	Queue Q;
	InitQueue(Q,SIZE);
	for(i=0;i<n;i++)G.tags[i] =UNVISITED;
	for(i=0;i<n;i++)
	{
		if(G.tags[i] == UNVISITED)
		{
			if(ERROR == visit(G.vexs[i]))
				return ERROR;
			G.tags[i] = VISITED;
			EnQueue(Q,i);
			while(FALSE == IsEmpty(Q))
			{
				loc = Q.front;
				DeQueue(Q,e);
				for(j=FirstAdjVex_UDG(G,loc);j!=ERROR;j=NextAdjVex_UDG(G,loc,j))
				{
					if(G.tags[j] == UNVISITED)
					{
						if(ERROR == visit(G.vexs[j]))
							return ERROR;
						G.tags[j] = VISITED;;
						EnQueue(Q,j);
					}
				}
					
			}
		}
	}
	return OK;
}


/**
 *  @name        : Status DestroyGraph_UDG(MGraph &G)
 *	@description : destroy the graph
 *	@param		 : G
 *	@return		 : OK
 *  @notice      : None
 */
Status DestroyGraph_UDG(MGraph &G){
	G.e = 0;
	G.n = 0;
	free(G.vexs);
	G.vexs = NULL;
	free(G.tags);
	G.tags = NULL;
	// 释放边的空间
	int i;
	for(i=0;i<G.n;i++)
		free(G.arcs[i]);
	free(G.arcs);
	G.arcs = NULL;
	return OK; 
} 

/**
 *  @name        : Status print_Graph(G)
 *	@description : printf the Graph
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */

Status print_Graph(MGraph G){
	if(0 == G.n)return ERROR;
	G.arcs[0][0] = 0;
	int i,j;
	printf("  ");
	for(i=0;i<G.n;i++)
		printf("%c",G.vexs[i]);
	printf("\n");
	for(i=0;i<G.n;i++){
		printf("%c ",G.vexs[i]);
		for(j=0;j<G.n;j++)
			printf("%d",G.arcs[i][j]);
		printf("\n");
	}
}


/**
 *  @name        : Status test()
 *	@description : test the function
 *	@param		 : None
 *	@return		 : OK
 *  @notice      : None
 */
void test_function(){
	MGraph G;
	int loc1,loc2;
	char a;
	VexType vexs[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	ArcInfo arcs[2];
	arcs[0].v = {'A'};
	arcs[0].w = {'B'};
	arcs[1].v = {'C'};
	arcs[1].w = {'D'};
	CreateGraph_UDG(G,vexs,7,arcs,7);
	// printf the Graph 
	print_Graph(G);
	 //test 1
	printf("*************************************************\n");
	printf("test1:find the location of vexs\n");
	loc1 = LocateVex_UDG(G,'A');
	printf("For the vexs 'A',the True result is 0\n");
	printf("Your result is %d\n",loc1);
	
	loc2 = LocateVex_UDG(G,'E');
	printf("For the vexs 'E',the True result is 4\n");
	printf("Your result is %d\n",loc2);
	
	printf("*************************************************\n");
	// test 2
	printf("test2:get the value of vexs to w\n");
	VexType w;
	int k1,k2;
	k1 = 2;
	GetVex_UDG(G,k1,w);
	printf("The %d vexs's is %c\n",k1,w);
	k2 = 0;
	GetVex_UDG(G,k2,w);
	printf("The %d vexs's is %c\n",k2,w);
	
	printf("*************************************************\n");
	// test3
	printf("give the k vexs a new value\n");
	w = 'M';
	printf("change the %d vexs with %c\n",k1,w);
	PutVex_UDG(G,k1,w);
	print_Graph(G);
	
	printf("*************************************************\n");
	// test 4
	printf("find the k vexs'first friend vexs\n");
	int result;
	if(ERROR == FirstAdjVex_UDG(G,k1))printf("can not find the positon\n");
	else {
		printf("For the %d vexs,the true result is 0\n",k1);
		result = FirstAdjVex_UDG(G,k1);
		printf("your result is %d\n",result);	
	}

	printf("*************************************************\n");
	// test 5
	printf("find the k vexs after m first friend vexs\n");
	int m=1;
	if(ERROR == NextAdjVex_UDG(G,k2,m))printf("can not find the positon\n");
	else {
		printf("For the %d vexs,the true result is 0\n",k2);
		NextAdjVex_UDG(G,k2,m);
		printf("your result is %d\n",result);	
	}
	printf("*************************************************\n");
	// test 6
	printf("add arc from k to m\n");
	k1 = 6;
	m = 1;
	AddArc_UDG(G,k1,m);
	print_Graph(G);
	printf("*************************************************\n");
	// test 7
	printf("remove the arc from k to m\n");
	k1 = 1;
	m = 0;
	RemoveArc_UDG(G,k1,m);
	print_Graph(G);
	printf("*************************************************\n");
	// test 8
	printf("DFS\n");
	DFSTraverse_UDG(G,visit);
	printf("\n");
	printf("*************************************************\n");
	// test 9 
	printf("BFS\n");
	BFSTraverse_UDG(G,visit);
	// test 10
	printf("\n");
	printf("*************************************************\n");
	printf("Destroy the Graph\n");
	DestroyGraph_UDG(G);
	printf("*************************************************\n");\
	printf("test finish\n");
}



/**
 *  @name        : void meau()
 *	@description : printf the meau to select the function
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
 
 void meau(){
	printf("***********************************************************\n");
	printf("******************无向图抽象数据类型实现*******************\n");
	printf("******************请选择你所要执行的功能*******************\n");
	printf("* 1.初始化创建图       2.取图G的k顶点的值到w      		   \n");
	printf("* 2.对图G的k顶点赋值w  4.求图G中k顶点的第一个邻接顶点的位序\n");
	printf("* 5.求k顶点相对于m顶点的下一个邻接点的位序			   \n");
	printf("* 6.加k到m的边  		7.删除k到m的边 			           \n");
	printf("* 8.深度优先遍历图G             9.广度优先遍历图G          \n");
	printf("*                  0. 销毁图并退出系统                     \n"); 
 }

