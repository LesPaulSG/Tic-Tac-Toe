#include "GameManager.h"
#include <iostream>
#include <math.h>
#include "definitions.h"

GameManager::GameManager(int n) : fieldNum(n) {
	this->field = std::vector<std::vector<char>>(n, std::vector<char>(n, 0));
	for (int i = 0; i < n-1; ++i) {
		RectangleShape v, h;									//temp shapes for visual grid
		v.setSize(Vector2f(3, n * FIELD_SIZE));
		v.setPosition(Vector2f(((i + 1) * FIELD_SIZE) + 5, 5));
		v.setFillColor(Color::Green);
		h.setSize(Vector2f(3, n * FIELD_SIZE));
		h.setPosition(Vector2f(5, ((i + 1) * FIELD_SIZE) + 5));
		h.setFillColor(Color::Green);
		h.setRotation(270);
		this->fieldVis.push_back(v);
		this->fieldVis.push_back(h);
	}
}

GameManager::~GameManager(){
	
}

int GameManager::GetFieldsNum(){
	return this->fieldNum;
}

std::vector<std::vector<char>>* GameManager::GetField(){
	return &this->field;
}

std::vector<RectangleShape>* GameManager::GetFieldVis(){
	return &this->fieldVis;
}

std::vector<RectangleShape>* GameManager::GetTics(){
	return &this->tics;
}

std::vector<CircleShape>* GameManager::GetTacs(){
	return &this->tacs;
}

bool GameManager::SetFieldSpot(char c, Vector2i pos){
	int x = pos.x;
	int y = pos.y;

	if (x < 0) {
		std::cout << " not in range " << std::endl;
		return false;
	}

	if (this->field[x][y] == 0) {														//is spot free
		this->field[x][y] = c;
		if (c == 'x') {
			RectangleShape f, s;														//shapes for draw X
			f.setPosition(Vector2f(x * FIELD_SIZE + 10, y * FIELD_SIZE + 9));			//imagine constants need to correct position
			s.setPosition(Vector2f((x * FIELD_SIZE) + FIELD_SIZE, y * FIELD_SIZE + 7));
			f.setSize(Vector2f(3, FIELD_SIZE + 6));										//imagine constants need to correct size
			s.setSize(Vector2f(3, FIELD_SIZE + 6));
			f.setRotation(315);
			s.setRotation(45);
			f.setFillColor(Color::Red);
			s.setFillColor(Color::Red);
			this->tics.push_back(f);
			this->tics.push_back(s);
		} else if (c == 'o') {
			CircleShape s;																//shape for draw O
			s.setPosition(Vector2f(x * FIELD_SIZE + 12, y * FIELD_SIZE + 9));			//imagine constants need to correct position
			s.setRadius(FIELD_SIZE/2.5);
			s.setOutlineColor(Color::Cyan);
			s.setFillColor(Color::Black);
			s.setOutlineThickness(3);
			this->tacs.push_back(s);
		}
		return true;
	}	
	return false;
}

bool GameManager::CheckVictory(char c){
	int num = 0;							//number of c in row
	int i, j;								//for loops

	for (i = 0; i < this->fieldNum; ++i) {												//check columns
		j = 0;
		while (this->field[i][j] == c){
			++num;
			++j;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, this->fieldNum * FIELD_SIZE));					//size 3x(gridSize*spotSize)
				line.setPosition(Vector2f(((i * FIELD_SIZE) + FIELD_SIZE / 2 + 5), 5)); //position is i*spotSize + spotSize/2 + 5 for line width
				line.setFillColor(Color::Yellow);
				this->fieldVis.push_back(line);
				winLineDrawn = true;
				return true;
			}
		}
		num = 0;
	}
	for (i = 0; i < this->fieldNum; ++i) {												//check rows
		j = 0;
		while (this->field[j][i] == c) {
			++num;
			++j;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, this->fieldNum * FIELD_SIZE));					//size 3x(gridSize*spotSize)
				line.setPosition(Vector2f(5, ((i * FIELD_SIZE) + FIELD_SIZE / 2 + 5)));	//position is i*spotSize + spotSize/2 + 5 for line width
				line.setFillColor(Color::Yellow);
				line.setRotation(270);
				this->fieldVis.push_back(line);
				winLineDrawn = true;
				return true;
			}
		}
		num = 0;
	}
	num = 0;
	for (int i = 0; i < this->fieldNum; ++i) {											//check diagonal
		if (this->field[i][i] == c) {
			++num;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, (this->fieldNum * FIELD_SIZE)*std::sqrt(2)));	//square diagonal
				line.setPosition(Vector2f(5, 5));
				line.setFillColor(Color::Yellow);
				line.setRotation(315);
				this->fieldVis.push_back(line);
				winLineDrawn = true;
				return true;
			}
		}
	}
	num = 0;
	for (int i = 0; i < this->fieldNum; ++i) {											//check reverse diagonal
		if (this->field[i][this->fieldNum-i-1] == c) {
			++num;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, (this->fieldNum * FIELD_SIZE) * std::sqrt(2)));//square diagonal
				line.setPosition(Vector2f(this->fieldNum * FIELD_SIZE, 5));
				line.setFillColor(Color::Yellow);
				line.setRotation(45);
				this->fieldVis.push_back(line);
				winLineDrawn = true;
				return true;
			}
		}
	}
	return false;
}

