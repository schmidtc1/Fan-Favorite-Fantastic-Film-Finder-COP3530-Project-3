#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
using namespace std;

class Movie
{
private:
    string movieID, title, datePub, genre, desc, vote, duration, country, language;
    vector<string> actors; // make an Actor class for actor objects that store the movies they play in and info
    vector<string> directors;

public:
    Movie(string _movieID, string _title, string _datePub, string _genre, string _desc);
    Movie();
    void addActor(string _actor) { actors.push_back(_actor); }
    void addDirector(string _director) { directors.push_back(_director); }
    void setID(string _movieID) { movieID = _movieID; }
    void setTitle(string _title) { title = _title; }
    void setDate(string _datePub) { datePub = _datePub; }
    void setGenre(string _genre) { genre = _genre; }
    void setDesc(string _desc) { desc = _desc; }
    void setDirectors(vector<string> directors);
    void setVote(string _vote) { vote = _vote; }
    void setDuration(string _duration) { duration = _duration; }
    void setCountry(string _country) { country = _country; }
    void setLanguage(string _language) { language = _language; }
    string getTitle() const { return title; }
    string getDate() { return datePub; }
    string getID() { return movieID; }
    string getGenre() { return genre; }
    string getDesc() { return desc; }
    string getVote() { return vote; }
    string getDuration() { return duration; }
    string getCountry() { return country; }
    string getLanguage() { return language; }
    vector<string> getActors() { return actors; }
    vector<string> getDirectors() { return directors; }
};

void checkActors(vector<string> &actorList, string _name);       // not necessary anymore
void checkDirectors(vector<string> &directorList, string _name); // not necessary anymore

string findCommonActor(Movie &film1, Movie &film2); //finds the common actor between two films

class Graph
{
private:
    unordered_map<string, unordered_set<string>> AdjList;

public:
    void insertEdge(string src, const vector<string> &actors, unordered_map<string, vector<string>> &actorMap); // actors vector needs to be const; I get an error when it isn't
    bool bfs(string src, string tgt, unordered_map<string, string> &prev);
    vector<string> shortestPath(string src, string tgt);
    Movie &searchMovies(string title, unordered_map<string, Movie> &IDmap, unordered_map<string, string> &titleMap);
    bool dfs(string src, string tgt, int lim, unordered_map<string, string> &prev, unordered_map<string, bool> &visited);
    bool idfs(string src, string tgt, unordered_map<string, string> &prev);
    vector<string> shortestPath2(string src, string tgt);
};

