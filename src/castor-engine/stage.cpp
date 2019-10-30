#include <algorithm>
#include <stack>

#include <stage.hpp>

using castor::Stage;

Stage::Stage(Stage&& other) noexcept : _actors(std::move(other._actors)),
				       _vp(std::move(other._vp)) {}

Stage& Stage::operator=(Stage&& other) noexcept
{
  _actors = std::move(other._actors);
  _vp     = std::move(other._vp);

  return *this;
}

void Stage::remove(const castor::actor::Actor& actor)
{
  auto it = std::find_if(_actors.begin(),_actors.end(),[&actor](auto&& a) {
      return a.get() == &actor;
    });

  if(it != _actors.end()) _actors.erase(it);
}

void Stage::act(float dt)
{
  std::stack<Actors::iterator> _to_remove;
  
  for(auto a = _actors.begin();a != _actors.end(); ++a) {
    (*a)->act(dt);
    if((*a)->is_dead()) _to_remove.push(a);
  }

  while(!_to_remove.empty()) {
    auto a = _to_remove.top();
    _to_remove.pop();
    _actors.erase(a);
  }
}
