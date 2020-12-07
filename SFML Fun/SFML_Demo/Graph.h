#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include "Movie.h"
#pragma once
class Graph
{
private:
    unordered_map<string, unordered_set<string>> AdjList;

public:
    void insertEdge(string src, const vector<string>& actors, unordered_map<string, vector<string>>& actorMap); // actors vector needs to be const; I get an error when it isn't
    bool bfs(string src, string tgt, unordered_map<string, string>& prev);
    vector<string> shortestPath(string src, string tgt);
    string searchMovies(string title, unordered_map<string, Movie>& IDmap, unordered_map<string, string>& titleMap);
    bool dfs(string src, string tgt, int lim, unordered_map<string, string>& prev, unordered_map<string, bool>& visited);
    bool idfs(string src, string tgt, unordered_map<string, string>& prev);
    vector<string> shortestPath2(string src, string tgt);
    string findCommonActor(Movie& film1, Movie& film2);
    string connectMovies(unordered_map<string, Movie> &IDmap, vector<string>& path);
};



