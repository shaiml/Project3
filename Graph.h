#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <set>
#include <queue>
#include <stack>
#include <cstdlib>
#include <random>
#pragma once

using namespace std;
class Graph{
    // map<string, float> genre;
    // genre, energy level, song name
    map<string, float> darktrap;
    map<string, float> undergroundrap;
    map<string, float> trapmetal;
    map<string, float> emo;
    map<string, float> rap;
    map<string, float> rnb;
    map<string, float> pop;
    map<string, float> hiphop;

    map<string, vector<pair<string, float>>> darktrapGraph;
    map<string, vector<pair<string, float>>> undergroundrapGraph;
    map<string, vector<pair<string, float>>> trapmetalGraph;
    map<string, vector<pair<string, float>>> emoGraph;
    map<string, vector<pair<string, float>>> rapGraph;
    map<string, vector<pair<string, float>>> rnbGraph;
    map<string, vector<pair<string, float>>> popGraph;
    map<string, vector<pair<string, float>>> hiphopGraph;

public:
    void ReadFile();
    void CreateGraph(map<string, vector<pair<string, float>>>& graph, map<string, float>& genre);
    vector<pair<string, float>> CreateConstantPlaylist(string genre, int playlistSize, int energy); //BFS
    vector<pair<string, float>> ConstantPlaylistHelper(map<string, vector<pair<string,float>>> &graph, map<string, float> &map, int playlistSize, int energy);
    vector<pair<string, float>> CreateRangePlaylist(string genre, int playlistSize, int energy1, int energy2); //DFS
    vector<pair<string, float>> RangePlaylistHelper(map<string, vector<pair<string,float>>>& graph, map<string, float>& map, int playlistSize, int energy1, int energy2);
    map<string, vector<pair<string, float>>> CheckGraph(string genre);
    map<string, float> CheckMap(string genre);
    string RandomSongHelper(map<string, float> &genre, int energy);
};


