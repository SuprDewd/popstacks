#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = 2147483647;

int k = 3;
// vii forb = {{127,73},{28,20},{8,0}};
// vii forb = {{61455,36873},{15420,9252},{4080,2448},{960,576},{384,0}};
vii forb;
int w = 0;

unordered_map<int,int> id;
vector<pair<ii,int> > edges;
int found = 0,
    cnt = 1;
int dfs(int mat) {
    if (mat & (1<<w)) {
        return found;
    }

    auto it = id.find(mat);
    if (it != id.end()) return it->second;
    int cur_id = (id[mat] = cnt++);

    rep(t,0,1<<k) {
        int nxt = 1<<0;
        rep(i,0,w) {
            if (~mat & (1<<i)) continue;

            int mask = 0,
                want = 0;
            rep(j,0,k) {
                mask |= ((forb[j].first>>i)&1)<<j;
                want |= ((forb[j].second>>i)&1)<<j;
            }

            if ((t & mask) == want) {
                nxt |= 1<<(i+1);
            }
        }
        int nxt_id = dfs(nxt);
        edges.push_back({{cur_id,nxt_id},t});
    }
    return cur_id;
}

int main(int argc, char* argv[]) {
    k = atoi(argv[1]);

    rep(i,0,k) {
        int a, b;
        cin >> a >> b;
        forb.push_back({a,b});
    }

    rep(i,0,k) {
        int tmp = forb[i].first,
            cur = 0;
        while (tmp) {
            cur++;
            tmp >>= 1;
        }
        w = max(w, cur);
    }

    int init = dfs(1<<0);
    rep(t,0,1<<k) edges.push_back({{found,found},t});

    cout << cnt << " " << size(edges) << " " << init << " " << cnt-1 << endl;
    iter(it,edges) {
        cout << it->first.first << " " << it->second << " " << it->first.second << endl;
    }
    rep(i,1,cnt) {
        cout << i << endl;
    }

    return 0;
}

