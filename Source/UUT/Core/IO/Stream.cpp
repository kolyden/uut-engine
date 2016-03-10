#include "Stream.h"

namespace uut
{
	bool Stream::Seek(SeekMethod method, int offset)
	{
		if (!CanSeek())
			return false;

		switch (method)
		{
		case SeekMethod::Begin:
			if (offset > 0)
			{
				SetPosition(offset);
				return true;
			}
			break;

		case SeekMethod::Current:
			SetPosition(GetPosition() + offset);
			break;

		case SeekMethod::End:
			if (offset > 0)
			{
				SetPosition(GetLength() - offset);
				return true;
			}
			break;
		}

		return false;
	}
}