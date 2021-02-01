#pragma once

struct recoil_control_t
{
	auto correct_recoil(  ) -> void
	{
		const auto calculate_angle = [ ]( std::float_t sensitivity, std::float_t fov, std::double_t delta ) -> std::double_t
		{
			return static_cast <std::double_t> ( ( ( fov / 2 ) * delta ) / ( sensitivity * fov ) );
		};
	}

	auto accurate_move( std::double_t delay, std::double_t reset, vec2_t delta ) -> void
	{
		const auto move = [ ]( const vec2_t move ) -> void
		{
			::mouse_event( 1, static_cast <uint32_t> ( move.m_x ), static_cast <std::uint32_t> ( move.m_y ), 0, 0 );
		};

		vec2_t context{ }, loop{ };

		for ( std::double_t i = 1.f; i <= reset; i++ )
		{
			loop = vec2_t( ( i * delta.m_x ) / reset, ( i * delta.m_y ) / reset, ( i * reset ) / reset );
			move( vec2_t( loop.m_x - context.m_x, loop.m_x - context.m_x ) );

			high_resolution_time->experimental_sleep( static_cast <std::uint32_t> ( loop.m_time - context.m_time ) );
			context = vec2_t( loop.m_x, loop.m_y, loop.m_time );
		}

		high_resolution_time->experimental_sleep( static_cast <std::uint32_t> ( delay - reset ) );
	}
};

recoil_control_t* recoil_control;