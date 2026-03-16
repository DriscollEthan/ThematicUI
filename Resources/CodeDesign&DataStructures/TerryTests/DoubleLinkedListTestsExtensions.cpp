#include "pch.h"
#include "CppUnitTest.h"
//#include "tracker.h"
//
//#include "List.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
///*
//* Renaming TList<T>
//* =========================
//*
//* If you did not name your double-linked list as TList, uncomment
//* the typedef below and replace the second half with your type.
//*
//* For example, if you created a SList<T>, it should read as follows...
//*
//* template<typename T>
//* using TList = SList<T>
//*
//* If you need to do this, you can uncomment and modify the lines below:
//*/
//
////template<typename T>
////using TList = TList<T>;
//
//namespace aiestd_test_extensions
//{
//	TEST_CLASS(ListExtensionTests)
//	{
//		TEST_METHOD(Splice)
//		{
//			TList<int> srcList;
//			srcList.AddBack(2);
//			srcList.AddBack(4);
//			srcList.AddBack(6);
//			srcList.AddBack(8);
//
//			TList<int> dstList;
//			dstList.AddBack(1);
//			dstList.AddBack(3);
//			dstList.AddBack(5);
//			dstList.AddBack(7);
//
//			dstList.Splice(++dstList.begin(), srcList, srcList.begin());
//
//			int expectedSrcList[] = { 4,6,8 };
//			int expectedDstList[] = { 1,2,3,5,7 };
//
//			{
//				Assert::AreEqual((size_t)3, srcList.Size());
//				auto it = srcList.begin();
//				for (size_t i = 0; i < srcList.Size(); ++i)
//				{
//					Assert::AreEqual(expectedSrcList[0], *it);
//				}
//			}
//
//			{
//				Assert::AreEqual((size_t)5, dstList.Size());
//				auto it = dstList.begin();
//				for (size_t i = 0; i < dstList.Size(); ++i)
//				{
//					Assert::AreEqual(expectedDstList[0], *it);
//				}
//			}
//		}
//
//		TEST_METHOD(Splice_Self)
//		{
//			TList<int> srcList;
//			srcList.AddBack(2);
//			srcList.AddBack(4);
//			srcList.AddBack(6);
//			srcList.AddBack(8);
//			srcList.AddBack(1);
//
//			srcList.Splice(srcList.begin(), srcList, --srcList.end());
//			Assert::AreEqual((size_t)5, srcList.Size());
//
//			int expectedSrcList[] = { 1,2,4,6,8 };
//
//			Assert::AreEqual((size_t)5, srcList.Size());
//			auto it = srcList.begin();
//			for (size_t i = 0; i < srcList.Size(); ++i)
//			{
//				Assert::AreEqual(expectedSrcList[0], *it);
//			}
//		}
//
//		// -- EXTRAS --
//		TEST_METHOD(Iterator_Cast_to_ConstIt)
//		{
//			TList<int> listNumbers;
//			listNumbers.AddFront(4);
//
//			auto it = listNumbers.begin();
//			auto cIt = TList<int>::Const_Iterator(it);
//
//			Assert::IsTrue(it == cIt, L"Iterators were not equal as expected");
//		}
//	};
//}
