#pragma once
#include <Core/Object.h>
#include <Core/Math/Matrix4.h>
#include <Core/Math/Ray3.h>

namespace uut
{
	class Vector2i;
	class CommandList;
	class Renderer;

	class Camera : public Object
	{
		UUT_OBJECT(uut, Camera, Object)
	public:
		Camera();
		virtual ~Camera();

		void Setup(const SharedPtr<CommandList>& commandList);
		const Matrix4& UpdateViewMatrix();

		virtual Ray3 CastRay(const Vector2& screenPos, Renderer* renderer) const = 0;

	protected:
		Matrix4 _matView;
		bool _viewUpdate;

		virtual void UpdateView() = 0;
	};
}