#pragma once
#include <cassert>

template <typename T>
class TList
{
  // Helper Struct
  struct TNode
  {
  public:
  // Variables

    T Data;
    TNode* PreviousNode;
    TNode* NextNode;

  public:
    // Constructors

    /* Initializes an empty node */
    TNode()
    {
      Data = T();
      PreviousNode = nullptr;
      NextNode = nullptr;
    }

    /* Initializes a node with just a value */
    TNode(const T& Value)
    {
      Data = Value;
      PreviousNode = nullptr;
      NextNode = nullptr;
    }
    
    /* Initializes a node with a value and pointers to other nodes */
    TNode(const T& Value, TNode* Previous, TNode* Next)
    {
      Data = Value;
      PreviousNode = Previous;
      NextNode = Next;
    }
  };

private:
// Variables

  TNode* Head;
  TNode* Middle;
  TNode* Tail;
  size_t ElementSize = 0;

public:
// Constructors and Destructors

  /* Create a TList with default values */
  TList()
  {
    Head = nullptr;
    Middle = nullptr;
    Tail = nullptr;
    ElementSize = 0;
  }

  /* Sets the current TList to be equal to the provided TList */
  TList(const TList& OtherList)
  {
    if (ElementSize > 0) Clear();

    if (OtherList.Head)
    {
      Head = new TNode(OtherList.GetFront());
    }

    ElementSize = OtherList.ElementSize;

    if (ElementSize == 0) return;

    TNode* trackerNode = OtherList.Head;
    TNode* creatorNode = Head;

    while (trackerNode)
    {
      if (trackerNode->NextNode)
      {
        creatorNode->NextNode = new TNode(trackerNode->NextNode->Data);
        creatorNode->NextNode->PreviousNode = creatorNode;

        creatorNode = creatorNode->NextNode;
        trackerNode = trackerNode->NextNode;
      }
      else
      {
        Tail = creatorNode;
        creatorNode = nullptr;
        trackerNode = nullptr;
      }
    }

    // Update Middle
    size_t midPoint = ElementSize / 2;

    Middle = Head;
    for (int i = 1; i <= midPoint; i++)
    {
      Middle = Middle->NextNode;
    }

    return;
  }

  /* Deletes every node within the TList */
  ~TList()
  {
    Clear();
  }

public:
//  Operator Overrides

  TList& operator= (const TList& OtherList)
  {
    if (ElementSize > 0) Clear();

    if (OtherList.Head)
    {
      Head = new TNode(OtherList.GetFront());
    }

    ElementSize = OtherList.ElementSize;

    if (ElementSize == 0) return *this;

    TNode* trackerNode = OtherList.Head;
    TNode* creatorNode = Head;

    while (trackerNode)
    {
      if (trackerNode->NextNode)
      {
        creatorNode->NextNode = new TNode(trackerNode->NextNode->Data);
        creatorNode->NextNode->PreviousNode = creatorNode;

        creatorNode = creatorNode->NextNode;
        trackerNode = trackerNode->NextNode;
      }
      else
      {
        Tail = creatorNode;
        creatorNode = nullptr;
        trackerNode = nullptr;
      }
    }

    // Update Middle
    size_t midPoint = ElementSize / 2;

    Middle = Head;
    for (int i = 1; i <= midPoint; i++)
    {
      Middle = Middle->NextNode;
    }

    return *this;
  }

  bool operator== (const TList& Other) const
  {
    // @todo Call Equals Function
    return GetIsEqual(Other);
  }

  bool operator!= (const TList& Other) const
  {
    // @todo Call Equals Function
    return !GetIsEqual(Other);
  }

public:
// Get Data

  /* Provides the data at the start of the list */
  T& GetFront()
  {
    assert(Head != nullptr && "HeadPtr Is Null");
    return Head->Data;
  }

  /* Provides the data at the start of the list */
  T& GetFront() const
  {
    assert(Head != nullptr && "HeadPtr Is Null");
    return Head->Data;
  }

  /* Provides the data at the middle of the list */
  T& GetMiddle()
  {
    assert(Middle != nullptr && "MiddlePtr Is Null");
    return Middle->Data;
  }

  /* Provides the data at the middle of the list */
  T& GetMiddle() const
  {
    assert(Middle != nullptr && "MiddlePtr Is Null");
    return Middle->Data;
  }

  /* Provides the data at the end of the list */
  T& GetEnd()
  {
    assert(Tail != nullptr && "TailPtr Is Null");
    return Tail->Data;
  }
  
  /* Provides the data at the end of the list */
  T& GetEnd() const
  {
    assert(Tail != nullptr && "TailPtr Is Null");
    return Tail->Data;
  }

