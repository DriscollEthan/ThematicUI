//// If required, include your precompiled headers here:
#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "hashmap.h"
//#include <vector>
//#include <limits>
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
///*
//* Renaming THashMap<T,V>
//* =========================
//*
//* If you need to rename the type being tested, uncomment
//* the typedef below and replace the second half with your type.
//*
//* If you need to do this, you can uncomment and modify the lines below:
//*/
//
////template<typename T, typename V>
////using THashmap = SHashmap<T,V>;
//
//namespace aiestd_test_extra
//{
//	TEST_CLASS(HashmapTests)
//	{
//		TEST_METHOD(Ctor_Default)
//		{
//			THashmap<int, float> hmap;
//			// left intentionally empty to evaluate construction
//			// and destruction of an empty THashmap
//		}
//
//		TEST_METHOD(Dtor_OneElement)
//		{
//			THashmap<int, float> hmap;
//
//			hmap[5] = 5.12f;
//			// left intentionally empty to evaluate construction
//			// and destruction of a THashmap with one element
//		}
//
//		TEST_METHOD(GetSet_OneValue)
//		{
//			THashmap<int, float> hmap;
//
//			// one value to insert
//			hmap[5] = 5.05f;
//
//			// checking value of inserted
//			Assert::AreEqual(5.05f, hmap[5], L"Data retrieved was not the same as inserted.");
//		}
//
//		TEST_METHOD(GetSet_Distinct)
//		{
//			THashmap<int, char> hmap;
//
//			// five different values that should be stored separately
//			hmap[5] = 'a';
//			hmap[10] = 'b';
//			hmap[12] = 'c';
//			hmap[32] = 'd';
//			hmap[34] = 'e';
//
//			Assert::AreEqual('a', hmap[5], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('b', hmap[10], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('c', hmap[12], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('d', hmap[32], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('e', hmap[34], L"Data retrieved was not the same as inserted.");
//
//			// five more different values that should be stored separately
//			hmap[52] = 'f';
//			hmap[102] = 'g';
//			hmap[121] = 'h';
//			hmap[326] = 'i';
//			hmap[349] = 'j';
//
//			Assert::AreEqual('f', hmap[52], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('g', hmap[102], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('h', hmap[121], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('i', hmap[326], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('j', hmap[349], L"Data retrieved was not the same as inserted.");
//		}
//
//		TEST_METHOD(GetSet_Update)
//		{
//			THashmap<int, char> hmap;
//
//			hmap[5] = 'x';
//			hmap[10] = 'y';
//			hmap[12] = 'z';
//
//			Assert::AreEqual('x', hmap[5], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('y', hmap[10], L"Data retrieved was not the same as inserted.");
//			Assert::AreEqual('z', hmap[12], L"Data retrieved was not the same as inserted.");
//
//			hmap[5] = 't'; // existing value updated to 't'
//
//			Assert::AreEqual('t', hmap[5], L"Data retrieved was not the same as updated.");
//		}
//	};
//}
//