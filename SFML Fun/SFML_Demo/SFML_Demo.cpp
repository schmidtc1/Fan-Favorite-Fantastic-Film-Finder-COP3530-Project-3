#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "Film Findr");
    sf::CircleShape shape(100.f);
    sf::Text txt;
    txt.setString("Hello World");
    txt.setFillColor(sf::Color::White);
    txt.setCharacterSize(50);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(txt);
        window.display();
    }

    return 0;
}