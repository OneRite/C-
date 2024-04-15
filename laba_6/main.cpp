#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Создаем окно размером 800x600 пикселей
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Spaceship and space");

    // Загружаем текстуры изображений
    sf::Texture backgroundTexture;
    sf::Texture spaceshipTexture;
    // Создаем спрайты для отображения изображений, а также отображение ошибок в случае незагрузки текстурки
    sf::Sprite spriteBackgroundTexture;
    sf::Sprite spriteSpaceshipTexture;

    if (!backgroundTexture.loadFromFile("assets\\background.jpg")) {
        std::cout << "Error loading background.jpg" << std::endl;
        return false;
    }
    if (!spaceshipTexture.loadFromFile("assets\\spaceship.png")) {
        std::cout << "Error loading spaceship.png" << std::endl;
        return false;
    }

    spriteBackgroundTexture.setTexture(backgroundTexture);
    spriteSpaceshipTexture.setTexture(spaceshipTexture);

    // Устанавливаем позицию корабля
    spriteSpaceshipTexture.setPosition(400, 200);
    
    // Уменьшаем размер корабля
    spriteSpaceshipTexture.setScale(0.10f, 0.10f); // Масштаб по осям X и Y

    // Главный цикл приложения
    while (window.isOpen()) {
        // Проверка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Управление кораблем с помощью клавиатуры
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            spriteSpaceshipTexture.move(-1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spriteSpaceshipTexture.move(1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            spriteSpaceshipTexture.move(0.0f, -1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            spriteSpaceshipTexture.move(0.0f, 1.0f);
        }

        // Очистка экрана
        window.clear();

        // Отрисовка фона и корабля
        window.draw(spriteBackgroundTexture);
        window.draw(spriteSpaceshipTexture);

        // Обновление экрана
        window.display();
    }

    return 0;
}
