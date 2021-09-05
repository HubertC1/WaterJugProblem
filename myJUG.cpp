#include <stdio.h>
#include<stdlib.h>
#include <stack>


int n,m[6],t,data[1000000][7],qs=1,qe=1;
long long c[6];
const long long p1 = 51;
const long long prime = 1000003;
long long hashy;
int hash_table[prime][6]{};
/* 變數說明
   n: 量杯數
   m[6]: 各量杯之最大容量，m[0]沒用到
   t: 最終需求之水量
   data[10000][6]: 組合紀錄，data[i][0]: 表示可達到此組e合所需的步驟數，data[i][1..5]: 此組合中各量杯的水量
   qs: 要檢查是否有繼續變化不同組合的量杯現況（相當於queue要pop的hashy指標）
   qe: queue中目前的指標（相當於queue要push的hashy指標）
   c[6]: 由queue第qs個量杯水量組合變化出來的可能性組合，
         c[0]:表示可達到此組e合所需的步驟數，c[1..5]:此組合中各量杯的水量
           作法：先檢查queue 中是否已有此組合紀錄，若無則新增(push)至queue 中
*/

int check(int ind){ // 2->got the answer 1->not in queue 0->in queue
     // printf("%d\n",ind);
     bool diflag = 0;
     int sum = 0;
     for (int i = 1; i<=n; ++i){
          if (c[i] == t){ // 如果有符合目標數字
               return 2;
          }
     }
     int j = ind;
     do{
          if (j>=prime){ //如果超出hash table範圍
               j = 0;    //就從0開始繼續搜尋
          }
          sum = 0;
          diflag = 0; 
          for (int i = 1; i<=n; ++i){
               sum += hash_table[j][i];
               if (hash_table[j][i] != c[i]){
                    diflag = 1; //代表hash_table[j] 與 c 不一樣
                    break;
               }
          }
          if (diflag == 0){ 
               return 0;
          }
          if (sum == 0){ // 代表hash_table[j] = {0,0,0,0,0,0} -> c不存在hash_table中
               return 1;
          }
          j ++;
     }while (true);
}
     
void insert(int ind){
     bool zflag = 0;
     int j = ind;
     do{
          if (j>=prime){ // 若index超出限制就從0開始填
               j = 0;
          }
          zflag = 0; // 若hash_table[j] == {0,0,0,0,0,0} -> zflag = 1
          for (int i = 1; i<=n; ++i){
               if (hash_table[j][i] != 0){
                    zflag = 1;
                    break;
               }
          }
          if (zflag == 0){ // 可以填這裡了
               for (int i = 1; i<=n; ++i){
                    hash_table[j][i] = c[i];
               }
               return;
          }
          j ++;
     }while (true);
}

// int check()
// {
//      /* 檢查是否已達到所需求之水量
//         2: 已達到所需求之水量，可停止處理了；否則必須檢查queue中是否已有此c[1..5]組合紀錄
//         0: queue中已有此c[1..5]組合紀錄
//         1: queue中無此c[1..5]組合紀錄（必須push到queue中）
//      */

//      int i,j,flag;
//      for(i=1;i<=n;i++) if(c[i]==t) return 2;  // 已得到所需求之量了
//      for(i=1;i<=qe;i++)
//      {
//           flag = 0;
//           // for(j=1;j<=n;j++) if(c[j]!=data[i][j]) flag = 1;
//           for(j=1;j<=n;j++) 
//                if(c[j]!=data[i][j]) 
//                {   // 有不同的量杯水量，不是相同的組合（break後可繼續比對下一個queue值）
//                     flag = 1;
//                     break;
//                }
//           if(flag==0) return 0;  // 完全相同的量杯水量組合（不必再放到queue中了）
//      }
//      return 1; // queue中無此c[1..5]組合紀錄（必須push到queue中）
// }

