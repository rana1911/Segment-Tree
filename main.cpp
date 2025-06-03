#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;

class segTree {
public:
	vector<int> seg;
	segTree(int n){
		seg.resize(4*n + 1);
	}

	void build(int idx, int low, int high, vector<int> &v){
		if(low == high){
			seg[idx] = v[low];
			return;
		}
		int mid = (low + high) >> 1;

		build(2*idx + 1, low, mid, v);
		build(2*idx + 2, mid + 1, high, v);
		int sbits = __builtin_popcount(high - low);
		if(sbits&1) seg[idx] = (seg[2*idx + 1] | seg[2*idx + 2]);
		else seg[idx] = (seg[2*idx + 1] ^ seg[2*idx + 2]);
	}

	int query(){
		return seg[0];
	}

	void update(int idx, int low, int high, int i, int val){
		if(low == high){
			seg[idx] = val;
			return;
		}

		int mid = (low + high) >> 1;
		if(i <= mid) update(2*idx + 1, low, mid, i, val);
		else update(2*idx + 2, mid + 1, high, i, val);
		int sbits = __builtin_popcount(high - low);
		if(sbits&1) seg[idx] = (seg[2*idx + 1] | seg[2*idx + 2]);
		else seg[idx] = (seg[2*idx + 1] ^ seg[2*idx + 2]);
	}
};

int32_t main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> v(n + 1), pref(n + 1);
	for(int i = 1; i <= n; i++){
		cin >> v[i];
		pref[i] = pref[i-1] + v[i];
	}
	int m;
	cin >> m;
	while(m--){
		int i, j;
		cin >> i >> j;
		int mn = min((pref[j - 1] - pref[j - i]), (pref[j] - pref[j - i + 1]));
		cout << v[j] + mn << '\n';
	}
}
