#include <bits/stdc++.h> 

using namespace std; 

typedef long long ll; 

const int MAXN = 500100; 

vector<pair<int,ll>> adj[MAXN]; 
vector<int> G[MAXN]; 
int par[20][MAXN]; 
ll dist[20][MAXN]; 
int h[MAXN]; 
int dfsn[MAXN], pv;
ll cost[MAXN]; 

void dfs(int v, int p){
  par[0][v] = p; 
  dfsn[v] = pv++; 
  for(auto& [ne,fuck]: adj[v]){
    if(ne==p) continue; 
    cost[ne] = cost[v] + fuck; 
    h[ne] = h[v]+1; 
    dist[0][ne] = fuck; 
    dfs(ne,v); 
  }
}

int lca(int u,int v){
  if(h[u]<h[v]) swap(u,v); 
  int diff = h[u]-h[v]; 
  for(int i=0; diff; i++){
    if(diff & 1) u = par[i][u];
    diff >>= 1;
  }
  if(u==v) return u; 
  for(int i=19; i>=0; i--) if(par[i][u]!=par[i][v]) u=par[i][u], v=par[i][v]; 
  return par[0][u];
}

int col[MAXN]; 
vector<int> shit; 
ll S[MAXN];
ll T[MAXN]; 
const ll inf = 2e18; 
int vis[MAXN]; 
void dfs2(int v){
  S[v] = inf, T[v] = inf; 
  vis[v] = 1; 
  if(col[v]==1) S[v] = 0; 
  if(col[v]==2) T[v] = 0; 
  for(auto& ne:G[v]){
    ll dist = abs(cost[ne]-cost[v]); 
    if(vis[ne]) continue; 
    dfs2(ne); 
    S[v] = min(S[v],dist+S[ne]); 
    T[v] = min(T[v],dist+T[ne]); 
  }
}

int main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); 
  cout.tie(nullptr); 
  int n,q; cin >> n >> q; 
  for(int i=0; i<n-1; i++){
    int a,b,d; cin >> a >> b >> d; adj[a].push_back({b,d}); adj[b].push_back({a,d}); 
  }
  dfs(0,0); 
  for(int i=1; i<20; i++){
    for(int j=0; j<n; j++) par[i][j] = par[i-1][par[i-1][j]], dist[i][j] = dist[i-1][j] + dist[i-1][par[i-1][j]]; 
  }
  while(q--){
    int s,t; cin >> s >> t; 
    vector<int> tmp; 
    for(int i=0; i<s; i++){
      int x; cin >> x; tmp.push_back(x); 
      col[x] = 1; 
    }
    for(int i=0; i<t; i++){
      int x; cin >> x; tmp.push_back(x); 
      col[x] = 2; 
    }
    sort(tmp.begin(),tmp.end(),[&](int i, int j){
      return dfsn[i]<dfsn[j];
    }); 
    for(int i=0; i<tmp.size()-1; i++) {
      shit.push_back(lca(tmp[i],tmp[i+1])); 
      shit.push_back(tmp[i]); if(i==tmp.size()-2) shit.push_back(tmp[i+1]); 
    }
    sort(shit.begin(),shit.end(),[&](int i, int j){
      return dfsn[i]<dfsn[j]; 
    }); 
    shit.erase(unique(shit.begin(),shit.end()),shit.end()); 
    for(int i=1; i<shit.size(); i++){
      int prv = lca(shit[i],shit[i-1]); 
      //ll dd = cost[shit[i]]-cost[prv]; 
      G[shit[i]].push_back(prv); 
      G[prv].push_back(shit[i]); 
    } 
    dfs2(shit[0]); 
    ll ans = inf; 
    for(auto& x : shit) ans = min(ans,S[x]+T[x]); 
    cout << ans << "\n"; 
    for(auto& s : shit) G[s].clear(), col[s] = 0, vis[s] = 0; 
    shit.clear();
  }
}