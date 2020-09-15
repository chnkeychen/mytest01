#include <iostream>
#include <string>
#include <ctime>
#include "speechControl.h"

int main()
{
	srand((unsigned int)time(NULL));
	speechControl sp;

	int select = -1;
	while (true)
	{
		sp.show_ui();
		cout << "ÇëÊäÈëÄúµÄÑ¡Ôñ£¿" << endl;
		cin >> select;

		switch (select)
		{
		case 1:
			sp.speech_Course();
			break;
		case 2:
			sp.speech_record();
			break;
		case 3:
			sp.speech_clear();
			break;
		case 4:
			sp.exit_system();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("cls");
	return 0;
}