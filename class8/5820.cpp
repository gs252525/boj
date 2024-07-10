#include <bits/stdc++.h> 

using namespace std; 

#define rep(i,n) for(int i=0; i<n; i++)
#define rrep(i,n) for(int i=1; i<=n; i++)
#define all(v) (v).begin(), (v).end(); 
#define pb push_back 

const int MAXN = 200100; 

int vis[MAXN]; 
int k; 
int n; 

vector<pair<int,int>> adj[MAXN]; 
int sz[MAXN]; 

const int inf = 1e9; 
vector<int> tmp; 
int min_len[2000000]; 

int get_size(int x, int p){
  sz[x] = 1; 
  for(auto [ne,d] : adj[x]){
    if(ne!=p && vis[ne]==0) sz[x] += get_size(ne,x); 
  }
  return sz[x]; 
}

int get_cnt(int x, int p, int s){
  for(auto [ne,d] : adj[x]){
    if(ne!=p && vis[ne]==0 && sz[ne]>s) return get_cnt(ne,x,s); 
  }
  return x; 
}

int ans = 1e9; 

vector<pair<int,int>> tmp1; 
void dfs(int v, int p, int dist, int st){
  if(dist>k) return; 
  //cerr << "fuck" << endl; 
  //cerr << v << " " << p << " " << dist << " " << st << endl; 
  if(min_len[k-dist]!=inf){
    ans = min(ans, st+min_len[k-dist]);  
    //cerr << "wtf???" << " " << k-dist << endl; 
    //cerr << tmp[k-dist] << " " << st << endl; 
  } 
  tmp1.pb({dist,st}); 
  for(auto& [ne,d] : adj[v]){
    if(ne!=p && vis[ne]==0){
      dfs(ne,v,dist+d,st+1); 
    }
  }
}


void solve(int i){
  int s = get_size(i,i); 
  int cnt = get_cnt(i,i,s/2); 
  //cerr << cnt << endl; 
  for(auto &ne : tmp) min_len[ne] = inf; 
  min_len[0] = 0; 
  tmp.clear(); 
  for(auto [ne,d] : adj[cnt]){
    if(vis[ne]) continue; 
    dfs(ne,cnt,d,1); 
    for(auto& [dist,st] : tmp1) min_len[dist] = min(min_len[dist],st), tmp.pb(dist); 
    //for(auto& [dist,st] : tmp1) cerr << "sthit" << dist <<" " << st << " " << min_len[dist] << endl; 
    tmp1.clear(); 
  }
  vis[cnt] = 1; 
  for(auto& [ne,d]:adj[cnt]){
    if(!vis[ne]) solve(ne); 
  }
} 

int main(void){
  cin >> n; 
  cin >> k; 
  for(int i=0; i<=k; i++) min_len[i] = inf; 
  rep(i,n-1){
    int a,b,l; cin >> a >> b >> l; 
    adj[a].pb({b,l}); 
    adj[b].pb({a,l}); 
  }
  solve(0); 
  cout << (ans == 1e9 ? -1 : ans); 
  return 0; 
}



