#ifndef _DFA_H_
#define _DFA_H_
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <iostream>

struct dfa {
    int n, start;
    std::map<int,int> *trans;
    std::set<int> term;
    dfa(int _n = 0, int _start = 0) : n(_n), start(_start) {
        trans = new std::map<int,int>[n];
    }
    dfa(const dfa &other) {
        n = other.n;
        start = other.start;
        term = other.term;
        trans = new std::map<int,int>[n];
        for (int i = 0; i < n; i++) trans[i] = other.trans[i];
    }
    ~dfa() {
        delete[] trans;
    }
    dfa& operator=(const dfa &other) {
        delete[] trans;
        n = other.n;
        start = other.start;
        term = other.term;
        trans = new std::map<int,int>[n];
        for (int i = 0; i < n; i++) trans[i] = other.trans[i];
        return *this;
    }
    void add_trans(int from, int label, int to) {
        assert(trans[from].find(label) == trans[from].end());
        trans[from][label] = to;
    }
    void add_term(int st) {
        term.insert(st);
    }
};

dfa input_dfa(std::istream &in) {
    int n, m, start, terms;
    in >> n >> m >> start >> terms;
    dfa res(n,start);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        in >> a >> b >> c;
        res.add_trans(a,b,c);
    }
    for (int i = 0; i < terms; i++) {
        int x;
        in >> x;
        res.add_term(x);
    }
    return res;
}

void output_dfa(std::ostream &out, const dfa &x) {
    std::vector<std::pair<std::pair<int,int>, int> > edges;

    for (int i = 0; i < x.n; i++) {
        for (auto it = x.trans[i].begin(); it != x.trans[i].end(); it++) {
            edges.push_back({{i,it->second},it->first});
        }
    }

    out << x.n << " " << edges.size() << " " << x.start << " " << x.term.size() << std::endl;
    for (size_t i = 0; i < edges.size(); i++) {
        out << edges[i].first.first << " " << edges[i].second << " " << edges[i].first.second << std::endl;
    }
    for (auto it = x.term.begin(); it != x.term.end(); ++it) {
        out << *it << std::endl;
    }
}
#endif
