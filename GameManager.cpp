#include "GameManager.h"
#include <iostream>

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
	}
	
	return false;
}

bool GameManager::CheckVictory(char c){
	int num = 0;
	int i, j;
	//for (std::vector<std::vector<char>>::iterator col = this->field.begin(); col != this->field.end(); ++col) {
	//	for (std::vector<char>::iterator row = col->begin(); row != col->end(); ++row) {
	//std::cout << "start - " << c << std::endl;
	for (i = 0; i < 8; ++i) {
		j = 0;
		while (this->field[i][j] == c){
			++num;
			++j;
			//std::cout << "count - " << num << std::endl;
			if (num == 8) {
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
	for (i = 0; i < 8; ++i) {
		j = 0;
		while (this->field[j][i] == c) {
			++num;
			++j;
			//std::cout << "count - " << num << std::endl;
			if (num == 8) {
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
			if (num == 8) {
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
			if (num == 8) {
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

void GameManager::ClearField(){
	this->tics.clear();
	this->tacs.clear();
	this->field = std::vector<std::vector<char>>(fieldNum, std::vector<char>(fieldNum, 0));
	this->fieldVis.pop_back();
}
