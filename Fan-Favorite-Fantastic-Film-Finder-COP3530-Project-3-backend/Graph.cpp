#include "Graph.h"
void Graph::insertEdge(string src, const vector<string>& actors, unordered_map<string, vector<string>>& actorMap)
{
    for (auto& m : actors)
    {                               //for every actor in src movie
        for (auto& n : actorMap[m]) {//add edge from src to all movies actor stars in 
            AdjList[src].insert(n);
            // AdjList[n].insert(src);
        }
    }
}

bool Graph::bfs(string src, string tgt, unordered_map<string, string>& prev)
{
    queue<string> q;
    unordered_map<string, bool> visited;
    visited[src] = true;
    q.push(src);
    while (!q.empty())
    {
        string curr = q.front();
        q.pop();
        for (auto& m : AdjList[curr])
        { //iterate through edges of curr

            if (!visited.count(m))
            {
                visited[m] = true; //if dest not visited mark as visited
                prev[m] = curr;    //note prev movie
                q.push(m);         //add to queue
            }
            if (m == tgt)
            {
                return true;
            }
        }
    }
    return false;
}

vector<string> Graph::shortestPath(string src, string tgt)
{
    vector<string> result;
    unordered_map<string, string> prev; //map of prev movie in path
    if (!bfs(src, tgt, prev))
    {
        cout << "No path exists" << endl;
        //  return empty vector
    }
    string curr = tgt;
    result.push_back(curr);
    while (prev.count(curr) > 0)
    { //retrace the path
        result.push_back(prev[curr]);
        curr = prev[curr];
    }
    return result;
}

string Graph::searchMovies(string title, unordered_map<string, Movie>& IDmap, unordered_map<string, string>& titleMap)
{

    if (titleMap.find(title) != titleMap.end()) {
        string ID = titleMap[title];
        return titleMap[title]; // exact match; returns ID of movie
    }
    else {
        cout << "start search" << endl;
        for (auto it = titleMap.begin(); it != titleMap.end(); it++) {
            //cout << it->first << endl;
            if (it->first.find(title) != string::npos) return it->second; // closest match; returns ID of movie
        }
    }
    //Movie movie;
    //movie.setDesc("Movie not found."); 
    return "tt0000000"; // no match; returns an invalid ID
}
bool Graph::dfs(string src, string tgt, int lim, unordered_map<string, string> &prev, unordered_map<string, bool> &visited)
{
    if (src == tgt)
    {
        // cout<<prev[src]<<endl;
        return true;
    }
    if (lim <= 0)
    { //if depth limit reached, return
        return false;
    }
    for (auto &m : AdjList[src])
    {                          //iterate through edges
        if (!visited.count(m)) //if not visited
        {
            // visited[m] = true; // mark as visited  , this changes the path for some reason?
            prev[m] = src; //note prev movie
            if (dfs(m, tgt, lim - 1, prev, visited))
            { //recursively search till limit reached
                return true;
            }
        }
    }
    return false;
}

bool Graph::idfs(string src, string tgt, unordered_map<string, string> &prev)
{
    unordered_map<string, bool> visited;
    for (int i = 0; i <= 10; i++)
    { //max depth can be changed
        visited.clear();
        prev.clear();
        visited[src] = true;
        if (dfs(src, tgt, i, prev, visited))
        {
            return true;
        }
    }
    return false;
}
vector<string> Graph::shortestPath2(string src, string tgt) // retrace path for idfs
{
    vector<string> result;
    unordered_map<string, string> prev; //map of prev movie in path
    if (!idfs(src, tgt, prev))
    {
        cout << "IDFS: No path exists" << endl;
        //  return empty vector
    }
    // cout << prev.size() << endl;
    string curr = tgt;
    result.push_back(curr);
    while (prev.count(curr) > 0)
    { //retrace the path
        //  cout << "HI" << endl;
        result.push_back(prev[curr]);
        curr = prev[curr];
    }
    return result;
}