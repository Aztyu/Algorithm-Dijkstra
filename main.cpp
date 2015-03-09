/* 
 * File:   main.cpp
 * Author: Aztyu
 *
 * Created on 7 mars 2015, 18:35
 */

#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#include "Matrice.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    int nbre_lettre = 0;
    int depart = 1;
    
    cout << "Rentrez la taille de la matrice" << endl;
    cin >> nbre_lettre;
    
    Matrice matrix = Matrice(nbre_lettre);
    
    //init
    map<int, int> dist;
    map<int, int> pred;
    vector<int> fait;
    
    for(int i=0;i<nbre_lettre;i++){
        dist.insert(pair<int, int>(i, 0));
        pred.insert(pair<int, int>(i, depart-1));
    }
    
    for(map<int, int>::iterator it = dist.begin(); it != dist.end(); it++){
        int t_mat = matrix.GetValue(depart-1, (*it).first);
        if(matrix.GetValue(depart-1, (*it).first) >= 0 && matrix.GetValue(depart-1, (*it).first) != 100){
            (*it).second = matrix.GetValue(depart-1, (*it).first);
            pred[(*it).first] = depart-1;
        }else{
            (*it).second = 100;
            pred[(*it).first] = -1;
        }
    }
    
    cout << "process" << endl;
    
    fait.push_back(depart-1);
    
    //process
    while(fait.size() != dist.size()){
        //choisir xEV tel que
        vector<int> non_traite;
        for(map<int, int>::iterator it = dist.begin(); it != dist.end(); it++){ //On recupere tous les sommets non traites
            bool traite = false;
            for(int i=0; i<fait.size();i++){
                if(fait[i] == (*it).first){
                    traite = true;
                }
            }
            if(!traite){
                non_traite.push_back((*it).first);
            }
        }
        
        //On prends le minimum
        int min_point = 0;
        int min_value = 100;
        
        for(int i=0; i<non_traite.size(); i++){     //On cherche le minimum
            if(dist[non_traite[i]] < min_value){
                min_point = non_traite[i];
                min_value = dist[non_traite[i]];
            }
        }
        
        //Pour tout y successeur de x
        for(map<int, int>::iterator it = dist.begin(); it != dist.end(); it++){
            std::vector<int>::iterator it_v;
            it_v = find(non_traite.begin(), non_traite.end(), (*it).first);
            
            //Si il est non traite
            if(it_v != non_traite.end()){
                //Tri des successeurs du point
                if(matrix.GetValue(min_point, (*it).first) >= 0 && matrix.GetValue(min_point, (*it).first) != 100){
                    if(dist[(*it).first] > dist[min_point] + matrix.GetValue(min_point, (*it).first)){
                        (*it).second = dist[min_point] + matrix.GetValue(min_point, (*it).first);
                        pred[(*it).first] = min_point;
                    }
                    //pred[(*it).first] = min_point;
                }
            }
        }
        fait.push_back(min_point);
    }
    
    /*for(map<int, int>::iterator it = dist.begin(); it != dist.end(); it++){
        cout << (*it).first << ":" << (*it).second << endl;
    }
    
    cout << endl;
    for(map<int, int>::iterator it = pred.begin(); it != pred.end(); it++){
        cout << (*it).first << ":" << (*it).second << endl;
    }*/
    
    for(map<int, int>::iterator it = dist.begin(); it != dist.end(); it++){
        cout << IntToLetter((*it).first) << ":" << (*it).second << endl;
    }
    
    cout << endl;
    for(map<int, int>::iterator it = pred.begin(); it != pred.end(); it++){
        cout << IntToLetter((*it).first) << ":" << IntToLetter((*it).second) << endl;
    }
    return 0;
}

