#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Rect.h>
#include <IMGUI/imgui.h>
#include <Core/Context.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Plugin.h>
#include <Core/Variant.h>
#include <Core/Enum.h>

namespace uut
{
	enum class EnumTest
	{
		ValueA,
		ValueB,
	};

	class EnumTestValue : public EnumValue<EnumTest>
	{
		UUT_TYPE(EnumTestValue, EnumValue<EnumTest>)
	public:
	};

	UUT_TYPE_IMPLEMENT(EnumTestValue)
	{
// 		internalType->AddMember(
// 			new PropertyInfoImpl<EnumTestValue, EnumTest>("ValueA",
// 				[](const EnumTestValue* obj) -> EnumTest { return EnumTest::ValueA; }, nullptr));
	}

	////////////////////////////////////////////////////////////////////////////
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);
		_plasma = new Plasma(_texture->GetSize());

		_gui = new DebugGUI(_renderer, _input);
		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_2D);

		_timer.Start();

		Variant var1(Vector2(12.111f, 45.6789f));
		Variant var2(_texture);
		Variant var3(666);
		Variant var4(true);
// 		Variant var5(EnumTest::ValueA);

		auto vec = var1.Get<Vector2>(Vector2::Zero);
		auto obj = var2.Get<Texture2D>();
		auto i = var3.Get<int>();
		auto b = var4.Get<bool>();

		int a = 0;
		a++;
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		_timer.Update();
		_gui->NewFrame();

		///////////////////////////////////////////////////////////////
		ImGui::SetNextWindowSize(ImVec2(250, 350), ImGuiSetCond_FirstUseEver);
		if (ImGui::Begin("Context"))
		{
			ImGui::Checkbox("Show Test Window", &show_test_window);

			ImGui::Separator();
			if (ImGui::CollapsingHeader("Plugins"))
			{
				ImGui::ListBoxHeader("##plugins");
				auto plugins = Context::GetPlugins();
				for (auto& it : plugins)
				{
					ImGui::Selectable(it->ToString());
				}
				ImGui::ListBoxFooter();
			}

			ImGui::Separator();
			if (ImGui::CollapsingHeader("Types"))
			{
				static const Type* current = nullptr;

				static ImGuiTextFilter filter;

				filter.Draw();
				ImGui::PushItemWidth(150);
				ImGui::ListBoxHeader("##types");
				for (auto& it : Context::GetTypes())
				{
					auto type = it.second;
					const auto typeName = type->ToString();
					if (!filter.PassFilter(typeName))
						continue;

					if (ImGui::Selectable(typeName, type == current))
						current = type;
				}
				ImGui::ListBoxFooter();
				ImGui::PopItemWidth();

				if (current != nullptr)
				{
					ImGui::SameLine();
					ImGui::BeginGroup();

					ImGui::Text(current->GetName().GetData());
					auto baseType = current->GetBaseType();
					ImGui::Separator();
					for (; baseType != nullptr; baseType = baseType->GetBaseType())
						ImGui::Text(baseType->GetName().GetData());
					ImGui::EndGroup();
				}				
			}
		}
		ImGui::End();

		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

		///////////////////////////////////////////////////////////////
		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_plasma->Apply(_texture,
				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10));

			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
			_graphics->Flush();

			_gui->SetupCamera();
			_gui->Draw();

			_renderer->EndScene();
		}
	}
}

int main(int argc, char *argv[])
{
	uut::SampleApp app;
	app.Run();

	return 0;
}