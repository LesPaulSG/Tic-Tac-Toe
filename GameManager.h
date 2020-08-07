#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

const int FIELD_SIZE = 50;

class GameManager
{
private:
	int fieldNum;
	std::vector<std::vector<char>> field;
	char gamerCase;
	int count;
	std::vector<RectangleShape> fieldVis;
	std::vector<RectangleShape> tics;
	std::vector<CircleShape>	tacs;

	bool fieldFree(Vector2i);
public:
	GameManager(int);
	~GameManager();

	int GetFieldsNum();
	char GetGamerCase();
	int GetCount();
	std::vector<std::vector<char>>* GetField();

	std::vector<RectangleShape>*	GetFieldVis();
	std::vector<RectangleShape>*	GetTics();
	std::vector<CircleShape>*		GetTacs();

	bool SetField(char, Vector2i);
	bool CheckVictory(char);
	void ClearField();
};

