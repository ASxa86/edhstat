#pragma once

#include <core/Export.h>
#include <functional>

namespace edh
{
	namespace core
	{
		class Player;

		///
		///	\class TurnAction
		///
		///	\brief This class represents and manages a single action or event that can occur within a turn.
		///
		///	A turn action consists of one player performing an action that targets him/herself or another player.
		///	If a player were to draw 5 cards in one action, then that player targets themselves when performing that draw.
		///
		///
		///	\date February 28, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT TurnAction
		{
		public:
			///
			///	\enum Type
			///
			///	\brief This enumeration describes the different type of actions that can be performed by a player in a single turn.
			///
			enum class Type : int
			{
				CardDraw,
				LandPlay,
				SpellPlay,
				LifeGain,
				LifeLoss
			};

			TurnAction() = delete;

			///
			///	\brief Constructor
			///
			///	\param x The player performing the action. Defaults the targeted player to the same player.
			///
			TurnAction(const Player& x);
			~TurnAction();

			///
			///	\brief The type of action being performed.
			///
			void setType(Type x);
			Type getType() const;

			///
			///	\brief The count of the action being performed.
			///
			void setCount(int x);
			int getCount() const;

			///
			///	\brief Get the player performing this action.
			///
			const Player& getPlayer() const;

			///
			///	\brief Set the target of this action.
			///
			void setTarget(const Player& x);
			const Player& getTarget() const;

		private:
			std::reference_wrapper<const Player> player;
			std::reference_wrapper<const Player> target;
			int count;
			Type type;
		};
	}
}
