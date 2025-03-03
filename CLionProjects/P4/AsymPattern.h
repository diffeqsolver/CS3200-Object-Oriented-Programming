#ifndef ASYMPATTERN_H
#define ASYMPATTERN_H
#include <memory>
#include "ArithSeq.h"

class AsymPattern {
public:

    AsymPattern(std::shared_ptr<std::shared_ptr<ArithSeq>[]> &ap, int length);

    AsymPattern &operator=(AsymPattern &&other) noexcept;

    AsymPattern(AsymPattern &&other) noexcept;

    ~AsymPattern() = default;

    void reset();

    std::shared_ptr<int[]> getKeys() const;

    void replicateWithNewKey(int replicateKey);

    bool operator==(const AsymPattern &other) const;

    bool operator!=(const AsymPattern &other) const;

    AsymPattern &operator++();

    AsymPattern operator++(int);

    AsymPattern &operator--();

    AsymPattern operator--(int);

    std::shared_ptr<ArithSeq> &operator[](int key);

private:
    std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap;
    std::shared_ptr<int[]> keys;
    int originalLength;
    int length;

    //Copying is suppressed
    AsymPattern(const AsymPattern &other) noexcept;

    AsymPattern &operator=(const AsymPattern &other) noexcept;

    void copy(const AsymPattern &other) noexcept;

    int generateUniqueKey() const;
};

#endif //ASYMPATTERN_H
