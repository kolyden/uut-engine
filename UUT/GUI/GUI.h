#pragma once
#include "DebugGUI.h"

namespace uut
{
	class GUI
	{
	public:
		static void Text(const String& text);
		static void Separator();

		static bool Button(const String& title);
		static bool Selectable(const String& title, bool selected = false);
		static bool Foldout(const String& title, bool foldout);
		static bool Toggle(const String& title, bool value);

		static float FloatSlider(float value, float minValue, float maxValue);

		static void BeginHorizontal();
		static void EndHorizontal();

		static void BeginVertical();
		static void EndVertical();

		static void BeginListBox(const String& title);
		static void EndListBox();

	protected:
		enum class StateType
		{
			Horizontal,
			Vertical,
			ListBox,
		};

		struct State
		{
			StateType type;
			bool sameLine = false;
			int itemsCount = 0;
		};

		static List<State> _states;

		static void StartItem();
		static void EndItem();
	};
}