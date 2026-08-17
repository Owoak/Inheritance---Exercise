#include "Snake.h"

Snake::Snake(const int fieldRows, const int fieldCols, const Point& startPos) :_FIELD_ROWS(fieldRows), _FIELD_COLS(fieldCols), _currPos(startPos), _snakeNodes() {
	_snakeNodes.push_back(_currPos);
}

Snake::~Snake() {}

StatusCode Snake::move(const Direction dir, const std::vector<Point>& obstacles, std::vector<Point>& powerUps) {
	switch (dir) {
	case Direction::UP:
		_currPos.row--;
		break;
	case Direction::DOWN:
		_currPos.row++;
		break;
	case Direction::LEFT:
		_currPos.col--;
		break;
	case Direction::RIGHT:
		_currPos.col++;
		break;
	}

	//borders check
	if (_currPos.row < 0 or _currPos.row >= _FIELD_ROWS or _currPos.col < 0 or _currPos.col >= _FIELD_COLS) {
		return StatusCode::SNAKE_DEAD;
	}

	//obsticle check
	for (auto it = obstacles.begin(); it != obstacles.end(); it++) {
		if (*it == _currPos) {
			return StatusCode::SNAKE_DEAD;
		}
	}

	_snakeNodes.push_front(_currPos);

	//check if we have bit ourselfs
	for (auto it = _snakeNodes.begin() + 1; it != _snakeNodes.end(); it++) {
		if (*it == _currPos) {
			return StatusCode::SNAKE_DEAD;
		}
	}

	//grow check
	for (auto it = powerUps.begin(); it != powerUps.end(); it++) {
		if (*it == _currPos) {
			powerUps.erase(it);
			return StatusCode::SNAKE_GROWING;
		}
	}

	//move update
	_snakeNodes.pop_back();
	return StatusCode::SNAKE_MOVING;
}

std::deque<Point>& Snake::getSnakeNodes() { return this->_snakeNodes; }