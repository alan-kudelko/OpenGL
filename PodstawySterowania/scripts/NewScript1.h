#pragma once

#ifdef HELLOWORLD_EXPORTS  // Ustawiane tylko przy kompilowaniu DLL
#define HELLOWORLD_API __declspec(dllexport)
#else
#define HELLOWORLD_API __declspec(dllimport)
#endif

// Deklaracja funkcji, która będzie eksportowana z DLL
HELLOWORLD_API void HelloWorld();