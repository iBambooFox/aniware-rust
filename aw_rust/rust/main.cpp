#include "shared/shared.hpp"

auto main() -> std::int32_t
{
	while ( true )
	{
		if ( input->key_handler( virtual_key_t::vk_function_1, key_flag_t::key_pressed ) )
			std::cout << "Pressed f1";
	}
}