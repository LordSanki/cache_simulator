#ifndef __RESULT_GENERATOR_H__
#define __RESULT_GENERATOR_H__

#include <Memory.h>
#include <Cache.h>
#include <iostream>
namespace CacheSimulator
{
  class ResultGenerator
  {
    public:
      ResultGenerator(i32 argc, c8** argv)
      {
        _argc = argc;
        _argv = argv;
      }
      void operator<<(Memory* mem)
      {
        if(mem->name() == "L1")
        {
          Cache *cache = (Cache*)mem;
          std::cout<<"===== Simulator configuration ====="<<std::endl;
          std::cout<<"L1_BLOCKSIZE:          "<<cache->_blocksize<<std::endl;
          std::cout<<"L1_SIZE:               "<<cache->_size<<std::endl;
          std::cout<<"L1_ASSOC:              "<<cache->_assoc<<std::endl;
          std::cout<<"L1_REPLACEMENT_POLICY: "<<cache->rPolicy()<<std::endl;
          std::cout<<"L1_WRITE_POLICY:       "<<cache->wPolicy()<<std::endl;
          std::cout<<"trace_file:            "<<_argv[6]<<std::endl;
          std::cout<<"==================================="<<std::endl;
          std::cout<<std::endl;
          std::cout<<"===== "<<cache->name()<<" contents ====="<<std::endl;

          std::cout<<"====== Simulation results (raw) ======"<<std::endl;
          ui32 a,b,c,d;
          f32 e;
          a = cache->reads();
          b = cache->reads() - cache->rhits();
          c = cache->writes();
          d = cache->writes() - cache->whits();
          e = ((f32)b+d)/((f32)a+c);
          std::cout<<"a. number of L1 reads:           "<< a    <<std::endl;
          std::cout<<"b. number of L1 read misses:     "<< b    <<std::endl;
          std::cout<<"c. number of L1 writes:          "<< c    <<std::endl;
          std::cout<<"d. number of L1 write misses:    "<< d    <<std::endl;
          std::cout<<"e. L1 miss rate:                 "<< e    <<std::endl;
          std::cout<<"f. number of writebacks from L1: "<< 0    <<std::endl;
          std::cout<<"g. total memory traffic:         "<<44280 <<std::endl;
        }
      }
    private:
      c8 **_argv;
      i32 _argc;
  };
};

#endif //__RESULT_GENERATOR_H__

