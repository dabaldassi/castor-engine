#ifndef CASTOR_SOUND_ENGINE_H
#define CASTOR_SOUND_ENGINE_H

#include <fmod/fmod.hpp>

#include <sound/sound_engine_impl.hpp>

namespace castor {
  
  class SoundEngine
  {
  public:
    using SoundDefinition = impl::SoundDefinition;
  private:
    static FMOD::System* _system;

    impl::SoundEngineImpl _impl;
    
  public:

    static constexpr int MAX_CHANNEL = 32;
  
    static void init();
    static void exit();

    //! Default constructor
    SoundEngine();

    //! Copy constructor
    SoundEngine(const SoundEngine &other);

    //! Move constructor
    SoundEngine(SoundEngine &&other) noexcept;

    //! Destructor
    virtual ~SoundEngine();

    //! Copy assignment operator
    SoundEngine& operator=(const SoundEngine &other);

    //! Move assignment operator
    SoundEngine& operator=(SoundEngine &&other) noexcept;

    void load(int sound_id);
    void unload(int sound_id);
    void update(float dt);
    void pause_sound(int sound_id);
    void stop_sound(int sound_id);
    int  play_sound(int sound_id, const Vec3<float>& v = Vec3<float>(0.f,0.f,0.f), float volume=1.0f);
    int  add_sound(const SoundDefinition& sound_def);
    bool is_channel_playing(int channel_id);
    
    // bool should_be_virtual();

  protected:
  private:
  };

}

#endif /* CASTOR_SOUND_ENGINE_H */
