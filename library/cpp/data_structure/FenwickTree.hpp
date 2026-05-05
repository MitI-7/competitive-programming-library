#pragma once
#include <cassert>
#include <vector>

// すべて 0-origin
template<class T>
class FenwickTree {
public:
    int n;
    std::vector<T> v;

    FenwickTree() = default;

    // n: 要素数
    explicit FenwickTree(const int n) : n(n), v(n, T{}) {}

    void init(const int n_) {
        this->n = n_;
        this->v.assign(this->n, T{});
    }

    int size() const {
        return this->n;
    }

    // v[i]
    // O(log n)
    T access(const int i) const {
        assert(0 <= i and i < this->n);
        return this->sum(i, i + 1);
    }

    // v[i] += x
    // O(log n)
    void add(int i, const T x) {
        assert(0 <= i and i < this->n);

        while (i < this->n) {
            this->v[i] += x;
            i |= i + 1;
        }
    }

    // v[i] = x
    // O(log n)
    void update(const int i, const T x) {
        assert(0 <= i and i < this->n);

        const T now = this->access(i);
        this->add(i, x - now);
    }

    // sum(v[0, i))
    // O(log n)
    T sum(int i) const {
        assert(0 <= i and i <= this->n);

        T s{};
        i -= 1;
        while (i >= 0) {
            s += this->v[i];
            i = (i & (i + 1)) - 1;
        }
        return s;
    }

    // sum(v[left, right))
    // O(log n)
    T sum(const int left, const int right) const {
        assert(0 <= left and left <= right and right <= this->n);
        if (left >= right) {
            return T{};
        }
        return this->sum(right) - this->sum(left);
    }
};