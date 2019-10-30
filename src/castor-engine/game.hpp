#ifndef CASTOR_GAME_H
#define CASTOR_GAME_H

#include <memory>

#include <common/has_method.hpp>

extern "C" {
  int  init_sandal(int,int,const char *);
  void exit_sandal();
}

namespace castor {

  class Stage;
  
  auto has_supervise = has_method([](auto&& a) -> decltype(a.supervise()) {});
  
  class Game
  {
  public:
    using StagePtr = std::unique_ptr<Stage>;
    
  private:
    StagePtr _current_stage;
    bool     _should_close;
    
  public:

    Game() {}

    template<typename Director>
    using has_supervise_t = decltype(has_supervise(std::declval<Director>()));
    

    template<typename Director>
    std::enable_if_t<Game::has_supervise_t<Director>::value,void> run();

    template<typename Director>
    std::enable_if_t<!has_supervise_t<Director>::value,void>
    run() {
      static_assert(has_supervise_t<Director>::value,"Director must implement supervise");
    }
    
    template<typename S, typename... Args>
    void swap_stage(Args... args) {
      _current_stage = std::make_unique<S>(std::forward<Args>(args)...);
    }
    
    void update();

    virtual ~Game(){}

    static bool init(int width, int height, const std::string& name) {
      return init_sandal(width,height,name.c_str());
    }
    
    static void exit() { exit_sandal(); }
  };

  template<typename Director>
  std::enable_if_t<Game::has_supervise_t<Director>::value,void>
  Game::run() {
    Director d;
    bool     r = true;

    while(!_should_close && r) {
      r = d.supervise();
      update();
    }
      
  }
  
}

#endif /* CASTOR_GAME_H */
