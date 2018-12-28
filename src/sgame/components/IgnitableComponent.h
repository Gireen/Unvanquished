/*
===========================================================================

Unvanquished GPL Source Code
Copyright (C) 2014 Unvanquished Developers

This file is part of the Unvanquished GPL Source Code (Unvanquished Source Code).

Unvanquished Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Unvanquished Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Unvanquished Source Code.  If not, see <http://www.gnu.org/licenses/>.

===========================================================================
*/

#ifndef IGNITABLE_COMPONENT_H_
#define IGNITABLE_COMPONENT_H_

#include "../backend/CBSEBackend.h"
#include "../backend/CBSEComponents.h"

#include <random>

class IgnitableComponent: public IgnitableComponentBase {
	public:
		const static float SELF_DAMAGE;
		const static float SPLASH_DAMAGE;
		const static float SPLASH_DAMAGE_RADIUS;

		/** The minimum time any fire will burn. */
		const static int   MIN_BURN_TIME;

		/** The average time an independent fire will burn. Includes the minimum burn period. */
		const static int   BASE_AVERAGE_BURN_TIME;

		/** The maximum additional average burn time per burning neighbour in range. */
		const static int   EXTRA_AVERAGE_BURN_TIME;

		/** The radius used to check for burning neighbours in range for the extra burn time. */
		const static float EXTRA_BURN_TIME_RADIUS;

		/** During the average lifetime of a fire, this is for each neighbour in range the
		 *  cummulated maximum chance to spread to it. */
		const static float LIFETIME_SPREAD_CHANCE;

		/** The radius in which fire can spread. */
		const static float SPREAD_RADIUS;

		// ///////////////////// //
		// Autogenerated Members //
		// ///////////////////// //

		/**
		 * @brief Default constructor of the IgnitableComponent.
		 * @param entity The entity that owns the component instance.
		 * @param alwaysOnFire An initialization parameter.
		 * @param r_ThinkingComponent A ThinkingComponent instance that this component depends on.
		 * @note This method is an interface for autogenerated code, do not modify its signature.
		 */
		IgnitableComponent(Entity& entity, bool alwaysOnFire, ThinkingComponent& r_ThinkingComponent);

		/**
		 * @brief Handle the PrepareNetCode message.
		 * @note This method is an interface for autogenerated code, do not modify its signature.
		 */
		void HandlePrepareNetCode();

		/**
		 * @brief Handle the Ignite message.
		 * @param fireStarter
		 * @note This method is an interface for autogenerated code, do not modify its signature.
		 */
		void HandleIgnite(struct gentity_s* fireStarter);

		/**
		 * @brief Handle the Extinguish message.
		 * @param immunityTime
		 * @note This method is an interface for autogenerated code, do not modify its signature.
		 */
		void HandleExtinguish(int immunityTime);

		// ///////////////////// //

		void DamageSelf(int timeDelta);
		void DamageArea(int timeDelta);
		void ConsiderStop(int timeDelta);
		void ConsiderSpread(int timeDelta);

	private:
		bool onFire;
		int igniteTime;         /**< Time of (re-)ignition. */
		int immuneUntil;        /**< Fire immunity time after being extinguished. */
		int spreadAt;           /**< Will try to spread to neighbours at this time. */
		gentity_t* fireStarter; /**< Client who originally started the fire. */

		std::default_random_engine randomGenerator;
		std::normal_distribution<float> normalDistribution;
};

#endif // IGNITABLE_COMPONENT_H_
