#include "main.h"
#include <Core/Math/Math.h>
#include <IMGUI/imgui.h>
#include <Core/Context.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Plugin.h>
#include <Core/Variant.h>
#include <Core/Enum.h>
#include <Core/EnumFlags.h>
#include <Core/Reflection/MethodInfo.h>
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>
#include <Windows.h>
#include <Video/BitmapFont.h>
#include <Core/Attribute.h>
#include <Core/AttributeUsage.h>
#include <CES/EntityPool.h>
#include <CES/Entity.h>
#include <CES/EntityMatcher.h>
#include <Video/Color.h>

namespace uut
{
	namespace Foo
	{
		class TestAttribute : public Attribute
		{
			UUT_OBJECT(TestAttribute, Attribute)
		public:
			explicit TestAttribute(const String& text) : _text(text) {}

			const String& GetText() const { return _text; }

			String ToString() override
			{
				return Super::ToString() + "(text:'" + _text + "')";
			}

		protected:
			String _text;
		};

		UUT_OBJECT_IMPLEMENT(TestAttribute)
		{
			internalType->AddAttribute(new AttributeUsage(AttributeTarget::All, false, false));
		}
	}

	////////////////////////////////////////////////////////////////////////////
	template<class T>
	static void EnumRegisterMemebers(Type* type)
	{
		for (auto& it : Enum<T>::GetNames())
		{
			T value = it.first;
			type->AddMember(new StaticPropertyInfo<T>(it.second,
				[value]() -> T { return value; }, nullptr));
		}
	}

	enum class Test
	{
		ValueA,
		ValueB,
		ValueC,
		ValueZ = 42,
	};
	UUT_ENUMFLAG(TestFlags, Test);
	UUT_ENUMFLAG_IMPLEMENT(TestFlags, Test)
	{
		RegisterValues(
			"ValueA", Test::ValueA,
			"ValueB", Test::ValueB,
			"ValueC", Test::ValueC,
			"ValueZ", Test::ValueZ);
 		EnumRegisterMemebers<Test>(internalType);
		internalType->AddAttribute(new Foo::TestAttribute("hello"));
	}

	enum class Direction
	{
		North,
		East,
		South,
		West,
	};
	UUT_ENUM(Direction);
	UUT_ENUM_IMPLEMENT(Direction)
	{
		RegisterValues(
			"North", Direction::North,
			"East", Direction::East,
			"South", Direction::South,
			"West", Direction::West);
		EnumRegisterMemebers<Direction>(internalType);
		internalType->AddAttribute(new Foo::TestAttribute("world"));
	}

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

	////////////////////////////////////////////////////////////////////////////

#define UUT_COMPONENT(name, dataType, dataName) \
	class name : public Component \
	{ \
		UUT_VALUETYPE(name, Component) \
	public: \
		dataType dataName; \
		void Reset(const dataType& value) \
		{ dataName = value; } \
	}; \
	UUT_VALUETYPE_IMPLEMENT(name) {} \

	class UIWidget : public Component
	{
		UUT_VALUETYPE(UIWidget, Component)
	public:
		IntRect rect;

		void Reset(int x, int y, int w, int h)
		{
			rect = IntRect(x, y, w, h);
		}
	};
	UUT_VALUETYPE_IMPLEMENT(UIWidget) {}

	UUT_COMPONENT(UIImage, SharedPtr<Texture2D>, texture)
	UUT_COMPONENT(UIColor, Color32, color)

	class UILabel : public Component
	{
		UUT_VALUETYPE(UILabel, Component)
	public:
		SharedPtr<Font> font;
		String text;

		void Reset(const SharedPtr<Font>& fnt, const String& txt)
		{
			font = fnt;
			text = txt;
		}
	};
	UUT_VALUETYPE_IMPLEMENT(UILabel) {}

	class UIImageRender : public EntitySystem
	{
	protected:
		void Render() override
		{
			static const EntityMatcher matcher =
				EntityMatcher::AllOf<UIWidget>() |
				EntityMatcher::AnyOf<UIImage, UIColor, UILabel>();

			for (auto& ent : _pool->GetEntities(matcher))
			{
				auto pos = ent->Get<UIWidget>();
				auto img = ent->Get<UIImage>();
				auto col = ent->Get<UIColor>();
				auto txt = ent->Get<UILabel>();

				const auto r = ToScreenSpace(pos->rect);
				Graphics::Instance()->DrawQuad(
					r, 15, img ? img->texture : nullptr,
					col ? col->color : Color32::White);

				if (txt == nullptr || !txt->font || txt->text.IsEmpty())
					continue;

				Graphics::Instance()->PrintText(IntVector2(r.x, r.y),
					15, txt->text, txt->font, Color32::White);
			}
		}

		static IntRect ToScreenSpace(const IntRect& r)
		{
			return IntRect(r.x, 600 - r.y - r.height, r.width, r.height);
		}
	};

	namespace Test2
	{
		namespace Foo
		{
			class Bar
			{};
		}
	}

