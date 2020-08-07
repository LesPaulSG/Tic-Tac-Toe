#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include <SFML\System\Vector2.hpp>

using namespace sf;

const int HEIGHT = 600;
const int WIDTH = 600;

void input();

Vector2i GetMouseGridField(Vector2i);