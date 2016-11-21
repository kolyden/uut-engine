#include "ContextGUI.h"
#include <Core/Plugin.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Reflection/MethodInfo.h>
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>
#include <IMGUI/imgui.h>

namespace uut
{
	void ContextGUI::Draw()
	{
		ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowCollapsed(true, ImGuiSetCond_FirstUseEver);
		if (ImGui::Begin("Context"))
		{
			GUI::Separator();
			static bool pluginFoldout = true;
			pluginFoldout = GUI::Foldout("Plugins", pluginFoldout);
			if (pluginFoldout)
			{
				GUI::BeginListBox("##plugins");
				auto plugins = Context::GetPlugins();
				for (auto& it : plugins)
					GUI::Selectable(it->ToString());
				GUI::EndListBox();
			}

			GUI::Separator();
			static bool typesFoldout = true;

			typesFoldout = GUI::Foldout("Types", typesFoldout);
			if (typesFoldout)
			{
				static const Type* current = nullptr;

				static ImGuiTextFilter filter;

				static List<const Type*> typeList;
				if (typeList.IsEmpty())
				{
					typeList = Context::GetTypes().GetValues();
					typeList.Sort([](const Type* a, const Type* b) -> int {
						return String::Compare(a->GetFullName(), b->GetFullName(), StringComparison::OrdinalIgnoreCase);
					});
				}

				filter.Draw();
				ImGui::PushItemWidth(150);
				GUI::BeginHorizontal();
				GUI::BeginListBox("##types");
				for (auto type : typeList)
				{
					const char* typeName = type->GetFullName();
					if (!filter.PassFilter(typeName))
						continue;

					GUI::BeginHorizontal();
					if (GUI::Selectable(typeName, type == current))
						current = type;
					GUI::Text(String::Format("(%d)", type->GetSize()));
					GUI::EndHorizontal();
				}
				GUI::EndListBox();
				ImGui::PopItemWidth();

				if (current != nullptr)
				{
					GUI::BeginVertical();
					GUI::Text(current->GetFullName());

					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						GUI::Text(baseType->GetFullName());

					GUI::Separator();
					DrawMembers(current, true);

					GUI::Separator();
					for (auto baseType = current->GetBaseType(); baseType != nullptr; baseType = baseType->GetBaseType())
						DrawMembers(baseType, false);
					GUI::EndVertical();
				}
				GUI::EndHorizontal();
			}
		}
		ImGui::End();
	}

	String ContextGUI::ArgTypeToString(const Type* type)
	{
		if (type == nullptr)
			return "void";

		return type->GetName();
	}

	void ContextGUI::DrawArgList(const List<const Type*>& args)
	{
		for (unsigned i = 0; i < args.Count(); i++)
		{
			GUI::BeginHorizontal();
			auto it = args[i];
			if (i > 0)
				GUI::Text(",");

			GUI::Text(it->GetName());
			GUI::EndHorizontal();
		}
	}

	void ContextGUI::DrawMembers(const Type* type, bool showCtor)
	{
		for (auto info : type->GetMembers())
		{
			GUI::BeginHorizontal();
			switch (info->GetMemberType())
			{
			case MemberType::Property:
			{
				GUI::Text(String::Format("prop: %s", info->GetName().GetData()));
				auto prop = static_cast<const IPropertyInfo*>(info);
				if (prop->IsStatic())
				{
					auto value = prop->GetValue(nullptr).Get<int>();
					GUI::Text(String::Format(" = %d", value));
				}
			}
			break;

			case MemberType::Constructor:
				if (showCtor)
				{
					GUI::Text("Constructor (");
					auto ctor = (const IConstructorInfo*)info;
					DrawArgList(ctor->GetArgsTypes());
					GUI::Text(")");
				}
				break;

			case MemberType::Method:
				{
					auto method = (const IMethodInfo*)info;
					GUI::Text(String::Format("method: %s %s(",
						ArgTypeToString(method->GetReturnType()),
						info->GetName().GetData()));
					DrawArgList(method->GetArgsTypes());
					GUI::Text(")");
				}
				break;

			case MemberType::Converter:
			{
				auto converter = (const IConverterInfo*)info;
				GUI::Text(String::Format("Convert to %s", converter->GetResultType()->GetName()));
			}
			break;

			default:
				GUI::Text(info->GetName());
			}
			GUI::EndHorizontal();
		}
	}
}