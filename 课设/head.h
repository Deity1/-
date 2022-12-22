#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define UNVISITED 0
#define VISITED 1
#define SELECTED 1
#define UNSELECTED 0
#define INFINITY 32627
#define MAX 100

typedef char VexType;
typedef int Status;

/* 邻接数组的存储结构类型 */
typedef struct {
	VexType** vexs;  // 顶点数组，默认为char类型
	int** arcs;   // 关系数组
	int n, e;   // 顶点数和边数
	int* tags;  // 标志数组，可以用于在图的遍历中标记访问与否 
}MGraph;

typedef struct {
	VexType *v, *w;  // 边（弧）的端点
	int info;
}ArcInfo;

// 普利姆算法的结构体 
typedef struct{
	int adjInd;  //U中顶点的位序
	int lowcost;  // 边的权值 
}ClosedgeInfo; 


int LocateVex_UDG(MGraph G, VexType *v) {
	int loc;
	for (loc = 0; loc < G.n; loc++)
		if (0 == strcmp(G.vexs[loc],v))return loc;
	return ERROR;
}


//<descirbe>  Init the Graph
//<parameter> MGraph G,VexType *vexs[],int n
//<return >  OK
//
Status InitGraph_UDG(MGraph& G, VexType* vexs[], int n) {
	int i, j, info;
	if (n < 0 || (n > 0 && NULL == vexs)) return ERROR;
	// 因为初始化的是无向图
	info = 0;
	G.n = n;
	G.e = 0;
	if (0 == n)return OK; // 空图
	if (NULL == (G.vexs = (VexType**)malloc(n * sizeof(VexType*))))
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (G.vexs[i] = (VexType*)malloc(n * sizeof(VexType))))
			return OVERFLOW;	
	for (i = 0; i < n; i++)G.vexs[i] = vexs[i];
	//G.vexs[i] = vexs[i]; // 对顶点数组进行赋值
	if (NULL == (G.arcs = (int**)malloc(n * sizeof(int*))))
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (G.arcs[i] = (int*)malloc(n * sizeof(int))))
			return OVERFLOW;
	if (NULL == (G.tags = (int*)malloc(n * sizeof(int))))return OVERFLOW;
	for (i = 0; i < n; i++) {
		G.tags[i] = UNVISITED;
		for (j = 0; j < n; j++)G.arcs[i][j] = 0;    //  修改一下 
	}
	return OK;
}
//<descirbe>  Create the Graph
//<parameter> MGraph G
//<return >  OK
//
Status CreateGraph_UDG(MGraph& G, VexType* vexs[], int n, ArcInfo* arcs, int e) {
	int i, j, k;
	VexType *v, *w;
	if (InitGraph_UDG(G, vexs, n) != OK)return ERROR;
	G.e = e;
	for (k = 0; k < e; k++) {
		v = arcs[k].v; w = arcs[k].w;  // 读入边的信息
		i = LocateVex_UDG(G, v);
		j = LocateVex_UDG(G, w);  // 确定位序

		if (i < 0 || j < 0)return ERROR;
		G.arcs[i][j] = G.arcs[j][i] = arcs[k].info; // 赋值为权值,无向赋权
	}
	return OK;
}

//<descirbe>  find the first vexs
//<parameter> MGraph G
//<return >  OK
//
int FirstAdjVex_UDG(MGraph G, int k) {
	if (k<0 || k>G.n)return ERROR;
	int loc;
	for (; loc < G.n; loc++) {
		if (G.arcs[k][loc] != 0)return loc;  // 无向赋权图
	}
	return ERROR;
}

//<descirbe>  find the next vexs
//<parameter> MGraph G
//<return >  OK
//
int NextAdjVex_UDG(MGraph G, int k, int m) {
	if (k < 0 || m>0 || k > G.n || m > G.n)return ERROR;
	if (G.n < 1)return 0;
	int loc = m + 1;
	for (; loc < G.n; loc++) {
		if (G.arcs[k][loc] != 0)return loc;
	}
	return ERROR;
}

