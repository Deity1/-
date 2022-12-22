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

/* �ڽ�����Ĵ洢�ṹ���� */
typedef struct {
	VexType** vexs;  // �������飬Ĭ��Ϊchar����
	int** arcs;   // ��ϵ����
	int n, e;   // �������ͱ���
	int* tags;  // ��־���飬����������ͼ�ı����б�Ƿ������ 
}MGraph;

typedef struct {
	VexType *v, *w;  // �ߣ������Ķ˵�
	int info;
}ArcInfo;

// ����ķ�㷨�Ľṹ�� 
typedef struct{
	int adjInd;  //U�ж����λ��
	int lowcost;  // �ߵ�Ȩֵ 
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
	// ��Ϊ��ʼ����������ͼ
	info = 0;
	G.n = n;
	G.e = 0;
	if (0 == n)return OK; // ��ͼ
	if (NULL == (G.vexs = (VexType**)malloc(n * sizeof(VexType*))))
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (G.vexs[i] = (VexType*)malloc(n * sizeof(VexType))))
			return OVERFLOW;	
	for (i = 0; i < n; i++)G.vexs[i] = vexs[i];
	//G.vexs[i] = vexs[i]; // �Զ���������и�ֵ
	if (NULL == (G.arcs = (int**)malloc(n * sizeof(int*))))
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (G.arcs[i] = (int*)malloc(n * sizeof(int))))
			return OVERFLOW;
	if (NULL == (G.tags = (int*)malloc(n * sizeof(int))))return OVERFLOW;
	for (i = 0; i < n; i++) {
		G.tags[i] = UNVISITED;
		for (j = 0; j < n; j++)G.arcs[i][j] = 0;    //  �޸�һ�� 
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
		v = arcs[k].v; w = arcs[k].w;  // ����ߵ���Ϣ
		i = LocateVex_UDG(G, v);
		j = LocateVex_UDG(G, w);  // ȷ��λ��

		if (i < 0 || j < 0)return ERROR;
		G.arcs[i][j] = G.arcs[j][i] = arcs[k].info; // ��ֵΪȨֵ,����Ȩ
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
		if (G.arcs[k][loc] != 0)return loc;  // ����Ȩͼ
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
		printf("��ͼ�Ѵ���������\n");
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
		printf("��ͼ������������\n");
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
	T.e = 0; // ��T������i����
	printf("%s->",G.vexs[i]);
	for(m=1;m<G.n;m++){
		min = INFINITY;k=0;
		for(j=0;j<G.n;j++)
			if(closedge[j].lowcost>0&&closedge[j].lowcost<min){
				k = j;min = closedge[j].lowcost;
			}
		if(INFINITY == min)break; // û�б߿���ѡ�������
		T.tags[k] = SELECTED;  // ��T������k����
		printf("%s->",T.vexs[k]); 
		T.arcs[k][closedge[k].adjInd] = T.arcs[closedge[k].adjInd][k] = closedge[k].lowcost;
		T.e++;
		closedge[k].lowcost = 0;
		for(j=0;j<G.n;j++)    // ����closedge���� 
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
	printf("�����Ϊ:%.0f\n",sum/2);
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
	// �ͷűߵĿռ�
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
	printf("������Ҫ�������ٸ�����:\n");
	scanf("%d",&n);
	printf("������Ҫ������������:\n");
	scanf("%d",&e);
	VexType **vexs;
	if (NULL == (vexs = (VexType**)malloc(n * sizeof(VexType*))))
		return OVERFLOW;
	for (i = 0; i < n; i++)
		if (NULL == (vexs[i] = (VexType*)malloc(n * sizeof(VexType))))
			return OVERFLOW;	
	for(i = 0;i<n;i++){
		printf("�����%d������:\n",i+1);
		scanf("%s",vexs[i]);
	}
	arcs = (ArcInfo*)malloc(e * sizeof(ArcInfo));
	for(i = 0;i < e;i++){
		arcs[i].v = (VexType*)malloc(e*sizeof(VexType));
		arcs[i].w = (VexType*)malloc(e*sizeof(VexType));
	}
	for(i = 0;i<e;i++){
		printf("�������%d����һ�����е�����:\n",i+1);
		scanf("%s",arcs[i].v);
		printf("�������%d���ж������е�����:\n",i+1);
		scanf("%s",arcs[i].w);
		printf("�������%d���еĳ���·������:\n",i+1);
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
	printf("�������Ƿ�Ҫ�޸�ͼ�Ķ�����Ϣ(y/n)\n");
	char ans;
	scanf("%c",&ans);
	if(ans == 'y')
	{
		int sel,i,j;
		printf("��������Ҫɾ����㻹��Ҫ���ӽ��(0:���� 1:ɾ��)\n");	
		scanf("%d",&sel); 
		if(0 == sel){
			printf("������Ҫ���Ӽ������\n");
			int add,temp = G.n;  // ͳ�����ӽ������� 
			scanf("%d",&add);
			printf("���ǰ��·��ͼ����(�벻Ҫ�����ͬ�ĳ�����):\n");
			print_Graph(G);
			G.n = G.n + add;
			// ���������ɾ��������� 
			if(G.n < temp){
				printf("���ӵĳ������������Ǹ�����\n");
				return ERROR;
			}
			G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//�������� 
			G.arcs=(int **)realloc(G.arcs,sizeof(int*)*G.n);
			//����realloc���Ա�֤ǰ�沿��ֵ���䣬���� ǰ100��������
			for(i = temp; i < G.n; i ++){
			
    			G.vexs[i] = (VexType*)malloc(sizeof(VexType)*G.n);
    			G.arcs[i] = (int*)malloc(sizeof(int)*G.n);
			}
			// �Աߵ���Ϣ���и���
			for(i = 0;i<G.n;i++)
				for(j = temp;j<G.n;j++)
					G.arcs[i][j] = 0; 
			for(i = temp; i < G.n; i ++)
			{
    			printf("��������ӵĳ�������:\n");
				scanf("%s",G.vexs[i]);
				for(j = 0;j<temp;j++)
					if(0 == strcmp(G.vexs[j],G.vexs[i])){
						printf("����ظ����,������\n");
						return ERROR;
					} 
			}
			printf("��Ӻ��·��ͼ����:\n");
			print_Graph(G);
			printf("������\n");
			return OK;
		}
		else if(1 == sel){
			printf("������Ҫɾ���������\n");
			int del,store = G.n;  // ͳ�����ӽ������� 
			scanf("%d",&del);
			if(G.n < 0){
				printf("����ȫ��ɾ��,ͼ����\n");
				if(OK == DestroyGraph_UDG(G))
					exit(0); 
			}
			printf("ɾ��ǰ�ĳ���ͼΪ:\n");
			print_Graph(G);
			char *s;   // ����Ҫɾ���Ľ�����Ϣ 
			int loc,swap,pp;
			for(i=1;i<=del;i++)
			{	
				s = (char*)malloc(G.n * sizeof(char)); 
				printf("��������Ҫɾ���ĵ�%d�����\n",i);
				scanf("%s",s);
				j = LocateVex_UDG(G,s);
				if(ERROR == j){
					printf("������,û���ҵ��ó�����\n");
					return ERROR;
				}
				// ��ȡ�����Ĳ��ԣ������һ���뵱ǰλ�ý�����Ȼ�����Ŀռ��ͷŵ�
				pp = G.arcs[j][store - i];
				// ������ֵĻ��� 
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
				// ֱ�ӽ����Ļ������ɾ������뽻��������·���Ļ���������⣬��Ҫ΢��
				if(0 != pp){
					G.arcs[store - i][j] = G.arcs[j][store - i] = pp; 
					G.arcs[store - i][store - i] = G.arcs[j][j] = 0;
					}
				}
			G.n = G.n - del; 		
			// ���ͷ��������ͷ��� 
			G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//��������
			for(i=G.n;i<store;i++)
				free(G.arcs[i]); 
			printf("ɾ�����ɹ�,ɾ�����·��ͼ����:\n");
			print_Graph(G);
			return OK;
		}
		else{
			printf("����ʧ��\n");
			return ERROR;
		}
	}
	else
		printf("�˳�����\n");
	return OK;
}


//<descirbe>  add new city into the Graph
//<parameter> MGraph G
//<return >  OK
//
Status Add_City(MGraph &G){
	int i,j;
	printf("������Ҫ���Ӽ������\n");
	int add,temp = G.n;  // ͳ�����ӽ������� 
	scanf("%d",&add);
	printf("���ǰ��·��ͼ����(�벻Ҫ�����ͬ�ĳ�����):\n");
	print_Graph(G);
	G.n = G.n + add;
	// ���������ɾ��������� 
	if(G.n < temp){
		printf("���ӵĳ������������Ǹ�����\n");
		return ERROR;
	}
	G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//�������� 
	G.arcs=(int **)realloc(G.arcs,sizeof(int*)*G.n);
	//����realloc���Ա�֤ǰ�沿��ֵ���䣬���� ǰ100��������
	for(i = temp; i < G.n; i ++){
	
		G.vexs[i] = (VexType*)malloc(sizeof(VexType)*G.n);
		G.arcs[i] = (int*)malloc(sizeof(int)*G.n);
	}
	// �Աߵ���Ϣ���и���
	for(i = 0;i<G.n;i++)
		for(j = temp;j<G.n;j++)
			G.arcs[i][j] = 0; 
	for(i = temp; i < G.n; i ++)
	{
		printf("��������ӵĳ�������:\n");
		scanf("%s",G.vexs[i]);
		for(j = 0;j<temp;j++)
			if(0 == strcmp(G.vexs[j],G.vexs[i])){
				printf("����ظ����,������\n");
				return ERROR;
			} 
	}
	printf("��Ӻ��·��ͼ����:\n");
	print_Graph(G);
	printf("������\n");
	return OK;
}
//<descirbe>  del city from the Graph
//<parameter> MGraph G
//<return >  OK
//
Status Del_City(MGraph G){
	int i,j;
	printf("������Ҫɾ���������\n");
	int del,store = G.n;  // ͳ�����ӽ������� 
	scanf("%d",&del);
	if(G.n < 0){
		printf("����ȫ��ɾ��,ͼ����\n");
		if(OK == DestroyGraph_UDG(G))
			exit(0); 
	}
	printf("ɾ��ǰ�ĳ���ͼΪ:\n");
	print_Graph(G);
	char *s;   // ����Ҫɾ���Ľ�����Ϣ 
	int loc,swap,pp;
	for(i=1;i<=del;i++)
	{	
		s = (char*)malloc(G.n * sizeof(char)); 
		printf("��������Ҫɾ���ĵ�%d�����\n",i);
		scanf("%s",s);
		j = LocateVex_UDG(G,s);
		if(ERROR == j && 0 != strcmp(G.vexs[0],s)){
			printf("������,û���ҵ��ó�����\n");
			return ERROR;
		}
		// ��ȡ�����Ĳ��ԣ������һ���뵱ǰλ�ý�����Ȼ�����Ŀռ��ͷŵ�
		pp = G.arcs[j][store - i];
		// ������ֵĻ��� 
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
		// ֱ�ӽ����Ļ������ɾ������뽻��������·���Ļ���������⣬��Ҫ΢��
		if(0 != pp){
			G.arcs[store - i][j] = G.arcs[j][store - i] = pp; 
			G.arcs[store - i][store - i] = G.arcs[j][j] = 0;
			}
		}
	G.n = G.n - del; 		
	// ���ͷ��������ͷ��� 
	G.vexs=(VexType**)realloc(G.vexs, sizeof(VexType*)*G.n);//��������
	for(i=G.n;i<store;i++)
		free(G.arcs[i]); 
	printf("ɾ�����ɹ�,ɾ�����·��ͼ����:\n");
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
		perror("fopen");				// �ļ���ʧ�ܣ���ӡ������Ϣ
		return ERROR;
	}
	// д�붥�����ͱ���
	fprintf(fp,"%d %d\n",G.n,G.e); 
	// д�붥�����Ϣ 
	for(i=0;i<G.n;i++)
		fprintf(fp,"%s ",G.vexs[i]);
	fprintf(fp,"\n");
	// д��ߵ���Ϣ 
	for(i=0;i<G.n;i++){
		for(j=0;j<G.n;j++)
			fprintf(fp,"%d ",G.arcs[i][j]);
		fprintf(fp,"\n");}
	// д��߼�����Ϣ
	for(i=0;i<G.e;i++)
		fprintf(fp,"%s %s %d\n",arcs[i].v,arcs[i].w,arcs[i].info); 
	fclose(fp); // �ر��ļ� 
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
		perror("fopen");				// �ļ���ʧ�ܣ���ӡ������Ϣ
		return ERROR;
	}
	
	fscanf(fp,"%d %d\n",&G.n,&G.e);  // ���ȶ�ȡ����ͱߵ���Ϣ
	// ���ٿռ� 
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
	// ���붥������ 
	for(i=0;i<G.n;i++)
		fscanf(fp,"%s ",G.vexs[i]);
	fscanf(fp,"\n");
	// д��ߵ���Ϣ 
	for(i=0;i<G.n;i++)
	{
		for(j=0;j<G.n;j++)
			fscanf(fp,"%d ",&G.arcs[i][j]);
		fscanf(fp,"\n");
	}
	for(i=0;i<G.e;i++){
	
		fscanf(fp,"%s %s %d\n",arcs[i].v,arcs[i].w,&arcs[i].info);
	}
	fclose(fp); // �ر��ļ� 
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
	printf("**    1. �û������������ݴ������е�·ͼ   ***\n");
	printf("**    2. �ӱ��ص����ݼ��е�����е�·ͼ   ***\n");
	printf("**    3. ����ķ�㷨�óǼ���·���跽��     ***\n");
	printf("**    4. ��³˹���㷨�Ǽ���·���跽��     ***\n");
	printf("**           5. �Ե�·ͼ�Ĳ���            ***\n");
	printf("**           6. ɾͼ���˳�ϵͳ            ***\n");
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
	printf("**             1. ����µĳ���            ***\n");
	printf("**             2. ɾ��ĳ������            ***\n");
	printf("**             3. ��ӳ��е�·            ***\n");
	printf("**             4. ɾ�����е�·            ***\n");
	printf("**             5. �˳���������            ***\n");
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
	printf("��������Ҫ���еĲ���\n");
	scanf("%d",&sel);
	if(sel < 1 || sel > 5){
		printf("û�и�ѡ�����ʧ��\n");
		return ERROR;
	}
	switch(sel){
		case 1:Add_City(G);system("pause");break;
		case 2:Del_City(G);system("pause");break;
		case 3:{
			int k,m,info;
			printf("��ǰ�ĵ�·ͼΪ:\n");
			print_Graph(G);
			char *s = (char*)malloc(G.n * sizeof(char));
			char *p = (char*)malloc(G.n * sizeof(char)); 
			printf("��������Ҫ��ӵ�·�ĵ�һ�����е�����\n");
			scanf("%s",s);
			if(ERROR == LocateVex_UDG(G,s) && 0 != strcmp(G.vexs[0],s)){
				printf("����ĳ��в��ڵ�·ͼ��,������ӳ��к��ٽ��в���\n");
				return ERROR;
			}
			else k = LocateVex_UDG(G,s);
			printf("��������Ҫ��ӵ�·�ĵڶ������е�����\n");
			scanf("%s",p);
			if(ERROR == LocateVex_UDG(G,p) && 0 != strcmp(G.vexs[0],p)){
				printf("����ĳ��в��ڵ�·ͼ��,������ӳ��к��ٽ��в���\n");
				return ERROR;
			}
			else m = LocateVex_UDG(G,p);
			printf("��������Ҫ��ӵ�·�ĳ���\n");
			scanf("%d",&info);
			if(OK == AddArc_UDG(G,k,m,info)){
				printf("��ӳɹ�\n");
				printf("��Ӻ�ĵ�·ͼΪ:\n");
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
			printf("��������Ҫɾ����·�ĵ�һ�����е�����\n");
			scanf("%s",s);
			if(ERROR == LocateVex_UDG(G,s) && 0 != strcmp(G.vexs[0],s)){
				printf("����ĳ��в��ڵ�·ͼ��,������ӳ��к��ٽ��в���\n");
				return ERROR;
			}
			else k = LocateVex_UDG(G,s);
			printf("��������Ҫɾ����·�ĵڶ������е�����\n");
			scanf("%s",p);
			if(ERROR == LocateVex_UDG(G,p) && 0 != strcmp(G.vexs[0],p)){
				printf("����ĳ��в��ڵ�·ͼ��,������ӳ��к��ٽ��в���\n");
				return ERROR;
			}
			else m = LocateVex_UDG(G,p);
			if(OK == RemoveArc_UDG(G,k,m))
				printf("ɾ���ɹ�\n");
			system("pause");	
			break;
		}
		case 5:printf("�˳��ò���\n");break; 
	}
}



//<descirbe>  sort
//<parameter> MGraph G
//<return >   OK
//
void Sort(MGraph G,ArcInfo *Edge)//���ϵ�Sort������������Edege�е�Ԫ�ذ�Ȩֵ��С�������������� ð������ 
{
	int i,j;//��¼���� 
	for(i=G.e-1;i>=0;i--)//���������ıȽ��յ� 
	{
		for(j=0;j<i;j++)//�������������ıȽ� 
		{
			if(Edge[j].info > Edge[j+1].info)//������ڣ�����λ�� 
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
	int Vexset[50];//������һ����������Vexset
	Sort(G,Edge);//����Ȩֵ����
	for(i=0;i<G.n;i++)//�������飬��ʾ�������Գ�һ����ͨ���� 
		Vexset[i] = i;
	int v1,v2,
		vs1,vs2;
	int sum = 0;
	printf("��³˹�����㷨ѡ�ߵ�˳������:\n");
	for(i=0;i<G.e;i++)//���β鿴����Edge�еı� 
	{
		v1 = LocateVex_UDG(G,Edge[i].v);//v1Ϊ�ߵ�ʼ����±�  ��λ���� 
		v2 = LocateVex_UDG(G,Edge[i].w);//v2Ϊ�ߵ��յ���±� 
		vs1 = Vexset[v1];//��ȡ��Edge[i]��ʼ�����ڵ���ͨ����vs1 
		vs2 = Vexset[v2];//��ȡ��Edge[i]���յ����ڵ���ͨ����vs2
		if(vs1 != vs2)//�ߵ��������������ͬ����ͨ���� 
		{
			printf("%s->%s  ",Edge[i].v,Edge[i].w);//�����ӡ�α� 
			sum = sum + Edge[i].info;
			for(j=0;j<G.n;j++)//�ϲ�vs1��vs2��������������������ͳһ��� 
				if(Vexset[j] == vs2)//���ϱ��Ϊvs2�Ķ���Ϊvs1 
					Vexset[j] = vs1;
		}
	}
	printf("�������Ϊ%d\n",sum);

} 



