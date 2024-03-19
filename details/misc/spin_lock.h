#ifndef _SGIMG_SPIN_LOCK_H
#define _SGIMG_SPIN_LOCK_H

#include <atomic>

namespace sgimg::misc {

class spin_lock {
public:
    auto lock() -> void;
    inline auto unlock() -> void;

private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};

inline auto spin_lock::lock() -> void {
    while (this->flag_.test_and_set(std::memory_order_acquire)) {
    }
}

inline auto spin_lock::unlock() -> void {
    this->flag_.clear(std::memory_order_release);
}

} // namespace sgimg::misc

#endif