//<descirbe>  add the acrs
//<parameter> MGraph G, int k,int m,int info
//<return >  OK
//
Status AddArc_UDG(MGraph& G, int k, int m, int info) {
	if (k<0 || k>G.n || m<0 || m>G.n)return ERROR;
	if (G.arcs[k][m] != 0) {
		printf("该图已存在这条边\n");
		return ERROR;
	}
	G.arcs[k][m] = G.arcs[m][k] = info;
	G.e++;
	return OK;
}

//<descirbe>  del the acrs
//<parameter> MGraph G,int k,int m
//<return >  OK
//
Status RemoveArc_UDG(MGraph& G, int k, int m) {
	if (k<0 || k>G.n || m<0 || m>G.n)return ERROR;
	if (G.arcs[k][m] == 0) {
		printf("该图不存在这条边\n");
		return ERROR;
	}
	G.arcs[k][m] = G.arcs[m][k] = 0;
	G.e--;
	return OK;
}
//<descirbe>  print the vexs
//<parameter> MGraph G
//<return >  OK
//
Status visit(VexType top) {
	if (top == '\0')return ERROR;
	printf("%c", top);
	return OK;
}

//<descirbe>  print the Graph
//<parameter> MGraph G
//<return >  OK
//
Status print_Graph(MGraph G) {
	if (0 == G.n)return ERROR;
	G.arcs[0][0] = 0;
	int i, j;
	printf("\t");
	for (i = 0; i < G.n; i++)
		printf("%s\t", G.vexs[i]);
	printf("\n");
	for (i = 0; i < G.n; i++) {
		printf("%s\t ", G.vexs[i]);
		for (j = 0; j < G.n; j++)
			printf("%d\t", G.arcs[i][j]);
		printf("\n");
	}
}
//<descirbe>  prepare for the prim
//<parameter> MGraph G
//<return >  OK
//
Status To_Infinity(MGraph &G){
	int i,j;
	for(i=0;i<G.n;i++)
		for(j=0;j<G.n;j++)
			if(G.arcs[i][j] == 0)G.arcs[i][j] = INFINITY;
	return OK;
}

//<descirbe>  return to the normal
//<parameter> MGraph G
//<return >  OK
//
Status To_normal(MGraph &G){
	int i,j;
	for(i=0;i<G.n;i++)
		for(j=0;j<G.n;j++)
			if(G.arcs[i][j] == INFINITY)G.arcs[i][j] = 0;
	return OK;
}

//<descirbe>  Prim find the lowcost road
//<parameter> MGraph G , int i ,T
//<return >  OK
//
Status Prim(MGraph G,int i,MGraph &T) {
	int j,min,k,m = 0;
	ClosedgeInfo *closedge;
	closedge = (ClosedgeInfo*)malloc(G.n * sizeof(ClosedgeInfo));
	InitGraph_UDG(T,G.vexs,G.n);
	if(OK != To_Infinity(G))return ERROR;
	for(j=0;j<G.n;j++){
		G.tags[j] = UNSELECTED;
		if(j != i){
			closedge[j].adjInd = i;
			closedge[j].lowcost = G.arcs[i][j];
		}
	}
	closedge[i].lowcost = 0;
	T.tags[i] = SELECTED;
	T.e = 0; // 在T中增加i顶点
	printf("%s->",G.vexs[i]);
	for(m=1;m<G.n;m++){
		min = INFINITY;k=0;
		for(j=0;j<G.n;j++)
			if(closedge[j].lowcost>0&&closedge[j].lowcost<min){
				k = j;min = closedge[j].lowcost;
			}
		if(INFINITY == min)break; // 没有边可以选的情况下
		T.tags[k] = SELECTED;  // 在T中新增k顶点
		printf("%s->",T.vexs[k]); 
		T.arcs[k][closedge[k].adjInd] = T.arcs[closedge[k].adjInd][k] = closedge[k].lowcost;
		T.e++;
		closedge[k].lowcost = 0;
		for(j=0;j<G.n;j++)    // 更新closedge数组 
		if(closedge[j].lowcost!=0 && G.arcs[k][j] < closedge[j].lowcost){
			closedge[j].adjInd = k; closedge[j].lowcost = G.arcs[k][j];
		}
			
	}
	To_normal(G);
	float sum=0;
	int loc;
	for(loc=0;loc<T.n;loc++)
		for(j=0;j<T.n;j++)
			if(T.arcs[loc][j] != 0)sum= sum + T.arcs[loc][j];
	printf("总里程为:%.0f\n",sum/2);
	free(closedge);
	if(T.e == G.n-1)return OK;
	return ERROR;
}

