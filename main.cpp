#include <iostream>
#include "PrintHeader.h"
#include "Functions.h"
using namespace std;

int main()
{
	MusicLib a;
	setlocale(LC_CTYPE, "ukr");
	a.main_menu();
	return 0;
}
