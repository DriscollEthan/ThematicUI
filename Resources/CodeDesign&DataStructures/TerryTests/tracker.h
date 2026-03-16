#pragma once

#include <string>

#include "CppUnitTest.h"

class Tracker
{
	static int _count;

public:
	// Debug data value for ease in identifying different values
	int data;

	Tracker()
	{
		++_count;

		data = 0;
	}

	Tracker(int newData)
	{
		++_count;

		data = newData;
	}

	Tracker(const Tracker& other)
	{
		++_count;

		data = other.data;
	}

	Tracker& operator=(const Tracker& other)
	{
		// NOTE: copy-assign copies into an existing object that
		//       has already incremented the counter, so we skip
		//       it here and only copy the data

		data = other.data;

		return *this;
	}

	~Tracker()
	{
		--_count;
	}

	bool operator==(const Tracker& other) const
	{
		return data == other.data;
	}

	bool operator!=(const Tracker& other) const
	{
		return *this != other;
	}

	bool operator<(const Tracker& other) const
	{
		return data < other.data;
	}

	bool operator>(const Tracker& other) const
	{
		return data > other.data;
	}

	bool operator<=(const Tracker& other) const
	{
		return data <= other.data;
	}

	bool operator>=(const Tracker& other) const
	{
		return data >= other.data;
	}

	void static Reset()
	{
		_count = 0;
	}

	int static Count()
	{
		return _count;
	}

	bool static IsZero()
	{
		return _count == 0;
	}
};

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			// explicit template instatiation to print Tracker data for debugging
			template<> inline std::wstring ToString<Tracker>(const Tracker& t) { return std::to_wstring(t.data); }
		}
	}
}
