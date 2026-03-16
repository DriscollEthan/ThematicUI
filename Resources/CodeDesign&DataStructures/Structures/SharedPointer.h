#pragma once


template <typename T>
class TSharedPointer
{
  class TNode
  {
  public:
    T Data;
    size_t Refrences = 0;

    TNode()
    {
      Data = T();
    }

    TNode(T& NewData)
    {
      Data = NewData;
    }

    TNode(const T& NewData)
    {
      Data = NewData;
    }
    
    ~TNode()
    {

    }
  };

  TNode* Node;

public:
// Consutrctors and Destructors

  TSharedPointer()
  {
    Node = new TNode();

    Node->Refrences++;
  }

  TSharedPointer(T& NewData)
  {
    Node = new TNode(NewData);
    Node->Refrences++;
  }

  TSharedPointer(const T& NewData)
  {
    Node = new TNode(NewData);
    Node->Refrences++;
  }

  TSharedPointer(TSharedPointer& OtherPointer)
  {
    Node = OtherPointer.Node;
    Node->Refrences++;
  }

  TSharedPointer(const TSharedPointer&& OtherPointer) = delete;

  ~TSharedPointer()
  {
    Node->Refrences--;

    if (Node->Refrences == 0)
    {
      delete Node;
    }
      Node = nullptr; 
  }

public:
// Operators

  TSharedPointer& operator=(TSharedPointer& OtherPointer)
  {
    Node = OtherPointer.Node;
    Node->Refrences++;
    return *this;
  }

  TSharedPointer& operator=(const T& NewData)
  {
    if (Node)
    {
      Node->Data = NewData;
    }
    else
    {
      Node = new TNode(NewData);
      Node->Refrences++;
    }
    return *this;
  }

  TSharedPointer& operator=(TSharedPointer&& OtherPointer) = delete;

  T* operator->()
  {
    return &Node->Data;
  }

  T& operator*()
  {
    return Node->Data;
  }
};