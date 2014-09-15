#ifndef __MAIN_MEMORY_H__
#define __MAIN_MEMORY_H__

#include <Memory.h>
#include <CustomTypes.h>
#include <iostream>
namespace CacheSimulator
{
  class MainMemory: public Memory
  {
    public:
      MainMemory()
      {
        _next = NULL;
      }
      ~MainMemory() 
      {
      }
      //function to initialize memory
      void initC()
      {
      }
      // function to read data
      ui8 readC(ui32 addr)
      {
        return DATA;
      }
      // function to write data
      void writeC(ui32 addr, ui8 data)
      {
      }
  };
};

#endif //__MAIN_MEMORY_H__