int main()
{   printf("Hi I am HubertC1!!!\a\n");
     int i,j,k,re,flag=0,answer=-1;
     scanf("%d",&n);                                   // n: 量杯數
     for(i=1;i<=n;i++) scanf("%d",&m[i]);    // m[6]: 各量杯之最大容量，m[0]沒用到
     scanf("%d",&t);                                   // t: 最終需求之水量
     data[1][0] = 0;                                   // data[1][0]: 第0步驟
     for(i=1;i<=n;i++) data[1][i] = 0;       // data[1][1..n]: 初始量杯水量為0

    // 每次 pop queue中一個水量組合data[qs][0..n]來處理，若已到queue指標qe仍未找到需求水量，就必須放棄
     while(qs<=qe)
     {
          // printf("loop\n");
          /* 處理程序一：
             針對目前水量組合data[qs][0..n]，若有任何量杯未滿，則倒滿該量杯
             每倒滿一量杯，必須檢查新組合c[1..5]在queue中是否已有紀錄，若無，則必須push到queue中     
           */
          //full
          for(i=1;i<=n;i++)                                 // 針對每一量杯，檢查是否已滿
          {
               if(data[qs][i]<m[i])//if is not full
               {
                    for(j=1;j<=n;j++) c[j] = data[qs][j];  // 先以c[1..n]紀錄原量杯組合
                    c[i] = m[i]; 
                    hashy = (c[1]*p1%prime+c[2]*p1*p1%prime+c[3]*p1*p1*p1%prime+c[4]*p1*p1*p1*p1%prime+c[5]*p1*p1*p1*p1*p1%prime)%prime;                                  // 將量杯i倒滿
                    re = check(hashy);//check if exist           // 檢查新組合 c[1..n]
                    // printf("%d\n",re);
                    if(re==0) continue;                          // queue 中已有，丟掉此組合
                    // 發現新組合，push 到 queue 中 
                    // printf("%d %d %d %d %d \n",c[1],c[2],c[3],c[4],c[5]);
                    insert(hashy);
                    qe++;//insert
                    data[qe][6] = qs; // 紀錄predecessor
                    data[qe][0] = data[qs][0] + 1;               // 步驟加一步
                    for(j=1;j<=n;j++) data[qe][j] = c[j];
                    if(re==2)
                    {
                         flag = 1;
                         answer = data[qs][0] + 1;
                         break;
                    }
               }
          }
          if(flag==1) break;

          /* 處理程序二：
             針對目前水量組合data[qs][0..n]，嘗試把量杯i倒到量杯j
             每倒一次，必須檢查新組合c[1..5]在queue中是否已有紀錄，若無，則必須push到queue中  
           */
          //transform
          for(i=1;i<=n;i++)
          {
               for(j=1;j<=n;j++)
               {
                    // 嘗試把量杯i倒到量杯j，若i為空，或j已滿，或i==j就不必倒了
                    if(i==j||data[qs][i]==0||data[qs][j]==m[j]) continue;

                    // 把量杯i倒到量杯j
                    //transform i to j
                    for(k=1;k<=n;k++) c[k] = data[qs][k];        // 先以c[1..n]紀錄原量杯組合

                    
                    if(m[j]-data[qs][j]>=data[qs][i])//transform all
                    {  // 可以全部倒到量杯j
                         c[j] += c[i];
                         c[i] = 0;
                    }
                    else//transform not all
                    {  // 只能倒部分，到量杯j滿
                         // c[i] -= m[j] - data[qs][j];
                         c[i] = data[qs][i] + data[qs][j] - m[j] ;
                         c[j] = m[j];
                    }

                    // 檢查新組合 c[1..n]
                    hashy = (c[1]*p1%prime+c[2]*p1*p1%prime+c[3]*p1*p1*p1%prime+c[4]*p1*p1*p1*p1%prime+c[5]*p1*p1*p1*p1*p1%prime)%prime;
                    re = check(hashy);//check if exist
                    // printf("%d\n",re);
                    if(re==0) continue;                          // queue 中已有，丟掉此組合
                    // 發現新組合，push 到 queue 中 
                    // printf("%d %d %d %d %d \n",c[1],c[2],c[3],c[4],c[5]);
                    insert(hashy);
                    qe++;//insert
                    data[qe][6] = qs;
                    data[qe][0] = data[qs][0] + 1;               // 步驟加一步
                    for(k=1;k<=n;k++) data[qe][k] = c[k];
                    if(re==2)
                    {
                         flag = 1;
                         answer = data[qs][0] + 1;
                         break;
                    }
               }
               if(flag==1) break;
          }
          if(flag==1) break;

          /* 處理程序三：
             針對目前水量組合data[qs][0..n]，嘗試把量杯i倒掉
             每倒一次，必須檢查新組合c[1..5]在queue中是否已有紀錄，若無，則必須push到queue中  
           */
          //empty
          for(i=1;i<=n;i++)
          {
               if(data[qs][i]>0)//if not empty                   // 量杯非空，可倒掉
               {
                    for(j=1;j<=n;j++) c[j] = data[qs][j];   // 先以c[1..n]紀錄原量杯組合
                    c[i] = 0;
                    // 檢查新組合 c[1..n]
                    hashy = (c[1]*p1%prime+c[2]*p1*p1%prime+c[3]*p1*p1*p1%prime+c[4]*p1*p1*p1*p1%prime+c[5]*p1*p1*p1*p1*p1%prime)%prime;
                    re = check(hashy);//check if exist
                    // printf("%d\n",re);
                    if(re==0) continue;                          // queue 中已有，丟掉此組合
                    // 發現新組合，push 到 queue 中 
                    // printf("%d %d %d %d %d \n",c[1],c[2],c[3],c[4],c[5]);
                    insert(hashy);
                    qe++;//insert
                    data[qe][6] = qs;
                    data[qe][0] = data[qs][0] + 1;
                    for(k=1;k<=n;k++) data[qe][k] = c[k];
               }
          }
          qs++;    // pop queue下一個組合
          // printf("qs:%d qe:%d answer%d \n",qs,qe,answer);
     }
     if(answer<0)
          printf("%d 不可能做到\n",-1);
     else{
          printf("%d\n",answer);
          std::stack<int> stk;// 因為是逆推回去，所以用一個stack把他轉正
          int i = qe;
          while (i!=1){
               stk.push(i); 
               i = data[i][6];
          }
          int pre[6] = {0,0,0,0,0,0};
          int cur[6] = {0,0,0,0,0,0}; //這邊是要分析前後兩個狀態，來看是做什麼動作
          while (!stk.empty()){
               for (int i = 1; i<=n; ++i){ //顯把狀態印出來
                    printf("%3d/%3d|",data[stk.top()][i],m[i]);
               }
               int one = -1,two=-1; /*這兩個變數是在分析 current 與 previous 共有幾個不同之處
                                    one and two 分別紀錄哪兩個位子與先前不一樣，若只有一個不一樣，
                                    則two維持-1，並且代表有一個量杯全部倒掉或裝滿。反之，有一個量杯
                                    倒到另一個量杯。
                                    */
               for (int i = 1;i <=n; ++i){
                    cur[i] = data[stk.top()][i];
                    if (cur[i] != pre[i]){
                         if (one == -1){
                              one = i;
                         }else{
                              two = i;
                         }
                    }
               }
               if (two == -1){
                    if (cur[one] < pre[one]){// 代表這輪我們把在index one的量杯倒掉
                         printf("把%3d公升量杯內的水倒光\n",m[one]);
                    }else{ // 代表我們把在index one的量杯裝滿
                         printf("把%3d公升量杯內的水裝滿\n",m[one]);
                    }
               }else{
                    if (cur[one]<pre[one]){ // 代表我們把在index one量杯中的水倒到 index two
                         printf("把%3d公升量杯內的水倒到%3d公升量杯內\n",m[one],m[two]);
                    }else{// 代表我們把在index two 量杯中的水倒到index one
                         printf("把%3d公升量杯內的水倒到%3d公升量杯內\n",m[two],m[one]);
                    }
               }
               stk.pop();
               for (int i = 1; i<=n; ++i){
                    pre[i] = cur[i]; // 把cur 轉成 pre
               }
          }
     }
     system("pause");
}












