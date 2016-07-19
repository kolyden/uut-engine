#include "TestTilemap.h"
#include "TestItemAttribute.h"
#include <Core/Math/Rect.h>
#include <Core/IO/Input.h>
#include <Video/Texture2D.h>
#include <Resources/ResourceLoader.h>
#include <Tilemap/InfoLayer.h>
#include <Tilemap/ObjectLayer.h>
#include <Tilemap/TilesetLayer.h>
#include <Tilemap/Tileset.h>
#include <Video/Graphics.h>
#include <Resources/ResourceCache.h>
#include <Tilemap/ObjectLayerItem.h>

namespace uut
{
	enum class Direction {North, East, South, West};
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
	};

	UUT_OBJECT_IMPLEMENT(CellInfoLayer)
	{}

	////////////////////////////////////////////////////////////////////////////
	class MapDoor : public ObjectLayerItem
	{
		UUT_OBJECT(MapDoor, ObjectLayerItem)
	public:
		MapDoor(const SharedPtr<TilesetLayer>& layer, uint8_t doorClosed, uint8_t doorOpen, bool opened = false)
			: _tilelayer(layer)
			, _tileClosed(doorClosed)
			, _tileOpened(doorOpen)
		{
			_flags.SetValue(ObjectLayerFlag::Blocked, !opened);
		}

		void SetBlocked(bool blocked)
		{
			if (IsBlocked() == blocked)
				return;

			_flags.SetValue(ObjectLayerFlag::Blocked, blocked);
			UpdateTile();
		}

		void SetOpened(bool opened) { SetBlocked(!opened); }

	protected:
		SharedPtr<TilesetLayer> _tilelayer;
		uint8_t _tileClosed;
		uint8_t _tileOpened;

		virtual void OnInit() override
		{
			UpdateTile();
		}

		void UpdateTile()
		{
			_tilelayer->SetTile(_position.x, _position.y,
				IsBlocked() ? _tileClosed : _tileOpened);
		}
	};
	UUT_OBJECT_IMPLEMENT(MapDoor) {}

	////////////////////////////////////////////////////////////////////////////
	class Player : public ObjectLayerItem
	{
		UUT_OBJECT(Player, ObjectLayerItem)
	public:
		Player(const SharedPtr<Texture2D>& tex, const SharedPtr<CellInfoLayer>& passability)
			: _texture(tex)
			, _passability(passability)
			, _moving(false)
		{
		}

		void OnUpdate(float deltaTime) override
		{
			if (!_moving)
				return;

			auto layer = _layer.Lock();
			if (!layer)
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
				const auto& size = layer->GetTilemap()->GetCellSize();
				switch (_moveDir)
				{
				case Direction::West: _offset = Vector2::Scale(size, Vector2(+t, 0)); break;
				case Direction::East: _offset = Vector2::Scale(size, Vector2(-t, 0)); break;
				case Direction::North: _offset = Vector2::Scale(size, Vector2(0, -t)); break;
				case Direction::South: _offset = Vector2::Scale(size, Vector2(0, +t)); break;
				}
			}
		}

		void Move(Direction dir)
		{
			if (_moving)
				return;

			auto layer = _layer.Lock();
			if (!layer)
				return;

			static const Dictionary<Direction, IntVector2> dirOffset = {
				{ Direction::West, IntVector2(-1, 0) },
				{ Direction::East, IntVector2(+1, 0) },
				{ Direction::North, IntVector2(0, -1) },
				{ Direction::South, IntVector2(0, +1) }
			};

			IntVector2 offset;
			if (!dirOffset.TryGetValue(dir, offset))
				return;

			const IntVector2 newPos = _position + offset;
			if (_passability->IsBlocked(newPos.x, newPos.y))
				return;

			auto item = layer->GetItemAt(newPos);
			if (item != nullptr)
			{
				if (item->IsBlocked())
				{
					auto door = DynamicCast<MapDoor>(item);
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
			OnUpdate(0);
		}

		void Move(int dx, int dy)
		{
			SetPosition(_position + IntVector2(dx, dy));
		}

		void OnRender() const override
		{
			static ModuleInstance<Graphics> graphics;
			auto layer = _layer.Lock();
			if (!layer)
				return;

			auto tilemap = layer->GetTilemap();
			auto& size = tilemap->GetSize();
			auto& cellSize = tilemap->GetCellSize();

			auto pos = IntVector2(_position.x, size.y - _position.y - 1);
			graphics->DrawQuad(Rect(Vector2::Scale(cellSize, pos) + _offset, cellSize), 15, _texture);
		}

	protected:
		SharedPtr<Texture2D> _texture;
		SharedPtr<CellInfoLayer> _passability;
		bool _moving;
		Direction _moveDir;
		float _time;
		Vector2 _offset;
	};

	UUT_OBJECT_IMPLEMENT(Player) {}

	////////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(TestTilemap)
	{
		internalType->AddAttribute(new TestItemAttribute(TestCategory::Basic, "Tilemap"));
	}

	TestTilemap::TestTilemap()
	{
		_tilemap = new Tilemap();
		_tilemap->SetSize(IntVector2(11));
		_tilemap->SetCellSize(Vector2(32));
		auto layer1 = _tilemap->CreateLayer<TilesetLayer>("Tiles");
		auto layer2 = _tilemap->CreateLayer<TilesetLayer>("Objects");
		auto layer3 = _tilemap->CreateLayer<ObjectLayer>("Characters");
		auto layer4 = _tilemap->CreateLayer<CellInfoLayer>("Passability");

		auto tileset = new Tileset();
		tileset->SetTexture(_cache->Load<Texture2D>("rogueliketiles.png"));
		tileset->GenerateItems(IntVector2(16));

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

		Dictionary<Direction, IntVector2> pairs = {
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
	}

	void TestTilemap::OnUpdate(float deltaTime)
	{
		if (_tilemap)
			_tilemap->Update(deltaTime);

		if (_player)
		{
			if (Input::IsKeyDown(SDL_SCANCODE_LEFT)) _player->Move(Direction::West);
			if (Input::IsKeyDown(SDL_SCANCODE_RIGHT)) _player->Move(Direction::East);
			if (Input::IsKeyDown(SDL_SCANCODE_UP)) _player->Move(Direction::North);
			if (Input::IsKeyDown(SDL_SCANCODE_DOWN)) _player->Move(Direction::South);
		}
	}

	void TestTilemap::OnRender() const
	{
		if (_tilemap)
			_tilemap->Render();
	}
}