#ifndef __TAG_STORE_H__
#define __TAG_STORE_H__

#include <vector>
#include <list>

namespace CacheSimulator
{
#define UNDEFINED_HISTORY 666
  class TagEntry
  {
    public:
      TagEntry(ui32 tag) 
      {
        _dirty = false;
        _valid = true;
        _tag = tag;
        _history = UNDEFINED_HISTORY;
      }
      TagEntry()
      {
        _valid = false;
        _dirty = false;
        _tag = 0U;
        _history = UNDEFINED_HISTORY;
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
      ui32 history() const {return _history;}
      void history(ui32 hist) {_history = hist;}
    private:
      ui32 _history;
      ui32 _tag;
      bool _valid;
      bool _dirty;
  };

  typedef std::list<TagEntry> TagSets;
  typedef std::vector<TagSets> TagStore;

};

#endif //__TAG_STORE_H__

