#include <SFML/Graphics.hpp>
#include <cmath>
#include <optional>

int main()
{
    const float windowWidth{ 400.f };
    const float windowHeight{ 400.f };
    const float ballRadius{ 25.f };

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

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(floor);
        window.display();
    }

    return 0;
}