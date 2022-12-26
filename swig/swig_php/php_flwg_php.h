/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef PHP_FLWG_PHP_H
#define PHP_FLWG_PHP_H

extern zend_module_entry flwg_php_module_entry;
#define phpext_flwg_php_ptr &flwg_php_module_entry

#ifdef PHP_WIN32
# define PHP_FLWG_PHP_API __declspec(dllexport)
#else
# define PHP_FLWG_PHP_API
#endif

ZEND_NAMED_FUNCTION(_wrap_ChooseFirstWord);
ZEND_NAMED_FUNCTION(_wrap_Allocate_IntToWordStruct);
ZEND_NAMED_FUNCTION(_wrap_Allocate_WordToInt);
ZEND_NAMED_FUNCTION(_wrap_Initialize_HashMaps);
ZEND_NAMED_FUNCTION(_wrap_Free_HashMaps);
ZEND_NAMED_FUNCTION(_wrap_Convert_WordToInt);
ZEND_NAMED_FUNCTION(_wrap_Convert_IntToWord);
ZEND_NAMED_FUNCTION(_wrap_init_WordSet);
ZEND_NAMED_FUNCTION(_wrap_reset_WordSet);
ZEND_NAMED_FUNCTION(_wrap_checkIfUsed_WordSet);
ZEND_NAMED_FUNCTION(_wrap_markUsed_WordSet);
ZEND_NAMED_FUNCTION(_wrap_free_WordSet);
ZEND_NAMED_FUNCTION(_wrap_botPly);
PHP_MINIT_FUNCTION(flwg_php);

#endif /* PHP_FLWG_PHP_H */