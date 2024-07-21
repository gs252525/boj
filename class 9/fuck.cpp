#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string.h>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()

using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;
int n, m;
vector<p> _a, _b, a, b;
ll mx;

void f(int s, int e, int l, int r)
{   
    
    if(s > e) return;
    int m = s + e >> 1;
    ll ret = -4e18, k = s;
    cerr << a[m].x << " " << a[m].y << endl;
    for(int i=l; i<=r; i++)
    {   cerr << "wtf??? "<< b[i].x << " " << b[i].y << endl;
        ll dx = b[i].x - a[m].x;
        ll dy = b[i].y - a[m].y;
        ll now = (dx < 0 && dy < 0) ? 0 : dx * dy;
        if(now > ret) ret = now, k = i;
    }
    cerr << s << " " <<e << " " << l << " " << ret << endl; 
    f(s, m-1, l, k); f(m+1, e, k, r);
    mx = max(mx, ret);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m; _a.resize(n), _b.resize(m);
    for(auto &i : _a) cin >> i.x >> i.y; sort(all(_a));
    for(auto &i : _b) cin >> i.x >> i.y; sort(all(_b), greater<p>());
    a.reserve(n), b.reserve(m);
    for(auto i : _a) if(a.empty() || a.back().y > i.y) a.push_back(i);
    for(auto i : _b) if(b.empty() || b.back().y < i.y) b.push_back(i);
    reverse(all(b));
    f(0, a.size()-1, 0, b.size()-1);
    cout << mx;
    return 0;
}
