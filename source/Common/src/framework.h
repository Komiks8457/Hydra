#pragma once

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

// 1. System/Build configurations first
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

// 2. Windows Basics
#include <Windows.h>
#include <tchar.h>
#include <intrin.h>

// 3. C Standard Library (Faster to parse)
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cwchar>
#include <cctype>
#include <cwctype>
#include <ctime>
#include <cassert>

// 4. C++ Standard Library
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <hash_map>
#include <algorithm>
#include <functional>
#include <utility>
#include <iterator>
#include <memory>
#include <limits>
#include <valarray>

#endif