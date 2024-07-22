class SimFunc {

	public:

		enum cell_types {

			empty, 
			green, 
			blue

		};

		typedef struct data {

			cell_types type;
			int age;

		}typeData;

		struct Target {

			int coord[2];

		};

		typeData cellTypeData[144][256];
		unsigned char cellColorData[144 * 256 * 3];

		SimFunc();
		void iterateEpoch();
		bool isValid(int i, int j);
		struct Target findTarget(cell_types currentCellType, int i, int j);
	
};