#include <bits/stdc++.h>

using namespace std; 

#define int long long 
typedef long double ld; 

struct line{
  int x1,y1,x2,y2; int id;
  line(){
    x1=y1=x2=y2=0; 
  }
  line(int x1, int y1, int x2, int y2, int id) : x1(x1), y1(y1), x2(x2), y2(y2), id(id) {
        if (x1 > x2) {
            swap(this->x1, this->x2);
            swap(this->y1, this->y2);
        }
  }
  ld get(int x) const {
    ld u = (ld)(y2-y1) / (x2-x1); 
    return u*(x-x1) + y1; 
  }

  bool operator < (const line& t) const {
    int x = max(x1,t.x1); 
    return get(x) < t.get(x); 
  }
};

struct fuck{
  int x, id, type; 
  fuck(int x, int id, int type): x(x), id(id), type(type) {}
};

int child[100020]; 

int32_t main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); cout.tie(nullptr); 
  int n; cin >> n; 
  vector<line> L; 
  vector<fuck> f; 
  for(int i=0; i<n; i++){
    int x1, y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2; 
    if(x1>x2) {
      swap(x1,x2); swap(y1,y2); 
    }
    L.push_back(line(x1,y1,x2,y2,i)); 
    f.push_back(fuck(x1,i,1)); 
    f.push_back(fuck(x2,i,0)); 
  }
  sort(f.begin(),f.end(),[](auto a, auto b){
    return a.x < b.x;
  }); 
  set<line> s;
  for(int i=0; i<n*2;){ 
    int j = i; 
    vector<int> add; vector<int> erase; 
    while(j<n*2 && f[j].x==f[i].x){
      int x = f[j].x, id = f[j].id, t = f[j].type; 
      // 0 erase
      // cerr << x << " " << id << " " << t << endl;
      if(t==0) erase.push_back(id); 
      else add.push_back(id); 
      j++;
    }
    //cerr << i<< " " << j << endl;
    for(auto ad : add) s.insert(L[ad]); 
    for(auto ad : add){
      if(L[ad].y1 < L[ad].y2){
        auto it = s.find(L[ad]); 
        if(it == s.begin()) child[ad] = -1; 
        else child[ad] = (*prev(it)).id;
      }
    }
    for(auto er : erase){
      if(L[er].y2 < L[er].y1){
        auto it = s.find(L[er]); 
        if(it == s.begin()) child[er] = -1; 
        else child[er] = (*prev(it)).id;
      }
    } 
    for(auto er : erase) s.erase(L[er]); 
    i = j; 
  }
  int x; cin >> x; 
  ld M = -1e20; int idx = -1; 
  for(int i=0; i<n; i++){
    //cerr << i << " " << child[i] << endl;
  }
  for(int i=0; i<n; i++){
    if(L[i].x1 <=x && x <= L[i].x2 && L[i].get(x) > M){
      M = L[i].get(x); idx = i; 
    }
  }
  if(idx==-1) cout << x; 
  else {
    while(child[idx]!=-1) idx = child[idx]; 
    int ans = L[idx].y1 > L[idx].y2 ? L[idx].x2 : L[idx].x1;
    cout << ans; 
  }
}