int main()
{
    //data retrieval

    ifstream file;
    string header, line;
    string ID, title, datePub, genre, actorLine, dirLine, desc, vote, duration, country, language, name;
    vector<string> directorList;
    vector<Movie> movieList(10000);
    vector<string> actorList;
    unordered_map<string, vector<string>> actorMap; //maps actor to movies
    unordered_map<string, Movie> IDmap;             //map ID to movie
    unordered_map<string, string> titleMap;         //map title to ID
    file.open("Movie_Files/IMDb movies.txt");
    if (!file.is_open())
    {
        cout << "File couldn't be loaded. Check that the file is in the right place!" << endl;
    }

    getline(file, header);
    int index = 0;
    while (getline(file, line) && index < 10000)
    {
        Movie movie;
        //  cout << endl;
        ID = line.substr(0, line.find('\t')); // gets title ID: may not be necessary
        line = line.substr(line.find('\t') + 1);
        movie.setID(ID);

        title = line.substr(0, line.find('\t')); // gets title
        line = line.substr(line.find('\t') + 1);
        movie.setTitle(title);

        datePub = line.substr(0, line.find('\t')); // gets date published
        line = line.substr(line.find('\t') + 1);
        movie.setDate(datePub);

        genre = line.substr(0, line.find('\t')); // gets genre
        line = line.substr(line.find('\t') + 1);
        movie.setGenre(genre);

        actorLine = line.substr(0, line.find('\t')); // separate into distinct actor strings and input into vector
        while (actorLine.find(',') != -1)
        {
            name = actorLine.substr(0, actorLine.find(','));
            movie.addActor(name);
            actorMap[name].push_back(ID);
            //   cout << name << endl;
            actorLine = actorLine.substr(actorLine.find(',') + 2);
        }
        name = actorLine.substr(0, actorLine.find('\t')); // testing with one actor
        movie.addActor(name);
        actorMap[name].push_back(ID); //map actor to movie
        line = line.substr(line.find('\t') + 1);

        desc = line.substr(0, line.find('\t'));  // gets description
        line = line.substr(line.find('\t') + 1); // .find(string) gives the first index of the string, so you must increment accordingly
        movie.setDesc(desc);

        vote = line.substr(0, line.find('\t')); // gets vote
        line = line.substr(line.find('\t') + 1);
        movie.setVote(vote);

        duration = line.substr(0, line.find('\t')); // gets duration
        line = line.substr(line.find('\t') + 1);
        movie.setDuration(duration);

        country = line.substr(0, line.find('\t')); // gets country
        line = line.substr(line.find('\t') + 1);
        movie.setCountry(country);

        language = line.substr(0, line.find('\t')); // gets language
        line = line.substr(line.find('\t') + 1);
        movie.setLanguage(language);
        titleMap[title] = ID; //map title to the ID
        IDmap[ID] = movie;    //map the ID to the movie

        // keep directors in a separate vector

        dirLine = line.substr(0, line.find('\t'));
        while (dirLine.find(',') != -1)
        {
            name = dirLine.substr(0, dirLine.find(','));
            //checkDirectors(directorList, name);
            movie.addDirector(name);
            dirLine = dirLine.substr(dirLine.find(',') + 2);
        }
        name = dirLine.substr(0, dirLine.find('\t'));
        //checkDirectors(directorList, name);
        movie.addDirector(name);
        line = line.substr(line.find('\t') + 1);

        movieList.at(index) = movie;
        index++;
        // test movie object
        /*cout << movie.getTitle() << endl;
        cout << movie.getDate() << endl;
        cout << movie.getGenre() << endl;
        cout << movie.getDesc() << endl;
        cout << movie.getVote() << endl;
        cout << movie.getDuration() << endl;
        cout << movie.getCountry() << endl;
        cout << movie.getLanguage() << endl;*/
    }
    // movie file data parsing ^^
    file.close();

    cout << "Movie data retrieved." << endl;

    //create adjacency List
    Graph list;
    for (auto &m : movieList)
    {
        list.insertEdge(m.getID(), m.getActors(), actorMap);
    }
    cout << "Adjacency List created. " << endl;

    //testing:
    string x = "tt0003772";
    string y = "tt0016832";
    vector<string> path = list.shortestPath(x, y);   //bfs
    vector<string> path2 = list.shortestPath2(x, y); // idfs
    if (path.size() > 1)
    {
        cout << "BFS: Path of the movie: " << IDmap[x].getTitle() << " to " << IDmap[y].getTitle() << endl;

        cout << IDmap[path[path.size() - 1]].getTitle() << " -> ";

        for (int i = path.size() - 2; i > 0; i--)
        {
            cout << findCommonActor(IDmap[path[i + 1]], IDmap[path[i]]) << " -> ";
            cout << IDmap[path[i]].getTitle() << " -> ";
        }
        cout << findCommonActor(IDmap[path[1]], IDmap[path[0]]) << " -> ";
        cout << IDmap[path[0]].getTitle() << endl;
    }
    if (path2.size() > 1)
    {
        cout << "IDFS: Path of the movie: " << IDmap[x].getTitle() << " to " << IDmap[y].getTitle() << endl;

        cout << IDmap[path2[path2.size() - 1]].getTitle() << " -> ";

        for (int i = path2.size() - 2; i > 0; i--)
        {
            cout << findCommonActor(IDmap[path2[i + 1]], IDmap[path2[i]]) << " -> ";
            cout << IDmap[path2[i]].getTitle() << " -> ";
        }
        cout << findCommonActor(IDmap[path2[1]], IDmap[path2[0]]) << " -> ";
        cout << IDmap[path2[0]].getTitle() << endl;
    }

    // movie search testing: Input movie titles or part of a title to test
    Movie movie = list.searchMovies("shing", IDmap, titleMap);
    if (movie.getDesc() == "Movie not found.")
    {
        cout << "Movie could not be found. Check the input again." << endl;
    }
    else
    {
        cout << "Movie found: " << movie.getTitle() << endl;
        cout << movie.getDesc() << endl;
        cout << movie.getDate() << endl;
        cout << movie.getGenre() << endl;
    }

    return 0;
}