//<descirbe>  destory the Graph
//<parameter> MGraph G
//<return >  OK
//
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
//<descirbe>  for  the user to create the  struct of the Graph 
//<parameter> MGraph G
//<return >  OK
//
Status Save_data(MGraph G);
Status Create_Self(MGraph &G,ArcInfo *arcs){
	system("cls");
	int n,e;
	int i;
	printf("请问你要创建多少个城市:\n");
	scanf("%d",&n);
	printf("请问你要创建多少条边:\n");
	scanf("%d",&e);
	VexType **vexs;
	if (NULL == (vexs = (VexType**)malloc(n * sizeof(VexType*))))
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (vexs[i] = (VexType*)malloc(n * sizeof(VexType))))
			return OVERFLOW;	
	for(i = 0;i<n;i++){
		printf("输入第%d个城市:\n",i+1);
		scanf("%s",vexs[i]);
	}
	arcs = (ArcInfo*)malloc(e * sizeof(ArcInfo));
	for(i = 0;i < e;i++){
		arcs[i].v = (VexType*)malloc(e*sizeof(VexType));
		arcs[i].w = (VexType*)malloc(e*sizeof(VexType));
	}
	for(i = 0;i<e;i++){
		printf("请输入第%d组中一个城市的名字:\n",i+1);
		scanf("%s",arcs[i].v);
		printf("请输入第%d组中二个城市的名字:\n",i+1);
		scanf("%s",arcs[i].w);
		printf("请输入第%d组中的城市路径长度:\n",i+1);
		scanf("%d",&arcs[i].info);
	}
	CreateGraph_UDG(G,vexs,n,arcs,e);
	return OK;
}


