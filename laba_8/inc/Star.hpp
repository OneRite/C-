#pragma once
#include <SpaceObject.hpp>

namespace mt
{
	class Star : public SpaceObject
	{
	public:
		Star() = default;
		virtual ~Star() {}

		void Attack() override
		{
			std::cout << "Star Attack" << m_x << std::endl;
		}

		void SpecialAbility() override
		{
			std::cout << "Star Special Ability" << std::endl;
		}

		void Test() {}
	};
}
