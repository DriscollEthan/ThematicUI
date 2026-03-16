#pragma once

template <typename T>
class TUniquePointer
{
  T* RawPointer;

public:
  // Consutrctors and Destructors

  TUniquePointer()
  {
    RawPointer = new T();
  }

  TUniquePointer(T& NewData)
  {
    RawPointer = new T(NewData);
  }

  TUniquePointer(const T& NewData)
  {
    RawPointer = new T(NewData);
  }

  TUniquePointer(TUniquePointer& OtherPointer) = delete;

  TUniquePointer(const TUniquePointer&& OtherPointer) = delete;

  ~TUniquePointer()
  {
    delete RawPointer;
  }

public:
  // Operators

  TUniquePointer& operator=(TUniquePointer& OtherPointer) = delete;

  TUniquePointer& operator=(const T& NewData)
  {
    delete RawPointer;
    RawPointer = new T(NewData);

    return *this;
  }

  TUniquePointer& operator=(TUniquePointer&& OtherPointer) = delete;

  T* operator->()
  {
    return RawPointer;
  }

  T& operator*()
  {
    return *RawPointer;
  }
};