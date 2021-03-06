#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

#include "MemoryManager.h"

int main(void)
{
  using namespace MemoryManager;

  initializeMemoryManager();

  long* int_pointer;
// char* string_pointer;
  long* int_pointer1;

  std::cout << "Free memory = " << freeRemaining() << std::endl;

  int_pointer = (long *) allocate(sizeof(long));
  //string_pointer = (char*) allocate(255);
  *int_pointer = 0xDEADBEEF;
 //string_pointer = (char*)allocate(255);
 
 std::cout << "Free memory = " << freeRemaining() << std::endl;
// std::strcpy(string_pointer,"It was the best of times, it was the worst of times");

 //deallocate(string_pointer);
 int_pointer1 = (long *)allocate(sizeof(long));
 std::cout << "Free memory = " << freeRemaining() << std::endl;
 std::cout << "Largest free = " << largestFree() << std::endl;
 std::cout << "Smallest free = " << smallestFree() << std::endl;
 *int_pointer1 = 2564;
 deallocate(int_pointer);
 std::cout << "Free memory = " << freeRemaining() << std::endl;
 std::cout << "Largest free = " << largestFree() << std::endl;
 std::cout << "Smallest free = " << smallestFree() << std::endl;
 
 long *int_pointer2 = (long *)allocate(sizeof(long));
 std::cout << "Free memory = " << freeRemaining() << std::endl;
 std::cout << "Largest free = " << largestFree() << std::endl;
 std::cout << "Smallest free = " << smallestFree() << std::endl;
 //string_pointer = (char*)allocate(255);
 /*deallocate(string_pointer);*/
 system("pause");
}

namespace MemoryManager
{
  void onOutOfMemory(void)
  {
    std::cerr << "Memory pool out of memory" << std::endl;
    exit( 1 );
  }

  // call for any other error condition, providing meaningful error messages are appreciated
  void onIllegalOperation(const char* fmt,...)
  {
    if ( fmt == NULL )
    {
      std::cerr << "Unknown illegal operation" << std::endl;
      exit( 1 );
    }
    else
    {
      char	buf[8192];

      va_list argptr;
      va_start (argptr,fmt);
      vsprintf_s (buf,fmt,argptr);
      va_end (argptr);

      std::cerr << "Illegal operation: \"" << buf << "\"" << std::endl;
      exit( 1 );
    }
  }
}
