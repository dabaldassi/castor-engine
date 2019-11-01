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
  _data.next_channel_id = 0;
  _data.next_sound_id = 0;
  _data.system = _system;
}

SoundEngine::~SoundEngine()
{
  
}

int SoundEngine::add_sound(const SoundEngineImpl::SoundDefinition &sound_def)
{
  int sound_id = _data.next_sound_id++;

  auto sound = SoundEngineImpl::make_ptr<SoundEngineImpl::Sound>();

  sound->def = sound_def;
  sound->id  = sound_id;

  _data.sounds[sound_id] = std::move(sound);
  
  return sound_id;
}

void SoundEngine::load(int sound_id)
{
  auto it = _data.sounds.find(sound_id);

  if(it != _data.sounds.end()) {
    _system->createSound(it->second->def.path.c_str(),
			 FMOD_DEFAULT,
			 nullptr,
			 &it->second->sound);
  }
}

int SoundEngine::play_sound(int sound_id, const Vec3<float>& position, float volume)
{
  auto it = _data.sounds.find(sound_id);

  if(it != _data.sounds.end()) {
    int ch_id = _data.next_channel_id++;

    _data.channels[ch_id] = SoundEngineImpl::make_ptr<SoundEngineImpl::Channel>(ch_id,
										_data,
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
  using channel_it = decltype(_data.channels)::iterator;

  std::vector<channel_it> stopped_channels;

  for(channel_it channel = _data.channels.begin(); channel != _data.channels.end(); ++channel) {
    channel->second->update(dt);
    
    if(channel->second->state() == SoundEngineImpl::Channel::State::STOPPED) {
	stopped_channels.push_back(channel);
    }
  }

  std::for_each(stopped_channels.begin(), stopped_channels.end(), [this](auto a){
      _data.channels.erase(a);
    });
  
  _system->update();
}

