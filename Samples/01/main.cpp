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
#include <CES/EntityPool.h>
#include <CES/Entity.h>
#include <CES/EntityMatcher.h>
#include <Video/Color.h>
#include <Video/Sprite.h>
#include <Core/Time.h>
#include <GUI/GUI.h>

namespace uut
{
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
	UUT_ENUMFLAG(uut, TestFlags, Test)
	UUT_ENUMFLAG_IMPLEMENT(TestFlags)
	{
		RegisterValues(
			"ValueA", Test::ValueA,
			"ValueB", Test::ValueB,
			"ValueC", Test::ValueC,
			"ValueZ", Test::ValueZ);
 		EnumRegisterMemebers<Test>(internalType);
	}

	enum class Direction
	{
		North,
		East,
		South,
		West,
	};
	UUT_ENUM(uut, Direction);
	UUT_ENUM_IMPLEMENT(Direction)
	{
		RegisterValues(
			"North", Direction::North,
			"East", Direction::East,
			"South", Direction::South,
			"West", Direction::West);
		EnumRegisterMemebers<Direction>(internalType);
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

#define UUT_COMPONENT(library, name, dataType, dataName) \
	class name : public Component \
	{ \
		UUT_VALUETYPE(library, name, Component) \
	public: \
		dataType dataName; \
		void Reset(const dataType& value) \
		{ dataName = value; } \
	}; \
	UUT_VALUETYPE_IMPLEMENT(name) {} \

	class UIWidget : public Component
	{
		UUT_VALUETYPE(uut, UIWidget, Component)
	public:
		IntRect rect;

		void Reset(int x, int y, int w, int h)
		{
			rect = IntRect(x, y, w, h);
		}
	};
	UUT_VALUETYPE_IMPLEMENT(UIWidget) {}

	UUT_COMPONENT(uut, UIImage, SharedPtr<Sprite>, sprite)
	UUT_COMPONENT(uut, UIColor, Color32, color)

	class UILabel : public Component
	{
		UUT_VALUETYPE(uut, UILabel, Component)
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
					r, 15, img ? img->sprite->GetTexture() : nullptr,
					img ? img->sprite->GetTextureRect() : Rect::Zero,
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

	template<class C>
	static SharedPtr<C> LoadResource(const Path& path, const Dictionary<HashString, Variant>& params = Dictionary<HashString, Variant>::Empty)
	{
		static ModuleInstance<ResourceCache> cache;

		const bool silent = params.Contains("silent");
		return cache->Load<C>(path, silent);
	}

	template<>
	static SharedPtr<Sprite> LoadResource<Sprite>(const Path& path, const Dictionary<HashString, Variant>& params)
	{
		static ModuleInstance<ResourceCache> cache;

		const bool silent = params.Contains("silent");
		auto tex = cache->Load<Texture2D>(path, silent);
		if (tex == nullptr)
			return nullptr;

		auto it = params.Find("rect");
		if (it != params.End())
		{
			IntRect rect;
			if (it->second.TryGet<IntRect>(rect))
				return Sprite::Create(tex, rect);
		}

		return Sprite::Create(tex, IntRect(0, 0, tex->GetSize()));
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

		Context::CreateModule<DebugGUI>();
		Context::CreateModule<Graphics>();

		Graphics::Instance()->SetProjection(Graphics::PM_2D);
		ModuleInstance<ResourceCache> cache;
		_tex = LoadResource<Texture2D>("rogueliketiles.png", { {"silent", nullptr} });
			// cache->Load<Texture2D>("rogueliketiles.png");
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
		_pool = MakeShared<EntityPool>();
		_pool->CreateSystem<UIImageRender>();
		_pool->CreateEntity()->
			Add<UIWidget>(20, 20, 200, 50)->
			Add<UIImage>(LoadResource<Sprite>("rogueliketiles.png", { {"rect", IntRect(0, 5 * 16, 32, 32)} }));
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
			GUI::BeginHorizontal();
			auto it = args[i];
			if (i > 0)
				GUI::Text(",");

			GUI::Text(it->GetName());
			GUI::EndHorizontal();
		}
	}

	static void DrawMembers(const Type* type, bool showCtor)
	{
		for (auto info : type->GetMembers())
		{
			GUI::BeginHorizontal();
			switch (info->GetMemberType())
			{
			case MemberType::Property:
			{
				GUI::Text(String::Format("prop: %s", info->GetName().GetData()));
				auto prop = static_cast<const IPropertyInfo*>(info);
				if (prop->IsStatic())
				{
					auto value = prop->GetValue(nullptr).Get<int>();
					GUI::Text(String::Format(" = %d", value));
				}
			}
			break;

			case MemberType::Constructor:
				if (showCtor)
				{
					GUI::Text("Constructor (");
					auto ctor = (const IConstructorInfo*)info;
					DrawArgList(ctor->GetArgsTypes());
					GUI::Text(")");
				}
				break;

			case MemberType::Method:
				{
					auto method = (const IMethodInfo*)info;
					GUI::Text(String::Format("method: %s %s(",
						ArgTypeToString(method->GetReturnType()),
						info->GetName().GetData()));
					DrawArgList(method->GetArgsTypes());
					GUI::Text(")");
				}
				break;

			case MemberType::Converter:
			{
				auto converter = (const IConverterInfo*)info;
				GUI::Text(String::Format("Convert to %s", converter->GetResultType()->GetName()));
			}
			break;

			default:
				GUI::Text(info->GetName());
			}
			GUI::EndHorizontal();
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
			show_test_window = GUI::Toggle("Show Test Window", show_test_window);

			GUI::Separator();
			static bool pluginFoldout = true;
			pluginFoldout = GUI::Foldout("Plugins", pluginFoldout);
			if (pluginFoldout)
			{
				GUI::BeginListBox("##plugins");
				auto plugins = Context::GetPlugins();
				for (auto& it : plugins)
					GUI::Selectable(it->ToString());
				GUI::EndListBox();
			}

			GUI::Separator();
			static bool typesFoldout = true;

			typesFoldout = GUI::Foldout("Types", typesFoldout);
			if (typesFoldout)
			{
				static const Type* current = nullptr;

				static ImGuiTextFilter filter;

				static List<const Type*> typeList;
				if (typeList.IsEmpty())
				{
					typeList = Context::GetTypes().GetValues();
					typeList.Sort([](const Type* a, const Type* b) -> int {
						return String::Compare(a->GetFullName(), b->GetFullName(), StringComparison::OrdinalIgnoreCase);
					});
				}

				filter.Draw();
				ImGui::PushItemWidth(150);
				GUI::BeginHorizontal();
				GUI::BeginListBox("##types");
				for (auto type : typeList)
				{
					const char* typeName = type->GetFullName();
					if (!filter.PassFilter(typeName))
						continue;

					GUI::BeginHorizontal();
					if (GUI::Selectable(typeName, type == current))
						current = type;
					GUI::Text(String::Format("(%d)", type->GetSize()));
					GUI::EndHorizontal();
				}
				GUI::EndListBox();
				ImGui::PopItemWidth();

				if (current != nullptr)
				{
					GUI::BeginVertical();
					GUI::Text(current->GetFullName());
					
					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						GUI::Text(baseType->GetFullName());

					GUI::Separator();
					DrawMembers(current, true);

					GUI::Separator();
					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						DrawMembers(baseType, false);
					GUI::EndVertical();
				}
				GUI::EndHorizontal();
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

		_pool->Update(Time::GetDeltaTime());

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