#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
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
    Movie() {}
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

void checkActors(vector<string> &actorList, string _name);
void checkDirectors(vector<string> &directorList, string _name);

class Graph
{
private:
    unordered_map<string, set<string>> AdjList;

public:
    void insertEdge(string src, vector<string> actors, unordered_map<string, vector<string>> actorMap);
    bool bfs(string src, string tgt, unordered_map<string, string> prev);
    vector<string> shortestPath(string src, string tgt);
};

int main()
{
    //data retrieval

    ifstream file;
    string header, line;
    string ID, title, datePub, genre, actorLine, dirLine, desc, vote, duration, country, language, director;
    string nameID, alias, name, bio, dob;
    vector<string> directorList;
    vector<Movie> movieList;
    vector<string> actorList;
    unordered_map<string, vector<string>> actorMap; //maps actor to movies
    unordered_map<string, Movie> IDmap;             //map ID to movie
    unordered_map<string, string> titleMap;         //map title to ID
    file.open("Movie_Files/IMDb movies.txt");

    getline(file, header);
    // cout << header << endl;
    while (getline(file, line))
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
            checkActors(actorList, name);
            movie.addActor(name);
            actorMap[name].push_back(ID);
            //   cout << name << endl;
            actorLine = actorLine.substr(actorLine.find(',') + 2);
        }
        name = actorLine.substr(0, actorLine.find('\t'));
        checkActors(actorList, name);
        movie.addActor(name);
        actorMap[name].push_back(ID); //map actor to movie
        //cout << name << endl;
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
            checkDirectors(directorList, name);
            movie.addDirector(name);
            dirLine = dirLine.substr(dirLine.find(',') + 2);
        }
        name = dirLine.substr(0, dirLine.find('\t'));
        checkDirectors(directorList, name);
        movie.addDirector(name);
        line = line.substr(line.find('\t') + 1);

        movieList.push_back(movie);
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

    //tt0000009, Miss Jerry, Miss Jerry, 1894, 1894 - 10 - 09, Romance, 45, USA, None, Alexander Black, Alexander Black, Alexander Black Photoplays, "Blanche Bayliss, William Courtenay, Chauncey Depew", The adventures of a female reporter in the 1890s., 5.9, 154, , , , , 1.0, 2.0

    //create adjacency List
    Graph list;
    for (auto &m : movieList)
    {
        list.insertEdge(m.getID(), m.getActors(), actorMap);
    }
    //testing:
    string x = "tt1235552";
    string y = "tt9908390";
    vector<string> path = list.shortestPath(x, y);
    if (path.size() > 1)
    {
        cout << "path of the movie:" << IDmap[x].getTitle() << " to " << IDmap[y].getTitle() << endl;

        for (int i = 0; i < path.size(); i++)
        {
            cout << IDmap[path[i]].getTitle() << endl;
        }
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
Movie::Movie(string _movieID, string _title, string _datePub, string _genre, string _desc)
{
    movieID = _movieID;
    title = _title;
    datePub = _datePub;
    genre = _genre;
    desc = _desc;
}

void Movie::setDirectors(vector<string> _directors)
{
    directors = _directors;
}

void Graph::insertEdge(string src, vector<string> actors, unordered_map<string, vector<string>> actorMap)
{
    for (auto &m : actors)
    {                               //for every actor in src movie
        for (auto &n : actorMap[m]) //add edge from src to all movies actor stars in
            AdjList[src].insert(n);
    }
}

bool Graph::bfs(string src, string tgt, unordered_map<string, string> prev)
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
