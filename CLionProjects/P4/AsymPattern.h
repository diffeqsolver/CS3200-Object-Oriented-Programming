#ifndef ASYMPATTERN_H
#define ASYMPATTERN_H
#include <memory>
#include "ArithSeq.h"

/* Class Invariant
 *
 *  AsymPattern manages a dynamic array of std::shared_ptr<ArithSeq>, allowing storage of both ArithSeq
 *  and DurableSeq objects while ensuring automatic memory management.
 *  Each sequence is accessed via a **unique integer key**, assigned internally to prevent duplication.
 *  The internal array can be resized when needed, maintaining flexibility.
 *  Operations like operator++, operator--, and modifyEveryPthValue() apply to all contained sequences.
 *  Copying is **disabled** to prevent accidental duplication; move semantics are supported.
 *
 *  Public Method Functionality:
 *  operator[](int key): Retrieves the sequence corresponding to a given key; throws an exception if the key is invalid.
 *  replicateWithNewKey(int key): Creates a deep copy of the sequence at key, assigns it a new unique key,
 *  and adds it to the collection.
 *  reset(): Restores all stored sequences to their original values.
 *
 *  Smart Pointer Justification:
 *  std::shared_ptr is used to manage ArithSeq objects **internally** to ensure proper cleanup when
 *  AsymPattern is destroyed or reassigned.
 *  It prevents memory leaks **without enforcing shared ownership across all AsymPattern instances**.
 *  Each AsymPattern has its own independent set of sequences.
 *
 */

class AsymPattern {
public:

    // Pre-condition: ap must not be nullptr,
    // length must be greater than 0.
    // Post-condition: Initializes the object with length sequences,
    // assigns a unique key to each stored sequence.
    AsymPattern(std::shared_ptr<std::shared_ptr<ArithSeq>[]> &ap, int length);

    // Pre-condition: other must be a valid AsymPattern object.
    // Post-condition: Moves ownership of sequences and keys from other.
    // Post-condition: other is left in a valid but empty state.
    AsymPattern &operator=(AsymPattern &&other) noexcept;

    // Pre-condition: other must be a valid AsymPattern object.
    // Post-condition: Moves ownership of sequences and keys from other,
    // other is left in a valid but empty state.
    AsymPattern(AsymPattern &&other) noexcept;

    // Pre-condition: None.
    // Post-condition: Releases all allocated resources.
    ~AsymPattern() = default;

    // Pre-condition: None.
    // Post-condition: Restores all sequences to their original values,
    // resets length to its initial value.
    void reset();

    // Pre-condition: None.
    // Post-condition: Returns a shared pointer to an array of unique keys.
    std::shared_ptr<int[]> getKeys() const;

    // Pre-condition: replicateKey must exist in the current collection.
    // Post-condition: Creates a deep copy of the sequence at replicateKey,
    // assigns the copy a new unique key and increases length by 1.
    void replicateWithNewKey(int replicateKey);

    // Pre-condition: Both AsymPattern objects must be properly initialized.
    // Post-condition: Returns true if both objects have the same sequences and keys.
    bool operator==(const AsymPattern &other) const;

    // Pre-condition: Both AsymPattern objects must be properly initialized.
    // Post-condition: Returns true if objects have different sequences or keys.
    bool operator!=(const AsymPattern &other) const;

    // Pre-condition: None.
    // Post-condition: Increments every sequence in the collection by 1.
    AsymPattern &operator++();

    // Pre-condition: None.
    // Post-condition: Increments every sequence in the collection by 1,
    // returns a copy of the object before modification.
    AsymPattern operator++(int);

    // Pre-condition: None.
    // Post-condition: Decrements every sequence in the collection by 1.
    AsymPattern &operator--();

    // Pre-condition: None.
    // Post-condition: Decrements every sequence in the collection by 1,
    // returns a copy of the object before modification.
    AsymPattern operator--(int);

    // Pre-condition: key must exist in the collection.
    // Post-condition: Returns a shared pointer to the sequence associated with the key.
    std::shared_ptr<ArithSeq> operator[](int key);

private:
    std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap;
    std::shared_ptr<int[]> keys;
    int originalLength;
    int length;

    // Pre-condition: None.
    // Post-condition: Copying is disabled.
    AsymPattern(const AsymPattern &other) noexcept;

    // Pre-condition: None.
    // Post-condition: Copying is disabled.
    AsymPattern &operator=(const AsymPattern &other) noexcept;

    // Pre-condition: other must be a valid AsymPattern object.
    // Post-condition: Copies data from other into the current object.
    void copy(const AsymPattern &other) noexcept;

    // Pre-condition: None.
    // Post-condition: Returns a new unique key not present in the collection.
    int generateUniqueKey() const;

};

/* Implementation Invariant
 *
 *  std::shared_ptr<std::shared_ptr<ArithSeq>[]> ensures safe dynamic storage and avoids manual memory management.
 *  Unique keys are assigned on insertion (generateUniqueKey() ensures no duplicates).
 *  Copying is **disabled** to prevent duplicated ownership; moving is allowed for efficient transfer.
 *  operator[]` returns a reference to the ArithSeq, allowing modifications.
 *  operator== compares stored sequences and keys, ensuring logical equivalence.
 *  replicateWithNewKey() creates a **new** deep copy of the referenced sequence and assigns it a fresh key.
 *  Exception safety is ensured in constructors and key-based lookups.
 *
 */

#endif //ASYMPATTERN_H
