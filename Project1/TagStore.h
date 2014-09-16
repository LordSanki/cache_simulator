#ifndef __TAG_STORE_H__
#define __TAG_STORE_H__

#include <vector>
#include <list>

namespace CacheSimulator
{
  class TagEntry
  {
    public:
      TagEntry(ui32 tag) 
      {
        _dirty = false;
        _valid = true;
        _tag = tag; 
      }
      TagEntry()
      {
        _valid = false;
        _dirty = false;
        _tag = 0U;
      }
      ui32 tag() const {return _tag;}
      void read() { }
      void write() { _dirty = true; }
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
    private:
      ui32 _tag;
      bool _valid;
      bool _dirty;
  };

  typedef std::vector<TagEntry> TagStore;
  typedef std::list<TagStore> AssociateTagStore;

};

#endif //__TAG_STORE_H__

