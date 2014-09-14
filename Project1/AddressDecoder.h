#ifndef __ADDRESS_DECODER_H__
#define __ADDRESS_DECODER_H__

#include <CustomTypes.h>
#include <cmath>

# define DEFAULT_ADDR_SIZE    32U
namespace CacheSimulator
{
  class AddressHelper
  {
    public:
      // parameterized constructor for variable address size
      AddressHelper(ui16 sets, ui16 block_size, ui8 address_size)
      {
        init(sets, block_size, address_size);
      }
      // parameterized constructor assuming 32 bit addresses
      AddressHelper(ui16 sets, ui16 block_size)
      {
        init(sets, block_size, DEFAULT_ADDR_SIZE);
      }
      // function to get tag
      ui32 tag(ui32 addr);
      // function to get index
      ui32 index(ui32 addr);
      // function to get block offset
      ui32 bo(ui32 addr);
    private:
      // no of tag bits = address_size - (index_bits + blockoffset_bits)
      ui16 _tagBits;
      // no of index bits = log2(sets)
      ui16 _indexBits;
      // no of blockoffset bits = log2(block_size)
      ui16 _boBits;
      // bit mask for extracting tag bits
      ui32 _tagMask;
      // bit mask for extracting index bits
      ui32 _indexMask;
      // bit mask for extracting blockoffset bits
      ui32 _boMask;
    private:
      ui16 find_log2(ui16 val)
      {
        ui16 count = 1;
        for(ui16 i=0; i<15; i++)
        {
          if(count == val)
            break;
          count = count*2;
        }
        return i;
      }
      void init(ui16 sets, ui16 block_size, ui8 address_size)
      {
        _boBits = find_log2(block_size);
        _indexBits = find_log2(sets);
        _tagBits = address_size - (_boBits + _indexBits);

      }
  };
};

#endif //__ADDRESS_DECODER_H__

