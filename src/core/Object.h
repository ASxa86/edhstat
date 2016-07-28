#pragma once

#include <core/Export.h>
#include <core/Pimpl.h>

#include <functional>
#include <iterator>
#include <string>
#include <vector>

namespace edh
{
	namespace core
	{
		///
		///	\class Object
		///
		///	\brief The base class for all objects of the game engine.
		///
		///	\date December 5, 2015
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Object
		{
			public:
				Object(const std::string& x);
				virtual ~Object();

				///
				///	Set the identifying string.
				///
				void setID(const std::string& x);

				///
				///	Get the identifying string.
				///
				std::string getID() const;

				///
				///	Add the given object.
				///
				///	Return false if the given object already exists.
				///
				bool addChild(std::unique_ptr<Object> x);

				///
				///	Remove the given object.
				///
				///	Returns false if the given object doesn't exist.
				///
				bool removeChild(Object* x);

				///
				///	Get the child of the given index.
				///
				Object* getChild(size_t x = 0) const;

				///
				///	Get the first child with the given id.
				///
				Object* getChild(const std::string& x) const;

				///
				/// Get the child of the given index and specified type.
				///
				template<typename T> T* getChild(size_t x = 0) const
				{
					auto children = this->getChildren<T>();

					if(x < children.size())
					{
						return children[x];
					}

					return nullptr;
				}

				///
				///	Get all children.
				///
				const std::vector<std::unique_ptr<Object>>& getChildren() const;

				///
				///	Get all children of the specified type.
				///
				template<typename T> std::vector<T*> getChildren() const
				{
					auto& children = this->getChildren();

					std::vector<T*> typeChildren;
					typeChildren.reserve(children.size());

					for(const auto& child : children)
					{
						auto typeChild = dynamic_cast<T*>(child.get());

						if(typeChild != nullptr)
						{
							typeChildren.push_back(typeChild);
						}
					}

					return typeChildren;
				}

				///
				///	Set the parent.
				///
				void setParent(Object* x);

				///
				///	Get the parent.
				///
				Object* getParent() const;

				///
				///	Get the parent of the specified type.
				///
				template<typename T> T* getParent() const
				{
					return dynamic_cast<T*>(this->getParent());
				}

				///
				///	Add a function to be called when a child has been added.
				///
				void addAddChildObserver(const std::function<void(Object*)>& x);

				///
				///	Add a function to be called when a child has been removed.
				///
				void addRemoveChildObserver(const std::function<void(Object*)>& x);

			private:
				class Impl;
				Pimpl<Impl> pimpl;
		};
	}
}
