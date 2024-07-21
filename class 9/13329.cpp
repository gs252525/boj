#include <bits/stdc++.h> 
#include <array>

using namespace std; 

#define int long long 

int ccw(int x1, int y1, int x2, int y2, int x3, int y3){
  int L = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1); 
  return (L>0) - (L<0); 
}

struct line{
  int x1,y1,x2,y2; int idx; 
  line(int x1, int y1, int x2, int y2, int idx): x1(x1), y1(y1), x2(x2), y2(y2), idx(idx) {} 
  bool operator <(const line& t) const{
    vector<array<int,3>> v; 
    if(ccw(0,0,x1,y1,t.x1,t.y1)>=0) return ccw(x1,y1,t.x2,t.y2,t.x1,t.y1)>0;
    else return ccw(x1,y1,x2,y2,t.x1,t.y1)>0; 
  }
};

int chk[100100];

int32_t main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); 
  cout.tie(nullptr); 
  int n; cin >> n; 
  vector<array<int,4>> v; 
  vector<line> L; 
  for(int i=0; i<n; i++){
    int t; cin >> t; 
    vector<array<int,2>> tmp(t); 
    for(int j=0; j<t; j++) for(int k=0; k<2; k++) cin >> tmp[j][k]; 
    sort(tmp.begin(), tmp.end(), [](auto p1, auto p2){
      return ccw(0,0,p2[0],p2[1],p1[0],p1[1])>0; 
    }); 
    //cerr << i << " " << tmp[0][0] << " " << tmp[0][1] << " " << tmp[t-1][0] << " " << tmp[t-1][1] << endl;
    L.push_back(line(tmp[0][0],tmp[0][1],tmp[t-1][0],tmp[t-1][1],i)); 
    v.push_back({tmp[0][0],tmp[0][1],i,1}); 
    v.push_back({tmp[t-1][0],tmp[t-1][1],i,0}); 
  }
  sort(v.begin(),v.end(),[](auto p1, auto p2){
    return ccw(0,0,p2[0],p2[1],p1[0],p1[1])>0; 
  }); 
  //cerr << "fuck" << endl;
  set<line> S; 
  for(int i=0; i<n*2;){
    int j = i; 
    vector<int> add; 
    vector<int> erase; 
    while(j<n*2 && ccw(0,0,v[i][0],v[i][1],v[j][0],v[j][1])==0){
      auto [f,u,c,k] = v[j]; if(k==1) add.push_back(c); else erase.push_back(c); 
      j++;
    }
    if(!S.empty()) chk[(*S.begin()).idx] = 1; 
    for(auto ad : add) S.insert(L[ad]); 
    for(auto er : erase) S.erase(L[er]); 
    if(!S.empty()) chk[(*S.begin()).idx] = 1; 
    i = j;
  }
  int shit = 0; for(int i=0; i<n; i++) shit += chk[i]; 
  cout << n -   shit;
}