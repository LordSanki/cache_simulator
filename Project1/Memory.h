#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <string>
#include <CustomTypes.h>

# define DATA 255U

namespace CacheSimulator
{
  class Memory
  {
    public:
      // initializing function setting read and write counter to 0
      void init ()
      {
        _reads = 0;
        _writes = 0;
        initC ();
      }

      // function to read data
      ui8 read(ui32 addr)
      {
        _reads++;
        return readC (addr);
      }
      // function to write data
      void write(ui32 addr, ui8 data = DATA)
      {
        _writes++;
        writeC (addr, data);
      }

      // getter for reads
      ui32 reads ()  { return _reads;  }
      // getter for writes
      ui32 writes () { return _writes; }
      // getter for name
      std::string name ()       { return _name; }
      // setter for name
      void name (std::string n) { _name = n;    }
    
    protected:
      // abstract function for initialization of memory
      void initC () = 0;
      // abstract function for customized reads
      ui8 readC (ui32 addr) = 0;
      // abstract function for customized writes
      void writeC (ui32 addr, ui8 data) = 0;

    private:
      // counter for tracking reads
      ui32 _reads;
      // counter for tracking writes
      ui32 _writes;
      // name of memory
      std::string _name;
  };
};

#endif //__MEMORY_H__

