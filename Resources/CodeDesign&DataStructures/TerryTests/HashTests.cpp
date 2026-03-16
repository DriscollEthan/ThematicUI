//// If required, include your precompiled headers here:
#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "hash.h"
//#include <string>
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
///*
//* Renaming Hash<T>
//* =========================
//*
//* If you need to rename the type being tested, uncomment
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
////using Hash = SHash<T>;
//
//namespace aiestd_test
//{
//	TEST_CLASS(HashTests)
//	{
//		TEST_METHOD(Hash_uint32_t)
//		{
//			size_t firstHash = Hash<uint32_t>(123u);
//			size_t secondHash = Hash<uint32_t>(123u);
//
//			Assert::AreEqual(firstHash, secondHash);
//		}
//
//		TEST_METHOD(Hash_char)
//		{
//			size_t firstHash = Hash<char>('J');
//			size_t secondHash = Hash<char>('J');
//
//			Assert::AreEqual(firstHash, secondHash);
//		}
//
//		TEST_METHOD(Hash_stdstring)
//		{
//			size_t firstHash = Hash<std::string>(std::string("John Madden"));
//			size_t secondHash = Hash<std::string>(std::string("John Madden"));
//
//			Assert::AreEqual(firstHash, secondHash);
//		}
//
//		TEST_METHOD(Hash_cstring)
//		{
//			size_t firstHash = Hash("John Madden");
//			size_t secondHash = Hash("John Madden");
//
//			Assert::AreEqual(firstHash, secondHash);
//		}
//	};
//}
//