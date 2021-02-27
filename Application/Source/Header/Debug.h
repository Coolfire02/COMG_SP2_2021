//Debug "Cout" -- Only couts whenever in debug mode
//Regular Cout is now deprecated.

#ifdef _DEBUG
#define DEBUG_MSG(str) do { std::cout << "LOG: " << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false ) //Forces a ';' at the end of the macro call.
#endif