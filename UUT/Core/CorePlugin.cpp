#include "CorePlugin.h"
#include "Context.h"
#include "ValueType.h"
#include "IO/Stream.h"
#include "IO/FileStream.h"
#include "IO/MemoryStream.h"
#include "IO/TextReader.h"
#include "IO/Input.h"
#include "Resources/Resource.h"
#include "Resources/ResourceLoader.h"
#include "Resources/ResourceCache.h"
#include "Windows/Window.h"
#include "Attribute.h"
#include "AttributeUsage.h"
#include "Boolean.h"
#include "Char.h"
#include "Numeric.h"
#include "Single.h"
#include "Double.h"
#include "Enum.h"
#include "Engine.h"
#include "Math/Vector2.h"
#include <Core/Math/Radian.h>
#include <Core/Math/Degree.h>
#include "Debug.h"
#include "Math/Vector3.h"
#include "Math/IntVector3.h"
#include "IO/BinaryReader.h"
#include "IntPtr.h"

namespace uut
{
	CorePlugin::CorePlugin()
		: Plugin("Core", Version(0, 1))
	{
	}

	void CorePlugin::OnRegister()
	{
		// BASE
		UUT_REGISTER_OBJECT(BaseObject);
		UUT_REGISTER_OBJECT(ValueType);
		UUT_REGISTER_OBJECT(Debug);

		// FUNDAMENTAL
		UUT_REGISTER_OBJECT(Boolean);
		UUT_REGISTER_OBJECT(Char);
		UUT_REGISTER_OBJECT(Int8);
		UUT_REGISTER_OBJECT(UInt8);
		UUT_REGISTER_OBJECT(Int16);
		UUT_REGISTER_OBJECT(UInt16);
		UUT_REGISTER_OBJECT(Int32);
		UUT_REGISTER_OBJECT(UInt32);
		UUT_REGISTER_OBJECT(Int64);
		UUT_REGISTER_OBJECT(UInt64);
		UUT_REGISTER_OBJECT(Single);
		UUT_REGISTER_OBJECT(Double);
		UUT_REGISTER_OBJECT(IntPtr);

		// ENUM
		UUT_REGISTER_OBJECT(EnumValue);

		// CORE
		UUT_REGISTER_OBJECT(Object);
		UUT_REGISTER_OBJECT(Attribute);
		UUT_REGISTER_OBJECT(AttributeTargets);
		UUT_REGISTER_OBJECT(AttributeUsage);
		UUT_REGISTER_OBJECT(Engine);
		UUT_REGISTER_OBJECT(Module);

		UUT_REGISTER_OBJECT(String);

		// Math
		UUT_REGISTER_OBJECT(Degree);
		UUT_REGISTER_OBJECT(Vector2);
		UUT_REGISTER_OBJECT(IntVector2);
		UUT_REGISTER_OBJECT(Radian);
		UUT_REGISTER_OBJECT(Vector3);
		UUT_REGISTER_OBJECT(IntVector3);

		// IO
		UUT_REGISTER_OBJECT(Stream);
		UUT_REGISTER_OBJECT(FileStream);
		UUT_REGISTER_OBJECT(MemoryStream);
		UUT_REGISTER_OBJECT(TextReader);
		UUT_REGISTER_OBJECT(BinaryReader);

		UUT_REGISTER_MODULE(Input);

		// RESOURCES
		UUT_REGISTER_OBJECT(Resource);
		UUT_REGISTER_OBJECT(ResourceLoader);
		UUT_REGISTER_MODULE(ResourceCache);

		// WINDOWS
		UUT_REGISTER_OBJECT(Window);
	}

	void CorePlugin::OnUnregister()
	{
	}
}
