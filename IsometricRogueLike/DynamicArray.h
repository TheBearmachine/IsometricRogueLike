#pragma once

template <typename T>
class DynamicArray
{
public:
	DynamicArray(T type, size_t size);
	~DynamicArray();

	T* getData() const;

private:
	T* mArray;
};

template<typename T>
inline DynamicArray<T>::DynamicArray(T type, size_t size)
{
	mArray = new T[size];
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
	delete[] mArray;
}

template<typename T>
inline T* DynamicArray<T>::getData() const
{
	return mArray;
}
