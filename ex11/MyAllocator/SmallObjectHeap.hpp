#ifndef SMALL_OBJECT_HEAP_HPP_INCLUDED
#define SMALL_OBJECT_HEAP_HPP_INCLUDED

#include <vector>

namespace details
{

	class Page
	{
	public:
		// allocate memory and initialize page
		void initialize( std::size_t blockSize, unsigned char blocks );

		// release memory
		void release();

		// return number of free block in page
		unsigned char blocksFree() const { return blocksAvailable_; }

		// return number og blocks in page
		unsigned char maxBlocks() const  { return maxBlocks_; }

		// is p allocated from this page
		bool isBlockInPage( void* p ) const	{ return p >= data_ && p < data_ + maxBlocks_*blockSize_; }

		// allocate block from page. Return NULL if no block is avaible
		void* allocate();

		// free block. Only pointers previously allocated with allocate are leagel
		void deallocate( void* p );

	private:
		unsigned char* data_;
		std::size_t blockSize_;
		unsigned char firstAvailableBlock_;
		unsigned char blocksAvailable_;
		unsigned char maxBlocks_;
	};

	inline void Page::initialize( std::size_t blockSize, unsigned char blocks )
	{
		data_ = new unsigned char[ blockSize * blocks ];

		blockSize_ = blockSize;
		firstAvailableBlock_ = 0;
		blocksAvailable_ = blocks;
		maxBlocks_ = blocks;

		unsigned char i = 0;
		for( unsigned char* p = data_; i != blocks; p += blockSize )
		{
			*p = ++i;
		}
	}

	inline void Page::release()
	{
		delete[] data_;
	}

	inline void* Page::allocate()
	{
		if( !blocksAvailable_ ) return 0;

		unsigned char* result = data_ + ( firstAvailableBlock_ * blockSize_ );
		firstAvailableBlock_ = *result;
		--blocksAvailable_;

		return result;
	}

	inline void Page::deallocate( void* p )
	{
		unsigned char* toRelease = static_cast<unsigned char*>( p );

		*toRelease = firstAvailableBlock_;
		firstAvailableBlock_ = static_cast<unsigned char>( ( toRelease - data_ ) / blockSize_ );

		++blocksAvailable_;
	}

} // namespace details


template <std::size_t objSize, int pageSize = 100>

class SmallObjectHeap{

public:
    //default parameter for page size allows user to use a fitting page size to avoid internal fragmentation
    static SmallObjectHeap<objSize, pageSize>* getInstance(){
        return &instance;
    }

    void* allocate(){
        for(auto i: pageList){
            if(i->blocksFree() > 0) return i->allocate();
        }
        pageList.pushBack(Page());
        pageList.back().initialize(objSize, pageSize);
        return pageList.back().allocate();
    }

    
private:
    SmallObjectHeap(){}
    std::list<Page> pageList;
    static SmallObjectHeap<objSize, pageSize> instance();
};

#endif	// SMALL_OBJECT_HEAP_HPP_INCLUDED
