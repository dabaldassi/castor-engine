#include <sound/sound_engine_impl.hpp>

using castor::impl::Channel;
using castor::impl::SoundEngineImpl;

FMOD::System * SoundEngineImpl::system = nullptr;

Channel::Channel(int ch_id,SoundEngineImpl& impl, int sound_id, const Vec3<float>& position, float volume)
  :_id(ch_id),_sound_id(sound_id),_impl(impl)
{
  _state = State::TO_PLAY;
}


void Channel::update(float dt)
{
  switch (_state) {
  case State::TO_PLAY: {
    auto sound_it = _impl.sounds.find(_sound_id);
    _impl.system->playSound(sound_it->second->sound, nullptr, false, &_channel);
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


void SoundEngineImpl::load(int sound_id)
{
  auto it = sounds.find(sound_id);

  if(it != sounds.end()) {
    FMOD_RESULT err = system->createSound(it->second->def.path.c_str(),
					  FMOD_DEFAULT,
					  nullptr,
					  &it->second->sound);
    if(err) throw std::runtime_error("Can't load "+it->second->def.path);
  }
}
