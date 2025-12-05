#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <map>
#include <string>
#include <vector>
using namespace std;

struct FileEntry {
    string filename;
    int count;
};

class InvertedIndex {
private:
    map<string, vector<FileEntry>> index;

public:
    void addTokens(const string& filename, const vector<string>& tokens);
    vector<FileEntry> search(const vector<string>& keywords);
};

#endif