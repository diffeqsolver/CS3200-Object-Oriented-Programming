CPSC 3200: Object-Oriented Development - Programming Assignment 4
Overview
This repository contains the implementation for Programming Assignment 4 (P4) in CPSC 3200: Object-Oriented Development.
The assignment focuses on operator overloading and modern C++ memory management, 
ensuring proper use of smart pointers while maintaining object-oriented principles.

Objectives
Extend previous class definitions (ArithSeq, DurableSeq, AsymPattern) with operator overloading.
Implement smart pointers (std::unique_ptr, std::shared_ptr) for safe memory management.
Suppress or allow object copying where appropriate, justifying design decisions.
Follow contractual design principles for operator overloading to improve abstraction and usability.
Key Features
Class Redesign:
DurableSeq rewritten from P3 with smart pointers.
ArithSeq updated to support inheritance.
AsymPattern reused with necessary modifications.
Operator Overloading:
==, !=, ++, --, [], and + implemented for relevant classes.
<< overloaded for at least one class (with reasoning on >> omission).
Memory Management:
Replaced raw pointers with appropriate smart pointers.
No STL containers (vector, map, etc.) are used.
Testing & Driver:
Functionally decomposed driver to demonstrate program requirements.
Tests operator overloading, deep copying, and various class configurations.
