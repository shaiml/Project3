#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
class Graph{
    map<string, vector<string, double>> darktrap;
    map<string, vector<string, double>> underground;
    map<string, vector<string, double>> trapmetal;
    map<string, vector<string, double>> emo;
    map<string, vector<string, double>> rap;
    map<string, vector<string, double>> rnb;
    map<string, vector<string, double>> pop;
    map<string, vector<string, double>> hiphop;
    map<string, vector<string, double>> techhouse;
    map<string, vector<string, double>> techno;
    map<string, vector<string, double>> trance;
    map<string, vector<string, double>> psytrance;
    map<string, vector<string, double>> trap;
    map<string, vector<string, double>> dnb;
    map<string, vector<string, double>> hardstyle;

public:
    void ReadFile();
    // danceability, energy, tempo, genre, song_name

};

void Graph::ReadFile() {
    fstream spotify;
    spotify.open("spotify_dataset.csv", ios::out | ios::app);
}
#endif //PROJECT3_GRAPH_H
