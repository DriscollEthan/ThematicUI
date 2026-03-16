#include "pch.h"
#include "CppUnitTest.h"
#include "List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicTestingSuite
{
	TEST_CLASS(DynamicLinkedListTests)
	{
	public:

		TEST_METHOD(AddElement)
		{
			TList<int> List;

			List.AddFront(7);
			List.AddFront(7);
			List.AddFront(7);
			List.AddFront(5);
			List.AddBack(7);
			List.AddBack(7);
			List.AddBack(7);
			List.AddBack(3);

			Assert::AreEqual(5, List.GetFront());
			Assert::AreEqual(3, List.GetEnd());
			Assert::AreEqual(7, List.GetMiddle());
		}

		TEST_METHOD(GetElementAt)
		{
			TList<int> List;

			List.AddFront(2);
			List.AddFront(1);
			List.AddFront(0);
			List.AddFront(5);

			List.AddBack(4);
			List.AddBack(6);
			List.AddBack(7);
			List.AddBack(3);

			Assert::AreEqual(0, List.GetElementAt(1));
			Assert::AreEqual(7, List.GetElementAt(6));
			Assert::AreEqual(4, List.GetElementAt(4));
		}

		TEST_METHOD(IsEqual)
		{
			TList<int> List;

			List.AddFront(2);
			List.AddFront(1);
			List.AddFront(0);
			List.AddFront(5);

			List.AddBack(4);
			List.AddBack(6);
			List.AddBack(7);
			List.AddBack(3);

			TList<int> ListB;

			ListB.AddFront(2);
			ListB.AddFront(1);
			ListB.AddFront(0);
			ListB.AddFront(5);
			ListB.AddBack(4);
			ListB.AddBack(6);
			ListB.AddBack(7);
			ListB.AddBack(3);

			TList<int> ListC;

			ListC.AddFront(2);
			ListC.AddFront(2);
			ListC.AddFront(0);
			ListC.AddFront(5);
			ListC.AddBack(4);
			ListC.AddBack(6);
			ListC.AddBack(7);
			ListC.AddBack(5);

			TList<int> ListD;

			ListD.AddFront(2);
			ListD.AddFront(2);
			ListD.AddFront(0);
			ListD.AddFront(5);
			ListD.AddBack(4);
			ListD.AddBack(6);
			ListD.AddBack(7);

			Assert::AreEqual(true, List == ListB);
			Assert::AreEqual(true, ListB != ListC);
			Assert::AreEqual(true, List != ListC);
			Assert::AreEqual(true, ListC != ListD);
		}

		TEST_METHOD(ElementSize)
		{
			TList<int> List;

			List.AddFront(2);
			List.AddFront(1);
			List.AddFront(0);
			List.AddFront(5);

			List.AddBack(4);
			List.AddBack(6);
			List.AddBack(7);
			List.AddBack(3);

			TList<int> ListBC;
			ListBC.AddBack(10);
			ListBC.RemoveFront();
			ListBC.AddFront(10);
			ListBC.RemoveBack();

			TList<int> ListD;

			ListD.AddFront(2);
			ListD.AddFront(2);
			ListD.AddFront(0);
			ListD.AddFront(5);
			ListD.AddBack(4);
			ListD.AddBack(6);
			ListD.AddBack(7);

			Assert::AreEqual((size_t)8, List.GetSize());
			Assert::AreEqual((size_t)7, ListD.GetSize());
			Assert::AreEqual(true, ListBC.GetIsEmpty());
		}

		TEST_METHOD(RemoveFrontSemantics)
		{
			TList<int> List;

			List.AddFront(2);
			List.AddFront(1);
			List.AddFront(5);

			List.AddBack(4);
			List.AddBack(6);
			List.AddBack(7);
			List.AddBack(3);

			List.RemoveFront();

			Assert::AreEqual(1, List.GetFront());
			Assert::AreEqual(3, List.GetEnd());
			Assert::AreEqual(6, List.GetMiddle());
		}

		TEST_METHOD(RemoveBackSemantics)
		{
			TList<int> List;

			List.AddFront(2);
			List.AddFront(1);
			List.AddFront(0);
			List.AddFront(5);

			List.AddBack(4);
			List.AddBack(6);
			List.AddBack(7);
			List.AddBack(3);

			List.RemoveBack();

			Assert::AreEqual(5, List.GetFront());
			Assert::AreEqual(7, List.GetEnd());
			Assert::AreEqual(2, List.GetMiddle());
		}

		TEST_METHOD(RemoveType)
		{
			TList<int> ListA;

			ListA.AddFront(7);
			ListA.AddFront(7);
			ListA.AddFront(7);
			ListA.AddFront(5);
			ListA.AddBack(7);
			ListA.AddBack(4);
			ListA.AddBack(7);
			ListA.AddBack(3);

			ListA.RemoveType(7);

			TList<int> ListCheckA;
			ListCheckA.AddFront(5);
			ListCheckA.AddBack(4);
			ListCheckA.AddBack(3);

			Assert::AreEqual(true, ListA == ListCheckA);

			TList<int> ListB;
			ListB.AddBack(3);
			ListB.AddFront(5);
			ListB.AddBack(5);

			ListB.RemoveType(5);

			TList<int> ListCheckB;
			ListCheckB.AddFront(3);

			Assert::AreEqual(true, ListB == ListCheckB);
		}

		TEST_METHOD(ClearGuarentees)
		{
			TList<int> List;

			List.AddFront(7);
			List.AddFront(7);
			List.AddFront(7);
			List.AddFront(5);
			List.AddBack(7);
			List.AddBack(4);
			List.AddBack(7);
			List.AddBack(3);

			List.Clear();

			Assert::AreEqual(true, List.GetIsEmpty());
		}

	};
}
