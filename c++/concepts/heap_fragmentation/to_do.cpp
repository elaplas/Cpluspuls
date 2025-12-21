what is heap fragmentation? show it by example?

Imagine there is a large chunk of memory consisting of many blocks. The memory blocks are allocated
and deallocated randomly. After enough random allocating and deallocating, the free memory blocks
might be scattered. If there would be 10 free memory blocks, none of them are next to each other os we 
can allocate e.g. 4 contigious blocks of memory. 

Fragmentation usually occurs when the memory is frequently allocated and freed. 