#include <SFML\Graphics.hpp>



int foo(sf::RenderWindow& window,sf::Vertex line[], int deep)
{
    if (deep == 0)
    {
        return 1;
    }

    int pointH1x = line[0].position.x;
    int pointH1y = line[0].position.y;
    int pointH2x = line[1].position.x;
    int pointH2y = line[1].position.y;
    int pointH3x = line[2].position.x;
    int pointH3y = line[2].position.y;

    int pointM1x = (pointH1x + pointH2x) / 2;
    int pointM1y = (pointH1y + pointH2y) / 2;
    int pointM2x = (pointH1x + pointH3x) / 2;
    int pointM2y = (pointH1y + pointH3y) / 2;
    int pointM3x = (pointH2x + pointH3x) / 2;
    int pointM3y = (pointH2y + pointH3y) / 2;


    
    sf::Vertex line1[] =
    {
          sf::Vertex(sf::Vector2f(pointH1x, pointH1y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointM1x, pointM1y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointM2x, pointM2y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointH1x, pointH1y), sf::Color::Red)
    };

    sf::Vertex line2[] =
    {
          sf::Vertex(sf::Vector2f(pointH2x, pointH2y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointM1x, pointM1y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointM3x, pointM3y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointH2x, pointH2y), sf::Color::Red)
    };

    sf::Vertex line3[] =
    {
          sf::Vertex(sf::Vector2f(pointH3x, pointH3y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointM2x, pointM2y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointM3x, pointM3y), sf::Color::Red),
          sf::Vertex(sf::Vector2f(pointH3x, pointH3y), sf::Color::Red)
    };

    window.draw(line1, 4, sf::LinesStrip);
    window.draw(line2, 4, sf::LinesStrip);
    window.draw(line3, 4, sf::LinesStrip);
    foo(window, line1, deep - 1);
    foo(window, line2, deep - 1);
    foo(window, line3, deep - 1);
}


int main()
{
  sf::RenderWindow window(sf::VideoMode(1000, 800), "My window");
  window.setFramerateLimit(30);
  while (window.isOpen())
  {
    
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
          {
              window.close();
          }
      }

      sf::Vertex line1[] =
      {
            sf::Vertex(sf::Vector2f(500,10), sf::Color::Red),
            sf::Vertex(sf::Vector2f(10, 790), sf::Color::Green),
            sf::Vertex(sf::Vector2f(990, 790), sf::Color::Blue),
            sf::Vertex(sf::Vector2f(500,10), sf::Color::Red)
      };
   
      window.clear(sf::Color::White);
      window.draw(line1, 4, sf::LinesStrip);
      foo(window, line1, 10);
      window.display();
  }

  return 0;
}
