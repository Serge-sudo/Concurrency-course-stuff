#pragma once

#include <twist/stdlike/mutex.hpp>
#include <twist/stdlike/condition_variable.hpp>

// std::lock_guard, std::unique_lock
#include <mutex>
#include <cstdint>

namespace solutions {

// A Counting semaphore

// Semaphores are often used to restrict the number of threads
// than can access some (physical or logical) resource

class Semaphore {
 public:
  // Creates a Semaphore with the given number of permits
  explicit Semaphore(size_t initial) {
    permits_ = initial;
  }

  // Acquires a permit from this semaphore,
  // blocking until one is available
  void Acquire() {
    std::unique_lock<twist::stdlike::mutex> guard(mutex_);
    while (permits_ == 0) {
      cv_.wait(guard);
    }
    --permits_;
  }

  // Releases a permit, returning it to the semaphore
  void Release() {
    std::unique_lock<twist::stdlike::mutex> guard(mutex_);
    ++permits_;
    cv_.notify_one();
  }

 private:
  twist::stdlike::mutex mutex_;
  twist::stdlike::condition_variable cv_;
  size_t permits_;
  // Permits
};

}  // namespace solutions
