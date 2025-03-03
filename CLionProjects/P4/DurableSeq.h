#ifndef DURABLESEQ_H
#define DURABLESEQ_H

#include "ArithSeq.h"
#include <string>

class DurableSeq : public ArithSeq {
public:
    void modifyEveryPthValue(int p, int q) override;

    void reset() override;

    void forceSave();

    ~DurableSeq();

    int getLength() override;

    std::string getFilePath();

    DurableSeq(int firstTerm, int commonDiff, int length, int maxOperations, const std::string &filePath);

    DurableSeq(const DurableSeq &other) noexcept;

    DurableSeq &operator=(const DurableSeq &other) noexcept;

    DurableSeq(DurableSeq &&other) noexcept;

    DurableSeq &operator=(DurableSeq &&other) noexcept;

    DurableSeq(const DurableSeq &&other) noexcept;

    DurableSeq &operator=(const DurableSeq &&other) noexcept;

    void assignNewFilePath();

    bool operator==(const DurableSeq &other) const;

    bool operator!=(const DurableSeq &other) const;

    DurableSeq &operator++();

    DurableSeq operator++(int);

    DurableSeq &operator--();

    DurableSeq operator--(int);

    int operator[](int index);

    friend std::ostream &operator<<(std::ostream &os, const DurableSeq &seq);

    friend std::istream &operator>>(std::istream &is, DurableSeq &seq);

private:
    void saveToFile();

    void loadFromFile();

    std::string filePath;
    bool isDirty = false;
};

#endif //DURABLESEQ_H
