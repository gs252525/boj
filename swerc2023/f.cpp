#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pii;
#define ff first
#define ss second
#define pb push_back

ll n, m;

vector<ll> v[1010101];
vector<pii> vs;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  ll t;
  cin >> t;
  while (t--) {
    ll ans = 0;
    cin >> n>>m;
    ll fl=0;

    for(ll i=1;i<=n;i++)
      v[i].clear();
    vs.clear();

    for(ll i=1;i<=m;i++){
      ll a,b;
      cin>>a>>b;
      v[a].pb(b);
      v[b].pb(a);
      vs.pb({a,b});
    }

    for(ll i=1;i<=n;i++){
      if(v[i].size()!=n-1){
        cout<<2<<'\n';
        for(auto k:vs){
          if(k.ff==i||k.ss==i) cout<<2<<' ';
          else cout<<1<<' ';
        }
        cout<<'\n';
        fl=1;
        break;
      }
    }
    if(fl==0){
      cout<<3<<'\n';
      for(auto k:vs){
          if(k.ff==1||k.ss==1){
            if(k.ff*k.ss==n) cout<<2<<' ';
            else cout<<3<<' ';
          }
          else cout<<1<<' ';
      }
    }
    
  }
}