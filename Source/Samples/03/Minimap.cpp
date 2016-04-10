#include "Minimap.h"
#include <Core/Math/Math.h>
#include <IMGUI/imgui.h>
#include "EditorLevel.h"
#include "EditorLevelChunk.h"
#include "Tileset.h"

namespace uut
{
	Minimap::Minimap(EditorLevel* level)
		: _level(level)
		, _wallTile(0)
		, _toolType(ToolType::Clear)
		, _direction(Direction::North)
	{
		_tileset = _level->GetTileset();
	}

	template<typename T>
	static void EnumGroup(T& value, const List<String>& names, const List<T>& values)
	{
		int index = static_cast<int>(value);
		const uint count = values.Count();
		for (uint i = 0; i < count; i++)
		{
			ImGui::RadioButton(names[i], &index, static_cast<int>(values[i]));
			if (i < count - 1)
				ImGui::SameLine();
		}

		value = static_cast<T>(index);
	}

	void Minimap::Update()
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiSetCond_FirstUseEver);
		if (!ImGui::Begin("Minimap"))
		{
			ImGui::End();
			return;
		}

		EnumGroup(_toolType, { "Clear", "Floor", "Solid", "Wall" },
			{ ToolType::Clear, ToolType::Floor, ToolType::Solid, ToolType::Wall });

		ImGui::Text("Direction:"); ImGui::SameLine();
		EnumGroup(_direction, { "N", "E", "S", "W" },
			{ Direction::North, Direction::East, Direction::South, Direction::West });

		if (_toolType == ToolType::Floor)
		{
			ImGui::Separator();
			for (int i = 0; i < _tileset->GetFloorCount(); i++)
			{
				auto tile = _tileset->GetFloor(i);
				if (i > 0) ImGui::SameLine();
				if (ImGui::ImageButton(tile->GetTexture(), ImVec2(32, 32)))
					_wallTile = i;
			}
		}
		else if (_toolType == ToolType::Wall)
		{
			ImGui::Separator();
			for (int i = 0; i < _tileset->GetWallcount(); i++)
			{
				auto tile = _tileset->GetWall(i);
				if (i > 0) ImGui::SameLine();
				if (ImGui::ImageButton(tile->GetTexture(), ImVec2(32, 32)))
					_wallTile = i;
			}
		}

		ImGui::Separator();
		ImVec2 canvas_pos = ImGui::GetCursorScreenPos();
		ImVec2 canvas_size = ImGui::GetContentRegionAvail();

		const int tileSize = 16;

		{
			static const ImU32 colClear = ImGui::ColorConvertFloat4ToU32(ImVec4(0.4f, 0.4f, 0.4f, 1));
			static const ImU32 colFloor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.6f, 0.6f, 0.6f, 1));
			static const ImU32 colWall = ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1));
			static const ImU32 colOutline = ImGui::ColorConvertFloat4ToU32(ImVec4(0.8f, 0.8f, 0.8f, 1));
			static const ImU32 colEntity = ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1));
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

						switch (cell.type)
						{
						case CellType::Solid:
							draw_list->AddRectFilled(a, b, colClear);
							draw_list->AddRectFilled(ImVec2(a.x-1, a.y-1), ImVec2(a.x+1, a.y+1), colOutline);
							break;

						case CellType::Walls:
							if (!cell.IsFloorEmpty())
								draw_list->AddRectFilled(a, b, colFloor);

							if (!cell.IsWallEmpty(Direction::North))
								draw_list->AddRectFilled(a, ImVec2(b.x, a.y + wallSide), colWall);

							if (!cell.IsWallEmpty(Direction::South))
								draw_list->AddRectFilled(ImVec2(a.x, b.y - wallSide), b, colWall);

							if (!cell.IsWallEmpty(Direction::East))
								draw_list->AddRectFilled(ImVec2(b.x - wallSide, a.y), b, colWall);

							if (!cell.IsWallEmpty(Direction::West))
								draw_list->AddRectFilled(a, ImVec2(a.x + wallSide, b.y), colWall);
							break;
						}

						auto ent = _level->GetEntityAt(chunk->GetGlobalPos(x, LevelChunk::COUNT - y - 1));
						if (ent != nullptr)
							draw_list->AddCircle(
								ImVec2(a.x + tileSize / 2, a.y + tileSize / 2),
								(tileSize / 2)*0.8f, colEntity);
					}
				}

				for (int y = 0; y <= LevelChunk::COUNT; y++)
				{
					for (int x = 0; x <= LevelChunk::COUNT; x++)
					{
						const ImVec2 a(
							canvas_pos.x + x * tileSize,
							canvas_pos.y + y * tileSize);

						draw_list->AddRectFilled(
							ImVec2(a.x - 1, a.y - 1),
							ImVec2(a.x + 1, a.y + 1),
							colOutline);
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
			auto chunk = dynamic_cast<EditorLevelChunk*>(_level->FindChunkAt(index, &pos));
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

				case ToolType::Solid:
					if (ImGui::IsMouseDown(0))
						chunk->SetSolid(pos, 0);
					else chunk->SetWall(pos, 0);
//						cell.SetSolid(0);
					break;

				case ToolType::Wall:
					if (ImGui::IsMouseDown(0))
						cell.SetWall(_direction, _wallTile);
					else cell.ClearWall(_direction);
					break;
				}
			}
		}

		ImGui::End();
	}
}