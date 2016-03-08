#pragma once
#include <Core/Object.h>
#include <Core/Math/Matrix4.h>

namespace uut
{
	class Renderer;

	class CameraBase : public Object
	{
	public:
		CameraBase();

		void Setup(Renderer* renderer);

	protected:
		Matrix4 _matView;
		bool _viewUpdate;

		virtual void UpdateView() = 0;
	};
}