void Graph::ReadFile() {
    ifstream spotify;
    spotify.open("../spotify_dataset.csv", ios::in);

    string firstLine;
    getline(spotify, firstLine);
    string line;

    while(!spotify.eof()){
        getline(spotify, line);
        string genre;
        string energy;
        string name;

        stringstream str(line);
        getline(str, genre, ',');
        getline(str, energy, ',');
        getline(str, name, '\n');


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
    spotify.close();
}

void Graph::CreateGraph(map<string, vector<pair<string, float>>> &graph, map<string, float> &genre) {
    map<string, vector<pair<string, float>>> tempGraph;
    for(auto it = genre.begin(); it != genre.end(); it++){
        //cout << it->first;
        for(auto iter = genre.find(it->first); iter != genre.end(); iter++){
            if (it->first != iter->first){
                float edgeWeight = abs(it->second - iter->second);
                //cout << it->first <<  " " << iter->first <<  " " << edgeWeight << endl;
                if(edgeWeight <= 0.10){
                    graph[it->first].push_back(make_pair(iter->first, edgeWeight));
                    graph[iter->first].push_back(make_pair(it->first, edgeWeight));
                }
                else { //make sure all songs are graphed even if they are disconnected
                    if (graph.find(it->first) == graph.end()){
                        graph[it->first] = {};
                    }
                }
            }
        }
    }
}

map<string, vector<pair<string, float>>> Graph ::CheckGraph(string genre){
    if (genre == "Dark Trap"){
        CreateGraph(darktrapGraph, darktrap);
        return darktrapGraph;
    }
    else if(genre == "Underground Rap"){
        CreateGraph(undergroundrapGraph, undergroundrap);
        return undergroundrapGraph;
    }
    else if(genre == "Trap Metal"){
        CreateGraph(trapmetalGraph, trapmetal);
        return trapmetalGraph;
    }
    else if(genre == "Emo"){
        CreateGraph(emoGraph, emo);
        return emoGraph;
    }
    else if(genre == "Rap"){
        CreateGraph(rapGraph, rap);
        return rapGraph;
    }
    else if(genre == "RnB"){
        CreateGraph( rnbGraph, rnb);
        return rnbGraph;
    }
    else if(genre == "Pop"){
        CreateGraph(popGraph, pop);
        return popGraph;
    }
    else if(genre == "Hip Hop"){
        CreateGraph(hiphopGraph, hiphop);
        return hiphopGraph;
    }
}

map<string, float> Graph::CheckMap(string genre){
    if (genre == "Dark Trap"){
        return darktrap;
    }
    else if(genre == "Underground Rap"){
        return rap;
    }
    else if(genre == "Trap Metal"){
        return trapmetal;
    }
    else if(genre == "Emo"){
        return emo;
    }
    else if(genre == "Rap"){
        return rap;
    }
    else if(genre == "RnB"){
        return rnb;
    }
    else if(genre == "Pop"){
        return pop;
    }
    return hiphop;

}

// if user chooses energy level to be (whole number) x, generate a random float between x.0 and x.9
string Graph::RandomSongHelper(map<string, float> &genre, int energy) {
    int min = 0;
    int max = 0;
    if (energy == 10){
        min = 90;
        max = 100;
    } else {
        energy = energy * 10; // changes energy from 3 to 30, for example
        min = energy;
        max = energy + 9;
    }

    bool found = false;

    while (!found){;
        double source_energy = (rand() % (max - min + 1)) + min;
        for(auto it = genre.begin(); it != genre.end(); it++) {
            if (ceil(it->second * 100) == source_energy) {
                //cout << "found" << endl;
                found = true;
                return it->first;
            }
            else{
                //cout << "not found" << endl;
            }
        }
    }
//    cout << "done" << endl;
}

vector<pair<string, float>> Graph::ConstantPlaylistHelper(map<string, vector<pair<string,float>>>& graph, map<string, float>& map, int playlistSize, int energy) {
    //BFS
    string startSong = RandomSongHelper(map, energy); //find random song that matches energy level
    vector<pair<string, float>> playlist; // initiate playlist of songs
    set<string> visited; // set to check if vertex has already been visited
    queue<string> q; //queue for vertexes

    visited.insert(startSong);
    q.push(startSong);
    playlist.push_back(make_pair(q.front(), map[q.front()] * 10));

    while (playlist.size() != playlistSize) { //continue until we reach desired playlist size
        string u = q.front();
        q.pop();
        vector<pair<string,float>> neighbors = graph[u];
        for (auto it = neighbors.begin(); it != neighbors.end(); it++){
            if (visited.count(it->first) == 0 && playlist.size() != playlistSize){
                visited.insert(it->first);
                q.push(it->first);
                float newEnergy = map[it->first] * 10;
                playlist.push_back(make_pair(it->first, newEnergy));
            }
            if (playlist.size() == playlistSize){
                break;
            }
        }
    }
    return playlist;
}

vector<pair<string, float>> Graph::RangePlaylistHelper(map<string, vector<pair<string,float>>>& graph, map<string, float>& map, int playlistSize, int energy1, int energy2) {
    string startSong = RandomSongHelper(map, energy1);
    vector<pair<string, float>> playlist;
    set<string> visited;
    set<float> visitedVal;
    stack<string> s;

    visited.insert(startSong);
    s.push(startSong);
    playlist.emplace_back(s.top(), (map[s.top()]) * 10.0);

    while((playlist.size() != playlistSize) && !s.empty()) {
        string u = s.top();
        if ((u != startSong) && visitedVal.count(map[u] * 10.0) == 0){
            visitedVal.insert(map[u] * 10.0);
            playlist.emplace_back(u, (map[u] * 10.0));
        }
        
        s.pop();
        vector<pair<string, float>> neighbors = graph[u];
        if (!neighbors.empty()){
            for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                if ((visited.count(it->first) == 0)) {
                    visited.insert(it->first);
                    if (((map[it->first] * 10.0) >= energy1) && ((map[it->first] * 10.0) <= energy2)) {
                        s.push(it->first);
                    }
                }
                if (playlist.size() == playlistSize) {
                    break;
                }
            }
        }
    }
    return playlist;
}

vector<pair<string, float>> Graph::CreateConstantPlaylist(string genre, int playlistSize, int energy) {
    map<string, vector<pair<string,float>>> genreGraph = CheckGraph(genre);
    map<string, float> genreMap = CheckMap(genre);
    return ConstantPlaylistHelper(genreGraph, genreMap, playlistSize, energy);
}

vector<pair<string, float>> Graph::CreateRangePlaylist(string genre, int playlistSize, int energy1, int energy2) {
    map<string, vector<pair<string,float>>> genreGraph = CheckGraph(genre);
    map<string, float> genreMap = CheckMap(genre);
    return RangePlaylistHelper(genreGraph, genreMap, playlistSize, energy1, energy2);
}
#endif //PROJECT3_GRAPH_H
