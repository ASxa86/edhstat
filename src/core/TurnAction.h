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
			TurnAction(const std::shared_ptr<Player>& x);
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
			std::shared_ptr<Player> getPlayer() const;

			///
			///	\brief Set the target of this action.
			///
			void setTarget(const std::shared_ptr<Player>& x);
			std::shared_ptr<Player> getTarget() const;

		private:
			std::weak_ptr<Player> player;
			std::weak_ptr<Player> target;
			int count;
			Type type;
		};
	}
}
