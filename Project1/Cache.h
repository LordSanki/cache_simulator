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
    friend class ResultGenerator;
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
      // read accessors
      ui32 size() const {return _size;}
      ui16 assoc() const {return _assoc;}
      ui16 blocksize() const {return _blocksize;}
      ui16 sets() const {return _sets;}
      ui32 rhits() const {return _rhits;}
      ui32 whits() const {return _whits;}
      ui32 rPolicy() const {return (ui32)_rPolicy;}
      ui32 wPolicy() const {return (ui32)_wPolicy;}
    protected:
      // function to read data
      ui8 readC(ui32 addr)
      {
        if(cacheHit(addr))
          _rhits++;
        else
          cacheMiss(addr);
        return DATA;
      }
      // function to write data
      void writeC(ui32 addr, ui8)
      {
        if(cacheHit(addr))
          _whits++;
        switch(_wPolicy)
        {
          case e_WBWA:
            break;
          case e_WTNA:
            break;
          default:
            throw "Invalid Write Policy";
            break;
        }
      }
      void initC()
      {
        _rhits = 0;
        _whits = 0;
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
      // counter for read hits
      ui32 _rhits;
      // counter for write hits
      ui32 _whits;
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
          {
            return true;
          }
        }
        return false;
      }
  };
};

#endif //__CACHE_H__

