#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

const float gravity = 165.0f; // Ускорение свободного падения 
const float height = 100.0f; //высота шарика
const sf::Vector2f WINDOW_SIZE(800, 600); 

struct Ball {
    sf::CircleShape shape;
    float velocity; //коэф. скорости падения
    float bounceDamping; 
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Falling Balls with Bounce");
    window.setFramerateLimit(60);

    std::vector<Ball> balls;
    // создаем три мяча разного размера 
    Ball ball1;
    ball1.shape.setRadius(20.0f);
    ball1.shape.setFillColor(sf::Color::Yellow);
    ball1.shape.setPosition(WINDOW_SIZE.x / 4 - ball1.shape.getRadius(), height);
    ball1.velocity = 0.0f; 
    ball1.bounceDamping = 0.9f; //высота отскова

    Ball ball2;
    ball2.shape.setRadius(40.0f);
    ball2.shape.setFillColor(sf::Color::Blue);
    ball2.shape.setPosition(WINDOW_SIZE.x / 2 - ball2.shape.getRadius(), height);
    ball2.velocity = 0.0f;
    ball2.bounceDamping = 0.8f;

    Ball ball3;
    ball3.shape.setRadius(60.0f);
    ball3.shape.setFillColor(sf::Color::Red);
    ball3.shape.setPosition(3 * WINDOW_SIZE.x / 4 - ball3.shape.getRadius(), height);
    ball3.velocity = 0.0f;
    ball3.bounceDamping = 0.7f;

    balls.push_back(ball1);
    balls.push_back(ball2);
    balls.push_back(ball3);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        for (auto& ball : balls) {
            ball.velocity += gravity * deltaTime;
            ball.shape.move(0, ball.velocity * deltaTime);

            if (ball.shape.getPosition().y + 2 * ball.shape.getRadius() >= WINDOW_SIZE.y) {
                ball.shape.setPosition(ball.shape.getPosition().x, WINDOW_SIZE.y - 2 * ball.shape.getRadius());
                ball.velocity = -ball.velocity * ball.bounceDamping;

                // чтобы шарик бесконечно не отскакивал
                if (std::abs(ball.velocity) < 1.0f) {
                    ball.velocity = 0.0f;
                }
            }
        }

        window.clear();
        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }
        window.display();
    }

    return 0;
}

