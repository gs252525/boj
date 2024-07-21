#include <bits/stdc++.h>

using namespace std; 

const int MAXN = 5010; 

int adj[MAXN][MAXN]; 
int scc[MAXN]; 
int deg[MAXN]; 
int n; 

bool vis[MAXN*2]; 
stack<int> st; 
void dfs(int i){
  if(vis[i]) return; 
  vis[i] = 1; 
  if(i<=n){
    for(int j=1; j<=n; j++) if(j!=i && !adj[i][j] && !vis[j+n]) dfs(j+n); 
  }
  else {
    for(int j=1; j<=n; j++) if(j!=i-n && adj[i-n][j] && !vis[j]) dfs(j); 
  }
  st.push(i); 
}

void dfs1(int i, int pv){
  if(vis[i]) return; 
  vis[i] = 1; 
  scc[i] = pv; 
  if(i<=n){
    for(int j=1; j<=n; j++) if(j!=i && adj[i][j] && !vis[j+n]) dfs1(j+n,pv); 
  }
  else {
    for(int j=1; j<=n; j++) if(j!=i-n && !adj[i-n][j] && !vis[j]) dfs1(j,pv); 
  }
}

int main(void){
  ios_base::sync_with_stdio(false); 
  cin.tie(nullptr); 
  cout.tie(nullptr); 
  cin >> n; 
  int a = 0; 
  for(int i=1; i<=n; i++){
    int x; cin >> x; a+=x; 
    while(x--){
      int j; cin >> j; adj[i][j] = 1; 
    }
  }
  if(a==0 || a== n*(n-1)){
    cout << n; return 0; 
  }
  
  for(int i=1; i<=n*2; i++) if(!vis[i]) dfs(i); 
  for(int i=1; i<=n*2; i++) vis[i] = 0; 
  int pv = 0; 
  while(!st.empty()){
    int t = st.top(); st.pop(); if(!vis[t]) dfs1(t,pv++); 
  }
  vector<int> c, nc; 
  for(int i=1; i<=n; i++){
    if(scc[i]==scc[i+n]) {
      cout << 0; return 0; 
    }
    if(scc[i]<scc[i+n]) nc.push_back(i); 
    else c.push_back(i); 
  }
  assert(c.size()!=0 && nc.size()!=0); 
  for(auto x : c){
    //cerr << x << " ";
    for(auto y : nc){
      if(adj[x][y]) deg[x]++, deg[y]++; 
    }
  }
  int ans = 1; 
  for(auto n1 : c) if(deg[n1]==0) ans++; 
  for(auto n1 : nc) if(deg[n1]==c.size()) ans++; 
  for(auto n : c){
    for(auto nn : nc){
      int p = deg[n] - (int)adj[n][nn], q = deg[nn] - (int)adj[n][nn]; 
      if(p==0 && q==c.size()-1) ans++; 
    }
  }
  cout << ans;
}

