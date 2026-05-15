#pragma once

#include "./aliases/aliases.h"
#include "./enums.h"


namespace dstr {

    
  struct Resident {
    string id;
    City city;
    i32 age;
    ModeOfTransport transport;
    i32 daily_distance_km;
    float carbon_emission_factor;
    i32 avg_days_per_month;


    // Computed: monthly carbon emission (kg CO2)
    float monthly_emission() const {
      return static_cast<float>(daily_distance_km)
        * carbon_emission_factor
        * static_cast<float>(avg_days_per_month);
    }


    // Derive age group from age field
    AgeGroup age_group() const {
      if (age >= 6 && age <= 17) { return AgeGroup::CHILDREN_TEENAGERS; }
      if (age >= 18 && age <= 25) { return AgeGroup::YOUNG_ADULTS; }
      if (age >= 26 && age <= 45) { return AgeGroup::WORKING_ADULTS_EARLY; }
      if (age >= 46 && age <= 60) { return AgeGroup::WORKING_ADULTS_LATE; }
      if (age >= 61 && age <= 100) { return AgeGroup::SENIOR_CITIZENS; }
      return AgeGroup::UNKNOWN;
    }


    bool operator==(const Resident& other) const {
      return id == other.id;
    }

    bool operator!=(const Resident& other) const {
      return !(*this == other);
    }


    // Sort by monthly emission for List::sort()
    bool operator>(const Resident& other) const {
      return monthly_emission() > other.monthly_emission();
    }

    bool operator<(const Resident& other) const {
      return monthly_emission() < other.monthly_emission();
    }


    friend std::ostream& operator<<(std::ostream& os, const Resident& r) {
      os << r.id
        << " | Age: " << r.age
        << " | Dist: " << r.daily_distance_km << " km"
        << " | Emission: " << r.monthly_emission() << " kg CO2";
      return os;
    }
  };


} // namespace dstr
