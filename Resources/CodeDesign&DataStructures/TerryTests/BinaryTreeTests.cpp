//// If needed, include your precompiled headers here:
#include "pch.h"
//#include "CppUnitTest.h"
//#include "tracker.h"
//#include "tbinarytree.h"
//
///*
//* Renaming TBinaryTree<T>
//* =========================
//*
//* If you did not name your binary tree as TBinaryTree, uncomment
//* the typedef below and replace the second half with your type.
//*
//* For example, if you created a SBinTree<T>, it should read as follows...
//*
//* template<typename T>
//* using TBinaryTree = SBinTree<T>;
//*
//* If you need to do this, you can uncomment and modify the lines below:
//*/
//
////template<typename T>
////using TBinaryTree = TBinaryTree<T>;
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace aiestd_test
//{
//	TEST_CLASS(BinaryTreeTests)
//	{
//	public:
//		TEST_CLASS_INITIALIZE(Init)
//		{
//			Tracker::Reset();
//		}
//
//		TEST_METHOD(ctor)
//		{
//			TBinaryTree<Tracker> tree;
//		}
//
//		TEST_METHOD(Dtor_empty)
//		{
//			TBinaryTree<Tracker> tree;
//		}
//
//		TEST_METHOD(Dtor_five)
//		{
//			auto starterCount = Tracker::Count();
//
//			{
//				TBinaryTree<Tracker> tree;
//				auto ctorCount = Tracker::Count();
//
//				tree.Insert(Tracker(1));
//				tree.Insert(Tracker(2));
//				tree.Insert(Tracker(3));
//				tree.Insert(Tracker(4));
//				tree.Insert(Tracker(5));
//
//				Assert::AreEqual(ctorCount + 5, Tracker::Count());
//			}
//
//			Assert::AreEqual(starterCount, Tracker::Count(), L"Count before construction and after destruction should be identical.");
//		}
//
//		TEST_METHOD(insert)
//		{
//			TBinaryTree<Tracker> tree;
//			int trackerNum = Tracker::Count();
//			tree.Insert(Tracker(4));
//			Assert::AreEqual(trackerNum + 1, Tracker::Count(), L"Incorrect number of trackers generated.");
//
//			tree.Insert(Tracker(2));
//			Assert::AreEqual(trackerNum + 2, Tracker::Count(), L"Incorrect number of trackers generated.");
//
//			tree.Insert(Tracker(6));
//			Assert::AreEqual(trackerNum + 3, Tracker::Count(), L"Incorrect number of trackers generated.");
//		}
//
//		TEST_METHOD(search_ref)
//		{
//			TBinaryTree<int> tree;
//			tree.Insert(4);
//			tree.Insert(2);
//			tree.Insert(6);
//			tree.Insert(8);
//			tree.Insert(5);
//
//			TBinaryTree<int>::Vertex* nullVertex = nullptr;
//			TBinaryTree<int>::Vertex* temp = nullptr;
//
//			tree.Search(4, temp);
//			Assert::AreEqual(4, temp->data);
//			Assert::IsNotNull(temp->left);
//			Assert::IsNotNull(temp->right);
//			Assert::AreEqual(2, temp->left->data, L"Unexpected value");
//			Assert::AreEqual(6, temp->right->data, L"Unexpected value");
//
//			tree.Search(2, temp);
//			Assert::AreEqual(2, temp->data);
//			Assert::IsNull(temp->left);
//			Assert::IsNull(temp->right);
//
//			tree.Search(6, temp);
//			Assert::AreEqual(6, temp->data);
//			Assert::IsNotNull(temp->left);
//			Assert::IsNotNull(temp->right);
//			Assert::AreEqual(5, temp->left->data, L"Unexpected value");
//			Assert::AreEqual(8, temp->right->data, L"Unexpected value");
//
//			tree.Search(8, temp);
//			Assert::AreEqual(8, temp->data);
//			Assert::IsNull(temp->left);
//			Assert::IsNull(temp->right);
//		}
//
//		TEST_METHOD(remove_noChildren)
//		{
//			// expected tree structure
//			//	 	   4
//			//     2		6
//			// 1		  5	  8
//			//                  9
//
//			TBinaryTree<int> tree;
//			tree.Insert(4);
//			tree.Insert(2);
//			tree.Insert(6);
//			tree.Insert(1);
//			tree.Insert(5);
//			tree.Insert(8);
//			tree.Insert(9);
//
//			TBinaryTree<int>::Vertex* nullVertex = nullptr;
//			TBinaryTree<int>::Vertex* temp = nullptr;
//
//			// no children (remove 5)
//			tree.Search(5, temp);
//			tree.RemoveType(temp);
//
//			tree.Search(6, temp);
//			Assert::AreEqual(6, temp->data);
//			Assert::IsNull(temp->left);
//			Assert::IsNotNull(temp->right);
//			Assert::AreEqual(8, temp->right->data, L"Unexpected value");
//		}
//
//		TEST_METHOD(remove_oneChildRight)
//		{
//			// expected tree structure
//			//	 	   4
//			//     2		6
//			// 1		  5	  8
//			//                  9
//
//			TBinaryTree<int> tree;
//			tree.Insert(4);
//			tree.Insert(2);
//			tree.Insert(6);
//			tree.Insert(1);
//			tree.Insert(5);
//			tree.Insert(8);
//			tree.Insert(9);
//
//			TBinaryTree<int>::Vertex* nullVertex = nullptr;
//			TBinaryTree<int>::Vertex* temp = nullptr;
//
//			// one child, right (remove 8)
//			tree.Search(8, temp);
//			tree.RemoveType(temp);
//
//			tree.Search(6, temp);
//			Assert::AreEqual(6, temp->data);
//			Assert::IsNotNull(temp->left);
//			Assert::IsNotNull(temp->right);
//			Assert::AreEqual(5, temp->left->data, L"Unexpected value");
//			Assert::AreEqual(9, temp->right->data, L"Unexpected value");
//
//			// check that the removed value is gone
//			tree.Search(8, temp);
//			Assert::IsNull(temp);
//		}
//
//		TEST_METHOD(remove_oneChildLeft)
//		{
//			// expected tree structure
//			//	 	   4
//			//     2		6
//			// 1		  5	  8
//			//                  9
//
//			TBinaryTree<int> tree;
//			tree.Insert(4);
//			tree.Insert(2);
//			tree.Insert(6);
//			tree.Insert(1);
//			tree.Insert(5);
//			tree.Insert(8);
//			tree.Insert(9);
//
//			TBinaryTree<int>::Vertex* nullVertex = nullptr;
//			TBinaryTree<int>::Vertex* temp = nullptr;
//
//			// one child, left (remove 2)
//			tree.Search(2, temp);
//			tree.RemoveType(temp);
//
//			tree.Search(4, temp);
//			Assert::AreEqual(4, temp->data);
//			Assert::IsNotNull(temp->left);
//			Assert::IsNotNull(temp->right);
//			Assert::AreEqual(1, temp->left->data, L"Unexpected value");
//			Assert::AreEqual(6, temp->right->data, L"Unexpected value");
//
//			// check that the removed value is gone
//			tree.Search(2, temp);
//			Assert::IsNull(temp);
//		}
//
//		TEST_METHOD(remove_twoChildren)
//		{
//			// expected tree structure
//			//	 	   4
//			//     2		6
//			// 1		  5	  8
//			//                  9
//
//			TBinaryTree<int> tree;
//			tree.Insert(4);
//			tree.Insert(2);
//			tree.Insert(6);
//			tree.Insert(1);
//			tree.Insert(5);
//			tree.Insert(8);
//			tree.Insert(9);
//
//			TBinaryTree<int>::Vertex* nullVertex = nullptr;
//			TBinaryTree<int>::Vertex* temp = nullptr;
//
//			// two children (6)
//			tree.Search(6, temp);
//			tree.RemoveType(temp);
//
//			// check that the removed value is gone
//			tree.Search(6, temp);
//			Assert::IsNull(temp);
//
//			// expected tree structure
//			//	 	   4
//			//     2		5
//			// 1		  	  8
//			//                  9
//
//			// verify that the rest of the tree is as-expected
//			tree.Search(4, temp);
//			Assert::AreEqual(4, temp->data);
//			Assert::IsNotNull(temp->left);
//			Assert::IsNotNull(temp->right);
//
//			Assert::AreEqual(2, temp->left->data, L"Unexpected value");
//			Assert::IsNotNull(temp->left->left);
//
//			Assert::AreEqual(5, temp->right->data, L"Unexpected value");
//			Assert::AreEqual(8, temp->right->right->data, L"Unexpected value");
//			Assert::AreEqual(9, temp->right->right->right->data, L"Unexpected value");
//		}
//
//		TEST_METHOD(remove_twoChildren_root)
//		{
//			// expected tree structure
//			//	 	   4
//			//     2		6
//			// 1		  5	  8
//			//                  9
//
//			TBinaryTree<int> tree;
//			tree.Insert(4);
//			tree.Insert(2);
//			tree.Insert(6);
//			tree.Insert(1);
//			tree.Insert(5);
//			tree.Insert(8);
//			tree.Insert(9);
//
//			TBinaryTree<int>::Vertex* nullVertex = nullptr;
//			TBinaryTree<int>::Vertex* temp = nullptr;
//
//			// two children, root (4)
//			tree.Search(4, temp);
//			tree.RemoveType(temp);
//
//			// check that the removed value is gone
//			tree.Search(4, temp);
//			Assert::IsNull(temp);
//
//			// expected tree structure
//			//	 	   4
//			//     2		6
//			// 1		  5	  8
//			//                  9
//
//			// verify that the rest of the tree is as-expected
//			tree.Search(2, temp);
//			Assert::IsNotNull(temp);
//			Assert::AreEqual(2, temp->data);
//			Assert::IsNotNull(temp->left);
//			Assert::AreEqual(1, temp->left->data, L"Unexpected value");
//			Assert::IsNotNull(temp->right);
//			Assert::AreEqual(6, temp->right->data, L"Unexpected value");
//		}
//	};
//}
