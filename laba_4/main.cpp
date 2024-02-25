#include <SFML/Graphics.hpp>
#include <iostream>


class Shape {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
public:
    Circle(float x, float y, float radius) {
        m_circle.setPosition(x, y);
        m_circle.setRadius(radius);
        m_circle.setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_circle);
    }

private:
    sf::CircleShape m_circle;
};

class Triangle : public Shape {
public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
        m_triangle.setPointCount(3);
        m_triangle.setPoint(0, sf::Vector2f(x1, y1));
        m_triangle.setPoint(1, sf::Vector2f(x2, y2));
        m_triangle.setPoint(2, sf::Vector2f(x3, y3));
        m_triangle.setFillColor(sf::Color::Green);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_triangle);
    }

private:
    sf::ConvexShape m_triangle;
};

class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height) {
        m_rectangle.setPosition(x, y);
        m_rectangle.setSize(sf::Vector2f(width, height));
        m_rectangle.setFillColor(sf::Color::Blue);
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_rectangle);
    }

private:
    sf::RectangleShape m_rectangle;
};

class Line : public Shape {
public:
    Line(float x1, float y1, float x2, float y2) {
        m_line = sf::VertexArray(sf::Lines, 2);
        m_line[0].position = sf::Vector2f(x1, y1);
        m_line[1].position = sf::Vector2f(x2, y2);
        m_line[0].color = sf::Color::Yellow;
        m_line[1].color = sf::Color::Yellow;
    }

    void draw(sf::RenderWindow& window) override {
        window.draw(m_line);
    }

private:
    sf::VertexArray m_line;
};

int main() {
    const int N = 5; // Задаем количество фигур

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shapes");

    std::vector<std::unique_ptr<Shape>> shapes;

    srand(time(nullptr));

    for (int i = 0; i < N; ++i) {
        int shapeType = rand() % 4; // Генерируем случайный тип фигуры: 0 - круг, 1 - треугольник, 2 - прямоугольник, 3 - линия

        float x = static_cast<float>(rand() % 700);
        float y = static_cast<float>(rand() % 500);

        switch (shapeType) {
        case 0:
            shapes.push_back(std::make_unique<Circle>(x, y, 50.f));
            break;
        case 1:
            shapes.push_back(std::make_unique<Triangle>(x, y, x + 100, y, x + 50, y + 100));
            break;
        case 2:
            shapes.push_back(std::make_unique<Rectangle>(x, y, 80.f, 50.f));
            break;
        case 3:
            shapes.push_back(std::make_unique<Line>(x, y, x + 100, y + 100));
            break;
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (const auto& shape : shapes) {
            shape->draw(window);
        }

        window.display();
    }

    return 0;
}
