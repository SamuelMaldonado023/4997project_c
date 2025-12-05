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

/* 
*/

// Recibe el nombre de un archivo y devuelve el contenido como un string.
string readFullFile(const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return "BAD FILE";
    stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}
int option;  // Opcion de usuario
vector<string> user_keywords;  // Input de usuario
string temp;  // Variable temporal para leer input


int main() {

    // -----load directory index ( turn databases into inverted index)
    cout << "\n Loading directory index.. please wait..." << endl;

    // Carga base de datos de peliculas
    string dir = "./moviesdb";
    vector<string> files;
    getdir(dir, files);  // Consigue lista de archivos
    InvertedIndex movieindex;

    for (auto &f : files) {
        if (f[0] == '.') continue;  // Ignora archivos ocultos

        string path = dir + "/" + f;
        ParsedFile pf(path);  // Objeto para leer y tokenizar los archivos
        vector<string> tokens = pf.readAndTokenize();

        movieindex.addTokens(path, tokens);
        //cout << "Files loading..(" << f << "/" << files << ")" << endl;
    }

    // Carga base de datos de libros
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

    while(true){  // Loop que permite que el usuario haga multiples busquedas.
        user_keywords.clear();
        cout << "\nSearch movies and books descriptions by keywords\nEnter keywords(| to end, 'quit' to exit): " ;

        while(cin >> temp){ // Lee los inputs del usuario
            if (temp == "|") break;  // Fin de input del usuario
            if (temp == "quit") {
            cout << "Quitting program...";
            return 0;
        }
            user_keywords.push_back(standardize(temp));  // Estandariza las palabras
    }

        if(user_keywords.empty()){
            cout << "There were no keywords entered. Please try again \n";
            continue;  // Pedira los inputs otra vez
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

        cerr << "User keywords: ";
for (auto &k : user_keywords) cerr << "[" << k << "]";
cerr << endl;

        // book printer
        cout << "\nBooks (4–6):\n";
        for (int i = 0; i < bookN; i++) {
            cout << (i+4) << ". " << bookResults[i].filename 
                << " (score=" << bookResults[i].count << ")\n";
        }

        int maxOption = movieN + bookN;

        if (maxOption == 0) {
            cout << "No matching results. Please try again...\n";
            continue;
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
