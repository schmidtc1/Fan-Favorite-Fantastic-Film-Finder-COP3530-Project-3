#include <vector>
#include <string>
#include <iostream>
using namespace std;
#pragma once
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
    vector<string> getDirectors() { return directors; }
    vector<string> getActors() { return actors; }
    
};
