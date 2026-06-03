#pragma once


#include <common/common.h>


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

	// Utility function prototype
	Result<int> get_option(std::istream& is);


	// Application UI (CLI) entry point
	Result<void> cli_start(char* argv[], int argc, AppState& state);


	namespace {


		struct ExecutionSession {
			Task task;
			robot_id robot;
			GridPosition station;
			GridPosition pickup;
			GridPosition dropoff;
			Path station_to_pickup;
			Path pickup_to_dropoff;
			Path dropoff_to_station;
			Array<GridPosition> route;
			Stack<GridPosition> reverse_stack;
			usize current_index = 0;
			usize pickup_index = 0;
			usize dropoff_index = 0;
			usize station_index = 0;
			bool finished = false;
			bool cancelled = false;
		};


		// =====Format helpers

		string cell_type_string(CellType type) {
			switch (type) {
			case CellType::EMPTY:
				return string(strings::VAL_EMPTY);
			case CellType::ROBOT:
				return string(strings::VAL_ROBOT);
			case CellType::OBSTACLE:
				return string(strings::VAL_OBSTACLE);
			case CellType::DROP_OFF:
				return string(strings::VAL_DROP_OFF);
			case CellType::PICK_UP:
				return string(strings::VAL_PICK_UP);
			case CellType::STATION:
				return string(strings::VAL_STATION);
			case CellType::NONE:
			default:
				return string(strings::VAL_NONE);
			}
		}

		string task_status_string(TaskStatus status) {
			if (status == TaskStatus::ASSIGNED) {
				return string(strings::VAL_ASSIGNED);
			}
			if (status == TaskStatus::COMPLETED) {
				return string(strings::VAL_COMPLETED);
			}
			if (status == TaskStatus::CANCELLED) {
				return string(strings::VAL_CANCELLED);
			}
			return string(strings::VAL_PENDING);
		}

		void clear_screen(AppState& state) {
			state.os << "\033[2J\033[H";
			state.os.flush();
		}

		void print_position(std::ostream& os, GridPosition position) {
			os << '(' << position.row << ',' << position.col << ')';
		}

		void pause(AppState& state);

		void print_result(AppState& state, Result<void> result) {
			if (result) {
				state.os << strings::MSG_DONE << strings::NL;
			}
			else {
				state.os << strings::MSG_ERROR_PREFIX << result.error().message() << strings::NL;
			}
			pause(state);
		}

		void pause(AppState& state) {
			state.os << strings::MSG_RETURN;
			await_return(state.is);
		}

		void print_layout(AppState& state) {
			print_header(state.os, string(strings::MSG_LAYOUT_MENU));
			if (state.layout) {
				state.layout->print(state.os);
			}
			state.os << strings::NL;
		}

		void print_menu_header(AppState& state, string title) {
			clear_screen(state);
			print_layout(state);
			print_header(state.os, title);
		}

		Array<GridPosition> station_positions(AppState& state) {
			Array<GridPosition> stations;
			for (usize row = 0; row < state.layout->rows(); row++) {
				for (usize col = 0; col < state.layout->cols(); col++) {
					GridPosition position(row, col);
					auto type = state.layout->type_at(position);
					if (type && type.value() == CellType::STATION) {
						stations.push_back(position);
					}
				}
			}
			return stations;
		}

		void rebuild_item_index(AppState& state) {
			state.item_index.clear();
			for (usize row = 0; row < state.layout->rows(); row++) {
				for (usize col = 0; col < state.layout->cols(); col++) {
					GridPosition position(row, col);
					auto storage = state.layout->storage_at(position);
					if (!storage) {
						continue;
					}
					for (usize i = 0; i < storage.value().size(); i++) {
						auto item = storage.value().item_at(i);
						if (item) {
							state.item_index.push_back(ItemIndexEntry{
								item.value().id(),
								item.value().name(),
								position,
								i
								});
						}
					}
				}
			}
		}

		Result<ItemIndexEntry> find_item_entry(AppState& state, item_id id) {
			rebuild_item_index(state);
			for (usize i = 0; i < state.item_index.size(); i++) {
				ItemIndexEntry entry = state.item_index.unchecked_at(i);
				if (entry.id == id) {
					return Ok(entry);
				}
			}
			return Err<ItemIndexEntry>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_TASK_ITEM_NOT_FOUND));
		}

		void refresh_next_ids(AppState& state) {
			robot_id max_robot = 0;
			for (usize i = 0; i < state.robots.size(); i++) {
				if (state.robots.robot_at(i).id() > max_robot) {
					max_robot = state.robots.robot_at(i).id();
				}
			}

			task_id max_task = 0;
			for (usize i = 0; i < state.tasks.pending_size(); i++) {
				auto task = state.tasks.pending_at(i);
				if (task && task.value().id() > max_task) {
					max_task = task.value().id();
				}
			}
			for (usize i = 0; i < state.tasks.assigned_size(); i++) {
				auto task = state.tasks.assigned_at(i);
				if (task && task.value().id() > max_task) {
					max_task = task.value().id();
				}
			}
			for (usize i = 0; i < state.tasks.completed_size(); i++) {
				auto task = state.tasks.completed_at(i);
				if (task && task.value().id() > max_task) {
					max_task = task.value().id();
				}
			}

			item_id max_item = 0;
			storage_id max_storage = 0;
			rebuild_item_index(state);
			for (usize row = 0; row < state.layout->rows(); row++) {
				for (usize col = 0; col < state.layout->cols(); col++) {
					auto storage = state.layout->storage_at(GridPosition(row, col));
					if (!storage) {
						continue;
					}
					if (storage.value().id() > max_storage) {
						max_storage = storage.value().id();
					}
					for (usize i = 0; i < storage.value().size(); i++) {
						auto item = storage.value().item_at(i);
						if (item && item.value().id() > max_item) {
							max_item = item.value().id();
						}
					}
				}
			}

			state.next_robot_id = max_robot + 1;
			state.next_task_id = max_task + 1;
			state.next_item_id = max_item + 1;
			state.next_storage_id = max_storage + 1;
		}


		// =====Input helpers

		Result<string> read_text(AppState& state, string prompt) {
			state.os << prompt;
			string value;
			std::getline(state.is, value);
			return Ok(trim(value));
		}

		Result<usize> read_usize(AppState& state, string prompt) {
			auto value = read_text(state, prompt);
			if (!value) {
				return Err<usize>(value.error().code(), value.error().message());
			}
			try {
				return Ok(static_cast<usize>(std::stoull(value.value())));
			}
			catch (...) {
				return Err<usize>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_NOT_NUMBER));
			}
		}

		Result<u32> read_u32(AppState& state, string prompt) {
			auto value = read_usize(state, prompt);
			if (!value) {
				return Err<u32>(value.error().code(), value.error().message());
			}
			return Ok(static_cast<u32>(value.value()));
		}

		Result<GridPosition> read_position(AppState& state) {
			auto row = read_usize(state, string(strings::MSG_INPUT_ROW));
			if (!row) {
				return Err<GridPosition>(row.error().code(), row.error().message());
			}
			auto col = read_usize(state, string(strings::MSG_INPUT_COL));
			if (!col) {
				return Err<GridPosition>(col.error().code(), col.error().message());
			}
			return Ok(GridPosition(row.value(), col.value()));
		}

		RobotStatus read_robot_status(AppState& state) {
			auto status = read_usize(state, string(strings::MSG_INPUT_STATUS));
			if (status && status.value() == 2) {
				return RobotStatus::BUSY;
			}
			if (status && status.value() == 3) {
				return RobotStatus::MAINTENANCE;
			}
			return RobotStatus::AVAILABLE;
		}


		// =====List helpers

		void print_robot(AppState& state, const Robot& robot) {
			state.os << strings::MSG_ROBOT_ID << robot.id() << strings::TXT_SPACE
				<< strings::MSG_STATUS << robot_status_string(robot.status()) << strings::TXT_SPACE
				<< strings::MSG_POSITION;
			print_position(state.os, robot.position());
			state.os << strings::TXT_SPACE << strings::MSG_HOME;
			print_position(state.os, robot.home_position());
			state.os << strings::TXT_SPACE << strings::MSG_TASKS_ASSIGNED << robot.tasks_assigned() << strings::NL;
		}

		void list_robots(AppState& state) {
			print_menu_header(state, string(strings::MSG_ROBOT_HEADER));
			if (state.robots.is_empty()) {
				state.os << strings::MSG_NO_ROBOTS << strings::NL;
				pause(state);
				return;
			}
			for (usize i = 0; i < state.robots.size(); i++) {
				print_robot(state, state.robots.robot_at(i));
			}
			pause(state);
		}

		void print_task(AppState& state, const Task& task) {
			state.os << strings::MSG_TASK_ID << task.id() << strings::TXT_SPACE
				<< strings::MSG_ITEM_ID << task.item() << strings::TXT_SPACE
				<< strings::MSG_STATUS << task_status_string(task.status()) << strings::TXT_SPACE
				<< strings::MSG_ASSIGNED_ROBOT << task.assigned_robot() << strings::TXT_SPACE
				<< strings::MSG_PICKUP;
			print_position(state.os, task.pickup());
			state.os << strings::TXT_SPACE << strings::MSG_DROPOFF;
			print_position(state.os, task.dropoff());
			state.os << strings::NL;
		}

		void list_task_section(AppState& state, string title, usize count, bool assigned, bool completed) {
			state.os << title << strings::NL;
			if (count == 0) {
				state.os << strings::MSG_NO_TASKS << strings::NL;
				return;
			}
			for (usize i = 0; i < count; i++) {
				auto task = completed ? state.tasks.completed_at(i)
					: (assigned ? state.tasks.assigned_at(i) : state.tasks.pending_at(i));
				if (task) {
					print_task(state, task.value());
				}
			}
		}

		void list_tasks(AppState& state) {
			print_menu_header(state, string(strings::MSG_TASK_MENU));
			list_task_section(state, string(strings::MSG_PENDING_TASKS), state.tasks.pending_size(), false, false);
			state.os << strings::MSG_SECTION_SEPARATOR << strings::NL;
			list_task_section(state, string(strings::MSG_ASSIGNED_TASKS), state.tasks.assigned_size(), true, false);
			state.os << strings::MSG_SECTION_SEPARATOR << strings::NL;
			list_task_section(state, string(strings::MSG_COMPLETED_TASKS), state.tasks.completed_size(), false, true);
			pause(state);
		}

		void list_storage_items(AppState& state, Storage storage) {
			if (storage.empty()) {
				state.os << strings::MSG_NO_ITEMS << strings::NL;
				return;
			}
			for (usize i = 0; i < storage.size(); i++) {
				auto item = storage.item_at(i);
				if (item) {
					state.os << strings::MSG_ITEM_ID << item.value().id() << strings::TXT_SPACE
						<< strings::MSG_ITEM_STORAGE_INDEX << i << strings::TXT_SPACE
						<< strings::MSG_INPUT_NAME << item.value().name() << strings::TXT_SPACE
						<< strings::MSG_QTY << item.value().quantity() << strings::TXT_SPACE
						<< strings::MSG_POSITION;
					print_position(state.os, item.value().location());
					state.os << strings::NL;
				}
			}
		}

		void print_item_match(AppState& state, const Item& item, GridPosition storage_position, usize storage_index) {
			state.os << strings::MSG_ITEM_ID << item.id() << strings::TXT_SPACE
				<< strings::MSG_ITEM_STORAGE_INDEX << storage_index << strings::TXT_SPACE
				<< strings::MSG_INPUT_NAME << item.name() << strings::TXT_SPACE
				<< strings::MSG_QTY << item.quantity() << strings::TXT_SPACE
				<< strings::MSG_POSITION;
			print_position(state.os, storage_position);
			state.os << strings::NL;
		}

		usize print_item_matches_by_id(AppState& state, item_id id) {
			rebuild_item_index(state);
			usize matches = 0;
			for (usize i = 0; i < state.item_index.size(); i++) {
				auto entry = state.item_index.unchecked_at(i);
				if (entry.id != id) {
					continue;
				}
				auto storage = state.layout->storage_at(entry.location);
				if (!storage) {
					continue;
				}
				auto item = storage.value().item_at(entry.storage_index);
				if (item) {
					print_item_match(state, item.value(), entry.location, entry.storage_index);
					matches++;
				}
			}
			return matches;
		}

		usize print_item_matches_by_name(AppState& state, const string& name) {
			rebuild_item_index(state);
			usize matches = 0;
			for (usize i = 0; i < state.item_index.size(); i++) {
				auto entry = state.item_index.unchecked_at(i);
				if (entry.name != name) {
					continue;
				}
				auto storage = state.layout->storage_at(entry.location);
				if (!storage) {
					continue;
				}
				auto item = storage.value().item_at(entry.storage_index);
				if (item) {
					print_item_match(state, item.value(), entry.location, entry.storage_index);
					matches++;
				}
			}
			return matches;
		}

		void print_route_position(AppState& state, GridPosition position, bool first) {
			if (!first) {
				state.os << strings::TXT_ARROW;
			}
			print_position(state.os, position);
		}

		void print_path(AppState& state, const Path& path) {
			for (usize i = 0; i < path.size(); i++) {
				auto step = path.at(i);
				if (step) {
					print_route_position(state, step.value(), i == 0);
				}
			}
			state.os << strings::NL;
		}

		void print_route(AppState& state, const Array<GridPosition>& route) {
			for (usize i = 0; i < route.size(); i++) {
				print_route_position(state, route.unchecked_at(i), i == 0);
			}
			state.os << strings::NL;
		}

		void print_reverse_stack(AppState& state, const Stack<GridPosition>& stack) {
			state.os << strings::MSG_EXEC_REVERSE_STACK;
			if (stack.empty()) {
				state.os << strings::MSG_EXEC_STACK_EMPTY << strings::NL;
				return;
			}
			for (usize i = stack.size(); i > 0; i--) {
				auto step = stack.at(i - 1);
				if (step) {
					print_route_position(state, step.value(), i == stack.size());
				}
			}
			state.os << strings::NL;
		}

		string next_checkpoint_name(const ExecutionSession& session) {
			if (session.current_index < session.pickup_index) {
				return string(strings::MSG_EXEC_CHECKPOINT_PICKUP);
			}
			if (session.current_index < session.dropoff_index) {
				return string(strings::MSG_EXEC_CHECKPOINT_DROPOFF);
			}
			if (session.current_index < session.station_index) {
				return string(strings::MSG_EXEC_CHECKPOINT_STATION);
			}
			return string(strings::MSG_EXEC_CHECKPOINT_DONE);
		}

		usize next_checkpoint_index(const ExecutionSession& session) {
			if (session.current_index < session.pickup_index) {
				return session.pickup_index;
			}
			if (session.current_index < session.dropoff_index) {
				return session.dropoff_index;
			}
			return session.station_index;
		}

		Result<void> append_path(Array<GridPosition>& route, const Path& path, bool skip_first) {
			usize start = skip_first ? 1 : 0;
			for (usize i = start; i < path.size(); i++) {
				auto step = path.at(i);
				if (!step) {
					return Err(step.error().code(), step.error().message());
				}
				route.push_back(step.value());
			}
			return Ok();
		}

		Result<void> complete_execution(AppState& state, ExecutionSession& session) {
			if (session.finished) {
				return Ok();
			}
			auto moved = state.robots.return_robot_home(session.robot);
			if (!moved) {
				return moved;
			}
			auto status = state.robots.set_robot_status(session.robot, RobotStatus::AVAILABLE);
			if (!status) {
				return status;
			}
			auto completed = state.tasks.complete(session.task.id());
			if (!completed) {
				return completed;
			}
			session.finished = true;
			state.os << strings::MSG_EXEC_COMPLETED << strings::NL;
			return Ok();
		}

		Result<void> cancel_execution(AppState& state, ExecutionSession& session) {
			if (session.finished) {
				return Ok();
			}
			auto moved = state.robots.return_robot_home(session.robot);
			if (!moved) {
				return moved;
			}
			auto status = state.robots.set_robot_status(session.robot, RobotStatus::AVAILABLE);
			if (!status) {
				return status;
			}
			auto cancelled = state.tasks.cancel(session.task.id());
			if (!cancelled) {
				return cancelled;
			}
			session.finished = true;
			session.cancelled = true;
			state.os << strings::MSG_EXEC_CANCELLED << strings::NL;
			return Ok();
		}

		Result<void> apply_current_robot_position(AppState& state, ExecutionSession& session) {
			return state.robots.set_robot_position(session.robot, session.route.unchecked_at(session.current_index));
		}

		Result<void> advance_execution_step(AppState& state, ExecutionSession& session, bool print_step) {
			if (session.finished) {
				state.os << strings::MSG_EXEC_ALREADY_DONE << strings::NL;
				return Ok();
			}
			if (session.current_index >= session.station_index) {
				state.os << strings::MSG_EXEC_REACHED_STATION << strings::NL;
				return complete_execution(state, session);
			}
			session.reverse_stack.push(session.route.unchecked_at(session.current_index));
			session.current_index++;
			auto moved = apply_current_robot_position(state, session);
			if (!moved) {
				return moved;
			}
			if (print_step) {
				state.os << strings::MSG_EXEC_NEXT_STEP;
				print_position(state.os, session.route.unchecked_at(session.current_index));
				state.os << strings::NL;
			}
			if (session.current_index == session.pickup_index) {
				state.os << strings::MSG_EXEC_REACHED_PICKUP << strings::NL;
			}
			if (session.current_index == session.dropoff_index) {
				state.os << strings::MSG_EXEC_REACHED_DROPOFF << strings::NL;
			}
			if (session.current_index == session.station_index) {
				state.os << strings::MSG_EXEC_REACHED_STATION << strings::NL;
				return complete_execution(state, session);
			}
			return Ok();
		}

		Result<void> step_execution_back(AppState& state, ExecutionSession& session) {
			if (session.finished) {
				state.os << strings::MSG_EXEC_ALREADY_DONE << strings::NL;
				return Ok();
			}
			if (session.reverse_stack.empty()) {
				state.os << strings::MSG_EXEC_STACK_EMPTY << strings::NL;
				return Ok();
			}
			auto previous = session.reverse_stack.pop();
			if (!previous) {
				return Err(previous.error().code(), previous.error().message());
			}
			if (session.current_index > 0) {
				session.current_index--;
			}
			auto moved = state.robots.set_robot_position(session.robot, previous.value());
			if (!moved) {
				return moved;
			}
			state.os << strings::MSG_EXEC_STEP_BACK;
			print_position(state.os, previous.value());
			state.os << strings::NL;
			return Ok();
		}

		Result<void> run_to_next_checkpoint(AppState& state, ExecutionSession& session) {
			if (session.finished) {
				state.os << strings::MSG_EXEC_ALREADY_DONE << strings::NL;
				return Ok();
			}
			if (session.current_index >= session.station_index) {
				state.os << strings::MSG_EXEC_REACHED_STATION << strings::NL;
				return complete_execution(state, session);
			}
			usize target = next_checkpoint_index(session);
			state.os << strings::MSG_EXEC_NEXT_CHECKPOINT << next_checkpoint_name(session) << strings::NL;
			while (!session.finished && session.current_index < target) {
				auto advanced = advance_execution_step(state, session, true);
				if (!advanced) {
					return advanced;
				}
			}
			return Ok();
		}

		Result<ExecutionSession> create_execution_session(AppState& state, const Task& task) {
			auto robot = state.robots.robot_by_id(task.assigned_robot());
			if (!robot) {
				return Err<ExecutionSession>(robot.error().code(), robot.error().message());
			}
			sp<Pathfinder> pathfinder = robot.value().pathfinder();
			if (!pathfinder) {
				pathfinder = std::make_shared<Pathfinder>(state.layout);
				auto stored = state.robots.set_robot_pathfinder(robot.value().id(), pathfinder);
				if (!stored) {
					return Err<ExecutionSession>(stored.error().code(), stored.error().message());
				}
			}
			pathfinder->set_layout(state.layout);

			ExecutionSession session;
			session.task = task;
			session.robot = robot.value().id();
			session.station = robot.value().home_position();
			session.pickup = task.pickup();
			session.dropoff = task.dropoff();

			auto first = pathfinder->find_path(session.station, session.pickup);
			if (!first) {
				return Err<ExecutionSession>(first.error().code(), first.error().message());
			}
			auto second = pathfinder->find_path(session.pickup, session.dropoff);
			if (!second) {
				return Err<ExecutionSession>(second.error().code(), second.error().message());
			}
			auto third = pathfinder->find_path(session.dropoff, session.station);
			if (!third) {
				return Err<ExecutionSession>(third.error().code(), third.error().message());
			}
			session.station_to_pickup = first.value();
			session.pickup_to_dropoff = second.value();
			session.dropoff_to_station = third.value();

			auto appended = append_path(session.route, session.station_to_pickup, false);
			if (!appended) {
				return Err<ExecutionSession>(appended.error().code(), appended.error().message());
			}
			session.pickup_index = session.route.size() - 1;
			appended = append_path(session.route, session.pickup_to_dropoff, true);
			if (!appended) {
				return Err<ExecutionSession>(appended.error().code(), appended.error().message());
			}
			session.dropoff_index = session.route.size() - 1;
			appended = append_path(session.route, session.dropoff_to_station, true);
			if (!appended) {
				return Err<ExecutionSession>(appended.error().code(), appended.error().message());
			}
			session.station_index = session.route.size() - 1;
			auto positioned = apply_current_robot_position(state, session);
			if (!positioned) {
				return Err<ExecutionSession>(positioned.error().code(), positioned.error().message());
			}
			return Ok(session);
		}

		void print_execution_header(AppState& state, const ExecutionSession& session) {
			print_menu_header(state, string(strings::MSG_EXEC_MENU));
			state.os << strings::MSG_EXEC_TASK << session.task.id() << strings::TXT_SPACE
				<< strings::MSG_EXEC_ROBOT << session.robot << strings::NL
				<< strings::MSG_EXEC_CURRENT;
			print_position(state.os, session.route.unchecked_at(session.current_index));
			state.os << strings::TXT_SPACE << strings::MSG_EXEC_NEXT_CHECKPOINT
				<< next_checkpoint_name(session) << strings::NL;
			state.os << strings::MSG_SECTION_SEPARATOR << strings::NL;
		}

		Result<void> execution_menu(AppState& state, ExecutionSession& session) {
			bool running = true;
			while (running) {
				print_execution_header(state, session);
				state.os
					<< strings::MSG_EXEC_OPTION_1 << strings::NL
					<< strings::MSG_EXEC_OPTION_2 << strings::NL
					<< strings::MSG_EXEC_OPTION_3 << strings::NL
					<< strings::MSG_EXEC_OPTION_4 << strings::NL
					<< strings::MSG_EXEC_OPTION_5 << strings::NL
					<< strings::MSG_EXEC_OPTION_6 << strings::NL
					<< strings::MSG_EXEC_OPTION_7 << strings::NL
					<< strings::MSG_EXEC_OPTION_8 << strings::NL
					<< strings::MSG_EXEC_OPTION_0 << strings::NL
					<< strings::MSG_OPTION;
				auto option = get_option(state.is);
				if (!option) {
					state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
					pause(state);
					continue;
				}
				switch (option.value()) {
				case 0:
					if (session.finished) {
						running = false;
					}
					else {
						state.os << strings::MSG_EXEC_LEAVE_BLOCKED << strings::NL;
						pause(state);
					}
					break;
				case 1:
					state.os << strings::MSG_EXEC_FULL_PATH << strings::NL;
					print_route(state, session.route);
					pause(state);
					break;
				case 2:
					state.os << strings::MSG_EXEC_STATION_PICKUP_PATH << strings::NL;
					print_path(state, session.station_to_pickup);
					pause(state);
					break;
				case 3:
					state.os << strings::MSG_EXEC_PICKUP_DROPOFF_PATH << strings::NL;
					print_path(state, session.pickup_to_dropoff);
					pause(state);
					break;
				case 4:
					print_reverse_stack(state, session.reverse_stack);
					pause(state);
					break;
				case 5: {
					auto cancelled = cancel_execution(state, session);
					if (!cancelled) {
						state.os << strings::MSG_ERROR_PREFIX << cancelled.error().message() << strings::NL;
					}
					pause(state);
					running = false;
					break;
				}
				case 6: {
					auto advanced = advance_execution_step(state, session, true);
					if (!advanced) {
						state.os << strings::MSG_ERROR_PREFIX << advanced.error().message() << strings::NL;
					}
					pause(state);
					break;
				}
				case 7: {
					auto backed = step_execution_back(state, session);
					if (!backed) {
						state.os << strings::MSG_ERROR_PREFIX << backed.error().message() << strings::NL;
					}
					pause(state);
					break;
				}
				case 8: {
					auto checkpoint = run_to_next_checkpoint(state, session);
					if (!checkpoint) {
						state.os << strings::MSG_ERROR_PREFIX << checkpoint.error().message() << strings::NL;
					}
					pause(state);
					break;
				}
				default:
					state.os << strings::MSG_INVALID_OPTION << strings::NL;
					pause(state);
					break;
				}
			}
			return Ok();
		}


		// =====Layout menu
		Result<void> layout_menu(AppState& state) {
			bool running = true;
			while (running) {
				print_menu_header(state, string(strings::MSG_LAYOUT_MENU));
				state.os
					<< strings::MSG_LAYOUT_OPTION_1 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_2 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_3 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_4 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_5 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_6 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_7 << strings::NL
					<< strings::MSG_LAYOUT_OPTION_0 << strings::NL
					<< strings::MSG_OPTION;
				auto option = get_option(state.is);
				if (!option) {
					state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
					pause(state);
					continue;
				}
				switch (option.value()) {
				case 0:
					running = false;
					break;
				case 1: {
					auto rows = read_usize(state, string(strings::MSG_INPUT_ROW));
					auto cols = read_usize(state, string(strings::MSG_INPUT_COL));
					if (rows && cols) {
						print_result(state, state.layout->resize(rows.value(), cols.value()));
					}
					break;
				}
				case 2: {
					auto position = read_position(state);
					if (position) {
						print_result(state, state.layout->set_empty(position.value()));
					}
					break;
				}
				case 3: {
					auto position = read_position(state);
					if (position) {
						print_result(state, state.layout->set_obstacle(position.value()));
					}
					break;
				}
				case 4: {
					auto position = read_position(state);
					if (position) {
						print_result(state, state.layout->set_type(position.value(), CellType::STATION));
					}
					break;
				}
				case 5: {
					auto position = read_position(state);
					if (position) {
						print_result(state, state.layout->set_type(position.value(), CellType::DROP_OFF));
					}
					break;
				}
				case 6: {
					auto position = read_position(state);
					if (position) {
						Storage storage(state.next_storage_id++);
						print_result(state, state.layout->set_storage(position.value(), storage));
					}
					break;
				}
				case 7: {
					auto position = read_position(state);
					if (position) {
						auto type = state.layout->type_at(position.value());
						if (type) {
							state.os << strings::MSG_CELL_TYPE << cell_type_string(type.value()) << strings::NL;
						}
						else {
							state.os << strings::MSG_ERROR_PREFIX << type.error().message() << strings::NL;
						}
					}
					pause(state);
					break;
				}
				default:
					state.os << strings::MSG_INVALID_OPTION << strings::NL;
					pause(state);
					break;
				}
			}
			return Ok();
		}


		// =====Robots menu
		Result<void> robots_menu(AppState& state) {
			bool running = true;
			while (running) {
				print_menu_header(state, string(strings::MSG_ROBOT_MENU));
				state.os
					<< strings::MSG_ROBOT_OPTION_1 << strings::NL
					<< strings::MSG_ROBOT_OPTION_2 << strings::NL
					<< strings::MSG_ROBOT_OPTION_3 << strings::NL
					<< strings::MSG_ROBOT_OPTION_0 << strings::NL
					<< strings::MSG_OPTION;
				auto option = get_option(state.is);
				if (!option) {
					state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
					pause(state);
					continue;
				}
				switch (option.value()) {
				case 0:
					running = false;
					break;
				case 1: {
					auto stations = station_positions(state);
					if (stations.empty()) {
						state.os << strings::MSG_NO_STATIONS << strings::NL;
						pause(state);
						break;
					}
					state.os << strings::MSG_STATIONS << strings::NL;
					for (usize i = 0; i < stations.size(); i++) {
						state.os << i << strings::TXT_RIGHT_BRACKET_SPACE;
						print_position(state.os, stations.unchecked_at(i));
						state.os << strings::NL;
						if ((i + 1) % 10 == 0 && i + 1 < stations.size()) {
							state.os << strings::MSG_STATION_PAGE_CONTINUE;
							await_return(state.is);
						}
					}
					auto station_index = read_usize(state, string(strings::MSG_STATION_INDEX));
					if (station_index && station_index.value() < stations.size()) {
						GridPosition position = stations.unchecked_at(station_index.value());
						Robot robot(state.next_robot_id++, RobotStatus::AVAILABLE, position);
						robot.set_pathfinder(std::make_shared<Pathfinder>(state.layout));
						print_result(state, state.robots.enqueue(robot));
					}
					else {
						state.os << strings::MSG_INVALID_OPTION << strings::NL;
						pause(state);
					}
					break;
				}
				case 2:
					list_robots(state);
					break;
				case 3: {
					auto id = read_u32(state, string(strings::MSG_INPUT_ID));
					RobotStatus status = read_robot_status(state);
					if (id) {
						print_result(state, state.robots.set_robot_status(id.value(), status));
					}
					break;
				}
				default:
					state.os << strings::MSG_INVALID_OPTION << strings::NL;
					pause(state);
					break;
				}
			}
			return Ok();
		}


		// =====Inventory menu
		Result<void> inventory_menu(AppState& state) {
			bool running = true;
			while (running) {
				print_menu_header(state, string(strings::MSG_INV_MENU));
				state.os
					<< strings::MSG_INV_OPTION_1 << strings::NL
					<< strings::MSG_INV_OPTION_2 << strings::NL
					<< strings::MSG_INV_OPTION_3 << strings::NL
					<< strings::MSG_INV_OPTION_4 << strings::NL
					<< strings::MSG_INV_OPTION_5 << strings::NL
					<< strings::MSG_INV_OPTION_0 << strings::NL
					<< strings::MSG_OPTION;
				auto option = get_option(state.is);
				if (!option) {
					state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
					pause(state);
					continue;
				}
				switch (option.value()) {
				case 0:
					running = false;
					break;
				case 1: {
					auto position = read_position(state);
					auto name = read_text(state, string(strings::MSG_INPUT_NAME));
					auto description = read_text(state, string(strings::MSG_INPUT_DESC));
					auto quantity = read_usize(state, string(strings::MSG_INPUT_QTY));
					if (position && name && description && quantity) {
						auto storage = state.layout->storage_at(position.value());
						Storage editable = storage ? storage.value() : Storage(state.next_storage_id++);
						Item item(state.next_item_id++, name.value(), description.value(), quantity.value(), position.value());
						auto added = editable.add_item(item);
						if (added) {
							auto stored = state.layout->set_storage(position.value(), editable);
							if (stored) {
								rebuild_item_index(state);
							}
							print_result(state, stored);
						}
						else {
							print_result(state, added);
						}
					}
					break;
				}
				case 2: {
					auto position = read_position(state);
					if (position) {
						auto storage = state.layout->storage_at(position.value());
						if (storage) {
							list_storage_items(state, storage.value());
						}
						else {
							state.os << strings::MSG_ERROR_PREFIX << storage.error().message() << strings::NL;
						}
					}
					pause(state);
					break;
				}
				case 3: {
					auto position = read_position(state);
					auto id = read_u32(state, string(strings::MSG_ITEM_ID));
					if (position && id) {
						auto storage = state.layout->storage_at(position.value());
						if (storage) {
							Storage editable = storage.value();
							auto removed = editable.remove_item(id.value());
							if (removed) {
								auto stored = state.layout->set_storage(position.value(), editable);
								if (stored) {
									rebuild_item_index(state);
								}
								print_result(state, stored);
							}
							else {
								print_result(state, removed);
							}
						}
					}
					break;
				}
				case 4: {
					auto id = read_u32(state, string(strings::MSG_ITEM_ID));
					if (id) {
						usize matches = print_item_matches_by_id(state, id.value());
						if (matches == 0) {
							state.os << strings::MSG_NO_ITEM_MATCHES << strings::NL;
						}
					}
					pause(state);
					break;
				}
				case 5: {
					auto name = read_text(state, string(strings::MSG_INPUT_NAME));
					if (name) {
						usize matches = print_item_matches_by_name(state, name.value());
						if (matches == 0) {
							state.os << strings::MSG_NO_ITEM_MATCHES << strings::NL;
						}
					}
					pause(state);
					break;
				}
				default:
					state.os << strings::MSG_INVALID_OPTION << strings::NL;
					pause(state);
					break;
				}
			}
			return Ok();
		}


		// =====Task menu
		Result<void> tasks_menu(AppState& state) {
			bool running = true;
			while (running) {
				print_menu_header(state, string(strings::MSG_TASK_MENU));
				state.os
					<< strings::MSG_TASK_OPTION_1 << strings::NL
					<< strings::MSG_TASK_OPTION_2 << strings::NL
					<< strings::MSG_TASK_OPTION_3 << strings::NL
					<< strings::MSG_TASK_OPTION_4 << strings::NL
					<< strings::MSG_TASK_OPTION_5 << strings::NL
					<< strings::MSG_TASK_OPTION_0 << strings::NL
					<< strings::MSG_OPTION;
				auto option = get_option(state.is);
				if (!option) {
					state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
					pause(state);
					continue;
				}
				switch (option.value()) {
				case 0:
					running = false;
					break;
				case 1: {
					auto item = read_u32(state, string(strings::MSG_ITEM_ID));
					state.os << strings::MSG_INPUT_DROPOFF << strings::NL;
					auto dropoff = read_position(state);
					if (item && dropoff) {
						auto entry = find_item_entry(state, item.value());
						if (!entry) {
							state.os << strings::MSG_ERROR_PREFIX << entry.error().message() << strings::NL;
							pause(state);
							break;
						}
						state.os << strings::MSG_TASK_PICKUP_FROM_ITEM;
						print_position(state.os, entry.value().location);
						state.os << strings::NL;
						Task task(state.next_task_id++, item.value(), entry.value().location, dropoff.value());
						print_result(state, state.tasks.enqueue(task));
					}
					break;
				}
				case 2:
					list_tasks(state);
					break;
				case 3: {
					if (state.tasks.pending_size() == 0) {
						state.os << strings::MSG_NO_TASKS << strings::NL;
						pause(state);
						break;
					}
					auto robot = state.robots.assign_next();
					if (!robot) {
						state.os << strings::MSG_ERROR_PREFIX << robot.error().message() << strings::NL;
						pause(state);
						break;
					}
					auto assigned = state.tasks.assign_next(robot.value());
					if (assigned) {
						print_task(state, assigned.value());
					}
					else {
						state.robots.set_robot_status(robot.value(), RobotStatus::AVAILABLE);
						state.os << strings::MSG_ERROR_PREFIX << assigned.error().message() << strings::NL;
					}
					pause(state);
					break;
				}
				case 4: {
					if (state.tasks.assigned_size() == 0) {
						state.os << strings::MSG_NO_TASKS << strings::NL;
						pause(state);
						break;
					}
					list_task_section(state, string(strings::MSG_ASSIGNED_TASKS), state.tasks.assigned_size(), true, false);
					auto id = read_u32(state, string(strings::MSG_INPUT_EXECUTE_TASK));
					if (id) {
						auto task = state.tasks.assigned_by_id(id.value());
						if (!task) {
							state.os << strings::MSG_ERROR_PREFIX << task.error().message() << strings::NL;
							pause(state);
							break;
						}
						auto session = create_execution_session(state, task.value());
						if (!session) {
							state.os << strings::MSG_ERROR_PREFIX << session.error().message() << strings::NL;
							pause(state);
							break;
						}
						execution_menu(state, session.value());
					}
					break;
				}
				case 5: {
					state.os << strings::MSG_START << strings::NL;
					auto start = read_position(state);
					state.os << strings::MSG_DESTINATION << strings::NL;
					auto destination = read_position(state);
					if (start && destination) {
						Pathfinder pathfinder(state.layout);
						auto path = pathfinder.find_path(start.value(), destination.value());
						if (path) {
							state.os << strings::MSG_PATH;
							for (usize i = 0; i < path.value().size(); i++) {
								auto step = path.value().at(i);
								if (step) {
									print_position(state.os, step.value());
									state.os << strings::TXT_SPACE;
								}
							}
							state.os << strings::NL;
						}
						else {
							state.os << strings::MSG_ERROR_PREFIX << path.error().message() << strings::NL;
						}
					}
					pause(state);
					break;
				}
				default:
					state.os << strings::MSG_INVALID_OPTION << strings::NL;
					pause(state);
					break;
				}
			}
			return Ok();
		}


		// =====Files menu
		Result<void> files_menu(AppState& state) {
			bool running = true;
			while (running) {
				print_menu_header(state, string(strings::MSG_FILES_MENU));
				state.os
					<< strings::MSG_FILES_OPTION_1 << strings::NL
					<< strings::MSG_FILES_OPTION_2 << strings::NL
					<< strings::MSG_FILES_OPTION_3 << strings::NL
					<< strings::MSG_FILES_OPTION_4 << strings::NL
					<< strings::MSG_FILES_OPTION_5 << strings::NL
					<< strings::MSG_FILES_OPTION_6 << strings::NL
					<< strings::MSG_FILES_OPTION_7 << strings::NL
					<< strings::MSG_FILES_OPTION_8 << strings::NL
					<< strings::MSG_FILES_OPTION_0 << strings::NL
					<< strings::MSG_OPTION;
				auto option = get_option(state.is);
				if (!option) {
					state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
					pause(state);
					continue;
				}
				if (option.value() == 0) {
					running = false;
					continue;
				}
				auto path = read_text(state, string(strings::MSG_INPUT_PATH));
				if (!path) {
					continue;
				}
				switch (option.value()) {
				case 1:
					print_result(state, save_state_json(path.value(), *state.layout, state.robots, state.tasks));
					break;
				case 2:
					print_result(state, load_state_json(path.value(), *state.layout, state.robots, state.tasks));
					refresh_next_ids(state);
					break;
				case 3:
					print_result(state, save_layout_csv(path.value(), *state.layout));
					break;
				case 4:
					print_result(state, load_layout_csv(path.value(), *state.layout));
					refresh_next_ids(state);
					break;
				case 5:
					print_result(state, save_robots_csv(path.value(), state.robots));
					break;
				case 6:
					print_result(state, load_robots_csv(path.value(), state.robots));
					refresh_next_ids(state);
					break;
				case 7:
					print_result(state, save_tasks_csv(path.value(), state.tasks));
					break;
				case 8:
					print_result(state, load_tasks_csv(path.value(), state.tasks));
					refresh_next_ids(state);
					break;
				default:
					state.os << strings::MSG_INVALID_OPTION << strings::NL;
					pause(state);
					break;
				}
			}
			return Ok();
		}


		// =====Guide
		Result<void> show_guide(AppState& state) {
			print_menu_header(state, string(strings::MSG_GUIDE_INTRO));
			state.os
				<< strings::MSG_GUIDE_1 << strings::NL
				<< strings::MSG_GUIDE_1A << strings::NL
				<< strings::MSG_GUIDE_1B << strings::NL
				<< strings::MSG_GUIDE_1C << strings::NL
				<< strings::MSG_GUIDE_1D << strings::NL
				<< strings::MSG_GUIDE_2 << strings::NL
				<< strings::MSG_GUIDE_3 << strings::NL
				<< strings::MSG_GUIDE_3A << strings::NL
				<< strings::MSG_GUIDE_3B << strings::NL
				<< strings::MSG_GUIDE_3C << strings::NL;
			pause(state);
			return Ok();
		}


		// =====Credits
		Result<void> show_credits(AppState& state) {
			print_menu_header(state, string(strings::MSG_DESC_INTRO));
			state.os
				<< strings::MSG_DESC << strings::NL
				<< strings::MSG_DESC_MEMBERS << strings::NL
				<< strings::MSG_DESC_DOCS << strings::NL
				<< strings::MSG_DESC_DOCS_FILES << strings::NL
				<< strings::MSG_DESC_ROLES_1 << strings::NL
				<< strings::MSG_DESC_ROLES_2 << strings::NL
				<< strings::MSG_DESC_ROLES_3 << strings::NL
				<< strings::MSG_DESC_ROLES_4 << strings::NL
				<< strings::MSG_DESC_ROLES_5 << strings::NL;
			pause(state);
			return Ok();
		}

		// =====Main menu
		void print_main_menu(AppState& state) {
			print_menu_header(state, state.first_run
				? string(strings::MSG_WELCOME) + string(strings::MSG_MAIN_MENU_FIRST_RUN_INTRO)
				: string(strings::MSG_MAIN_MENU_INTRO));
			state.os
				<< strings::MSG_MAIN_MENU_OPTION_1 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_2 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_3 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_4 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_5 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_6 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_7 << strings::NL
				<< strings::MSG_MAIN_MENU_OPTION_0 << strings::NL
				<< strings::MSG_OPTION;
		}


	} // namespace


	// =====Helpers

	Result<int> get_option(std::istream& is) {
		string soption;
		int option = -1;
		if (!std::getline(is, soption)) {
			return Ok(0);
		}
		try {
			option = std::stoi(trim(soption));
		}
		catch (const std::invalid_argument&) {
			return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_NOT_NUMBER));
		}
		if (option < 0) {
			return Err<int>(ErrorCode::INVALID_ARGUMENT, string(strings::ERR_MENU_OPT_BELOW_ZERO));
		}
		return Ok(option);
	}


	// =====Entry point

	Result<void> cli_start(
		[[maybe_unused]] char* argv[],
		[[maybe_unused]] int argc,
		AppState& state
	) {
		bool running = true;
		while (running) {
			print_main_menu(state);
			auto option = get_option(state.is);
			if (!option) {
				state.os << strings::MSG_ERROR_PREFIX << option.error().message() << strings::NL;
				pause(state);
				continue;
			}
			switch (option.value()) {
			case 0:
				running = false;
				break;
			case 1:
				layout_menu(state);
				break;
			case 2:
				robots_menu(state);
				break;
			case 3:
				inventory_menu(state);
				break;
			case 4:
				tasks_menu(state);
				break;
			case 5:
				show_guide(state);
				break;
			case 6:
				show_credits(state);
				break;
			case 7:
				files_menu(state);
				break;
			default:
				state.os << strings::MSG_INVALID_OPTION << strings::NL;
				pause(state);
				break;
			}
			state.first_run = false;
		}
		state.os << strings::MSG_BYE << strings::NL;
		return Ok();
	}

}
