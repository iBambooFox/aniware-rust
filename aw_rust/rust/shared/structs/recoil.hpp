#pragma once

enum table_translation_t : std::uint32_t
{
	weapon_ak = 0,
	weapon_lr,
};

const std::vector <vec2_t> recoil_t[ ] = {
	{ { -35, 50, 121.96149709966872f }, { 5, 46, 92.6333814724611f }, { -55, 42, 138.60598637206294f }, {-42, 37, 113.37874368443146f }, { 0, 33, 66.25151186427745f },
	{ 16, 28, 66.29530438019354f }, { 29, 24, 75.9327831420658f }, { 38, 19, 85.05526144256157f }, { 42, 14, 89.20256669256554f }, { 42, 9, 86.68010184667988f },
	{ 38, 9, 78.82145888317788f }, { 30, 18, 70.0451048111144f }, { 17, 25, 60.85979604582978f }, { 0, 29, 59.51642457624619f }, { -15, 32, 71.66762996283607f },
	{ -27, 33, 86.74060009403034f }, { -37, 32, 98.3363599080854f }, { -43, 29, 104.34161954944257f }, { -46, 24, 104.09299204005345f }, { -45, 17, 97.58780746901739f },
	{ -42, 8, 85.48062700875559f }, { -35, 5, 70.4889202349561f }, { -24, 14, 56.56417811530545f }, { -11, 21, 47.386907899993936f }, { 12, 25, 56.63787408680247f },
	{ 36, 28, 91.5937793023631f }, { 49, 28, 112.38667610336424f }, { 49, 26, 111.39338971888095f }, { 38, 21, 87.5067801164596f } },
};

const std::double_t delay_t[ ] = { 133.3333333f };

struct recoil_control_t
{
	auto accurate_move( std::double_t delay, std::double_t reset, vec2_t delta ) -> void
	{
		const auto move = [ ]( const vec2_t move ) -> void
		{
			::mouse_event( 1, static_cast <uint32_t> ( move.m_x ), static_cast <std::uint32_t> ( move.m_y ), 0, 0 );
		};

		vec2_t context{ }, loop{ };

		for ( std::double_t i = 1.f; i <= reset; i++ )
		{
			loop = vec2_t( i * delta.m_x / reset, i * delta.m_y / reset, i * reset / reset );
			move( vec2_t( loop.m_x - context.m_x, loop.m_x - context.m_x ) );

			high_resolution_time->accurate_sleep( static_cast <std::uint32_t> ( loop.m_time - context.m_time ) );
			context = vec2_t( loop.m_x, loop.m_y, loop.m_time );
		}

		if ( delay - reset >= 0.f )
		{	
			high_resolution_time->accurate_sleep( static_cast <std::uint32_t> ( delay - reset ) );
		}
	}

	auto correct_recoil( const std::float_t sensitivity, const std::float_t fov ) -> void
	{
		const auto calculate_angle = [ ]( std::float_t sensitivity, std::float_t fov, std::double_t delta ) -> std::double_t
		{
			return static_cast <std::double_t> ( ( ( fov / 2.f ) * delta ) / ( static_cast <std::double_t> ( sensitivity ) * static_cast <std::double_t> ( fov ) ) );
		};

		std::uint32_t bullets_fired{ };

		for ( ;; )
		{
			if ( input->mouse_handler( virtual_key_t::vk_rbutton, virtual_key_t::vk_lbutton, sensitivity, fov,
				[ & ]( const std::float_t sensitivity, const std::float_t fov ) -> void 
				{
					if ( auto &context = recoil_t[ table_translation_t::weapon_ak ]; bullets_fired < context.size( ) )
					{
						accurate_move( delay_t[ table_translation_t::weapon_ak ], context[ bullets_fired ].m_time, vec2_t( calculate_angle( sensitivity, fov, context[ bullets_fired ].m_x ),
							calculate_angle( sensitivity, fov, context[ bullets_fired ].m_y ) ) );

						std::cout << bullets_fired << std::endl;
					}
				}
			) )
			{
				bullets_fired++;
			}
			else
			{
				bullets_fired = 0;
			}
		}
	}
};

recoil_control_t* recoil_control;