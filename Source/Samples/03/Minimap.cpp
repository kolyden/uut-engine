#include "Minimap.h"
#include <IMGUI/imgui.h>
#include "Level.h"
#include "LevelChunk.h"
#include <Core/Math/Math.h>
#include "Tileset.h"

namespace uut
{
	Minimap::Minimap(Level* level)
		: _level(level)
		, _wallTile(0)
		, _toolType(ToolType::Clear)
		, _direction(Direction::North)
	{
		_tileset = _level->GetTileset();
	}

	void Minimap::Update()
	{
		ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiSetCond_FirstUseEver);
		if (!ImGui::Begin("Minimap"))
		{
			ImGui::End();
			return;
		}

		int tool = static_cast<int>(_toolType);
		ImGui::RadioButton("Clear", &tool, 0); ImGui::SameLine();
		ImGui::RadioButton("Floor", &tool, 1); ImGui::SameLine();
		ImGui::RadioButton("Wall", &tool, 2);
		_toolType = static_cast<ToolType>(tool);

		int dir = static_cast<int>(_direction);
		ImGui::Text("Direction:"); ImGui::SameLine();
		ImGui::RadioButton("N", &dir, (int)Direction::North); ImGui::SameLine();
		ImGui::RadioButton("E", &dir, (int)Direction::East); ImGui::SameLine();
		ImGui::RadioButton("S", &dir, (int)Direction::South); ImGui::SameLine();
		ImGui::RadioButton("W", &dir, (int)Direction::West);
		_direction = static_cast<Direction>(dir);

		if (_toolType == ToolType::Floor)
		{
			ImGui::Separator();
			for (int i = 0; i < _tileset->GetFloorCount(); i++)
			{
				auto& tile = _tileset->GetFloor(i);
				if (i > 0) ImGui::SameLine();
				if (ImGui::ImageButton(tile.texture.Get(), ImVec2(32, 32)))
					_wallTile = i;
			}
		}
		else if (_toolType == ToolType::Wall)
		{
			ImGui::Separator();
			for (int i = 0; i < _tileset->GetWallcount(); i++)
			{
				auto& tile = _tileset->GetWall(i);
				if (i > 0) ImGui::SameLine();
				if (ImGui::ImageButton(tile.texture.Get(), ImVec2(32, 32)))
					_wallTile = i;
			}
		}

		ImGui::Separator();
		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
		ImVec2 canvas_size = ImGui::GetContentRegionAvail();

		const int tileSize = 16;

		{
			static const ImU32 colClear = ImGui::ColorConvertFloat4ToU32(ImVec4(0.4, 0.4, 0.4, 1));
			static const ImU32 colFloor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.6, 0.6, 0.6, 1));
			static const ImU32 colWall = ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1));
			static const float wallSide = 3.0f;

			auto chunk = _level->GetChunk(IntVector2::Zero);
			if (chunk != nullptr)
			{
				auto draw_list = ImGui::GetWindowDrawList();
				for (int y = 0; y < LevelChunk::COUNT; y++)
				{
					for (int x = 0; x < LevelChunk::COUNT; x++)
					{
						auto& cell = chunk->GetCell(x, LevelChunk::COUNT - y - 1);
						const ImVec2 a(
							canvas_pos.x + x * tileSize,
							canvas_pos.y + y * tileSize);
						const ImVec2 b(a.x + tileSize, a.y + tileSize);

						if (cell.IsEmpty())
						{
							draw_list->AddRectFilled(a, b, colClear);
							continue;
						}

						if (!cell.IsFloorEmpty())
							draw_list->AddRectFilled(a, b, colFloor);
						else draw_list->AddRectFilled(a, b, colClear);

						if (!cell.IsWallEmpty(Direction::North))
							draw_list->AddRectFilled(a, ImVec2(b.x, a.y + wallSide), colWall);

						if (!cell.IsWallEmpty(Direction::South))
							draw_list->AddRectFilled(ImVec2(a.x, b.y - wallSide), b, colWall);

						if (!cell.IsWallEmpty(Direction::East))
							draw_list->AddRectFilled(ImVec2(b.x - wallSide, a.y), b, colWall);

						if (!cell.IsWallEmpty(Direction::West))
							draw_list->AddRectFilled(a, ImVec2(a.x + wallSide, b.y), colWall);
					}
				}
			}
		}

		ImGui::InvisibleButton("canvas", canvas_size);
		if (ImGui::IsItemHovered() && (ImGui::IsMouseDown(0) || ImGui::IsMouseDown(1)))
		{
			const ImVec2 mouse_pos_in_canvas = ImVec2(
				ImGui::GetIO().MousePos.x - canvas_pos.x,
				ImGui::GetIO().MousePos.y - canvas_pos.y);

			const IntVector2 index(
				Math::FloorToInt(mouse_pos_in_canvas.x / tileSize),
				LevelChunk::COUNT - Math::FloorToInt(mouse_pos_in_canvas.y / tileSize) - 1);
			
			IntVector2 pos;
			auto chunk = _level->FindChunkAt(index, &pos);
			if (chunk != nullptr)
			{
				auto& cell = chunk->GetCell(pos);
				switch (_toolType)
				{
				case ToolType::Clear:
					cell.Clear();
					break;

				case ToolType::Floor:
					if (ImGui::IsMouseDown(0))
						cell.SetFloor(0);
					else cell.ClearFloor();
					break;

				case ToolType::Wall:
					if (ImGui::IsMouseDown(0))
						cell.SeWall(_direction, _wallTile);
					else cell.ClearWall(_direction);
					break;
				}
			}
		}

		ImGui::End();
	}
}