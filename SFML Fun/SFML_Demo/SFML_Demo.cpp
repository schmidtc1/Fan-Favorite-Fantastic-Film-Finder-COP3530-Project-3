#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

//Includes code from the SFML website for creating an SFML Project: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
int main()
{
    //bools for radio buttons
    bool searchMovie = true;
    bool searchPeople = false;
    bool search = true;
    bool separation = false;

    //variables for search bars
    bool txtBox1 = false;
    bool txtBox2 = false;
    string entry1 = "First";
    string entry2 = "Second";

    bool showDetails = false;

    //sf objects
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Film Finder");
    sf::RenderWindow detailWindow(sf::VideoMode(720, 1280), "Details");
    //detailWindow's position is window.x + window's x size and window.y - detailWindow overhang
    detailWindow.setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x, window.getPosition().y - (detailWindow.getSize().y - window.getSize().y)));
    sf::Font fnt;
    sf::Text title;
    sf::Text detailLine1;
    sf::Text detailLine2;
    

    //drawing text
    //text drawn with the help of this SFML tutorial: https://www.sfml-dev.org/tutorials/2.5/graphics-text.php
    //Oswald is licensed under the SIL Open Font License OFL
    //https://scripts.sil.org/cms/scripts/page.php?site_id=nrsi&id=OFL
    if (!(fnt.loadFromFile("Oswald-Medium.ttf")))
    {
        cout << "Font couldn't be loaded. Check that the file is in the right place!" << endl;
    }
    title.setFont(fnt);
    detailLine1.setFont(fnt);
    detailLine2.setFont(fnt);
    title.setCharacterSize(120);
    detailLine1.setCharacterSize(120);
    detailLine2.setCharacterSize(120);
    title.setFillColor(sf::Color::White);
    detailLine1.setFillColor(sf::Color::White);
    detailLine2.setFillColor(sf::Color::White);
    detailLine2.setPosition(sf::Vector2f(0, 120));
    title.setString("Fan-Favorite Fantastic Film Finder");
    detailWindow.setVisible(false);

    //script to run while window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //closes both windows
            if (event.type == sf::Event::Closed)
            {
                window.close();
                detailWindow.close();
            }

            //test event to toggle detail window display
            //DELETE IN FINAL RELEASE
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    if (title.getGlobalBounds().contains(position.x, position.y))
                    {
                        showDetails = true;
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

        //draw objects
        window.clear();
        window.draw(title);
        window.display();

        //Shows detail window
        if (showDetails)
        {
            detailWindow.setVisible(true);
            detailWindow.clear();

            //different details are displayed depending on which button is selected
            if (searchMovie)
            {
                detailLine1.setString("Name: ");
                detailLine2.setString("Date of Birth: ");
            }
            else if (searchPeople)
            {
                detailLine1.setString("Title: ");
                detailLine2.setString("Release Date: ");
            }

            //draw objects
            detailWindow.draw(detailLine1);
            detailWindow.draw(detailLine2);
            detailWindow.display();
        }
    }

    return 0;
}