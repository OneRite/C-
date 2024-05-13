#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <bullet.hpp>


namespace mt
{

	class Ship
	{
		const int m_bulletR = 10;
		float m_v_bullet = 500;

		float m_x, m_y;
		float m_alpha;
		float m_v;
		float m_r;
		sf::Texture m_textureShip;
		sf::Sprite m_spriteShip;
		float m_scaleFactor = 0.2f;

		Bullet bullet;

		std::vector<Bullet> m_bullets;

	public:
		Ship() = default;
		Ship(float x, float y)
		{
			m_x = x;
			m_y = y;
			bullet = Bullet();
			m_bullets.clear();
		}

		bool Setup(float x, float y)
		{
			m_x = x;
			m_y = y;
			m_alpha = 0;
			m_v = 0;

			if (!m_textureShip.loadFromFile("assets\\falcon.png"))
			{
				std::cout << "Error while loading falcon.png" << std::endl;
				return false;
			}
			m_spriteShip.setTexture(m_textureShip);

			m_spriteShip.setScale(m_scaleFactor, m_scaleFactor);
			m_spriteShip.setOrigin(m_textureShip.getSize().x / 2, m_textureShip.getSize().y / 2);
			m_spriteShip.setPosition(m_x, m_y);
			m_spriteShip.setRotation(m_alpha);

			if (m_textureShip.getSize().x > m_textureShip.getSize().y)
				m_r = m_scaleFactor * m_textureShip.getSize().x / 2;
			else
				m_r = m_scaleFactor * m_textureShip.getSize().y / 2;

		}


		void UpdateBullets(float dt)
		{
			for (auto& bullet : m_bullets)
			{
				bullet.Move(dt);
			}
		}

		void Attack()
		{
			float alphaRad = acos(-1) * m_alpha / 180;
			m_bullets.push_back(Bullet(m_x, m_y, m_bulletR, (m_v + m_v_bullet) * cos(alphaRad), (m_v + m_v_bullet) * sin(alphaRad)));
		}

		std::vector<Bullet>& GetBullets()
		{
			return m_bullets;
		}


		void setVelocity(float dv)
		{
			m_v += dv;
		}

		float V() { return m_v; }

		void Move(float dt)
		{
			bullet.Move(dt);

			float alphaRad = acos(-1) * m_alpha / 180;
			m_x += m_v * cos(alphaRad) * dt;
			m_y += m_v * sin(alphaRad) * dt;
			m_spriteShip.setPosition(m_x, m_y);
		}

		float R() { return m_r; }
		float X() { return m_x; }
		float Y() { return m_y; }

		void Rotate(float dalpha)
		{
			m_alpha += dalpha;
			m_spriteShip.setRotation(m_alpha);
		}

		sf::Sprite Get()
		{
			return m_spriteShip;
		}

		bool BulletAvailable()
		{
			return bullet.Available();
		}

		sf::CircleShape GetBullet()
		{
			return bullet.Get();
		}
	};

}