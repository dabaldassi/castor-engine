
#include "catch.hpp"

#include <common/has_method.hpp>

#include <string>

using namespace castor;

struct Foo {
  void foo(){}
};

struct Bar
{
  void bar(int,int,float,const std::string&){}
};

auto has_foo = has_method([](auto&& a) -> decltype(a.foo()) {});

template<typename T>
using has_foo_t = decltype(has_foo(std::declval<T>())); 

template<typename T>
std::enable_if_t<has_foo_t<T>::value,int>
foo() {
  return 5;
}

template<typename T>
std::enable_if_t<!has_foo_t<T>::value,int>
foo() {
  return 0;
}

TEST_CASE("has method") {
  
  REQUIRE(decltype(has_foo(Foo()))::value);
  REQUIRE_FALSE(decltype(has_foo(Bar()))::value);

  auto has_bar = has_method([](auto&& a, auto&&... args)
			    -> decltype(a.bar(std::declval<decltype(args)>()...)) {});
  
  REQUIRE(decltype(has_bar(Bar(),int{},int{},float{},std::string{}))::value);
  REQUIRE_FALSE(decltype(has_bar(Bar(),int{},int{},float{}))::value);


  REQUIRE(foo<Foo>() == 5);
  REQUIRE(foo<Bar>() == 0);
}
