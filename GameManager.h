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

	const int MAX_DEPTH = 30;

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
	bool CheckVictoryMM(char);
	bool CheckDraw();
	bool isFreeStep();
	int FreeSteps();
	void ClearField();
	void AiMove(char);
	void RandomMove(char);

	int minimax(int, int, int, int*, char, bool);
};

