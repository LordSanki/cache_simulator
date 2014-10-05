#ifndef __TAG_STORE_H__
#define __TAG_STORE_H__

#include <vector>
#include <list>
#include <CustomTypes.h>

namespace CacheSimulator
{
#define UNDEFINED_COUNT_BLOCK 0xfffffffe
  class TagEntry
  {
    public:
      TagEntry(ui32 tag) 
      {
        _dirty = false;
        _valid = true;
        _tag = tag;
        _count_block = UNDEFINED_COUNT_BLOCK;
      }
      TagEntry()
      {
        _valid = false;
        _dirty = false;
        _tag = 0U;
        _count_block = UNDEFINED_COUNT_BLOCK;
      }
      static TagEntry & invalidTag()
      {
        static TagEntry null;
        null = TagEntry();
        return null;
      }
      ui32 tag() const {return _tag;}
      void read() { }
      void write(bool flag) { _dirty = flag; }
      bool dirty() const { return _dirty; }
      operator bool() const { return _valid; }
      bool operator ==(const TagEntry &other) const
      {
        return (_tag == other.tag());
      }
      bool operator ==(ui32 tag) const
      {
        return (_tag == tag);
      }
      ui32 count_block() const {return _count_block;}
      void count_block(ui32 hist) {_count_block = hist;}
    private:
      ui32 _count_block;
      ui32 _tag;
      bool _valid;
      bool _dirty;
  };
  
  class TagSet : public std::vector<TagEntry>
  {
    public:
      TagSet(ui32 count=0):std::vector<TagEntry>(count) { _count_set = 0; }
      ui32 count_set() const { return _count_set; }
      void count_set(ui32 val) { _count_set = val; }
    private:
      ui32 _count_set;
  }; 
  typedef std::vector<TagSet> TagStore;

};

#endif //__TAG_STORE_H__

