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

class InvertedIndex {  // Clase que implementa un indice invertido que asocia palabras con los archivos donde aparecen sus frecuencias.
private:
    map<string, vector<FileEntry>> index;

public:
    void addTokens(const string& filename, const vector<string>& tokens);
    vector<FileEntry> search(const vector<string>& keywords);
};

#endif