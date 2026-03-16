#include "pch.h"
#include "CppUnitTest.h"
#include "tracker.h"

#include "Array.h"
#include "List.h"
//#include "tbinarytree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace aiestd_test_extra
{
	TEST_CLASS(Vector_Tests)
	{
	public:
		TEST_CLASS_INITIALIZE(Init)
		{
			Tracker::Reset();
		}

		TEST_METHOD(ctor)
		{
			TArray<int> nums;
			Assert::AreEqual(nums.GetSize(), (size_t)0);
		}
		TEST_METHOD(AddBack)
		{
			TArray<Tracker> trackers;
			trackers.Add(Tracker());
			Assert::AreEqual(trackers.GetSize(), (size_t)1, L"Size did not match");
			Assert::IsTrue(trackers.GetCapacity() >= trackers.GetSize(), L"Capacity is insufficient");

			trackers.Add(Tracker());
			Assert::AreEqual(trackers.GetSize(), (size_t)2, L"Size did not match");
			Assert::IsTrue(trackers.GetCapacity() >= trackers.GetSize(), L"Capacity is insufficient");

			// TODO: test ability to expand Capacity
		}
		TEST_METHOD(Dtor)
		{
			{
				TArray<Tracker> trackers;
				trackers.Add(Tracker());

				Assert::AreEqual(trackers.GetCapacity(), (size_t)Tracker::Count(), L"Failed to store object Pushed to vector");
			}
			Assert::IsTrue(Tracker::IsZero());
		}
		TEST_METHOD(CopyCtor)
		{
			TArray<Tracker> trackersA;
			trackersA.Add(Tracker());
			trackersA.Add(Tracker());

			TArray<Tracker> trackersB;
			trackersB = trackersA;
			Assert::AreEqual(trackersB.GetSize(), (size_t)2, L"Size did not match");
		}
	};
}
