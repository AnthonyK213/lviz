#ifndef _LVIZ_CANVAS_HANDLE_H
#define _LVIZ_CANVAS_HANDLE_H

#include "object.h"

#include <cstdint>
#include <functional>

namespace lviz {
namespace canvas {

template <typename T> class handle {
public:
  handle() : obj_(nullptr) {}

  handle(const T *ptr) : obj_(const_cast<T *>(ptr)) {
    beginScope();
  }

  handle(const handle &h) : obj_(h.obj_) {
    beginScope();
  }

  handle(handle &&h) : obj_(h.obj_) {
    h.obj_ = nullptr;
  }

  ~handle() {
    endScope();
  }

  void Nullify() {
    endScope();
  }

  bool IsNull() const {
    return obj_ == nullptr;
  }

  void reset(T *ptr) {
    assign(ptr);
  }

  handle &operator=(const handle &h) {
    assign(h.obj_);
    return *this;
  }

  handle &operator=(handle &&h) noexcept {
    handle(::std::move(h)).swap(*this);
    return *this;
  }

  handle &operator=(const T *ptr) {
    assign(const_cast<T *>(ptr));
    return *this;
  }

  T *get() const {
    return static_cast<T *>(obj_);
  }

  T *operator->() const {
    return static_cast<T *>(obj_);
  }

  T &operator*() const {
    return *get();
  }

  template <typename T1> bool operator==(const handle<T1> &h) const {
    return get() == h.get();
  }

  template <typename T1> bool operator==(const T1 *ptr) const {
    return get() == ptr;
  }

  template <typename T1>
  friend bool operator==(const T1 *left, const handle &right) {
    return left == right.get();
  }

  template <typename T1> bool operator!=(const handle<T1> &h) const {
    return get() != h.get();
  }

  template <typename T1> bool operator!=(const T1 *ptr) const {
    return get() != ptr;
  }

  template <typename T1>
  friend bool operator!=(const T1 *left, const handle &right) {
    return left != right.get();
  }

  template <typename T1> bool operator<(const handle<T1> &h) const {
    return get() < h.get();
  }

  template <typename T1>
  static
      typename ::std::enable_if<::std::is_base_of<T1, T>::value, handle>::type
      DownCast(const handle<T1> &h) {
    return handle(dynamic_cast<T *>(const_cast<T1 *>(h.get())));
  }

  template <typename T1>
  static
      typename ::std::enable_if<::std::is_base_of<T1, T>::value, handle>::type
      DownCast(const T1 *ptr) {
    return handle(dynamic_cast<T *>(const_cast<T1 *>(ptr)));
  }

  explicit operator bool() const {
    return obj_ != nullptr;
  }

  template <typename T1, typename = typename ::std::enable_if<
                             ::std::is_base_of<T1, T>::value>::type>
  operator const handle<T1> &() const {
    return reinterpret_cast<const handle<T1> &>(*this);
  }

  template <typename T1, typename = typename ::std::enable_if<
                             ::std::is_base_of<T1, T>::value>::type>
  operator handle<T1> &() const {
    return reinterpret_cast<handle<T1> &>(*this);
  }

private:
  void swap(handle &h) {
    ::std::swap(obj_, h.obj_);
  }

  void assign(Object *ptr) {
    if (ptr == obj_)
      return;
    endScope();
    obj_ = ptr;
    beginScope();
  }

  void beginScope() {
    if (obj_)
      obj_->IncrementRefCounter();
  }

  void endScope() {
    if (obj_ && obj_->DecrementRefCounter() == 0)
      obj_->Delete();
    obj_ = nullptr;
  }

  template <typename T1> friend class handle;

private:
  Object *obj_;
};

} // namespace canvas
} // namespace lviz

namespace std {

template <typename T> struct hash<lviz::canvas::handle<T>> {
  size_t operator()(const lviz::canvas::handle<T> &h) const noexcept {
    return static_cast<size_t>(reinterpret_cast<::std::uintptr_t>(h.get()));
  }
};

} // namespace std

#endif
