#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> arr[100100];
int D[100100];
void dfs(int x,int p){
  D[x]=D[p]^1;
  for(int y:arr[x])if(y!=p)
    dfs(y,x);
}

int dex;
int eex;

int imp(int x,int p){
  int res=0;
  int cnt=0;
  for(int y:arr[x])if(y!=p){
    int ii=imp(y,x);
    res=max(res,ii);
    if(ii)cnt++;
  }
  if(res>2)return 99;
  if(res==2){
    if(cnt>1 || x>=dex)return 99;
    return 2;
  }
  if(res==1){
    if(D[x]!=eex)return 1;
    return cnt;
  }
  if(x>=dex)return 1;
  return 0;
}

bool f(int j){
  for(int i=j;i<=n;i++){
    if(arr[i].size()<=1)
      return false;
    if(D[i]^D[n])
      return false;
  }
  dex=j;
  eex=D[n];
  int ii=imp(1,0);
  if(ii>2)return false;
  return n&1;
}

int main(){
  cin.tie(0);
  ios::sync_with_stdio(false);
  cin>>n;
  for(int i=1;i<n;i++){
    int x,y;cin>>x>>y;
    arr[x].push_back(y);
    arr[y].push_back(x);
  }
  dfs(1,0);
  int minj=0,maxj=n+1;
  for(int j;maxj-minj>1;f(j)?maxj=j:(minj=j))
    j=maxj+minj>>1;
  cout<<minj;
}