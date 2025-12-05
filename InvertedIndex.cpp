#include "InvertedIndex.h"
#include <algorithm>
#include <set>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

void InvertedIndex::addTokens(const string& filename, const vector<string>& tokens) {
    map<string,int> freq;
    for (auto &w : tokens) freq[w]++;
    for (auto &p : freq) {
        index[p.first].push_back({ filename, p.second });
    }
}

vector<FileEntry> InvertedIndex::search(const vector<string>& keywords) {
    map<string,int> ranking;
    for (auto &k : keywords) {
        if (index.count(k)) {
            for (auto &e : index[k])
                ranking[e.filename] += e.count;
        }
    }

    vector<FileEntry> results;
    for (auto &p : ranking)
        results.push_back({ p.first, p.second });
    sort(results.begin(), results.end(),
         [](auto &a, auto &b){ return a.count > b.count; });

    return results;
}