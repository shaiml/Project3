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
    // maps of the songs and their energy levels by genre
    map<string, float> darktrap;
    map<string, float> undergroundrap;
    map<string, float> trapmetal;
    map<string, float> emo;
    map<string, float> rap;
    map<string, float> rnb;
    map<string, float> pop;
    map<string, float> hiphop;

    // graphs connecting each song to another if their energy levels are at most .1 apart, by genre
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
    vector<pair<string, float>> CreateConstantPlaylist(string genre, int playlistSize, int energy); // creates BFS playlist
    vector<pair<string, float>> ConstantPlaylistHelper(map<string, vector<pair<string,float>>> &graph, map<string, float> &map, int playlistSize, int energy); // conducts BFS through given genre graph
    vector<pair<string, float>> CreateRangePlaylist(string genre, int playlistSize, int energy1, int energy2); // creates DFS playlist
    vector<pair<string, float>> RangePlaylistHelper(map<string, vector<pair<string,float>>>& graph, map<string, float>& map, int playlistSize, int energy1, int energy2); // conducts DFS through given genre graph
    map<string, vector<pair<string, float>>> CheckGraph(string genre); // processes user input to create the appropriate graph
    map<string, float> CheckMap(string genre); // processess user input to search the appropriate map
    string RandomSongHelper(map<string, float> &genre, int energy); // generates random source vertex 
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

        // processes data set values into their appropriate containers
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
        for(auto iter = genre.find(it->first); iter != genre.end(); iter++){
            if (it->first != iter->first){
                float edgeWeight = abs(it->second - iter->second);
                if(edgeWeight <= 0.10){ // if a song's energy is at most .1 different from another's, they are pointed to each other
                    graph[it->first].push_back(make_pair(iter->first, edgeWeight));
                    graph[iter->first].push_back(make_pair(it->first, edgeWeight));
                }
                else { // ensures all songs are graphed even if they are disconnected
                    if (graph.find(it->first) == graph.end()){
                        graph[it->first] = {};
                    }
                }
            }
        }
    }
}

map<string, vector<pair<string, float>>> Graph ::CheckGraph(string genre){
    // check's user input before creating the graph
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
        energy = energy * 10; 
        min = energy;
        max = energy + 9; // if a user enters "3", a range of energy levels is created from 30-39 (3.0-3.9) that the source vertex can be chosen from
    }

    bool found = false;

    while (!found){;
        double source_energy = (rand() % (max - min + 1)) + min; 
        for(auto it = genre.begin(); it != genre.end(); it++) {
            if (ceil(it->second * 100) == source_energy) {
                // checks if the random value generated exists in the genre's graph
                found = true;
                return it->first;
            }
            else{
                //cout << "not found" << endl;
            }
        }
    }
}

vector<pair<string, float>> Graph::ConstantPlaylistHelper(map<string, vector<pair<string,float>>>& graph, map<string, float>& map, int playlistSize, int energy) {
    string startSong = RandomSongHelper(map, energy); // find random song that matches energy level
    vector<pair<string, float>> playlist; // initiate playlist container for songs
    set<string> visited; // stores the verticies that have been visited 
    queue<string> q; // queue of verticies

    visited.insert(startSong);
    q.push(startSong);
    playlist.push_back(make_pair(q.front(), map[q.front()] * 10));

    // BFS
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
    string startSong = RandomSongHelper(map, energy1); // find random song that matches energy level
    vector<pair<string, float>> playlist; // initiate playlist container for songs
    set<string> visited; // stores the verticies that have been visited 
    set<float> visitedVal; // stores the energy levels already in the playlist to ensure a variety of levels
    stack<string> s; // stack of verticies

    visited.insert(startSong);
    s.push(startSong);
    playlist.emplace_back(s.top(), (map[s.top()]) * 10.0); // convert's the energy level in the data set to match the visual's energy levels (ex. 0.38 becomes 3.8) 

    // DFS
    while((playlist.size() != playlistSize) && !s.empty()) {
        string u = s.top();
        if ((u != startSong) && visitedVal.count(map[u] * 10.0) == 0){ // skips re-entering the source node and any energy levels already in the playlist
            visitedVal.insert(map[u] * 10.0);
            playlist.emplace_back(u, (map[u] * 10.0));
        }
        
        s.pop();
        vector<pair<string, float>> neighbors = graph[u]; 
        if (!neighbors.empty()){ // visits the neighbors of the vertex on the top of the stack
            for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                if ((visited.count(it->first) == 0)) {
                    visited.insert(it->first);
                    if (((map[it->first] * 10.0) >= energy1) && ((map[it->first] * 10.0) <= energy2)) {
                        s.push(it->first); // pushes all values within the range given by the user onto the stack
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
