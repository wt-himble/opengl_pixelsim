class SimFunc {

	public:

		// Possible types for cells. Some may currently be unsupported. 

		enum cell_types {

			empty, 
			green, 
			blue

		};

		// Contains the information relating a cell. The type of cell and age are stored. 

		typedef struct data {

			cell_types type;
			int age;

		}typeData;

		struct Target {

			int coord[2];

		};

		// Arrays for storing the cell information. Hard coded as the simulation will not be larger than 256 * 144. 

		typeData cellTypeData[144][256];
		unsigned char cellColorData[144 * 256 * 3];

		SimFunc();
		void iterateEpoch();
		bool isValid(int i, int j);
		struct Target findTarget(cell_types currentCellType, int i, int j);
	
};