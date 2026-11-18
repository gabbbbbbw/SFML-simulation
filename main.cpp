#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>
#include <algorithm>

void applygravity(
    sf::Vector2f& velocity,
    const float gravity,
    const float deltaTime,
    const bool isgrounded)
{
    if (!isgrounded) {
        velocity.y += gravity * deltaTime;
    }
}

void updateposition(
    sf::CircleShape& ball,
    const sf::Vector2f& velocity,
    const float deltaTime) {
    ball.move(velocity * deltaTime);
}

int main()
{
    const float windowWidth{ 400.f };
    const float windowHeight{ 400.f };
    const float ballRadius{ 25.f };

    const float gravity{ 800.f };

    sf::RenderWindow window(
        sf::VideoMode({ 400u, 400u }),
        "Bouncing Ball Simulation"
    );

    window.setFramerateLimit(60);

    sf::CircleShape ball(ballRadius);
    ball.setOrigin({ ballRadius, ballRadius });
    ball.setFillColor(sf::Color::Cyan);
    ball.setPosition({
        windowWidth / 2.f,
        windowHeight / 5.f
        });

    sf::RectangleShape floor;
    floor.setSize({ windowWidth, 20.f });
    floor.setFillColor(sf::Color::White);
    floor.setPosition({ 0.f, 380.f });

    sf::Vector2f velocity{ 0.f,0.f };
    bool isgrounded{ false };

    sf::Clock clock;

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        applygravity(velocity, gravity, deltaTime, isgrounded);

        updateposition(ball, velocity, deltaTime);
        
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(floor);
        window.display();
    }

    return 0;
}