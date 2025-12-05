#include "ParsedFile.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;




/*
   Muestra como invocar la funcion getdir para obtener los nombres de los 
   archivos del directorio. Luego muestra como crear un objeto tipo
   ParsedFile para luego obtener las palabras del archivo en un vector
   de strings.
*/

int main()
{
    string dir = string("./moviesdb");  // Nombre de directorio donde estan los archivos de pelicula.

    vector<string> files = vector<string>();

    getdir(dir,files);
	vector< map <string, int> > all_freq_tables;
	vector<string> filenames;
	
	
    for (unsigned int i = 0; i < files.size(); i++) {
    	if (files[i][0]!='.') {
    		string filepath = dir + "/" + files[i];  // Construye la ruta completa del archivo
			ParsedFile pf(filepath);

			vector<string> tokens = pf.readAndTokenize();

			map<string, int> freq;  // Tabla de frecuencias
			for(auto &w : tokens) {
				freq[w]++;
        }

			all_freq_tables.push_back(freq);  // Guarda la tabla de frecuencias en el vector.
			filenames.push_back(filepath);  // Guarda el nombre del archivo
    }
        
}
