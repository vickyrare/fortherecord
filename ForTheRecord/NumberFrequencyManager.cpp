#include "NumberFrequencyManager.h"

bool NumberFrequencyManager::isFibonacci(int num)
{
	double X1 = 5 * pow(num, 2) + 4;
	double X2 = 5 * pow(num, 2) - 4;

	long X1_sqrt = (long)sqrt(X1);
	long X2_sqrt = (long)sqrt(X2);

	return (X1_sqrt * X1_sqrt == X1) || (X2_sqrt * X2_sqrt == X2);
}

void NumberFrequencyManager::takePeriodInput()
{
    cout << "Please enter the output period: ";
    cin >> period;
    if (cin.fail() || period < 1) {
        cout << "Invalid input. Please type in a positive number!" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        takePeriodInput();
        return;
    }
}

void NumberFrequencyManager::takeNumberInput(string message)
{
    cout << message.c_str() << endl;
    cin >> number;
    if (cin.fail()) {
        cout << "Invalid input. Please type in a number!" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        takeNumberInput(message);
        return;
    }
    if (isFibonacci(number))
    {
        cout << "FIB!" << endl;
    }
}

void NumberFrequencyManager::insertDatatable(int num)
{
	std::lock_guard<std::mutex> guard(mutex);
	if (dataTable.find(num) == dataTable.end())
	{
		// new entry
		dataTable.insert(std::pair<int, int>(num, 1));
	}
	else
	{
		// update existing entry
		dataTable[num] = dataTable[num] + 1;
	}
}

std::map<int, int> NumberFrequencyManager::getDatatable()
{
    return dataTable;
}

std::vector<pair<int, int>> NumberFrequencyManager::getSortedDatatable()
{
    std::lock_guard<std::mutex> guard(mutex);
    std::vector<pair<int, int>> vec;

    // copy key-value pairs from the map to the vector
    std::copy(dataTable.begin(), dataTable.end(), std::back_inserter<vector<pair<int, int>>>(vec));

    // sort the vector by decreasing order of its pair's second value (value)
    // if second value are equal, order by the pair's first value (key)
    sort(vec.begin(), vec.end(),
         [](const pair<int, int>& l, const pair<int, int>& r)
         {
             if (l.second != r.second)
             {
                 return l.second > r.second;
             }

             return l.first < r.first;
         });

    return vec;
}

void NumberFrequencyManager::printDatatable()
{
	std::vector<pair<int, int>> vec = getSortedDatatable();

	bool first = true;
	for (auto const &pair : vec)
	{
		if (first)
		{
			cout << pair.first << ":" << pair.second;
			first = false;
		}
		else
		{
			cout << ", " << pair.first << ":" << pair.second;
		}
	}
	cout << endl;
}

void NumberFrequencyManager::processInput()
{
	char input;
	while (state != QUIT)
	{
		if (state == RUNNING)
		{
			cin >> input;
		}
		switch (input)
		{
			case 'N':
				timer.pause();
				state = NEW_ENTRY;
				takeNumberInput("Please enter the new number: ");
				insertDatatable(number);
				timer.start();
				state = RUNNING;
				break;
			case 'P':
				timer.pause();
				state = PAUSED;
				cin >> input;
				switch (input) {
				case 'N':
				case 'Q':
				case 'R':
					state = RUNNING;
					timer.start();
					break;
				}
				break;
			case 'Q':
				state = QUIT;
				printDatatable();
				cout << "See you next time!" << endl;
				break;
			case 'R':
				state = RUNNING;
				break;
			case 'A':
				printDatatable();
				break;
		}
	}
}

void NumberFrequencyManager::start()
{
	takePeriodInput();
	takeNumberInput("Please enter the first number: ");
	insertDatatable(number);
	state = RUNNING;
	timer.start();
	// start a new thread to handle user input in background
	thread inputThread(&NumberFrequencyManager::processInput, this);
	while (state != QUIT) {
		while (timer.elapsedSeconds() < period && state != QUIT)
		{
		}
		if (state != QUIT)
		{
			printDatatable();
		}
		timer.stop();
		timer.start();
	}
	inputThread.join();
}