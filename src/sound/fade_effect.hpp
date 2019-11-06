#ifndef CASTOR_FADE_EFFECT_H
#define CASTOR_FADE_EFFECT_H

#include <list>
#include <fmod/fmod.h>

namespace castor {

  // TODO : START and STOP --->> ms instead of sec or percent maybe more simple and less specialization
  template<typename ChannelType, int START, int STOP, int VOLUME>
  struct FadeEffectImpl
  {
    void operator()(ChannelType* c) {
      unsigned long long dspclock;
      int                rate;
      FMOD::System *     system = nullptr;
      
      c->getSystemObject(&system);
      system->getSoftwareFormat(&rate, 0, 0);
      c->getDSPClock(nullptr, &dspclock);
      c->addFadePoint(dspclock + rate * START, VOLUME);
      c->addFadePoint(dspclock + rate * STOP, 1 - VOLUME);
    }
  };

  using limit = std::numeric_limits<int>;

  template<typename ChannelType>
  struct FadeEffectImpl<ChannelType, limit::min(),limit::min(),limit::min()>
  {
    std::list<std::tuple<float,float>> points;

    template<typename Tuple>
    void add_point(Tuple&& p) { points.push_back(std::forward<Tuple>(p)); }

    void remove_point(const std::tuple<float,float>& p) { points.remove(p); }
    
    void operator()(ChannelType *c) {
      unsigned long long dspclock;
      int                rate;
      FMOD::System *     system = nullptr;
      
      c->getSystemObject(&system);
      system->getSoftwareFormat(&rate, 0, 0);
      c->getDSPClock(nullptr, &dspclock);

      for(auto&& [start,volume] : points) {
	c->addFadePoint(dspclock + rate * start, volume);
      }
    }
  };

  template<typename ChannelType, int START>
  struct FadeEffectImpl<ChannelType, START, limit::max(), 1>
  {
    void operator()(ChannelType * c) {
      unsigned long long dspclock;
      int                rate;
      FMOD::System *     system = nullptr;

      c->getSystemObject(&system);
      system->getSoftwareFormat(&rate,0,0);
      c->getDSPClock(nullptr, &dspclock);

      FMOD::Sound * current_sound = nullptr;
      unsigned int  lenms;
      
      c->getCurrentSound(&current_sound);
      current_sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
      c->addFadePoint(dspclock + rate * START, 1);
      c->addFadePoint(dspclock + rate * lenms/1000, 0);
    }
  };
  
  template<typename ChannelType>
  using AudioFader = FadeEffectImpl<ChannelType,limit::min(),limit::min(),limit::min()>;

  template<typename ChannelType, int DURATION>
  using AudioFadeIn = FadeEffectImpl<ChannelType,0,DURATION,0>;

  template<typename ChannelType, int START, int STOP>
  using AudioFadeOff = FadeEffectImpl<ChannelType,START,STOP,1>;

  template<typename ChannelType, int START>
  using AudioFadeOut = FadeEffectImpl<ChannelType,START,limit::max(),1>;


}  // castor


#endif /* CASTOR_FADE_EFFECT_H */
