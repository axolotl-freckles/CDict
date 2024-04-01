#include <iostream>
#include <fstream>
// #include <cstdio>
// #include <cstdlib>
#include <string>
#include <locale>
#include <vector>

#include <loop_limits.hpp>
#include <gui_api.hpp>

// #define MAX_IT       256

#define STD_STR_LEN  256
#define STD_CONT_CAP 16
#define BASE_OUT    "res\\test_out.txt"
#define STD_LOCALE  ".utf-8"

size_t getdir(const char* fileroute, char* dest, const size_t max) {
	size_t len = 0;
	while (len < max)
		if (fileroute[len++] == NULL) break;

	while (len > 0)
		if (fileroute[len--] == '\\') break;
	size_t it = 0;
	while (it <= len) {
		dest[it] = fileroute[it];
		it++;
	}
	dest[it] = NULL;
	return it;
}

int main(int nargs, char *args[]) {
	(void)std::setlocale(LC_ALL, STD_LOCALE);
	// std::locale base_locale(STD_LOCALE);
	// std::locale inte_locale("");
	// std::cout.imbue(base_locale);
	// std::cin .imbue(base_locale);

	char dir_name     [STD_STR_LEN] = {0};
	char test_filename[STD_STR_LEN] = {0};

	(void)getdir(args[0], dir_name, STD_STR_LEN);
	(void)std::sprintf(test_filename, "%s\\%s", dir_name, BASE_OUT);

	std::cout <<"Ruta de ejecutable:\n\t"        <<dir_name     <<'\n';
	std::cout <<"Ruta del archivo de prueba:\n\t"<<test_filename<<'\n';
	std::cout <<"El locale global actual es:       " << std::setlocale(LC_ALL, NULL)<<'\n';
	std::cout <<"El locale de lectura actual es:   " <<std::cin .getloc().name()<<'\n';
	std::cout <<"El locale de escritura actual es: " <<std::cout.getloc().name()<<'\n';
	// (void)std::fprintf(std::cout, "Ruta de ejecutable:\n\t%s\n", dir_name);
	// (void)std::fprintf(std::cout, "Ruta del archivo de prueba:\n\t%s\n", test_filename);
	// (void)std::fprintf(std::cout, "El locale actual es: %s\n", base_locale.name());

	std::cout <<"\n¡Hola mundo!\n";
	// (void)std::fprintf(std::cout, "\n¡Hola mundo!\n");

	char buffer[STD_STR_LEN] = {0};

	std::vector<char*> content;
	content.reserve(STD_CONT_CAP);

	(void)lplim::reset_loop();
	while (std::cin && lplim::count_loop()) {
		(void)std::cin.getline(buffer, STD_STR_LEN, '\n');
		char *line = new char[STD_STR_LEN];
		if (line == nullptr) continue;
		(void)std::strcpy(line, buffer);

		content.push_back(line);
	}

	std::ofstream output_file(test_filename);
	if (!output_file) {
		std::cerr << "ERROR AL ABRIR ARCHIVO\n";
		for(char* i : content) delete[] i;
		return 1;
	}
	(void)std::cout.put('\n');
	for (char* line : content) {
		std::cout   << line <<'\n';
		output_file << line <<'\n';
		delete[] line;
	}
	content.clear();
	std::cout <<buffer<<'\n';
	// (void)std::fprintf(std::cout, "%s\n", buffer);

	WINDOW_HANDLER window_id = gui::create_window(1200, 720, "¡Hola!");

	if (window_id == NULL) {
		std::cerr << "ERROR AL CREAR VENTANA\n";
		return 1;
	}

	while (gui::window_running(window_id)) {
		gui::update_window(window_id);
	}
	return 0;
}
