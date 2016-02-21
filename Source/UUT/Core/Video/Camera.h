#pragma once
#include <Core/Object.h>
#include <Core/Math/Matrix4.h>
#include <Core/Math/IntVector2.h>
#include <Core/Math/Vector3.h>
#include <Core/Math/Vector2.h>

namespace uut
{
	class Renderer;

	enum class CameraType
	{
		Perspective,
		Orthogonal,
	};

	class Camera : public Object
	{
	public:
		Camera();

		void SetCameraType(CameraType type);
		CameraType GetCameraType() const;

		void SetPosition(const Vector3& position);
		const Vector3& GetPosition() const;

		void SetFov(float fov);
		float GetFov() const;

		void SetNearClipPlane(float znear);
		float GetNearClipPlane() const;

		void SetFarClipPlane(float zfar);
		float GetFarClipPlane() const;

		void SetSize(const Vector2& size);
		const Vector2& GetSize() const;

		void Apply(Renderer* renderer);

	protected:
		CameraType _type;
		Vector3 _position;
		Matrix4 _matView;
		Matrix4 _matProj;
		bool _updateView;
		bool _updateProj;
		float _nearClipPlane;
		float _farClipPlane;
		float _fov;
		Vector2 _size;
	};
}
