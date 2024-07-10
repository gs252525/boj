#include <bits/stdc++.h> 

using namespace std; 

int main(void) {
	int t; cin >> t; 
	for (int u = 1; u <= t; u++) {
		printf("Case #%d:\nYES\n", u); 
		int n; scanf("%d",&n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				printf("%d %d %d %d %d %d %d %d\n", j, i, i, j, 0, i, j, 1); 
			}
		}
	}
}