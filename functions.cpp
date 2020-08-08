#include "definitions.h"
#include "GameManager.h"

Vector2i GetMouseGridField(Vector2i mp, int gs) {
	int mx = mp.x;
	int my = mp.y;
	int nx = 0, ny = 0;
	for (int i = 0; i < gs; ++i) {
		if ((mx >= nx) && (mx <= nx + FIELD_SIZE)) {
			for (int j = 0; j < gs; ++j) {
				if ((my >= ny) && (my <= ny + FIELD_SIZE)) {
					return Vector2i(i, j);
				}
				ny += FIELD_SIZE;
			}
		}
		nx += FIELD_SIZE;
	}
	return Vector2i(-1, -1);
}