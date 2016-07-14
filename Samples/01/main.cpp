#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Rect.h>
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
#include <CES/Matcher.h>
#include <CES/EntityGroup.h>

namespace uut
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
		internalType->AddAttribute(new TestAttribute("hello"));
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
		internalType->AddAttribute(new TestAttribute("world"));
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
	class Position : public Component
	{
		UUT_VALUETYPE(Position, Component)
	public:
		int x, y;

		void Reset(int ix, int iy)
		{
			x = ix;
			y = iy;
		}
	};

	UUT_VALUETYPE_IMPLEMENT(Position) {}

	class Move : public Component
	{
		UUT_VALUETYPE(Move, Component)
	public:
		int dx, dy;

		void Reset(int idx, int idy)
		{
			dx = idx;
			dy = idy;
		}
	};
	UUT_VALUETYPE_IMPLEMENT(Move) {}

	class MoveSystem : public System
	{
	protected:
		SharedPtr<EntityGroup> _group;

		void Init() override
		{
			_group = _pool->AddGroup(Matcher::AllOf<Move>());
			_group->onAdd += [](const SharedPtr<Entity>& entity)
			{
				int a = 0;
				a++;
			};
		}

		void Execute() override
		{
			for (auto& ent : _pool->GetEntities(Matcher::AllOf<Position, Move>()))
			{
				auto pos = ent->Get<Position>();
				auto move = ent->Get<Move>();
				ent->Replace<Position>(
					pos->x + move->dx,
					pos->y + move->dy);
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		Context::RegisterType<TestFlags>();
		UUT_REGISTER_ENUM(Direction);
		UUT_REGISTER_OBJECT(TestAttribute);

		Context::RegisterModule(new DebugGUI());
		Context::RegisterModule(new Graphics());

		Graphics::Instance()->SetProjection(Graphics::PM_2D);
		_tex = ResourceCache::Instance()->Load<Texture2D>("rogueliketiles.png");
		_font = ResourceCache::Instance()->Load<Font>("Consolas.fnt");

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
		EntityPool pool;
		pool.AddSystem(new MoveSystem());
		auto ent1 = pool.CreateEntity()->
			Add<Position>(10, 15)->
			Add<Move>(5, 0);
		pool.Execute();

		pool.CreateEntity()->
			Add<Position>(4, 2);

		auto pos = ent1->Get<Position>();
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