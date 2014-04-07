#include <iostream>
using std::cout;

int main() {
int i = 0;
i = 1, i++;
i = i + 1;
i = i++;
cout << i << std::endl;
std::cin.ignore();
return 0;
}