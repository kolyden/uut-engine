#pragma once
#include <Core/HashString.h>
#include <Core/Variant.h>
#include <Core/IO/Keycode.h>
#include <Core/Module.h>
#include <Core/Collections/List.h>

namespace uut
{
	enum class InputControlType
	{
		Button,
		RelativeAxis,
		AbsoluteAxis,
		Vector2,
	};

	class InputControlData
	{
	public:
		InputControlData() {}

		InputControlData(const char* name, InputControlType type)
			: _name(name), _type(type)
		{}

	protected:
		HashString _name;
		InputControlType _type;
	};

	class InputControlState
	{
	public:
	};

	//////////////////////////////////////////////////////////////////////////
	enum class InputDeviceType
	{
		Mouse,
		Keyboard,
	};

	class InputDevice : public Object
	{
		UUT_OBJECT(uut, InputDevice, Object)
	public:
		InputDevice(const HashString& name)
			: _name(name)
		{}

	protected:
		intptr_t _idetifier;
		HashString _name;
		List<InputControlData> _controls;
	};

	//////////////////////////////////////////////////////////////////////////
	class NewInputSystem : public Module
	{
		UUT_MODULE(uut, NewInputSystem, Module)
	public:

		SPtr<InputDevice> FindDevice(const Type* type)
		{
			if (type == nullptr)
				return nullptr;

			for (auto& it : _devices)
			{
				if (it->GetType()->IsDerived(type))
					return it;
			}

			return nullptr;
		}

		template<class C>
		SPtr<C> FindDevice() { return DynamicCast<C>(FindDevice(C::GetTypeStatic())); }

	protected:
		List<SPtr<InputDevice>> _devices;
	};

	//////////////////////////////////////////////////////////////////////////
	class Keyboard : public InputDevice
	{
		UUT_OBJECT(uut, Keyboard, InputDevice)
	public:
		Keyboard() : Super("Keyboard")
		{
			_controls.SetReserve(Enum<Keycode>::Count());
			for (auto& code : Enum<Keycode>::GetValues())
			{
				auto name = Enum<Keycode>::ToString(code);
				_controls.Add(InputControlData(name, InputControlType::Button));
			}
		}

		static SPtr<Keyboard> Current() { return NewInputSystem::Instance()->FindDevice<Keyboard>(); }
	};

	//////////////////////////////////////////////////////////////////////////
	class Pointer : public InputDevice
	{
		UUT_OBJECT(uut, Pointer, InputDevice)
	public:
		Pointer(const HashString& name)
			: Super(name)
		{
		}
	};

	class Mouse : public Pointer
	{
		UUT_OBJECT(uut, Mouse, Pointer)
	public:
		Mouse() : Super("Mouse")
		{
			_controls.Add(InputControlData("Left Button", InputControlType::Button));
			_controls.Add(InputControlData("Right Button", InputControlType::Button));
			_controls.Add(InputControlData("Middle Button", InputControlType::Button));

			_controls.Add(InputControlData("Position", InputControlType::Vector2));
			_controls.Add(InputControlData("Position X", InputControlType::AbsoluteAxis));
			_controls.Add(InputControlData("Position Y", InputControlType::AbsoluteAxis));

			_controls.Add(InputControlData("Delta", InputControlType::Vector2));
			_controls.Add(InputControlData("Delta X", InputControlType::RelativeAxis));
			_controls.Add(InputControlData("Delta Y", InputControlType::RelativeAxis));

			_controls.Add(InputControlData("Wheel", InputControlType::RelativeAxis));
		}

		static SPtr<Mouse> Current() { return NewInputSystem::Instance()->FindDevice<Mouse>(); }
	};
}