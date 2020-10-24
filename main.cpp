#include <iostream>

int main(int argc, char* argv[]) {

    try {
        //lettura lancia errore
    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
