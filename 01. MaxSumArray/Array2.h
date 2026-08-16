#pragma once
#include <vector>
template <typename T>
class Array : public std::vector<T> {
private:
	std::vector <T> array;
public:
	Array(size_t sizeArray) { array.resize(sizeArray); }
	int getSize() const {
		return static_cast<int>(array.size());
	}
};