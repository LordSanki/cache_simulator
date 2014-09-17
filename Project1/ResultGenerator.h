#ifndef __RESULT_GENERATOR_H__
#define __RESULT_GENERATOR_H__

#include <Memory.h>
#include <Cache.h>
#include <iostream>
#include <iomanip>
#include <cmath>
namespace CacheSimulator
{
#define ROUNDFACTOR 10000
  class ResultGenerator
  {
    public:
      ResultGenerator(i32 argc, c8** argv)
      {
        _argc = argc;
        _argv = argv;
      }
      void operator<<(Cache* mem)
      {
        ui32 a,b,c,d;
        f32 e;

        std::cout<<"===== Simulator configuration ====="<<std::endl;
        std::cout<<"L1_BLOCKSIZE:          "<<mem->blocksize()<<std::endl;
        std::cout<<"L1_SIZE:               "<<mem->size()<<std::endl;
        std::cout<<"L1_ASSOC:              "<<mem->assoc()<<std::endl;
        std::cout<<"L1_REPLACEMENT_POLICY: "<<mem->rPolicy()<<std::endl;
        std::cout<<"L1_WRITE_POLICY:       "<<mem->wPolicy()<<std::endl;
        std::cout<<"trace_file:            "<<_argv[6]<<std::endl;
        std::cout<<"==================================="<<std::endl;
        std::cout<<std::endl;
        std::cout<<"===== "<<mem->name()<<" contents ====="<<std::endl;

        for(ui32 i=0; i<mem->sets(); i++)
        {
          TagSets &sets = mem->_tags[i];
          std::cout<<"set  "<<i<<":";
          for(TagSets::const_iterator it = sets.begin();
              it != sets.end(); it++)
          {
            const TagEntry &tag = (*it);
            std::cout<<"   "<<std::hex<<tag.tag()<<std::dec;
            if(tag.dirty())
              std::cout<<" D";
          }
          std::cout<<std::endl;
        }

        std::cout<<"====== Simulation results (raw) ======"<<std::endl;
        a = mem->reads();
        b = mem->reads() - mem->rhits();
        c = mem->writes();
        d = mem->writes() - mem->whits();
        e = ((f32)b+d)/((f32)a+c);

        // Traversing to the main memory which is always the last element.
        Memory *main = mem;
        while(main->next()) main = main->next();

        std::cout<<"a. number of L1 reads:           "<< a    <<std::endl;
        std::cout<<"b. number of L1 read misses:     "<< b    <<std::endl;
        std::cout<<"c. number of L1 writes:          "<< c    <<std::endl;
        std::cout<<"d. number of L1 write misses:    "<< d    <<std::endl;
        std::cout<<"e. L1 miss rate:                 "<< roundf(e * ROUNDFACTOR)/ROUNDFACTOR    <<std::endl;
        std::cout<<"f. number of writebacks from L1: "<< mem->wbacks() <<std::endl;
        std::cout<<"g. total memory traffic:         "<< main->writes() + main->reads() <<std::endl;

        f64 l1_hit_time = (mem->rhits() + mem->whits())
          *(0.25 + 2.5 * (mem->size() / (512*1024)) 
           + 0.025 * (mem->blocksize()/16) + 0.025 * mem->assoc());
        f64 l1_miss_time = (b+d)*(20 + 0.5*(mem->blocksize() / 16 ));
        //f64 l2_hit_time = 2.5ns + 2.5ns * (L2_Cache Size / 512kB) + 0.025ns * (L2_BLOCKSIZE / 16B) + 0.025ns * L2_SET_ASSOCIATIVITY;
        //f64 l2_miss_time =  20 ns + 0.5*(L2_BLOCKSIZE / 16 B/ns);
        std::cout<<"==== Simulation results (performance) ===="<<std::endl;
        std::cout<<"1. average access time:         "<<(l1_hit_time+l1_miss_time)/(a+c)<<" ns"<<std::endl;
      }
    private:
      c8 **_argv;
      i32 _argc;
  };
};

#endif //__RESULT_GENERATOR_H__