	////////////////////////////////////////////////////////////////////////////
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		Context::RegisterType<TestFlags>();
		UUT_REGISTER_ENUM(Direction);
		UUT_REGISTER_OBJECT(Foo::TestAttribute);

		Context::RegisterModule(new DebugGUI());
		Context::RegisterModule(new Graphics());

		Graphics::Instance()->SetProjection(Graphics::PM_2D);
		ModuleInstance<ResourceCache> cache;
		_tex = cache->Load<Texture2D>("rogueliketiles.png");
		_font = cache->Load<Font>("Consolas.fnt");

		Variant var1(Vector2(12.111f, 45.6789f));
		Variant var2(_font);
		Variant var3(666.555f);
		Variant var4(true);
// 		Variant var5(Test::ValueZ);
		Variant var6(TypeOf<float>());
		Variant var7(Math::HALF_PI);
		Variant var8(L'ß');
		Variant var9(256);

		auto& bool_def = GetDefault<bool>(); UUT_ASSERT(bool_def == false);
		auto& float_def = GetDefault<float>(); UUT_ASSERT(float_def == 0.0f);
		auto& int_def = GetDefault<int>(); UUT_ASSERT(int_def == 0);
		auto& enum_def = GetDefault<Test>(); UUT_ASSERT(enum_def == Test::ValueA);
		auto& ivec2_def = GetDefault<IntVector2>(); UUT_ASSERT(ivec2_def == IntVector2::Zero);

		auto vec = var1.Get<Vector2>();
		auto ivec = var1.Get<IntVector2>(); UUT_ASSERT(ivec == Vector2(12, 46));
		auto obj = var2.Get<Object>(); UUT_ASSERT(obj == _font);
		auto i = var3.Get<int>(); UUT_ASSERT(i == 666);
		auto b = var4.Get<bool>(); UUT_ASSERT(b == true);
// 		auto flag = var5.Get<Test>(); UUT_ASSERT(flag == Test::ValueZ);
// 		auto flagInt = var5.Get<int>(); UUT_ASSERT(flagInt == 42);
		auto type = var6.Get<Type>(); UUT_ASSERT(type == TypeOf<float>());
		auto angleDeg = var7.Get<Degree>(); UUT_ASSERT(angleDeg.GetDegrees() == 90);
		auto angle = var7.Get<float>(); UUT_ASSERT(angle == Math::HALF_PI.GetRadians());
		auto c = var8.Get<wchar_t>(); UUT_ASSERT(c == L'ß');
		auto vari = var9.Get<int>(); UUT_ASSERT(vari == 256);
		auto varf = var9.Get<float>(); UUT_ASSERT(varf == 256);
		auto vars = var9.Get<String>(); UUT_ASSERT(vars == "256");

		auto fstr = var3.Get<String>();
// 		auto flagStr = var5.Get<String>();

// 		auto str = StringFormat("Object type = ", typeof<Test>(), " and value = ");
		////////////////////////////////////////////////////////////////////////////
		_pool = new EntityPool();
		_pool->AddSystem(new UIImageRender());
		_pool->CreateEntity()->
			Add<UIWidget>(20, 20, 200, 50)->
			Add<UIImage>(cache->Load<Texture2D>("brick_dark0.png"))->
			Add<UIColor>(Color::Green);
		_pool->CreateEntity()->
			Add<UIWidget>(20, 80, 200, 50)->
			Add<UIColor>(Color::Red)->
			Add<UILabel>(_font, "Label");
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

	static void DrawAttributes(const Type* type)
	{
		for (auto& attribute : type->GetAttributes())
		{
			ImGui::Text("attr: %s", attribute->ToString().GetData());
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

	void SampleApp::OnFrame()
	{
		DebugGUI::Instance()->NewFrame();

		///////////////////////////////////////////////////////////////
		ImGui::SetNextWindowPos(ImVec2(350, 50), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiSetCond_FirstUseEver);
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
					const auto typeName = type->GetName();
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

					ImGui::Text(current->GetFullName());
					
					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						ImGui::Text(baseType->GetName());

					ImGui::Separator();
					DrawMembers(current, true);
					DrawAttributes(current);

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
		auto renderer = Renderer::Instance();
		auto graphics = Graphics::Instance();
		auto gui = DebugGUI::Instance();

		_pool->Update();

		renderer->Clear(Color32(114, 144, 154));
		if (renderer->BeginScene())
		{
// 			_plasma->Apply(_texture,
// 				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10));
// 			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
			graphics->SetMaterial(Graphics::MT_TRANSPARENT);
			graphics->SetProjection(Graphics::PM_2D);
			if (_font)
				graphics->PrintText(Vector2(10, 10), 15, "qwertyuiopasdfghjklzxcvbnm", _font, Color32::Black);
			if (_tex)
				graphics->DrawQuad(IntRect(10, 30, _tex->GetWidth() * 2, _tex->GetHeight() * 2), 15, _tex);
			_pool->Render();
			graphics->Flush();

			gui->SetupCamera();
			gui->Draw();

			renderer->EndScene();
		}
	}
}

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	uut::SampleApp app;
	app.Run();

	return 0;
}