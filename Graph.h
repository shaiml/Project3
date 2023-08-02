#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class Graph{
    // map<string, double> genre;
    // song, attributes <(danceability, 0.9), (energy, 0.4), (tempo, 100), (
    map<string, double> darktrap;
    map<string, double> undergroundrap;
    map<string, double> trapmetal;
    map<string, double> emo;
    map<string, double> rap;
    map<string, double> rnb;
    map<string, double> pop;
    map<string, double> hiphop;
    map<string, vector<pair<string, double>>> darktrapGraph;
    map<string, vector<pair<string, double>>> undergroungrapGraph;
    map<string, vector<pair<string, double>>> trapmetalGraph;
    map<string, vector<pair<string, double>>> emoGraph;
    map<string, vector<pair<string, double>>> rapGraph;
    map<string, vector<pair<string, double>>> rnbGraph;
    map<string, vector<pair<string, double>>> popGraph;
    map<string, vector<pair<string, double>>> hiphopGraph;

public:
    void ReadFile();
    void CreateGraph(map<string, vector<pair<string, double>>>& graph, map<string, double>& genre);
    // danceability, energy, tempo, genre, song_name
    vector<string> CreateConstantPlaylist(map<string, double>& genre, double energyLevel); //BFS
    vector<string> CreateRangePlaylist(map<string, double>& genre, double energyLevel); //DFS
};

void Graph::ReadFile() {
    fstream spotify;
    spotify.open("spotify_dataset.csv", ios::in);
    string firstLine;
    getline(spotify, firstLine);

    string line;
    while(getline(spotify, line)){
        string energy;
        string genre;
        string name;

        stringstream str(line);
        getline(str, energy, ',');
        getline(str, genre, ',');
        getline(str, name, ' ');

        if (genre == "Dark Trap"){
            darktrap[name] = stod(energy);
        }
        else if(genre == "Underground Rap"){
            undergroundrap[name] = stod(energy);
        }
        else if(genre == "Trap Metal"){
            trapmetal[name] = stod(energy);
        }
        else if(genre == "Emo"){
            emo[name] = stod(energy);
        }
        else if(genre == "Rap"){
            rap[name] = stod(energy);
        }
        else if(genre == "RnB"){
            rnb[name] = stod(energy);
        }
        else if(genre == "Pop"){
            pop[name] = stod(energy);
        }
        else if(genre == "Hiphop"){
            hiphop[name] = stod(energy);
        }
    }
    //CreateGraph(darktrapGraph, darktrap);
    //CreateGraph(undergroundrapGraph, undergroundrap);
    //CreateGraph(trapmetalGraph, trapmetal);
    //CreateGraph(emoGraph, emo);
    //CreateGraph(rapGraph, rap);
    //CreateGraph(rnbGraph, rnb);
    //CreateGraph(popGraph, pop);
    //CreateGraph(hiphopGraph, hiphop);
}

void Graph::CreateGraph(map<string, vector<pair<string, double>>> &graph, map<string, double> &genre) {
    for(auto it = genre.begin(); it != genre.end(); it++){
        for(auto iter = genre.begin(); it != genre.end(); it++){
            if (it->first != iter->first){
                double edgeWeight = abs(it->second - iter->second);
                if(edgeWeight <= 0.10){
                    graph[it->first].push_back(make_pair(iter->first, edgeWeight));
                }
                else { //make sure all songs are graphed even if they are disconnected
                    graph[it->first] = {};
                }
            }
        }
    }
}

vector<string> Graph::CreateConstantPlaylist(map<string, double> &genre, double energyLevel) {
    //BFS
}

vector<string> Graph::CreateRangePlaylist(map<string, double> &genre, double energyLevel) {
    //DFS
}
#endif //PROJECT3_GRAPH_H
