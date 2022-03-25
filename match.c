/*  */
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define N 50 /* ���s�� */
#define OID (id^1) /* �����id */
#define CLIENT_0 "ID0" /* ���O */
#define CLIENT_1 "ID1"

/*
 int sct[2][2]:�_���\
 			����		����
 	[0][0]�F	����		����
 	[0][1]�F	����		���؂�
 	[1][0]�F	���؂�		����
 	[1][1]�F	���؂�		���؂�
 int *h:�ߋ��̎�
        *(h+2*i+ID):i��ڂ�ID�̎�
 int sc[2]:�_��
 	sc[ID]:ID�̓_
*/

/*
   ���̎���v�Z����֐��̃v���g�^�C�v�錾
   ���O�͉��ł��悢�B�������K�v�ɉ����ĕς��邱��
   ���̗�ł�
   ������ID�A������ڂ��A���݂܂ł̓_���A�ߋ��̎�̔z��
   ��n���Ă���B
*/
int play_0(int ID, int n,int SC[2] , int *H);/*ID0�̊֐�*/
int play_1(int ID, int n,int SC[2] , int *H);/*ID1�̊֐�*/
const int SCT[2][2]={{5,0},{10,2}}; /*�_���\*/

int main(void){
  int i,j,k,t,n = N,rh[2] ;
  char c_name[2][255];
 
  int *h; //int h[2][N];
  int sc[2]={0,0};
  FILE *LOG;

  LOG=fopen("log_tai","w");

  setbuf(stderr,NULL);
  
  // �������g���������ɔ����ď�����  
  //  srand((unsigned int)time(NULL));
    srand((unsigned int)19720117L);

  //calloc
  h=(int *)calloc(2*n,sizeof(int));

/////////////////////////////////////////
    for(j=0;j<n;j++){
		rh[0]=play_0(0, j, sc, h);
		rh[1]=play_1(1, j, sc, h);
    	
		for(k=0;k<2;k++){
			*(h+(2*j)+k)=rh[k];
			sc[k] += SCT[rh[k]][rh[k^1]];
		}
		fprintf(LOG,"Turn %3d,h: %d %d, sc:%3d %3d,total: %3d %3d\n",j+1,
			*(h+(2*j)),*(h+(2*j)+1),
			SCT[*(h+(2*j))][*(h+(2*j)+1)],SCT[*(h+(2*j)+1)][*(h+(2*j))],sc[0],sc[1]);
    }  
    
    fprintf(LOG,"      %s : %s .\n",CLIENT_0,CLIENT_1);
    fprintf(LOG,"score  %d : %d . %d\n",sc[0],sc[1],sc[0]+sc[1]);
    printf("      %s : %s .\n",CLIENT_0,CLIENT_1);
    printf("score  %d : %d . %d\n",sc[0],sc[1],sc[0]+sc[1]);
    fprintf(stderr,"\n THE END\n");

    fclose(LOG);
    return 0;  
}
/////////////////////////////////////////
/////////////////////////////////////////

int play_0(int ID,int n,int SC[2] , int *H)/*ID0�̊֐�*/
{
  int  t,i,j;
  
  if(ID == 0){
    t = rand() & 1;
  }
  
  if(ID == 1){
    t = (rand()>>1) & 1;
  }

  return t;
}

int play_1(int ID,int n,int SC[2] , int *H)/*ID1�̊֐�*/
{
  int  t,i,j;
  
  if(ID == 0){
    t = rand() & 1;
  }
  
  if(ID == 1){
    t = (rand()>>1) & 1;
  }

  return t;
}