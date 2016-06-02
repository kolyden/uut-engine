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
#include <Resources/ResourceLoader.h>
#include <Video/BitmapFont.h>
#include <Video/Loaders/BitmapFontLoader.h>
#include <Tilemap/Tilemap.h>
#include <Tilemap/TilesetLayer.h>
#include <Tilemap/Tileset.h>
#include <Tilemap/ObjectLayer.h>
#include <Tilemap/PassabilityLayer.h>
#include <Tilemap/InfoLayer.h>

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
	template <typename T>
	struct _eat {
		T   _value;

		template <typename Any>
		_eat& operator =(Any value) { return *this; }   // Игнорирует аргумент.

		explicit _eat(T value) : _value(value) { }      // Преобразует из T.
		operator T() const { return _value; }           // Преобразует в T.
	};

#define EXPAND(X) X    // for MSVC10 compatibility

	// compute number of (variadic) macro arguments
	// from http://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5?pli=1
#define PP_NARG(...) EXPAND( PP_NARG_(__VA_ARGS__, PP_RSEQ_N()) )
#define PP_NARG_(...) EXPAND( PP_ARG_N(__VA_ARGS__) )
#define PP_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define PP_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0

#define PP_ENUM_NAME_1(arg0) #arg0
#define PP_ENUM_NAME_2(arg0, arg1) #arg0, #arg1
#define PP_ENUM_NAME_3(arg0, arg1, arg2) #arg0, #arg1, #arg2
#define PP_ENUM_NAME_4(arg0, arg1, arg2, arg3) #arg0, #arg1, #arg2, #arg3

#define PP_ENUM_NAME_(N) PP_ENUM_NAME_##N
#define PP_ENUM_NAME_EVAL(N) PP_ENUM_NAME_(N)
#define PP_ENUM_NAME(...) EXPAND( PP_ENUM_NAME_EVAL(EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )

#define PP_ENUM_VALUE_1(arg0) (_eat<Enum>)arg0
#define PP_ENUM_VALUE_2(arg0, arg1) (_eat<Enum>)arg0, (_eat<Enum>)arg1
#define PP_ENUM_VALUE_3(arg0, arg1, arg2) (_eat<Enum>)arg0, (_eat<Enum>)arg1, (_eat<Enum>)arg2
#define PP_ENUM_VALUE_4(arg0, arg1, arg2, arg3) (_eat<Enum>)arg0, (_eat<Enum>)arg1, (_eat<Enum>)arg2, (_eat<Enum>)arg3

#define PP_ENUM_VALUE_(N) PP_ENUM_VALUE_##N
#define PP_ENUM_VALUE_EVAL(N) PP_ENUM_VALUE_(N)
#define PP_ENUM_VALUE(...) EXPAND( PP_ENUM_VALUE_EVAL(EXPAND( PP_NARG(__VA_ARGS__) ))(__VA_ARGS__) )



#define UUT_ENUM_TEST(name, ...) \
	struct name { \
	enum Enum { __VA_ARGS__ }; \
	static constexpr int COUNT = PP_NARG(__VA_ARGS__); \
	static const char* NAMES[COUNT]; \
	static const int VALUES[COUNT]; \
	}; \
	const char* name::NAMES[COUNT] = { EXPAND( PP_ENUM_NAME(__VA_ARGS__) ) }; \
	const int name::VALUES[COUNT] = { EXPAND( PP_ENUM_VALUE(__VA_ARGS__) ) };

	UUT_ENUM_TEST(Direction, North = 1, East = 2, South = 4, West = 8)

	template<typename T>
	static void RegisterValues(Type* type, unsigned count, const char* names[], const int values[])
	{
		for (unsigned i = 0; i < count; i++)
		{
			String name = names[i];
			int value = values[i];
			type->AddMember(
				new StaticPropertyInfo<T>(name,
					[name, value]() -> T { return (T)value; }, nullptr));
		}
	}

	////////////////////
