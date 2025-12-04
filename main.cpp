#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "ParsedFile.h"
#include "InvertedIndex.h"
#include <map>


using namespace std;
namespace fs = std::filesystem;

// Function to read all files that are inside the directory that receives
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
        */

        }
    }
    return counter;
}

int option;
vector<string> user_keywords;
string top1,top2,top3,top4,top5;


int main() {
    // load directory index ( turn databases into inverted index)




    // user program start
    cout<< "\n----Description Search Engine-----\n
            \tSearch movies and books descriptions by keywords
            \tEnter keywords:" ;

    while(cin >> temp){ // will enter ekywords as long as user permits
        if (temp == "|") break;
        user_keywords.push_back(temp);
    }

    // if nothing with that keyword found, desplegar failure or empty, 
    // si encuentran related keywords
     cout<< "\n----Top 5-----\n
            \t" << top1 << endl << top2 << endl << top3 << endl << top4 << endl << top5 << endl;
     cout << "Choose from 1-5, 0 to quit";
     cin << option;
     
     
     while (option < 0 || option > 5){
        cout << "Invalid option(has to be 1-5): ";
        cin << option;
     }
    
     if (option == 0) { // quit if user enters 0
        cout << "Quitting.." << endl;
        return 0;
     }

    return 0;
}
