#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "ParsedFile.h"
#include "InvertedIndex.h"
#include <map>
#include <vector>


using namespace std;
namespace fs = std::filesystem;

/* Function to read all files that are inside the directory that receives
int readFiles(const string& directory) {
    int counter = 0;

    // Interates through all the files in directory
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::ifstream file(entry.path());
            if (!file.is_open()) {
                std::cerr << "No se pudo abrir el archivo: " << entry.path() << '\n';
                continue;
            }
        counter++;
        
        /* Code to get file name: entry.path().filename().string()
        
           READ FILE WORD BY WORD
        
           while(file >> word) {
                ADD YOUR CODE
           }
        

        }
    }
    return counter;
}
*/
// file reader for option selecter 1-5
string readFullFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return "BAD FILE";
    stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}
int option;
vector<string> user_keywords;
string top1,top2,top3,top4,top5;
string temp;


int main() {
    // load directory index ( turn databases into inverted index)
    cout << "\n Loading directory index.. please wait..." << endl;

    string dir = "./moviesdb";
    vector<string> files;
    getdir(dir, files);
    InvertedIndex index;

    for (auto &f : files) {
        if (f[0] == '.') continue;

        string path = dir + "/" + f;
        ParsedFile pf(path);
        vector<string> tokens = pf.readAndTokenize();

        index.addTokens(path, tokens);
        cout << "Files loaded!: " << path << endl;
    }


    // user program start
    cout<< "\n\t----Description Search Engine-----\nSearch movies and books descriptions by keywords\nEnter keywords(| to end):" ;

    while(cin >> temp){ // will enter ekywords as long as user permits
        if (temp == "|") break;
        user_keywords.push_back(temp);
    }

    vector<FileEntry> results = index.search(user_keywords);

    cout << "\n\t----- Top 5  -----\n";

    int n = min(5, (int)results.size());
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". " << results[i].filename 
             << " (score=" << results[i].count << ")\n";
    }

    // if nothing with that keyword found, desplegar failure or empty, 
    if (n == 0) {
        cout << "No matching results.. quitting..\n";
        return 0;
    }

    // si encuentran related keywords
     cout << "\nChoose 1-" << n << " or 0 to quit: ";
     cin >> option;
    
     while (option < 0 || option > 5){
        cout << "Invalid option(has to be 1-5): ";
        cin >> option;
     }
    
     if (option == 0) { // quit if user enters 0
        cout << "Quitting.." << endl;
        return 0;
     }

     // selects options
     string selectedFile = results[option - 1].filename;

     // option printer
    cout << "\n\t-----RESULT-----\n";
    cout << selectedFile << "\n\n";
    cout << readFullFile(selectedFile) << "\n";

return 0;

    return 0;
}
