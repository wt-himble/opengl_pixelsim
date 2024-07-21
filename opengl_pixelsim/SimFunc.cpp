#include "SimFunc.h"
#include <iostream>

SimFunc::SimFunc() {

	// Constructor for cellTypeData (defaults all cells to empty):
	
	for (int i = 0; i < 144; i++) {

		for (int j = 0; j < 256; j++) {

			cellTypeData[i][j] = empty;
			cellTypeData[0][0] = red;
			cellTypeData[0][50] = green;
			cellTypeData[0][100] = blue;

		}
	}

	// Constructor for cellColorData (defaults all cells to black):

	for (int i = 0; i < 256 * 144 * 3; i++) {

		cellColorData[i] = 0;

	}

}

// Checks to see if the provided indices are within the range of the texture. If not returns false.

bool SimFunc::isValid(int i, int j) {

	if (i < 0 || i > 143 || j < 0 || j > 255) {

		return false;

	} else {

		return true;

	}
}

// Goes through the neighbouring cells of the current target cell and returns the coordinates of the first valid target.
// Returns a Target struct.

SimFunc::Target SimFunc::findTarget(cell_types currentCellType, int i, int j) {

	cell_types validTarget;
	Target target;

	target.coord[0] = -1;
	target.coord[1] = -1;

	if (currentCellType == red) {

		validTarget = green;

	} else if (currentCellType == green) {

		validTarget = blue;

	} else if (currentCellType == blue) {

		validTarget = red;

	} else {

		validTarget = invalid;

	}

	if (validTarget != invalid) {

		if (isValid(i+1, j) && (cellTypeData[i+1][j] == validTarget || cellTypeData[i+1][j] == empty)) {

			target.coord[0] = i + 1;
			target.coord[1] = j;

		}
		else if (isValid(i, j + 1) && (cellTypeData[i][j + 1] == validTarget || cellTypeData[i][j + 1] == empty)) {

			target.coord[0] = i;
			target.coord[1] = j + 1;

		}
		else if (isValid(i - 1, j) && (cellTypeData[i - 1][j] == validTarget || cellTypeData[i - 1][j] == empty)) {

			target.coord[0] = i - 1;
			target.coord[1] = j;

		}
		else if (isValid(i, j - 1) && (cellTypeData[i][j - 1] == validTarget || cellTypeData[i][j - 1] == empty)) {

			target.coord[0] = i;
			target.coord[1] = j - 1;

		}

	}

	return target;

}

void SimFunc::iterateEpoch() {

	for (int i = 0; i < 144; i++) {

		for (int j = 0; j < 256; j++) {

			if (cellTypeData[i][j] != empty) {

				Target target = findTarget(cellTypeData[i][j], i, j);

				if (target.coord[0] != -1) {

					int index = (target.coord[0] * 256 + target.coord[1]) * 3;

					switch (cellTypeData[i][j]) {

					case red:

						cellColorData[index] = 255;
						cellColorData[index + 1] = 0;
						cellColorData[index + 2] = 0;

						cellTypeData[target.coord[0]][target.coord[1]] = red;

						break;

					case green:

						cellColorData[index] = 0;
						cellColorData[index + 1] = 255;
						cellColorData[index + 2] = 0;

						cellTypeData[target.coord[0]][target.coord[1]] = green;

						break;

					case blue:

						cellColorData[index] = 0;
						cellColorData[index + 1] = 0;
						cellColorData[index + 2] = 255;

						cellTypeData[target.coord[0]][target.coord[1]] = blue;

						break;

					}
				}
			}
		}
	}
}