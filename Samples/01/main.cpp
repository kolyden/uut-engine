#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Quaternion.h>
#include <Core/Context.h>
#include <Core/Variant.h>
#include <Core/Enum.h>
#include <Core/EnumFlags.h>
#include <Core/Reflection/PropertyInfo.h>
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
#include <GUI/ContextGUI.h>
#include <Video/FreeCamera.h>
#include <Core/IO/JSONFile.h>
#include <Core/IO/YamlFile.h>
#include <Core/IO/YamlSerializer.h>
#include <Core/IO/XMLFile.h>
#include <Core/IO/XMLFileLoader.h>
#include <Video/Primitives/Sphere.h>
#include <IMGUI/imgui.h>

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
		Context::RegisterType<DirectionEnum>();

		Context::CreateModule<DebugGUI>();

		ModuleInstance<ResourceCache> cache;
		cache->AddLoader(SharedPtr<JsonFileLoader>::Make());
		cache->AddLoader(SharedPtr<YamlFileLoader>::Make());
		cache->AddLoader(SharedPtr<XMLFileLoader>::Make());

		cache->AddSaver(SharedPtr<YamlFileSaver>::Make());

		_tex = cache->Load<Texture2D>("brick_dark0.png");
		_font = cache->Load<Font>("Consolas.fnt");

		_graphics = SharedPtr<Graphics>::Make(Graphics::MT_OPAQUE, Graphics::PM_3D);

		_mesh = CreateSphere(5);

		_camera = SharedPtr<FreeCamera>::Make();
		_camera->SetPosition(Vector3(8.5f, 10, -50));

		auto xml = cache->Load<XMLFile>("tilemap.xml");
		if (xml)
		{
			auto root = xml->GetRoot();
			for (auto attr = root.FirstAttribute(); attr.Valid(); attr = attr.Next())
			{
				auto name = attr.GetName();
				auto val = attr.GetValue();
			}
		}

// 		auto json = cache->Load<JsonFile>("test.json");
// 		if (json)
// 		{
// 			auto root = json->GetRoot();
// 			float f = root["pi"].ToFloat();
// 			String str = root["name"].ToString();
// 
// 			int a = 0;
// 			a++;
// 		}

// 		auto yaml = SharedPtr<YamlFile>::Make();
// 		if (yaml)
// 		{
// 			auto root = yaml->AddMapping();
// 			root.AppendMapping("i", 12345);
// 			root.AppendMapping("f", 12.345f);
// 			root.AppendMapping("vec", Vector2(12, 42));
// 			cache->Save(yaml, "test.yaml");
// 		}

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

	static List<HashString> MakeRange(const String& prefix, int start, int end)
	{
		List<HashString> list;
		list.SetReserve(end - start + 1);
		for (int i = start; i <= end; i++)
			list.Add(String::Format("%s%d", prefix.GetData(), i).GetData());

		return list;
	}

	void SampleApp::OnFrame()
	{
		DebugGUI::Instance()->NewFrame();

		///////////////////////////////////////////////////////////////
		ContextGUI::Draw();

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
		auto gui = DebugGUI::Instance();

		if (renderer->BeginScene())
		{
			_graphics->BeginRecord();
			_graphics->SetViewport(Viewport(0, 0, renderer->GetScreenSize()));
			_graphics->Clear(Color32(114, 144, 154));
			_graphics->SetProjection(Graphics::PM_3D);
			_graphics->SetMaterial(Graphics::MT_OPAQUE);
			_graphics->SetCamera(_camera);

			_graphics->DrawLine(Vector3::Zero, Vector3::AxisX * 100, Color32::Red);
			_graphics->DrawLine(Vector3::Zero, Vector3::AxisY * 100, Color32::Green);
			_graphics->DrawLine(Vector3::Zero, Vector3::AxisZ * 100, Color32::Blue);

			if (_mesh)
				_graphics->DrawMesh(Matrix4::Translation(10, 10, 10), _mesh, _tex);

			_graphics->SetMaterial(Graphics::MT_TRANSPARENT);
			_graphics->SetProjection(Graphics::PM_2D);
			_graphics->SetViewMatrix(Matrix4::Identity);

			if (_font)
				_graphics->PrintText(Vector2(10, 10), 15, "qwertyuiopasdfghjklzxcvbnm", _font, Color32::Black);

			_graphics->EndRecord();
			_graphics->Draw();

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