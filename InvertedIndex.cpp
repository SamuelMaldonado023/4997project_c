#include "InvertedIndex.h"
#include <algorithm>
#include <set>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;


/*
 Recibe el nombre de un archivo y un vector de tokes y calcula la frequencia de cada palabra.
 Y actualiza el indice invertido. Y conecta cada palabra con el archivo y su frecuencia.
*/
void InvertedIndex::addTokens(const string& filename, const vector<string>& tokens) {
    map<string,int> freq;  // Tabla de frequencias
    for (auto &w : tokens) freq[w]++;
    for (auto &p : freq) {
        index[p.first].push_back({ filename, p.second });
        
    }

    

}


/*
  Recibe un vector de palabras y devuelve una lista de archivos relevantes medidos por su indice.
  Si la busqueda es de una sola palabra devuelve los archivos ordenados por frecuencia de la palabra.
  Si la busqueda es de dos palabras devuelve primero los archivos que contengan ambas palabras. Ordenados por la suma de frecuencia
  Si no hay archivos que contengan ambas devuelve archivos que contenga almenos una de ellas.
*/
vector<FileEntry> InvertedIndex::search(const vector<string>& keywords) {
    vector<FileEntry> results_both, results_one;  // Vectores para archivos que contiene ambas o una de las palabras
    if(keywords.empty()){
        return {}; // Si no hay palabras devuelve vector vacio.
    }

    map<string,int> ranking;  // Acumula puntuacion por archivo
    for (auto &k : keywords) {  // Recorre las palabaras y acumula su frecuencia
        if (index.count(k)) {
            for (auto &e : index[k])
                ranking[e.filename] += e.count;
        }
        
    }


    
    for (auto &p : ranking){  // Clasifica si los archivos contienen ambas palabras o solo una
        const string& filename = p.first;
        int total_score = p.second;

    bool contains_everything = true; 

    if (keywords.size() > 1){  // Si hay mas de una palabra verifica si el archivo contiene ambas.
        for (const auto &k : keywords) {
            if(!index.count(k)){
                contains_everything = false;
                break;
            }

            bool found = false;
            for(const auto &e : index[k]){
                if(e.filename == filename){
                    found = true;
                    break;
                }
            }

            if(!found){
                contains_everything = false;
                break;
            }
        }  
    }

    if(contains_everything){  // Clasificar resultado basado en cuantas palabras hay en el archivo
        results_both.push_back({filename, total_score});
    }

    else{
        results_one.push_back({filename, total_score});
    }
    }

    // Si hay archivos con ambas palabras usa esos. Si no utiliza archivos que contenga almenos una palabra.
    vector<FileEntry> results = results_both.empty() ? results_one : results_both;


    // Ordena los resultados por relevancia. De frecuencia descendente
    sort(results.begin(), results.end(),
         [](auto &a, auto &b){ return a.count > b.count; });

    return results;  
}