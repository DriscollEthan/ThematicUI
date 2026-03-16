#include "pch.h"
#include "CppUnitTest.h"
#include "Deque.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicTestingSuite
{
	TEST_CLASS(DynamicDequeTests)
	{
		TEST_METHOD(AddElementFront)
		{
			TDeque<int> Deque = TDeque<int>();

			Deque.AddFront(0);
			Deque.AddFront(1);
			Deque.AddFront(2);
			Deque.AddFront(3);
			Deque.AddFront(4);

			Assert::AreEqual(Deque.GetSize(), (size_t)5);
			Assert::AreEqual(Deque.GetFront(), 4);
		}

		TEST_METHOD(RemoveElementFront)
		{
			TDeque<int> Deque = TDeque<int>();

			Deque.AddFront(0);
			Deque.AddFront(1);
			Deque.AddFront(2);
			Deque.AddFront(3);
			Deque.AddFront(4);

			Deque.RemoveFront();

			Assert::AreEqual(Deque.GetSize(), (size_t)4);
			Assert::AreEqual(Deque.GetFront(), 3);
		}

		TEST_METHOD(AddElementBack)
		{
			TDeque<int> Deque = TDeque<int>();

			Deque.AddBack(0);
			Deque.AddBack(1);
			Deque.AddBack(2);
			Deque.AddBack(3);
			Deque.AddBack(4);

			Assert::AreEqual(Deque.GetSize(), (size_t)5);
			Assert::AreEqual(Deque.GetBack(), 4);
		}

		TEST_METHOD(RemoveElementBack)
		{
			TDeque<int> Deque = TDeque<int>();

			Deque.AddBack(0);
			Deque.AddBack(1);
			Deque.AddBack(2);
			Deque.AddBack(3);
			Deque.AddBack(4);

			Deque.RemoveBack();

			Assert::AreEqual(Deque.GetSize(), (size_t)4);
			Assert::AreEqual(Deque.GetBack(), 3);
		}
	};
}