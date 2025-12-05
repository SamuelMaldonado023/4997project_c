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

    // -----load directory index ( turn databases into inverted index)
    cout << "\n Loading directory index.. please wait..." << endl;

    // load movies
    string dir = "./moviesdb";
    vector<string> files;
    getdir(dir, files);
    InvertedIndex movieindex;

    for (auto &f : files) {
        if (f[0] == '.') continue;

        string path = dir + "/" + f;
        ParsedFile pf(path);
        vector<string> tokens = pf.readAndTokenize();

        movieindex.addTokens(path, tokens);
        //cout << "Files loading..(" << f << "/" << files << ")" << endl;
    }

    // load books
    dir = "./books_description_files";
    getdir(dir, files);
    InvertedIndex bookindex;
    for (auto &f : files) {
        if (f[0] == '.') continue;

        string path = dir + "/" + f;
        ParsedFile pf(path);
        vector<string> tokens = pf.readAndTokenize();

        bookindex.addTokens(path, tokens);
        //cout << "Files loading..(" << f << "/" << files << ")" << endl;
    }

    // ----user program start-----
    cout<< "\n\t----Description Search Engine-----\n";

    while(true){  // Loop to allow user to keep performing searches.
        user_keywords.clear();
        cout << "\nSearch movies and books descriptions by keywords\nEnter keywords(| to end, 'quit' to exit): " ;

        while(cin >> temp){ // will enter keywords as long as user permits
            if (temp == "|") break;
            if (temp == "quit") {
            cout << "Quitting program...";
            return 0;
        }
            user_keywords.push_back(temp);
    }

        if(user_keywords.empty()){
            cout << "There were no keywords entered. Please try again \n";
            continue;  // Will ask for keywords again
        }
    

        // ----- AFTER USER results----
        vector<FileEntry> movieResults = movieindex.search(user_keywords);
        vector<FileEntry> bookResults  = bookindex.search(user_keywords);

        cout << "\n\t----- Top Hits -----\n";

        int movieN = min(3, (int)movieResults.size());
        int bookN  = min(3, (int)bookResults.size());

        // move printer
        cout << "\nMovies (1–3):\n";
        for (int i = 0; i < movieN; i++) {
            cout << i+1 << ". " << movieResults[i].filename 
                << " (score=" << movieResults[i].count << ")\n";
        }

        // book printer
        cout << "\nBooks (4–6):\n";
        for (int i = 0; i < bookN; i++) {
            cout << (i+4) << ". " << bookResults[i].filename 
                << " (score=" << bookResults[i].count << ")\n";
        }

        int maxOption = movieN + bookN;

        if (maxOption == 0) {
            cout << "No matching results.. quitting..\n";
            return 0;
        }

    //------- user option input --------
        cout << "\nChoose 1-" << maxOption << " or 0 to quit: ";
        cin >> option;

        while (option < 0 || option > maxOption) {
            cout << "Invalid option(has to be 1-" << maxOption << "): ";
            cin >> option;
        }

        if (option == 0) {
            cout << "Quitting.." << endl;
            return 0;
        }

        // ------- option selection output-----
        string selectedFile;

        if (option <= movieN) {
            // movies 1–3
            selectedFile = movieResults[option - 1].filename;
        }
        else {
            // books 4–6
            int bookIndexSelected = option - movieN - 1; 
            selectedFile = bookResults[bookIndexSelected].filename;
        }

        // -------- search engine results -------
        cout << "\n\t-----RESULT-----\n";
        cout << selectedFile << "\n\n";
        cout << readFullFile(selectedFile) << "\n";


    }
}
