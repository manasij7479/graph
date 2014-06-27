#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "graph.hpp"
#include "layout/random_layout.hpp"
#include "test/testgraph.h" //switch to generators soon
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(600, 600), "LayoutTester");

    auto g = getOriginalTestGraph();
    
    graph::RandomLayout<decltype(g)> layout(g,{300,300},{100,100});
    sf::CircleShape c(3,10);
    c.setFillColor(sf::Color::Blue);
    sf::Font font;
    if(!font.loadFromFile("courier.ttf"))
        throw std::runtime_error("Fout loading failed");
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(20);
    t.setColor(sf::Color::Black);
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);
        
        // draw everything here...
        for(auto x=g.begin();x!=g.end();++x)
        {
            graph::Point p =layout.Vertex(x->first);
            c.setPosition(p.x,p.y);
            t.setString(x->first);
            t.setPosition(p.x+5,p.y-5);
            window.draw(c);
            window.draw(t);
            for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
            {
                graph::Curve c=layout.Edge(x->first,y->first);
                if(c.size()!=2)
                    throw std::runtime_error("wtf");
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(c[0].x, c[0].y)),
                    sf::Vertex(sf::Vector2f(c[1].x, c[1].y))
                };
                line[0].color=sf::Color::Black;
                line[1].color=sf::Color::Black;
                window.draw(line, 2, sf::Lines);
            }
        }
        
        // end the current frame
        
        window.display();
    }

    return 0;
}