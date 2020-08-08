#include "GameManager.h"
#include <iostream>
#include "definitions.h"

using namespace std;

int main() {
	int gridSize;										
	bool xAi, oAi;										//is X player are AI, is O player are AI
	bool gameOver = false, xMove = true, exit = false;	//xMove - X player move
	int uiLenght;										//lenght of uiString, needs for updating string
	cout << "Enter grid size: ";						//input grid size
	cin >> gridSize;
	cout << endl;										
	cout << "Is 'X' player AI? ";						//who should play for X
	cin >> xAi;
	cout << endl;
	cout << "Is 'O' player AI? ";						//who should play for O
	cin >> oAi;
	cout << endl;

	string uiString, temp, endGameLine;					//for simple UI
	uiString.append("X is ");
	temp = (xAi) ? "AI" : "human";
	uiString += temp;
	uiString.append("\nO is ");
	temp = (oAi) ? "AI" : "human";
	uiString += temp;
	uiLenght = uiString.size();							//for string update

	Font font;											//text obj for UI
	font.loadFromFile("OpenSans-Bold.ttf");				
	Text ui(uiString, font, 30);						
	ui.setPosition(gridSize * FIELD_SIZE + 10, 5);
	ui.setFillColor(Color::Red);						

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Tic-Tac-Toe", Style::Default);
	window.setVerticalSyncEnabled(true);

	GameManager gm(gridSize);

	while (!exit) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (!gameOver) {
					if (event.mouseButton.button == Mouse::Left) {														//X
						if (xMove) {																
							if (xAi) {																					//AI move
								gm.AiMove('x');
								xMove = false;
							} else if (gm.SetFieldSpot('x', GetMouseGridField(Mouse::getPosition(window), gridSize))) {	//human move
								xMove = false;
							}
						}
					}
					if (event.mouseButton.button == Mouse::Right) {														//O
						if (!xMove) {																
							if (oAi) {																					//AI
								gm.AiMove('o');
								xMove = true;
							} else if (gm.SetFieldSpot('o', GetMouseGridField(Mouse::getPosition(window), gridSize))) {	//human move
								xMove = true;
							}
						}
					}
				}
			}
		}

		if (gameOver) {
			if (Keyboard::isKeyPressed(Keyboard::C)) {		//wait for clear command
				gm.ClearField();
				uiString.erase(uiLenght, 9);
				ui.setString(uiString);
				gameOver = false;
			}
		} else {											//adds game over info
			if (gm.CheckVictory('x')) {						//for X win
				endGameLine = "\nX wins!";
				uiString.insert(uiLenght, endGameLine);
				ui.setString(uiString);
				gameOver = true;
			} else if (gm.CheckVictory('o')) {				//for O win
				endGameLine = "\nO wins!";
				uiString.insert(uiLenght, endGameLine);
				ui.setString(uiString);
				gameOver = true;
			} else if (!gm.isFreeSpot()) {					//for draw
				endGameLine = "\nDraw!  ";
				uiString.insert(uiLenght, endGameLine);
				ui.setString(uiString);
				gameOver = true;
			}
		}

		window.clear();

		for (std::vector<RectangleShape>::iterator iter = gm.GetTics()->begin(); iter != gm.GetTics()->end(); ++iter) {
			window.draw(*iter);
		}
		for (std::vector<CircleShape>::iterator iter = gm.GetTacs()->begin(); iter != gm.GetTacs()->end(); ++iter) {
			window.draw(*iter);
		}
		for (std::vector<RectangleShape>::iterator iter = gm.GetFieldVis()->begin(); iter != gm.GetFieldVis()->end(); ++iter) {
			window.draw(*iter);
		}
		window.draw(ui);

		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			exit = true;
		}
	}
}