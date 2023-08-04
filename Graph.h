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
    // danceability, energy, tempo, genre, song_name
    vector<pair<string, double>> CreateConstantPlaylist(string genre, int playlistSize, double energy); //BFS
    vector<pair<string, double>> ConstantPlaylistHelper(map<string, vector<pair<string,double>>> &graph, map<string, double> &map, int playlistSize, double energy);
    vector<pair<string, double>> CreateRangePlaylist(string genre, int playlistSize, double energy1, double energy2); //DFS
    vector<pair<string, double>> RangePlaylistHelper(map<string, vector<pair<string,double>>>& graph, map<string, double>& map, int playlistSize, double energy1, double energy2);
    map<string, vector<pair<string, double>>> CheckGraph(string genre);
    map<string, double> CheckMap(string genre);
    string RandomSongHelper(map<string, double> &genre, double energy);
};


void Graph::ReadFile() {
    ifstream spotify;
    spotify.open("../spotify_dataset.csv", ios::in);

    /*if (!spotify.is_open()){
        cout << "Error opening file" << endl;
    }
    if (spotify.is_open()){
        cout << "File is open" << endl;
     }*/

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

    /// check why map wont print first + second next to each other
//    for (auto& pair : pop){
//        cout << pair.first << endl;
//        cout << pair.second << endl;
//        cout << pair.first << " " << pair.second << endl;
//    }


    CreateGraph(darktrapGraph, darktrap);
    CreateGraph(undergroundrapGraph, undergroundrap);
    CreateGraph(trapmetalGraph, trapmetal);
    CreateGraph(emoGraph, emo);
    CreateGraph(rapGraph, rap);
    CreateGraph(rnbGraph, rnb);
    CreateGraph(popGraph, pop);
    CreateGraph(hiphopGraph, hiphop);


//    cout << darktrapGraph.size() << endl; ///
//    cout << undergroundrapGraph.size() << endl; ///
//    cout << emoGraph.size() << endl; ///
//    cout << rapGraph.size() << endl; ///
//    cout << rnbGraph.size() << endl; ///
//    cout << trapmetalGraph.size() << endl; ///
//    cout << popGraph.size() << endl; ///
//    cout << hiphopGraph.size() << endl; ///
//    for(auto it = popGraph.begin(); it != popGraph.end(); it++){
//        cout << it->first << " ";
//       for (auto iter = 0; iter != it->second.size(); iter++){
//          cout << it->second[iter].first << " " << it->second[iter].second << endl;
//        }
//    }



//    for (auto& entry : popGraph){
//        string key = entry.first;
//        cout << key << endl;
//        vector<pair<string, double>> songs = entry.second;
//        for (auto& song : songs){
//            string songname = song.first;
//            double energy = song.second;
//            cout << songname << energy << endl;
//        }
//    }
    cout<< "done" << endl;
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

map<string, vector<pair<string, double>>> Graph ::CheckGenre(string genre){
    if (genre == "Dark Trap"){
        return darktrapGraph;
    }
    else if(genre == "Underground Rap"){
        return rapGraph;
    }
    else if(genre == "Trap Metal"){
        return trapmetalGraph;
    }
    else if(genre == "Emo"){
        return emoGraph;
    }
    else if(genre == "Rap"){
        return rapGraph;
    }
    else if(genre == "RnB"){
        return rnbGraph;
    }
    else if(genre == "Pop"){
        return popGraph;
    }
    else if(genre == "Hiphop") {
        return hiphopGraph;
    }
}


double random(double min, double max){
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> source_energy(min, max);
    return source_energy(gen);

}

// if user chooses energy level to be (whole number) x, generate a random double between x.0 and x.9
string Graph::RandomSongHelper(map<string, double> &genre, double energy) {
    energy = (energy - 1.0)/10.0; // changes range from 1-10 to 0.0 - 9.9 to match the dataset values
    double min = energy;
    double max = energy + 0.9;
    bool found = false;

    while (!found){
        double source_energy = random(min, max);
        for(auto it = genre.begin(); it != genre.end(); it++) {
            if (it->second == source_energy) {
                found = true;
                return it->first;
            }
        }
    }
}

vector<string> Graph::ConstantPlaylistHelper(map<string, vector<pair<string,double>>>& genre, int playlistSize, double energyLevel) {
    //BFS
    string startSong = RandomSongHelper(genre, energyLevel);
    vector<string> playlist;
    set<string> visited;
    queue<string> q;

    visited.insert(startSong);
    q.push(startSong);

    while(!q.empty()){
        string u = q.front();
        q.pop();
        vector<pair<string,double>> neighbors = genre[u];
        std::sort(neighbors.begin(),neighbors.begin()+neighbors.size());
        for(string v: neighbors)
        {
            if(visited.count(v)==0)
            {
                visited.insert(v);
                q.push(v);
            }
        }
    }
    while(playlist.size() != playlistSize){

    }
}

vector<string> Graph::RangePlaylistHelper(map<string, vector<pair<string,double>>>& genre, int length, double energy1, double energy2) {
    //DFS [randomly accessed]
    string startSong = RandomSongHelper(map, energy1);
    vector<pair<string, double>> playlist;
    set<string> visited;
    stack<string> s;

    visited.insert(startSong);
    s.push(startSong);
    playlist.push_back(make_pair(s.top(), map[s.top()]));

    while (playlist.size() != playlistSize) {
        string u = s.top();
        if (energy1 > energy2){
            if (map[u] < map[playlist[-1].first] && playlist.size() != 1){
                playlist.push_back(make_pair(u, map[u]));
            }
        } else if (energy1 < energy2) {
            if (map[u] > map[playlist[-1].first] && playlist.size() != 1) {
                playlist.push_back(make_pair(u, map[u]));
            }
        }
        s.pop();
        vector<pair<string, double>> neighbors = graph[u];
        for (auto it = neighbors.begin(); it != neighbors.end(); it++){
            if ((visited.count(it->first) == 0) && (playlist.size() != playlistSize)){
                visited.insert(it->first);
                //string lastEntry = playlist[-1].first; // last song pushed into the playlist
                if (energy1 > energy2){ // range is decreasing
                    if ((map[it->first] < energy1) && (map[it->first] > energy2)){
                        s.push(it->first);
                        //playlist.push_back(make_pair(it->first, map[it->first]));
                    }
                } else if (energy1 < energy2){ // range is increasing
                    if ((map[it->first] > energy1) && (map[it->first] < energy2)){
                        s.push(it->first);
                        //playlist.push_back(make_pair(it->first, map[it->first]));
                    }
                }
            }
            if (playlist.size() == playlistSize){
                break;
            }
        }
    }
    return playlist;
}

vector<string> Graph::CreateConstantPlaylist(string genre, int playlistSize, double energyLevel) {
    map<string, vector<pair<string,double>>> genreGraph = CheckGenre(genre);
    return ConstantPlaylistHelper(genreGraph, playlistSize, energyLevel);
}

vector<string> Graph::CreateRangePlaylist(string genre, int playlistSize, double energy1, double energy2) {
    map<string, vector<pair<string,double>>> genreGraph = CheckGenre(genre);
    return RangePlaylistHelper(genreGraph, playlistSize, energy1, energy2);
}
#endif //PROJECT3_GRAPH_H