//<descirbe>  for  the user to change the  struct of the Graph 
//<parameter> MGraph G
//<return >  OK
//
Status Change_Vexs(MGraph &G){
	system("cls");
	printf("请问你是否要修改图的顶点信息(y/n)\n");
	char ans;
	scanf("%c",&ans);
	if(ans == 'y')
	{
		int sel,i,j;
		printf("请问你是要删除结点还是要增加结点(0:增加 1:删除)\n");	
		scanf("%d",&sel); 
		if(0 == sel){
			printf("请问你要增加几个结点\n");
			int add,temp = G.n;  // 统计增加结点的数量 
			scanf("%d",&add);
			printf("添加前的路径图如下(请不要添加相同的城市噢):\n");
			print_Graph(G);
			G.n = G.n + add;
			// 如果出现了删除结点的情况 
			if(G.n < temp){
				printf("增加的城市数量不能是负数噢\n");
				return ERROR;
			}
			G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//扩大容量 
			G.arcs=(int **)realloc(G.arcs,sizeof(int*)*G.n);
			//由于realloc可以保证前面部分值不变，所以 前100个不动。
			for(i = temp; i < G.n; i ++){
			
    			G.vexs[i] = (VexType*)malloc(sizeof(VexType)*G.n);
    			G.arcs[i] = (int*)malloc(sizeof(int)*G.n);
			}
			// 对边的信息进行赋空
			for(i = 0;i<G.n;i++)
				for(j = temp;j<G.n;j++)
					G.arcs[i][j] = 0; 
			for(i = temp; i < G.n; i ++)
			{
    			printf("请输入添加的城市名字:\n");
				scanf("%s",G.vexs[i]);
				for(j = 0;j<temp;j++)
					if(0 == strcmp(G.vexs[j],G.vexs[i])){
						printf("添加重复结点,出错啦\n");
						return ERROR;
					} 
			}
			printf("添加后的路径图如下:\n");
			print_Graph(G);
			printf("添加完成\n");
			return OK;
		}
		else if(1 == sel){
			printf("请问你要删除几个结点\n");
			int del,store = G.n;  // 统计增加结点的数量 
			scanf("%d",&del);
			if(G.n < 0){
				printf("城市全部删除,图销毁\n");
				if(OK == DestroyGraph_UDG(G))
					exit(0); 
			}
			printf("删除前的城市图为:\n");
			print_Graph(G);
			char *s;   // 用于要删除的结点的信息 
			int loc,swap,pp;
			for(i=1;i<=del;i++)
			{	
				s = (char*)malloc(G.n * sizeof(char)); 
				printf("请输入你要删除的第%d个结点\n",i);
				scanf("%s",s);
				j = LocateVex_UDG(G,s);
				if(ERROR == j){
					printf("出错啦,没有找到该城市噢\n");
					return ERROR;
				}
				// 采取交换的策略，将最后一个与当前位置交换，然后将最后的空间释放掉
				pp = G.arcs[j][store - i];
				// 结点名字的互换 
				s = G.vexs[j];
				G.vexs[j] = G.vexs[store - i];
				G.vexs[store - i] = s;
				for(loc = 0;loc < store;loc++){
					swap = 	G.arcs[loc][j];
					G.arcs[loc][j] = G.arcs[loc][store - i];
					G.arcs[loc][store - i] = swap;
					
					swap = G.arcs[j][loc];
					G.arcs[j][loc] = G.arcs[store - i][loc];
					G.arcs[store - i][loc] = swap;	
				}
				// 直接交换的话，如果删除结点与交换结点存在路劲的话会出现问题，需要微调
				if(0 != pp){
					G.arcs[store - i][j] = G.arcs[j][store - i] = pp; 
					G.arcs[store - i][store - i] = G.arcs[j][j] = 0;
					}
				}
			G.n = G.n - del; 		
			// 先释放列再再释放行 
			G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//减少容量
			for(i=G.n;i<store;i++)
				free(G.arcs[i]); 
			printf("删除结点成功,删除后的路径图如下:\n");
			print_Graph(G);
			return OK;
		}
		else{
			printf("操作失败\n");
			return ERROR;
		}
	}
	else
		printf("退出操作\n");
	return OK;
}


