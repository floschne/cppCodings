#include <iostream>
#include <sstream>
#include <string>


int main(const int argc, const char** argv) {

	std::string xml {"<root><a>hello u fucksssrr</a><asd><c><a>hlloansdl123</a></c></asd></root>"};
	std::stringstream ss(xml);

	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load(ss);

	pugi::xpath_node_set contentNodes = doc.select_nodes("//a");

	for(auto n : contentNodes ) {
		std::cout << n.node().child_value() << " --------" << std::endl;
	}

	std::cout << "hello pugi" << std::endl;
}