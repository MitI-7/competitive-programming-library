#pragma once
#include <iostream>

template<int mod>
struct mint {
    long long x;

    mint(long long x = 0) : x((x % mod + mod) % mod) {
    }

    mint &operator+=(const mint a) {
        if ((x += a.x) >= mod) {
            x -= mod;
        }
        return *this;
    }

    mint &operator-=(const mint a) {
        if ((x += mod - a.x) >= mod) {
            x -= mod;
        }
        return *this;
    }

    mint &operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }

    mint operator+(const mint a) const {
        mint res(*this);
        return res += a;
    }

    mint operator-(const mint a) const {
        mint res(*this);
        return res -= a;
    }

    mint operator*(const mint a) const {
        mint res(*this);
        return res *= a;
    }

    mint pow(long long t) const {
        if (!t) {
            return 1;
        }
        mint a = pow(t >> 1);
        a *= a;
        if (t & 1) {
            a *= *this;
        }
        return a;
    }

    // mod が素数のときのみ利用可能
    mint inv() const {
        return pow(mod - 2);
    }

    mint &operator/=(const mint a) {
        return (*this) *= a.inv();
    }

    mint operator/(const mint a) const {
        mint res(*this);
        return res /= a;
    }

    bool operator==(const mint a) const {
        return this->x == a.x;
    }

    friend std::ostream &operator<<(std::ostream &os, const mint &obj) {
        os << obj.x;
        return os;
    }
};


//const int MOD = 1000000000 + 7; // 10^9 + 7
//const int MOD = 998244353;