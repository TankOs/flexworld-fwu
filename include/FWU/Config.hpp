#pragma once

#if defined( _WIN32 ) || defined( __WIN32__ )
	#define WIN32_LEAN_AND_MEAN
	#define FWU_SYSTEM_WINDOWS

	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#endif

#if defined( FWU_SYSTEM_WINDOWS ) && !defined( FWU_STATIC )
	#ifdef FWU_EXPORTS
		#define FWU_API __declspec( dllexport )
	#else
		#define FWU_API __declspec( dllimport )
	#endif
#else
	#define FWU_API
#endif

#if !defined( NDEBUG )
	#define FWU_DEBUG
	#include <iostream>
#endif

/** FlexWorld utility.
 */
namespace util {
}
