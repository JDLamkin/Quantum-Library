#include <iostream>
#include <complex>
#include <vector>
#include <random>

#define __Q_DUMP__

class qpu {
public:
    typedef float real;

private:
    std::vector<std::complex<real>> states;
    std::default_random_engine rng;
    std::size_t tick;
    unsigned sz;

public:
    qpu(unsigned);
    qpu(qpu&) = delete;
    qpu(qpu&&);
    qpu& operator=(qpu&) = delete;
    qpu& operator=(qpu&&);

    std::size_t timestep() const;
    unsigned size() const;
    bool measure(unsigned);

    void H(unsigned);
    void X(unsigned);
    void Y(unsigned);
    void Z(unsigned);
    void RX(unsigned, real r);
    void RY(unsigned, real r);
    void RZ(unsigned, real r);
    void S(unsigned, bool invert = false);
    void T(unsigned, bool invert = false);

    void CX(unsigned, unsigned);
    void CCX(unsigned, unsigned, unsigned);

#ifdef __Q_DUMP__
    void dump(std::ostream& out = std::cerr) const;
#endif
};
