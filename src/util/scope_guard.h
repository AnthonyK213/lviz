#ifndef LVIZ_UTIL_SCOPE_GUARD_H
#define LVIZ_UTIL_SCOPE_GUARD_H

namespace lviz {
namespace util {

template <typename F> class ScopeGuard {
public:
  explicit ScopeGuard(F &&func) : func_(std::forward<F>(func)) {}

  ScopeGuard(const ScopeGuard &) = delete;

  ScopeGuard &operator=(const ScopeGuard &) = delete;

  ScopeGuard(ScopeGuard &&other) noexcept : func_(std::move(other.func_)) {}

  ScopeGuard &operator=(ScopeGuard &&other) noexcept {
    func_ = std::move(other.func_);
  }

  ~ScopeGuard() {
    func_();
  }

private:
  F func_;
};

template <typename F> ScopeGuard<F> MakeScopeGuard(F &&func) {
  return ScopeGuard<F>(std::forward<F>(func));
}

} // namespace util
} // namespace lviz

#endif
