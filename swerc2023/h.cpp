#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
ll n, m;
ll arr[1010101];
ll brr[1010101];
ll idx[1010101];

ll tree[1010101];

ll upt(ll idx, ll val, ll s, ll e, ll nod) {
  // cout<<idx<<' '<<val<<' '<<s<<' '<<e<<' '<<nod<<'\n';
  if (idx < s || idx > e)
    return tree[nod];
  if (s == e) {
    return tree[nod] = 1;
  }
  ll m = (s + e) / 2;
  return tree[nod] = upt(idx, val, s, m, nod * 2) +
                     upt(idx, val, m + 1, e, nod * 2 + 1);
}

ll qry(ll l, ll r, ll s, ll e, ll nod) {
  if (r < s || e < l)
    return 0;
  if (l <= s && e <= r)
    return tree[nod];
  ll m = (s + e) / 2;

  return qry(l, r, s, m, nod * 2) + qry(l, r, m + 1, e, nod * 2 + 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  ll t;
  cin >> t;
  while (t--) {
    ll ans = 0;
    cin >> n;

    for (ll i = 1; i <= n; i++) {
      ll x;
      cin >> x;
      idx[x] = i;
    }
    for (ll i = 1; i <= n; i++) {
      ll x;
      cin >> x;
      upt(idx[x], 1, 1, n, 1);

      // for(ll j=1;j<=4*n;j++){
      //   cout<<tree[j]<<' ';
      // }
      // cout<<'\n';

      //cout << i << ' ' << x << ' ' << idx[x] << ' ' << qry(1, idx[x], 1, n, 1)<< '\n';
      if (qry(1, idx[x], 1, n, 1) != idx[x])
        ans++;
    }

    for (ll i = 1; i <= 8 * n; i++) {
      tree[i] = 0;
      idx[i] = 0;
    }
    cout << ans << '\n';
  }
}