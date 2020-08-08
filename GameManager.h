#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

class GameManager
{
private:
	int fieldNum;	
	bool winLineDrawn;
	std::vector<std::vector<char>> field;
	std::vector<RectangleShape> fieldVis;
	std::vector<RectangleShape> tics;
	std::vector<CircleShape>	tacs;
	const int MAX_DEPTH = 30;

public:
	GameManager(int);
	~GameManager();

	int GetFieldsNum();
	std::vector<std::vector<char>>* GetField();
	std::vector<RectangleShape>*	GetFieldVis();
	std::vector<RectangleShape>*	GetTics();
	std::vector<CircleShape>*		GetTacs();

	bool SetFieldSpot(char, Vector2i);
	bool CheckVictory(char);
	bool CheckVictoryMM(char);
	bool isFreeSpot();
	int FreeSteps();
	void ClearField();
	void AiMove(char);
	void RandomMove(char);

	int minimax(int, int, int, char, bool);
};

