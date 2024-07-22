class SimFunc {

	public:

		enum cell_types {

			empty, 
			red

		};

		typedef struct data {

			int age;
			cell_types type;

		}typeData;

		struct Target {

			int coord[2];

		};

		cell_types cellTypeData[144][256];
		unsigned char cellColorData[144 * 256 * 3];

		SimFunc();
		void iterateEpoch();
		bool isValid(int i, int j);
		struct Target findTarget(cell_types currentCellType, int i, int j);
	
};