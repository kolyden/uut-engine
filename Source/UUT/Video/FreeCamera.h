#pragma once
#include <Core/Math/Vector3.h>
#include <Core/Math/Radian.h>
#include <Video/Camera.h>

namespace uut
{
	class Renderer;

	class FreeCamera : public Camera
	{
		UUT_OBJECT(FreeCamera, Camera)
	public:
		FreeCamera();
		virtual ~FreeCamera();

		void SetPosition(const Vector3& position);
		const Vector3& GetPosition() const;

		const Vector3& GetRight() const { return _right; }
		const Vector3& GetUp() const { return _up; }
		const Vector3& GetLook() const { return _look; }

		void MoveForward(float amount) { _position += _look*amount; _viewUpdate = true; }
		void MoveRight(float amount) { _position += _right*amount; _viewUpdate = true; }
		void MoveUp(float amount) { _position += _up*amount; _viewUpdate = true; }

		void Yaw(const Radian& angle) { _yaw += angle; _viewUpdate = true; }
		void Pitch(const Radian& angle) { _pitch += angle; _viewUpdate = true; }
		void Roll(const Radian& angle) { _roll += angle; _viewUpdate = true; }

		virtual Ray3 CastRay(const Vector2& screenPos, Renderer* renderer) const override;

	protected:
		Vector3 _position;
		Vector3 _right;
		Vector3 _up;
		Vector3 _look;
		Radian _yaw;
		Radian _pitch;
		Radian _roll;

		virtual void UpdateView() override;
	};
}
