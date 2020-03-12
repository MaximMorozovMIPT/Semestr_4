#include <SFML\Graphics.hpp>
#include <vector>
#include <cmath>
#include "vector2.h"

#define PI 3.14159265358979323846

class Charge
{
public:
    Charge(sf::Vector2i position, sf::Color _color, int _positive)
    {
        for (int i = 0; i < 8; ++i)
        {
            Vector2 newV(-1, 0);
            newV.rotate(2 * PI / 8 * i);
            vect.push_back(newV);
            sf::VertexArray newVArr(sf::LinesStrip);
            lines.push_back(newVArr);
        }
        charge.setPosition(sf::Vector2f(position.x, position.y));
        charge.setFillColor(_color);
        charge.setRadius(20);
        charge.setOrigin(20, 20);
        color = _color;
        positive = _positive; 
    }
    sf::CircleShape charge;
    int positive;
    std::vector<Vector2> vect;
    std::vector<sf::VertexArray> lines;
    sf::Color color;
};

bool CheckPointInside(std::vector<Charge>& charges, sf::CircleShape& charge, float x, float y);
void Draw(sf::RenderWindow& window, std::vector<Charge>& charges);
void CreateField(sf::RenderWindow& window, std::vector<Charge>& charges, int positive);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen);
    window.setFramerateLimit(30);
    std::vector<Charge> chargeVector;

    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();

    while (window.isOpen())
    {

        sf::Time curTime = clock.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (curTime.asMilliseconds() - prevTime.asMilliseconds() > 100))
        {
            CreateField(window, chargeVector, 1);
            prevTime = curTime;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && (curTime.asMilliseconds() - prevTime.asMilliseconds() > 100))
        {
            CreateField(window, chargeVector, -1);
            prevTime = curTime;
        }
    }

  return 0;
}

bool CheckPointInside(std::vector<Charge>& charges, sf::CircleShape& charge, float x, float y)
{
    sf::Vector2f n = charge.getPosition();
    for (auto& c : charges)
    {
        sf::Vector2f f = c.charge.getPosition();
        if ((f.x == n.x) && (f.y == n.y))
            continue;

        sf::Vector2f v = f - sf::Vector2f(x, y);
        if ((v.x * v.x + v.y * v.y) <= 20 * 20)
            return true;
    }

    return false;
}

void CreateField(sf::RenderWindow& window, std::vector<Charge>& charges, int positive)
{
    const int offset = 10;
    const int step = 10;
    window.clear(sf::Color::White);
    sf::Color color;
    if (positive == 1)
    {
        color = sf::Color::Red;
    }
    else
    {
        color = sf::Color::Blue;
    } 
    Charge charge(sf::Mouse::getPosition(window), color, positive);
    charges.push_back(charge);
   
    for (auto& charge : charges)
    {
        for (int i = 0; i < 8; ++i)
        {
            charge.lines[i].clear();

            float x = charge.charge.getPosition().x + charge.vect[i].x;
            float y = charge.charge.getPosition().y + charge.vect[i].y;
            charge.lines[i].append(sf::Vertex(sf::Vector2f(x, y), charge.color));

            while ((x > (0 - offset)) && (x < (window.getSize().x + offset)) && (y > (0 - offset)) && (y < (window.getSize().y + offset)))
            {
                Vector2 resulted(0, 0);
                for (auto& c : charges)
                {
                    Vector2 v(x - c.charge.getPosition().x, y - c.charge.getPosition().y);
                    v = v / v.squareLen();
                    resulted += v * c.positive;
                }
                resulted = resulted.norm();
                x += step * resulted.x * charge.positive;
                y += step * resulted.y * charge.positive;

                charge.lines[i].append(sf::Vertex(sf::Vector2f(x, y), charge.color));
                if (CheckPointInside(charges, charge.charge, x, y))
                {
                    break;
                }
            }
        }
    }

    Draw(window, charges);
    window.display();
}

void Draw(sf::RenderWindow& window, std::vector<Charge>& charges)
{
    for (auto& charge : charges)
    {
        for (auto& line : charge.lines)
        {
            window.draw(line);
        }
    }
    for (auto& charge : charges)
    {
        window.draw(charge.charge);
    }
}