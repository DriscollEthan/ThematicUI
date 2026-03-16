#pragma once

#include "List.h"

template <typename T>
class TQueue
{
private:
// Variables

  TList<T> QueueList;

public:
// Constructors and Destructors

  /* Create a TQueue with all values set to defaults. */
  TQueue()
  {
    QueueList = TList<T>();
  }

  /* Creates a TQueue with values exactly equal to the provided TQueue */
  TQueue(const TQueue& OtherQueue)
  {
    QueueList = OtherQueue.QueueList;
  }

  /* Deletes anything that has to do with the TQueue */
  ~TQueue()
  {

  }

public:
// Get Data

  /* Get the data stored in the front of the queue */
  T& GetFront() const
  {
    return QueueList.GetEnd();
  }

  /* Get the element count in the queue */
  size_t GetSize() const
  {
    return QueueList.GetSize();
  }

  /* Get if the current que has no elements */
  bool GetIsEmpty() const
  {
    return QueueList.GetIsEmpty();
  }

public:
// Set/Add Data

  /* Adds the provided element to the back of the queue */
  void AddBack(const T& Value)
  {
    QueueList.AddFront(Value);
  }

  /* Delete the element at the very front of the queue */
  void RemoveFront()
  {
    QueueList.RemoveBack();
  }
};