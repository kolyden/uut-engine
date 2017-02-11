#include "FreeCamera.h"
#include <Core/Math/Vector2.h>
#include <Video/Renderer.h>
#include "Viewport.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(FreeCamera)
	{}

	FreeCamera::FreeCamera()
		: _position(0, 0, 0)
		, _right(Vector3::Right)
		, _up(Vector3::Up)
		, _look(Vector3::Forward)
	{
	}

	FreeCamera::~FreeCamera()
	{		
	}

	void FreeCamera::SetPosition(const Vector3& position)
	{
		_position = position;
		_viewUpdate = true;
	}

	const Vector3& FreeCamera::GetPosition() const
	{
		return _position;
	}

	Ray3 FreeCamera::CastRay(const Vector2& screenPos, Renderer* renderer) const
	{
		//if (renderer == nullptr)
			return Ray3::Zero;

		/*auto& viewport = renderer->GetViewport();
		auto& matProj = renderer->GetTransform(RT_PROJECTION);

		const Vector3 v(
			(( 2.0f * screenPos.x) / viewport.width  - 1.0f) / matProj._11,
			((-2.0f * screenPos.y) / viewport.height + 1.0f) / matProj._22,
			1.0f);

		const auto m = _matView.Inverse();
		Vector3 rayDir(
			v.x*m._11 + v.y*m._21 + v.z*m._31,
			v.x*m._12 + v.y*m._22 + v.z*m._32,
			v.x*m._13 + v.y*m._23 + v.z*m._33);
		rayDir.Normalize();
		Vector3 rayOrigin(m._41, m._42, m._43);

		return Ray3(rayOrigin, rayDir);*/
	}

	///////////////////////////////////////////////////////////////////////////
	void FreeCamera::UpdateView()
	{
		_right = Vector3::Right;
		_up = Vector3::Up;
		_look = Vector3::Forward;

		const auto matYaw = Matrix4::RotationAxis(_up, _yaw);
		_look = matYaw.VectorTransform(_look);
		_right = matYaw.VectorTransform(_right);

		const auto matPitch = Matrix4::RotationAxis(_right, _pitch);
		_up = matPitch.VectorTransform(_up);
		_look = matPitch.VectorTransform(_look);

		const auto matRoll = Matrix4::RotationAxis(_look, _roll);
		_right = matRoll.VectorTransform(_right);
		_up = matRoll.VectorTransform(_up);

		_matView = Matrix4::Identity;
		_matView._11 = _right.x; _matView._12 = _up.x; _matView._13 = _look.x;
		_matView._21 = _right.y; _matView._22 = _up.y; _matView._23 = _look.y;
		_matView._31 = _right.z; _matView._32 = _up.z; _matView._33 = _look.z;

		_matView._41 = -Vector3::Dot(_position, _right);
		_matView._42 = -Vector3::Dot(_position, _up);
		_matView._43 = -Vector3::Dot(_position, _look);
	}
}
