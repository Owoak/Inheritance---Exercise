#pragma once
#include <algorithm>
template <typename T>
class Array {
private:
	size_t arrSize;
	T* ptrArray;
public:
	class Iterator {
		T* currElemnt;
	public:
		Iterator(T* currElemnt) :currElemnt(currElemnt) {}
		T& operator*() {
			return *currElemnt;
		}
		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}
		bool operator==(const Iterator& other) const {
			if (this->currElemnt == other.currElemnt) {
				return true;
			}
			else {
				return false;
			}
		}
		Iterator& operator++() {
			++currElemnt;
			return *this;
		}
	};

	Array(size_t arrSize = 0) :arrSize(arrSize), ptrArray((arrSize != 0) ? new T[arrSize] : nullptr) {}
	~Array() { if (ptrArray != nullptr) { delete[] ptrArray; } }
	Array(const Array<T>& other) :arrSize(other.arrSize), ptrArray((arrSize != 0) ? new T[arrSize] : nullptr) {
		std::copy(other.ptrArray, other.ptrArray + other.arrSize, ptrArray);
	}
	Array& operator=(const Array<T>& other) {
		if (this == &other) {
			return *this;//same thing
		}
		arrSize = other.arrSize;
		this->clearArray();
		ptrArray = (arrSize != 0) ? new T[arrSize] : nullptr;
		std::copy(other.ptrArray, other.ptrArray + other.arrSize, ptrArray);

		return *this;
	}
	T& operator[](size_t index) {
		return *(ptrArray + index);
	}
	int getSize() const { return static_cast<int>(arrSize); }

	Iterator begin() {
		return Iterator(ptrArray);
	}
	Iterator end() {
		return Iterator(ptrArray + arrSize);
	}

private:
	void clearArray() {
		if (ptrArray != nullptr) { delete[]ptrArray; }
		ptrArray = nullptr;
	}
};