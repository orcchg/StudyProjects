#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

struct Chunk {
  void init(size_t block_size, unsigned char blocks_count);
  void* allocate(size_t size, size_t block_size);
  void deallocate(void* ptr, size_t block_size);
  void release();

  unsigned char* data;
  unsigned char first_available_block;
  unsigned char available_blocks_count;
};

class FixedAllocator {
public:
  allocate();
  deallocate();

private:
  vector<Chunk> chunks;
};

class SmallObjAllocator {

};

class SmallObject {
  //
};
