#include "harpoon/memory/serializer/binary_file.hh"
#include "harpoon/memory/memory.hh"

using namespace harpoon::memory::serializer;

void binary_file::start_memory_block(const memory * memory, const address_range& address_range) {
	_address_range = address_range;
	_memory = memory;
	_output.exceptions(std::ofstream::badbit);
	_output.open(_file_name, std::ios::binary);
}

std::size_t binary_file::write(const uint8_t * data, std::size_t length, bool sparse) {
	if (sparse) {
		_memory->log(log_debug_c(_memory->get_name() + " => binary_file")
					 << "Writing " << length << " bytes of sparse buffer to " << _file_name);
		_output.seekp(length, std::ios_base::cur);
	} else {
		_memory->log(log_debug_c(_memory->get_name() + " => binary_file")
					 << "Writing " << length << " bytes to " << _file_name);
		_output.write(reinterpret_cast<const char *>(data), length);
	}
	return length;
}

void binary_file::end_memory_block() {}

void binary_file::seek_memory_block(const memory * memory, const address_range& address_range) {
	_address_range = address_range;
	_memory = memory;
	_input.exceptions(std::ifstream::badbit);
	_input.open(_file_name, std::ios::binary);
}

std::size_t binary_file::read(uint8_t * data, std::size_t length) {
	_memory->log(log_debug_c("binary_file => " + _memory->get_name())
				<< "Reading " << length << " bytes from " << _file_name);
	_input.read(reinterpret_cast<char *>(data), length);
	return _input.gcount();
}