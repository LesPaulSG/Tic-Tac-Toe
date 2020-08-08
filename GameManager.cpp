#include "GameManager.h"
#include <iostream>
#include <math.h>
#include <thread>

GameManager::GameManager(int n) : fieldNum(n) {
	this->field = std::vector<std::vector<char>>(n, std::vector<char>(n, 0));
	//for (std::vector<std::vector<char>>::iterator iter = this->field.begin(); iter != this->field.end(); ++iter) {
	//	iter->reserve(n);
		//*iter = 0;
	//}
	for (int i = 0; i < n-1; ++i) {
		RectangleShape v, h;

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

char GameManager::GetGamerCase(){
	return this->gamerCase;
}

int GameManager::GetCount(){
	return this->count;
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

bool GameManager::SetField(char c, Vector2i pos){
	int x = pos.x - 1;
	int y = pos.y - 1;

	if (x < 0) {
		std::cout << " not in range " << std::endl;
		//std::cout << x << " " << y << std::endl;
		return false;
	}

	//std::cout << this->field.size() << std::endl;
	//for (int i = 0; i < 8; ++i) {
	//	std::cout << this->field[i].size();
	//}
	//std::cout << std::endl;

	if (this->field[x][y] == 0) {
		std::cout << x << y << std::endl;
		this->field[x][y] = c;
		if (c == 'x') {
			RectangleShape f, s;
			f.setPosition(Vector2f(x * FIELD_SIZE + 10, y * FIELD_SIZE + 9));
			s.setPosition(Vector2f((x * FIELD_SIZE) + FIELD_SIZE, y * FIELD_SIZE + 7));
			f.setSize(Vector2f(3, FIELD_SIZE + 6));
			s.setSize(Vector2f(3, FIELD_SIZE + 6));
			f.setRotation(315);
			s.setRotation(45);
			f.setFillColor(Color::Red);
			s.setFillColor(Color::Red);
			this->tics.push_back(f);
			this->tics.push_back(s);
		}
		else if (c == 'o') {
			CircleShape s;
			s.setPosition(Vector2f(x * FIELD_SIZE + 12, y * FIELD_SIZE + 9));
			s.setRadius(FIELD_SIZE/2.5);
			s.setOutlineColor(Color::Cyan);
			s.setFillColor(Color::Black);
			s.setOutlineThickness(3);
			this->tacs.push_back(s);
		}
		return true;
		++this->count;
	}
	
	return false;
}

bool GameManager::CheckVictory(char c){
	int num = 0;
	int i, j;
	//for (std::vector<std::vector<char>>::iterator col = this->field.begin(); col != this->field.end(); ++col) {
	//	for (std::vector<char>::iterator row = col->begin(); row != col->end(); ++row) {
	//std::cout << "start - " << c << std::endl;
	for (i = 0; i < this->fieldNum; ++i) {
		j = 0;
		while (this->field[i][j] == c){
			++num;
			++j;
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, this->fieldNum * FIELD_SIZE));
				line.setPosition(Vector2f((i * FIELD_SIZE + FIELD_SIZE / 2 + 5), 5));
				line.setFillColor(Color::Yellow);
				this->fieldVis.push_back(line);
				std::cout << "winner - " << c << std::endl;
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
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, this->fieldNum * FIELD_SIZE));
				line.setPosition(Vector2f(5, (i * FIELD_SIZE + FIELD_SIZE / 2 + 5)));
				line.setFillColor(Color::Yellow);
				line.setRotation(270);
				this->fieldVis.push_back(line);
				std::cout << "winner - " << c << std::endl;
				return true;
			}
		}
		num = 0;
	}
	for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][i] == c) {
			++num;
			//++j;
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, this->fieldNum * FIELD_SIZE + 3 * FIELD_SIZE));
				line.setPosition(Vector2f(5, 5));
				line.setFillColor(Color::Yellow);
				line.setRotation(315);
				this->fieldVis.push_back(line);
				std::cout << "winner - " << c << std::endl;
				return true;
			}
		}
	}
	num = 0;
	for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][this->fieldNum-i-1] == c) {
			++num;
			//++j;
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				RectangleShape line;
				line.setSize(Vector2f(3, this->fieldNum * FIELD_SIZE + 3 * FIELD_SIZE));
				line.setPosition(Vector2f(this->fieldNum * FIELD_SIZE, 5));
				line.setFillColor(Color::Yellow);
				line.setRotation(45);
				this->fieldVis.push_back(line);
				std::cout << "winner - " << c << std::endl;
				return true;
			}
		}
	}
	return false;
}

