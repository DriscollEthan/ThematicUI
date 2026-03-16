#include "pch.h"
#include "CppUnitTest.h"
#include "Stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicTestingSuite
{
	TEST_CLASS(DynamicStackTests)
	{
		TEST_METHOD(AddElement)
		{
			TStack<int> Stack = TStack<int>(5);

			Stack.Add(0);
			Stack.Add(1);
			Stack.Add(2);
			Stack.Add(3);
			Stack.Add(4);

			Assert::AreEqual(Stack.GetSize(), (size_t)5);
			Assert::AreEqual(Stack.GetTop(), 4);
		}

		TEST_METHOD(RemoveElement)
		{
			TStack<int> Stack = TStack<int>(5);
			
			Stack.Add(0);
			Stack.Add(1);
			Stack.Add(2);
			Stack.Add(3);
			Stack.Add(4);

			Stack.RemoveType();

			Assert::AreEqual(Stack.GetSize(), (size_t)4);
			Assert::AreEqual(Stack.GetTop(), 3);
		}
	};
}