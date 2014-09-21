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
        ui32 a,b,c,d, f, g;
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

        for(ui32 i=0; i<mem->set(); i++)
        {
          TagSet &set = mem->_tags[i];
          std::cout<<"set  "<<i<<":";
          for(TagSetIter it = set.begin(); it != set.end(); it++)
          {
            std::cout<<"   "<<std::hex<<it->tag()<<std::dec;
            if(it->dirty())
              std::cout<<" D";
          }
          std::cout<<std::endl;
        }

        Memory *main = mem;
        while(main->next()) main = main->next();

        std::cout<<"====== Simulation results (raw) ======"<<std::endl;
        a = mem->reads();
        b = mem->reads() - mem->rhits();
        c = mem->writes();
        d = mem->writes() - mem->whits();
        e = round_to( ((f64)b+d)/(a+c), 4U);
        f = mem->wbacks();
        g = main->writes() + main->reads();
        // Traversing to the main memory which is always the last element.

        std::cout<<"a. number of L1 reads:           "<< a <<std::endl;
        std::cout<<"b. number of L1 read misses:     "<< b <<std::endl;
        std::cout<<"c. number of L1 writes:          "<< c <<std::endl;
        std::cout<<"d. number of L1 write misses:    "<< d <<std::endl;
        std::cout<<"e. L1 miss rate:                 "<< e <<std::endl;
        std::cout<<"f. number of writebacks from L1: "<< f <<std::endl;
        std::cout<<"g. total memory traffic:         "<< g <<std::endl;

#if 1
        f64 l1_hit_time = (0.25 + 2.5 * (mem->size() / (512.0f*1024))
            + 0.025 * (mem->blocksize()/16.0f) + 0.025 * mem->assoc());
        f64 l1_miss_time = (20.0f + 0.5*(mem->blocksize() / 16.0f ));
        f64 avg_access_time = l1_hit_time + (((f64)b+d)/(a+c) * l1_miss_time);
#else
        f64 l1_hit_time = ((a+c))
          *(0.25 + 2.5 * (mem->size() / (512.0f*1024)) 
           + 0.025 * (mem->blocksize()/16.0f) + 0.025 * mem->assoc());
        f64 l1_miss_time = (b+d)*(20.0f + 0.5*(mem->blocksize() / 16.0f ));
        //f64 l2_hit_time = 2.5ns + 2.5ns * (L2_Cache Size / 512kB) + 0.025ns * (L2_BLOCKSIZE / 16B) + 0.025ns * L2_SET_ASSOCIATIVITY;
        //f64 l2_miss_time =  20 ns + 0.5*(L2_BLOCKSIZE / 16 B/ns);
        
        f64 avg_access_time = (l1_hit_time+l1_miss_time)/(a+c);
#endif
        avg_access_time = round_to(avg_access_time, 4U);
        std::cout<<"==== Simulation results (performance) ===="<<std::endl;
        std::cout<<"1. average access time:         "<< avg_access_time <<" ns"<<std::endl;
      }
    private:
      c8 **_argv;
      i32 _argc;
      f64 round_to(f64 val, ui32 digits)
      {
        ui32 factor = 1U;
        while(digits !=0)
        {
          factor = factor*10U;
          digits--;
        }
        return (round(val*factor)/factor);
      }
  };
};

#endif //__RESULT_GENERATOR_H__

