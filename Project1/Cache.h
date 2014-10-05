#ifndef __CACHE_H__
#define __CACHE_H__

#include <Memory.h>
#include <CustomTypes.h>
#include <AddressDecoder.h>
#include <iostream>
#include <TagStore.h>
#include <ReplacementPolicy.h>
#include <cassert>
#define ASSOC
namespace CacheSimulator
{
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
          ReplacementPolicy::Types rPol, WritePolicy wPol, Memory *next)
        :_set(size/(block_size*assoc)),
        _addrDec(_set, block_size)
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
      ui16 set() const {return _set;}
      ui32 rhits() const {return _rhits;}
      ui32 whits() const {return _whits;}
      ui32 rPolicy() const {return (ui32)_rPolicy;}
      ui32 wPolicy() const {return (ui32)_wPolicy;}
      ui32 wbacks() const {return _wbacks;}
      virtual bool isCache() {return true;}
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
        TagEntry &tag = cacheHit(addr);
        bool dirty = true;
        switch(_wPolicy)
        {
          case e_WBWA:
            dirty = true;
            if(!tag)
            {
              cacheMiss(addr).write(dirty);
            }
            break;
          case e_WTNA:
            dirty = false;
            _next->write(addr);
            break;
          default:
            throw "Invalid Write Policy";
            break;
        }
        if(tag)
        {
          _whits++;
          tag.write(dirty);
        }
      }
      void initC()
      {
        _rhits = 0;
        _whits = 0;
        _wbacks = 0;
        TagSet set(_assoc);
        
        switch(_rPolicy)
        {
          case ReplacementPolicy::e_LRU:
            ReplacementPolicy::initLRU(set);
            break;
          case ReplacementPolicy::e_LFU:
            ReplacementPolicy::initLFU(set);
            break;
          default:
            throw "Invalid Read Policy";
            break;
        }
        for(ui32 i=0; i<_set; i++)
          _tags.push_back(set);
      }
    private:
      // total bytes of data store
      ui32 _size;
      //  the associativity of the cache
      ui16 _assoc;
      // number of bytes in a block
      ui16 _blocksize;
      // replacement policy
      ReplacementPolicy::Types _rPolicy;
      // write policy
      WritePolicy _wPolicy;
      // no of set = size/(assoc*blocksize)
      ui16 _set;
      // counter for read hits
      ui32 _rhits;
      // counter for write hits
      ui32 _whits;
      // counter for writebacks
      ui32 _wbacks;
      // pointer to object of AddressDecoder
      AddressDecoder _addrDec;
      // tag store memory
      TagStore _tags;
    private:
      TagEntry & cacheMiss(ui32 addr)
      {
        TagEntry &tag = replaceTag(addr);
        _next->read(addr);
        return tag;
      }
      TagEntry & cacheHit(ui32 addr)
      {
        ui32 index = _addrDec.index(addr);
        ui32 tag = _addrDec.tag(addr);
        TagSet & set =  _tags[index];
        for( ui32 i=0; i<set.size(); i++)
        {
          if( (set[i].tag() == tag) && set[i] )
          {
            updateAccessHistory(set, set[i]);
            return set[i];
          }

        }
        return TagEntry::invalidTag();
      }
      TagEntry & replaceTag(ui32 addr)
      {
        ui32 index = _addrDec.index(addr);
        TagSet &set = _tags[index];

        TagEntry & tag = findTagToReplace(set);
        if (tag.dirty() && tag)
        {
          _wbacks++;
          ui32 wb_addr = _addrDec.generate(tag.tag(), _addrDec.index(addr));
          _next->write(wb_addr);
        }
        tag = TagEntry(_addrDec.tag(addr));
        updateAccessHistory(set, tag);
        return tag;
      }
      void updateAccessHistory(TagSet & set, TagEntry &ref)
      {
        switch(_rPolicy)
        {
          case ReplacementPolicy::e_LRU:
            ReplacementPolicy::updateLRU(set, ref);
            break;
          case ReplacementPolicy::e_LFU:
            ReplacementPolicy::updateLFU(set, ref);
            break;
          default:
            throw "Invalid replacement Policy";
        }
      }
      TagEntry & findTagToReplace(TagSet & set)
      {
        switch(_rPolicy)
        {
          case ReplacementPolicy::e_LRU:
            return ReplacementPolicy::findLRU(set);
            break;
          case ReplacementPolicy::e_LFU:
            return ReplacementPolicy::findLFU(set);
            break;
          default:
            throw "Invalid replacement Policy";
        }
        return TagEntry::invalidTag();
      }
  };
};

#endif //__CACHE_H__

