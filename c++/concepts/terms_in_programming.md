incomplete type: 

A class that has been declared but not defined, an enumeration type in certain contexts ([dcl.enum]), or an array of unknown bound 
or of incomplete element type, is an incompletely-defined object type. Incompletely-defined object types and cv void are incomplete
types ([basic.fundamental]). Objects shall not be defined to have an incomplete type.

Contianer: 

- It stores objects in an organized way that follows specific access rules.

- Containers can be characterized by the following three properties:

access: that is the way of accessing the objects of the container. Arrays by array indexing, Stacks by LIFO and Queue by FIFO 
storage: that is the way of storing the objects of the container 
traversal: that is the way of traversing the objects of the container.

- Container classes are expected to implement CRUD-like ( create,read, update and delete) methods

Sequence container:

- The elements can be accessed sequentially 
- Examples are array, vector, forward-list, doubly liked list, queue, dequeue, ...
- Insertion to and deletion from the end of container is constant time
- Insertion to and deletion is linear time

Associative contianer: 

- Elements are stored as key-value pairs 
- Elements follow strict weak ordering 
- Examples are set (key and value are the same), map
- Insertion to and deletion from the end of container is O(log n)
- Insertion to and deletion is constant time in best case and linear in worse case

Allocator aware container:

- It holds an instance of an allocator and uses it in all ist member functions to allocate and deallocate memory and construct and destroy objects

Allocator:

- Encapsulates strategies for accessing/addressing, allocation/deallocation and construction/destruction of objects
- All standard lib components, except array, allocate and release memory through allocators

Void:
- It doesn't have any types. If you cast a type to void, its type is removed and it becomes typeless
- Void pointer cannot be dereferenced because it doesn't hold ayn values
- Void pointer has no type associated with it