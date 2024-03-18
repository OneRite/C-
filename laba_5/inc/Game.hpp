#pragma once
#include <string>
#include <thread>

namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		void Setup(int n)
		{
			m_n = n;
			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);

			srand(time(0));

			m_c = new mt::Circle[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 1;
				int x, y;
				bool intersects;
				do {
					intersects = false;
					x = rand() % (1000 - 2 * r) + r;
					y = rand() % (600 - 2 * r) + r;
					for (int j = 0; j < i; ++j) {
						float dx = x - m_c[j].X();
						float dy = y - m_c[j].Y();
						float distance = sqrt(dx * dx + dy * dy);
						if (distance < r + m_c[j].R()) {
							intersects = true;
							break;
						}
					}
				} while (intersects);

				int v = rand() % 50 + 10;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}
		}

		
		void TouchBorder(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();

			if (x + r >= m_width || x - r <= 0)
			{
				obj.Alfa(pi - obj.Alfa());
			}

			if (y + r >= m_height || y - r <= 0)
			{
				obj.Alfa(2*pi-obj.Alfa());
			}

		}
		void CheckCollisions()
		{
			for (int i = 0; i < m_n; ++i)
			{
				for (int j = i + 1; j < m_n; ++j)
				{
					float dx = m_c[j].X() - m_c[i].X();
					float dy = m_c[j].Y() - m_c[i].Y();
					float distance = sqrt(dx * dx + dy * dy);
					float minDist = m_c[i].R() + m_c[j].R();

					if (distance <= minDist)
					{
						// Нормализуем вектор разности для получения направления столкновения
						dx /= distance;
						dy /= distance;

						// Вычисляем новые скорости для шаров
						float vx1 = m_c[i].Alfa() * cos(m_c[i].Alfa());
						float vy1 = m_c[i].Alfa() * sin(m_c[i].Alfa());
						float vx2 = m_c[j].Alfa() * cos(m_c[j].Alfa());
						float vy2 = m_c[j].Alfa() * sin(m_c[j].Alfa());

						// Проекции скоростей на вектор столкновения
						float v1n = dx * vx1 + dy * vy1;
						float v2n = dx * vx2 + dy * vy2;

						// Вычисляем новые скорости после столкновения
						float v1t = -dy * vx1 + dx * vy1;
						float v2t = -dy * vx2 + dx * vy2;

						// Проекции скоростей после столкновения
						float v1n_ = (v1n * (m_c[i].R() - m_c[j].R()) + 2.0f * m_c[j].R() * v2n) / (m_c[i].R() + m_c[j].R());
						float v2n_ = (v2n * (m_c[j].R() - m_c[i].R()) + 2.0f * m_c[i].R() * v1n) / (m_c[i].R() + m_c[j].R());

						// Обновляем скорости шаров
						vx1 = dx * v1n_ + -dy * v1t;
						vy1 = dy * v1n_ + dx * v1t;
						vx2 = dx * v2n_ + -dy * v2t;
						vy2 = dy * v2n_ + dx * v2t;

						// Обновляем углы
						m_c[i].Alfa(atan2(vy1, vx1));
						m_c[j].Alfa(atan2(vy2, vx2));
					}
				}
			}
		}
		void LifeCycle()
		{
			sf::Clock clock;
			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				for (int i = 0; i < m_n; i++)
					m_c[i].Move(dt);

				CheckCollisions(); // Проверяем столкновения

				for (int i = 0; i < m_n; i++)
					TouchBorder(m_c[i]);

				m_window.clear();
				for (int i = 0; i < m_n; i++)
					m_window.draw(m_c[i].Get());
				m_window.display();
			}
		}
	};

}