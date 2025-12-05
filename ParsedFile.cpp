/*
   ParsedFile.cpp
   
   Este archivo contiene implementaciones para funciones miembro
   de la clase ParsedFile y algunas otras funciones.
*/


#include "ParsedFile.h"

/* Funcion miembro readAndTokenize
   Esta funcion abre el archivo y lee cada linea y la tokeniza en palabaras.
   Devuelve un vector con todas las palabras.
*/
vector<string> ParsedFile::readAndTokenize() {
  	string line;
  	ifstream myfile (name.c_str());
	vector<string> result;
 
 	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			// for every line in the file, tokenize and store
			// to a vector of strings.
			vector<string> tokenized_line = tokenize(line, " "); 
			for(uint i=0; i<tokenized_line.size(); i++)
				result.push_back(tokenized_line[i]);
		}
		myfile.close();
	}

	return result;
}

string standardize(const string& w){  // Funcion que convierte strings a minusculas y elimina caracteres no alfabeticos.
    string out;
    for(char c : w) {
        if(isalpha(c)){ 
        out.push_back(tolower(c));
        }
    }
    return out;
}

/* Recibe un string y un delimitador y los divide en plabras
   Luego devuelve un vector con las palabras. (Las palabras ya estan estandarizadas.)
*/
vector<string> tokenize(const string& str, const string& delim) {
    vector<string> tokens;
    size_t p0 = 0, p1;

    while ((p1 = str.find_first_of(delim, p0)) != string::npos) {  // Busca delimitadores y extrae palabras.
        if (p1 > p0) {
            string stand_ = standardize(str.substr(p0, p1 - p0));
            if(!stand_.empty()){
                tokens.push_back(stand_);  // PUSH REAL WORD
            }
        }
        p0 = p1 + 1;
    }

    // Procesa la ultima palabra si existe.
    if (p0 < str.size()){
        string stand_ = standardize(str.substr(p0));
        if(!stand_.empty()){
            tokens.push_back(stand_);
        }
    }

        // Caso especial por si no encontro token pero la linea no esta vacia
        if(!str.empty() && tokens.empty()){
            string stand_ = standardize(str);

            if(!stand_.empty()){
                tokens.push_back(stand_);
            }
        }
    
    return tokens;
}

/*Recibe un nombre de directorio y devuelve un vector con los
  nombres de todos los archivos contenidos en el. 
*/ 
int getdir (string dir, vector<string> &files){  
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


