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

using namespace std;
class Graph{
    // map<string, double> genre;
    // genre, energy level, song name
    map<string, double> darktrap;
    map<string, double> undergroundrap;
    map<string, double> trapmetal;
    map<string, double> emo;
    map<string, double> rap;
    map<string, double> rnb;
    map<string, double> pop;
    map<string, double> hiphop;

    map<string, vector<pair<string, double>>> darktrapGraph;
    map<string, vector<pair<string, double>>> undergroundrapGraph;
    map<string, vector<pair<string, double>>> trapmetalGraph;
    map<string, vector<pair<string, double>>> emoGraph;
    map<string, vector<pair<string, double>>> rapGraph;
    map<string, vector<pair<string, double>>> rnbGraph;
    map<string, vector<pair<string, double>>> popGraph;
    map<string, vector<pair<string, double>>> hiphopGraph;

public:
    void ReadFile();
    void CreateGraph(map<string, vector<pair<string, double>>>& graph, map<string, double>& genre);
    vector<pair<string, double>> CreateConstantPlaylist(string genre, int playlistSize, int energy); //BFS
    vector<pair<string, double>> ConstantPlaylistHelper(map<string, vector<pair<string,double>>> &graph, map<string, double> &map, int playlistSize, int energy);
    vector<pair<string, double>> CreateRangePlaylist(string genre, int playlistSize, int energy1, int energy2); //DFS
    vector<pair<string, double>> RangePlaylistHelper(map<string, vector<pair<string,double>>>& graph, map<string, double>& map, int playlistSize, int energy1, int energy2);
    map<string, vector<pair<string, double>>> CheckGraph(string genre);
    map<string, double> CheckMap(string genre);
    string RandomSongHelper(map<string, double> &genre, int energy);
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

void Graph::CreateGraph(map<string, vector<pair<string, double>>> &graph, map<string, double> &genre) {
    map<string, vector<pair<string, double>>> tempGraph;
    for(auto it = genre.begin(); it != genre.end(); it++){
        //cout << it->first;
        for(auto iter = genre.find(it->first); iter != genre.end(); iter++){
            if (it->first != iter->first){
                double edgeWeight = abs(it->second - iter->second);
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

map<string, vector<pair<string, double>>> Graph ::CheckGraph(string genre){
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
    else if(genre == "Hiphop") {
        return hiphopGraph;
    }
}

map<string, double> Graph::CheckMap(string genre){
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

// if user chooses energy level to be (whole number) x, generate a random double between x.0 and x.9
string Graph::RandomSongHelper(map<string, double> &genre, int energy) {
    //double epsilon = 1e-10;
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

    while (!found){
        double source_energy = random(min, max);
        for(auto it = genre.begin(); it != genre.end(); it++) {
            if (ceil(it->second * 100) == source_energy) {
                //cout << "found" << endl;
                found = true;
                return it->first;
            }
        }
    }
}

vector<pair<string, double>> Graph::ConstantPlaylistHelper(map<string, vector<pair<string,double>>>& graph, map<string, double>& map, int playlistSize, double energy) {
    //BFS
    string startSong = RandomSongHelper(map, energy); //find random song that matches energy level
    vector<pair<string, double>> playlist; // initiate playlist of songs
    set<string> visited; // set to check if vertex has already been visited
    queue<string> q; //queue for vertexes

    visited.insert(startSong);
    q.push(startSong);
    playlist.push_back(make_pair(q.front(), map[q.front()] * 10));

    while (playlist.size() != playlistSize) { //continue until we reach desired playlist size
        string u = q.front();
        q.pop();
        vector<pair<string,double>> neighbors = graph[u];
        for (auto it = neighbors.begin(); it != neighbors.end(); it++){
            if (visited.count(it->first) == 0 && playlist.size() != playlistSize){
                visited.insert(it->first);
                q.push(it->first);
                double newEnergy = map[it->first] * 10;
                playlist.push_back(make_pair(it->first, newEnergy));
            }
            if (playlist.size() == playlistSize){
                break;
            }
        }
    }
    return playlist;
}

vector<pair<string, double>> Graph::RangePlaylistHelper(map<string, vector<pair<string,double>>>& graph, map<string, double>& map, int playlistSize, int energy1, int energy2) {

    string startSong = RandomSongHelper(map, energy1);
    vector<pair<string, double>> playlist;
    set<string> visited;
    stack<string> s;
    int halfway = floor(playlistSize / 2);
    int middleEnergy = energy2 - energy1;

    visited.insert(startSong);
    s.push(startSong);
    playlist.push_back(make_pair(s.top(), (map[s.top()]) * 10));

    while((playlist.size() != playlistSize) && !s.empty()) {
        string u = s.top();
        float prev = playlist[playlist.size()-1].second;
//        if ((playlist.size() < halfway) && (u != startSong) && (abs(map[u]*10 - prev) >= 0.1)){
//            if ((map[u]*10) > energy1 && (map[u]*10) <= middleEnergy) {
//                playlist.push_back(make_pair(u, (map[u] * 10)));
//            }
//        } else {
//            if (((map[u]*10) < energy2) && (map[u]*10) >= middleEnergy) && map[u]*10 - prev >= 0.1))) {
//                playlist.push_back(make_pair(u, (map[u] * 10)));
//            }
//        }
        if ((u != startSong)) {
            if (((map[u] * 10) > energy1 && (map[u] * 10) < energy2) && (u != startSong) && (map[u] * 10 - prev >= 0.1)) {
                playlist.push_back(make_pair(u, (map[u] * 10)));
            }
        }

        s.pop();
        vector<pair<string, double>> neighbors = graph[u];
        if (!neighbors.empty()){
            for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                if ((visited.count(it->first) == 0) && (playlist.size() != playlistSize)) {
                    visited.insert(it->first);
                    if (((map[it->first] * 10) > energy1) && ((map[it->first] * 10) < energy2)) {
                        s.push(it->first);
                    }
                }
                if (playlist.size() == playlistSize) {
                    break;
                }
            }
        }
    }

    //    //DFS [randomly accessed]
//    string startSong = RandomSongHelper(map, energy1);
//    vector<pair<string, double>> playlist;
//    set<string> visited;
//    stack<string> s;
//
//    visited.insert(startSong);
//    s.push(startSong);
//    playlist.push_back(make_pair(s.top(), map[s.top()]));
//
//    int rangeDiff = abs(energy1 - energy2);
//    int distribution = ceil(playlistSize / rangeDiff);
//    int bucket  =  1;
//
//    while ((playlist.size() != playlistSize) && (!s.empty())) {
//        string u = s.top();
//        if (energy1 > energy2 && u != startSong){
//            int variance =  energy1 - (floor(playlist.size()/rangeDiff));
//            if (((map[u]*10) < variance)){
//                playlist.push_back(make_pair(u, map[u]));
//            }
//        } else if (energy1 < energy2 && u != startSong) {
//            int variance =  energy1 + (floor(playlist.size()/rangeDiff));
//            if (((map[u]*10) > variance)){
//            }
//        }
//        s.pop();
//        vector<pair<string, double>> neighbors = graph[u];
//        for (auto it = neighbors.begin(); it != neighbors.end(); it++){
//            if ((visited.count(it->first) == 0) && (playlist.size() != playlistSize)){
//                visited.insert(it->first);
//                //string lastEntry = playlist[-1].first; // last song pushed into the playlist
//                if (energy1 > energy2){ // range is decreasing
//                    if (((map[it->first] * 10) < energy1) && ((map[it->first] * 10) > energy2)){
//                        s.push(it->first);
//                        //playlist.push_back(make_pair(it->first, map[it->first]));
//                    }
//                } else if (energy1 < energy2){ // range is increasing
//                    if (((map[it->first] * 10) > energy1) && ((map[it->first] * 10) < energy2)){
//                        s.push(it->first);
//                        //playlist.push_back(make_pair(it->first, map[it->first]));
//                    }
//                }
//            }
//            if (playlist.size() == playlistSize){
//                break;
//            }
//        }
//    }
    cout << playlist.size() << endl;
    return playlist;
}

vector<pair<string, double>> Graph::CreateConstantPlaylist(string genre, int playlistSize, double energy) {
    map<string, vector<pair<string,double>>> genreGraph = CheckGraph(genre);
    map<string, double> genreMap = CheckMap(genre);
    return ConstantPlaylistHelper(genreGraph, genreMap, playlistSize, energy);
}

vector<pair<string, double>> Graph::CreateRangePlaylist(string genre, int playlistSize, int energy1, int energy2) {
    map<string, vector<pair<string,double>>> genreGraph = CheckGraph(genre);
    map<string, double> genreMap = CheckMap(genre);
    return RangePlaylistHelper(genreGraph, genreMap, playlistSize, energy1, energy2);
}
#endif //PROJECT3_GRAPH_H
