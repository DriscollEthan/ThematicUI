#pragma once

#include <cassert>

template <typename T>
class TArray
{
private:
  // Variables

  T* DynamicArray;
  size_t ElementSize = 0;
  size_t AllocatedSize = 1;
  size_t GrowthRate = 2;

public:
  // Constructors and Destructors

    /* Defaults Array to hold 1 element */
    TArray()
  {
    DynamicArray = new T[AllocatedSize];
  }

  /* Copy Constructor */
  TArray(const TArray& OtherArray)
  {
    AllocatedSize = OtherArray.AllocatedSize;
    ElementSize = OtherArray.ElementSize;
    GrowthRate = OtherArray.GrowthRate;

    T* tempArray = new T[AllocatedSize];

    for (size_t i = 0; i < ElementSize; i++)
    {
      tempArray[i] = OtherArray.DynamicArray[i];
    }

    delete[] DynamicArray;
    DynamicArray = tempArray;
  }

  /* Destructor deletes the Dynamic Array, and resets AllocatedSize and ElementSize to 0 */
  ~TArray()
  {
    delete[] DynamicArray;

    AllocatedSize = 0;
    ElementSize = 0;
  }

public:
  // Operator Overrides

  T& operator[] (size_t Index)
  {
    return GetAt(Index);
  }

  TArray& operator= (const TArray& OtherArray)
  {
    AllocatedSize = OtherArray.AllocatedSize;
    GrowthRate = OtherArray.GrowthRate;

    T* tempArray = new T[AllocatedSize];

    for (size_t i = 0; i < ElementSize; i++)
    {
      tempArray[i] = OtherArray.DynamicArray[i];
    }

    ElementSize = OtherArray.ElementSize;

    delete[] DynamicArray;
    DynamicArray = tempArray;
    
    return *this;
  }

  bool operator== (const TArray& OtherArray)
  {
    return GetIsEqual(OtherArray);
  }

public:
  // Get Data

    /* Returns a pointer to the underlying array */
  T* GetData() const
  {
    return DynamicArray;
  }

  /* Returns the element at the given index */
  T& GetAt(const size_t Index) const
  {
    assert(Index < ElementSize && "Index MUST be less than ElementSize");

    return DynamicArray[Index];
  }

  /* Returns the element at the last index */
  T& GetLastIndex() const
  {
    return DynamicArray[ElementSize - 1];
  }

  /* Returns the element at the first index */
  T& GetFirstIndex() const
  {
    return DynamicArray[0];
  }

  /* Returns the current number of elements */
  size_t GetSize() const
  {
    return ElementSize;
  }

  /* Returns the maximum number of elements we can currently store */
  size_t GetCapacity() const
  {
    return AllocatedSize;
  }

  /* Returns true if there are no elements in the array */
  bool GetIsEmpty() const
  {
    return ElementSize == 0;
  }

  /* Returns if the current array is exactly equal to the provided array */
  bool GetIsEqual(const TArray& OtherArray) const
  {
    if (ElementSize != OtherArray.ElementSize) return false;

    for (int i = 0; i < ElementSize; i++)
    {
      if (DynamicArray[i] != OtherArray.GetAt(i)) return false;
    }

    return true;
  }

public:
  // Add & Remove/Set Data

    /* Changes Default Growth Rate to anything greater than 1 */
  void SetGrowthRate(const size_t NewGrowthRate)
  {
    if (NewGrowthRate > 1) GrowthRate = NewGrowthRate;
  }

  /* Resizes the aray to be able to hold at least NewCapacity worth of elements */
  void Reserve(size_t NewCapacity, const bool bDefaultInitializeSlots = false)
  {
    if (AllocatedSize < NewCapacity)
    {
      AllocatedSize = NewCapacity;

      T* moveArray = new T[AllocatedSize];

      for (size_t i = 0; i < AllocatedSize; i++)
      {
        if (i < ElementSize)
        {
          moveArray[i] = DynamicArray[i];
        }
        else if (bDefaultInitializeSlots)
        {
          moveArray[i] = T();
        }
        else
        {
          break;
        }
      }

      delete[] DynamicArray;
      DynamicArray = moveArray;

      if (bDefaultInitializeSlots) ElementSize = AllocatedSize;
    }
  }

