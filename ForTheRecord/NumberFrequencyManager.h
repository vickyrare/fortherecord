#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

#include "timer.h"

using namespace std;

class NumberFrequencyManager 
{
	enum STATE {
		STARTUP,
		PAUSED,
		RUNNING,
		NEW_ENTRY,
		QUIT
	};

	private:
		STATE state = STARTUP;
		std::map<int, int> dataTable;
		Timer timer;
		int period, number;
		std::mutex mutex;

		void takePeriodInput();
		void takeNumberInput(string message);
		void printDatatable();
		void processInput();

	public:
		void start();
        bool isFibonacci(int num);
        void insertDatatable(int num);
        std::map<int, int> getDatatable();
        std::vector<pair<int, int>> getSortedDatatable();
};

