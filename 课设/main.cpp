#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "./head.h"
# include <string>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc,char *argv[]) {
//	ArcInfo  arcs[19] = {
//	 {"广州","上海",1434},{"广州","深圳",135},{"广州","杭州",1257},{"广州","成都",1584},
//	 {"广州","北京",2127},{"广州","重庆",1287},{"深圳","重庆",1426},{"深圳","成都",1696},       
//	 {"杭州","重庆",1622},{"杭州","南京",278},{"南京","上海",299},{"南京","天津",893},
//	 {"北京","成都",1892},{"北京","上海",1217},{"北京","重庆",1758},{"北京","哈尔滨",1239},       
//	 {"西安","哈尔滨",2281},{"西安","成都",829},{"天津","哈尔滨",1231},   
//	};
//	VexType *city[11] = { "广州","北京","上海","南京","深圳","杭州","成都","重庆","西安","天津","哈尔滨"};
	int n = 11;
	MGraph G,T;
	//CreateGraph_UDG(G,city, 11, arcs, 19);
	//Save_data(G,arcs);
	int i,j;
	int sum;
	int tag = 0;
	//MGraph G,T;
	ArcInfo *arcs;
	int e = 19;
	while(true){
		system("cls");
		Meau_Main();
		int sel,loc;
		printf("请选择你的操作:\n");
		scanf("%d",&sel);
		switch(sel){
			case 1:{
				if(OK !=Create_Self(G,arcs))break;
				printf("城市图创建完成\n");
				tag = 1;
				print_Graph(G);
				printf("是否要把您所创建的城市图保存到本地\n");
				char s;
				scanf("%c",&s);
				if(s == 'y')Save_data(G,arcs);
				system("pause"); 
				break;
			}
			case 2:{
				tag = 1;
				Read_data(G,arcs);
				printf("数据导入成功\n");
				print_Graph(G);
				system("pause");
				break;
			}
			case 3:{
				if(tag == 0){
					printf("图还未创建,请创建再使用\n");
					system("pause");
					break;
				}
				printf("请输入你要开始的起点:\n");
				char *s = (char*)malloc(G.n * sizeof(char));
				scanf("%s",s);
				loc = LocateVex_UDG(G,s);
				if(ERROR == loc && 0!=strcmp(G.vexs[0],s)){
					printf("不存在该城市,请重新尝试\n");
					break;
				}
				Prim(G,loc,T);
				system("pause");
				break;
			}
			case 4:{
				if(tag == 0){
					printf("图还未创建,请创建再使用\n");
					break;
				}
				Kruskal(G,arcs);
				system("pause");
				break;
			}
			case 5:{
				if(tag == 0){
					printf("图还未创建,请创建再使用\n");
					break;
				}
				Call_function(G);
				break;
			}
			case 6:{
				DestroyGraph_UDG(G);
				exit(0);
				break;
			}
			default: continue;break;
			
		}
	}
	return 0;
}
