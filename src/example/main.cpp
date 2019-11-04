#include <iostream>
#include <chrono>
#include <thread>
#include <sound/sound_engine.hpp>

int main(){
  castor::SoundEngine::init();

  castor::SoundEngine sound_engine;
  castor::SoundEngine::SoundDefinition sound_def;

  sound_def.path = "hit.wav";
  
  int id = sound_engine.add_sound(sound_def);
  sound_engine.load(id);
  int i = sound_engine.play_sound(id);

  sound_engine.update(0.f);
  
  std::cout << "Channel id : " << i << "\n";

  auto t1 = std::chrono::system_clock::now();
  while(sound_engine.is_channel_playing(i)) {
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    sound_engine.update(diff.count());
    t1 = t2;
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  
  castor::SoundEngine::exit();
}
