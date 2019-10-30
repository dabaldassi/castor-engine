#ifndef CASTOR_VIEWPORT_H
#define CASTOR_VIEWPORT_H

namespace castor {

  /**
   * This cass contains information relative to the area visible in the windows
   */
  struct Viewport {
    static constexpr float METER_TO_PIXEL = 50.;

    float x;
    float y;
    float width;
    float height;

    Viewport(int width, int height) 
      : x(0), y(0), width(width / METER_TO_PIXEL), height(height / METER_TO_PIXEL) {}

    Viewport(const Viewport& other)
      :x(other.x),y(other.y),width(other.width),height(other.height) {}

    Viewport(Viewport&& other) noexcept
      :x(other.x),y(other.y),width(other.width),height(other.height) {}

    Viewport& operator=(const Viewport& other) {
      x = other.x, y = other.y, width = other.width, height = other.height;
      return *this;
    }

    Viewport& operator=(Viewport&& other) {
      x = other.x, y = other.y, width = other.width, height = other.height;
      return *this;
    }
  };

}  // castor

#endif /* CASTOR_VIEWPORT_H */
