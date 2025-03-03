#include "ArithSeq.h"
#include <stdexcept>
#include <memory>
//class invariant - note that [] operator does not allow modification
//as it returs an int by value and not by reference
ArithSeq::ArithSeq(int firstTerm, int commonDiff, int length, int maxOperations) {
    if (length <= 0 || maxOperations <= 0) {
        throw std::invalid_argument("length and maxOperations must be positive");
    }
    this->firstTerm = firstTerm;
    this->commonDiff = commonDiff;
    this->length = length;
    this->maxOperations = maxOperations;
    operationCount = 0;
    this->sequence = std::shared_ptr<int[]>(new int[length]);
    generateSequence();
}

void ArithSeq::generateSequence() {
    for (int i = 0; i < length; i++) {
        sequence[i] = firstTerm + (i * commonDiff);
    }
}

void ArithSeq::copy(const ArithSeq &other) noexcept {
    firstTerm = other.firstTerm;
    commonDiff = other.commonDiff;
    length = other.length;
    maxOperations = other.maxOperations;
    operationCount = other.operationCount;
    this->sequence = std::shared_ptr<int[]>(new int[length]);
    for (int i = 0; i < length; i++) {
        this->sequence[i] = other.sequence[i];
    }
}

ArithSeq::ArithSeq(const ArithSeq &other) noexcept {
    copy(other);
}

ArithSeq::ArithSeq(ArithSeq &&other) noexcept {
    firstTerm = other.firstTerm;
    commonDiff = other.commonDiff;
    length = other.length;
    maxOperations = other.maxOperations;
    operationCount = other.operationCount;
    sequence = move(other.sequence);
    other.firstTerm = 0;
    other.commonDiff = 0;
    other.length = 0;
    other.maxOperations = 0;
    other.operationCount = 0;
}

ArithSeq &ArithSeq::operator=(const ArithSeq &other) noexcept {
    if (this != &other) {
        copy(other);
    }
    return *this;
}

ArithSeq &ArithSeq::operator=(ArithSeq &&other) noexcept {
    if (this != &other) {
        firstTerm = other.firstTerm;
        commonDiff = other.commonDiff;
        length = other.length;
        maxOperations = other.maxOperations;
        operationCount = other.operationCount;
        sequence = move(other.sequence);
        other.firstTerm = 0;
        other.commonDiff = 0;
        other.length = 0;
        other.maxOperations = 0;
        other.operationCount = 0;
    }
    return *this;
}

bool ArithSeq::operator==(const ArithSeq &other) const {
    if (this == &other) return true;
    if (this->length != other.length) return false;
    if (this->firstTerm != other.firstTerm) return false;
    if (this->commonDiff != other.commonDiff) return false;
    return true;
}

bool ArithSeq::operator!=(const ArithSeq &other) const {
    return !(*this == other);
}

ArithSeq &ArithSeq::operator++() {
    for (int i = 0; i < length; i++) sequence[i] += 1;
    return *this;
}

ArithSeq ArithSeq::operator++(int) {
    //copy current object, pre-increment, then return old copy
    ArithSeq temp(*this);
    ++(*this);
    return temp;
}

ArithSeq &ArithSeq::operator--() {
    for (int i = 0; i < length; i++) sequence[i] -= 1;
    return *this;
}

ArithSeq ArithSeq::operator--(int) {
    //copy current object, pre-decrement, then return old copy
    ArithSeq temp(*this);
    --(*this);
    return temp;
}

int ArithSeq::operator[](int index) {
    if (index < 0 || index >= length) throw std::invalid_argument("Index for DurableSeq not found");
    return sequence[index];
}

ArithSeq &ArithSeq::operator+(ArithSeq &other) {
    if (length != other.length) throw std::invalid_argument(
        "ArithSeq object addition only works with equal length objects");
    for (int i = 0; i < length; i++) sequence[i] = sequence[i] + other.sequence[i];
    return *(this);
}

bool ArithSeq::checkOperationLimit() {
    if (operationCount >= maxOperations) return false;
    return true;
}

int ArithSeq::getLength() { return length; }

int ArithSeq::getKthVal(int k) {
    if (checkOperationLimit()) {
        if (k < 0 || k >= length) throw std::invalid_argument("k must be a valid index");
        operationCount++;
        return sequence[k - 1];
    }
    return -1;
}

int ArithSeq::evenlyDividedBy(int n) {
    if (checkOperationLimit()) {
        if (n == 0) throw std::invalid_argument("n must be non-zero");
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (sequence[i] % n == 0) count++;
        }
        operationCount++;
        return count;
    };
    return -1;
}

void ArithSeq::modifyEveryPthValue(int p, int q) {
    if (checkOperationLimit()) {
        if (p < 0 || p >= length) throw std::invalid_argument("p must be a valid index");
        for (int i = 0; i < length; i += p) {
            sequence[i] += q;
        }
        operationCount++;
    }
}

void ArithSeq::reset() {
    operationCount = 0;
    generateSequence();
}
