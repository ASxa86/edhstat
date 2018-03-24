#pragma once

#include <core/Export.h>
#include <core/Pimpl.h>
#include <boost/signals2/signal.hpp>
#include <functional>

namespace edh
{
	namespace core
	{
		template <typename T>
		class Dirty : public std::enable_shared_from_this<T>
		{
		public:
			Dirty()
			{
			}

			virtual ~Dirty()
			{
			}

			boost::signals2::connection addDirtyObserver(const std::function<void(std::shared_ptr<T>)>& x)
			{
				return this->dirtyObservers.connect(x);
			}

			void makeDirty()
			{
				this->dirtyObservers(this->shared_from_this());
			}

		private:
			boost::signals2::signal<void(std::shared_ptr<T>)> dirtyObservers;
		};
	}
}
