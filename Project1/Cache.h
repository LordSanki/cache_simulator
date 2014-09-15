#ifndef __CACHE_H__
#define __CACHE_H__

#include <Memory.h>
#include <CustomTypes.h>
#include <AddressDecoder.h>
#include <iostream>
#include <TagStore.h>
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
      ~Cache()
      {
      }
    protected:
      // function to read data
      ui8 readC(ui32 addr)
      {
        if(!cacheHit(addr))
          cacheMiss(addr);
        return DATA;
      }
      // function to write data
      void writeC(ui32 addr, ui8)
      {
      }
      void initC()
      {
        TagStore tStore(_sets);
        for(ui32 i=0; i<_assoc; i++)
          _tags.push_back(tStore);
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
      // pointer to object of AddressDecoder
      AddressDecoder _addrDec;
      // tag store memory
      AssociateTagStore _tags;
    private:
      void cacheMiss(ui32 addr)
      {
        _next->read(addr);
        replaceTag(addr);
      }
      void replaceTag(ui32 addr)
      {
        ui32 index = _addrDec.index(addr);
        TagEntry tag(_addrDec.tag(addr));
        if(_assoc < 2)
          _tags.front().at(index) = tag;
      }
      bool cacheHit(ui32 addr)
      {
        ui32 index = _addrDec.index(addr);
        ui32 tag = _addrDec.tag(addr);
        for(AssociateTagStore::const_iterator it = _tags.begin();
            it != _tags.end(); it++)
        {
          if((*it)[index] == tag)
            return true;
        }
        return false;
      }
  };
};

#endif //__CACHE_H__

