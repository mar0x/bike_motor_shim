
#pragma once

namespace artl {

template<typename CALLBACK>
struct timer : public CALLBACK {

    using CALLBACK::CALLBACK;

    constexpr unsigned long max_delay() const {
        return ((unsigned long) -1) / 2;
    }

    void schedule(unsigned long t) { at_ = t; }

    void cancel() { at_ = 0; }

    void update(unsigned long t) {
        if (at_ != 0 && t - at_ < max_delay()) {
            at_ = 0;
            (*this)(t);
        }
    }

    bool active() const { return at_ != 0; }

private:
    unsigned long at_ = 0;
};

}
