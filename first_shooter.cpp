#include <SFML\Graphics.hpp>
#include <cmath>
#include <vector>

#define PI 3.14159265

class Bullet {
public:
    Bullet(float _angle): angle(_angle)
    {
        bullet.setRadius(15);
        bullet.setFillColor(sf::Color::Blue);
    }

    void fire() 
    {
        bullet.move(10 * sin(angle * PI / 180), -10 * cos(angle * PI / 180));
    }

    void draw(sf::RenderWindow& window) 
    {
        window.draw(bullet);
    }

    void setPos(float x, float y) 
    {
        bullet.setPosition(x, y);
    }

private:
    sf::CircleShape bullet;
    float angle;
};

void Motion(sf::Sprite& circle, sf::RenderWindow& window);
void Laser(sf::Sprite& circle, sf::RenderWindow& window);
void NewBullet(sf::Sprite& circle, sf::RenderWindow& window, sf::Clock& clock, std::vector<Bullet>& bulletVec);

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen, settings);
    sf::Clock clock;
    sf::Texture texture;
    texture.loadFromFile("Bee-256.png");

    sf::Sprite circle(texture);
    circle.setPosition(450, 350);
    sf::Vector2u circleSize = circle.getTexture()->getSize();
    circle.setOrigin(circleSize.x / 2, circleSize.y / 2);

    std::vector<Bullet> bulletVec;

    window.setKeyRepeatEnabled(true);
    sf::Time oldTime = clock.getElapsedTime();
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

        Motion(circle, window);
        window.clear(sf::Color::White);
        window.draw(circle);
        Laser(circle, window);
        sf::Time newTime = clock.getElapsedTime();
        if (newTime.asMilliseconds() - oldTime.asMilliseconds() > 100)
        {
            NewBullet(circle, window, clock, bulletVec);
            oldTime = newTime;
        }
        for (int i = 0; i < bulletVec.size(); i++) {
            bulletVec[i].draw(window);
            bulletVec[i].fire();
        }
        window.display();
    }

    return 0;
}

void Motion(sf::Sprite& circle, sf::RenderWindow& window)
{
    float angle = circle.getRotation();

    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        circle.move(-10 * cos(angle * PI / 180), -10 * sin(angle * PI / 180));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        circle.move(10 * cos(angle * PI / 180), 10 * sin(angle * PI / 180));
    }*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        circle.move(10 * sin(angle * PI / 180), -10 * cos(angle * PI / 180));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        circle.move(-10 * sin(angle * PI / 180), 10 * cos(angle * PI / 180));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        circle.rotate(-5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        circle.rotate(5);
    }

    int moveX = 0, moveY = 0;
    unsigned sizeX = window.getSize().x;
    unsigned sizeY = window.getSize().y;
    auto bounds = circle.getGlobalBounds();

    if (bounds.left < 0)
    {
        moveX -= bounds.left;
    }
    else if (bounds.left + bounds.width > sizeX)
    {
        moveX -= (bounds.left + bounds.width - sizeX);
    }
    if (bounds.top < 0)
    {
        moveY -= bounds.top;
    }
    else if (bounds.top + bounds.height > sizeY)
    {
        moveY -= (bounds.top + bounds.height - sizeY);
    }

    circle.move(moveX, moveY);
}

void Laser(sf::Sprite& circle, sf::RenderWindow& window)
{
    float angle = circle.getRotation();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        sf::Vertex line[]
        {
            sf::Vertex(circle.getPosition(), sf::Color::Red),
            sf::Vertex(sf::Vector2f(5000 * sin(angle * PI / 180) + circle.getPosition().x,
            -5000 * cos(angle * PI / 180) + circle.getPosition().y),
            sf::Color::Red)
        };
        window.draw(line, 2, sf::Lines);
    }
}

void NewBullet(sf::Sprite& circle, sf::RenderWindow& window, sf::Clock& clock, std::vector<Bullet>& bulletVec)
{
    float angle = circle.getRotation();
    bool isFiring = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        isFiring = true;
    }

    if (isFiring == true) {
        
        Bullet newBullet(angle);
        newBullet.setPos(
            circle.getPosition().x,
            circle.getPosition().y
        );

        bulletVec.push_back(newBullet);
        isFiring = false;
    }
}
