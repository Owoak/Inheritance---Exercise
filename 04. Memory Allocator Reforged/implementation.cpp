#include "Defines.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

class Comand {
protected:
	static int allocatedMemory;
	int index;
	int MemoryType;
	std::vector<MemoryNode>& memory;
	Comand(int index, int MemoryType, std::vector<MemoryNode>& memory) :index(index), MemoryType(MemoryType), memory(memory) {}
};
int Comand::allocatedMemory;

class AllocateCommand :public Comand {
public:
	AllocateCommand(int index, int MemoryType, std::vector<MemoryNode>& memory) :Comand(index, MemoryType, memory) {}
	ErrorCode tryAllocate() {
		//look for memory leak
		if (memory[Comand::index].rawMemory != nullptr) {
			return ErrorCode::MEMORY_LEAK;
		}
		memory[Comand::index].memoryType = Comand::MemoryType;
		memory[Comand::index].rawMemory = &Comand::allocatedMemory;

		return ErrorCode::EXECUTE_SUCCESS;
	}
};

class DeallocateCommand :public Comand {
public:
	DeallocateCommand(int index, int MemoryType, std::vector<MemoryNode>& memory) :Comand(index, MemoryType, memory) {}
	ErrorCode tryDeallocate() {
		//look for double free and mismatch
		if (memory[Comand::index].rawMemory == nullptr) {
			return ErrorCode::DOUBLE_FREE;
		}
		else if (memory[Comand::index].memoryType != this->Comand::MemoryType) {
			return ErrorCode::ALLOCATE_DEALLOCATE_MISMATCH;
		}

		memory[Comand::index].rawMemory = nullptr;
		memory[Comand::index].memoryType = MemoryType::UNKNOWN;

		return ErrorCode::EXECUTE_SUCCESS;
	}
};

ErrorCode executeCommand(const std::string& command, std::vector<MemoryNode>& memory) {
	std::istringstream buffer(command);
	std::string action, type; int index;
	buffer >> action >> type >> index;

	switch (action[0]) {
	case ('A'):
		switch (type[0]) {
		case 'S':
			return AllocateCommand(index, MemoryType::SINGLE, memory).tryAllocate();
			break;
		case 'M':
			return AllocateCommand(index, MemoryType::MULTIPLE, memory).tryAllocate();
			break;
		}
		break;
	case ('D'):
		switch (type[0]) {
		case 'S':
			return DeallocateCommand(index, MemoryType::SINGLE, memory).tryDeallocate();
			break;
		case 'M':
			return DeallocateCommand(index, MemoryType::MULTIPLE, memory).tryDeallocate();
			break;
		}
		break;
	}
}

void printResult(const ErrorCode errorCode, const std::string& command) {
	std::string result;
	if (errorCode == ErrorCode::EXECUTE_SUCCESS) {
		result = "success";
	}
	else if (errorCode == ErrorCode::DOUBLE_FREE) {
		result = "system crash prevented, will skip this deallocation";
	}
	else if (errorCode == ErrorCode::MEMORY_LEAK) {
		result = "memory leak prevented, will not make allocation";
	}
	else {
		result = "Warning allocate/deallocate mismatch, will skip this deallocation";
	}
	std::cout << command << " - " << result << std::endl;
}