// Written by Jan Vijfhuizen
#pragma once
#include <cstdint>

namespace jv
{
	template <typename T>
	struct KeyPair
	{
		uint32_t key;
		T value;
	};
	
	// A nonlinear data container that automatically sorts values added.
	template <typename T>
	struct Heap final
	{
		KeyPair<T>* data = nullptr;
		uint32_t length = 0;
		uint32_t count = 0;

		void Insert(const T& value, uint32_t key);
		[[nodiscard]] T Peek();
		T Pop();
		void Clear();

	private:
		void HeapifyBottomToTop(uint32_t index);
		void HeapifyTopToBottom(uint32_t index);
	};

	template <typename T>
	void Heap<T>::Insert(const T& value, const uint32_t key)
	{
		assert(count < length);
		count++;

		auto& keyPair = data[count];
		keyPair.key = key;
		keyPair.value = value;
		HeapifyBottomToTop(count);
	}

	template <typename T>
	T Heap<T>::Peek()
	{
		assert(count > 0);
		const T value = data[1].value;
		return value;
	}

	template <typename T>
	T Heap<T>::Pop()
	{
		assert(count > 0);

		const T value = data[1].value;
		data[1] = data[count--];

		HeapifyTopToBottom(1);
		return value;
	}

	template <typename T>
	void Heap<T>::Clear()
	{
		count = 0;
	}

	template <typename T>
	void Heap<T>::HeapifyBottomToTop(const uint32_t index)
	{
		// Tree root found.
		if (index <= 1)
			return;

		uint32_t parentIndex = index / 2;

		// If current is smaller than the parent, swap and continue.
		if (data[index].key < data[parentIndex].key)
		{
			auto keyPair = data[index];
			data[index] = data[parentIndex];
			data[parentIndex] = keyPair;
			HeapifyBottomToTop(parentIndex);
		}
	}

	template <typename T>
	void Heap<T>::HeapifyTopToBottom(const uint32_t index)
	{
		const uint32_t left = index * 2;
		const uint32_t right = index * 2 + 1;

		// If no more nodes remain on the left side.
		if (count < left)
			return;

		// Is the left node smaller than index.
		const bool lDiff = data[index].key > data[left].key;
		// Is the right node smaller than index.
		const bool rDiff = count > left ? data[index].key > data[right].key : false;
		// Is left smaller than right.
		const bool dir = rDiff ? data[left].key > data[right].key : false;

		if (lDiff || rDiff)
		{
			const uint32_t newIndex = left + dir;

			const auto temp = data[index];
			data[index] = data[newIndex];
			data[newIndex] = temp;

			HeapifyTopToBottom(newIndex);
		}
	}
}
