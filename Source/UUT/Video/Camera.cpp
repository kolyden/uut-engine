#include "Camera.h"
#include "Renderer.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Camera)
	{}

	Camera::Camera()
		: _viewUpdate(true)
	{
	}

	Camera::~Camera()
	{		
	}

	void Camera::Setup(Renderer* renderer)
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
}