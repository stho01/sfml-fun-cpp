//
// Created by stenm on 01.05.2025.
//

#pragma once
namespace stho {
  template<typename T>
  struct Range {
    T min;
    T max;
  };

  using Rangef = Range<float>;
  using Rangei = Range<int>;
  using Rangeu = Range<unsigned int>;
}
