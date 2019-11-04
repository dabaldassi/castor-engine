#include <vector>
#include <algorithm>

#include <sound/sound_engine.hpp>

using castor::SoundEngine;

FMOD::System* SoundEngine::_system = nullptr;

void SoundEngine::init()
{
  FMOD::System_Create(&_system);
  _system->init(MAX_CHANNEL, FMOD_INIT_NORMAL, nullptr);
}

void SoundEngine::exit()
{
  _system->release();
  _system = nullptr;
}

SoundEngine::SoundEngine()
{
  _impl.next_channel_id = 0;
  _impl.next_sound_id = 0;
  _impl.system = _system;
}

SoundEngine::~SoundEngine()
{
  
}

int SoundEngine::add_sound(const SoundEngine::SoundDefinition &sound_def)
{
  int sound_id = _impl.next_sound_id++;

  auto sound = impl::make_ptr<impl::Sound>();

  sound->def = sound_def;
  sound->id  = sound_id;

  _impl.sounds[sound_id] = std::move(sound);
  
  return sound_id;
}

void SoundEngine::load(int sound_id)
{
  _impl.load(sound_id);
}

int SoundEngine::play_sound(int sound_id, const Vec3<float>& position, float volume)
{
  auto it = _impl.sounds.find(sound_id);

  if(it != _impl.sounds.end()) {
    int ch_id = _impl.next_channel_id++;

    _impl.channels[ch_id] = impl::make_ptr<impl::Channel>(ch_id,
							  _impl,
							  sound_id,
							  position,
							  volume);
    return ch_id;
  }
  else return -1;
}

void SoundEngine::stop_sound(int id)
{
  
}

void SoundEngine::update(float dt)
{
  using channel_it = decltype(_impl.channels)::iterator;

  std::vector<channel_it> stopped_channels;

  for(channel_it channel = _impl.channels.begin(); channel != _impl.channels.end(); ++channel) {
    channel->second->update(dt);
    
    if(channel->second->state() == impl::Channel::State::STOPPED) {
	stopped_channels.push_back(channel);
    }
  }

  std::for_each(stopped_channels.begin(), stopped_channels.end(), [this](auto a){
      _impl.channels.erase(a);
    });
  
  _system->update();
}

bool SoundEngine::is_channel_playing(int channel_id)
{
  auto it = _impl.channels.find(channel_id);

  return (it != _impl.channels.end() && it->second->is_playing());
}
