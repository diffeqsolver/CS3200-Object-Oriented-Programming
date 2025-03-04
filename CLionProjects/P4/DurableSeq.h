#ifndef DURABLESEQ_H
#define DURABLESEQ_H

#include "ArithSeq.h"
#include <string>

/* Class Invariant
 *
 * DurableSeq extends ArithSeq, adding file persistence functionality.
 * Every DurableSeq instance is associated with a file (filePath), where its state is stored.
 * isDirty flag is used to track modifications; changes are only saved when necessary.
 * Supports deep copying with a new unique file path for each copied object.
 * Move semantics allow efficient resource transfer.
 * Operator overloads (++, --, [], ==, !=) allow intuitive interactions.
 * File operations (saveToFile() and loadFromFile()) ensure persistence across instances.
 *
 * Public Method Functionality & Client Expectations:
 * operator[](int index): Retrieves the value at the specified index; writes to file **only if modified**.
 * modifyEveryPthValue(int p, int q): Updates sequence values and marks instance as dirty (triggers save).
 * reset(): Restores sequence from file if available; otherwise, regenerates it.
 * getLength(): Returns sequence length.
 * getFilePath(): Returns the current file path.
 * forceSave(): Forces immediate write to file, regardless of isDirty flag.
 * operator==(const DurableSeq&): Compares sequences, ignoring file paths.
 * operator!= (const DurableSeq&): Returns true if sequences differ.
 * operator++/-- (pre & post): Increments/decrements all values and sets isDirty = true to indicate file needs updating.
 * << and >> operators: Handle serialization and deserialization of the sequence to/from file.
 * 
 */

class DurableSeq : public ArithSeq {
public:

    // Pre-condition: firstTerm, commonDiff, length, and maxOperations must be valid integers,
    // filePath must be a valid string representing a writable file.
    // Post-condition: Initializes a DurableSeq instance and writes sequence to file,
    // deletes any pre-existing file with the same name.
    DurableSeq(int firstTerm, int commonDiff, int length, int maxOperations, const std::string &filePath);

    // Pre-condition: other must be a valid DurableSeq object.
    // Post-condition: Performs a deep copy of other, ensuring a new file path
    // saves the copied sequence to a new file.
    DurableSeq(const DurableSeq &other) noexcept;

    // Pre-condition: other must be a valid DurableSeq object.
    // Post-condition: Copies data from other, ensuring a unique file path
    // saves the copied sequence to a new file.
    DurableSeq &operator=(const DurableSeq &other) noexcept;

    // Pre-condition: other must be a valid DurableSeq object.
    // Post-condition: Moves ownership of sequence and file path from other,
    // leaves other in a valid but empty state.
    DurableSeq(DurableSeq &&other) noexcept;

    // Pre-condition: other must be a valid DurableSeq object.
    // Post-condition: Moves ownership of sequence and file path from other.
    // leaves other in a valid but empty state.
    DurableSeq &operator=(DurableSeq &&other) noexcept;

    // Pre-condition: None.
    // Post-condition: If isDirty is true, writes the current sequence to file.
    ~DurableSeq();

    // Pre-condition: None.
    // Post-condition: Returns the length of the sequence.
    int getLength() override;

    // Pre-condition: None.
    // Post-condition: Returns the file path associated with this DurableSeq instance.
    std::string getFilePath();

    // Pre-condition: p must be a valid step (0 < p < length),
    // operation count must be within limits.
    // Post-condition: Modifies every p-th value in the sequence by q,
    // marks the sequence as dirty (isDirty = true).
    void modifyEveryPthValue(int p, int q) override;

    // Pre-condition: None.
    // Post-condition: If a valid file exists, reloads the sequence from the file,
    // if no file exists, resets the sequence and saves it to the file,
    // clears isDirty flag after restoring the sequence.
    void reset() override;

    // Pre-condition: None.
    // Post-condition: Writes the current sequence to file **even if isDirty is false**.
    void forceSave();

    // Pre-condition: Both DurableSeq objects must be properly initialized.
    // Post-condition: Returns true if the sequences have identical terms and parameters (ignores file path).
    bool operator==(const DurableSeq &other) const;

    // Pre-condition: Both DurableSeq objects must be properly initialized.
    // Post-condition: Returns true if the sequences differ in terms or parameters.
    bool operator!=(const DurableSeq &other) const;

    // Pre-condition: None.
    // Post-condition: Increments each element in the sequence by 1,
    // marks the sequence as dirty (isDirty = true).
    DurableSeq &operator++();

    // Pre-condition: None.
    // Post-condition: Increments each element in the sequence by 1,
    // returns the original sequence before modification,
    // post-condition: Marks the sequence as dirty (isDirty = true).
    DurableSeq operator++(int);

    // Pre-condition: None.
    // Post-condition: Decrements each element in the sequence by 1,
    // marks the sequence as dirty (isDirty = true).
    DurableSeq &operator--();

    // Pre-condition: None.
    // Post-condition: Decrements each element in the sequence by 1,
    // returns the original sequence before modification,
    // marks the sequence as dirty (isDirty = true).
    DurableSeq operator--(int);

    // Pre-condition: index must be within range (0 ≤ index < length).
    // Post-condition: Returns a copy of the value at the given index,
    // if isDirty is true, writes the current sequence to file before returning.
    int operator[](int index);

    // Pre-condition: None.
    // Post-condition: Writes the sequence to file in a human-readable format.
    friend std::ostream &operator<<(std::ostream &os, const DurableSeq &seq);

    // Pre-condition: Input stream must contain valid sequence data.
    // Post-condition: Reads sequence values from the input stream,
    // ensures sequence length matches expected value.
    friend std::istream &operator>>(std::istream &is, DurableSeq &seq);

private:

    // Pre-condition: None.
    // Post-condition: If isDirty is true, overwrites the file with the current sequence,
    // resets isDirty to false after writing.
    void saveToFile();

    // Pre-condition: The file must exist and be readable.
    // Post-condition: Loads sequence data from the file into memory.
    void loadFromFile();

    std::string filePath;
    bool isDirty = false;
};

/* Implementation Invariant
 *
 * isDirty flag ensures file writes occur **only when necessary**, reducing redundant I/O operations.
 * Constructor deletes an existing file with the same path before writing a new sequence.
 * Copy constructor and assignment create a **new file path** (_copy suffix) to maintain unique persistence.
 * Move constructor and assignment transfer ownership, leaving the original object in a valid but empty state.
 * File writing (saveToFile()) **only occurs when isDirty is true**, reducing unnecessary disk writes.
 * File reading (loadFromFile()) restores the sequence only when needed.
 * reset() restores the original sequence from the file, ensuring consistency.
 * operator[] checks isDirty before writing, preventing redundant writes.
 * << and >> operators allow seamless serialization and deserialization of sequence data.
 * Exception safety is enforced in all file operations to prevent corrupted states.
 * 
 */


#endif //DURABLESEQ_H
