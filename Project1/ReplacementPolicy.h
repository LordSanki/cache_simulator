#ifndef __REPLACEMENT_POLICY_H__
#define __REPLACEMENT_POLICY_H__

#include <CustomTypes.h>
#include <TagStore.h>
#include <exception>
#include <iostream>
namespace CacheSimulator
{
  namespace ReplacementPolicy
  {
    enum Types
    {
      e_LRU=0,
      e_LFU=1
    };

    void initLRU(TagSets &sets)
    {
      ui32 i=sets.size()-1;
      for(TagSets::iterator it = sets.begin();
          it != sets.end(); it++)
      {
        it->history(i--);
      }
    }
    TagEntry & findLRU(TagSets &sets)
    {
#if 0
      return sets.front();
#else
      ui32 max_index = sets.size() -1;
      for(TagSets::iterator it = sets.begin();
          it != sets.end(); it++)
      {
        if(it->history() == max_index)
          return (*it);
      }
      throw "Unable to find LRU candidate";
      return TagEntry::invalidTag();
#endif
    }
    TagEntry & findLFU(TagSets &sets)
    {
      return TagEntry::invalidTag();
    }
    void updateLRU(TagSets &sets, TagEntry &ref)
    {
      for(TagSets::iterator it = sets.begin();
          it != sets.end(); it++)
      {
        TagEntry &tag = (*it);

        if( tag.history() < ref.history() )
        {
          tag.history( tag.history() + 1 );
        }
      }
      ref.history(0);
    }
    void updateLFU(TagSets &sets, TagEntry &ref)
    {
    }
  };
};

#endif //__REPLACEMENT_POLICY_H__

