#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main () {
    for(int i=0;i<10;i++) {
        std::stringstream ss;
        ss << "akk.txt" << i;
        std::cout << ss.str() << std::endl;

        std::ofstream ofs (ss.str(), std::ofstream::out);

        ofs << "lorem ipsum" << std::endl;

        ofs.close();
        int j=0;
        std::cin >> j;

    }

    return 0;
}