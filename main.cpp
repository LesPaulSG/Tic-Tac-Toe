#include <iostream>
#include "IO_Thread.h"
#include <thread>
#include "GameManager.h"

using namespace std;

int main() {
	int gridSize;
	bool xAi, oAi;
	bool gameOver = false, xMove = true, exit = false;
	cout << "Enter grid size: ";
	cin >> gridSize;
	cout << endl;
	cout << "Is 'X' player AI? ";
	cin >> xAi;
	cout << endl;
	cout << "Is 'O' player AI? ";
	cin >> oAi;
	cout << endl;

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Tic-Tac-Toe", Style::Default);
	window.setVerticalSyncEnabled(true);

	//std::chrono::duration<float> time;
	//auto start = std::chrono::high_resolution_clock::now();
	//auto end = start;

	GameManager gm(gridSize);

	while (!exit) {
		//start = std::chrono::high_resolution_clock::now();

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (!gameOver) {
					if (event.mouseButton.button == Mouse::Left) {
						if (xMove) {
							if (xAi) {
								gm.AiMove('x');
								gameOver = gm.CheckVictory('x');
								xMove = false;
							}
							if (gm.SetField('x', GetMouseGridField(Mouse::getPosition()))) {
								std::cout << 'x' << std::endl;
								gameOver = gm.CheckVictory('x');
								xMove = false;
							}
						}
					}
					if (event.mouseButton.button == Mouse::Right) {
						if (!xMove) {
							if (oAi) {
								gm.AiMove('o');
								gameOver = gm.CheckVictory('o');
								xMove = true;
							}
							if (gm.SetField('o', GetMouseGridField(Mouse::getPosition()))) {
								std::cout << 'o' << std::endl;
								gameOver = gm.CheckVictory('o');
								xMove = true;
							}
						}
					}
				}
			}
		}

		if (gameOver) {
			if (Keyboard::isKeyPressed(Keyboard::C)) {
				gm.ClearField();
				gameOver = false;
			}
		} else {
			gameOver = !gm.isFreeStep();
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

		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			exit = true;
		}

		//end = std::chrono::high_resolution_clock::now();
		//time = end - start;
	}
}