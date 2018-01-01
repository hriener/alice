/* alice: C++ command shell library
 * Copyright (C) 2017-2018  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
  \file store_api.hpp
  \brief API to customize behavior of store elements

  \author Mathias Soeken
*/

#pragma once

#include <exception>
#include <iostream>
#include <string>

#include <json.hpp>

#include "command.hpp"

namespace alice
{

class command;

/*! \brief Empty prototype class for store information

  You need to specialize this struct in order declare a new store type for the
  CLI.  In this specialization five ``static constexpr const char*`` variables
  must be defined:

  - ``key``: A unique key for internal storing in the ``environment``
  - ``option``: A long option name for commands (without dashes)
  - ``mnemonic``: A single character for short option (without dash, cannot be ``n`` or ``v``)
  - ``name``: A singular name that is used in help texts
  - ``name_plural``: A plural name that is used in help texts

  \verbatim embed:rst
      
      .. note::
      
        Make sure to specialize ``store_info`` inside the ``alice`` namespace.  You
        can use the :c:macro:`ALICE_ADD_STORE` macro instead of the partial
        specialization.  Also :c:macro:`ALICE_MAIN` will automatically pick up all
        stores that were defined using :c:macro:`ALICE_ADD_STORE`.

      Here is an example code to define a store type for a fictional type ``graph``:

      .. code-block:: c++
      
         namespace alice {
        
         template<>
         struct store_info<graph>
         {
           static constexpr const char* key = "graph";
           static constexpr const char* option = "graph";
           static constexpr const char* mnemonic = "g";
           static constexpr const char* name = "graph";
           static constexpr const char* name = "graphs";
         };

         }

      You can then use this data structure as part of the CLI when listing its type in the
      declaration of ``cli``:

      .. code-block:: c++

         alice::cli<..., graph, ...> cli( "prefix" );

  \endverbatim
 */
template<typename StoreType>
struct store_info
{
};

/*! \brief Produce short one-line description of store element */
template<typename StoreType>
std::string to_string( const StoreType& element )
{
  (void)element;
  return "";
}

/*! \brief Routine to print a store element to an output stream

  This routine is called by the `print` command.

  \param out Output stream
  \param element Store element
 */
template<typename StoreType>
void print( std::ostream& out, const StoreType& element )
{
  (void)element;
  out << std::endl;
}

/*! \brief Routine to print statistics of a store element to an output stream

  This routine is called by the `ps` command.

  \param out Output stream
  \param element Store element
*/
template<typename StoreType>
void print_statistics( std::ostream& out, const StoreType& element )
{
  (void)element;
  out << std::endl;
}

/*! \brief Statistics to log when calling `ps`

  This routine is called by the `ps` command, if logging is enabled.

  \param element Store element
*/
template<typename StoreType>
nlohmann::json log_statistics( const StoreType& element )
{
  (void)element;
  return nlohmann::json({});
}

/*! \brief Controls whether a store entry can read from a specific format

  If this function is overriden to return true, then also the function
  `read` must be impemented for the same store element type and format
  tag.

  \param cmd Mutable reference to command, e.g., to add custom options
*/
template<typename StoreType, typename Tag>
bool can_read( command& cmd )
{
  (void)cmd;
  return false;
}

/*! \brief Reads from a format and returns store element

  This function must be enabled by overriding the `can_read` function
  for the same store element type and format tag.

  \param filename Filename to read from
  \param cmd Reference to command, e.g., to check whether custom options are set
*/
template<typename StoreType, typename Tag>
StoreType read( const std::string& filename, const command& cmd )
{
  (void)filename;
  (void)cmd;
  throw std::runtime_error( "[e] unimplemented function" );
}

/*! \brief Controls whether a store entry can write to a specific format

  If this function is overriden to return true, then also the function
  `write` must be impemented for the same store element type and
  format tag.

  \param cmd Mutable reference to command, e.g., to add custom options
*/
template<typename StoreType, typename Tag>
bool can_write( command& cmd )
{
  (void)cmd;
  return false;
}

/*! \brief Writes to a format and returns store element

  This function must be enabled by overriding the `can_write` function
  for the same store element type and format tag.

  \param element Store element to write
  \param filename Filename to write to
  \param cmd Reference to command, e.g., to check whether custom options are set
*/
template<typename StoreType, typename Tag>
void write( const StoreType& element, const std::string& filename, const command& cmd )
{
  (void)element;
  (void)filename;
  (void)cmd;
  throw std::runtime_error( "[e] unimplemented function" );
}

/*! \brief Controls whether a store entry can be converted to an entry of a different store type

  If this function is overriden to return true, then also the function
  `convert` must be implemented for the same store types.
 */
template<typename SourceStoreType, typename DestStoreType>
bool can_convert()
{
  return false;
}

/*! \brief Converts a store entry into an entry of a different store type

  This function must be enabled by overriding the `can_convert`
  function for the same store element types.

  \param element Store element to convert
  \return Converted store element
*/
template<typename SourceStoreType, typename DestStoreType>
DestStoreType convert( const SourceStoreType& element )
{
  (void)element;
  throw std::runtime_error( "[e] unimplemented function" );
}
}
