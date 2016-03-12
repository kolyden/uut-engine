#include "FreeCamera.h"

namespace uut
{
	FreeCamera::FreeCamera()
		: _position(0, 0, 0)
		, _right(Vector3::Right)
		, _up(Vector3::Up)
		, _look(Vector3::Forward)
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