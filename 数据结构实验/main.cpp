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
		printf("������Ĳ�����\n");
		scanf("%d",&num);
		switch(num){
			case 1:{
				VexType *vexs;
				ArcInfo *arcs;
				int i;
				int e,n;
				printf("��������Ҫ�����Ķ�����\n");
				scanf("%d",&n);
				printf("��������Ҫ�����ı���\n");
				scanf("%d",&e);
				// ���ٿռ�
				vexs = (VexType*)malloc(n*sizeof(VexType));
				arcs = (ArcInfo*)malloc(e*sizeof(ArcInfo)); 
				
				for (i = 0; i < n; i++){
					printf("�������%d���������Ϣ\n",i);
					scanf(" %c", &vexs[i]);
				}
				
				for (i = 0; i < e; i++) { 
				printf("�밴˳������ߵ���������Ԫ�ص�ֵ(�ַ���)\n");
				scanf(" %c %c", &arcs[i].v, &arcs[i].w); 
				arcs[i].info = 1;
				 }
				CreateGraph_UDG(G,vexs,n,arcs,e);
				// make the graph
				init = TRUE;
				break;
			}
			case 2:{
				//  ȡ����k��ֵ��w���� 
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				int k;
				printf("��������Ҫ��õĶ����λ��\n");
				scanf("%d",&k);
				VexType w;
				GetVex_UDG(G,k,w);
				break;
			}
			case 3:{
				// �Զ���k��ֵw
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				int k;
				VexType w;
				printf("��������Ҫ�޸ĵĶ���λ��\n");
				scanf("%d",&k);
				printf("����������Ҫ��ֵ��ֵ");
				scanf("%c",&w);
				PutVex_UDG(G,k,w);  
				break;
			}
			case 4:{
				// �󶥵�k�ĵ�һ���ڽӶ��� 
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				int k;
				int loc;
				printf("��������Ҫ��ѯ�Ķ�����\n");
				scanf("%d",&k);
				if(ERROR == FirstAdjVex_UDG(G,k))printf("����ʧ��\n");
				else{
					loc = FirstAdjVex_UDG(G,k);
					printf("��һ���ڽӶ����λ��Ϊ%d",loc);
				}
				break;
			}
			case 5:{
				// �󶥵�k����һ���ڽӶ��� 
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				int k,m;
				int loc;
				printf("������k�����λ��\n");
				scanf("%d",&k);
				//
				printf("������m�����λ��\n");
				scanf("%d",&m);
				if(ERROR == NextAdjVex_UDG(G,k,m))printf("����ʧ��\n");
				else{
					loc = NextAdjVex_UDG(G,k,m);
					printf("��һ���ڽӶ����λ��Ϊ%d",loc);
				}
				break;
			}
			case 6:{
				//  ����k��m�ı�
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				int k,m;
				printf("������k�����λ��\n");
				scanf("%d",&k);
				printf("������m�����λ��\n");
				scanf("%d",&m);
				if(ERROR == AddArc_UDG(G,k,m))printf("�ñ��Ѵ��ڣ�����ʧ��\n");
				else
					printf("����ɹ�\n");
				break;
			}
			case 7:{
				//  ɾ��k��m�ı�
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				int k,m;
				printf("������k�����λ��\n");
				scanf("%d",&k);
				printf("������m�����λ��\n");
				scanf("%d",&m);
				if(ERROR == RemoveArc_UDG(G,k,m))printf("�ñ߲����ڣ�ɾ��ʧ��\n");
				else
					printf("ɾ���ɹ�\n");
				break;
			}
			case 8:{
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				if(ERROR == DFSTraverse_UDG(G,visit))
					printf("����ʧ��\n");
				else
					printf("�����ɹ�\n");
				break;
			}
			case 9:{
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				if(ERROR == BFSTraverse_UDG(G,visit))
					printf("����ʧ��\n");
				else
					printf("�����ɹ�\n");
				break;
			}
			case 0:{
				if(init == FALSE){
					printf("ͼ��û�д��������ȴ���ͼ\n");
					break;
				}
				if(ERROR == DestroyGraph_UDG(G))printf("ɾ��ʧ��\n");
				else
					printf("ɾ�������ٳɹ�");
				exit(0);
				break;
			} 
		}
		system("pause"); 
	} 
	
	
	return 0;
}
