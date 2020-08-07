#include "IO_Thread.h"
#include "GameManager.h"
#include <iostream>

int GRID_SIZE = 8;
bool playerMove = true;
bool gameOver = false;

Vector2i GetMouseGridField(Vector2i mp) {
	int mx = mp.x - 668;
	int my = mp.y - 271;
	int nx = 0, ny = 0;
	std::cout << mx << " " << my << std::endl;
	for (int i = 0; i < GRID_SIZE; ++i) {
		//std::cout << nx << " " << nx + FIELD_SIZE + 3 << std::endl;
		if ((mx >= nx) && (mx <= nx + FIELD_SIZE)) {
			for (int j = 0; j < GRID_SIZE; ++j) {
				//std::cout << ny << " " << ny + FIELD_SIZE + 3 << std::endl;
				if ((my >= ny) && (my <= ny + FIELD_SIZE)) {
					return Vector2i(i+1, j+1);
				}
				ny += FIELD_SIZE;
			}
		}
		nx += FIELD_SIZE;
	}
	return Vector2i(-1, -1);
}

Vector2i RandomAI() {
	Vector2i res;
	srand(time(0));
	res.x = rand() % GRID_SIZE + 1;
	res.y = rand() % GRID_SIZE + 1;
	return res;
}

void input() {
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Tic-Tac-Toe", Style::Default);
	window.setVerticalSyncEnabled(true);

	std::chrono::duration<float> time;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = start;

	GameManager gm(GRID_SIZE);

	while (true) {
		start = std::chrono::high_resolution_clock::now();

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed) {
				if (!gameOver) {
					if (event.mouseButton.button == Mouse::Left) {
						if (playerMove) {
							if (gm.SetField('x', GetMouseGridField(Mouse::getPosition()))) {
								std::cout << 'x' << std::endl;
								gameOver = gm.CheckVictory('x');
							}
							playerMove = false;
						}
					}
					if (event.mouseButton.button == Mouse::Right) {
						if (!playerMove) {
							if (gm.SetField('o', RandomAI())) {
								std::cout << 'o' << std::endl;
								gameOver = gm.CheckVictory('o');
							}
							playerMove = true;
						}
					}
				}
			}
		}

		if (gameOver) {
			if (Keyboard::isKeyPressed(Keyboard::C)) {
				std::cout << "clear" << std::endl;
				gameOver = false;
				gm.ClearField();
			}
		}

		window.clear();

		//bm->SetProcessed(false);

		for (std::vector<RectangleShape>::iterator iter = gm.GetTics()->begin(); iter != gm.GetTics()->end(); ++iter) {
			window.draw(*iter);
		}
		for (std::vector<CircleShape>::iterator iter = gm.GetTacs()->begin(); iter != gm.GetTacs()->end(); ++iter) {
			window.draw(*iter);
		}
		for (std::vector<RectangleShape>::iterator iter = gm.GetFieldVis()->begin(); iter != gm.GetFieldVis()->end(); ++iter) {
			window.draw(*iter);
		}

		//bm->SetProcessed(true);
		//bm->GetCv()->notify_one();

		window.display();

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			//*gameOver = true;
		}

		end = std::chrono::high_resolution_clock::now();
		time = end - start;
	}
}
