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

vi* adj;
bool* done;
int* owner;
int alternating_path(int left) {
  if (done[left]) return 0;
  done[left] = true;
  rep(i,0,size(adj[left])) {
    int right = adj[left][i];
    if (owner[right] == -1 ||
        alternating_path(owner[right])) {
      owner[right] = left; return 1; } }
  return 0; }

#define MAXN 5010
vi Adj[MAXN];
int color[5010],
    num[5010];

void dfs(int at) {
    iter(it,Adj[at]) {
        assert(color[*it] != color[at]);
        if (color[*it] == -1) {
            color[*it] = 1 - color[at];
            dfs(*it);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    memset(color,-1,sizeof(color));
    rep(i,0,m) {
        int a, b;
        cin >> a >> b;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }
    rep(i,0,n) {
        if (color[i] == -1) {
            color[i] = 0;
            dfs(i);
        }
    }
    int l = 0, r = 0;
    rep(i,0,n) {
        if (color[i] == 0) {
            num[i] = l++;
        } else {
            num[i] = r++;
        }
    }
    adj = new vi[l];
    rep(i,0,n) {
        if (color[i] == 0) {
            iter(it,Adj[i]) {
                adj[num[i]].push_back(num[*it]);
            }
        }
    }
    done = new bool[l];
    owner = new int[r];
    memset(owner,-1,sizeof(int)*r);
    int cnt = 0;
    rep(i,0,l) {
        memset(done,0,sizeof(bool)*l);
        cnt += alternating_path(i);
    }
    cout << cnt << endl;
    return 0;
}

