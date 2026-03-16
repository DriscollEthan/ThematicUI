#pragma once

#include <functional>
#include <iostream>
#include "Array.h"

template<typename K, typename V>
class TMap
{
  class Pair
  {
  public:
    K Key;
    V Value;

    Pair()
    {

    }

    Pair(const K& k, const V& v)
    {
      Key = k;
      Value = v;
    }

    Pair(const Pair& OtherPair)
    {
      Key = OtherPair.Key;
      Value = OtherPair.Value;
    }

    Pair& operator=(const Pair& OtherPair)
    {
      Key = OtherPair.Key;
      Value = OtherPair.Value;
      return *this;
    }
  };

  TArray<Pair> PairArray;
  
public:

  TMap()
  {
    PairArray.Reserve(10, true);
  }

  TMap(const size_t Capacity)
  {
    PairArray.Reserve(Capacity, true);
  }

  TMap(const TMap& OtherMap)
  {
    PairArray = OtherMap.PairArray;
  }

  ~TMap()
  {

  }

public:

  TMap& operator= (const TMap& OtherMap)
  {
    PairArray = OtherMap.PairArray;
    return *this;
  }

  V& operator[] (const K& Key)
  {
    K key = Key;

    Pair pair = PairArray[(HashKey(key) % PairArray.GetCapacity())];

    V value = pair.Value;

    if (value == NULL || pair.Key != key)
    {
      std::cout << "NOTHING HERE" << std::endl;
      V v;
      return v;
    }

    return value;
  }

public:

  void AddValue(const K& NewKey, const V& NewValue)
  {
    size_t hashedKey = HashKey(NewKey) % PairArray.GetCapacity();
    
    Pair pair = PairArray[hashedKey];

    PairArray[hashedKey] = Pair(NewKey, NewValue);
  }

private:

  size_t HashKey(const K& KeyToHash)
  {
    std::hash<K> hashFunction;

    size_t hashValue = hashFunction(KeyToHash);

    return hashValue;
  }
};