#ifndef CASTOR_SOUND_ENGINE_IMPL_H
#define CASTOR_SOUND_ENGINE_IMPL_H

#include <map>
#include <memory>

#include <fmod/fmod.hpp>

#include <common/vec.hpp>

namespace castor {

  namespace impl {

    struct SoundDefinition {
      std::string   path;
      bool          is_3d;
      bool          is_looping;
      float         default_volume;
      float         min_distance;
      float         max_distance;
    };

    struct Sound
    {
      int               id;
      SoundDefinition   def;
      bool              is_loaded;
      FMOD::Sound     * sound;
    };

    struct SoundEngineImpl;
    
    class Channel
    {
    public:
      enum class State { NONE, LOADING, TO_PLAY, PLAYING, PAUSED, STOPPED };
    private:
      
      int              _id;
      FMOD::Channel *  _channel = nullptr;
      State            _state   = State::NONE;
      int              _sound_id;
      SoundEngineImpl& _impl; 

    public:
      Channel(int ch_id, SoundEngineImpl& impl, int sound_id, const Vec3<float>& position, float volume);
      
      void update(float dt);
      bool is_playing() const;
      float get_volume() const;
      State state() const { return _state; }
    };

    using SoundPtr = std::unique_ptr<Sound>;
    using ChannelPtr = std::unique_ptr<Channel>;
    
    struct SoundEngineImpl
    {
      std::map<int,SoundPtr>   sounds;
      std::map<int,ChannelPtr> channels;

      int next_sound_id;
      int next_channel_id;

      static FMOD::System * system;

      void load(int sound_id);
      bool is_loaded(int sound_id);
    };

    template<typename T, typename... Args>
    auto make_ptr(Args&&... args) {
      return std::make_unique<T>(std::forward<Args>(args)...);
    }

    
  }  // SoundEngineImpl

}  // castor

#endif /* CASTOR_SOUND_ENGINE_IMPL_H */
