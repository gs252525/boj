#include <bits/stdc++.h>

using namespace std; 

typedef long double ld; 

typedef pair<long double, long double> pl; 

pl p[200100]; 
ld sum[200100]; 

int n; 
pair<pl,int> get(ld l){
  int i=0;
  while(1){
    if(l>=sum[i]&&l<sum[i+1]) break; 
    i++; 
  }
  ld a = l-sum[i], b = sum[i+1]-l; 
  return {{a/(a+b),b/(a+b)},i}; 
}

ld area(vector<pl> &v){
  ld ans = 0; 
  int n = v.size(); 
  for(int i=0; i<v.size(); i++){
    ans += v[i].first * v[(i+1)%n].second - v[i].second * v[(i+1)%n].first; 
  }
  return abs(ans); 
}

ld fuck(ld l){
  auto gl = get(l); 
  auto gll = get(l+sum[n]/2.0); 
  vector<pl> v; 
  int i = gl.second; 
  pl s; 
  s.first = p[i].first * (gl.first.second) + p[i+1].first*(gl.first.first); 
  s.second = p[i].second * gl.first.second + p[i+1].second * gl.first.first; 
  v.push_back(s); 
  int j = gll.second; 
  pl e; 
  e.first = p[j].first * (gll.first.second) + p[j+1].first*(gll.first.first); 
  e.second = p[j].second * gll.first.second + p[j+1].second * gll.first.first; 
  for(int k=i+1; k<=j; k++)v.push_back(p[k]); 
  v.push_back(e); 
  return area(v); 
}


int main(void){
  ios::sync_with_stdio(false); 
  cin.tie(nullptr); 
  cout.tie(nullptr);
  cin >> n; 
  for(int i=0; i<n; i++){
    cin >> p[i].first >> p[i].second; 
  }
  p[n] = p[0]; 
  for(int i=1; i<=n; i++){
    sum[i] = sum[i-1] + sqrt((p[i%n].first-p[i-1].first)*(p[i%n].first-p[i-1].first) + (p[i%n].second-p[i-1].second)*(p[i%n].second-p[i-1].second)); 
  }
  ld l = 0, r = sum[n]/2; 
  vector<pl> v; for(int i=0; i<n; i++) v.push_back(p[i]); 
  ld S = area(v); 
  bool flag = true; // fuck(l) < S/2; 
  if(fuck(l) > S/2) flag = false; 
  ld m; 
  for(int i=0; i<450; i++){
    m = (l+r)/2; 
    ld ff = fuck(m); 
    if(abs(S/2 - ff)<1e-7) break; 
    if(fuck(m)>S/2) {
      if(flag) r = m; 
      else l = m;
    }
    else {
      if(flag) l = m; 
      else r = m; 
    }
  }
  cout << "YES\n"; 
  auto s = get(m), e = get(m+sum[n]/2); 
  cout << fixed; 
  cout << setprecision(8); 
  cout << s.second+1 << " " << s.first.first << "\n"; 
  cout << e.second+1 << " " << e.first.first; 
}