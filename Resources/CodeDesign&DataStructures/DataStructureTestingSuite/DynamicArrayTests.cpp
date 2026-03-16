#include "pch.h"
#include "CppUnitTest.h"
#include "Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DynamicTestingSuite
{
	TEST_CLASS(DynamicArrayTests)
	{
	public:
		
		TEST_METHOD(AddElement)
		{
			TArray<int> IntArray;
			IntArray.Add(1);
			IntArray.Add(2);
			IntArray.Add(3);

			TArray<float> FloatArray;
			FloatArray.Add(1.1f);
			FloatArray.Add(2.2f);
			FloatArray.Add(3.3f);

			Assert::AreEqual(IntArray[0], 1);
			Assert::AreEqual(IntArray[1], 2);
			Assert::AreEqual(IntArray[2], 3);
			Assert::AreEqual(FloatArray[0], 1.1f);
			Assert::AreEqual(FloatArray[1], 2.2f);
			Assert::AreEqual(FloatArray[2], 3.3f);
		}

		TEST_METHOD(InsertElement)
		{
			TArray<int> IntArray;
			IntArray.Insert(3, 3);

			TArray<float> FloatArray;
			FloatArray.Insert(3.3f, 3);

			Assert::AreEqual(IntArray[3], 3);
			Assert::AreEqual(FloatArray[3], 3.3f);
		}

		TEST_METHOD(GetSize)
		{
			TArray<int> AddArray;
			AddArray.Add(1);
			AddArray.Add(2);
			AddArray.Add(3);
			AddArray.Add(4);

			TArray<int> InsertArray;
			InsertArray.Insert(10, 7);

			size_t ExpectedSizeAdd = 4;
			size_t ExpectedSizeInsert = 8;

			Assert::AreEqual(AddArray.GetSize(), ExpectedSizeAdd);
			Assert::AreEqual(InsertArray.GetSize(), ExpectedSizeInsert);
		}

		TEST_METHOD(GetCapacity)
		{
			TArray<int> AddArray;
			AddArray.Add(1); // Index: 0 | Capacity: 1
			AddArray.Add(2); // Index: 1 | Capacity: 2
			AddArray.Add(3); // Index: 2 | Capacity: 4
			AddArray.Add(4); // Index: 3 | Capacity: 4 
			AddArray.Add(5); // Index: 4 | Capacity: 8

			TArray<int> InsertArray;
			InsertArray.Insert(10, 7);

			size_t ExpectedCapacityAdd = 8;
			size_t ExpectedCapacityInsert = 8;

			Assert::AreEqual(AddArray.GetCapacity(), ExpectedCapacityAdd);
			Assert::AreEqual(InsertArray.GetCapacity(), ExpectedCapacityInsert);
		}

		TEST_METHOD(IsEmpty)
		{
			TArray<int> Array;

			Assert::AreEqual(Array.GetIsEmpty(), true);

			Array.Add(97862);

			Assert::AreNotEqual(Array.GetIsEmpty(), true);
		}

		TEST_METHOD(Copy)
		{
			TArray<int> AddArray;
			AddArray.Add(1);
			AddArray.Add(2);
			AddArray.Add(3);
			AddArray.Add(4);

			TArray<int> CopyArray = AddArray;

			for (int i = 0; i < CopyArray.GetSize(); i++)
			{
				Assert::AreEqual(CopyArray[i], AddArray[i]);
			}

			CopyArray.Insert(4, 0);
			CopyArray.Insert(3, 1);
			CopyArray.Insert(2, 2);
			CopyArray.Insert(1, 3);

			for (int i = 0; i < CopyArray.GetSize(); i++)
			{
				Assert::AreNotEqual(CopyArray[i], AddArray[i]);
			}
		}

		TEST_METHOD(GetData)
		{
			TArray<int> AddArray;
			AddArray.Add(1);
			AddArray.Add(2);
			AddArray.Add(3);
			AddArray.Add(4);

			for (int i = 0; i < AddArray.GetSize(); i++)
			{
				int* ptr = AddArray.GetData();
				Assert::AreEqual(*(ptr + i), AddArray[i]);
			}
		}

		TEST_METHOD(Remove)
		{
			TArray<int> Array;
			Array.Reserve(10, true);

			for (int i = 0; i < Array.GetCapacity(); i++)
			{
				Array.Insert(i, i);
			}

			for (int i = 0; i < Array.GetSize(); i++)
			{
				Assert::AreEqual(i, Array[i]);
			}

			Array.RemoveType(3, true);

			for (int i = 0; i < Array.GetSize(); i++)
			{
				if (i >= 3)
					Assert::AreEqual(i + 1, Array[i]);
				else
					Assert::AreEqual(i, Array[i]);
			}

			Array.RemoveType(3);

			Assert::AreEqual(0, Array[0]);
			Assert::AreEqual(1, Array[1]);
			Assert::AreEqual(2, Array[2]);
			Assert::AreEqual(9, Array[3]);
			Assert::AreEqual(5, Array[4]);
			Assert::AreEqual(6, Array[5]);
			Assert::AreEqual(7, Array[6]);
			Assert::AreEqual(8, Array[7]);
		}

		TEST_METHOD(ShrinkToFit)
		{
			TArray<int> Array;
			Array.Reserve(10, true);

			for (int i = 0; i < Array.GetCapacity(); i++)
			{
				Array.Insert(i, i);
			}

			Array.RemoveType(3, true);
			Array.RemoveType(3);

			Array.ShrinkToFit();

			size_t CapacitySize = 8;

			Assert::AreEqual(Array.GetCapacity(), CapacitySize);
			Assert::AreEqual(Array.GetSize(), CapacitySize);
		}

		TEST_METHOD(Clear)
		{
			TArray<int> Array;
			Array.Reserve(10, true);

			for (int i = 0; i < Array.GetCapacity(); i++)
			{
				Array.Insert(i, i);
			}

			Array.Clear();

			Assert::AreEqual(Array.GetIsEmpty(), true);
		}
	};
}
