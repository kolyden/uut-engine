#include "Camera.h"
#include "Renderer.h"
#include "CommandList.h"

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

	void Camera::Setup(const SharedPtr<CommandList>& commandList)
	{
		if (commandList == nullptr)
			return;

		if (_viewUpdate)
		{
			_viewUpdate = false;
			UpdateView();
		}

		commandList->SetTransform(RT_VIEW, _matView);
	}

	const Matrix4& Camera::UpdateViewMatrix()
	{
		if (_viewUpdate)
		{
			_viewUpdate = false;
			UpdateView();
		}

		return _matView;
	}
}