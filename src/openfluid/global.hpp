/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
  
*/

/**
  @file global.hpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@supagro.inra.fr>
*/



#ifndef __OPENFLUID_GLOBAL_HPP__
#define __OPENFLUID_GLOBAL_HPP__



// Processor

#if defined(__i386) || defined(__i386__) || defined(_M_IX86)
  #define OPENFLUID_PROCESSOR_X86
  #define OPENFLUID_PROCESSOR_X86_32
  #define OPENFLUID_PROCESSOR_IS_SUPPORTED
#elif defined(__x86_64) || defined(__x86_64__) || defined(__amd64) || defined(_M_X64)
  #define OPENFLUID_PROCESSOR_X86
  #define OPENFLUID_PROCESSOR_X86_64
  #define OPENFLUID_PROCESSOR_IS_SUPPORTED
#endif


#if !defined(OPENFLUID_PROCESSOR_IS_SUPPORTED)
  #error "OpenFLUID requires a supported processor (X86 family)"
#endif


// =====================================================================
// =====================================================================


// Operating system


#define OPENFLUID_OS_IS_SUPPORTED

#if defined(__linux__) || defined(__linux)
  #define OPENFLUID_OS_LINUX
  #if defined(__LP64__)
    #define OPENFLUID_OS_LINUX64
  #else
    #define OPENFLUID_OS_LINUX32
  #endif
#elif (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
  #define OPENFLUID_OS_WIN64
  #define OPENFLUID_OS_WIN32
  #define OPENFLUID_OS_WINDOWS
#elif (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
  #define OPENFLUID_OS_WIN32
  #define OPENFLUID_OS_WINDOWS
#elif defined(__APPLE__)
  #define OPENFLUID_OS_MAC
  #if defined(__LP64__)
    #define OPENFLUID_OS_MAC64
  #else
    #define OPENFLUID_OS_MAC32
  #endif
#else
  #undef OPENFLUID_OS_IS_SUPPORTED
#endif

#if defined(OPENFLUID_OS_WINDOWS)
  #undef OPENFLUID_OS_UNIX
#elif !defined(OPENFLUID_OS_UNIX)
  #define OPENFLUID_OS_UNIX
#endif


#if defined(OPENFLUID_OS_LINUX64)
  #define OPENFLUID_OS_STRLABEL "linux-x86-64";
#elif defined(OPENFLUID_OS_LINUX32)
  #define OPENFLUID_OS_STRLABEL "linux-i386";
#elif defined(OPENFLUID_OS_WIN32) && !defined(OPENFLUID_OS_WIN64)
  #define OPENFLUID_OS_STRLABEL "win32";
#elif defined(OPENFLUID_OS_WIN64)
  #define OPENFLUID_OS_STRLABEL "win64";
#elif defined(OPENFLUID_OS_MAC64)
  #define OPENFLUID_OS_STRLABEL "osx64";
#elif defined(OPENFLUID_OS_MAC32)
  #define OPENFLUID_OS_STRLABEL "osx32";
#else
  #define OPENFLUID_OS_STRLABEL "";
#endif


// =====================================================================
// =====================================================================


// Compiler

#if defined(__GNUC__)
  #if defined(__clang__)
    #define OPENFLUID_CC_IS_SUPPORTED
  #elif __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 8 || (__GNUC_MINOR__ == 8 )))
    #define OPENFLUID_CC_IS_SUPPORTED
  #endif
#endif


#if !defined(OPENFLUID_CC_IS_SUPPORTED)
  #error "OpenFLUID requires a supported C++ compiler (GNU C++ 4.8 or greater)"
#endif


// =====================================================================
// =====================================================================


// Code location

#if defined(__GNUC__)
  #define OPENFLUID_CODE_LOCATION __PRETTY_FUNCTION__
#else
  #define OPENFLUID_CODE_LOCATION __func__
#endif



#endif /* __OPENFLUID_GLOBAL_HPP__ */
