// errОrs.h
#pragma once


#include "./base.h"


namespace dstr::strings {


  SCSTR ERR_GENERAL = "Error occured: ";
  SCSTR ERR_TERMINATED = "Program was terminated by user.";
  SCSTR ERR_NOT_IMPLEMENTED = "This method or class is yet to be implemented.";
  SCSTR ERR_INVALID_ARGUMENT = "Invalid method/function argument.";
  SCSTR ERR_NOT_NUMBER = "Not a number.";

  SCSTR ERR_TRIM_ERROR = "trim() finished with an error.";
  SCSTR ERR_MENU_OPT_BELOW_ZERO = "Menu option number was less than zero.";

  SCSTR ERR_CANT_OPEN_FILE = "Cannot open file: ";
  SCSTR ERR_FILE_EMPTY = "File is empty: ";
  SCSTR ERR_FILE_NO_RECORDS = "No valid records found in file: ";

  SCSTR ERR_LINE = "Line ";


}
