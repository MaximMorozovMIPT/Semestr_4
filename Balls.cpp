#include <SFML\Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <random>

#define PI 3.14159265358979323846

class Ball
{
public:
    Ball(sf::Vector2i position, std::default_random_engine& generator)
    {
        ball.setPosition(sf::Vector2f(position.x, position.y));

        std::uniform_int_distribution<int> radGen(35, 65);
        radius = radGen(generator);
        ball.setRadius(radius);
        ball.setOrigin(radius, radius);
        mass = radius * radius;
       
        std::uniform_int_distribution<int> colorGen(0, 255);
        int red = colorGen(generator);
        int green = colorGen(generator);
        int blue = colorGen(generator);
        ball.setFillColor(sf::Color(red, green, blue, 255));

        std::uniform_int_distribution<int> speedGen(-10, 10);
        speed.x = speedGen(generator);
        speed.y = speedGen(generator);
    }

    sf::CircleShape ball;
    sf::Color color;
    sf::Vector2f speed;
    int mass;
    int radius;
};

void Draw(sf::RenderWindow& window, std::vector<Ball>& balls);
void Move(sf::RenderWindow& window, std::vector<Ball>& balls);
void Collisions(sf::RenderWindow& window, std::vector<Ball>& balls);
bool Intersection(Ball& ball1, Ball& ball2);
void Pushing(Ball& ball1, Ball& ball2);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    std::vector<Ball> balls;
    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    std::default_random_engine generator;

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (curTime.asMilliseconds() - prevTime.asMilliseconds() > 200))
        {
            balls.push_back({sf::Mouse::getPosition(), generator});
            prevTime = curTime;
        }

        Collisions(window, balls);
        Move(window, balls);
        Draw(window, balls);
       // std::cout << balls.size() << std::endl;

        window.display();
    }

    return 0;
}

void Draw(sf::RenderWindow& window, std::vector<Ball>& balls)
{
    window.clear(sf::Color::White);
    for (auto& ball : balls)
    {
        window.draw(ball.ball);
    }
}

void Move(sf::RenderWindow& window, std::vector<Ball>& balls)
{
    for (auto& ball : balls)
    {
        int moveX = 0, moveY = 0;
        unsigned sizeX = window.getSize().x;
        unsigned sizeY = window.getSize().y;
        auto bounds = ball.ball.getGlobalBounds();

        if (bounds.left < 0)
        {
            moveX -= bounds.left;
            ball.speed.x *= -1;
        }
        else if (bounds.left + bounds.width > sizeX)
        {
            moveX -= (bounds.left + bounds.width - sizeX);
            ball.speed.x *= -1;
        }
        if (bounds.top < 0)
        {
            moveY -= bounds.top;
            ball.speed.y *= -1;
        }
        else if (bounds.top + bounds.height > sizeY)
        {
            moveY -= (bounds.top + bounds.height - sizeY);
            ball.speed.y *= -1;
        }
        ball.ball.move(moveX, moveY);
        ball.ball.move(ball.speed);
    }

}

void Collisions(sf::RenderWindow& window, std::vector<Ball>& balls)
{
    for (int i = 0; i < balls.size(); ++i)
    {
        for (int j = i + 1; j < balls.size(); ++j)
        {
            if (Intersection(balls[i], balls[j]))
            {
                Pushing(balls[i], balls[j]);
            }
        }
    }

}

bool Intersection(Ball& ball1, Ball& ball2)
{
    int x1 = ball1.ball.getPosition().x;
    int x2 = ball2.ball.getPosition().x;
    int y1 = ball1.ball.getPosition().y;
    int y2 = ball2.ball.getPosition().y;
    int r1 = ball1.radius;
    int r2 = ball2.radius;
    if (pow(x1 - x2, 2) + pow(y1 - y2, 2) <= pow(r1 + r2, 2))
    {
        return true;
    }
    else return false;
}

void Pushing(Ball& ball1, Ball& ball2)
{
    float x1 = ball1.ball.getPosition().x;
    float x2 = ball2.ball.getPosition().x;
    float y1 = ball1.ball.getPosition().y;
    float y2 = ball2.ball.getPosition().y;
    int r1 = ball1.radius;
    int r2 = ball2.radius;

    // Distance between balls
    float fDistance = sqrtf(pow(x1 - x2, 2) + pow(y1 - y2, 2));

    // Normal
    float nx = (x1 - x2) / fDistance;
    float ny = (y1 - y2) / fDistance;

    // Tangent
    float tx = -ny;
    float ty = nx;

    // Dot Product Tangent
    float dpTan1 = ball1.speed.x * tx + ball1.speed.y * ty;
    float dpTan2 = ball2.speed.x * tx + ball2.speed.y * ty;

    // Dot Product Normal
    float dpNorm1 = ball1.speed.x * nx + ball1.speed.y * ny;
    float dpNorm2 = ball2.speed.x * nx + ball2.speed.y * ny;

    // Conservation of momentum in 1D
    float m1 = (dpNorm1 * (ball1.mass - ball2.mass) + 2.0f * ball2.mass * dpNorm2) / (ball1.mass + ball2.mass);
    float m2 = (dpNorm2 * (ball2.mass - ball1.mass) + 2.0f * ball1.mass * dpNorm1) / (ball1.mass + ball2.mass);
    float intersectDistance = sqrt(fabs(pow(r1 + r2, 2) - pow(x1 - x2, 2) - pow(y1 - y2, 2)));
    float intersectDistanceX = fabs(intersectDistance * nx);
    float intersectDistanceY = fabs(intersectDistance * ny);

    float move1X = 0;
    float move2X = 0;
    float move1Y = 0;
    float move2Y = 0;
    if (x1 >= x2)
    {
        move1X = intersectDistanceX;
        move2X = - intersectDistanceX;
    }
    else
    {
        move1X = -intersectDistanceX;
        move2X = intersectDistanceX;
    }
    if (y1 >= y2)
    {
        move1Y = intersectDistanceY;
        move2Y = -intersectDistanceY;
    }
    else
    {
        move1Y = -intersectDistanceY;
        move2Y = intersectDistanceY;
    }
    ball1.ball.move(move1X / 4, move1Y / 4);
    ball2.ball.move(move2X / 4, move2Y / 4);

    // Update ball velocities
    ball1.speed.x = tx * dpTan1 + nx * m1;
    ball1.speed.y = ty * dpTan1 + ny * m1;
    ball2.speed.x = tx * dpTan2 + nx * m2;
    ball2.speed.y = ty * dpTan2 + ny * m2;
}
