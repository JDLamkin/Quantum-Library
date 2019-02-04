#include <cmath>
#include <ctime>
#include "qpu.h"

using namespace std;

#define FORSTATES(idx) \
    for(size_t idx = 0; idx < states.size(); ++idx)
#define GET(q) (1ULL << (q))
#define BIT(idx, q) ((bool)((idx) & GET(q)))

unsigned getSeed() {
    static random_device r;
    unsigned v = r();
    v ^= time(nullptr);
    return v;
}

qpu::qpu(unsigned bits) : states(1ULL << bits, 0), rng(getSeed()) {
    states[0] = complex<real>(1, 0);
    sz = bits;
    tick = 0;
}
qpu::qpu(qpu&& o) {
    *this = move(o);
}
qpu& qpu::operator=(qpu&& o) {
    states = move(o.states);
    rng = move(o.rng);
    tick = o.tick;
    sz = o.sz;
    return *this;
}

size_t qpu::timestep() const {
    return tick;
}
unsigned qpu::size() const {
    return sz;
}
bool qpu::measure(unsigned q) {
    ++tick;
    real m[2];
    m[0] = m[1] = 0;
    FORSTATES(idx)
        m[BIT(idx, q)] += norm(states[idx]);
    bernoulli_distribution bd(m[1]/(m[0] + m[1]));
    bool decision = bd(rng);
    real fact = 1/sqrt(m[decision]);
    FORSTATES(idx) {
        if(BIT(idx, q) == decision)
            states[idx] *= fact;
        else
            states[idx] = 0;
    }
    return decision;
}

void qpu::H(unsigned q) {
#ifdef __Q_DUMP__
    static constexpr real h = 1/sqrt((real)2);
#else
    static constexpr complex<real> h(0.5f, 0.5f);
#endif
    ++tick;
    FORSTATES(idx) if(!BIT(idx, q)) {
        auto& s0 = states[idx];
        auto& s1 = states[idx | GET(q)];
        auto a = s0, b = s1;
        s0 = h*(a + b);
        s1 = h*(a - b);
    }
}
void qpu::X(unsigned q) {
    RX(q, 0.5);
}
void qpu::Y(unsigned q) {
    RY(q, 0.5);
}
void qpu::Z(unsigned q) {
    RZ(q, 0.5);
}
void qpu::RX(unsigned q, real r) {
    H(q); --tick;
    RZ(q, r);
    H(q); --tick;
}
void qpu::RY(unsigned q, real r) {
    S(q, false); --tick;
    RX(q, r);
    S(q, true); --tick;
}
void qpu::RZ(unsigned q, real r) {
    ++tick;
    real r8;
    r = modf(r, &r8);
    r = modf(8*r, &r8)/8;
    int i8 = (int)(r8 + 0.5f);
    complex<real> phi = polar(1.0f, (real)(r*2*M_PI));
    if(i8 & 1) phi *= complex<real>(1.0f, 1.0f)/sqrt((real)2);
    i8 /= 2;
    while(i8 --> 0) phi *= complex<real>(0, 1);
    FORSTATES(idx) if(BIT(idx, q))
        states[idx] *= phi;
}
void qpu::S(unsigned q, bool invert) {
    RZ(q, invert ? -0.25f : 0.25f);
}
void qpu::T(unsigned q, bool invert) {
    RZ(q, invert ? -0.125f : 0.125f);
}

void qpu::CX(unsigned c, unsigned q) {
    ++tick;
    FORSTATES(idx) if(BIT(idx, c) && !BIT(idx, q))
        swap(states[idx], states[idx | GET(q)]);
}
void qpu::CCX(unsigned c1, unsigned c2, unsigned q) {
    ++tick;
    FORSTATES(idx) if(BIT(idx, c1) && BIT(idx, c2) && !BIT(idx, q))
        swap(states[idx], states[idx | GET(q)]);
}

#ifdef __Q_DUMP__
static bool printComplex(ostream& out, complex<qpu::real> z) {
    auto x = real(z), y = imag(z);
    if(y == 0) {
        if(x == 0) return true;
        out << x;
    } else if(x == 0) {
        out << y << "i";
    } else {
        out << "(" << x << (y > 0 ? " + " : " - ") << abs(y) << "i)";
    }
    return false;
}

void qpu::dump(ostream& out) const {
    FORSTATES(idx) {
        if(printComplex(out, states[idx]))
            continue;
        out << " |";
        for(unsigned i = 0; i < sz; ++i)
            out << ((idx >> i) & 1);
        out << ">" << endl;
    }
}
#endif
