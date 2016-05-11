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

namespace uut
{
	enum class EnumTest
	{
		ValueA,
		ValueB,
		ValueC,
		ValueD,
		ValueZ = 42,
	};

	////
	namespace detail
	{
		// FNV-1a constants
		static constexpr unsigned long long basis = 14695981039346656037ULL;
		static constexpr unsigned long long prime = 1099511628211ULL;

		// compile-time hash helper function
		constexpr unsigned long long hash_one(char c, const char* remain, unsigned long long value)
		{
			return c == 0 ? value : hash_one(remain[0], remain + 1, (value ^ c) * prime);
		}

		// compile-time hash
		constexpr unsigned long long hash(const char* str)
		{
			return hash_one(str[0], str + 1, basis);
		}
	}
	////
	namespace detail
	{
		template<typename Arg>
		String& Write(String& o, Arg&& arg) {
			return o += ToString<std::remove_reference_t<Arg>>(arg);
		}

		template<typename Arg, typename ...Args>
		String& Write(String& o, Arg&& arg, Args&&... args)
		{
			o += ToString<std::remove_reference_t<Arg>>(arg);
			return Write(o, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static String StringFormat(Args... args)
	{
		String str;
		detail::Write(str, args...);
		return str;
	}

	////////////////////
	UUT_ENUM(EnumTest);

#define UUT_ENUM_VALUE(name, value) \
	internalType->AddMember( \
		new PropertyInfoImpl<ClassName, EnumType>(name, \
			[](const ClassName* obj) -> EnumType { return value; }, nullptr));

	static int Foo(int a, int b)
	{
		return a + b;
	}

	UUT_ENUM_IMPLEMENT(EnumTest)
	{
		//internalType->AddMember(
		//	new PropertyInfoImpl<ClassName, EnumType>("ValueA",
		//		[](const ClassName* obj) -> EnumType {
		//	return EnumTest::ValueA;
		//}, nullptr));

 		UUT_ENUM_VALUE("ValueA", EnumTest::ValueA);
		UUT_ENUM_VALUE("ValueB", EnumTest::ValueB);
		UUT_ENUM_VALUE("ValueC", EnumTest::ValueC);
		UUT_ENUM_VALUE("ValueD", EnumTest::ValueD);
		UUT_ENUM_VALUE("ValueZ", EnumTest::ValueZ);

		internalType->AddMember(new StaticFunctionInfo<int, int, int>("test", &Foo));
	}

	////////////////////////////////////////////////////////////////////////////
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		UUT_REGISTER_ENUM(EnumTest);

		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);
		_plasma = new Plasma(_texture->GetSize());

		_gui = new DebugGUI(_renderer, _input);
		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_2D);

		_timer.Start();

// 		auto obj = Context::CreateObject<()

		Variant var1(Vector2(12.111f, 45.6789f));
		Variant var2(_texture);
		Variant var3(666);
		Variant var4(true);
		Variant var5(EnumTest::ValueZ);
		Variant var6(typeof<float>());
		Variant var7(90_deg);

		auto bool_def = GetDefault<float>();
		auto int_def = GetDefault<int>();
		auto flag_def = GetDefault<EnumTest>();
		auto vec2_def = GetDefault<Vector2>();

		auto vec = var1.Get<Vector2>();
		auto obj = var2.Get<Object>();
		auto i = var3.Get<int>();
		auto b = var4.Get<bool>();
		auto flag = var5.Get<EnumTest>();
// 		auto flagTest = var5.Get<EnumValue<EnumTest>>();
// 		auto flagTestStr = flagTest.ToString();
		auto type = var5.GetType();
		auto func = dynamic_cast<const MethodInfo*>(type->FindMember("test"));
		if (func != nullptr)
		{
			Variant result;
			func->Call({ 2, 8 }, result);
			int a = result.Get<int>();
			a++;
		}

		auto angle = var7.Get<Degree>();
		auto str = StringFormat("Object type = ", typeof<EnumTest>(), " and value = ");
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

					ImGui::Text(current->GetName());
					auto baseType = current->GetBaseType();
// 					ImGui::Separator();
					for (; baseType != nullptr; baseType = baseType->GetBaseType())
						ImGui::Text(baseType->GetName());

					ImGui::Separator();
					for (auto& it : current->GetFields())
					{
						ImGui::Text(it->GetName());
					}
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