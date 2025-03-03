CPSC 3200 Object-Oriented Development Programming Assignment #4
P4 design requires operator overloading and modern C++ memory management
1) Augment type definitions from previous PAs, as noted below
2) Expand the interfaces of ArithSeq, DurableSeq, AsymPattern to include the
overloading of appropriate operators.
a. Focus on external (client) expectations for use of type
b. Remember type definition is concerned with consistency.
Use Contractual design for documentation. DO NOT hard code
Part I: Class Design
Re-write the DurableSeq class from P3 in C++
You do not need to write dispose(), as ofstream’s destructor automatically closes the file.
Update your definition of ArithSeq from P2 to support inheritance, and make any
other needed modifications (as noted in graded P2). Reuse AsymPattern from P2, also
with any needed modifications.
Replace all raw pointers in your classes with smart pointers, choosing the most
appropriate type of smart pointer for each specific use. With the introduction of smart
pointers, you may wish to modify memory management details designed in P2.
Suppress copying of AsymPattern objects. You choose whether to allow or suppress
copying of DurableSeq; justify your decision in your implementation invariants. 
Copying of ArithSeq carries over from P2, with any needed modifications. 
You may use STL smart pointers but NOT STL containers (vector, map, etc.).
The following operators MUST be implemented in each class.
(== and !=) 
++ (pre and post) 
-- (pre and post)
[] the index operator
Fully support ‘addition’ for at least one class -design a consistent interface for client
Overload << for at least one class Explain why or why not >> is overloaded.
Contractual Design
Overloading an expected operator in an appropriate manner increases abstraction and
readability. Consider existing methods when writing overloaded operators. If an existing
method already provides the behavior expected of an operator, overloading the operator
may increase abstraction and may be easily implemented via call forwarding. Add a
justification for each operator to your implementation invariants, explaining why that
operator is appropriate for the class.
Distinguish between destructive and non-destructive operators. 
Part II: Driver -- unit testing is not required or expected.
Do NOT use cin in your driver.
Driver specifics: 
1) Design a functionally decomposed driver to demonstrate program requirements
2) Illustrate (test):
a. Design modifications
b. Overloaded operators – invoke either directly in the driver or indirectly
c. Correct implementation of deep copying
3) Instantiate several instances of AsymPattern with a variety of different configurations
of ArithSeqs (all ArithSeqs, a mix of ArithSeqs and DurableSeqs).
4) Test all overloaded operators.
Upload your individual files to Canvas: NO zip file
