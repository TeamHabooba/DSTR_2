// app_stÐte.h
#pragma once


#include <area_layout/area_layout.h>
#include <common/common.h>
#include <order_management/task_queue.h>
#include <robot_assignment/robot_queue.h>



namespace dstr {


	struct ItemIndexEntry {
		item_id id;
		string name;
		GridPosition location;
		usize storage_index;
	};


	struct AppState {
		std::ostream& os;
		std::istream& is;
		bool first_run = true;
		sp<AreaLayout> layout;
		RobotQueue robots;
		TaskQueue tasks;
		Array<ItemIndexEntry> item_index;
		item_id next_item_id = 1;
		storage_id next_storage_id = 1;
		robot_id next_robot_id = 1;
		task_id next_task_id = 1;

		AppState(std::ostream& os, std::istream& is)
				: os{ os },
					is{ is },
					layout{ std::make_shared<AreaLayout>() },
					robots{},
					tasks{},
					item_index{} {
		}

	};


}
