#include <iostream>
#include <vector>
#include <memory>
#include "Array.h"
#include "List.h"
#include "Stack.h"
#include "SharedPointer.h"
#include "UniquePointer.h"
#include "Map.h"

class TestingClass
{
public:
	int ID = 0;
	TArray<char> Name;

	TestingClass()
	{

	}

	TestingClass(const int id, const TArray<char>& name)
	{
		ID = id;
		Name = name;
	}
};

int main()
{
	TMap<int, char> Map;

	Map.AddValue(1, 'T');
	Map.AddValue(10, 'E');
	Map.AddValue(20, 'R');
	Map.AddValue(30, 'R');
	Map.AddValue(40, 'Y');

	std::cout << Map[1] << std::endl;
	std::cout << Map[10] << std::endl;
	std::cout << Map[20] << std::endl;
	std::cout << Map[30] << std::endl;
	std::cout << Map[40] << std::endl;

	TSharedPointer<int> PtrI;

	{
		TSharedPointer<int> IntPtr = 100;
		std::cout << *IntPtr << "\n\n";
		PtrI = IntPtr;
		TUniquePointer<int> UniPtr = 99;

		std::cout << *UniPtr << "\n\n";

		TArray<char> name;
		name.Add('E');
		name.Add('t');
		name.Add('h');
		name.Add('a');
		name.Add('n');

		TSharedPointer<TestingClass> Ethan = TestingClass(10, name);

		std::cout << Ethan->ID << Ethan->Name[0] << Ethan->Name[1] << Ethan->Name[2] << Ethan->Name[3] << Ethan->Name[4] << std::endl;

		TSharedPointer<TestingClass> Terry = Ethan;
		
		Terry->ID = 100;
		Terry->Name[0] = 'T';
		Terry->Name[1] = 'e';
		Terry->Name[2] = 'r';
		Terry->Name[3] = 'r';
		Terry->Name[4] = 'y';

		std::cout << Ethan->ID << Ethan->Name[0] << Ethan->Name[1] << Ethan->Name[2] << Ethan->Name[3] << Ethan->Name[4] << std::endl;
	}
	PtrI = 23045930;
	PtrI = 2;
	std::cout << *PtrI << "\n\n";

	{
		TArray<int> Array;
		Array.Add(1);
		Array.Add(2);
		Array.Add(3);
		Array.Add(72159);

		std::vector<int> Vect;
		Vect.push_back(1);
		Vect.push_back(2);
		Vect.push_back(3);

		for (int Int : Array)
		{
			std::cout << Int << std::endl;
		}

		Array.RemoveLastIndex();

		TArray NewArray = Array;

		for (int Int : Array)
		{
			std::cout << Int << std::endl;
		}

		for (int Int : NewArray)
		{
			std::cout << Int << std::endl;
		}

		std::cout << std::endl;

		TList<int> List;

		List.AddFront(7);
		List.AddFront(7);
		List.AddFront(7);
		List.AddFront(5);
		List.AddBack(7);
		List.AddBack(4);
		List.AddBack(7);
		List.AddBack(3);

		for (int Int : List)
		{
			std::cout << Int << std::endl;
		}
	}

	{
		TList<int> List;
		for (int i = 0; i < 9; i++)
		{
			List.AddBack(i);
		}

		TList<int> ListB;

		ListB = List;

		assert(ListB == List);
		
		std::cout << std::endl;

		for (int I : ListB)
		{
			std::cout << I << std::endl;
		}
	}

}