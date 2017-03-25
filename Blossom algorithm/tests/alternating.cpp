#include <bits/stdc++.h>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = 2147483647;

#define MAXN 5010
vi adj[MAXN];
bool vis[MAXN],
     matched[MAXN][MAXN];
int mate[MAXN];

bool augment(int at) {
    if (vis[at]) return false;
    iter(it,adj[at]) {
        if (vis[*it]) continue;
        if (mate[*it] == -1) {
            if (mate[at] != -1) {
                mate[mate[at]] = -1;
                mate[at] = -1;
            }
            mate[*it] = at;
            mate[at] = *it;
            return true;
        }
        vis[at] = true;
        vis[*it] = true;
        if (augment(mate[*it])) {
            assert(mate[*it] == -1);

            if (mate[at] != -1) {
                mate[mate[at]] = -1;
                mate[at] = -1;
            }

            mate[*it] = at;
            mate[at] = *it;

            vis[*it] = false;
            vis[at] = false;
            return true;
        }
        vis[*it] = false;
        vis[at] = false;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(matched,0,sizeof(matched));
    memset(mate,-1,sizeof(mate));
    memset(vis,0,sizeof(vis));
    rep(i,0,m) {
        int a, b;
        cin >> a >> b;
        if (a == b) continue;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int cnt = 0;
    while (true) {
        bool found = false;
        rep(i,0,n) {
            if (mate[i] == -1 && augment(i)) {
                cnt++;
                found = true;
            }
        }
        if (!found) {
            break;
        }
    }
    cout << cnt << endl;

    return 0;
}

