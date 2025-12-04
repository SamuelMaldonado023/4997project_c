#include "ParsedFile.h"
#include <map>




/*
   Muestra como invocar la funcion getdir para obtener los nombres de los 
   archivos del directorio. Luego muestra como crear un objeto tipo
   ParsedFile para luego obtener las palabras del archivo en un vector
   de strings.
*/

int main()
{
    string dir = string("./moviesdb");
    vector<string> files = vector<string>();

    getdir(dir,files);
	vector< map <string, int> > all_freq_tables;
    for (unsigned int i = 0;i < files.size();i++) {
    	if (files[i].c_str()[0]!='.') {
    		string tmp;
    		cout <<  "./moviesdb/" + files[i] << endl;        
        }
    }
        
}
