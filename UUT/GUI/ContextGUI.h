#pragma once
#include "GUI.h"

namespace uut
{
	class ContextGUI
	{
	public:
		static void Draw();

	protected:
		static String ArgTypeToString(const Type * type);
		static void DrawArgList(const List<const Type*>& args);
		static void DrawMembers(const Type * type, bool showCtor);
	};
}