#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"

namespace uut
{
	template<typename T>
	class Geometry
	{
	public:
		Geometry() {}
		explicit Geometry(uint count) { SetCount(count); }

		void SetCount(uint count)
		{
			if (_count == count)
				return

			_count = count;
			_buffer = nullptr;
			if (_count > 0)
				_buffer = ModuleInstance<Renderer>()->CreateVertexBuffer(_count*GetItemSize());
		}

		uint GetCount() const
		{
			return _count;
		}

		void Clear() override { SetCount(0); }

		uint GetItemSize() const { return sizeof(T); }

		T* Lock()
		{
			if (!_buffer)
				return nullptr;

			return (T*)_buffer->Lock(GetItemSize()*_count);
		}

		void Unlock()
		{
			_buffer->Unlock();
		}

	protected:
		SPtr<VertexBuffer> _buffer;
		uint _count;
	};
}