  /* Proivdes the underlying data the node that lays at the provided index */
  T& GetElementAt(const size_t Index)
  {
    assert(Middle != nullptr && "TList::GetElementAt MiddlePtr is Null");

    size_t midPoint = ElementSize / 2;

    if (midPoint == Index)
    {
      return Middle->Data;
    }
    else if (midPoint < Index)
    {
      TNode* nextNode = Middle;
      for (int i = midPoint; i != Index; i++)
      {
        assert(nextNode != nullptr && "TList::GetElementAt nextNodePtr == NULL");

        nextNode = nextNode->NextNode;
      }

      return nextNode->Data;
    }
    else if (midPoint > Index)
    {
      TNode* previousNode = Middle;
      for (int i = midPoint; i != Index; i--)
      {
        assert(previousNode != nullptr && "TList::GetElementAt previousNodePtr == NULL");

        previousNode = previousNode->PreviousNode;
      }

      return previousNode->Data;
    }
    else
    {
      assert(false && "TList::GetElementAt ...SHOULD NEVER BE HERE. WTF IS WRONG WITH IF STATEMENTS?!?!?!?!?!");
    }
  }

  /* Provides if the current TList is exactly equal to the provided TList
   * Starts at middle and checks forwards and backwards at the same time.
   */
  bool GetIsEqual(const TList& OtherList) const
  {
    if (ElementSize != OtherList.ElementSize) return false;

    TNode* firstPlusDirection = Middle;
    TNode* firstMinusDirection = Middle;

    TNode* secondPlusDirection = OtherList.Middle;
    TNode* secondMinusDirection = OtherList.Middle;

    while (firstPlusDirection || firstMinusDirection || secondPlusDirection || secondMinusDirection)
    {
      if (firstPlusDirection && secondPlusDirection)
      {
        if (firstPlusDirection->Data != secondPlusDirection->Data) return false;

        firstPlusDirection = firstPlusDirection->NextNode;

        secondPlusDirection = secondPlusDirection->NextNode;
      }
      else if (firstPlusDirection || secondPlusDirection)
      {
        return false;
      }

      if (firstMinusDirection && secondMinusDirection)
      {
        if (firstMinusDirection->Data != secondMinusDirection->Data) return false;

        firstMinusDirection = firstMinusDirection->NextNode;

        secondMinusDirection = secondMinusDirection->NextNode;
      }
      else if (firstMinusDirection || secondMinusDirection)
      {
        return false;
      }
    }

    return true;
  }

  /* Returns if there are no elements in this TList */
  bool GetIsEmpty()
  {
    return ElementSize == 0;
  }

  /* Provides how many elements are in this TList */
  size_t GetSize() const
  {
    return ElementSize;
  }

public:
// Add & Remove/Set Data

  /* Adds a node with the provided data to the very front of the TList */
  void AddFront(const T& Value)
  {
    TNode* newNode = new TNode(Value, nullptr, Head);
    if (Head) Head->PreviousNode = newNode;
    Head = newNode;
    ElementSize++;

    if (ElementSize == 1) [[unlikely]]
    {
      Tail = newNode;
      Middle = newNode;
    }

    if (ElementSize % 2 != 0)
    {
      if (Middle->PreviousNode) Middle = Middle->PreviousNode;
    }
  }

  /* Removes the very first node in the TList */
  void RemoveFront()
  {
    if (ElementSize == 0) return;

    assert(Head != nullptr && "TList::RemoveFront HeadPtr == NULL");

    TNode* tempNode = Head;
    if (Head->NextNode)
    {
      Head = tempNode->NextNode;
      Head->PreviousNode = nullptr;
    }
    else Head = nullptr;
    ElementSize--;

    delete tempNode;

    if (GetIsEmpty())
    {
      Middle = nullptr;
      Tail = nullptr;
      return;
    }

    if (ElementSize % 2 == 0)
    {
      Middle = Middle->NextNode;
    }

    if (ElementSize <= 2)
    {
      Middle->NextNode = nullptr;
    }
  }
  
  /* Adds a node with the provided data to the very end of the TList */
  void AddBack(const T& Value)
  {
    TNode* newNode = new TNode(Value, Tail, nullptr);
    if (Tail) Tail->NextNode = newNode;
    Tail = newNode;
    ElementSize++;

    if (ElementSize == 1) [[unlikely]]
    {
      Head = newNode;
      Middle = newNode;
    }

    if (ElementSize % 2 == 0)
    {
      if (Middle->NextNode) Middle = Middle->NextNode;
    }
  }

  /* Removes the very last node in the TList */
  void RemoveBack()
  {
    if (ElementSize == 0) return;
    
    assert(Tail != nullptr && "TList::RemoveBack TailPtr == NULL");

    TNode* tempNode = Tail;
    if (tempNode->PreviousNode) 
    {
      Tail = tempNode->PreviousNode;
      Tail->NextNode = nullptr;
    }
    else Tail = nullptr;
    ElementSize--;

    delete tempNode;

    if (GetIsEmpty())
    {
      Middle = nullptr;
      Head = nullptr;
      return;
    }

    if (ElementSize % 2 != 0)
    {
      Middle = Middle->PreviousNode;
    }

    if (ElementSize <= 2)
    {
      Middle = Tail;
      Middle->NextNode = nullptr;
    }
  }

