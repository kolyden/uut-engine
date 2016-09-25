#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Quaternion.h>
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
#include <Video/Mesh.h>
#include <Core/Time.h>
#include <GUI/GUI.h>
#include <Video/FreeCamera.h>
#include <Quake1/Quake1Plugin.h>
#include <Quake1/Quake1ModelLoader.h>
#include <Quake1/Quake1Model.h>

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
		cache->AddLoader(SharedPtr<Quake1ModelLoader>::Make());
		_tex = LoadResource<Texture2D>("rogueliketiles.png", { {"silent", nullptr} });
			// cache->Load<Texture2D>("rogueliketiles.png");
		_font = cache->Load<Font>("Consolas.fnt");
		_model = cache->Load<Quake1Model>("player.mdl");

		_camera = SharedPtr<FreeCamera>::Make();
		_camera->SetPosition(Vector3(8.5f, 10, -50));

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
		ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_FirstUseEver);
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

		float moveSpeed = 50.0f;
		Radian rotateSpeed = Math::PI / 2;
		if (Input::IsKey(Scancode::Space))
		{
			moveSpeed *= 4;
			rotateSpeed *= 2;
		}
		if (Input::IsKey(Scancode::A))
			_camera->MoveRight(-moveSpeed * Time::GetDeltaTime());
		if (Input::IsKey(Scancode::D))
			_camera->MoveRight(+moveSpeed * Time::GetDeltaTime());
		if (Input::IsKey(Scancode::S))
			_camera->MoveForward(-moveSpeed * Time::GetDeltaTime());
		if (Input::IsKey(Scancode::W))
			_camera->MoveForward(+moveSpeed * Time::GetDeltaTime());
		if (Input::IsKey(Scancode::Q))
			_camera->MoveUp(-moveSpeed * Time::GetDeltaTime());
		if (Input::IsKey(Scancode::E))
			_camera->MoveUp(+moveSpeed * Time::GetDeltaTime());

		if (Input::IsKey(Scancode::Left))
			_camera->Yaw(-rotateSpeed*Time::GetDeltaTime());
		if (Input::IsKey(Scancode::Right))
			_camera->Yaw(+rotateSpeed*Time::GetDeltaTime());

		if (Input::IsKey(Scancode::Up))
			_camera->Pitch(-rotateSpeed*Time::GetDeltaTime());
		if (Input::IsKey(Scancode::Down))
			_camera->Pitch(+rotateSpeed*Time::GetDeltaTime());

		///////////////////////////////////////////////////////////////
		auto renderer = Renderer::Instance();
		auto graphics = Graphics::Instance();
		auto gui = DebugGUI::Instance();

		renderer->Clear(Color32(114, 144, 154));
		if (renderer->BeginScene())
		{
// 			_plasma->Apply(_texture,
// 				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10))
// 			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
			graphics->SetMaterial(Graphics::MT_OPAQUE);
			graphics->SetProjection(Graphics::PM_3D);
			graphics->Flush();

			Matrix4 oldMat = renderer->GetTransform(RT_VIEW);
			auto& cameraMat = _camera->UpdateViewMatrix();
			renderer->SetTransform(RT_VIEW, cameraMat);

			graphics->DrawLine(Vector3::Zero, Vector3::AxisX * 100, Color32::Red);
			graphics->DrawLine(Vector3::Zero, Vector3::AxisY * 100, Color32::Green);
			graphics->DrawLine(Vector3::Zero, Vector3::AxisZ * 100, Color32::Blue);

			if (_model)
			{				
				static const List<HashString> anim = {
					"axstnd1", "axstnd2", "axstnd3", "axstnd4", "axstnd5", "axstnd6", "axstnd7",
					"axstnd8", "axstnd9", "axstnd10", "axstnd11", "axstnd12"
				};
				static const float frameTime = 0.15f;
				static int index = 0;
				static float time = 0;

				const Vector3 pos = Vector3(20, 0, 30);
				graphics->DrawLine(pos, pos + Vector3::AxisY * 10, Color32::Magenta);

				static const auto rot = Quaternion::RotationAxis(Vector3::AxisX, -Degree::Angle90) *
					Quaternion::RotationAxis(Vector3::AxisY, Degree::Angle90);

				static const Matrix4 mat = Matrix4::Transformation(pos, Quaternion::Identity, Vector3::One);
				auto& frames = _model->GetFrames();
				auto it = _model->GetAnimations().Find(anim[index]);
				if (it != _model->GetAnimations().End())
					graphics->DrawGeometry(mat, frames[it->second], _model->GetSkins()[0]);

				time += Time::GetDeltaTime();
				while (time >= frameTime)
				{
					time -= frameTime;
					index = (index + 1) % anim.Count();
				}
			}

			graphics->Flush();
			renderer->SetTransform(RT_VIEW, oldMat);

			graphics->SetProjection(Graphics::PM_2D);
			graphics->SetMaterial(Graphics::MT_TRANSPARENT);

			if (_font)
				graphics->PrintText(Vector2(10, 10), 15, "qwertyuiopasdfghjklzxcvbnm", _font, Color32::Black);
// 			if (_tex)
// 				graphics->DrawQuad(IntRect(10, 30, _tex->GetWidth() * 2, _tex->GetHeight() * 2), 15, _tex);
			if (_model)
			{
				graphics->SetMaterial(Graphics::MT_OPAQUE);
				const List<SharedPtr<Texture2D>>& skins = _model->GetSkins();
				int x = 0;
				for (size_t i = 0; i < skins.Count(); i++)
				{
					x += 10;
					auto& tex = skins[i];
					graphics->DrawQuad(Rect(Vector2(x, 50), tex->GetSize()), 15, tex);
					x += tex->GetSize().x;
				}
			}
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