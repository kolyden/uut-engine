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
}