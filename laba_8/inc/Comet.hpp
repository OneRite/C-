#pragma once
#include <SpaceObject.hpp>

namespace mt
{
	class Comet : public SpaceObject
	{
	public:
		Comet() = default;
		virtual ~Comet() {}

		void Attack()
		{
			std::cout << "Comet Attack" << std::endl;
		}

		void SpecialAbility()
		{
			std::cout << "Comet Special Ability" << std::endl;
		}
	};
}