bool GameManager::CheckVictoryMM(char c){						//same func for minimax algorythm without drawing line
	int num = 0;
	int i, j;
	for (i = 0; i < this->fieldNum; ++i) {
		j = 0;
		while (this->field[i][j] == c) {
			++num;
			++j;
			if (num == this->fieldNum) {
				return true;
			}
		}
		num = 0;
	}
	for (i = 0; i < this->fieldNum; ++i) {
		j = 0;
		while (this->field[j][i] == c) {
			++num;
			++j;
			if (num == this->fieldNum) {
				return true;
			}
		}
		num = 0;
	}
	for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][i] == c) {
			++num;
			if (num == this->fieldNum) {
				return true;
			}
		}
	}
	num = 0;
	for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][this->fieldNum - i - 1] == c) {
			++num;
			if (num == this->fieldNum) {
				return true;
			}
		}
	}
	return false;
}

bool GameManager::isFreeSpot(){							//if there is free spot
	for (int i = 0; i < this->fieldNum; ++i) {
		for (int j = 0; j < this->fieldNum; ++j) {
			if (this->field[i][j] == 0) {
				return true;
			}
		}
	}
	return false;
}

int GameManager::FreeSteps(){							//returns count of free spots
	int count = 0;
	for (int i = 0; i < this->fieldNum; ++i) {
		for (int j = 0; j < this->fieldNum; ++j) {
			if (this->field[i][j] == 0) {
				++count;
			}
		}
	}
	return count;
}

void GameManager::ClearField(){							//clears field for new game
	if (winLineDrawn) {
		this->fieldVis.pop_back();
	}
	this->tics.clear();
	this->tacs.clear();
	this->field = std::vector<std::vector<char>>(fieldNum, std::vector<char>(fieldNum, 0));	
}

void GameManager::AiMove(char c){
	int score = 0, maxS = -100;
	Vector2i move;

	if (this->FreeSteps() > 10) {						//if too many free spots makes random move
		this->RandomMove(c);
		return;
	}

	for (int i = 0; i < this->fieldNum; ++i) {
		for (int j = 0; j < this->fieldNum; ++j) {
			if (this->field[i][j] == 0) {
				this->field[i][j] = c;
				score = this->minimax(0, -100, 100, c, false);
				this->field[i][j] = 0;
				if (score > maxS) {
					maxS = score;
					move.x = i;
					move.y = j;
				}
			}
		}
	}
	this->SetFieldSpot(c, move);
}

void GameManager::RandomMove(char c){					//random move
	Vector2i res;
	srand(time(0));
	res.x = rand() % (this->fieldNum) + 0;
	res.y = rand() % (this->fieldNum) + 0;
	while (!this->SetFieldSpot(c, res)) {				//try until move fits
		res.x = rand() % (this->fieldNum) + 0;
		res.y = rand() % (this->fieldNum) + 0;
	}
}

int GameManager::minimax(int depth, int alpha, int beta, char c, bool isMax){
	int score, bestScore;
	static char enemy;

	if (depth > this->MAX_DEPTH) {						//return if max depth reached
		return 0;
	}

	if (c == 'x') {										//set enemy's symbol
		enemy = 'o';
	} else if (c == 'o') {
		enemy = 'x';
	}

	if (this->CheckVictoryMM(c)) {						//check win
		return 10;
	} else if (this->CheckVictoryMM(enemy)) {			//check lose
		return -10;
	} else if (!this->isFreeSpot()) {					//check draw
		return 0;
	}

	if (isMax) {										//maximazing
		bestScore = -100;
		for (int i = 0; i < this->fieldNum; ++i) {
			for (int j = 0; j < this->fieldNum; ++j) {
				if (this->field[i][j] == 0) {
					this->field[i][j] = c;
					score = minimax(depth + 1, alpha, beta, c, false);
					bestScore = std::max(bestScore, score);
					alpha = std::max(alpha, score);
					if (beta <= alpha) {
						this->field[i][j] = 0;
						break;
					}
					this->field[i][j] = 0;
				}
			}
		}
		return bestScore;
	} else {											//minimazing
		bestScore = 100;
		for (int i = 0; i < this->fieldNum; ++i) {
			for (int j = 0; j < this->fieldNum; ++j) {
				if (this->field[i][j] == 0) {
					this->field[i][j] = enemy;
					score = minimax(depth + 1, alpha, beta, c, true);
					bestScore = std::min(bestScore, score);
					beta = std::min(beta, score);
					if (beta <= alpha) {
						this->field[i][j] = 0;
						break;
					}
					this->field[i][j] = 0;
				}
			}
		}
		return bestScore;
	}
}
