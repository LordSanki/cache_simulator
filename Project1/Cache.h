#ifndef __CACHE_H__
#define __CACHE_H__

#include <Memory.h>
#include <CustomTypes.h>
#include <AddressDecoder.h>

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
          ReplacementPolicy rPol, WritePolicy wPol, Memory *next)
        :_sets(size/(block_size*assoc)),
        _addrDec(_sets, block_size)
      {
        _next = next;
        _rPolicy = rPol;
        _wPolicy = wPol;
        _size = size;
        _assoc = assoc;
        _blocksize = block_size;
      }

    protected:
      // function to read data
      ui8 readC(ui32 addr)
      {
      }
      // function to write data
      void writeC(ui32 addr, ui8 data = DATA)
      {
      }
      void initC()
      {
      }

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
      // pointer to object of AddressDecoder
      AddressDecoder _addrDec;
  };
};

#endif //__CACHE_H__

