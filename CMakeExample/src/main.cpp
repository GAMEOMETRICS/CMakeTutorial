#include "Configure.h"
#include <iostream>

#ifdef USEXADD
#include "ExternalAdd.h"
#else
#include "MyAdd/MyAdd.h"
#endif

int main(int argc, char *argv[]) {

  std::cout << "Hello CMake\n";

  std::cout << "Current Version: " << CURRENT_VERSION
            << ", Current Major: " << CURRENT_MAJOR << "\n";

  std::cout << "2 + 3：\n";

#ifdef USEXADD
  ExternalAdd(2, 3);
#else
  MyAdd(2, 3);
#endif
}