void checkActors(vector<string> &actorList, string _name)
{ // search for and return an actor object if it exists
    for (unsigned int i = 0; i < actorList.size(); i++)
    {
        if (actorList.at(i) == _name)
            return;
    }
    actorList.push_back(_name);
}
void checkDirectors(vector<string> &directorList, string _name)
{
    for (unsigned int i = 0; i < directorList.size(); i++)
    {
        if (directorList.at(i) == _name)
            return;
    }
    directorList.push_back(_name);
}
Movie::Movie() // default movie object is blank
{
    movieID = "";
    title = "";
    datePub = "";
    genre = "";
    desc = "";
    vote = "";
    duration = "";
    country = "";
    language = "";
}
Movie::Movie(string _movieID, string _title, string _datePub, string _genre, string _desc)
{
    movieID = _movieID;
    title = _title;
    datePub = _datePub;
    genre = _genre;
    desc = _desc;
}

void Movie::setDirectors(vector<string> _directors) // not necessary anymore
{
    directors = _directors;
}

void Graph::insertEdge(string src, const vector<string> &actors, unordered_map<string, vector<string>> &actorMap)
{
    for (auto &m : actors)
    { //for every actor in src movie
        for (auto &n : actorMap[m])
        { //add edge from src to all movies actor stars in
            AdjList[src].insert(n);
            // AdjList[n].insert(src);
        }
    }
}

bool Graph::bfs(string src, string tgt, unordered_map<string, string> &prev)
{
    queue<string> q;
    unordered_map<string, bool> visited;
    visited[src] = true;
    q.push(src);
    while (!q.empty())
    {
        string curr = q.front();
        q.pop();
        for (auto &m : AdjList[curr])
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
        cout << "BFS: No path exists" << endl;
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
            // visited[m] = true; // mark as visited
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

Movie &Graph::searchMovies(string title, unordered_map<string, Movie> &IDmap, unordered_map<string, string> &titleMap)
{

    if (titleMap.find(title) != titleMap.end())
    {
        string ID = titleMap[title];
        return IDmap[ID]; // exact match
    }
    else
    {
        for (auto it = titleMap.begin(); it != titleMap.end(); it++)
        {
            //cout << it->first << endl;
            if (it->first.find(title) != string::npos)
                return IDmap[it->second]; // closest match
        }
    }
    Movie movie;
    movie.setDesc("Movie not found."); // no match
    return movie;
}

//finds and returns the common actor between two films
string findCommonActor(Movie &film1, Movie &film2)
{
    vector<string> actors1 = film1.getActors();
    for (int i = 0; i < film1.getDirectors().size(); i++)
    {
        actors1.push_back(film1.getDirectors()[i]);
    }
    vector<string> actors2 = film2.getActors();
    for (int i = 0; i < film2.getDirectors().size(); i++)
    {
        actors2.push_back(film2.getDirectors()[i]);
    }

    for (int i = 0; i < actors1.size(); i++)
    {
        for (int j = 0; j < actors2.size(); j++)
        {
            if (actors1[i] == actors2[j])
            {
                return actors1[i];
            }
        }
    }
    return NULL;
}