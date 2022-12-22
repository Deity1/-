#include <stdio.h>
#include <stdlib.h>
#include "./head.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	MGraph G;
	int status = TRUE;
	int init = FALSE;
	int loc;
	char a;
	test_function();
	system("pause");
	while(status){
		system("cls");
		meau();  // print the meau
		int num;
		printf("输入你的操作数\n");
		scanf("%d",&num);
		switch(num){
			case 1:{
				VexType *vexs;
				ArcInfo *arcs;
				int i;
				int e,n;
				printf("请输入你要创建的顶点数\n");
				scanf("%d",&n);
				printf("请输入你要创建的边数\n");
				scanf("%d",&e);
				// 开辟空间
				vexs = (VexType*)malloc(n*sizeof(VexType));
				arcs = (ArcInfo*)malloc(e*sizeof(ArcInfo)); 
				
				for (i = 0; i < n; i++){
					printf("请输入第%d个顶点的信息\n",i);
					scanf(" %c", &vexs[i]);
				}
				
				for (i = 0; i < e; i++) { 
				printf("请按顺序输入边的两个顶点元素的值(字符型)\n");
				scanf(" %c %c", &arcs[i].v, &arcs[i].w); 
				arcs[i].info = 1;
				 }
				CreateGraph_UDG(G,vexs,n,arcs,e);
				// make the graph
				init = TRUE;
				break;
			}
			case 2:{
				//  取顶点k的值到w当中 
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				int k;
				printf("请输入你要获得的顶点的位序\n");
				scanf("%d",&k);
				VexType w;
				GetVex_UDG(G,k,w);
				break;
			}
			case 3:{
				// 对顶点k赋值w
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				int k;
				VexType w;
				printf("请输入你要修改的顶点位序\n");
				scanf("%d",&k);
				printf("请你输入你要赋值的值");
				scanf("%c",&w);
				PutVex_UDG(G,k,w);  
				break;
			}
			case 4:{
				// 求顶点k的第一个邻接顶点 
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				int k;
				int loc;
				printf("请输入你要查询的顶点数\n");
				scanf("%d",&k);
				if(ERROR == FirstAdjVex_UDG(G,k))printf("查找失败\n");
				else{
					loc = FirstAdjVex_UDG(G,k);
					printf("第一个邻接顶点的位序为%d",loc);
				}
				break;
			}
			case 5:{
				// 求顶点k的下一个邻接顶点 
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				int k,m;
				int loc;
				printf("请输入k顶点的位序\n");
				scanf("%d",&k);
				//
				printf("请输入m顶点的位序\n");
				scanf("%d",&m);
				if(ERROR == NextAdjVex_UDG(G,k,m))printf("查找失败\n");
				else{
					loc = NextAdjVex_UDG(G,k,m);
					printf("第一个邻接顶点的位序为%d",loc);
				}
				break;
			}
			case 6:{
				//  增加k到m的边
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				int k,m;
				printf("请输入k顶点的位序\n");
				scanf("%d",&k);
				printf("请输入m顶点的位序\n");
				scanf("%d",&m);
				if(ERROR == AddArc_UDG(G,k,m))printf("该边已存在，插入失败\n");
				else
					printf("插入成功\n");
				break;
			}
			case 7:{
				//  删除k到m的边
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				int k,m;
				printf("请输入k顶点的位序\n");
				scanf("%d",&k);
				printf("请输入m顶点的位序\n");
				scanf("%d",&m);
				if(ERROR == RemoveArc_UDG(G,k,m))printf("该边不存在，删除失败\n");
				else
					printf("删除成功\n");
				break;
			}
			case 8:{
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				if(ERROR == DFSTraverse_UDG(G,visit))
					printf("遍历失败\n");
				else
					printf("遍历成功\n");
				break;
			}
			case 9:{
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				if(ERROR == BFSTraverse_UDG(G,visit))
					printf("遍历失败\n");
				else
					printf("遍历成功\n");
				break;
			}
			case 0:{
				if(init == FALSE){
					printf("图还没有创建，请先创建图\n");
					break;
				}
				if(ERROR == DestroyGraph_UDG(G))printf("删除失败\n");
				else
					printf("删除并销毁成功");
				exit(0);
				break;
			} 
		}
		system("pause"); 
	} 
	
	
	return 0;
}
