/**
 * @file Rename.hpp
 * @brief Macros used for renaming nested standard library symbols
 *
 * This file contains all macros that are used to rename classes within
 * the standard library that are nested in other classes, thus being impossible
 * to rename without using preprocessor macros.
 */

#pragma once

#ifndef OPENJUICE_NO_STD_NESTED_CLASS_RENAMES
#define ValueType value_type
#define ConstPointer const_pointer
#define Reference reference
#define ConstReference const_reference
#define Iterator iterator
#define ConstIterator const_iterator
#define ConstReverseIterator const_reverse_iterator
#define ReverseIterator reverse_iterator
#define SizeType size_type
#define DifferenceType difference_type
#define AllocatorType allocator_type
#endif
