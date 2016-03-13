#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Vector2.h>
#include <Core/Math/Vector3.h>
#include <Core/IO/File.h>
#include <Core/Video/Loaders/Texture2DLoader.h>
#include <Core/IO/FileStream.h>
#include "Tileset.h"
#include "Level.h"
#include "LevelChunk.h"
#include <Core/Math/Random.h>

namespace uut
{
	SampleApp::SampleApp()
		: _cellIndex(0, 0)
		, _dragStart(false)
	{
		_windowSize = IntVector2(1024, 768);
		_ground = Plane(Vector3::Zero, Vector3::Up);
	}

	void SampleApp::OnInit()
	{
		_window->SetTitle("Sample 02");

		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_3D);

		_camera = new FreeCamera();
		_camera->SetPosition(Vector3(10, 8, -20));

		auto loader = new Texture2DLoader(_renderer);
		auto entity0 = DynamicCast<Texture2D>(loader->Load(File::OpenRead("angel.png")));
		auto wall0 = DynamicCast<Texture2D>(loader->Load(File::OpenRead("brick_dark0.png")));
		auto floor0 = DynamicCast<Texture2D>(loader->Load(File::OpenRead("crystal_floor0.png")));

		auto tileset = new Tileset();
		tileset->AddFloorTile(floor0);
		tileset->AddWallTile(wall0);

		_level = new Level(tileset);

		_player = new Entity();
		_player->SetTexture(entity0);
		_level->PlaceEntity(_player, IntVector2(5, 5));

		auto chunk = _level->GetChunk(IntVector2(0, 0));
		for (int y = 0; y < LevelChunk::COUNT; y++)
		{
			for (int x = 0; x < LevelChunk::COUNT; x++)
			{
				auto& cell = chunk->GetCell(x, y);
				cell.SetNormalFloor(0);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			const int x = Random::Range(0, LevelChunk::COUNT);
			const int y = Random::Range(0, LevelChunk::COUNT);
// 			const Direction dir = static_cast<Direction>(Random::Range(0, 4));

			auto& cell = chunk->GetCell(x, y);
			cell.SetSolid(0, 0);
		}

		_timer.Start();
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		_timer.Update();

		float moveSpeed = 50.0f;
		Radian rotateSpeed = Math::PI / 2;
		if (_input->IsKey(SDL_SCANCODE_SPACE))
		{
			moveSpeed *= 4;
			rotateSpeed *= 2;
		}

		if (_input->IsKey(SDL_SCANCODE_A))
			_camera->MoveRight(-moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_D))
			_camera->MoveRight(+moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_S))
			_camera->MoveForward(-moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_W))
			_camera->MoveForward(+moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_Q))
			_camera->MoveUp(-moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_E))
			_camera->MoveUp(+moveSpeed * _timer.GetDeltaTime());

		if (_input->IsKeyDown(SDL_SCANCODE_LEFT))
			_player->Move(Direction::West);
		if (_input->IsKeyDown(SDL_SCANCODE_RIGHT))
			_player->Move(Direction::East);
		if (_input->IsKeyDown(SDL_SCANCODE_UP))
			_player->Move(Direction::North);
		if (_input->IsKeyDown(SDL_SCANCODE_DOWN))
			_player->Move(Direction::South);

		if (_input->IsMouseButton(1))
		{
			if (_dragStart)
			{
				Degree dragMove(0.1f);
				if (_input->IsKey(SDL_SCANCODE_SPACE))
					dragMove *= 2;

				auto& curPos = _input->GetMousePos();
				const auto delta = curPos - _dragPos;
				_dragPos = curPos;

				if (delta.x != 0)
					_camera->Yaw(dragMove*delta.x);
				if (delta.y != 0)
					_camera->Pitch(dragMove*delta.y);
			}
			else
			{
				_dragStart = true;
				_dragPos = _input->GetMousePos();
			}
		}
		else _dragStart = false;

		_level->Update(_timer.GetDeltaTime());

		if (_input->IsMouseButton(0))
		{
			const auto ray = _camera->CastRay(_input->GetMousePos(), _renderer);
			Vector3 vec;
			if (_ground.IntersectLine(ray.origin, ray.GetPoint(1000), vec))
			{
				_cellIndex.x = Math::FloorToInt(vec.x / LevelCell::SIZE);
				_cellIndex.y = Math::FloorToInt(vec.z / LevelCell::SIZE);
			}
		}

		///////////////////////////////////////////////////////////////
		if (_renderer->BeginScene())
		{
			_camera->Setup(_renderer);
			_renderer->Clear(Color32(114, 144, 154));

			_graphics->DrawLine(Vector3::Zero, Vector3::Right * 1000, Color32::Red);
			_graphics->DrawLine(Vector3::Zero, Vector3::Up * 1000, Color32::Green);
			_graphics->DrawLine(Vector3::Zero, Vector3::Forward * 1000, Color32::Blue);

			_graphics->DrawWireCube(
				Vector3(
					LevelCell::SIZE * _cellIndex.x + LevelCell::HALF_SIZE, LevelCell::HALF_SIZE,
					LevelCell::SIZE * _cellIndex.y + LevelCell::HALF_SIZE),
				LevelCell::SIZE);
			//_graphics->DrawLine(_groundHit, _groundHit + Vector3::Up * 20, Color32(255, 0, 255));

			_level->Draw(_graphics);

			_graphics->Flush();

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