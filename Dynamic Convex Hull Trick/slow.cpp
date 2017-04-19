#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = (a); i < (b); i++)
#define iter(it,c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end();++it)
typedef pair<double,double> dd;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = ~(1<<31);
const double pi = acos(-1);

struct dynamic_convex_hull_trick {
	vector<dd> arr;
	void add(double m, double b) { arr.push_back(dd(m,b)); } 
	double get_min(double x, int i=0) {return i==arr.size()?INFINITY:min(arr[i].first*x+arr[i].second,get_min(x,i+1));} 
};

int main() {
	cin.sync_with_stdio(false);
	int n;
	cin >> n;
	dynamic_convex_hull_trick con;
	rep(i,0,n) {
		int op;
		cin >> op;
		if(op == 1) {
			double a,b;
			cin >> a >> b;
			con.add(a,b);
		} else {
			double x;
			cin >> x;
			cout << setprecision(15) << fixed << con.get_min(x) << endl;
		}
	}
	return 0;
}

