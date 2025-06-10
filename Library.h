#pragma once

/* The __stdcall calling convention is used to call Win32 API functions. The callee cleans the stack, 
 * so the compiler makes vararg functions __cdecl. Functions that use this calling convention require 
 * a function prototype.
 *
 * __stdcall is the standard and produces smaller code. */
void __stdcall HenCluck();
