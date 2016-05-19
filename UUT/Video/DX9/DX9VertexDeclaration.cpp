#include "DX9VertexDeclaration.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DX9VertexDeclaration)
	{}

	DX9VertexDeclaration::DX9VertexDeclaration()
		: _data(nullptr)
	{
	}

	DX9VertexDeclaration::~DX9VertexDeclaration()
	{
		if (_data)
			_data->Release();
	}

	uintptr_t DX9VertexDeclaration::GetInternalHandle() const
	{
		return reinterpret_cast<uintptr_t>(_data);
	}
}