#include "IndexedSet.h"
#include <algorithm>

IndexedSet::IndexedSet() :valuesSet(), valuesArray(nullptr) {}
IndexedSet::IndexedSet(const IndexedSet& other) :valuesSet(other.valuesSet), valuesArray((other.valuesArray != nullptr) ? new Value[other.size()] : nullptr) {
	if (valuesArray != nullptr) {
		std::copy(other.valuesArray, other.valuesArray + other.size(), valuesArray);
	}
}
IndexedSet& IndexedSet::operator=(const IndexedSet& other) {
	if (this == &other) {
		return *this;// redundant action
	}
	Value* tempPtr = nullptr;
	if (other.valuesArray != nullptr) {
		tempPtr = new Value[other.size()];
		std::copy(other.valuesArray, other.valuesArray + other.size(), tempPtr);
	}

	this->valuesSet = other.valuesSet;
	this->clearIndex();
	this->valuesArray = tempPtr;
	return *this;
}
void IndexedSet::add(const Value& v) {
	if (valuesSet.insert(v).second) {
		clearIndex();
	}
}
size_t IndexedSet::size() const {
	return valuesSet.size();
}
IndexedSet::~IndexedSet() {
	if (valuesArray != nullptr) {
		delete[]valuesArray;
	}
}

const Value& IndexedSet::operator[](size_t index) {
	if (valuesArray != nullptr) {
		return valuesArray[index];
	}
	else {
		buildIndex();
		return valuesArray[index];
	}
}

void IndexedSet::buildIndex() {
	valuesArray = new Value[this->size()];
	size_t index = 0;
	for (auto it = valuesSet.begin(); it != valuesSet.end(); it++, index++) {
		valuesArray[index] = *it;
	}
}
void IndexedSet::clearIndex() {
	if (valuesArray != nullptr) {
		delete[]valuesArray;
		valuesArray = nullptr;
	}
}