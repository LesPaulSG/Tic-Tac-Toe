#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int HEIGHT = 600;		//window size
const int WIDTH = 600;

//int GRID_SIZE;
const int FIELD_SIZE = 50;		 //size for the single spot in field

Vector2i GetMouseGridField(Vector2i, int);