#include "bcd.h"

#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

/** Return BCD encoding of binary (which has normal binary representation).
 *
 *  Examples: binary_to_bcd(0xc) => 0x12;
 *            binary_to_bcd(0xff) => 0x255
 *
 *  If error is not NULL, sets *error to OVERFLOW_ERR if binary is too
 *  big for the Bcd type, otherwise *error is unchanged.
 */
Bcd
powers(int x, int y){
  Bcd value = 1;
  for(int i = 0; i < y; i++)
    value *= x;
  
  return value;
}

Bcd
binary_to_bcd(Binary value, BcdError *error)
{
  int move = 0;
  Bcd bcd = 0;
  Binary temp = value;
  int counter = 0;
  while(temp > 0){
    counter++;
    temp /= 10;
  }
  if(*error == NULL){
    if(counter > MAX_BCD_DIGITS)
      *error = OVERFLOW_ERR;
  }
  while(value > 0) {
    bcd |= (value % 10) << (move++ << 2);
    value /= 10;
  }
  return bcd;
}

/** Return binary encoding of BCD value bcd.
 *
 *  Examples: bcd_to_binary(0x12) => 0xc;
 *            bcd_to_binary(0x255) => 0xff
 *
 *  If error is not NULL, sets *error to BAD_VALUE_ERR if bcd contains
 *  a bad BCD digit.
 *  Cannot overflow since Binary can represent larger values than Bcd
 */
Binary
bcd_to_binary(Bcd bcd, BcdError *error)
{
  Bcd temp = bcd;
  int counter = 0;
  Bcd sum = 0;
  while (temp > 0){
    if((temp & 0xf) > 9){
      *error = BAD_VALUE_ERR;
    }    
    sum += (temp & 0xf)*powers(10,counter);
    counter++;
    temp = temp >> 4;
  }
  
  return sum;
}

/** Return BCD encoding of decimal number corresponding to string s.
 *  Behavior undefined on overflow or if s contains a non-digit
 *  character.  Sets *p to point to first non-digit char in s.
 *  Rougly equivalent to strtol().
 *
 *  If error is not NULL, sets *error to OVERFLOW_ERR if binary is too
 *  big for the Bcd type, otherwise *error is unchanged.
 */
Bcd
str_to_bcd(const char *s, const char **p, BcdError *error)
{
  int length = strlen(s);
  if(*error != NULL && length > MAX_BCD_DIGITS)
    *error = OVERFLOW_ERR;

  int value = s[0] - '0';
  int i = 0;
  Bcd sum = 0;
  int found = 0;
  while(value != -48){
    if(value > -1 && value < 10){
      sum *= 10;
      sum += value;
    }else{
      if(!found){
        *p = &s[i];
        found = 1;
      }
    }
    i++;
    value = s[i] - '0';
  }
  if(!found)
    *p = &s[i];
  
  return binary_to_bcd(sum, error);
}

/** Convert bcd to a NUL-terminated string in buf[] without any
 *  non-significant leading zeros.  Never write more than bufSize
 *  characters into buf.  The return value is the number of characters
 *  written (excluding the NUL character used to terminate strings).
 *
 *  If error is not NULL, sets *error to BAD_VALUE_ERR is bcd contains
 *  a BCD digit which is greater than 9, OVERFLOW_ERR if bufSize bytes
 *  is less than BCD_BUF_SIZE, otherwise *error is unchanged.
 */
int
bcd_to_str(Bcd bcd, char buf[], size_t bufSize, BcdError *error)
{
  if(*error == NULL){
    if(bufSize < BCD_BUF_SIZE){
      *error = OVERFLOW_ERR;
    }
    Bcd temp = bcd;
    while(temp > 0){
      if((temp & 0xf) > 9){
	*error = BAD_VALUE_ERR;
      }
      temp = temp >> 4;
    }
  }

  Bcd binary = bcd_to_binary(bcd, error);
  return sprintf(buf, "%d", binary);
}

/** Return the BCD representation of the sum of BCD int's x and y.
 *
 *  If error is not NULL, sets *error to to BAD_VALUE_ERR is x or y
 *  contains a BCD digit which is greater than 9, OVERFLOW_ERR on
 *  overflow, otherwise *error is unchanged.
 */
Bcd
bcd_add(Bcd x, Bcd y, BcdError *error)
{
  //@TODO
  return 0;
}

/** Return the BCD representation of the product of BCD int's x and y.
 *
 * If error is not NULL, sets *error to to BAD_VALUE_ERR is x or y
 * contains a BCD digit which is greater than 9, OVERFLOW_ERR on
 * overflow, otherwise *error is unchanged.
 */
Bcd
bcd_multiply(Bcd x, Bcd y, BcdError *error)
{
  //@TODO
  return 0;
}
