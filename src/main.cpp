#include <iostream>
#include <string>

int main(void) {
	std::wcout << L"¡Hola mundo!\n";
	std::wstring str(256, 0);

	std::wcin  >> str;
	std::wcout << str <<'\n';
	return 0;
}
