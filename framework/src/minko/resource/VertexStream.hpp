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

#include "minko/resource/AbstractResource.hpp"

namespace minko
{
	namespace resource
	{
		class VertexStream :
			public AbstractResource
		{
		public:
			typedef std::shared_ptr<VertexStream>		Ptr;

		private:
			typedef std::shared_ptr<VertexAttribute>	VxAttrPtr;

		private:
			std::vector<float>		_data;
			std::list<VxAttrPtr>	_attributes;

		public:
			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext> context)
			{
				return std::shared_ptr<VertexStream>(new VertexStream(context));
			}

			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext>	context,
					float*									data,
					const unsigned int						size,
					const unsigned int						offset = 0)
			{
				return std::shared_ptr<VertexStream>(new VertexStream(
					context, data, offset, size
				));
			}

			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext>	context,
					std::vector<float>::const_iterator		begin,
					std::vector<float>::const_iterator		end)
			{
				return std::shared_ptr<VertexStream>(new VertexStream(context, begin, end));
			}
				
			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext>	context, float* begin, float* end)
			{
				return std::shared_ptr<VertexStream>(new VertexStream(
					context, 
					begin,
					end
				));
			}
				
			inline static
			Ptr
			create(std::shared_ptr<render::AbstractContext>	context, 
				   const std::vector<float>&				data)
			{
				return create(context, data.begin(), data.end());
			}

			inline
			const std::vector<float>&
			data()
			{
				return _data;
			}

			inline
			const std::list<VxAttrPtr>&
			attributes()
			{
				return _attributes;
			}

			void
			upload();

			void
			dispose();

			void
			addAttribute(VxAttrPtr attribute);

			bool
			hasAttribute(VxAttrPtr attribute);

			VxAttrPtr
			attribute(const std::string& attributeName);

		private:
			VertexStream(std::shared_ptr<render::AbstractContext> context);

			VertexStream(std::shared_ptr<render::AbstractContext>	context,
							float*									data,
							const unsigned int						size,
							const unsigned int						offset);

			VertexStream(std::shared_ptr<render::AbstractContext>	context,
							std::vector<float>::const_iterator		begin,
							std::vector<float>::const_iterator		end);

			VertexStream(std::shared_ptr<render::AbstractContext>	context,
						 float*										begin,
						 float*										end);
		};
	}
}