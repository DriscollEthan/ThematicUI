#include "pch.h"
#include "CppUnitTest.h"
#include "Queue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicTestingSuite
{
	TEST_CLASS(DynamicQueueTests)
	{
		TEST_METHOD(AddElement)
		{
			TQueue<int> Queue = TQueue<int>();

			Queue.AddBack(0);
			Queue.AddBack(1);
			Queue.AddBack(2);
			Queue.AddBack(3);
			Queue.AddBack(4);

			Assert::AreEqual(Queue.GetSize(), (size_t)5);
			Assert::AreEqual(Queue.GetFront(), 0);
		}

		TEST_METHOD(RemoveElement)
		{
			TQueue<int> Queue = TQueue<int>();

			Queue.AddBack(0);
			Queue.AddBack(1);
			Queue.AddBack(2);
			Queue.AddBack(3);
			Queue.AddBack(4);

			Queue.RemoveFront();

			Assert::AreEqual(Queue.GetSize(), (size_t)4);
			Assert::AreEqual(Queue.GetFront(), 1);
		}
	};
}