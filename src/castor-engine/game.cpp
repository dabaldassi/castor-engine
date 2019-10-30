#include <castor-engine/game.hpp>
#include <castor-engine/stage.hpp>

#include <SANDAL2.h>

using castor::Game;

int init_sandal(int w, int h, const char * name)
{
  int          black[4] = {0,0,0,0};

  if(initAllSANDAL2(IMG_INIT_JPG)) {
    puts("Failed to init SANDAL2");
    return 1;
  }

  createWindow(w, h, name, /*SDL_WINDOW_FULLSCREEN_DESKTOP*/ SDL_WINDOW_RESIZABLE, black, 0);
  
  if(!initIteratorWindow()) {
    closeAllSANDAL2();
    fprintf(stderr, "Failed to open window \n");
    return 1;
  }

  return 0;
}

void exit_sandal()
{
  closeAllWindow(); /* close all windows */
  closeAllSANDAL2();
}


void Game::update()
{
  int   tps,ticks;
  float dt;

  static int oldTps = 0;

  constexpr float frame_rate = 1000/60.f;
    
  tps = SDL_GetTicks();
  dt = tps - oldTps;
  oldTps = tps;
  
  _should_close = !!PollEvent(NULL);
    
  _current_stage->act(dt);
  _current_stage->update();
    
  updateWindow();
  displayWindow();
    
  ticks = frame_rate - SDL_GetTicks() + tps;

  if(ticks > 0)
    SDL_Delay(ticks);

  if(!initIteratorWindow())
    _should_close = true;
      
}
