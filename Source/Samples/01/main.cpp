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

namespace uut
{
	enum class Test
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
#define UUT_ENUM(type) \
	class type ## Enum : public EnumValue<type> \
	{ UUT_STRUCT(type ## Enum, Enum) }; \
	UUT_FUNDAMENTAL(type, type ## Enum)

#define UUT_ENUM_IMPLEMENT(type) \
	UUT_STRUCT_IMPLEMENT(type ## Enum)

#define UUT_REGISTER_ENUM(type) \
	UUT_REGISTER_TYPE(TypeInfo::Enum, EnumValue<type>, #type)

#define UUT_REGISTER_ENUM_VALUE(name) \
	internalType->AddMember( \
		new StaticPropertyInfo<ClassName, EnumType>(#name, \
			[]() -> EnumType { return EnumType::name; }, nullptr));

#define UUT_REGISTER_ENUM_VALUE_EX(name, value) \
	internalType->AddMember( \
		new StaticPropertyInfo<ClassName, EnumType>(name, \
			[]() -> EnumType { return value; }, nullptr));

	UUT_ENUM(Test)

	UUT_ENUM_IMPLEMENT(Test)
	{
 		UUT_REGISTER_ENUM_VALUE(ValueA);
		UUT_REGISTER_ENUM_VALUE(ValueB);
		UUT_REGISTER_ENUM_VALUE(ValueC);
		UUT_REGISTER_ENUM_VALUE(ValueD);
		UUT_REGISTER_ENUM_VALUE(ValueZ);
	}

	////////////////////////////////////////////////////////////////////////////
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		UUT_REGISTER_OBJECT(TestEnum);

		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);
		_plasma = new Plasma(_texture->GetSize());

		_gui = new DebugGUI(_renderer, _input);
		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_2D);

		_timer.Start();

// 		auto obj = Context::CreateObject<()

		Variant var1(Vector2(12.111f, 45.6789f));
		Variant var2(_texture);
		Variant var3(666.555f);
		Variant var4(true);
		Variant var5(Test::ValueZ);
		Variant var6(typeof<float>());
		Variant var7(Math::HALF_PI);
		Variant var8(L'ß');

		constexpr auto bool_def = GetDefault<bool>();
		constexpr auto float_def = GetDefault<float>();
		constexpr auto int_def = GetDefault<int>();
		constexpr auto enum_def = GetDefault<Test>();
		auto vec2_def = GetDefault<Vector2>();

		auto vec = var1.Get<Vector2>();
		auto ivec = var1.Get<IntVector2>(); UUT_ASSERT(ivec == Vector2(12, 46));
		auto obj = var2.Get<Object>(); UUT_ASSERT(obj == _texture);
		auto i = var3.Get<int>(); UUT_ASSERT(i == 666);
		auto b = var4.Get<bool>(); UUT_ASSERT(b == true);
		auto flag = var5.Get<Test>(); UUT_ASSERT(flag == Test::ValueZ);
		auto flagInt = var5.Get<int>(); UUT_ASSERT(flagInt == 42);
		auto angleDeg = var7.Get<Degree>(); UUT_ASSERT(angleDeg.GetDegrees() == 90);
		auto angle = var7.Get<float>();
		auto c = var8.Get<wchar_t>(); UUT_ASSERT(c != 'ß');

		auto str = StringFormat("Object type = ", typeof<Test>(), " and value = ");
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
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
					auto baseType = current->GetBaseType();
// 					ImGui::Separator();
					for (; baseType != nullptr; baseType = baseType->GetBaseType())
						ImGui::Text(baseType->GetName());

					ImGui::Separator();
					for (auto info : current->GetMembers())
					{						
						switch (info->GetMemberType())
						{
						case MemberType::Property:
							{
								ImGui::Text("prop: %s", info->GetName().GetData());
								auto prop = static_cast<const PropertyInfo*>(info);
								if (prop->IsStatic())
								{
									auto value = prop->GetValue(nullptr).Get<Test>();
									ImGui::SameLine();
									ImGui::Text(" = %d", (int)value);
								}
							}
							break;

						case MemberType::Constructor:
							ImGui::Text("Constructor");
							break;

						case MemberType::Method:
							ImGui::Text("method: %s", info->GetName().GetData());
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

int main(int argc, char *argv[])
{
	uut::SampleApp app;
	app.Run();

	return 0;
}