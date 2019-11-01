#include <sound/sound_engine.hpp>

#include <unistd.h>
#include <iostream>

int main(){
  castor::SoundEngine::init();

  castor::SoundEngine sound_engine;
  castor::SoundEngine::SoundDefinition sound_def;

  sound_def.path = "hit.wav";
  
  int id = sound_engine.add_sound(sound_def);
  sound_engine.load(id);
  int i = sound_engine.play_sound(id);

  sound_engine.update(0.f);
  
  std::cout << i << "\n";
  sleep(1);
   
  castor::SoundEngine::exit();
}
