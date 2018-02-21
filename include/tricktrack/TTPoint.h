#ifndef SEEDING_TTPOINT_HPP
#define SEEDING_TTPOINT_HPP

#include <algorithm>
#include <cmath>
#include <ostream>
#include <vector>

namespace tricktrack {


class TTPoint {
public:
  TTPoint(double x, double y, double z, double t, unsigned int id) : m_coordinates{x, y, z, t}, m_identifier(id) {}

  double x() const { return m_coordinates[0]; }
  double y() const { return m_coordinates[1]; }
  double z() const { return m_coordinates[2]; }
  double t() const { return m_coordinates[3]; }
  double rho() const { return std::sqrt(std::pow(m_coordinates[0], 2) + std::pow(m_coordinates[1], 2)); }
  double phi() const { return std::atan2(m_coordinates[1], m_coordinates[0]); }
  const unsigned int identifier() const { return m_identifier; }

  double& operator[](unsigned int const i) { return m_coordinates[i]; }

  double const& operator[](unsigned int const i) const { return m_coordinates[i]; }
  unsigned int getId() const { return m_identifier; }

private:
  std::array<double, 4> m_coordinates;
  unsigned int m_identifier;
};


}  // namespace tricktrack

#endif  // SEEDING_TTPOINT_HPP
