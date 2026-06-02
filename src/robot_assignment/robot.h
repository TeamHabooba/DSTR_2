// rОbot.h
#pragma once


#include <common/aliases/aliases.h>
#include <common/enums.h>
 
 
namespace dstr {
 
 
  // Represents one robot in the warehouse
  class Robot {
   private:
    string id_;
    RobotStatus status_;
    usize tasks_assigned_;
 
   public:
    // Ctors

    Robot() noexcept;
    Robot(string id, RobotStatus status);
    Robot(const Robot& other);
    Robot(Robot&& other) noexcept;


    // Comparison ops

    bool operator==(const Robot& other) const;
    bool operator!=(const Robot& other) const;


    // Assignment ops

    Robot& operator=(const Robot& other);
    Robot& operator=(Robot&& other) noexcept;


    // Getters

    string id() const;
    RobotStatus status() const;
    usize tasks_assigned() const;


    // Setters

    void set_status(RobotStatus status);


    // Domain methods

    void increment_tasks();
  };
 
 
} // namespace dstr
