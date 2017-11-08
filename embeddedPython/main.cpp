#include <python3.5/Python.h>
#include <sstream>
#include <iostream>


/* Build command:
 * g++ main.cpp -o main -lpthread -ldl -lutil -lm -lpython3.5m
 */

int main(int argc, char *argv[])
{
  	Py_Initialize();
	std::stringstream pyCommand;
	try {
		pyCommand << "import img2pdf\n";
		pyCommand << "pdf_bytes = img2pdf.convert('test.png.pdf.png')\n";
		pyCommand << "file = open('./asda.pdf.png.pdf','wb')\n";
		pyCommand << "file.write(pdf_bytes)\n";
		PyRun_SimpleString(pyCommand.str().c_str());
	} catch (...) {
		std::cout << "exc!";
	}

    Py_Finalize();
  return 0;
}