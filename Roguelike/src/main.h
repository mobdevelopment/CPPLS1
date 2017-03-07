#ifndef MAIN_HEADER_INCLUDED
#define MAIN_HEADER_INCLUDED

#ifdef _WIN32
 #include <Windows.h>
 #ifdef _DEBUG
  #define _CRTDBG_MAP_ALLOC
  #define _CRTDBG_MAP_ALLOC_NEW
  #include <stdlib.h>
  #include <crtdbg.h>
 #endif // _DEBUG 
#endif // _WIN32

#include <iostream>
#include <stdexcept>
#include <system_error>

#include "game/game.h"
#include "ui/userinterfacebase.h"
#include "ui/cnsl/userinterface.h"

#endif // #ifndef MAIN_HEADER_INCLUDED