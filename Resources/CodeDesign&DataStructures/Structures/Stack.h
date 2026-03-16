#pragma once

#include "Array.h"

template <typename T>
class TStack
{
private:
// Variables

  TArray<T> StackArray;
  
public:
// Constructors and Destructors

  /* Create a TStack with default values */
  TStack()
  {
    StackArray = TArray<T>();
  }

  /* Creates a TStack that is exactly equal to the provided TStack */
  TStack(const TStack& OtherStack)
  {
    StackArray = OtherStack.StackArray;
  }

  /* Creates a TStack reserving the provided number of slots for quick access and useage */
  TStack(size_t PredictedSize)
  {
    StackArray.Reserve(PredictedSize);
  }

  /* Deletes everything that has to do with the current TStack */
  ~TStack()
  {
    
  }

public:
// Get Data

  /* Get the data that is at the top of the Stack */
  T& GetTop() const
  {
    return StackArray.GetLastIndex();
  }

  /* Get the amount of elements located within the TStack */
  size_t GetSize() const
  {
    return StackArray.GetSize();
  }

  /* Get if there is no elements in the current TStack*/
  bool GetIsEmpty() const
  {
    return StackArray.GetIsEmpty();
  }

public:
// Set/Add Data

  /* Create an element with the proivded data and set it on the top of the TStack */
  void Add(const T& Value)
  {
    StackArray.Add(Value);
  }

  /* Delete the element at the top of the TStack */
  void RemoveType()
  {
    StackArray.RemoveLastIndex();
  }
};