//<descirbe>  add new city into the Graph
//<parameter> MGraph G
//<return >  OK
//
Status Add_City(MGraph &G){
	int i,j;
	printf("请问你要增加几个结点\n");
	int add,temp = G.n;  // 统计增加结点的数量 
	scanf("%d",&add);
	printf("添加前的路径图如下(请不要添加相同的城市噢):\n");
	print_Graph(G);
	G.n = G.n + add;
	// 如果出现了删除结点的情况 
	if(G.n < temp){
		printf("增加的城市数量不能是负数噢\n");
		return ERROR;
	}
	G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//扩大容量 
	G.arcs=(int **)realloc(G.arcs,sizeof(int*)*G.n);
	//由于realloc可以保证前面部分值不变，所以 前100个不动。
	for(i = temp; i < G.n; i ++){
	
		G.vexs[i] = (VexType*)malloc(sizeof(VexType)*G.n);
		G.arcs[i] = (int*)malloc(sizeof(int)*G.n);
	}
	// 对边的信息进行赋空
	for(i = 0;i<G.n;i++)
		for(j = temp;j<G.n;j++)
			G.arcs[i][j] = 0; 
	for(i = temp; i < G.n; i ++)
	{
		printf("请输入添加的城市名字:\n");
		scanf("%s",G.vexs[i]);
		for(j = 0;j<temp;j++)
			if(0 == strcmp(G.vexs[j],G.vexs[i])){
				printf("添加重复结点,出错啦\n");
				return ERROR;
			} 
	}
	printf("添加后的路径图如下:\n");
	print_Graph(G);
	printf("添加完成\n");
	return OK;
}
//<descirbe>  del city from the Graph
//<parameter> MGraph G
//<return >  OK
//
Status Del_City(MGraph G){
	int i,j;
	printf("请问你要删除几个结点\n");
	int del,store = G.n;  // 统计增加结点的数量 
	scanf("%d",&del);
	if(G.n < 0){
		printf("城市全部删除,图销毁\n");
		if(OK == DestroyGraph_UDG(G))
			exit(0); 
	}
	printf("删除前的城市图为:\n");
	print_Graph(G);
	char *s;   // 用于要删除的结点的信息 
	int loc,swap,pp;
	for(i=1;i<=del;i++)
	{	
		s = (char*)malloc(G.n * sizeof(char)); 
		printf("请输入你要删除的第%d个结点\n",i);
		scanf("%s",s);
		j = LocateVex_UDG(G,s);
		if(ERROR == j && 0 != strcmp(G.vexs[0],s)){
			printf("出错啦,没有找到该城市噢\n");
			return ERROR;
		}
		// 采取交换的策略，将最后一个与当前位置交换，然后将最后的空间释放掉
		pp = G.arcs[j][store - i];
		// 结点名字的互换 
		s = G.vexs[j];
		G.vexs[j] = G.vexs[store - i];
		G.vexs[store - i] = s;
		for(loc = 0;loc < store;loc++){
			swap = 	G.arcs[loc][j];
			G.arcs[loc][j] = G.arcs[loc][store - i];
			G.arcs[loc][store - i] = swap;
			
			swap = G.arcs[j][loc];
			G.arcs[j][loc] = G.arcs[store - i][loc];
			G.arcs[store - i][loc] = swap;	
		}
		// 直接交换的话，如果删除结点与交换结点存在路劲的话会出现问题，需要微调
		if(0 != pp){
			G.arcs[store - i][j] = G.arcs[j][store - i] = pp; 
			G.arcs[store - i][store - i] = G.arcs[j][j] = 0;
			}
		}
	G.n = G.n - del; 		
	// 先释放列再再释放行 
	G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//减少容量
	for(i=G.n;i<store;i++)
		free(G.arcs[i]); 
	printf("删除结点成功,删除后的路径图如下:\n");
	print_Graph(G);
	return OK;
} 

//<descirbe>  save data in the txt 
//<parameter> MGraph G
//<return >  OK
//
Status Save_data(MGraph G,ArcInfo *arcs){
	FILE *fp;
	fp  = fopen("./road_data.txt","w");
	int i,j;
	if(fp == NULL)
	{
		perror("fopen");				// 文件打开失败，打印错误信息
		return ERROR;
	}
	// 写入顶点数和边数
	fprintf(fp,"%d %d\n",G.n,G.e); 
	// 写入顶点的信息 
	for(i=0;i<G.n;i++)
		fprintf(fp,"%s ",G.vexs[i]);
	fprintf(fp,"\n");
	// 写入边的信息 
	for(i=0;i<G.n;i++){
		for(j=0;j<G.n;j++)
			fprintf(fp,"%d ",G.arcs[i][j]);
		fprintf(fp,"\n");}
	// 写入边集的信息
	for(i=0;i<G.e;i++)
		fprintf(fp,"%s %s %d\n",arcs[i].v,arcs[i].w,arcs[i].info); 
	fclose(fp); // 关闭文件 
	return OK;
}


