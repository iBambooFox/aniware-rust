#pragma once

enum time_flag_t : std::uint32_t
{
	performance_counter = 0,
	performance_frequency
};

struct high_resolution_time_t
{
	auto experimental_sleep( std::uint32_t time ) -> void
	{
		auto m_start = std::chrono::steady_clock::now( );

		while ( std::chrono::duration_cast <std::chrono::milliseconds> ( std::chrono::steady_clock::now( ) - m_start ).count( ) < time )
		{
			std::this_thread::sleep_for( std::chrono::nanoseconds( 1 ) );
		}
	}

	auto accurate_sleep( std::uint32_t time ) -> void
	{
		std::uint64_t m_resolution{ }, m_desired{ }, m_current{ };

		const auto query_performance = [ ]( std::uint64_t& time, time_flag_t flag ) -> bool
		{
			return ( flag ? ::QueryPerformanceFrequency( reinterpret_cast <LARGE_INTEGER*> ( &time ) ) :
				::QueryPerformanceCounter( reinterpret_cast <LARGE_INTEGER*> ( &time ) ) );
		};

		if ( query_performance( m_resolution, time_flag_t::performance_frequency ) )
		{
			m_resolution /= 1000;
		}

		if ( query_performance( m_current, time_flag_t::performance_counter ) )
		{
			m_desired = (m_current / m_resolution) + time, m_current = 0;
		}

		while ( m_current < m_desired )
		{
			if ( query_performance( m_current, time_flag_t::performance_counter ) )
			{
				m_current /= m_resolution;
			}
		}
	}
};

high_resolution_time_t* high_resolution_time;