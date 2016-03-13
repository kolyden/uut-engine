#include "Tools.h"
#include <IMGUI/imgui.h>
#include "Tileset.h"

namespace uut
{
	Tools::Tools(Tileset* tilest)
		: _tileset(tilest)
		, _type(ToolType::Clear)
		, _direction(Direction::North)
	{
	}

	void Tools::Update()
	{
		ImGui::Begin("Tools");

		int tool = static_cast<int>(_type);
		ImGui::RadioButton("Clear", &tool, 0); ImGui::SameLine();
		ImGui::RadioButton("Floor", &tool, 1); ImGui::SameLine();
		ImGui::RadioButton("Wall", &tool, 2);
		_type = static_cast<ToolType>(tool);

		if (_type == ToolType::Wall)
		{
			int dir = static_cast<int>(_direction);
			ImGui::Text("Direction:"); ImGui::SameLine();
			ImGui::RadioButton("N", &dir, (int)Direction::North); ImGui::SameLine();
			ImGui::RadioButton("E", &dir, (int)Direction::East); ImGui::SameLine();
			ImGui::RadioButton("S", &dir, (int)Direction::South); ImGui::SameLine();
			ImGui::RadioButton("W", &dir, (int)Direction::West);
			_direction = static_cast<Direction>(dir);
		}


// 		for (int i = 0; i < _tileset->GetFloorCount(); i++)
// 		{
// 			auto& tile = _tileset->GetFloor(i);
// 			if (ImGui::ImageButton(tile.texture, ImVec2(32, 32)))
// 			{
// 				
// 			}
// 		}

		ImGui::End();
	}
}