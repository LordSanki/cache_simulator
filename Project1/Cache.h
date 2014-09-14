#ifndef __CACHE_H__
#define __CACHE_H__

#include <Memory.h>
#include <CustomTypes.h>

namespace CacheSimulator
{

  enum ReplacementPolicy
  {
    e_LRU=0,
    e_LFU=1
  };
  enum WritePolicy
  {
    e_WBWA=0,
    e_WTNA=1
  };



  class Cache: public Memory
  {
    public:

      Cache(ui16 block_size, ui16 size, ui16 assoc,
          ReplacementPolicy rPol, WritePolicy wPol, Memory *next);

      // function to read data
      ui8 read(ui32 addr);
      // function to write data
      void write(ui32 addr, ui8 data = DATA);

    private:
      // total bytes of data store
      ui32 _size;
      //  the associativity of the cache
      ui16 _assoc;
      // number of bytes in a block
      ui16 _blocksize;
      // replacement policy
      ReplacementPolicy _rPolicy;
      // write policy
      WritePolicy _wPolicy;
      // no of sets = size/(assoc*blocksize)
      ui16 _sets;
      // pointer to object of next memory
      Memory *_next;
      // pointer to object of AddressHelper
      AddressHelper *_addrHelp;
  };
};

#endif //__CACHE_H__