#define UUT_ENUM(type) \
	class type ## Enum : public EnumValue<type> \
	{ UUT_STRUCT(type ## Enum, Enum) \
	public: constexpr type ## Enum() {} \
	constexpr type ## Enum(type value) : EnumValue(value) {} }; \
	UUT_FUNDAMENTAL(type, type ## Enum) \
	namespace detail { template<>struct Enum<type> { typedef type ## Enum TYPE; }; }

#define UUT_ENUM_IMPLEMENT(type) \
	UUT_STRUCT_IMPLEMENT(type ## Enum)

#define UUT_REGISTER_ENUM(type) \
	UUT_REGISTER_TYPE(TypeInfo::Enum, EnumValue<type>, #type)

#define UUT_REGISTER_ENUM_VALUE(name) \
	internalType->AddMember( \
		new StaticPropertyInfo<EnumType>(#name, \
			[]() -> EnumType { return EnumType::name; }, nullptr));

#define UUT_REGISTER_ENUM_VALUE_EX(name, value) \
	internalType->AddMember( \
		new StaticPropertyInfo<EnumType>(name, \
			[]() -> EnumType { return value; }, nullptr));

	UUT_ENUM(Test)

	UUT_ENUM_IMPLEMENT(Test)
	{
 		UUT_REGISTER_ENUM_VALUE(ValueA);
		UUT_REGISTER_ENUM_VALUE(ValueB);
		UUT_REGISTER_ENUM_VALUE(ValueC);
		UUT_REGISTER_ENUM_VALUE(ValueD);
		UUT_REGISTER_ENUM_VALUE(ValueZ);

		UUT_REGISTER_CONVERTER_FUNC(String, ToString);
	}

	////////////////////////////////////////////////////////////////////////////
	struct CellInfo
	{
		bool blocked;
	};

	class CellInfoLayer : public InfoLayer<CellInfo>
	{
		UUT_OBJECT(CellInfoLayer, TilemapLayer)
	public:

		void SetBlocked(int x, int y, bool blocked) { Get(x, y).blocked = blocked; }
		bool IsBlocked(int x, int y) const { return Get(x, y).blocked; }

		void Update(float deltaTime) override {}
		void DrawLayer(Graphics* graphics) const override {}
	};

	UUT_OBJECT_IMPLEMENT(CellInfoLayer)
	{}

	////////////////////////////////////////////////////////////////////////////
	class MapDoor : public ObjectLayerItem
	{
	public:
		MapDoor(TilesetLayer* layer, uint8_t doorClosed, uint8_t doorOpen, bool opened = false)
			: _tilelayer(layer)
			, _tileClosed(doorClosed)
			, _tileOpened(doorOpen)
			, _opened(opened)
		{}

		void SetOpened(bool opened)
		{
			if (_opened == opened)
				return;

			_opened = opened;
			UpdateTile();
		}

		bool IsOpened() const
		{
			return _opened;
		}

		virtual void Update(float deltaTime) override {}
		virtual void Draw(Graphics* graphics) const override {}
		virtual bool IsBlocked() const override { return !IsOpened(); }

	protected:
		WeakPtr<TilesetLayer> _tilelayer;
		uint8_t _tileClosed;
		uint8_t _tileOpened;
		bool _opened;

		virtual void OnInit() override
		{
			UpdateTile();
		}

		void UpdateTile()
		{
			_tilelayer->SetTile(_position.x, _position.y,
				_opened ? _tileOpened : _tileClosed);
		}
	};

	////////////////////////////////////////////////////////////////////////////
	class Player : public ObjectLayerItem
	{
	public:
		Player(Texture2D* tex, CellInfoLayer* passability)
			: _texture(tex), _passability(passability), _moving(false)
		{
		}

		void Update(float deltaTime) override
		{
			if (!_moving)
				return;

			const float moveTime = 0.1f;

			_time += deltaTime;
			if (_time >= moveTime)
			{
				_moving = false;
				_offset = Vector2::Zero;
			}
			else
			{
				const float t = 1.0f - _time / moveTime;
				const auto& size = _layer->GetTilemap()->GetCellSize();
				switch (_moveDir)
				{
				case Direction::West: _offset = Vector2::Scale(size, Vector2(+t, 0)); break;
				case Direction::East: _offset = Vector2::Scale(size, Vector2(-t, 0)); break;
				case Direction::North: _offset = Vector2::Scale(size, Vector2(0, -t)); break;
				case Direction::South: _offset = Vector2::Scale(size, Vector2(0, +t)); break;
				}
			}
		}

		void Move(Direction::Enum dir)
		{
			if (_moving)
				return;

			static const Dictionary<Direction::Enum, IntVector2> dirOffset = {
				{Direction::West, IntVector2(-1, 0) },
				{Direction::East, IntVector2(+1, 0) },
				{Direction::North, IntVector2(0, -1) },
				{Direction::South, IntVector2(0, +1) }
			};

			IntVector2 offset;
			if (!dirOffset.TryGetValue(dir, offset))
				return;

			const IntVector2 newPos = _position + offset;
			if (_passability->IsBlocked(newPos.x, newPos.y))
				return;

			auto item = _layer->GetItem(newPos);
			if (item != nullptr)
			{
				if (item->IsBlocked())
				{
					auto door = dynamic_cast<MapDoor*>(item);
					if (door == nullptr)
						return;

					door->SetOpened(true);
					return;
				}
			}

			_position = newPos;
			_moving = true;
			_moveDir = dir;
			_time = 0;
			Update(0);
		}

		void Move(int dx, int dy)
		{
			SetPosition(_position + IntVector2(dx, dy));
		}

		void Draw(Graphics* graphics) const override
		{
			auto tilemap = _layer->GetTilemap();
			auto& size = tilemap->GetSize();
			auto& cellSize = tilemap->GetCellSize();

			auto pos = IntVector2(_position.x, size.y - _position.y - 1);
			graphics->DrawQuad(Rect(Vector2::Scale(cellSize, pos) + _offset, cellSize), 15, _texture);
		}

	protected:
		SharedPtr<Texture2D> _texture;
		WeakPtr<CellInfoLayer> _passability;
		bool _moving;
		Direction::Enum _moveDir;
		float _time;
		Vector2 _offset;
	};

	////////////////////////////////////////////////////////////////////////////
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		UUT_REGISTER_OBJECT(TestEnum);

		_gui = new DebugGUI();
		_graphics = new Graphics();
		_graphics->SetProjection(Graphics::PM_2D);
		_font = _cache->Load<Font>("Consolas.fnt");

		_tilemap = new Tilemap();
		_tilemap->SetSize(IntVector2(11));
		_tilemap->SetCellSize(Vector2(32));
		auto layer1 = _tilemap->AddLayer<TilesetLayer>("Tiles");
		auto layer2 = _tilemap->AddLayer<TilesetLayer>("Objects");
		auto layer3 = _tilemap->AddLayer<ObjectLayer>("Characters");
		auto layer4 = _tilemap->AddLayer<CellInfoLayer>("Passability");

		auto tileset = new Tileset();
		tileset->SetTexture(_cache->Load<Texture2D>("rogueliketiles.png"));
		tileset->GenerateItems(IntVector2(16));
// 		tileset->SetItems({
// 			TilesetItem(16, 0, 16, 16), TilesetItem(16, 16, 16, 16), TilesetItem(32, 0, 16, 16),
// 			TilesetItem(0, 0, 16, 16), TilesetItem(0, 48, 16, 16) });

		layer1->SetTileset(tileset);
		layer1->ForEach([this, layer4](int x, int y, uint8_t& tile)
		{
			const uint8_t grassTile = 1;
			const uint8_t wallTile = 7;

			if (x == 0 || y == 0 || x == _tilemap->GetSize().x - 1 || y == _tilemap->GetSize().y - 1)
			{
				tile = wallTile;
				layer4->SetBlocked(x, y, true);
			}
			else
			{
				tile = grassTile;
				layer4->SetBlocked(x, y, false);
			}
		});
		layer1->SetTile(5, 0, 1); layer4->SetBlocked(5, 0, false);

		Dictionary<Direction::Enum, IntVector2> pairs = {
			{ Direction::North, IntVector2::Zero },
			{ Direction::West, IntVector2::Zero }
		};

		const uint8_t treeTile = 0;
		const uint8_t torchTile = 16;
		const uint8_t welltile = 42;
		layer2->SetTileset(tileset);
		layer2->SetTransparent(true);
		layer2->Clear();
		layer2->SetTile(3, 3, treeTile); layer4->SetBlocked(3, 3, true);
		layer2->SetTile(6, 7, treeTile); layer4->SetBlocked(6, 7, true);
		layer2->SetTile(2, 8, treeTile); layer4->SetBlocked(2, 8, true);
		layer2->SetTile(4, 0, torchTile);
		layer2->SetTile(6, 0, torchTile);
		layer2->SetTile(5, 5, welltile); layer4->SetBlocked(5, 5, true);

		_player = new Player(_cache->Load<Texture2D>("angel.png"), layer4);
		layer3->AddItem(IntVector2(5, 1), _player);
		layer3->AddItem(IntVector2(5, 0), new MapDoor(layer2, 2, 3));
		layer3->AddItem(IntVector2(8, 1), new MapDoor(layer2, 18, 19));

		_timer.Start();

		Variant var1(Vector2(12.111f, 45.6789f));
		Variant var2(_font);
		Variant var3(666.555f);
		Variant var4(true);
		Variant var5(Test::ValueZ);
		Variant var6(typeof<float>());
		Variant var7(Math::HALF_PI);
		Variant var8(L'Я');
		Variant var9(256);

		constexpr auto bool_def = GetDefault<bool>(); UUT_ASSERT(bool_def == false);
		constexpr auto float_def = GetDefault<float>(); UUT_ASSERT(float_def == 0.0f);
		constexpr auto int_def = GetDefault<int>(); UUT_ASSERT(int_def == 0);
		constexpr auto enum_def = GetDefault<Test>(); UUT_ASSERT(enum_def == Test::ValueA);
		auto ivec2_def = GetDefault<IntVector2>(); UUT_ASSERT(ivec2_def == IntVector2::Zero);

		auto vec = var1.Get<Vector2>();
		auto ivec = var1.Get<IntVector2>(); UUT_ASSERT(ivec == Vector2(12, 46));
		auto obj = var2.Get<Object>(); UUT_ASSERT(obj == _font);
		auto i = var3.Get<int>(); UUT_ASSERT(i == 666);
		auto b = var4.Get<bool>(); UUT_ASSERT(b == true);
		auto flag = var5.Get<Test>(); UUT_ASSERT(flag == Test::ValueZ);
		auto flagInt = var5.Get<int>(); UUT_ASSERT(flagInt == 42);
		auto type = var6.Get<Type>(); UUT_ASSERT(type == typeof<float>());
		auto angleDeg = var7.Get<Degree>(); UUT_ASSERT(angleDeg.GetDegrees() == 90);
		auto angle = var7.Get<float>(); UUT_ASSERT(angle == Math::HALF_PI.GetRadians());
		auto c = var8.Get<wchar_t>(); UUT_ASSERT(c == L'Я');
		auto vari = var9.Get<int>(); UUT_ASSERT(vari == 256);
		auto varf = var9.Get<float>(); UUT_ASSERT(varf == 256);
		auto vars = var9.Get<String>(); UUT_ASSERT(vars == "256");

		auto fstr = var3.Get<String>();
		auto flagStr = var5.Get<String>();

		auto str = StringFormat("Object type = ", typeof<Test>(), " and value = ");
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

	void SampleApp::OnFrame()
	{
		_timer.Update();
		_gui->NewFrame();
		if (_tilemap)
			_tilemap->Update(_timer.GetDeltaTime());

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

		if (_player)
		{
			if (Input::IsKeyDown(SDL_SCANCODE_LEFT)) _player->Move(Direction::West);
			if (Input::IsKeyDown(SDL_SCANCODE_RIGHT)) _player->Move(Direction::East);
			if (Input::IsKeyDown(SDL_SCANCODE_UP)) _player->Move(Direction::North);
			if (Input::IsKeyDown(SDL_SCANCODE_DOWN)) _player->Move(Direction::South);
		}

		///////////////////////////////////////////////////////////////
		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
// 			_plasma->Apply(_texture,
// 				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10));
// 			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
			_graphics->SetMaterial(Graphics::MT_TRANSPARENT);
			_graphics->SetProjection(Graphics::PM_2D);
			if (_font)
				_graphics->PrintText(Vector2(10, 10), 15, "qwertyuiopasdfghjklzxcvbnm", _font, Color32::Black);
			_graphics->Flush();

			if (_tilemap)
				_tilemap->Draw(_graphics);
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
	uut::SampleApp app;
	app.Run();

	return 0;
}