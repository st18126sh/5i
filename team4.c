int team4(int ID,int n,int SC[2] , int *H)/*ID0の関数*/
{
  srand((unsigned)time(NULL));
  int random = (rand()%(100 - 0 + 1)) + 0;
  int percent = ;
  int Enemy_Last_Hand = *(h+2*n+ID);
  if(percent < random){
    int My_Next_Hand = Enemy_Last_Hand ;
  }
  else{
    int MY_Next_Hand = Enemy_Last_Hand ^ 1;
  }
  return My_Next_Hand;
}