bool GameManager::CheckVictoryMM(char c){
	int num = 0;
	int bestNum = 0;
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
		bestNum = std::max(num, bestNum);
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
		bestNum = std::max(num, bestNum);
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
	bestNum = std::max(num, bestNum);
	num = 0;
	for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][this->fieldNum - i - 1] == c) {
			++num;
			if (num == this->fieldNum) {
				return true;
			}
		}
	}
	//bestNum = std::max(num, bestNum);
	return false;
}

bool GameManager::CheckDraw(){
	int num = 0;
	int i, j;

	if (this->count == pow(this->fieldNum, 2)) {
		std::cout << this->count << std::endl;
		return true;
	}
	//std::cout << this->count << std::endl;
	return false;
}

bool GameManager::isFreeStep(){
	for (int i = 0; i < this->fieldNum; ++i) {
		for (int j = 0; j < this->fieldNum; ++j) {
			if (this->field[i][j] == 0) {
				return true;
			}
		}
	}
	return false;
}

int GameManager::FreeSteps(){
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

void GameManager::ClearField(){
	if (this->isFreeStep()) {
		this->fieldVis.pop_back();
	}
	this->tics.clear();
	this->tacs.clear();
	this->field = std::vector<std::vector<char>>(fieldNum, std::vector<char>(fieldNum, 0));	
}

void GameManager::AiMove(char c){
	int num = 0, res = 0, row = 0, col = 0;
	int j;

	int score = 0, maxS = -100, path = 0, minPath = 1000;
	Vector2i move;

	if (this->FreeSteps() > 10) {
		this->RandomMove(c);
		return;
	}

	for (int i = 0; i < this->fieldNum; ++i) {
		for (int j = 0; j < this->fieldNum; ++j) {
			if (this->field[i][j] == 0) {
				this->field[i][j] = c;
				//++this->count;
				score = this->minimax(0, -100, 100, &path, c, false);
				//std::cout << score << std::endl;
				this->field[i][j] = 0;
				//--this->count;
				if (score > maxS) {
					//if (path < minPath) {
						std::cout << "score update " << path << std::endl;
						maxS = score;
						//minPath = path;
						move.x = i + 1;
						move.y = j + 1;
					//}
				}
			}
		}
	}
	std::cout << move.x << " " << move.y << std::endl;
	this->SetField(c, move);

	/*static bool first = true;

	if (this->count <= 3) {
		this->RandomMove(c);
		++this->count;
		return;
	}
	
	for (int i = 0; i < this->fieldNum; ++i) {
		j = 0;
		while (this->field[i][j] == c) {
			++num;
			++j;
			//std::cout << "count - " << num << std::endl;
			if (num > res) {
				res = num;
				row = j;
				std::cout << "winner - " << c << std::endl;
			}
		}
		num = 0;
	}
	for (int i = 0; i < this->fieldNum; ++i) {
		j = 0;
		while (this->field[j][i] == c) {
			++num;
			++j;
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				res = num;
				col = j;
				std::cout << "winner - " << c << std::endl;
			}
		}
		num = 0;
	}
	if (row > col) {
		int t = 0;
		std::cout << "---row" << row;
		while(!this->SetField(c, Vector2i(row+1, t+1))) {
			++t;
			if (t >= this->fieldNum) {
				break;
			}
			std::cout << " " << t;
		}
		std::cout << std::endl;
	} else {
		int t = 0;
		std::cout << "---col" << col;
		while (!this->SetField(c, Vector2i(t+1, col+1))) {
			++t;
			if (t >= this->fieldNum) {
				break;
			}
			std::cout << " " << t;
		}
		std::cout << std::endl;
	}
	/*for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][i] == c) {
			++num;
			//++j;
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				
				std::cout << "winner - " << c << std::endl;
			}
		}
	}
	num = 0;
	for (int i = 0; i < this->fieldNum; ++i) {
		if (this->field[i][this->fieldNum - i - 1] == c) {
			++num;
			//++j;
			//std::cout << "count - " << num << std::endl;
			if (num == this->fieldNum) {
				
				std::cout << "winner - " << c << std::endl;
			}
		}
	}*/
}

void GameManager::RandomMove(char c){
	Vector2i res;
	srand(time(0));
	res.x = rand() % this->fieldNum + 1;
	res.y = rand() % this->fieldNum + 1;
	std::cout << res.x << " " << res.y << std::endl;
	while (!this->SetField(c, res)) {
		res.x = rand() % this->fieldNum + 1;
		res.y = rand() % this->fieldNum + 1;
		std::cout << res.x << " " << res.y << std::endl;
	}
}
//static int cnt = 0;
int GameManager::minimax(int depth, int alpha, int beta, int* path, char c, bool isMax){
	int score = 0;
	static char enemy;

	if (depth > this->MAX_DEPTH) {
		return 10;
	}

	//std::cout << depth << std::endl;
	if (c == 'x') {
		enemy = 'o';
	} else if (c == 'o') {
		enemy = 'x';
	}
	if (this->CheckVictoryMM(c)) {
		//std::cout << "victory " << depth << std::endl;
		//for (int i = 0; i < this->fieldNum; ++i) {
		//	for (int j = 0; j < this->fieldNum; ++j) {
		//		std::cout << this->field[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
		*path = depth;
		return 10;
	} else if (this->CheckVictoryMM(enemy)) {
		//std::cout << "defeat " << depth << std::endl;
		*path = depth;
		return -10;
	} else if (!this->isFreeStep()) {
		//std::cout << "draw " << c << enemy << std::endl;
		*path = depth;
		return 0;
	}

	//cnt++;

	/*if (depth >= *path) {
		if (c == 'o') {
			return -10;
		}
		else if (c == 'x') {
			return 10;
		}
	}

	if (depth >= 10) {
		return this->CheckVictoryMM(c);
	}
	else if (this->CheckVictoryMM(c) == 10) {
		if (c == 'o') {
			*path = depth;
			return 10;
		}
		else {
			*path = depth;
			return -10;
		}	
	}
	else if (!this->isFreeStep()) {
		return 0;
	}*/

	//std::cout << depth << std::endl;

	/*for (int i = 0; i < this->fieldNum; ++i) {
		for (int j = 0; j < this->fieldNum; ++j) {
			std::cout << this->field[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	//std::cout << std::endl;
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::cout << 'x' << std::endl;
	//std::cout << this->CheckVictoryMM('x') << std::endl; 
	//std::cout << 'o' << std::endl;
	//std::cout << this->CheckVictoryMM('o') << std::endl;

	/*if (this->CheckVictoryMM('x')) {
		return -1;
	}
	else if (this->CheckVictoryMM('o')) {
		return 1;
	}
	else if (this->CheckDraw()) {
		return 0;
	}*/

	if (isMax) {
		int maxScore = -100;
		for (int i = 0; i < this->fieldNum; ++i) {
			for (int j = 0; j < this->fieldNum; ++j) {
				if (this->field[i][j] == 0) {
					this->field[i][j] = c;
					//++this->count;
					score = minimax(depth + 1, alpha, beta, path, c, false);
					maxScore = std::max(maxScore, score);
					alpha = std::max(alpha, score);
					if (beta <= alpha) {
						this->field[i][j] = 0;
						break;
					}
					this->field[i][j] = 0;
					//--this->count;
				}
			}
		}
		return maxScore;
	} else {
		int minScore = 100;
		for (int i = 0; i < this->fieldNum; ++i) {
			for (int j = 0; j < this->fieldNum; ++j) {
				if (this->field[i][j] == 0) {
					this->field[i][j] = enemy;
					//++this->count;
					score = minimax(depth + 1, alpha, beta, path, c, true);
					minScore = std::min(minScore, score);
					beta = std::min(beta, score);
					if (beta <= alpha) {
						this->field[i][j] = 0;
						break;
					}
					this->field[i][j] = 0;
					//--this->count;
				}
			}
		}
		return minScore;
	}
}
