#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>

#define N 50 /* 試行回数 */
#define OID (id^1) /* 相手のid */
/*
 int sct[2][2]:点数表
 			自分	相手
 	[0][0]：	協調	協調
 	[0][1]：	協調	裏切り
 	[1][0]：	裏切り	協調
 	[1][1]：	裏切り	裏切り
 int *h:過去の手
        *(h+2*i+ID):i回目のIDの手
 int sc[2]:点数
 	sc[ID]:IDの点
 */

int main(void)
{
  int i,j,k,t,n = N,rh,er ;
  char c_name[2][255];
  int server_sockfd , client_sockfd[2] ;
  int server_len , client_len[2] ;
  struct sockaddr_un server_address ;
  struct sockaddr_un client_address[2] ;
  char ch[2] ={0,1} ;
  const int SCT[2][2]={{5,10},{0,2}};
  int *h; //int h[2][N];
  int sc[2]={0,0};
  FILE *LOG;

  LOG=fopen("ser_log","w");

  setbuf(stderr,NULL);
  
  // Initialize  
  srand((unsigned int)time(NULL));

  //calloc
  h=(int *)calloc(2*n,sizeof(int));


  for(i=0;i<n;i++){
    for(j=0;j<2;j++){
      *(h+(2*i+j))=-2;
    }
  }

  unlink("server_socket");

  server_sockfd = socket(AF_UNIX,SOCK_STREAM,0);
  server_address.sun_family = AF_UNIX ;
  strcpy(server_address.sun_path , "server_socket");
  server_len = sizeof(server_address);
  bind(server_sockfd , (struct sockaddr *)&server_address , server_len);

  listen(server_sockfd , 4);
  
  //printf("server waiting\n");

  for(i=0;i<2;i++){
    for(j=0;j<255;j++){
      c_name[i][j]=0;
    }
  }

  //  while(1) {
    for(i=0;i<2;i++){
      client_sockfd[i] = accept(server_sockfd, (struct sockaddr *)&(client_address[i]), &(client_len[i]));

      fprintf(stderr,"ser  %d er:[%d]\n",i, client_sockfd[i]);
      if(client_sockfd[i]<0){
	shutdown(client_sockfd[i],2);
	close(client_sockfd[i]);
	i--;
	continue;
      }

	  
      // receive the length of client name
      /*      do{
	sleep(1);
	er = recv(client_sockfd[i],&k,sizeof(int),2);
	fprintf(stderr,"\n %d:recv2[%d]\n",i,er);
      }while(er<=0);}*/
      er = recv(client_sockfd[i],&k,sizeof(int),0);

      // send the ID
      er = send(client_sockfd[i],&ch[i],1,0);
      //fprintf(stderr, "ser[%d]\n",er);	    

      // receive the client name
      er = recv(client_sockfd[i],(c_name[i]),k,0);      
	  
      // send the number of turn 
      send(client_sockfd[i],&n,sizeof(int),0);
      
    // send score table
      send(client_sockfd[i],SCT,sizeof(SCT),0);

    }
      /////////////////////////////////////////
    for(j=0;j<n;j++){
      for(i=0;i<2;i++){      
    // send score
	send(client_sockfd[i],sc,sizeof(sc),0);

    // send hand log
	send(client_sockfd[i],h,2*n*sizeof(int),0);

    // receive a hand
	recv(client_sockfd[i],&rh,sizeof(rh),0);//////////////////////
      
	*(h+(2*j+i))=rh;

      }
      for(k=0;k<2;k++){
	sc[k] += SCT[*(h+2*j+k)][*(h+2*j+(k^1))];
      }
      fprintf(LOG,"Turn %3d,h: %d %d, sc:%3d %3d,total: %3d %3d\n",j+1,*(h+(2*j)),*(h+(2*j+1)),SCT[*(h+2*j)][*(h+2*j+1)],SCT[*(h+2*j+1)][*(h+2*j)],sc[0],sc[1]);
    }  
    
    fprintf(LOG,"      %s : %s .\n",c_name[0],c_name[1]);
    fprintf(LOG,"score  %d : %d .\n",sc[0],sc[1]);
    fprintf(stderr,"\n THE END\n");

    shutdown(client_sockfd[i],2);
    close(client_sockfd[i]);
    

    // }
    fclose(LOG);
    return 0;  
}
