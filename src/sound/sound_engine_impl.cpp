#include <sound/sound_engine_impl.hpp>

using castor::SoundEngineImpl::Channel;

FMOD::System * castor::SoundEngineImpl::SoundEngineData::system = nullptr;

Channel::Channel(int ch_id,SoundEngineData& data, int sound_id, const Vec3<float>& position, float volume)
  :_id(ch_id),_sound_id(sound_id),_data(data)
{
  _state = State::TO_PLAY;
}


void Channel::update(float dt)
{
  switch (_state) {
  case State::TO_PLAY: {
    auto sound_it = _data.sounds.find(_sound_id);
    _data.system->playSound(sound_it->second->sound, nullptr, false, &_channel);
    _state = State::PLAYING;
    break;
    }
  case State::PLAYING:
    if(!is_playing()) _state = State::STOPPED;
    break;
  case State::STOPPED:

    break;
    
  default:
    break;
  }
}

bool Channel::is_playing() const
{
  bool b = false;
  if(_channel) _channel->isPlaying(&b);
  return b;
}
