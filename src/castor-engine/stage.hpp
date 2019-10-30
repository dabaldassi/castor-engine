#ifndef CASTOR_STAGE_H
#define CASTOR_STAGE_H

#include <memory>
#include <list>

#include <viewport.hpp>
#include <actor/actor.hpp>

namespace castor {

  namespace actor {

    class Actor;

  }  // actor
  
  class Stage
  {
  public:
    using ActorPtr = std::unique_ptr<actor::Actor>;
    using Actors   = std::list<ActorPtr>;

  private:
    Actors   _actors;
    Viewport _vp;
  public:
    //! Default constructor
    Stage()
      :_vp(0,0) {}
    Stage(int width, int height)
      :_vp(width,height) {}

    //! Copy constructor
    Stage(const Stage &other) = delete;

    //! Move constructor
    Stage(Stage &&other) noexcept;

    //! Destructor
    virtual ~Stage() noexcept {}

    //! Copy assignment operator
    Stage& operator=(const Stage &other) = delete;

    //! Move assignment operator
    Stage& operator=(Stage &&other) noexcept;

    void act(float dt);
    void update() { for(auto&& a: _actors) a->update(_vp); }

    template<typename A, typename... Args>
    A& create(Args&&... args);

    void remove(const actor::Actor& actor);

  protected:
  private:
  };


  template <class A, class... Args>
  A & Stage::create(Args &&... args)
  { 
    _actors.push_back(std::make_unique<A>(std::forward<Args>(args)...)); 
    A & a = *static_cast<A *>(_actors.back().get());
    a.set_stage(this);
    return a;
  }
  
}  // castor

#endif /* CASTOR_STAGE_H */
