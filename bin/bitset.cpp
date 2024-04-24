#include <bitset>
#include <iostream>

using namespace std;


int main()
{
    bitset<100000> big = 0b010;
    cout << sizeof(big) << endl;

    bitset<5> spibit = 0b11000;
    for (int i=0; i<5; i++)
        cout << spibit[i] << endl;

    return 0;
}
