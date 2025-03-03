#include "ArithSeq.h"
#include "AsymPattern.h"
#include <stdexcept>
#include <memory>

AsymPattern::AsymPattern(std::shared_ptr<std::shared_ptr<ArithSeq>[]> &ap, int length) {
    if (!ap) throw std::invalid_argument("must be a non null parameter");
    if (length <= 0) throw std::invalid_argument("length must be greater than 0");

    originalLength = length;
    this->length = length;

    this->ap = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(new std::shared_ptr<ArithSeq>[length]);
    this->keys = std::shared_ptr<int[]>(new int[length]);

    for (int i = 0; i < length; i++) {
        this->ap[i] = ap[i];
        keys[i] = generateUniqueKey();
    }
}

void AsymPattern::copy(const AsymPattern &other) noexcept {
    length = other.length;
    originalLength = other.originalLength;
    this->ap = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(new std::shared_ptr<ArithSeq>[length]);
    this->keys = std::shared_ptr<int[]>(new int[length]);
    for (int i = 0; i < length; i++) {
        this->ap[i] = other.ap[i];
        this->keys[i] = other.keys[i];
    }
}

AsymPattern &AsymPattern::operator=(const AsymPattern &other) noexcept {
    if (this != &other) copy(other);
    return *this;
}

AsymPattern &AsymPattern::operator=(AsymPattern &&other) noexcept {
    if (this != &other) {
        this->ap = move(other.ap);
        this->keys = move(other.keys);
        length = other.length;
        originalLength = other.originalLength;
        other.length = 0;
        other.originalLength = 0;
    }
    return *this;
}

AsymPattern::AsymPattern(const AsymPattern &other) noexcept {
    copy(other);
}

AsymPattern::AsymPattern(AsymPattern &&other) noexcept {
    this->ap = move(other.ap);
    this->keys = move(other.keys);
    length = other.length;
    originalLength = other.originalLength;
    other.length = 0;
    other.originalLength = 0;
}

int AsymPattern::generateUniqueKey() const {
    int candidateKey = 1;
    while (true) {
        bool found = false;
        for (int i = 0; i < this->length; i++) {
            if (keys[i] == candidateKey) {
                found = true;
                break;
            }
        }
        if (!found) {
            return candidateKey;
        }
        candidateKey++;
    }
}

std::shared_ptr<int[]> AsymPattern::getKeys() const {
    std::shared_ptr<int[]> result(new int[length]);
    for (int i = 0; i < length; i++) result[i] = keys[i];
    return result;
}

//note that the only way users can access ap elements through [] is through keys which are given to them
std::shared_ptr<ArithSeq> &AsymPattern::operator[](int key) {
    for (int i = 0; i < length; i++) {
        if (keys[i] == key) return ap[i];
    }
    throw std::invalid_argument("Key not found");
}

void AsymPattern::reset() {
    length = originalLength;
    for (int i = 0; i < length; i++) {
        if (ap[i]) ap[i]->reset();
    }
}

void AsymPattern::replicateWithNewKey(int replicateKey) {
    std::shared_ptr<ArithSeq> newSeq = std::make_shared<ArithSeq>(*this->ap[replicateKey]);
    //CHECK FOR DURABLESEQ OBJ
    std::shared_ptr<std::shared_ptr<ArithSeq>[]> newAp(new std::shared_ptr<ArithSeq>[length + 1]);
    std::shared_ptr<int[]> newKeys(new int[length + 1]);
    for (int i = 0; i < length; i++) {
        newAp[i] = ap[i];
        newKeys[i] = keys[i];
    }
    newAp[length] = newSeq;
    newKeys[length] = generateUniqueKey();
    length++;
    ap = std::move(newAp);
    keys = std::move(newKeys);
}

bool AsymPattern::operator==(const AsymPattern &other) const {
    if (this == &other) return true;
    if (this->length != other.length) return false;
    for (int i = 0; i < length; i++) {
        if (this->keys[i] != other.keys[i]) return false;
    }
    for (int i = 0; i < length; i++) {
        if ((*this->ap[i] != *(other.ap[i]))) return false;
    }
    return true;
}

bool AsymPattern::operator!=(const AsymPattern &other) const {
    return !(*this == other);
}

AsymPattern &AsymPattern::operator++() {
    for (int i = 0; i < length; i++) {
        ++(*ap[i]);
    }
    return *this;
}

AsymPattern AsymPattern::operator++(int) {
    AsymPattern temp(*this);
    ++(*this);
    return temp;
}

AsymPattern &AsymPattern::operator--() {
    for (int i = 0; i < length; i++) {
        --(*ap[i]);
    }
    return *this;
}

AsymPattern AsymPattern::operator--(int) {
    AsymPattern temp(*this);
    --(*this);
    return temp;
}
