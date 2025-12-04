#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

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
string userkeys,top1,top2,top3,top4,top5;

int main() {
   
    // How you send the file name dependes of where your executable file is
    //int amount_of_files = readFiles("books_description_files");
    //cout << "The amount of files in directory is: " << amount_of_files << "\n";

    cout<< "\n----Description Search Engine-----\n
            \tSearch movies and books descriptions by keywords
            \tEnter keywords:" ;

    cin >> userkeys;

    // if nothing with that keyword found, desplegar failure or empty, 
    // si encuentran related keywords
     cout<< "\n----Top 5-----\n
            \t" << top1 << endl << top2 << endl << top3 << endl << top4 << endl << top5 << endl;
     cout << "Choose from 1-5, 0 to quit";
     cin << option;
     if (option == 0) break;
     else // display filename chosen and description
            

    return 0;
}
