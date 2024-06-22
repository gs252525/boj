struct BCC{
  int N, pv=0; 
  int cnt = 0; 
  vector<int> included; 
  vector<int> dfsn; 
  vector<vector<int>> BCC_V; 
  vector<vector<pair<int,int>>> BCC_E; 
  stack<pair<int,int>> st; 
  vector<vector<int>> adj; 
  BCC(int N): N(N) {
    adj.resize(N+1);
    included.resize(N+1); 
    dfsn.resize(N+1); 
  } 
  
  void addEdge(int a, int b){
    adj[a].pb(b); adj[b].pb(a); 
  }
  
  int dfs(int cur, int p){
    int re = dfsn[cur] = ++pv; 
    for(auto ne : adj[cur]){
      if(ne==p) continue; 
      
      if(dfsn[ne]<dfsn[cur]) st.push({cur,ne}); 
      if(dfsn[ne]!=0) re = min(re, dfsn[ne]); 
      else {
        int tmp = dfs(ne,cur); 
        re = min(re, tmp); 
        if(tmp >= dfsn[cur]){
          included[cur]++; 
          vector<int> V; 
          vector<pair<int,int>> E; 
          while(1){
            auto tt = st.top(); 
            st.pop(); 
            V.pb(tt.ff); 
            V.pb(tt.ss); 
            E.pb(tt); 
            if(tt==make_pair(cur,ne)) break; 
          }
          sort(all(V));
          V.erase(unique(all(V)),V.end()); 
          BCC_V.pb(V); 
          BCC_E.pb(E); 
        }
      }
    }
    return re;
    
  }
  void build(){
    rep(i,N) if(dfsn[i]==0) dfs(i,i); else included[i]++; 
  }
  
  bool chk_cactus(){
    for(int i=0; i<BCC_V.size(); i++){
      if(BCC_V[i].size()>=3){
        if(BCC_E[i].size()!=BCC_V[i].size()) return false; 
      }
    }
    vector<int> cnt(N,0); 
    for(int i=0; i<BCC_V.size(); i++){
      if(BCC_V[i].size()>=3){
        for(auto x : BCC_V[i]) cnt[x]++; 
      }
    }
    rep(i,N) if(cnt[i]>=2) return false; 
    return true; 
  }
};