#pragma once

struct vec2_t
{
	vec2_t( ) = default;
	vec2_t( const std::double_t x, const std::double_t y, const std::double_t t = 0.f )
		: m_x( x ), m_y( y ), m_time( t ) { };

	std::double_t m_x, m_y, m_time;
};