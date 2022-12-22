#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include "./head.h"
# include <string>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc,char *argv[]) {
//	ArcInfo  arcs[19] = {
//	 {"����","�Ϻ�",1434},{"����","����",135},{"����","����",1257},{"����","�ɶ�",1584},
//	 {"����","����",2127},{"����","����",1287},{"����","����",1426},{"����","�ɶ�",1696},       
//	 {"����","����",1622},{"����","�Ͼ�",278},{"�Ͼ�","�Ϻ�",299},{"�Ͼ�","���",893},
//	 {"����","�ɶ�",1892},{"����","�Ϻ�",1217},{"����","����",1758},{"����","������",1239},       
//	 {"����","������",2281},{"����","�ɶ�",829},{"���","������",1231},   
//	};
//	VexType *city[11] = { "����","����","�Ϻ�","�Ͼ�","����","����","�ɶ�","����","����","���","������"};
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
		printf("��ѡ����Ĳ���:\n");
		scanf("%d",&sel);
		switch(sel){
			case 1:{
				if(OK !=Create_Self(G,arcs))break;
				printf("����ͼ�������\n");
				tag = 1;
				print_Graph(G);
				printf("�Ƿ�Ҫ�����������ĳ���ͼ���浽����\n");
				char s;
				scanf("%c",&s);
				if(s == 'y')Save_data(G,arcs);
				system("pause"); 
				break;
			}
			case 2:{
				tag = 1;
				Read_data(G,arcs);
				printf("���ݵ���ɹ�\n");
				print_Graph(G);
				system("pause");
				break;
			}
			case 3:{
				if(tag == 0){
					printf("ͼ��δ����,�봴����ʹ��\n");
					system("pause");
					break;
				}
				printf("��������Ҫ��ʼ�����:\n");
				char *s = (char*)malloc(G.n * sizeof(char));
				scanf("%s",s);
				loc = LocateVex_UDG(G,s);
				if(ERROR == loc && 0!=strcmp(G.vexs[0],s)){
					printf("�����ڸó���,�����³���\n");
					break;
				}
				Prim(G,loc,T);
				system("pause");
				break;
			}
			case 4:{
				if(tag == 0){
					printf("ͼ��δ����,�봴����ʹ��\n");
					break;
				}
				Kruskal(G,arcs);
				system("pause");
				break;
			}
			case 5:{
				if(tag == 0){
					printf("ͼ��δ����,�봴����ʹ��\n");
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
