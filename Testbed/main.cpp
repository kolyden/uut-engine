#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Rect.h>
#include <IMGUI/imgui.h>
#include <Core/Context.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Plugin.h>
#include <Core/Variant.h>
#include <Core/Enum.h>
#include <Core/Reflection/MethodInfo.h>
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>
#include <Windows.h>

namespace uut
{
	TestbedApp::TestbedApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void TestbedApp::OnInit()
	{
		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);

		_gui = new DebugGUI(_renderer, _input);
		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_2D);

		_timer.Start();
	}

	static bool show_test_window = false;

	static String ArgTypeToString(const Type* type)
	{
		if (type == nullptr)
			return "void";

		return type->GetName();
	}

	static void DrawArgList(const List<const Type*>& args)
	{
		for (unsigned i = 0; i < args.Count(); i++)
		{
			auto it = args[i];
			if (i > 0)
			{
				ImGui::SameLine();
				ImGui::Text(",");
			}

			ImGui::SameLine();
			ImGui::Text(it->GetName());
		}
	}

	static void DrawMembers(const Type* type, bool showCtor)
	{
		for (auto info : type->GetMembers())
		{
			switch (info->GetMemberType())
			{
			case MemberType::Property:
			{
				ImGui::Text("prop: %s", info->GetName().GetData());
				auto prop = static_cast<const PropertyInfo*>(info);
				if (prop->IsStatic())
				{
					auto value = prop->GetValue(nullptr).Get<int>();
					ImGui::SameLine();
					ImGui::Text(" = %d", value);
				}
			}
			break;

			case MemberType::Constructor:
				if (showCtor)
				{
					ImGui::Text("Constructor (");
					auto ctor = (const ConstructorInfo*)info;
					DrawArgList(ctor->GetArgsTypes());
					ImGui::SameLine();
					ImGui::Text(")");
				}
				break;

			case MemberType::Method:
			{
				auto method = (const MethodInfo*)info;
				ImGui::Text("method: %s %s(",
					ArgTypeToString(method->GetReturnType()),
					info->GetName().GetData());
				DrawArgList(method->GetArgsTypes());
				ImGui::SameLine();
				ImGui::Text(")");
			}
			break;

			case MemberType::Converter:
			{
				auto converter = (const ConverterInfo*)info;
				ImGui::Text("Convert to %s", converter->GetResultType()->GetName());
			}
			break;

			default:
				ImGui::Text(info->GetName());
			}
		}
	}

	void TestbedApp::OnFrame()
	{
		_timer.Update();
		_gui->NewFrame();

		///////////////////////////////////////////////////////////////
		ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiSetCond_FirstUseEver);
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
			if (ImGui::CollapsingHeader("Types", nullptr, true, true))
			{
				static const Type* current = nullptr;

				static ImGuiTextFilter filter;

				static List<const Type*> typeList;
				if (typeList.IsEmpty())
				{
					typeList = Context::GetTypes().GetValues();
					typeList.Sort([](const Type* a, const Type* b) -> int {
						return String::Compare(a->GetName(), b->GetName(), StringComparison::OrdinalIgnoreCase);
					});
				}

				filter.Draw();
				ImGui::PushItemWidth(150);
				ImGui::ListBoxHeader("##types");
				for (auto type : typeList)
				{
					const auto typeName = type->ToString();
					if (!filter.PassFilter(typeName))
						continue;

					if (ImGui::Selectable(typeName, type == current))
						current = type;
					ImGui::SameLine();
					ImGui::Text("(%d)", type->GetSize());
				}
				ImGui::ListBoxFooter();
				ImGui::PopItemWidth();

				if (current != nullptr)
				{
					ImGui::SameLine();
					ImGui::BeginGroup();

					ImGui::Text(current->GetName());

					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						ImGui::Text(baseType->GetName());

					ImGui::Separator();
					DrawMembers(current, true);

					ImGui::Separator();
					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						DrawMembers(baseType, false);
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
			// 			_plasma->Apply(_texture,
			// 				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10));
			// 			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
			_graphics->Flush();

			_gui->SetupCamera();
			_gui->Draw();

			_renderer->EndScene();
		}
	}
}

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	uut::TestbedApp app;
	app.Run();

	return 0;
}