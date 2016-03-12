#include "CameraBase.h"
#include "Renderer.h"

namespace uut
{
	CameraBase::CameraBase()
		: _viewUpdate(true)
	{
	}

	void CameraBase::Setup(Renderer* renderer)
	{
		if (renderer == nullptr)
			return;

		if (_viewUpdate)
		{
			_viewUpdate = false;
			UpdateView();
		}

		renderer->SetTransform(RT_VIEW, _matView);
	}

	Ray3 CameraBase::CastRay(const IntVector2& screenPos, const IntVector2& screenSize) const
	{
		const float px = (2.0f * screenPos.x) / screenSize.x - 1.0f;
		const float py = (2.0f * screenPos.y) / screenSize.y - 1.0f;
		const Matrix4 invMat = _matView.Inverse();

		Ray3 ray;
		ray.origin = invMat.VectorTransform(Vector3::Zero);
		ray.direction = invMat.VectorTransform(Vector3(px, py, 1.0f)).Normalize();

		return ray;
	}
}