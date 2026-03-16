#pragma once

#include "List.h"

template <typename T>
class TDeque
{
private:
// Variables

  TList<T> DequeList;

public:
// Constructors and Destructors

  /* Creates a TDeque with default values */
  TDeque()
  {
    DequeList = TList<T>();
  }

  /* Create a TDeque that is exactly equal to the provide TDeque */
  TDeque(const TDeque& OtherDeque)
  {
    DequeList = OtherDeque.DequeList;
  }

  /* Delete everything within the TDeque */
  ~TDeque()
  {
    
  }

public:
// Get Data

  /* Get the data located at the front of the TDeque */
  T& GetFront() const
  {
    return DequeList.GetEnd();
  }

  /* Get the data located at the end of the TDeque */
  T& GetBack() const
  {
    return DequeList.GetFront();
  }

  /* Get the amount of elements in the TDeque */
  size_t GetSize() const
  {
    return DequeList.GetSize();
  }

  /* Get if there is no elements in the TDeque */
  bool GetIsEmpty() const
  {
    return DequeList.GetIsEmpty();
  }

public:
// Set/Add Data

  /* Add the provided data to an element to the front of the TDeque */
  void AddFront(const T& Value)
  {
    DequeList.AddBack(Value);
  }

  /* Add the provided data to an element to the back of the TDeque */
  void AddBack(const T& Value)
  {
    DequeList.AddFront(Value);
  
  }

  /* Remove the element located at the front of the TDeque */
  void RemoveFront()
  {
    DequeList.RemoveBack();
  }

  /* Remove the element lcoated at the back of the TDeque */
  void RemoveBack()
  {
    DequeList.RemoveFront();
  }
};