#include "Movie.h"
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
