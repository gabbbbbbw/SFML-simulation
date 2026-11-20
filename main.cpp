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

void handlefloorcollision(
    sf::CircleShape& ball,
    const sf::RectangleShape& floor,
    sf::Vector2f& velocity,
    const float restitution,
    const float restingspeed,
    bool& isgrounded)
{
    const sf::FloatRect ballbounds = ball.getGlobalBounds();
    const sf::FloatRect floorbounds = floor.getGlobalBounds();

    const float ballbottom = ballbounds.position.y + ballbounds.size.y;
    const float floortop = floorbounds.position.y;

    const bool isabovefloor = ballbounds.position.y < floortop;
    const bool reachedfloor = ballbottom >= floortop -0.1f;

    if (isabovefloor && reachedfloor && velocity.y >= 0.f) {
        ball.move({ 0.f,floortop - ballbottom });
        velocity.y = -velocity.y * restitution;

        if (std::abs(velocity.y) < restingspeed) {

            velocity.y = 0.f;
            isgrounded = true;

        }
        else {
            isgrounded = false;
        }
    }
    else {
        isgrounded = false;
    }
    
}

void resetsimulation(
    sf::CircleShape& ball,
    sf::Vector2f& velocity,
    bool& isgrounded,
    const float windowwidth,
    const float windowheight)
{
    ball.setPosition({ windowwidth / 2,windowheight / 5 });
    velocity = { 0.f,0.f };
    isgrounded = false;
}

int main()
{
    const float windowWidth{ 400.f };
    const float windowHeight{ 400.f };
    const float ballRadius{ 25.f };

    const float gravity{ 800.f };
    const float restitution{ 0.75f };
    const float restingspeed{ 20.f };

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
    bool ispaused{ false };

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
            if (const auto* keypressed =
                event->getIf<sf::Event::KeyPressed>())
            {
                if (keypressed->code == sf::Keyboard::Key::Space)
                {
                    ispaused = !ispaused;
                }

                if (keypressed->code == sf::Keyboard::Key::R)
                {
                    resetsimulation(
                        ball,
                        velocity,
                        isgrounded,
                        windowWidth,
                        windowHeight
                    );
                }
            }
        }
        if (!ispaused) {
            applygravity(velocity, gravity, deltaTime, isgrounded);

            updateposition(ball, velocity, deltaTime);

            handlefloorcollision(ball, floor, velocity, restitution, restingspeed, isgrounded);
        }
        
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(floor);
        window.display();
    }

    return 0;
}