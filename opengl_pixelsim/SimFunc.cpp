#include "SimFunc.h"

SimFunc::SimFunc() {

	// Constructor for cellTypeData (defaults all cells to empty):

	for (int i = 0; i < 144; i++) {

		for (int j = 0; j < 256; j++) {

			cellTypeData[i][j] = green;

		}
	}

	// Constructor for cellColorData (defaults all cells to black):

	for (int i = 0; i < 256 * 144 * 3; i++) {

		cellColorData[i] = 0;

	}

}

bool SimFunc::isValid(int i, int j) {

	if (i < 0 || i > 144 || j < 0 || j < 255) {

		return false;

	} else {

		return true;

	}
}

SimFunc::Target SimFunc::findTarget(cell_types currentCellType, int i, int j) {

	if (isValid(i + 1, j)) {

		

	}

	



}

void SimFunc::iterateEpoch() {

	for (int i = 0; i < 144; i++) {

		for (int j = 0; j < 256; j++) {

			switch (cellTypeData[i][j]) {

				case red:

				

					







			}

			



		}



	}


}