//// If needed, include your precompiled headers here:
#include "pch.h"
//#include "CppUnitTest.h"
//#include "tracker.h"
//
//#include "TAdjacencyList.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
///*
//* Renaming TAdjacencyList<T>
//* =========================
//*
//* If you did not name your adjacency list as TList, uncomment
//* the typedef below and replace the second half with your type.
//*
//* For example, if you created a SAdjList<T>, it should read as follows...
//*
//* template<typename T>
//* using TAdjacencyList = SAdjList<T>;
//*
//* If you need to do this, you can uncomment and modify the lines below:
//*/
//
////template<typename T>
////using TAdjacencyList = TAdjacencyList<T>;
//
//#include <vector>
//
//namespace aiestd_test_extra
//{
//	TEST_CLASS(AdjListTests)
//	{
//		TEST_METHOD(AddVertex)
//		{
//			TAdjacencyList<char> letters;
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//		}
//
//		TEST_METHOD(AddLotsOfVertices)
//		{
//			TAdjacencyList<char> letters;
//			std::vector<TAdjacencyList<char>::Vertex*> nodes;
//			for (size_t i = 0; i < 100; ++i)
//			{
//				nodes.push_back(&letters.Add((char)i + 32));
//			}
//
//			// do all nodes still contain the data they're supposed to?
//			for (size_t i = 0; i < 100; ++i)
//			{
//				Assert::AreEqual((char)(i + 32), nodes[i]->data);
//			}
//		}
//
//		TEST_METHOD(RemoveVertexSolo)
//		{
//			TAdjacencyList<char> letters;
//			auto& HNode = letters.Add('H');
//			auto& eNode = letters.Add('e');
//			HNode.AddConnection(eNode);
//			Assert::AreEqual((size_t)1, HNode.ConnectionCount());
//
//			letters.RemoveType(eNode);
//			Assert::AreEqual((size_t)0, HNode.ConnectionCount());
//		}
//
//		TEST_METHOD(RemoveVertexConnected)
//		{
//			TAdjacencyList<char> letters;
//			auto& HNode = letters.Add('H');
//			auto& eNode = letters.Add('e');
//			HNode.AddConnection(eNode);
//			Assert::AreEqual((size_t)1, HNode.ConnectionCount());
//
//			letters.RemoveType(eNode);
//			Assert::AreEqual((size_t)0, HNode.ConnectionCount());
//		}
//
//		TEST_METHOD(Add_Get_Edge)
//		{
//			TAdjacencyList<char> letters;
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//
//			auto& enode = letters.Add('e');
//			Hnode.AddConnection(enode);
//			auto connectedNode = Hnode.GetConnection(0);
//			Assert::AreEqual('e', connectedNode->data);
//		}
//
//		TEST_METHOD(RemoveEdge)
//		{
//			TAdjacencyList<char> letters;
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//
//			auto& enode = letters.Add('e');
//			Hnode.AddConnection(enode);
//			Assert::IsNotNull(Hnode.GetConnection(0));
//			Hnode.RemoveConnection(enode);
//		}
//
//		TEST_METHOD(CountConnections_One)
//		{
//			TAdjacencyList<char> letters;
//
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//
//			auto& enode = letters.Add('e');
//			Hnode.AddConnection(enode);
//			Assert::AreEqual((size_t)1, Hnode.ConnectionCount());
//		}
//
//		TEST_METHOD(CountConnections_Two)
//		{
//			TAdjacencyList<char> letters;
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//
//			Hnode.AddConnection(letters.Add('e'));
//			Hnode.AddConnection(letters.Add('l'));
//			Assert::AreEqual((size_t)2, Hnode.ConnectionCount());
//		}
//
//		TEST_METHOD(CountConnections_TwoMinusOne)
//		{
//			TAdjacencyList<char> letters;
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//
//			Hnode.AddConnection(letters.Add('e'));
//			auto& lNode = letters.Add('l');
//			Hnode.AddConnection(lNode);
//			Hnode.RemoveConnection(lNode);
//			Assert::AreEqual((size_t)1, Hnode.ConnectionCount());
//		}
//
//		TEST_METHOD(CountConnections_TwoMinusTwo)
//		{
//			TAdjacencyList<char> letters;
//			auto& Hnode = letters.Add('H');
//			Assert::AreEqual('H', Hnode.data);
//
//			auto& eNode = letters.Add('e');
//			auto& lNode = letters.Add('l');
//			Hnode.AddConnection(eNode);
//			Hnode.AddConnection(lNode);
//			Hnode.RemoveConnection(eNode);
//			Hnode.RemoveConnection(lNode);
//			Assert::AreEqual((size_t)0, Hnode.ConnectionCount());
//		}
//	};
//}
