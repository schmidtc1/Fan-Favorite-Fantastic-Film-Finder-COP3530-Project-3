#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <chrono>
#include "Movie.h"
#include "Graph.h"
using namespace std;

void parseFile(vector<Movie>& movieList, vector<string>& actorList, unordered_map<string,
    vector<string>>&actorMap, unordered_map<string, Movie>& IDmap, unordered_map<string, string>& titleMap);

//Timer functionality is based off of the GeeksForGeeks tutorial https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
//We used the Kaggle movie data set found here: https://www.kaggle.com/stefanoleone992/imdb-extensive-dataset?
//Based off of code from the SFML website for creating an SFML Project: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
int main()
{
    // data retrieval: 
    vector<Movie> movieList(15000);
    vector<string> actorList;
    unordered_map<string, vector<string>> actorMap; //maps actor to movies
    unordered_map<string, Movie> IDmap;             //map ID to movie
    unordered_map<string, string> titleMap;         //map title to ID

    // path stuff
    vector<string> path1;
    vector<string> path2;
    bool IDcheck1 = false;
    bool IDcheck2 = false;
    bool pathCheck1 = false;
    bool pathCheck2 = false;

    parseFile(movieList, actorList, actorMap, IDmap, titleMap);
    cout << "Movie data retrieved." << endl;

    //create adjacency List
    Graph list;
    for (auto& m : movieList)
    {
        list.insertEdge(m.getID(), m.getActors(), actorMap);
    }
    cout << "Adjacency List created. " << endl;

    //bools for serach status (false indicates one is searching for separation, true indicates one is searching)
    bool searchToggle = true;
    string search = "Searching";
    sf::Text searchTxt;

    //buttons
    //creating with help of this SFML tutorial: https://www.sfml-dev.org/tutorials/2.5/graphics-shape.php
    sf::Text toggleTxt;
    sf::RectangleShape searchToggleButton;
    sf::Text goTxt;
    sf::RectangleShape goButton;

    //timer variables
    bool timed1 = false;
    bool timed2 = false;
    float time1 = 0.f;
    float time2 = 0.f;

    //variables for search bars
    bool txtBox1 = false;
    bool txtBox2 = false;
    
    string entry1 = "Click to Enter 1st Film";
    string entry2 = "Click to Enter 2nd Film";
    sf::Text entry1Txt;
    sf::Text entry2Txt;

    //toggles window visibility
    bool showDetails = false;

    //sf objects
    sf::RenderWindow mainWindow(sf::VideoMode(1920, 1080), "Film Finder", sf::Style::Titlebar | sf::Style::Close);
    sf::RenderWindow detailWindow(sf::VideoMode(1280, 1280), "Details", sf::Style::Titlebar | sf::Style::Close);
    //middle of my screen is at 860, 540 -Noah (Check if the current placement of the window is off-centered to the left (it worked!) on your end pls)
    // Chris: I have to adjust the size for it to fit on my laptop, otherwise the detailWindow does not show
    mainWindow.setPosition(sf::Vector2i(0, 0));
    //detailWindow's position is mainWindow.x + mainWindow's x size and mainWindow.y - detailWindow overhang
    detailWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x, mainWindow.getPosition().y));

    //maybe add details for genre, rating, and language
    sf::Font fnt;
    sf::Text title;
    sf::Text detailLine1;
    sf::Text detailLine2;
    sf::Text detailLine3;
    sf::Text detailLine4;
    sf::Text detailLine5;
    sf::Text detailLine6;
    sf::Text detailLine7;
    sf::Text detailLine8;
    sf::Text detailLine9;
    sf::Text detailLine10;

    sf::Text detailLine11;
    sf::Text detailLine12;

    //drawing text
    //text drawn with the help of this SFML tutorial: https://www.sfml-dev.org/tutorials/2.5/graphics-text.php
    //Oswald is licensed under the SIL Open Font License OFL: https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL
    if (!(fnt.loadFromFile("Oswald-Medium.ttf")))
    {
        cout << "Font couldn't be loaded. Check that the file is in the right place!" << endl;
    }
    //title text
    title.setFont(fnt);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::White);
    title.setString("Fan-Favorite Fantastic Film Finder");

    //detail window text
    detailLine1.setFont(fnt);
    detailLine1.setCharacterSize(40);
    detailLine1.setFillColor(sf::Color::White);
    detailLine2.setFont(fnt);
    detailLine2.setCharacterSize(40);
    detailLine2.setFillColor(sf::Color::White);
    detailLine2.setPosition(sf::Vector2f(0, detailLine1.getPosition().y + detailLine1.getCharacterSize() + 20));
    detailLine3.setFont(fnt);
    detailLine3.setCharacterSize(40);
    detailLine3.setFillColor(sf::Color::White);
    detailLine3.setPosition(sf::Vector2f(0, detailLine2.getPosition().y + detailLine2.getCharacterSize() + 20));
    detailLine4.setFont(fnt);
    detailLine4.setCharacterSize(40);
    detailLine4.setFillColor(sf::Color::White);
    detailLine4.setPosition(sf::Vector2f(0, detailLine3.getPosition().y + detailLine3.getCharacterSize() + 20));
    detailLine5.setFont(fnt);
    detailLine5.setCharacterSize(40);
    detailLine5.setFillColor(sf::Color::White);
    detailLine5.setPosition(sf::Vector2f(0, detailLine4.getPosition().y + detailLine4.getCharacterSize() + 20));
    detailLine6.setFont(fnt);
    detailLine6.setCharacterSize(40);
    detailLine6.setFillColor(sf::Color::White);
    detailLine6.setPosition(sf::Vector2f(0, detailLine5.getPosition().y + detailLine5.getCharacterSize() + 20));
    detailLine7.setFont(fnt);
    detailLine7.setCharacterSize(40);
    detailLine7.setFillColor(sf::Color::White);
    detailLine7.setPosition(sf::Vector2f(0, detailLine6.getPosition().y + detailLine6.getCharacterSize() + 20));
    detailLine8.setFont(fnt);
    detailLine8.setCharacterSize(40);
    detailLine8.setFillColor(sf::Color::White);
    detailLine8.setPosition(sf::Vector2f(0, detailLine7.getPosition().y + detailLine7.getCharacterSize() + 20));
    detailLine9.setFont(fnt);
    detailLine9.setCharacterSize(40);
    detailLine9.setFillColor(sf::Color::White);
    detailLine9.setPosition(sf::Vector2f(0, detailLine8.getPosition().y + detailLine8.getCharacterSize() + 20));
    detailLine10.setFont(fnt);
    detailLine10.setCharacterSize(40);
    detailLine10.setFillColor(sf::Color::White);
    detailLine10.setPosition(sf::Vector2f(0, detailLine9.getPosition().y + detailLine9.getCharacterSize() + 20));
    detailWindow.setVisible(false);

    //text for inputs
    entry1Txt.setFont(fnt);
    entry2Txt.setFont(fnt);
    entry1Txt.setCharacterSize(60);
    entry2Txt.setCharacterSize(60);
    entry1Txt.setFillColor(sf::Color::White);
    entry2Txt.setFillColor(sf::Color::White);
    entry1Txt.setPosition(0, title.getPosition().y + title.getCharacterSize() + 20);
    entry2Txt.setPosition(0, entry1Txt.getPosition().y + entry1Txt.getCharacterSize() + 20);


    //toggle button
    toggleTxt.setFont(fnt);
    toggleTxt.setCharacterSize(60);
    toggleTxt.setFillColor(sf::Color::White);
    toggleTxt.setString("Click to Toggle");
    //add 20 as a buffer, add 5 to center in button
    toggleTxt.setPosition(0, entry2Txt.getPosition().y + entry2Txt.getCharacterSize() + 25);
    searchToggleButton.setSize(sf::Vector2f(350.0f, 80.0f));
    searchToggleButton.setFillColor(sf::Color::Red);
    searchToggleButton.setPosition(0, entry2Txt.getPosition().y + entry2Txt.getCharacterSize() + 20);

    //go button
    goTxt.setFont(fnt);
    goTxt.setCharacterSize(60);
    goTxt.setFillColor(sf::Color::White);
    goTxt.setString("Go");
    goTxt.setPosition(0, searchToggleButton.getPosition().y + searchToggleButton.getSize().y + 25);
    goButton.setSize(sf::Vector2f(75.0f, 80.0f));
    goButton.setFillColor(sf::Color(20, 110, 20, 255));
    goButton.setPosition(0, searchToggleButton.getPosition().y + searchToggleButton.getSize().y + 20);

    //text related to buttons
    searchTxt.setFont(fnt);
    searchTxt.setCharacterSize(60);
    searchTxt.setFillColor(sf::Color::White);
    searchTxt.setPosition(searchToggleButton.getSize().x + 20, entry2Txt.getPosition().y + entry2Txt.getCharacterSize() + 25);

    //script to run while window is open
    while (mainWindow.isOpen())
    {
        sf::Event mainEvent;
        while (mainWindow.pollEvent(mainEvent))
        {
            //closes both windows
            if (mainEvent.type == sf::Event::Closed)
            {
                mainWindow.close();
                detailWindow.close();
            }

            //test event to toggle detail window display
            if (mainEvent.type == sf::Event::MouseButtonPressed)
            {
                if (mainEvent.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i position = sf::Mouse::getPosition(mainWindow);
                    if (goButton.getGlobalBounds().contains(position.x, position.y))
                    {
                        showDetails = true;
                        timed1 = false;
                        timed2 = false;
                        pathCheck1 = false;
                        pathCheck2 = false;
                        path1.clear();
                        path2.clear();
                        time1 = 0.f;
                        time2 = 0.f;
                        detailLine1.setString("");
                        detailLine2.setString("");
                        detailLine3.setString("");
                        detailLine4.setString("");
                        detailLine5.setString("");
                        detailLine6.setString("");
                        detailLine7.setString("");
                        detailLine8.setString("");
                        detailLine9.setString("");
                        detailLine10.setString("");

                    }
                    //allow text entry
                    if (entry1Txt.getGlobalBounds().contains(position.x, position.y))
                    {
                        txtBox1 = true;
                        txtBox2 = false;
                        detailWindow.setVisible(false);
                        showDetails = false;
                    }
                    else if (entry2Txt.getGlobalBounds().contains(position.x, position.y))
                    {
                        txtBox2 = true;
                        txtBox1 = false;
                        detailWindow.setVisible(false);
                        showDetails = false;
                    }
                    else
                    {
                        txtBox1 = false;
                        txtBox2 = false;
                    }
                    //toggle between search and separation
                    if (searchToggleButton.getGlobalBounds().contains(position.x, position.y) || toggleTxt.getGlobalBounds().contains(position.x, position.y))
                    {
                        searchToggle = !(searchToggle);
                        detailWindow.setVisible(false);
                        showDetails = false;
                    }


                }

            }

            //check for text entry
            //text input with help of this SFML tutorial: https://www.sfml-dev.org/tutorials/2.5/window-events.php
            if (mainEvent.type == sf::Event::TextEntered)
            {
                if (txtBox1)
                {
                    //cout << mainEvent.text.unicode;
                    //backspace
                    if (mainEvent.text.unicode == 010)
                    {
                        entry1 = entry1.substr(0, entry1.size() - 1);
                    }
                    //enter
                    else if (mainEvent.text.unicode == 015)
                    {
                        txtBox1 = false;
                    }
                    else
                    {
                        entry1 += static_cast<char>(mainEvent.text.unicode);
                    }
                }
                else if (txtBox2)
                {
                    //cout << mainEvent.text.unicode;
                    //backspace
                    if (mainEvent.text.unicode == 010)
                    {
                        entry2 = entry2.substr(0, entry2.size() - 1);
                    }
                    //enter
                    else if (mainEvent.text.unicode == 015)
                    {
                        txtBox2 = false;
                    }
                    else
                    {
                        entry2 += static_cast<char>(mainEvent.text.unicode);
                    }
                }
            }
        }

        //hides detail window when closed
        sf::Event detailEvent;
        while (detailWindow.pollEvent(detailEvent))
        {
            if (detailEvent.type == sf::Event::Closed)
            {
                detailWindow.setVisible(false);
                showDetails = false;
            }
        }

        //change search bars
        //entry1 is now editable
        if (txtBox1)
        {

            entry1Txt.setFillColor(sf::Color::Red);
        }
        else
        {
            entry1Txt.setFillColor(sf::Color::White);
        }
        //entry2 is now editable
        if (txtBox2)
        {

            entry2Txt.setFillColor(sf::Color::Red);
        }
        else
        {
            entry2Txt.setFillColor(sf::Color::White);
        }

        //set search bar text
        //set texts in bars so that they can be accessed
        //ISSUES ENTERING A SPACE AT THE BEGINNING OF THE BOX WILL REPLACE TEXT WITH THIS
        if (txtBox1 == false && (entry1.empty() || entry1.at(0) == ' '))
        {
            entry1 = "Click to Enter 1st Film";
        }
        if (txtBox2 == false && (entry2.empty() || entry2.at(0) == ' '))
        {
            entry2 = "Click to Enter 2nd Film";
        }
        entry1Txt.setString(entry1);
        entry2Txt.setString(entry2);

        //set text within search toggle
        if (searchToggle)
        {
            search = "Searching";
        }
        else
        {
            search = "Separation";
        }
        searchTxt.setString(search);

        //draw objects
        mainWindow.clear();
        mainWindow.draw(title);
        mainWindow.draw(entry1Txt);
        if (!(searchToggle))
        {
            mainWindow.draw(entry2Txt);
        }
        mainWindow.draw(searchToggleButton);
        mainWindow.draw(toggleTxt);
        mainWindow.draw(searchTxt);
        mainWindow.draw(goButton);
        mainWindow.draw(goTxt);
        mainWindow.display();

        //Shows detail window
        if (showDetails)
        {
            detailWindow.setVisible(true);
            detailWindow.clear();

            //different details are displayed depending on which button is selected (searching and separating)
            if (searchToggle)
            {
                string ID = list.searchMovies(entry1, IDmap, titleMap);
                if (ID == "tt0000000") {
                    detailLine1.setString("Movie not found. Check input again!");
                    detailWindow.draw(detailLine1);
                }
                else {
                    Movie movie = IDmap[ID];
                    detailLine1.setString("Title: " + movie.getTitle());
                    detailLine2.setString("Release Date: " + movie.getDate());
                    detailLine3.setString("Genre: " + movie.getGenre());
                    detailLine4.setString("IMDB Rating: " + movie.getVote());
                    detailLine5.setString("Duration: " + movie.getDuration() + " minutes");
                    detailLine6.setString("Country: " + movie.getCountry());
                    detailLine7.setString("Language: " + movie.getLanguage());

                    string directors = "";
                    for (int i = 0; i < movie.getDirectors().size() - 1; i++) {
                        directors += movie.getDirectors()[i];
                        directors += ", ";
                    }
                    directors += movie.getDirectors()[movie.getDirectors().size() - 1];
                    detailLine8.setString("Director: " + directors);


                    detailLine9.setString("About: ");
                    string about = movie.getDesc();
                    //wrapping text
                    //resources: https://en.sfml-dev.org/forums/index.php?topic=14976.0
                    //https://www.geeksforgeeks.org/5-different-methods-find-length-string-c/
                    detailLine10.setString(about);
                    //determine if text exceeds bounds of window
                   // while (detailLine10.getGlobalBounds().width > detailWindow.getSize().x)
                    //{
                        //loop through all characters if the string
                        for (int i = 0; i < strlen(about.c_str()); i++)
                        {
                            //if a character is outside of the window
                            if (detailLine10.findCharacterPos(i).x > detailWindow.getSize().x - 10)
                            {
                                //if that character is a space, replace it with a newline character
                                if (about.at(i) == ' ')
                                {
                                    about.at(i) = '\n';
                                }
                                //else find the previous space and replace it with a newline character
                                else
                                {

                                    string temp = about.substr(0, i + 1);
                                    int pos = temp.find_last_of(' ');
                                    about.at(pos) = '\n';
                                }
                                detailLine10.setString(about);
                            }
                        }
                    //}
                    //draws line
                    detailLine10.setString(about);
                    detailWindow.draw(detailLine10);

                    //create a loop that will wrap text for the about section

                    //draw objects
                    detailLine5.setFillColor(sf::Color::White); // reset color from separation search

                    detailWindow.draw(detailLine1);
                    detailWindow.draw(detailLine2);
                    detailWindow.draw(detailLine3);
                    detailWindow.draw(detailLine4);
                    detailWindow.draw(detailLine5);
                    detailWindow.draw(detailLine6);
                    detailWindow.draw(detailLine7);
                    detailWindow.draw(detailLine8);
                    detailWindow.draw(detailLine9);
                }
                
            }
            else
            {
                //create loop to display separation
                string ID1 = "";
                string ID2 = "";
                if (titleMap.find(entry1) != titleMap.end()) {
                    ID1 = titleMap[entry1];
                }
                if (titleMap.find(entry2) != titleMap.end()) {
                    ID2 = titleMap[entry2];
                }
                if (ID1 == ID2) {
                    ID1 = "";
                    ID2 = "";
                }
                
                
                if (!timed1 && IDmap.find(ID1) != IDmap.end() && IDmap.find(ID2) != IDmap.end()) {
                    auto start = chrono::high_resolution_clock::now();
                    if (!pathCheck1) {
                        path1 = list.shortestPath(ID1, ID2);
                        pathCheck1 = true;
                    }
                    auto stop = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
                    time1 = duration.count();
                    timed1 = true;
                }
                string pathText1 = "";
                string pathToText = entry1 + " to " + entry2;
                if (path1.size() > 1) {
                    pathText1 = "Time for BFS: ";
                    detailLine1.setString(pathToText);
                    

                    string separation1 = list.connectMovies(IDmap, path1);
                    //path is in yellow
                    
                    stringstream precision1;
                    precision1 << fixed << setprecision(1) << time1;
                    detailLine2.setString(pathText1 + precision1.str() + " milliseconds.");
                    //wrapping text
                    //resources: https://en.sfml-dev.org/forums/index.php?topic=14976.0
                    //https://www.geeksforgeeks.org/5-different-methods-find-length-string-c/
                    detailLine5.setString(separation1);
                    detailLine5.setFillColor(sf::Color::Yellow);
                    //determine if text exceeds bounds of window
                    //while (detailLine5.getGlobalBounds().width > detailWindow.getSize().x)
                    //{
                        //loop through all characters if the string
                        for (int i = 0; i < strlen(separation1.c_str()); i++)
                        {
                            //if a character is outside of the window
                            if (detailLine5.findCharacterPos(i).x > detailWindow.getSize().x - 10)
                            {
                                //if that character is a space, replace it with a newline character
                                if (separation1.at(i) == ' ')
                                {
                                    separation1.at(i) = '\n';
                                }
                                //else find the previous space and replace it with a newline character
                                else
                                {

                                    string temp = separation1.substr(0, i + 1);
                                    int pos = temp.find_last_of(' ');
                                    separation1.at(pos) = '\n';
                                }
                                detailLine5.setString(separation1);
                            }
                        }
                    //}
                    detailLine5.setString(separation1);
                    
                }
                else {
                    if (entry1 == entry2) {
                        pathText1 = "Identical movies entered. Please submit two different movies.";
                        detailLine1.setString(pathText1);
                        pathCheck2 = true;
                    }
                    else {
                        pathText1 = "No path found.";
                        detailLine1.setString(pathText1);
                        pathCheck2 = true;
                    }
                }
                
                if (!timed2 && IDmap.find(ID1) != IDmap.end() && IDmap.find(ID2) != IDmap.end()) {
                    auto start = chrono::high_resolution_clock::now();
                    if (!pathCheck2) {
                        path2 = list.shortestPath2(ID1, ID2);
                        pathCheck2 = true;
                    }
                    auto stop = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
                    time2 = duration.count();
                    timed2 = true;
                }
                string pathText2 = "";
                
                if (path2.size() > 1) {
                    pathText2 = "Time for IDFS: ";
                    stringstream precision2;
                    precision2 << fixed << setprecision(1) << time2;
                    detailLine3.setString(pathText2 + precision2.str() + " milliseconds.");
                    detailLine4.setString("Path of the movies: ");
                }
                detailWindow.draw(detailLine1);
                detailWindow.draw(detailLine2);
                detailWindow.draw(detailLine3);
                detailWindow.draw(detailLine4);
                detailWindow.draw(detailLine5);
            }

            detailWindow.display();
        }
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
    while (getline(file, line) && index < 15000) { // can change file entries from 10000-15000 by adjusting index
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

        dirLine = line.substr(0, line.find('\t'));
        while (dirLine.find(',') != -1) {
            name = actorLine.substr(0, actorLine.find(','));
            movie.addDirector(name);
            dirLine = dirLine.substr(dirLine.find(',') + 2);
        }
        name = dirLine.substr(0, dirLine.find('\t'));
        movie.addDirector(name);


        titleMap[title] = ID; //map title to the ID
        IDmap[ID] = movie;    //map the ID to the movie

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
