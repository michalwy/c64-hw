#ifndef HARPOON_COMPUTER_SYSTEM_HH
#define HARPOON_COMPUTER_SYSTEM_HH

#include "harpoon/harpoon.hh"
#include "harpoon/hardware_component.hh"
#include "harpoon/execution/execution_unit.hh"

namespace harpoon {

class computer_system : public hardware_component {
public:
	using hardware_component::hardware_component;

	virtual ~computer_system();

	void set_main_execution_unit(const execution::execution_unit_ptr& main_execution_unit);
	execution::execution_unit_ptr get_main_execution_unit() const {
		return _main_execution_unit.lock();
	}

	virtual void run();

private:
	execution::execution_unit_weak_ptr _main_execution_unit{};
};

using computer_system_ptr = std::shared_ptr<computer_system>;
using computer_system_weak_ptr = std::weak_ptr<computer_system>;
template<typename... Args>
computer_system_ptr make_computer_system(Args&&... args) {
	return std::make_shared<computer_system>(std::forward<Args>(args)...);
}

}

#endif