#pragma once

#include <core/Export.h>
#include <core/Pimpl.h>
#include <functional>

namespace boost
{
	namespace signals2
	{
		class connection;
	}
}

namespace edh
{
	namespace core
	{
		class EDHCORE_EXPORT Object : public std::enable_shared_from_this<Object>
		{
		public:
			Object();
			virtual ~Object();

			boost::signals2::connection addDirtyObserver(const std::function<void(std::shared_ptr<Object>)>& x);
			void makeDirty();

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
