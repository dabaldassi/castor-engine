#ifndef CASTOR_ACTOR_H
#define CASTOR_ACTOR_H


namespace castor {
  class Stage;

  
  namespace actor {

    using namespace castor;
    
    class Actor
    {
      Stage * _stage;

      float _life;
      
    public:
      //! Default constructor
      Actor();

      //! Copy constructor
      Actor(const Actor &other) = delete;

      //! Move constructor
      Actor(Actor &&other) noexcept;

      //! Destructor
      virtual ~Actor() noexcept = default;

      //! Copy assignment operator
      Actor& operator=(const Actor &other) = delete;

      //! Move assignment operator
      Actor& operator=(Actor &&other) noexcept;

      bool is_dead() { return _life <= 0; }
      void act(float dt);
      void update(const Viewport& v);
      void set_stage(Stage * s) { _stage = s; }

    protected:
    private:
    };

  }  // actor

}  // castor

#endif /* CASTOR_ACTOR_H */
