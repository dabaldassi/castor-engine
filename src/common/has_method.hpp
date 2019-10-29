#ifndef CASTOR_HAS_METHOD_H
#define CASTOR_HAS_METHOD_H

#include <utility>

namespace castor {

  template<typename T>
  struct HasMethod
  {
    template<typename... Args>
    constexpr auto has(int)
      -> decltype(std::declval<T>()(std::declval<Args>()...),std::true_type()) {
      return std::true_type();
    }

    template<typename... Args>
    constexpr std::false_type has(...) { return std::false_type(); }

    template<typename... Args>
    constexpr auto operator()(Args&& ...) {
      return has<Args...>(int{});
    }
  };

  template<typename Lambda> constexpr auto has_method(Lambda&&) {
    return HasMethod<Lambda>();
  }

}  // castor

#endif /* CASTOR_HAS_METHOD_H */
