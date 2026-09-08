#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
    int x = std::stoi(argv[1]);
    

    cout << x * 2 << " and " << x / 2 << '\n';


    for (int r = 0; r < x; r++) {
        cout << "Sam\n";
    }


    return 0;
}