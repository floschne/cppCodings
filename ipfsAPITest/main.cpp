#include <iostream>
#include <ipfs/client.h>

int main(int argc, const char** argv) {

	std::stringstream ss;

	ipfs::Client client("localhost", 5001);

	client.FilesGet("/ipfs/QmYwAPJzv5CZsnA625s3Xf2nemtYgPpHdWEz79ojWnPbdG/readme", &ss);

	std::cout << ss.str() << std::endl;
}
