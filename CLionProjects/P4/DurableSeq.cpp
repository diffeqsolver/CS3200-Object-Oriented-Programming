#include <fstream>
#include <stdexcept>
#include <memory>
#include <string>
#include <iostream>
#include <cstdio>
#include "ArithSeq.h"
#include "DurableSeq.h"

DurableSeq::DurableSeq(int firstTerm, int commonDiff, int length, int maxOperations, const std::string &filePath)
    : ArithSeq(firstTerm, commonDiff, length, maxOperations), filePath(filePath) {
    isDirty = false;

    //delete existing file which holds DurableSeq
    if (std::ifstream(filePath)) {
        std::remove(filePath.c_str());
    }
    //create a new sequence and save to file
    saveToFile();
}

DurableSeq::DurableSeq(const DurableSeq &other) noexcept : ArithSeq(other), filePath(other.filePath + "_copy") {
    saveToFile();
}

DurableSeq &DurableSeq::operator=(const DurableSeq &other) noexcept {
    if (this != &other) {
        ArithSeq::operator=(other);
        filePath = other.filePath + "_copy";
        saveToFile();
    }
    return *this;
}

DurableSeq::DurableSeq(DurableSeq &&other) noexcept
    : ArithSeq(std::move(other)), filePath(std::move(other.filePath)), isDirty(other.isDirty) {
    other.isDirty = false;
}

DurableSeq &DurableSeq::operator=(DurableSeq &&other) noexcept {
    if (this != &other) {
        ArithSeq::operator=(std::move(other)); // Move base class
        filePath = std::move(other.filePath);
        isDirty = other.isDirty;
        other.isDirty = false; // Reset the moved-from object
    }
    return *this;
}

void DurableSeq::saveToFile() {
    if (!isDirty) return;

    //overwrite existing file
    //std::ios::trunc (truncate) removes old content when the file is opened
    std::ofstream outFile(filePath, std::ios::trunc);
    if (!outFile) throw std::ios_base::failure("Error opening file for writing");

    //utilizes operator overload
    outFile << *this;

    outFile.close();
    isDirty = false;
}

void DurableSeq::loadFromFile() {
    std::ifstream inFile(filePath);
    if (!inFile) throw std::ios_base::failure("Error opening file for reading");

    inFile >> *this;

    inFile.close();
}

void DurableSeq::modifyEveryPthValue(int p, int q) {
    ArithSeq::modifyEveryPthValue(p, q);
    isDirty = true;
}

void DurableSeq::reset() {
    ArithSeq::reset();
    if (std::ifstream(filePath)) {
        loadFromFile();
    } else {
        saveToFile();
    }
    isDirty = false;
}

int DurableSeq::getLength() { return length; }

std::string DurableSeq::getFilePath() { return filePath; }

DurableSeq::~DurableSeq() {
    if (isDirty) saveToFile();
}

bool DurableSeq::operator==(const DurableSeq &other) const {
    if (this == &other) return true;
    if (this->length != other.length) return false;
    if (this->firstTerm != other.firstTerm) return false;
    if (this->commonDiff != other.commonDiff) return false;
    return true;
}

bool DurableSeq::operator!=(const DurableSeq &other) const {
    return !(*this == other);
}

DurableSeq &DurableSeq::operator++() {
    for (int i = 0; i < length; i++) sequence[i] += 1;
    isDirty = true;
    return *this;
}

DurableSeq DurableSeq::operator++(int) {
    DurableSeq temp(*this);
    ++(*this);
    isDirty = true;
    return temp;
}

DurableSeq &DurableSeq::operator--() {
    for (int i = 0; i < length; i++) sequence[i] -= 1;
    isDirty = true;
    return *this;
}

DurableSeq DurableSeq::operator--(int) {
    DurableSeq temp(*this);
    --(*this);
    isDirty = true;
    return temp;
}

int DurableSeq::operator[](int index) {
    if (index < 0 || index >= length) throw std::invalid_argument("Index for DurableSeq not found");
    if (isDirty) saveToFile();
    return sequence[index];
}

std::ostream &operator<<(std::ostream &os, const DurableSeq &seq) {
    for (int i = 0; i < seq.length; i++) {
        //each value is on a separate line
        os << seq.sequence[i] << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &is, DurableSeq &seq) {
    //create a temporary sequence
    std::shared_ptr<int[]> tempSequence(new int[seq.length]);
    int index = 0, value;
    std::string line;

    //read each line and store into tempSequence
    while (index < seq.length && is >> value) {
        tempSequence[index] = value;
        index++;
    }

    //check if length is correct
    if (index != seq.length) {
        throw std::invalid_argument("File data does not match sequence length");
    }

    for (int i = 0; i < seq.length; i++) {
        seq.sequence[i] = tempSequence[i];
    }
    //mark as clean
    seq.isDirty = false;
    return is;
}
