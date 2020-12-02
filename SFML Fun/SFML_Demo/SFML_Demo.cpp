#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

//Based off of code from the SFML website for creating an SFML Project: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
int main()
{
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
    mainWindow.setPosition(sf::Vector2i(320, 540));
    //detailWindow's position is mainWindow.x + mainWindow's x size and mainWindow.y - detailWindow overhang
    detailWindow.setPosition(sf::Vector2i(mainWindow.getPosition().x + mainWindow.getSize().x, mainWindow.getPosition().y - (detailWindow.getSize().y - mainWindow.getSize().y)));
    
    //maybe add details for genre, rating, and language
    sf::Font fnt;
    sf::Text title;
    sf::Text detailLine1;
    sf::Text detailLine2;
    
    //drawing text
    //text drawn with the help of this SFML tutorial: https://www.sfml-dev.org/tutorials/2.5/graphics-text.php
    //Oswald is licensed under the SIL Open Font License OFL: https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL
    if (!(fnt.loadFromFile("Oswald-Medium.ttf")))
    {
        cout << "Font couldn't be loaded. Check that the file is in the right place!" << endl;
    }
    //title text
    title.setFont(fnt);
    title.setCharacterSize(120);
    title.setFillColor(sf::Color::White);
    title.setString("Fan-Favorite Fantastic Film Finder");

    //detail window text
    detailLine1.setFont(fnt);
    detailLine1.setCharacterSize(120);
    detailLine1.setFillColor(sf::Color::White);
    detailLine2.setFont(fnt);
    detailLine2.setCharacterSize(120);
    detailLine2.setFillColor(sf::Color::White);
    detailLine2.setPosition(sf::Vector2f(0, detailLine1.getPosition().y + detailLine1.getCharacterSize() + 20));
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
                    }
                    //allow text entry
                    if (entry1Txt.getGlobalBounds().contains(position.x, position.y))
                    {
                        txtBox1 = true;
                        txtBox2 = false;
                    }
                    else if (entry2Txt.getGlobalBounds().contains(position.x, position.y))
                    {
                        txtBox2 = true;
                        txtBox1 = false;
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
                    }


                }

            }

            //check for text entry
            //text input with help of this SFML tutorial: https://www.sfml-dev.org/tutorials/2.5/window-events.php
            if (mainEvent.type == sf::Event::TextEntered)
            {
                if (txtBox1)
                {
                    cout << mainEvent.text.unicode;
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
                    cout << mainEvent.text.unicode;
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
            detailLine1.setString("Title: ");
            detailLine2.setString("Release Date: ");
  

            //draw objects
            detailWindow.draw(detailLine1);
            detailWindow.draw(detailLine2);
            detailWindow.display();
        }
    }

    return 0;
}