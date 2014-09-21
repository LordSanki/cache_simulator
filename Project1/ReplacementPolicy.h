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

    void initLRU(TagSet &set)
    {
      ui32 i = set.size()-1;
      for(TagSetIter it = set.begin(); it != set.end(); it++)
      {
        it->count_block(i--);
      }
    }
    void initLFU(TagSet &set)
    {
      set.count_set(0);
/*      for(TagSetIter it = set.begin(); it != set.end(); it++)
      {
        it->count_block(UNDEFINED_COUNT_BLOCK);
      }*/
    }
    TagEntry & findLRU(TagSet &set)
    {
      ui32 max_index = set.size() -1;
      for(TagSetIter it = set.begin(); it != set.end(); it++)
      {
        if(it->count_block() == max_index)
          return *it;
      }
      throw "Unable to find LRU candidate";
      return TagEntry::invalidTag();
    }
    TagEntry & findLFU(TagSet &set)
    {
      TagSetIter lfu = set.begin();
      for(TagSetIter it = set.begin(); it != set.end(); it++)
      {
        if(lfu->count_block() > it->count_block())
        {
          lfu = it;
        }
      }
      set.count_set(lfu->count_block());
      return *lfu;
    }
    void updateLRU(TagSet &set, TagEntry &ref)
    {
      for(TagSetIter it = set.begin(); it != set.end(); it++)
      {
        if( it->count_block() < ref.count_block() )
        {
          it->count_block( it->count_block() + 1 );
        }
      }
      ref.count_block(0);
    }
    void updateLFU(TagSet &set, TagEntry &ref)
    {
      if(ref.count_block() == UNDEFINED_COUNT_BLOCK)
      {
        ref.count_block(set.count_set()+1);
      }
      else
      {
        ref.count_block(ref.count_block()+1);
      }
    }
  };
};

#endif //__REPLACEMENT_POLICY_H__

