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
#define LOG_OUT     "logs\\log.log"
#define BASE_OUT    "res\\test_out.txt"
#define TEST_IN     "res\\test_inp.txt"
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
	// std::clog.imbue(base_locale);
	// std::cin .imbue(base_locale);


	char dir_name [STD_STR_LEN] = {0};
	char char_buff[STD_STR_LEN] = {0};

	(void)getdir(args[0], dir_name, STD_STR_LEN);

	(void)std::sprintf(char_buff, "%s\\%s", dir_name, LOG_OUT);
	std::ofstream log_out(char_buff);
	if (log_out)
		(void)std::clog.rdbuf(log_out.rdbuf());

	std::clog <<"Ruta de ejecutable:\n\t"        <<dir_name     <<'\n';
	std::clog <<"Ruta del archivo de prueba:\n";
	(void)std::sprintf(char_buff, "%s\\%s", dir_name, BASE_OUT);
	std::clog << '\t'<<char_buff<<'\n';
	(void)std::sprintf(char_buff, "%s\\%s", dir_name, TEST_IN);
	std::clog << '\t'<<char_buff<<'\n';
	std::clog <<"El locale global actual es:       " << std::setlocale(LC_ALL, NULL)<<'\n';
	std::clog <<"El locale de lectura actual es:   " <<std::cin .getloc().name()<<'\n';
	std::clog <<"El locale de escritura actual es: " <<std::clog.getloc().name()<<'\n';
	// (void)std::fprintf(std::clog, "Ruta de ejecutable:\n\t%s\n", dir_name);
	// (void)std::fprintf(std::clog, "Ruta del archivo de prueba:\n\t%s\n", char_buff);
	// (void)std::fprintf(std::clog, "El locale actual es: %s\n", base_locale.name());

	(void)std::sprintf(char_buff, "%s\\%s", dir_name, TEST_IN);

	char input_buffer[STD_STR_LEN] = {0};

	std::clog <<"\n¡Hola mundo!\n";
	// (void)std::fprintf(std::clog, "\n¡Hola mundo!\n");
	std::ifstream input_file(char_buff);
	(void)lplim::reset_loop();
	while (input_file && lplim::count_loop()) {
		(void)input_file.getline(input_buffer, STD_STR_LEN, '\n');
		input_buffer[STD_STR_LEN-1] = 0;
		std::clog << input_buffer << '\n';
	}
	input_file.close();

	std::vector<char*> content;
	content.reserve(STD_CONT_CAP);

	// (void)lplim::reset_loop();
	// while (std::cin && lplim::count_loop()) {
	// 	(void)std::cin.getline(input_buffer, STD_STR_LEN, '\n');
	// 	char *line = new char[STD_STR_LEN];
	// 	if (line == nullptr) continue;
	// 	(void)std::strcpy(line, input_buffer);

	// 	content.push_back(line);
	// }

	(void)std::sprintf(char_buff, "%s\\%s", dir_name, BASE_OUT);
	std::ofstream output_file(char_buff);
	if (!output_file) {
		std::cerr << "ERROR AL ABRIR ARCHIVO\n";
		for(char* i : content) delete[] i;
		return 1;
	}
	(void)std::clog.put('\n');
	for (char* line : content) {
		std::clog   << line <<'\n';
		output_file << line <<'\n';
		delete[] line;
	}
	content.clear();
	std::clog <<input_buffer<<'\n';
	// (void)std::fprintf(std::clog, "%s\n", input_buffer);

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
