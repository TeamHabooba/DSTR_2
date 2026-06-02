// robot.h
#pragma once


#include <common/aliases/aliases.h>
#include <common/enums.h>
#include <common/position.h>


namespace dstr {


  class Pathfinder;


  class Robot {
   private:
    robot_id id_;
    RobotStatus status_;
    GridPosition position_;
    GridPosition home_position_;
    usize tasks_assigned_;
    sp<Pathfinder> pathfinder_;

   public:
    Robot() noexcept;
    Robot(robot_id id, RobotStatus status, GridPosition position);
    Robot(const Robot& other);
    Robot(Robot&& other) noexcept;

    bool operator==(const Robot& other) const;
    bool operator!=(const Robot& other) const;

    Robot& operator=(const Robot& other);
    Robot& operator=(Robot&& other) noexcept;

    robot_id id() const;
    RobotStatus status() const;
    GridPosition position() const;
    GridPosition home_position() const;
    usize tasks_assigned() const;
    sp<Pathfinder> pathfinder() const;

    void set_status(RobotStatus status);
    void set_position(GridPosition position);
    void set_home_position(GridPosition position);
    void set_pathfinder(sp<Pathfinder> pathfinder);

    void increment_tasks();
  };


} // namespace dstr