//<descirbe>  read data in the txt into the G 
//<parameter> MGraph G
//<return >  OK
//
Status Read_data(MGraph &G,ArcInfo *&arcs){
	FILE *fp;
	int i,j;
		
	fp = fopen("./road_data.txt","r");
	if(fp == NULL)
	{
		perror("fopen");				// 文件打开失败，打印错误信息
		return ERROR;
	}
	
	fscanf(fp,"%d %d\n",&G.n,&G.e);  // 首先读取顶点和边的信息
	// 开辟空间 
	if (NULL == (G.vexs = (VexType**)malloc(G.n * sizeof(VexType*))))
		return OVERFLOW;
	for (i = 0; i < G.n; i++)
		if (NULL == (G.vexs[i] = (VexType*)malloc(G.n * sizeof(VexType))))
			return OVERFLOW;
	if (NULL == (G.arcs = (int**)malloc(G.n * sizeof(int*))))
		return OVERFLOW;
	for (i = 0; i < G.n; i++)
		if (NULL == (G.arcs[i] = (int*)malloc(G.n * sizeof(int))))
			return OVERFLOW;
	for(i = 0;i<G.n;i++)
		G.tags = (int*)malloc(G.n * sizeof(int));
	arcs = (ArcInfo*)malloc(G.e * sizeof(ArcInfo));
	for(i = 0;i < G.e;i++){
		arcs[i].v = (VexType*)malloc(G.e*sizeof(VexType));
		arcs[i].w = (VexType*)malloc(G.e*sizeof(VexType));
	}
	// 读入顶点数据 
	for(i=0;i<G.n;i++)
		fscanf(fp,"%s ",G.vexs[i]);
	fscanf(fp,"\n");
	// 写入边的信息 
	for(i=0;i<G.n;i++)
	{
		for(j=0;j<G.n;j++)
			fscanf(fp,"%d ",&G.arcs[i][j]);
		fscanf(fp,"\n");
	}
	for(i=0;i<G.e;i++){
	
		fscanf(fp,"%s %s %d\n",arcs[i].v,arcs[i].w,&arcs[i].info);
	}
	fclose(fp); // 关闭文件 
	return OK;		
}


//<descirbe>  show the meau of the main
//<parameter> NULL
//<return >  NULL
//
void Meau_Main(){
	printf("*********************************************\n");
	printf("***---------------------------------------***\n");
	printf("**   Author:Deity        Time:2022.12.18  ***\n");
	printf("***---------------------------------------***\n");
	printf("**    1. 用户自行输入数据创建城市道路图   ***\n");
	printf("**    2. 从本地的数据集中导入城市道路图   ***\n");
	printf("**    3. 普里姆算法得城际铁路建设方案     ***\n");
	printf("**    4. 克鲁斯卡算法城际铁路建设方案     ***\n");
	printf("**           5. 对道路图的操作            ***\n");
	printf("**           6. 删图并退出系统            ***\n");
	printf("***---------------------------------------***\n");
	printf("*********************************************\n");
} 
//<descirbe>  show the meau of the change of the struct
//<parameter> NULL
//<return >  NULL
//
void Meau_Change(){
	printf("*********************************************\n");
	printf("***---------------------------------------***\n");
	printf("**   Author:Deity        Time:2022.12.18  ***\n");
	printf("***---------------------------------------***\n");
	printf("**             1. 添加新的城市            ***\n");
	printf("**             2. 删除某个城市            ***\n");
	printf("**             3. 添加城市道路            ***\n");
	printf("**             4. 删除城市道路            ***\n");
	printf("**             5. 退出操作环节            ***\n");
	printf("***---------------------------------------***\n");
	printf("*********************************************\n");
	printf("\n");
}



