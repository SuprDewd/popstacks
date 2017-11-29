#include "lib/dfa.hpp"
using namespace std;
template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef long long ll;
const int INF = 2147483647;

map<ii,int> id;
set<int> accept;
vector<pair<ii,int> > edges;
int dfs(const dfa &a, const dfa &b, int x, int y) {

    auto it = id.find({x,y});
    if (it != id.end()) return it->second;
    int cur_id = size(id);
    id[ii(x,y)] = cur_id;

    if (a.term.find(x) != a.term.end() && b.term.find(y) != b.term.end()) {
        accept.insert(cur_id);
    }

    iter(it,a.trans[x]) {
        if (b.trans[y].find(it->first) == b.trans[y].end()) continue;
        int nxt_id = dfs(a, b, it->second, b.trans[y][it->first]);
        edges.push_back({{cur_id, nxt_id}, it->first});
    }

    return cur_id;
}

int main() {
    dfa a = input_dfa(cin),
        b = input_dfa(cin);
    int init = dfs(a, b, a.start, b.start);

    cout << size(id) << " " << size(edges) << " " << init << " " << size(accept) << endl;
    iter(it,edges) {
        cout << it->first.first << " " << it->second << " " << it->first.second << endl;
    }
    iter(it,accept) {
        cout << *it << endl;
    }

    return 0;
}

