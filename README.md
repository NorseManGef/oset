You are on an application development team and the architect has come up with a system design which requires a custom data structure. This custom structure will require O(1) runtime to insert and remove objects from it, but also support both forward and backward iteration in the order items were added to the structure. It have functions to provide the number of elements and convert it to a string representation. Design and implement this structure.

This structure should be iterable.

The stream insertion operator should create a string representation of this structure which is a comma-separated list in brackets:
[1, 2, 3, 4, 5]

The structure should not allow the same object to be inserted twice.