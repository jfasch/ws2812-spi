#include <bitset>
#include <iostream>

using namespace std;


int main()
{
    bitset<100000> big = 0b010;
    cout << sizeof(big) << endl;
    return 0;
}
