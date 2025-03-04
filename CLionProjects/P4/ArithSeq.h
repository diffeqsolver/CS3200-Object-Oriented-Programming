#ifndef ARITHSEQ_H
#define ARITHSEQ_H
#include <memory>

/* Class Invariant
 *
 * ArithSeq represents an arithmetic sequence defined by a first term, common difference, and length.
 * The sequence is generated dynamically using std::shared_ptr<int[]>, ensuring proper memory management.
 * The sequence allows controlled modifications, subject to an operation limit (maxOperations).
 * Copying is supported and implemented as a deep copy, ensuring independent instances.
 * Move semantics are supported for efficient resource transfer.
 * Operator overloads (++, --, [], +, ==, !=) allow intuitive interactions with sequence elements.
 * The class ensures index validity checks and operation count enforcement to prevent excessive modifications.
 *
 * Public Method Functionality:
 * operator[](int index): Retrieves the value at the specified index; throws an exception if the index is invalid.
 * getKthVal(int k): Returns the k-th value in the sequence, respecting the maxOperations limit.
 * evenlyDividedBy(int n): Counts how many terms in the sequence are divisible by n.
 * modifyEveryPthValue(int p, int q): Increments every p-th term by q, if operation limits allow.
 * reset(): Resets the sequence to its original values and resets operationCount to 0.
 * getLength(): Returns the length of the sequence.
 * operator+ (ArithSeq&): Adds corresponding terms of two sequences of equal length.
 *
 */

class ArithSeq {
public:

    // Pre-condition: length and maxOperations must be positive.
    // Post-condition: Initializes an arithmetic sequence with the given parameters,
    // allocates memory for sequence and fills it using generateSequence().
    ArithSeq(int firstTerm, int commonDiff, int length, int maxOperations);

    // Pre-condition: other must be a valid ArithSeq object.
    // Post-condition: Moves ownership of sequence and data from other,
    // other is left in a valid but empty state.
    ArithSeq &operator=(ArithSeq &&other) noexcept;

    // Pre-condition: other must be a valid ArithSeq object.
    // Post-condition: Copies data from other into the current object,
    // performs deep copy to ensure independent sequences.
    ArithSeq &operator=(const ArithSeq &other) noexcept;

    // Pre-condition: other must be a valid ArithSeq object.
    // Post-condition: Moves ownership of sequence and data from other,
    // other is left in a valid but empty state.
    ArithSeq(ArithSeq &&other) noexcept;

    // Pre-condition: other must be a valid ArithSeq object.
    // Post-condition: Performs deep copy of other’s sequence and data.
    ArithSeq(const ArithSeq &other) noexcept;

    // Pre-condition: None.
    // Post-condition: Generates an arithmetic sequence based on firstTerm and commonDiff.
    void generateSequence();

    // Pre-condition: None.
    // Post-condition: Returns the length of the sequence.
    virtual int getLength();

    // Pre-condition: None.
    // Post-condition: Resets sequence to its original state,
    // resets operation count to zero.
    virtual void reset();

    // Pre-condition: k must be a valid index (0 ≤ k < length).
    // Pre-condition: Operation count must be within limits,
    // returns the k-th value in the sequence.
    int getKthVal(int k);

    // Pre-condition: n must be non-zero.
    // Pre-condition: Operation count must be within limits,
    // returns the count of terms divisible by n.
    int evenlyDividedBy(int n);

    // Pre-condition: p must be a valid step (0 < p < length).
    // Pre-condition: Operation count must be within limits,
    // increments every p-th value in the sequence by q.
    virtual void modifyEveryPthValue(int p, int q);

    // Pre-condition: Both ArithSeq objects must have the same length.
    // Post-condition: Adds corresponding terms of the sequences.
    ArithSeq &operator+(ArithSeq &other);

    // Pre-condition: None.
    // Post-condition: Returns true if two sequences have identical parameters.
    bool operator==(const ArithSeq &other) const;

    // Pre-condition: None.
    // Post-condition: Returns true if two sequences differ in parameters or values.
    bool operator!=(const ArithSeq &other) const;

    // Pre-condition: None.
    // Post-condition: Increments each element of the sequence by 1.
    ArithSeq &operator++();

    // Pre-condition: None.
    // Post-condition: Increments each element of the sequence by 1,
    // returns the original sequence before modification.
    ArithSeq operator++(int);

    // Pre-condition: None.
    // Post-condition: Decrements each element of the sequence by 1.
    ArithSeq &operator--();

    // Pre-condition: None.
    // Post-condition: Decrements each element of the sequence by 1,
    // returns the original sequence before modification.
    ArithSeq operator--(int);

    // Pre-condition: index must be within range (0 ≤ index < length).
    // Post-condition: Returns a copy of the value at the given index.
    int operator[](int index);

protected:
    std::shared_ptr<int[]> sequence;
    int operationCount;
    int maxOperations;
    int commonDiff;
    int firstTerm;
    int length;

private:

    // Pre-condition: None.
    // Post-condition: Returns true if operation count has not exceeded maxOperations.
    bool checkOperationLimit();

    // Pre-condition: other must be a valid ArithSeq object.
    // Post-condition: Performs deep copy from other.
    void copy(const ArithSeq &other) noexcept;
};

/* Implementation Invariant
 *
 * The sequence is allocated dynamically via std::shared_ptr<int[]>, avoiding manual memory deallocation.
 * The constructor initializes the sequence and enforces positive, nonzero values for length and maxOperations.
 * Copy constructor and assignment operator perform deep copies, ensuring data integrity across instances.
 * Move constructor and assignment operator transfer ownership, resetting the source object to a valid empty state.
 * Arithmetic operations (++, --, +) modify the sequence in place while respecting the maxOperations constraint.
 * operator[] returns values by copy, preventing accidental modifications.
 * generateSequence() initializes values according to the arithmetic progression formula.
 * modifyEveryPthValue() ensures valid index bounds before modifying elements.
 * getKthVal() and evenlyDividedBy() enforce operation count limits before executing computations.
 * Exception safety is ensured by validating parameters in methods that modify or retrieve sequence elements.
 *
 */

#endif //ARITHSEQ_H
