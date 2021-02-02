#pragma once

enum key_flag_t : std::int32_t
{
	key_pressed = 0x7FFF
};

enum virtual_key_t : std::int32_t
{
	vk_lbutton = 0x01,
	vk_rbutton = 0x02,
	vk_end = 0x23,
	vk_home = 0x24,
	vk_numpad_0 = 0x60,
	vk_numpad_1 = 0x61,
	vk_numpad_2 = 0x62,
	vk_numpad_3 = 0x63,
	vk_numpad_4 = 0x64,
	vk_numpad_5 = 0x65,
	vk_numpad_6 = 0x66,
	vk_numpad_7 = 0x67,
	vk_numpad_8 = 0x68,
	vk_numpad_9 = 0x69,
	vk_function_1 = 0x70,
	vk_function_2 = 0x71,
	vk_function_3 = 0x72,
	vk_function_4 = 0x73,
	vk_function_5 = 0x74,
	vk_function_6 = 0x75,
	vk_function_7 = 0x76,
	vk_function_8 = 0x77,
	vk_function_9 = 0x78,
	vk_function_10 = 0x79
};

struct input_t
{
	auto mouse_handler( const virtual_key_t first, const virtual_key_t second, const std::float_t sensitivity, const std::float_t fov,
		const std::function <void( const std::float_t, const std::float_t )> &func ) -> void
	{
		if ( ::GetAsyncKeyState( first ) )
		{
			if ( ::GetAsyncKeyState( second ) )
			{
				func( sensitivity, fov );
			}
		}
	}
	
	auto key_handler( const virtual_key_t key, const key_flag_t flag ) -> bool
	{
		return ( ::GetAsyncKeyState( key ) == -flag );
	}
};

input_t* input;