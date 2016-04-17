#pragma once
#include <Core/Windows/Application.h>
#include <Core/GUI/DebugGUI.h>
#include <Video/Graphics.h>
#include <Video/Effects/Plasma.h>

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")

namespace uut
{
	namespace internal
	{
		template<typename T>
		struct EnumImpl
		{
		};
}

	enum class TestFlag
	{
		TestA,
		TestB,
	};
	
	namespace internal
	{
		template<>
		struct EnumImpl<TestFlag>
		{
			static void _RegisterInternal()
			{}

			static Type& GetTypeInternal()
			{
				static Type t(TypeInfo::Enum, "TestFlag", nullptr, &_RegisterInternal);
				return t;
			}
		};
	}

	template<>
	static const Type* typeof<TestFlag>()
	{
		return &internal::EnumImpl<TestFlag>::GetTypeInternal();
	}

	//////////////////////////////////////////////////////////////////////////////
	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		static const int texSize = 402;

		SharedPtr<Texture2D> _texture;
		SharedPtr<DebugGUI> _gui;
		SharedPtr<Plasma> _plasma;
		SharedPtr<Graphics> _graphics;

		Timer _timer;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}