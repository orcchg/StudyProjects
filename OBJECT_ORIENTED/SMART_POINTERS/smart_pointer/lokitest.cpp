#include <loki/SmartPtr.h>
using Loki::SmartPtr;

int main() {
  SmartPtr(new int(15));
  return 0;
}