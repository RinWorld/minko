/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"
#include "minko/Signal.hpp"

#include "minko/scene/Layout.hpp"

namespace minko
{
	namespace component
	{
		class AbstractComponent:
			public std::enable_shared_from_this<AbstractComponent>
		{
			friend class scene::Node;

		public:
			typedef std::shared_ptr<AbstractComponent>					Ptr;

		private:
			std::vector<std::shared_ptr<scene::Node>>					_targets;
			Layouts														_layoutMask;

			std::shared_ptr<Signal<Ptr, std::shared_ptr<scene::Node>>>	_targetAdded;
			std::shared_ptr<Signal<Ptr, std::shared_ptr<scene::Node>>>	_targetRemoved;
			std::shared_ptr<Signal<Ptr>>								_layoutMaskChanged;

		public:
			AbstractComponent() :
				_targets(),
				_layoutMask(scene::Layout::Mask::EVERYTHING),
				_targetAdded(Signal<Ptr, std::shared_ptr<scene::Node>>::create()),
				_targetRemoved(Signal<Ptr, std::shared_ptr<scene::Node>>::create()),
				_layoutMaskChanged(Signal<Ptr>::create())
			{
			}

			virtual
			~AbstractComponent() = 0;

			inline
			const std::vector<std::shared_ptr<scene::Node>>&
			targets() const
			{
				return _targets;
			}

			inline
			const unsigned int
			numTargets() const
			{
				return _targets.size();
			}

			inline
			std::shared_ptr<scene::Node>
			getTarget(unsigned int index) const
			{
				return _targets[index];
			}

			inline
			Layouts
			layoutMask() const
			{
				return _layoutMask;
			}

			inline
			void
			layoutMask(Layouts value)
			{
				if (_layoutMask != value)
				{
					_layoutMask = value;
					_layoutMaskChanged->execute(shared_from_this());
				}
			}


			inline
			Signal<Ptr, std::shared_ptr<scene::Node>>::Ptr
			targetAdded() const
			{
				return _targetAdded;
			}

			inline
			Signal<Ptr, std::shared_ptr<scene::Node>>::Ptr
			targetRemoved() const
			{
				return _targetRemoved;
			}

			inline
			Signal<Ptr>::Ptr
			layoutMaskChanged() const
			{
				return _layoutMaskChanged;
			}
		};

		inline
		AbstractComponent::~AbstractComponent()
		{
		}
	}
}
