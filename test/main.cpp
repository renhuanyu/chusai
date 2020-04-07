
#include<cstdio>
#include<vector>
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<set>
#include<ctime>
#include<stack>
#include <initializer_list>
#include <unordered_map>
using namespace std;

const int maxn = 30000;

vector<vector<int> > G(maxn);
vector<vector<int> > G_reverse(maxn);
int path_flag[maxn];
int vis[maxn];
int bfs_flag[maxn];
int minn = 30000, maxx = 1;
int first_node;
vector<int> path;
vector<vector<int> > all_path;
set<int> s;
int cntt = 0;
bool cmp(vector<int> a , vector<int> b){
      int  len_a = a.size();
        int  len_b = b.size();
        if(len_a < len_b)      return true;
        else if(len_a > len_b) return false;
        else{
               for(int i = 0;i < len_a;i++){
                       if(a[i] < b[i])      return true;
                       else if(a[i] > b[i]) return false;
                      else                 continue;
                   }
          }
    
       return false;
}

vector<int> temp;
vector<int> low_to_high;

void dfs(int   v , int  depth){
        if(vis[v] == 1)                     return;
    
    
       path_flag[v] = 1;
       path.push_back(v);
    
        int len_next;
        len_next = G[v].size();
        for(int i = 0;i < len_next;i++){
        int next_v = G[v][i];
        if(G[v][i] != first_node && path_flag[G[v][i]] == 1)   {continue;}
        //if(G[v][i] <  first_node || bfs_flag[G[v][i]] != 1)    {continue;}
        if(G[v][i] == first_node){//出现环
            if(path.size() == 2) continue;
            //                     int cnt = path.size();
            //                     int value = 0;
            //                     for(int j = 0;j < cnt;j++)
            //                          value = 10*value + path[j];
            //
            //
            //                     if(s.find(value) == s.end()){//第一次找到这个环
            //                             s.insert(value);
            //                             all_path.push_back(path);//insert to vector<vector>;
            //                         }
            cntt++;
            continue;
        }
        if(depth < 7 && next_v > first_node  && bfs_flag[next_v] == 1)
                     dfs(G[v][i] , depth + 1);
          }
    
      path.pop_back();
      path_flag[v] = 0;
    
    return;
}


int main(){
    
     string infile_name = "/Users/apple/test_data_1.txt";//输入文件
       ifstream readFile(infile_name);
    
       string line;
       vector<int> num;
       s.clear();
       clock_t input_star  , input_end;
       input_star = clock();
    
       while(getline(readFile , line)){
               stringstream ss;
               ss << line;//一行的字符串 存在line中
        
               int index1 , index2;
               int len = line.length();
               int cnt = 0;
               for(int i = 0;i < len;i++){
                       if(line[i] == ',' && cnt == 0) {cnt++;index1 = i;continue;}
                       if(line[i] == ',' && cnt == 1) {index2 = i;break;}
                   }
        
               string stemp1 , stemp2;
               stemp1 = line.substr(0 , index1 );
               stemp2 = line.substr(index1 + 1 , index2 - index1 - 1);
               int temp1 , temp2;
        
               temp1 = stoi(stemp1);
               temp2 = stoi(stemp2);
               minn = min(temp2, min(minn , temp1));
               maxx = max(temp2 ,max(maxx , temp1));
              // printf("%d %d\n" , temp1 , temp2);
               //G_check[temp1][temp2] = 1;
               G[temp1].push_back(temp2);
              G_reverse[temp2].push_back(temp1);
          }
    
        input_end = clock();
        cout << "input time: " <<(double)(input_end - input_star) / CLOCKS_PER_SEC << "s" << endl;
    
        clock_t dfs_star , dfs_end;
        dfs_star = clock();
    
    
    //递归dfs
        vector<int> queue;
        int queue_len , node_len ,step_index;
        for(int i = minn;i <= maxx;i++){//寻找以节点i为起点的所有环
        
                //剪枝准备
                memset(bfs_flag, 0, sizeof(int));
                int cnt;
        
                queue.clear();
                queue.push_back(i);
                queue_len = 0;
                cnt = 3;
                while(cnt--){
                    step_index = queue_len;       //一步到达
                    queue_len = queue.size();
                    for(int j = step_index;j < queue_len;j++){
                            node_len = G[queue[j]].size();
                            //printf(" node_len = %d ",&node_len);
                            for(int k = 0;k < node_len;k++)
                                queue.push_back(G[queue[j]][k]);
                        }
                  }
                queue_len = queue.size();
                for(int j = 0;j < queue_len;j++){
                        if(bfs_flag[queue[j]] == 0)
                              bfs_flag[queue[j]]++;
                    }
        
                queue_len = queue.size();
        //        for(int j = 0;j < queue_len;j++)//标记输出
        //            printf("%d " , queue[j]);
        //        printf("\n");
        
        
                queue.clear();
                queue.push_back(i);
                queue_len = 0;
                cnt = 3;
                while(cnt--){
                        step_index = queue_len;       //一步到达
                        queue_len = queue.size();
                        for(int j = step_index;j < queue_len;j++){
                                node_len = G_reverse[queue[j]].size();
                                //printf(" node_len = %d ",&node_len);
                                for(int k = 0;k < node_len;k++)
                                        queue.push_back(G_reverse[queue[j]][k]);
                            }
                    }
                queue_len = queue.size();
                for(int j = 0;j < queue_len;j++){
                        if(bfs_flag[queue[j]] == 0)
                               bfs_flag[queue[j]]++;
                    }
        
                queue_len = queue.size();//标记输出
        //        for(int j = 0;j < queue_len;j++)
        //            printf("%d " , queue[j]);
        //        printf("\n");
                first_node = i;
        path.clear();
                dfs(i , 1);
                vis[i] = 1;
            }
    
    
    
    
        dfs_end = clock();
        cout << "dfs time: " <<(double)(dfs_end - dfs_star) / CLOCKS_PER_SEC << "s" << endl;
    
        int lenn = all_path.size();
    
        clock_t sort_star , sort_end;
        sort_star = clock();
        sort(all_path.begin(), all_path.end(), cmp);
        sort_end = clock();
       // cout << "sort time: " <<(double)(sort_end - sort_star) / CLOCKS_PER_SEC << "s" << endl;
    //        for(int i = 0;i < lenn;i++){
    //                int lennn = all_path[i].size();
    //                for(int j = 0;j < lennn;j++)
    //                        printf("%d " , all_path[i][j]);
    //                printf("\n");
    //            }
    //          printf("%d\n" , lenn);
    printf("%d\n"  , cntt);
    
}

