#include "GUI.h"
#include <ImGui/imgui.h>

namespace uut
{
	List<GUI::State> GUI::_states;

	bool GUI::Button(const String& title)
	{
		StartItem();
		const bool pressed = ImGui::Button(title);
		EndItem();

		return pressed;
	}

	bool GUI::Selectable(const String& title, bool selected)
	{
		StartItem();
		ImGui::Selectable(title, &selected);
		EndItem();
		return selected;
	}

	bool GUI::Foldout(const String& title, bool foldout)
	{
		StartItem();
		ImGui::SetNextTreeNodeOpened(foldout, ImGuiSetCond_Always);
		foldout = ImGui::CollapsingHeader(title, 0, true, false);
		EndItem();
		return foldout;
	}

	bool GUI::Toggle(const String& title, bool value)
	{
		StartItem();
		ImGui::Checkbox(title, &value);
		EndItem();
		return value;
	}

	void GUI::Text(const String& text)
	{
		StartItem();
		ImGui::Text(text);
		EndItem();
	}

	void GUI::Image(const SPtr<Texture2D>& texture, const Vector2& size)
	{
		StartItem();
		ImGui::Image(texture.Get(), ImVec2(size.x, size.y));
		EndItem();
	}

	void GUI::Separator()
	{
		ImGui::Separator();
	}

	float GUI::FloatSlider(float value, float minValue, float maxValue)
	{
		StartItem();
		bool changed = false;
		if (ImGui::SliderFloat("", &value, minValue, maxValue))
			changed = true;
		EndItem();

		return value;
	}

	void GUI::BeginHorizontal()
	{
		StartItem();

		State state;
		state.type = StateType::Horizontal;
		state.sameLine = true;
		_states << state;

		ImGui::BeginGroup();
	}

	void GUI::EndHorizontal()
	{
		if (_states.IsEmpty() || _states.Last().type != StateType::Horizontal)
			return;

		_states.RemoveAt(_states.Count() - 1);
		ImGui::EndGroup();

		EndItem();
	}

	void GUI::BeginVertical()
	{
		StartItem();

		State state;
		state.type = StateType::Vertical;
		_states << state;

		ImGui::BeginGroup();
	}

	void GUI::EndVertical()
	{
		if (_states.IsEmpty() || _states.Last().type != StateType::Vertical)
			return;

		_states.RemoveAt(_states.Count() - 1);
		ImGui::EndGroup();

		EndItem();
	}

	void GUI::BeginListBox(const String& title)
	{
		StartItem();

		State state;
		state.type = StateType::ListBox;
		_states << state;

		ImGui::ListBoxHeader(title);
	}

	void GUI::EndListBox()
	{
		if (_states.IsEmpty() || _states.Last().type != StateType::ListBox)
			return;

		_states.RemoveAt(_states.Count() - 1);
		ImGui::ListBoxFooter();

		EndItem();
	}

	void GUI::StartItem()
	{
		if (_states.IsEmpty())
			return;

		const GUI::State& last = _states.Last();
		if (last.sameLine && last.itemsCount > 0)
			ImGui::SameLine();
	}

	void GUI::EndItem()
	{
		if (_states.IsEmpty())
			return;

		_states.Last().itemsCount++;
	}
}