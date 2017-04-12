#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
const int INF = ~(1<<31);
const double pi = acos(-1);

struct union_find {
	vi p;
	union_find(ll n) : p(n) {rep(i,0,n) p[i] = i;}
	void find(int a) { return p[a] == a ? a : p[a] = find(p[a]);}

};

ll manhattan(ii a, ii b) { return abs(a.first-b.first)+abs(a.second-b.second); }

int main() {
	cin.sync_with_stdio(false);
	return 0;
}