//<descirbe>  call the change function
//<parameter> MGraph G
//<return >   OK
//
Status Call_function(MGraph &G){
	system("cls");
	Meau_Change();
	int sel;
	printf("请输入你要进行的操作\n");
	scanf("%d",&sel);
	if(sel < 1 || sel > 5){
		printf("没有该选项，操作失败\n");
		return ERROR;
	}
	switch(sel){
		case 1:Add_City(G);system("pause");break;
		case 2:Del_City(G);system("pause");break;
		case 3:{
			int k,m,info;
			printf("当前的道路图为:\n");
			print_Graph(G);
			char *s = (char*)malloc(G.n * sizeof(char));
			char *p = (char*)malloc(G.n * sizeof(char)); 
			printf("请输入你要添加道路的第一个城市的名字\n");
			scanf("%s",s);
			if(ERROR == LocateVex_UDG(G,s) && 0 != strcmp(G.vexs[0],s)){
				printf("输入的城市不在道路图内,请先添加城市后再进行操作\n");
				return ERROR;
			}
			else k = LocateVex_UDG(G,s);
			printf("请输入你要添加道路的第二个城市的名字\n");
			scanf("%s",p);
			if(ERROR == LocateVex_UDG(G,p) && 0 != strcmp(G.vexs[0],p)){
				printf("输入的城市不在道路图内,请先添加城市后再进行操作\n");
				return ERROR;
			}
			else m = LocateVex_UDG(G,p);
			printf("请输入你要添加道路的长度\n");
			scanf("%d",&info);
			if(OK == AddArc_UDG(G,k,m,info)){
				printf("添加成功\n");
				printf("添加后的道路图为:\n");
				print_Graph(G);
				}
			system("pause");
			break;
		}
		case 4:{
			int k,m,info;
			print_Graph(G); 
			char *s = (char*)malloc(G.n * sizeof(char));
			char *p = (char*)malloc(G.n * sizeof(char)); 
			printf("请输入你要删除道路的第一个城市的名字\n");
			scanf("%s",s);
			if(ERROR == LocateVex_UDG(G,s) && 0 != strcmp(G.vexs[0],s)){
				printf("输入的城市不在道路图内,请先添加城市后再进行操作\n");
				return ERROR;
			}
			else k = LocateVex_UDG(G,s);
			printf("请输入你要删除道路的第二个城市的名字\n");
			scanf("%s",p);
			if(ERROR == LocateVex_UDG(G,p) && 0 != strcmp(G.vexs[0],p)){
				printf("输入的城市不在道路图内,请先添加城市后再进行操作\n");
				return ERROR;
			}
			else m = LocateVex_UDG(G,p);
			if(OK == RemoveArc_UDG(G,k,m))
				printf("删除成功\n");
			system("pause");	
			break;
		}
		case 5:printf("退出该操作\n");break; 
	}
}



//<descirbe>  sort
//<parameter> MGraph G
//<return >   OK
//
void Sort(MGraph G,ArcInfo *Edge)//书上的Sort函数，将数组Edege中的元素按权值从小到大排序，这里用 冒泡排序 
{
	int i,j;//记录次数 
	for(i=G.e-1;i>=0;i--)//相邻两数的比较终点 
	{
		for(j=0;j<i;j++)//进行相邻两数的比较 
		{
			if(Edge[j].info > Edge[j+1].info)//如果大于，互换位置 
			{
				Edge[G.e] = Edge[j];
				Edge[j] = Edge[j+1];
				Edge[j+1] = Edge[G.e];
			}
		}
	}
}


//<descirbe>  Krusal 
//<parameter> MGraph G,ArcInfo *Edge
//<return >   OK
//
Status Kruskal(MGraph G,ArcInfo *Edge){
	int i,j;
	int Vexset[50];//再申请一个辅助数组Vexset
	Sort(G,Edge);//根据权值排序
	for(i=0;i<G.n;i++)//辅助数组，表示各顶点自成一个连通分量 
		Vexset[i] = i;
	int v1,v2,
		vs1,vs2;
	int sum = 0;
	printf("克鲁斯卡尔算法选边的顺序如下:\n");
	for(i=0;i<G.e;i++)//依次查看数组Edge中的边 
	{
		v1 = LocateVex_UDG(G,Edge[i].v);//v1为边的始点的下标  定位函数 
		v2 = LocateVex_UDG(G,Edge[i].w);//v2为边的终点的下标 
		vs1 = Vexset[v1];//获取边Edge[i]的始点所在的连通分量vs1 
		vs2 = Vexset[v2];//获取边Edge[i]的终点所在的连通分量vs2
		if(vs1 != vs2)//边的两个顶点分属不同的连通分量 
		{
			printf("%s->%s  ",Edge[i].v,Edge[i].w);//输出打印次边 
			sum = sum + Edge[i].info;
			for(j=0;j<G.n;j++)//合并vs1和vs2两个分量，即两个集合统一编号 
				if(Vexset[j] == vs2)//集合编号为vs2的都改为vs1 
					Vexset[j] = vs1;
		}
	}
	printf("总里程数为%d\n",sum);

} 



