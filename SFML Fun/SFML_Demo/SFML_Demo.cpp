#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <chrono>
#include "Movie.h"
#include "Graph.h"
using namespace std;

void parseFile(vector<Movie>& movieList, vector<string>& actorList, unordered_map<string, 
    vector<string>>& actorMap, unordered_map<string, Movie>& IDmap, unordered_map<string, string>& titleMap);

int main()
{
    //data retrieval

    vector<Movie> movieList(15000);
    vector<string> actorList;
    unordered_map<string, vector<string>> actorMap; //maps actor to movies
    unordered_map<string, Movie> IDmap;             //map ID to movie
    unordered_map<string, string> titleMap;         //map title to ID

    auto start = chrono::high_resolution_clock::now();

    parseFile(movieList, actorList, actorMap, IDmap, titleMap);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    float time = duration.count();
    cout << time << endl;
    cout << "Movie data retrieved in " << time / 1000000 << " seconds." << endl;

    //create adjacency List
    Graph list;
    for (auto& m : movieList)
    {
        list.insertEdge(m.getID(), m.getActors(), actorMap);
    }
    cout << "Adjacency List created. " << endl;

    /*TESTING DFS*/
    string x = titleMap["Cinderella"];
    string y = titleMap["Tih Minh"];
    vector<string> path = list.shortestPath(x, y);
    
    if (path.size() > 1)
    {
        cout << "path of the movie:" << IDmap[x].getTitle() << " to " << IDmap[y].getTitle() << endl;

        for (int i = 0; i < path.size(); i++)
        {
            cout << i << ". " << IDmap[path[i]].getTitle() << endl;
        }
        cout << list.connectMovies(IDmap, path) << endl;
    }

    /*TESTING SEARCH FUNCTION*/
    /*string foundID = list.searchMovies("kmnkp", IDmap, titleMap);
    cout << "ID found: " << foundID << endl;
    if (foundID == "tt0000000") {
        cout << "Movie could not be found. Check the input again." << endl;
    }
    else {
        Movie movie = IDmap[foundID];
        cout << "Movie found: " << movie.getTitle() << endl;
        cout << movie.getDesc() << endl;
        cout << movie.getDate() << endl;
        cout << movie.getGenre() << endl;
    }*/
    cout << "TEST IDFS" << endl;
    vector<string> path2 = list.shortestPath2(x, y);
    if (path2.size() > 1) {
        cout << "path of the movie:" << IDmap[x].getTitle() << " to " << IDmap[y].getTitle() << endl;

        for (int i = 0; i < path2.size(); i++)
        {
            cout << IDmap[path2[i]].getTitle() << endl;
        }
        cout << list.connectMovies(IDmap, path2);
    }

    return 0;
}

void parseFile(vector<Movie>& movieList, vector<string>& actorList, unordered_map<string,
    vector<string>>&actorMap, unordered_map<string, Movie>& IDmap, unordered_map<string, string>& titleMap) 
{
    ifstream file;
    string header, line;
    string ID, title, datePub, genre, actorLine, dirLine, desc, vote, duration, country, language, name;
    file.open("Movie_Files/IMDb movies.txt");
    if (!file.is_open()) {
        cout << "File couldn't be loaded. Check that the file is in the right place!" << endl;
    }

    getline(file, header);
    int index = 0;
    while (getline(file, line) && index < 15000)
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
            movie.addDirector(name);
            dirLine = dirLine.substr(dirLine.find(',') + 2);
        }
        name = dirLine.substr(0, dirLine.find('\t'));
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
}


