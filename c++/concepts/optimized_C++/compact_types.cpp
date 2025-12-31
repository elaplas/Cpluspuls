/*
how much memory the following type is consuming and how to make it more comapct?
*/

struct A
{
    char c;
    double d;
    int i;
    bool b;
};


/* The alignment of the struct is equal to the size of the biggest member variable so in this case is 
d, which 8 bytes. The size of the struct is a multiple of 8 bytes: 

struct A
{
    char c;  // 8 byte (1 bytes for c and the remaining 7 bytes are padded because for the next member variable we need 8 bytes and the alignment is 8 bytes too)
    double d; // 8 bytes
    int i; // 4 bytes
    bool b; // 4 byte (one byte is allocated from the remaining bytes after allocating for i. The three reamining bytes are padded.)
};

so 24 bytes are reserved for this strcut. By reordering the member variables we can save some memory because the
they can fit better to a mutiple of alignment. 
**/




struct AImproved
{
    double d; // 8 bytes
    int i;  // 4 bytes
    char c; // 1 byte
    bool b; // 2 bytes (i, c and b accomedate to 7 bytes. The last remaining byte is padded)
};

