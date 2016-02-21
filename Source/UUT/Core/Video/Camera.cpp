#include "Camera.h"
#include "Renderer.h"

namespace uut
{
	Camera::Camera()
		: _type(CameraType::Perspective)
		, _position(0)
		, _rotation(Quaternion::IDENTITY)
		, _updateView(true)
		, _updateProj(true)
		, _nearClipPlane(0.01f)
		, _farClipPlane(1000.0f)
		, _fov(50)
		, _size(800, 600)
	{
	}

	void Camera::SetCameraType(CameraType type)
	{
		if (_type == type)
			return;

		_type = type;
		_updateProj = true;
	}

	CameraType Camera::GetCameraType() const
	{
		return _type;
	}

	void Camera::SetPosition(const Vector3& position)
	{
		_position = position;
		_updateView = true;
	}

	const Vector3& Camera::GetPosition() const
	{
		return _position;
	}

	void Camera::SetRotation(const Quaternion& roatation)
	{
		_rotation = roatation;
		_updateView = true;
	}

	const Quaternion& Camera::GetRotation() const
	{
		return _rotation;
	}

	void Camera::SetFov(float fov)
	{
		_fov = fov;
		if (_type == CameraType::Perspective)
			_updateProj = true;
	}

	float Camera::GetFov() const
	{
		return _fov;
	}

	void Camera::SetNearClipPlane(float znear)
	{
		_nearClipPlane = znear;
		_updateProj = true;
	}

	float Camera::GetNearClipPlane() const
	{
		return _nearClipPlane;
	}

	void Camera::SetFarClipPlane(float zfar)
	{
		_farClipPlane = zfar;
		_updateProj = true;
	}

	float Camera::GetFarClipPlane() const
	{
		return  _farClipPlane;
	}

	void Camera::SetSize(const Vector2& size)
	{
		_size = size;
		if (_type == CameraType::Orthogonal)
			_updateProj = true;
	}

	const Vector2& Camera::GetSize() const
	{
		return _size;
	}

	void Camera::Apply(Renderer* renderer)
	{
		if (renderer == nullptr)
			return;

		if (_updateView)
		{
			_updateView = false;
			_matView = //Matrix4::Translate(_position);
				Matrix4::Transform(_position, _rotation, Vector3::ONE);
		}

		if (_updateProj)
		{
			_updateProj = false;
			switch (_type)
			{
			case CameraType::Orthogonal:
				_matProj = Matrix4::OrthoProjection(
					0, _size.x, 0, _size.y,
					_nearClipPlane, _farClipPlane);
				break;

			case CameraType::Perspective:
				_matProj = Matrix4::PerspectiveFovLH(_fov,
					_size.x / _size.y, _nearClipPlane, _farClipPlane);
				break;
			}
		}

		renderer->SetTransform(RT_VIEW, _matView);
		renderer->SetTransform(RT_PROJECTION, _matProj);
	}
}