  /* Adds Value to end of the array. Will reallocate as needed */
  void Add(const T& Value)
  {
    ElementSize++;
    if (ElementSize > AllocatedSize)
    {
      Reserve(AllocatedSize * GrowthRate);
    }

    assert(ElementSize <= AllocatedSize && "ElementSize in Add >= AllocatedSize");

    DynamicArray[ElementSize - 1] = Value;
  }

  /* Inserts Value to specified Index. Will reallocate as needed */
  void Insert(const T& Value, const size_t Index)
  {
    if (ElementSize == Index)
    {
      Add(Value);
      return;
    }

    if (Index > ElementSize)
    {
      Resize(Index + 1);
    }

    DynamicArray[Index] = Value;

  }

  /* 
   * Removes the element at the given Index
   * Index which index to remove the element at
   * bPreserveOrder will ensure that after removing the index, will preserve the order set before removing the target index
   */
  void RemoveType(const size_t Index, const bool bPreserveOrder = false)
  {
    assert(Index < ElementSize && "Index To Remove MUST be within Array Size");


    ElementSize--;

    if (bPreserveOrder)
    {
      for (size_t i = Index; i < ElementSize; i++)
      {
        DynamicArray[i] = DynamicArray[i + 1];
      }
    }
    else
    {
      // Knowing Last Index = ElementSize in this Case
      DynamicArray[Index] = DynamicArray[ElementSize];
    }
  }

  /* Removes the element at the last index */
  void RemoveLastIndex()
  {
    ElementSize--;
  }

  /* Resizes the array to contain the given number of elements */
  void Resize(size_t NewSize)
  {
    if (NewSize > AllocatedSize)
    {
      Reserve(NewSize, true);
    }
    else
    {
      for (size_t i = ElementSize; i < NewSize; i++)
      {
        DynamicArray[ElementSize] = T();
      }

      ElementSize = NewSize;
    }
  }

  /* Resizes the array's capacity to match its size */
  void ShrinkToFit()
  {
    if (AllocatedSize != ElementSize)
    {
      T* tempArray = new T[ElementSize];

      AllocatedSize = ElementSize;

      for (size_t i = 0; i < AllocatedSize; i++)
      {
        tempArray[i] = DynamicArray[i];
      }

      delete[] DynamicArray;
      DynamicArray = tempArray;
    }
  }

  /* Empties the array, (all elements are destroyed) */
  void Clear()
  {
    AllocatedSize = 1;
    ElementSize = 0;
    delete[] DynamicArray;

    DynamicArray = new T[AllocatedSize];
  }

public:
//ITERATOR
  class Iterator
  {
  private:
  //Variables
    TArray* Array;
    size_t CurrentIndex = 0;

  public:
  // Constructors and Destructors

    Iterator()
    {
      Array = nullptr;
      CurrentIndex = 0;
    }

    Iterator(TArray* Target, size_t Start)
    {
      Array = Target;
      CurrentIndex = Start;
    }

    ~Iterator()
    {
      Array = nullptr;
      CurrentIndex = 0;
    }

  public:
  // Operators
    bool operator==(const Iterator& Rhs) const
    {
      return &Array[CurrentIndex] == &Rhs.Array[Rhs.CurrentIndex];
    }

    bool operator!=(const Iterator& Rhs) const
    {
      return &Array[CurrentIndex] != &Rhs.Array[Rhs.CurrentIndex];
    }

    Iterator& operator++()
    {
      ++CurrentIndex;
      return *this;
    }

    Iterator operator++(int)
    {
      CurrentIndex++;
      Iterator NewIterator(Array, CurrentIndex);
      return NewIterator;
    }

    T& operator*() const
    {
      return Array->GetAt(CurrentIndex);
    }
  };

public:
// Iterator Functions
  Iterator begin()
  {
    Iterator It =  Iterator(this, 0);
    return It;
  }

  Iterator end()
  {
    Iterator It = Iterator(this, ElementSize);
    return It;
  }
};