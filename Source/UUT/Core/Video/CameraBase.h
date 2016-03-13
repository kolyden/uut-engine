#pragma once
#include <Core/Object.h>
#include <Core/Math/Matrix4.h>
#include <Core/Math/Ray3.h>

namespace uut
{
	class IntVector2;
	class Renderer;

	class CameraBase : public Object
	{
	public:
		CameraBase();

		void Setup(Renderer* renderer);

		virtual Ray3 CastRay(const Vector2& screenPos, Renderer* renderer) const = 0;

	protected:
		Matrix4 _matView;
		bool _viewUpdate;

		virtual void UpdateView() = 0;
	};
}