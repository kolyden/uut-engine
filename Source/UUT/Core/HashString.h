#pragma once
#include <string>

namespace uut
{
	class HashString
	{
	public:
		HashString();

		int GetHash() const { return _hash; }

	protected:
		int _hash;
		std::string _data;
	};
}