  /* Removes all nodes within the TList that has the same data as provided */
  void RemoveType(const T& ValueToRemove)
  {
    if (ElementSize == 0) return;

    TNode* plusDirection = Middle;
    TNode* minusDirection = Middle;

    while (plusDirection != nullptr || minusDirection != nullptr)
    {
      TNode* tempNode;

      if (plusDirection)
      {
        tempNode = plusDirection->NextNode;

        if (plusDirection->Data == ValueToRemove)
        {
          if (tempNode) tempNode->PreviousNode = plusDirection->PreviousNode;
          plusDirection->PreviousNode->NextNode = tempNode;

          if (plusDirection == minusDirection)
          {
            minusDirection = plusDirection->PreviousNode;
          }

          if (plusDirection == Tail)
          {
            Tail = plusDirection->PreviousNode;
          }

          delete plusDirection;

          ElementSize--;
        }
        plusDirection = tempNode;
      }
      if (minusDirection)
      {
        tempNode = minusDirection->PreviousNode;

        if (minusDirection->Data == ValueToRemove)
        {
          if (tempNode) tempNode->NextNode = minusDirection->NextNode;
          minusDirection->NextNode->PreviousNode = tempNode;

          if (minusDirection == Head)
          {
            Head = minusDirection->NextNode;
          }

          delete minusDirection;

          ElementSize--;
        }
        minusDirection = tempNode;
      }
    }

    // Update Middle
    size_t midPoint = ElementSize / 2;
    for (int i = 1; i <= midPoint; i++)
    {
      Middle = Head->NextNode;
    }
  }

  /* Deletes every node from the TList and sets everything to NULL */
  void Clear()
  {
    if (ElementSize == 0) return;

    TNode* plusDirection = Middle;
    TNode* minusDirection = Middle;

    while (plusDirection || minusDirection)
    {
      TNode* tempNode = nullptr;

      if (plusDirection)
      {
        tempNode = (plusDirection->NextNode) ? plusDirection->NextNode : nullptr;

        if (plusDirection == minusDirection)
        {
          minusDirection = minusDirection->PreviousNode;
        }

        delete plusDirection;
        plusDirection = tempNode;
        ElementSize--;
      }

      if (minusDirection)
      {
        tempNode = minusDirection->PreviousNode;
        delete minusDirection;
        minusDirection = tempNode;
      }
    }

    ElementSize = 0;
    Head = nullptr;
    Middle = nullptr;
    Tail = nullptr;
  }

  class Iterator
  {
  private:
  // Variables

    TNode* CurrentNode;

  public:
  // Consructors

    Iterator()
    {
      CurrentNode = nullptr;
    }

    Iterator(TNode* StartNode)
    {
      CurrentNode = StartNode;
    }

  public:
  // Operator Overloads

    bool operator== (const Iterator& rhs) const
    {
      return CurrentNode == rhs.CurrentNode;
    }

    bool operator != (const Iterator& rhs) const
    {
      return CurrentNode != rhs.CurrentNode;
    }

    T& operator* () const
    {
      return CurrentNode->Data;
    }

    Iterator& operator++ ()
    {
      CurrentNode = CurrentNode->NextNode;
      return *this;
    }

    Iterator operator++(int)
    {
      CurrentNode = CurrentNode->NextNode;
      return *this;
    }
  };

  class ConstIterator
  {
  private:
    // Variables

    TNode* CurrentNode;

  public:
    // Consructors

    ConstIterator()
    {
      CurrentNode = nullptr;
    }

    ConstIterator(TNode* StartNode)
    {
      CurrentNode = StartNode;
    }

  public:
    // Operator Overloads

    bool operator== (const ConstIterator& rhs) const
    {
      return CurrentNode == rhs.CurrentNode;
    }

    bool operator != (const ConstIterator& rhs) const
    {
      return CurrentNode != rhs.CurrentNode;
    }

    T& operator* () const
    {
      return CurrentNode->Data;
    }

    ConstIterator& operator++ ()
    {
      CurrentNode = CurrentNode->NextNode;
      return *this;
    }

    ConstIterator operator++(int)
    {
      CurrentNode = CurrentNode->NextNode;
      return *this;
    }
  };

  Iterator begin()
  {
    Iterator It = Iterator(Head);
    return It;
  }

  Iterator end()
  {
    Iterator It = Iterator(Tail->NextNode);
    return It;
  }

  ConstIterator cbegin() const
  {
    ConstIterator It = ConstIterator(Head);
    return It;
  }

  ConstIterator cend() const
  {
    ConstIterator It = ConstIterator(Tail->NextNode);
    return It;
  }
};
