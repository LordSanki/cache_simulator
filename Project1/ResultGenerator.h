#ifndef __RESULT_GENERATOR_H__
#define __RESULT_GENERATOR_H__

#include <Memory.h>
#include <Cache.h>
#include <iostream>
#include <iomanip>
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
      void operator<<(Cache* mem)
      {
        ui32 a,b,c,d;
        f32 e;

        std::cout<<"===== Simulator configuration ====="<<std::endl;
        std::cout<<"L1_BLOCKSIZE:          "<<mem->_blocksize<<std::endl;
        std::cout<<"L1_SIZE:               "<<mem->_size<<std::endl;
        std::cout<<"L1_ASSOC:              "<<mem->_assoc<<std::endl;
        std::cout<<"L1_REPLACEMENT_POLICY: "<<mem->rPolicy()<<std::endl;
        std::cout<<"L1_WRITE_POLICY:       "<<mem->wPolicy()<<std::endl;
        std::cout<<"trace_file:            "<<_argv[6]<<std::endl;
        std::cout<<"==================================="<<std::endl;
        std::cout<<std::endl;
        std::cout<<"===== "<<mem->name()<<" contents ====="<<std::endl;
        TagStore & tag_store = mem->_tags.front();
        for(ui32 i=0; i<tag_store.size(); i++)
        {
          std::cout<<"set  "<<i<<":"<<"   "<<std::hex<<tag_store[i].tag()<<std::dec;
          if(tag_store[i].dirty())
            std::cout<<" D"<<std::endl;
          else
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
        std::cout<<"e. L1 miss rate:                 "<< e    <<std::endl;
        std::cout<<"f. number of writebacks from L1: "<< mem->wbacks() <<std::endl;
        std::cout<<"g. total memory traffic:         "<< main->writes() + main->reads() <<std::endl;

      }
    private:
      c8 **_argv;
      i32 _argc;
  };
};

#endif //__RESULT_GENERATOR_H__

