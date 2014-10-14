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
  
  typedef std::list<TagEntry>::iterator TagSetIter;
  typedef std::list<TagEntry>::reverse_iterator TagSetRIter;
  class TagSet
  {
    public:
      TagSet(ui32 count=0):_entries(count) { _count_set = 0; }
      ui32 size() const { return _entries.size(); }
      ui32 count_set() const { return _count_set; }
      void count_set(ui32 val) { _count_set = val; }
      TagSetIter begin() { return _entries.begin(); }
      TagSetIter end() { return _entries.end(); }
      TagSetRIter rbegin() { return _entries.rbegin(); }
      TagSetRIter rend() { return _entries.rend(); }
    private:
      ui32 _count_set;
      std::list<TagEntry> _entries;
  }; 
  typedef std::vector<TagSet> TagStore;

};

#endif //__TAG_STORE_H__

