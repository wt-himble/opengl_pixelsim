#include "SimFunc.h"
#include <iostream>

SimFunc::SimFunc() {

	// Constructor for cellTypeData (defaults all cells to empty):
	
	for (int i = 0; i < 144; i++) {

		for (int j = 0; j < 256; j++) {

			cellTypeData[i][j].type = empty;
			cellTypeData[i][j].age = 0;

		}
	}

	// Initial conditions for simulation:

	cellTypeData[0][0].type = green;
	cellTypeData[0][0].age = 30;

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

// It is currently setup to be random.

SimFunc::Target SimFunc::findTarget(cell_types currentCellType, int i, int j) {

	Target target;

	target.coord[0] = -1;
	target.coord[1] = -1;

	int randNum = rand() % 4;

	switch (randNum) {

		case 0:

			if (isValid(i + 1, j)) {

				if (cellTypeData[i + 1][j].type == empty) {

					target.coord[0] = i + 1;
					target.coord[1] = j;

					break;


				}
			}

		case 1:

			if (isValid(i, j + 1)) {

				if (cellTypeData[i][j+1].type == empty) {

					target.coord[0] = i;
					target.coord[1] = j + 1;

					break;

				}
			}

		case 2:

			if (isValid(i - 1, j)) {

				if (cellTypeData[i - 1][j].type == empty) {

					target.coord[0] = i - 1;
					target.coord[1] = j;

					break;


				}
			}

		case 3:

			if (isValid(i, j - 1)) {

				if (cellTypeData[i][j-1].type == empty) {

					target.coord[0] = i;
					target.coord[1] = j - 1;

					break;


				}

			}
		
	}

	return target;
}

// Iterates through the current epoch of the simulation. Ages and spreads cells.
// Also updates colours of cells to reflect these changes.

void SimFunc::iterateEpoch() {

	for (int i = 0; i < 144; i++) {

		for (int j = 0; j < 256; j++) {

			// Rendering colors based on cell type:

			int index = (i * 256 + j) * 3;

			if (cellTypeData[i][j].type == green) {

				cellColorData[index] = 3.8 * cellTypeData[i][j].age;
				cellColorData[index + 1] = 3.4 * cellTypeData[i][j].age;
				cellColorData[index + 2] = 4.1 * cellTypeData[i][j].age;;

			} else if (cellTypeData[i][j].type == blue) {

				cellColorData[index] = 0;
				cellColorData[index + 1] = 0;
				cellColorData[index + 2] = 8 * cellTypeData[i][j].age;

			} else {

				cellColorData[index] = 0;
				cellColorData[index + 1] = 0;
				cellColorData[index + 2] = 0;
			}

			// Aging cells:

			if (cellTypeData[i][j].age > 0) {

				cellTypeData[i][j].age--;

			} else if (cellTypeData[i][j].age == 0) {

				cellTypeData[i][j].type = empty;

			}

			// Spreading cells:

			if (cellTypeData[i][j].type != empty && cellTypeData[i][j].age > 5) {

				Target target = findTarget(cellTypeData[i][j].type, i, j);

				if (target.coord[0] != -1) {

					switch (cellTypeData[i][j].type) {

						case green:

							cellTypeData[target.coord[0]][target.coord[1]].type = green;
							cellTypeData[target.coord[0]][target.coord[1]].age = 30;

							break;

						case blue:

							cellTypeData[target.coord[0]][target.coord[1]].type = blue;
							cellTypeData[target.coord[0]][target.coord[1]].age = 5;

							break;

					}
				}
			}
		}
	}
}