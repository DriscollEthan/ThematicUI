#include "pch.h"
#include "CppUnitTest.h"
#include "tracker.h"

#include "List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
* Renaming TList<T>
* =========================
*
* If you did not name your double-linked list as TList, uncomment
* the typedef below and replace the second half with your type.
*
* For example, if you created a SList<T>, it should read as follows...
*
* template<typename T>
* using TList = SList<T>
*
* If you need to do this, you can uncomment and modify the lines below:
*/

//template<typename T>
//using TList = TList<T>;

namespace aiestd_test
{
	TEST_CLASS(ListTests)
	{
		TEST_CLASS_INITIALIZE(Init)
		{
			Tracker::Reset();
		}

		// Validates that AddFront Pushes objects to the GetFront
		//
		// Also requires GetFront() for validating the value of the object
		TEST_METHOD(Push_Front_and_Front)
		{
			TList<Tracker> trackers;
			int baseCount = Tracker::Count();

			trackers.AddFront(Tracker(5));
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Did not allocate a new instance of T for storage");
			Assert::AreEqual(Tracker(5), trackers.GetFront(), L"Value at GetFront was not as expected");

			trackers.AddFront(Tracker(7));
			Assert::AreEqual(baseCount + 2, Tracker::Count(), L"Did not allocate a new instance of T for storage");
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
		}

		// Validates that objects Popped off the GetFront are destroyed
		TEST_METHOD(Pop_Front_and_Front)
		{
			TList<Tracker> trackers;
			int baseCount = Tracker::Count();
			trackers.AddFront(Tracker(5));
			trackers.RemoveFront();
			Assert::AreEqual(baseCount, Tracker::Count(), L"Value was not destroyed after being Popped");

			trackers.AddFront(Tracker(7));
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not added to the list - failed after Popping the last element prior");
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");

			trackers.AddFront(Tracker(9));
			Assert::AreEqual(baseCount + 2, Tracker::Count(), L"Value was not added to the list");
			Assert::AreEqual(Tracker(9), trackers.GetFront(), L"Value at GetFront was not as expected");

			trackers.RemoveFront();
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not destroyed after being Popped");
		}

		// Validates that AddBack Pushes objects to the GetEnd
		//
		// Also requires GetEnd() for validating the value of the object
		TEST_METHOD(Push_Back_and_Back)
		{
			TList<Tracker> trackers;
			int baseCount = Tracker::Count();

			trackers.AddBack(Tracker(5));
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Did not allocate a new instance of T for storage");
			Assert::AreEqual(Tracker(5), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			trackers.AddBack(Tracker(7));
			Assert::AreEqual(baseCount + 2, Tracker::Count(), L"Did not allocate a new instance of T for storage");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");
		}

		// Validates that objects Popped off the GetEnd are destroyed
		TEST_METHOD(Pop_Back_and_Back)
		{
			TList<Tracker> trackers;
			int baseCount = Tracker::Count();
			trackers.AddBack(Tracker(5));
			trackers.RemoveBack();
			Assert::AreEqual(baseCount, Tracker::Count(), L"Value was not destroyed after being Popped");

			trackers.AddBack(Tracker(7));
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not added to the list - failed after Popping the last element");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			trackers.AddBack(Tracker(9));
			Assert::AreEqual(baseCount + 2, Tracker::Count(), L"Value was not added to the list");
			Assert::AreEqual(Tracker(9), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			trackers.RemoveBack();
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetFront was not as expected");
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not destroyed after being Popped");
		}

		TEST_METHOD(Push_Pop_Front_Back)
		{
			TList<Tracker> trackers;
			int baseCount = Tracker::Count();

			// Pushing and Popping from GetEnd, resulting in an empty List
			trackers.AddBack(Tracker(5));
			trackers.RemoveBack();
			Assert::AreEqual(baseCount, Tracker::Count(), L"Value was not destroyed after being Popped");

			// Validate front and back with 1 element
			trackers.AddBack(Tracker(7));
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not added to the list - failed after Popping the last element");
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			// Validate front and back with 2 elements
			trackers.AddBack(Tracker(9));
			Assert::AreEqual(baseCount + 2, Tracker::Count(), L"Value was not added to the list");
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(Tracker(9), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			// Validate front and back with 1 element again
			trackers.RemoveBack();
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not destroyed after being Popped");

			// Clearing the list
			trackers.RemoveBack();
			// Ensure that all popped objects were destroyed
			Assert::AreEqual(baseCount, Tracker::Count(), L"Value was not destroyed after being Popped");

			// Pushing and Popping from GetFront
			trackers.AddFront(Tracker(5));
			trackers.RemoveFront();
			// Ensure that all popped objects were destroyed
			Assert::AreEqual(baseCount, Tracker::Count(), L"Value was not destroyed after being Popped");

			// Push 1
			trackers.AddFront(Tracker(7));
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not added to the list - failed after Popping the last element prior");
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			// Push 1 more
			trackers.AddFront(Tracker(9));
			Assert::AreEqual(baseCount + 2, Tracker::Count(), L"Value was not added to the list");
			Assert::AreEqual(Tracker(9), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");

			// Pop 1
			trackers.RemoveFront();
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value at GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value at GetEnd was not as expected");
			Assert::AreEqual(baseCount + 1, Tracker::Count(), L"Value was not destroyed after being Popped");
		}

		// copy constructor - part of rule of three
		TEST_METHOD(Copy_Constructor)
		{
			// Create a list with 1, 2, and 3
			TList<int> numbers;
			numbers.AddBack(1);
			numbers.AddBack(2);
			numbers.AddBack(3);

			// Copy it into another list
			// this is equivalent to 'TList<int> otherNumbers(numbers)';
			TList<int> otherNumbers = numbers;
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			Assert::AreEqual(3, otherNumbers.GetEnd(), L"Value at GetEnd was not as expected");

			// Pop from the copy - check both
			otherNumbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			Assert::AreEqual(2, otherNumbers.GetEnd(), L"Value at GetEnd was not as expected");

			// Pop another from the copy - check both
			otherNumbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			Assert::AreEqual(1, otherNumbers.GetEnd(), L"Value at GetEnd was not as expected");
		}

		// copy assignment - part of rule of three
		TEST_METHOD(Copy_Assignment)
		{
			// Create a list with 1, 2, and 3
			TList<int> numbers;
			numbers.AddBack(1);
			numbers.AddBack(2);
			numbers.AddBack(3);

			// Create an empty list
			TList<int> otherNumbers;
			// Copy assign to an empty list
			otherNumbers = numbers;
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected - original list should be unchanged");
			Assert::AreEqual(3, otherNumbers.GetEnd(), L"Value at GetEnd was not as expected");

			// Pop from copy - check both
			otherNumbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected - original list should be unchanged");
			Assert::AreEqual(otherNumbers.GetEnd(), 2, L"Value at GetEnd was not as expected");

			// Pop another from copy - check both
			otherNumbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected - original list should be unchanged");
			Assert::AreEqual(1, otherNumbers.GetEnd(), L"Value at GetEnd was not as expected");

			// Assigning to an existing and pre-populated list
			TList<int> existingNumbers;
			existingNumbers.AddBack(99);
			existingNumbers.AddBack(533);
			existingNumbers.AddBack(7444);
			// ^^ (above is junk data that won't persist after copy assignment)

			// Overwrite existing list of elements with copy assignment
			existingNumbers = numbers;

			// Check both
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected - original list should be unchanged");
			Assert::AreEqual(3, existingNumbers.GetEnd(), L"Value at GetEnd was not as expected");

			// Pop from copy, check both
			existingNumbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected - original list should be unchanged");
			Assert::AreEqual(existingNumbers.GetEnd(), 2, L"Value at GetEnd was not as expected");

			// Pop from copy, check both
			existingNumbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected - original list should be unchanged");
			Assert::AreEqual(1, existingNumbers.GetEnd(), L"Value at GetEnd was not as expected");
		}

		TEST_METHOD(Destructor)
		{
			int baseTrackerCount = 0;
			{
				TList<Tracker> trackers;
				baseTrackerCount = Tracker::Count();

				trackers.AddBack(Tracker(1));
				trackers.AddBack(Tracker(2));
				trackers.AddBack(Tracker(3));
				Assert::AreEqual(baseTrackerCount + 3, Tracker::Count(), L"Number of trackers constructed is mismatched");
			}
			baseTrackerCount = 0;
			Assert::AreEqual(baseTrackerCount, Tracker::Count(), L"Number of trackers constructed is mismatched");
		}

		// validating that GetFront() has an overload for const-qualified
		TEST_METHOD(Front_Const)
		{
			TList<int> numbers;
			numbers.AddFront(1);
			numbers.AddBack(2);
			numbers.AddBack(3);

			const TList<int>& numbersConst = numbers;
			Assert::AreEqual(1, numbers.GetFront(), L"Value at GetFront (const) was not as expected");
		}

		// validating that GetEnd() has an overload for const-qualified
		TEST_METHOD(Back_Const)
		{
			TList<int> numbers;
			numbers.AddFront(1);
			numbers.AddBack(2);
			numbers.AddBack(3);

			const TList<int>& numbersConst = numbers;
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd (const) was not as expected");
		}

		TEST_METHOD(RemoveByValue)
		{
			// if we remove 2s from this list...
			// 1 1 2 2 3 3
			// then we should have...
			// 1 1 3 3
			TList<int> numbers;
			numbers.AddFront(1);
			numbers.AddBack(1);
			numbers.AddBack(2);
			numbers.AddBack(2);
			numbers.AddBack(3);
			numbers.AddBack(3);

			numbers.RemoveType(2);

			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			numbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");

			numbers.RemoveBack();
			Assert::AreEqual(1, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			numbers.RemoveBack();
			Assert::AreEqual(1, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		}

		TEST_METHOD(RemoveByValue_Head)
		{
			// if we remove 1s from this list...
			// 1 1 2 2 3 3
			// then we should have...
			// 2 2 3 3
			TList<int> numbers;
			numbers.AddFront(1);
			numbers.AddBack(1);
			numbers.AddBack(2);
			numbers.AddBack(2);
			numbers.AddBack(3);
			numbers.AddBack(3);

			numbers.RemoveType(1);

			Assert::AreEqual(2, numbers.GetFront(), L"Value at GetFront as not as expected");
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd as not as expected");

			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			numbers.RemoveBack();
			Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");

			numbers.RemoveBack();
			Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			numbers.RemoveBack();
			Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");

		}

		TEST_METHOD(RemoveByValue_Tail)
		{
			// if we remove 3s from this list...
			// 1 1 2 2 3 3
			// then we should have...
			// 1 1 2 2
			TList<int> numbers;
			numbers.AddFront(1);
			numbers.AddBack(1);
			numbers.AddBack(2);
			numbers.AddBack(2);
			numbers.AddBack(3);
			numbers.AddBack(3);

			numbers.RemoveType(3);

			Assert::AreEqual(1, numbers.GetFront(), L"Value at GetFront as not as expected");
			Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd as not as expected");

			Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			numbers.RemoveBack();
			Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");

			numbers.RemoveBack();
			Assert::AreEqual(1, numbers.GetEnd(), L"Value at GetEnd was not as expected");
			numbers.RemoveBack();
			Assert::AreEqual(1, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		}

		//TEST_METHOD(RemoveByIterator)
		//{
		//	// if we remove the element [1] from this list...
		//	// 1 1 2 2 3 3
		//	// then we should have...
		//	// 1 2 2 3 3
		//	TList<int> numbers;
		//	numbers.AddFront(1);
		//	numbers.AddBack(1);
		//	numbers.AddBack(2);
		//	numbers.AddBack(2);
		//	numbers.AddBack(3);
		//	numbers.AddBack(3);
		//
		//	// Remove second element
		//	numbers.RemoveType(++numbers.begin());
		//
		//	Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//	Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//	Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::AreEqual(1, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::IsTrue(numbers.GetIsEmpty());
		//}

		//TEST_METHOD(RemoveByIterator_Duplicates)
		//{
		//	// if we remove the last element from this list...
		//	// 1 2 3 3 2 1
		//	// then we should have...
		//	// 1 2 2 3 2 
		//	TList<int> numbers;
		//	numbers.AddFront(1);
		//	numbers.AddBack(2);
		//	numbers.AddBack(3);
		//	numbers.AddBack(3);
		//	numbers.AddBack(2);
		//	numbers.AddBack(1); // position to be removed
		//
		//	// Remove last element
		//	numbers.RemoveType(--numbers.end());
		//
		//	// the 1 at the front should still be there
		//	Assert::AreEqual(1, numbers.GetFront(), L"Value at GetFront was not as expected");
		//	// the 1 at the back should be gone, leaving 2 at the back instead
		//	Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//}

		//TEST_METHOD(RemoveByIterator_Head)
		//{
		//	// if we remove the head element from this list...
		//	// 1 2 3 4 5 6
		//	// then we should have...
		//	// 2 3 4 5 6
		//	TList<int> numbers;
		//	numbers.AddFront(1);
		//	numbers.AddBack(2);
		//	numbers.AddBack(3);
		//	numbers.AddBack(4);
		//	numbers.AddBack(5);
		//	numbers.AddBack(6);
		//
		//	// Remove first element
		//	numbers.RemoveType(numbers.begin());
		//
		//	Assert::AreEqual(6, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//	Assert::AreEqual(5, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::AreEqual(4, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//	Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//}
		//
		//TEST_METHOD(RemoveByIterator_Tail)
		//{
		//	// if we remove the tail element from this list...
		//	// 1 2 3 4 5 6
		//	// then we should have...
		//	// 1 2 3 4 5
		//	TList<int> numbers;
		//	numbers.AddFront(1);
		//	numbers.AddBack(2);
		//	numbers.AddBack(3);
		//	numbers.AddBack(4);
		//	numbers.AddBack(5);
		//	numbers.AddBack(6);
		//
		//	// Remove last element
		//	numbers.RemoveType(--numbers.end());
		//
		//	Assert::AreEqual(5, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::AreEqual(4, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//	Assert::AreEqual(3, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//
		//	Assert::AreEqual(2, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//	Assert::AreEqual(1, numbers.GetEnd(), L"Value at GetEnd was not as expected");
		//	numbers.RemoveBack();
		//}

		TEST_METHOD(GetIsEmpty)
		{
			// default list should be GetIsEmpty
			TList<int> nothing;
			TList<int>& nothingRef = nothing;
			Assert::IsTrue(nothingRef.GetIsEmpty(), L"List was not GetIsEmpty");

			// list should be GetIsEmpty when you Push GetEnd and Pop GetEnd
			TList<int> clearedBack;
			clearedBack.AddBack(5);
			clearedBack.RemoveBack();
			TList<int>& clearedRefB = clearedBack;
			Assert::IsTrue(clearedRefB.GetIsEmpty(), L"List was not GetIsEmpty");

			// list should be GetIsEmpty when you Push GetFront and Pop GetFront
			TList<int> clearedFront;
			clearedFront.AddFront(5);
			clearedFront.RemoveFront();
			TList<int>& clearedRefF = clearedFront;
			Assert::IsTrue(clearedRefF.GetIsEmpty(), L"List was not GetIsEmpty");
		}

		TEST_METHOD(Clear)
		{
			// list should be clear after you Push thrice and clear
			TList<Tracker> trackers;
			int baseCount = Tracker::Count();
			trackers.AddFront(Tracker(5));
			trackers.AddFront(Tracker(7));
			trackers.AddFront(Tracker(9));

			trackers.Clear();
			Assert::IsTrue(trackers.GetIsEmpty(), L"List was not GetIsEmpty");
			Assert::AreEqual(baseCount, Tracker::Count(), L"Number of outstanding allocations was not as expected");

			// make sure the list behaves as expected after clearing

			trackers.AddBack(7);
			Assert::AreEqual(Tracker(7), trackers.GetFront(), L"Value from GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value from GetEnd was not as expected");

			trackers.AddFront(5);
			Assert::AreEqual(Tracker(5), trackers.GetFront(), L"Value from GetFront was not as expected");
			Assert::AreEqual(Tracker(7), trackers.GetEnd(), L"Value from GetEnd was not as expected");
		}

		//TEST_METHOD(Resize)
		//{
		//	TList<Tracker> fromEmpty;
		//	//fromEmpty.Resize(5);
		//
		//	// NOTE: forgot to ask students to implement a `Size` function
		//	// so this is our next best option - Pop until GetIsEmpty
		//	size_t listSize = 0;
		//	while (!fromEmpty.GetIsEmpty())
		//	{
		//		++listSize;
		//		fromEmpty.RemoveBack();
		//	}
		//	Assert::AreEqual((size_t)5, listSize, L"List did not contain the expected number of elements");
		//
		//	TList<Tracker> sizeUp;
		//	sizeUp.AddFront(1);
		//	sizeUp.AddFront(1);
		//	//sizeUp.Resize(4);
		//
		//	Assert::AreEqual(Tracker(), sizeUp.GetEnd(), L"Extra elements from resizing up don't seem to be default initialized");
		//
		//	// NOTE: forgot to ask students to implement a `Size` function
		//	// so this is our next best option - Pop until GetIsEmpty
		//	listSize = 0;
		//	while (!sizeUp.GetIsEmpty())
		//	{
		//		++listSize;
		//		sizeUp.RemoveBack();
		//	}
		//	Assert::AreEqual((size_t)4, listSize, L"List did not contain the expected number of elements");
		//
		//	TList<Tracker> sizeDown;
		//	sizeDown.AddFront(-1);
		//	sizeDown.AddFront(-1);
		//	sizeDown.AddFront(-1);
		//	sizeDown.AddFront(-1);
		//
		//	//sizeDown.Resize(2);
		//
		//
		//	// NOTE: forgot to ask students to implement a `Size` function
		//	// so this is our next best option - Pop until GetIsEmpty
		//	listSize = 0;
		//	while (!sizeDown.GetIsEmpty())
		//	{
		//		++listSize;
		//		sizeDown.RemoveBack();
		//	}
		//	Assert::AreEqual((size_t)2, listSize, L"List did not contain the expected number of elements");
		//}

		TEST_METHOD(Iterator_Begin_and_Deref)
		{
			TList<int> numbers;
			numbers.AddFront(5);
			numbers.AddBack(9);

			auto it = numbers.begin();
			Assert::AreEqual(5, *it, L"Iterator did not return the expected value at the GetFront");
		}

		TEST_METHOD(Iterator_PreIncrement)
		{
			TList<int> numbers;
			numbers.AddFront(5);
			numbers.AddBack(9);

			auto it = numbers.begin();
			Assert::AreEqual(9, *(++it), L"Iterator did not return the expected value");
		}
		//
		//TEST_METHOD(Iterator_PostIncrement)
		//{
		//	TList<int> numbers;
		//	numbers.AddFront(5);
		//	numbers.AddBack(9);
			//
		//	auto it = numbers.begin();
		//	Assert::AreEqual(5, *(it++), L"Iterator did not return the expected value");
		//	Assert::AreEqual(9, *(it), L"Iterator did not return the expected value");
		//}

		//TEST_METHOD(Iterator_PreDecrement)
		//{
		//	TList<int> numbers;
		//	numbers.AddFront(5);
		//	numbers.AddBack(9);
		//
		//	auto it = numbers.begin();
		//	++it;
		//	Assert::AreEqual(5, *(--it), L"Iterator did not return the expected value");
		//}
		//
		//TEST_METHOD(Iterator_PostDecrement)
		//{
		//	TList<int> numbers;
		//	numbers.AddFront(5);
		//	numbers.AddBack(9);
		//
		//	auto it = numbers.begin();
		//	++it;
		//	Assert::AreEqual(9, *(it--), L"Iterator did not return the expected value");
		//	Assert::AreEqual(5, *(it), L"Iterator did not return the expected value");
		//}

		TEST_METHOD(Iterator_End)
		{
			TList<int> numbers;
			numbers.AddFront(4);
			numbers.AddBack(9);

			auto it = numbers.begin();
			++it;
			++it;
			Assert::IsTrue(it == numbers.end(), L"Iterator did not return the expected value at the end");
		}

		TEST_METHOD(Iterator_End_Memory)
		{
			// tracks the number of allocations BEFORE using the list
			size_t initial = Tracker::Count();
			{
				int numbers[] = { 1,3,5,7 };
				TList<Tracker> listNumbers;
				listNumbers.AddBack(Tracker(7));
				listNumbers.AddBack(Tracker(5));
				listNumbers.AddBack(Tracker(3));
				listNumbers.AddBack(Tracker(1));

				// call end(), possibly allocating any hidden variables to wra
				listNumbers.end();
			}
			// tracks the number of allocations AFTER using the list
			size_t end = Tracker::Count();
			Assert::AreEqual(initial, end);
		}

		TEST_METHOD(Iterator_Equality)
		{
			TList<int> numbers;
			numbers.AddFront(5);
			numbers.AddBack(9);

			auto itA = numbers.begin();
			Assert::IsTrue(itA == itA, L"Iterator was not considered equal to a copy of itself");

			auto itB = numbers.begin();
			Assert::IsTrue(itA == itB, L"Iterator was not considered equal to its equivalent");
		}

		TEST_METHOD(Iterator_Inequality)
		{
			TList<int> numbers;
			numbers.AddFront(5);
			numbers.AddBack(9);

			auto itbeginA = numbers.begin();
			Assert::IsFalse(itbeginA != itbeginA, L"Iterator was not considered inequal to a copy of itself");

			auto itbeginB = numbers.begin();
			Assert::IsFalse(itbeginA != itbeginB, L"Iterator was not considered inequal to its equivalent");

			auto itend = numbers.end();
			Assert::IsTrue(itbeginA != itend, L"Iterator was not considered inequal despite being different");
		}

		TEST_METHOD(Iterator_Range_based_For)
		{
			// list of test values
			TList<int> listNumbers;
			listNumbers.AddBack(1);
			listNumbers.AddBack(3);
			listNumbers.AddBack(5);
			listNumbers.AddBack(7);

			// array of test values
			int numbers[] = { 1,3,5,7 };
			auto it = listNumbers.begin();
			// tracks the number of times the loop runs
			size_t runs = 0;
			for (auto& num : numbers)
			{
				Assert::AreEqual(num, *it);
				++it;
				++runs;
			}

			Assert::AreEqual((size_t)4, runs, L"Iteration took more/less runs than expected");
		}

		//TEST_METHOD(Insert)
		//{
		//	int numbers[] = { 1,3,5,7 };
		//
		//	TList<int> listNumbers;
		//	listNumbers.AddBack(1);
		//	listNumbers.AddBack(3);
		//	// - a five will be inserted -
		//	listNumbers.AddBack(7);
		//
		//	auto insertionIt = listNumbers.end();
		//	--insertionIt;
		//
		//	listNumbers.Insert(insertionIt, 5);
		//
		//	auto it = listNumbers.begin();
		//	for (auto& num : numbers)
		//	{
		//		Assert::AreEqual(num, *it);
		//		++it;
		//	}
		//}

		TEST_METHOD(Size)
		{
			TList<int> emptyNumbers;
			Assert::AreEqual((size_t)0, emptyNumbers.GetSize());

			TList<int> listNumbers;
			listNumbers.AddBack(1);
			listNumbers.AddBack(2);
			listNumbers.AddBack(3);
			listNumbers.AddBack(4);

			Assert::AreEqual((size_t)4, listNumbers.GetSize());

			listNumbers.RemoveBack();

			Assert::AreEqual((size_t)3, listNumbers.GetSize());
		}

		//TEST_METHOD(Sort)
		//{
		//	int numbers[] = { 1,3,5,7 };
		//	TList<int> listNumbers;
		//	listNumbers.AddBack(7);
		//	listNumbers.AddBack(5);
		//	listNumbers.AddBack(3);
		//	listNumbers.AddBack(1);
		//
		//	listNumbers.Sort();
		//
		//	for (size_t i = 0; i < 4; ++i)
		//	{
		//		Assert::AreEqual(numbers[i], listNumbers.GetFront());
		//		listNumbers.RemoveFront();
		//	}
		//}
		//
		//TEST_METHOD(Sort_Two)
		//{
		//	int numbers[] = { 1,3 };
		//	TList<int> listNumbers;
		//	listNumbers.AddBack(3);
		//	listNumbers.AddBack(1);
		//
		//	listNumbers.Sort();
		//
		//	for (size_t i = 0; i < 2; ++i)
		//	{
		//		Assert::AreEqual(numbers[i], listNumbers.GetFront());
		//		listNumbers.RemoveFront();
		//	}
		//}
		//
		//TEST_METHOD(Sort_One)
		//{
		//	int numbers[] = { 1 };
		//	TList<int> listNumbers;
		//	listNumbers.AddBack(1);
		//
		//	listNumbers.Sort();
		//
		//	for (size_t i = 0; i < 1; ++i)
		//	{
		//		Assert::AreEqual(numbers[i], listNumbers.GetFront());
		//		listNumbers.RemoveFront();
		//	}
		//}
		//
		//TEST_METHOD(Sort_None)
		//{
		//	TList<int> listNumbers;
		//	listNumbers.Sort();
		//
		//	// intentionally empty - this test should only fail if an error occurs while
		//	// sorting an empty list
		//}
	};
}
