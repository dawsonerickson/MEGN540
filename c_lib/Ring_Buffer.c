#include "Ring_Buffer.h"

// define constant masks for use later based on length chosen
// these are global scope only to this c file
const uint8_t RB_MASK_F = RB_LENGTH_F-1;
const uint8_t RB_MASK_C = RB_LENGTH_C-1;


/* Initialization */
void rb_initialize_F( struct Ring_Buffer_F* p_buf )
{
    // set start and end indicies to 0
    // no point changing data
    p_buf->start_index = 0;
    p_buf->end_index = 0;
}

void rb_initialize_C( struct Ring_Buffer_C* p_buf )
{
    // set start and end indicies to 0
    // no point changing data

    // your code here!
    p_buf->start_index = 0;
    p_buf->end_index = 0;
}


/* Return active Length of Buffer */
uint8_t rb_length_F( const struct Ring_Buffer_F* p_buf)
{
    // calculate the active length using the mask and 2's complement to help
    // verify for your self why this works!
    uint8_t length = (p_buf->end_index - p_buf->start_index) & RB_MASK_F;
    return length;
}
uint8_t rb_length_C( const struct Ring_Buffer_C* p_buf)
{
    // your code here!
    // make sure to use the correct mask!
    uint8_t length = (p_buf->end_index - p_buf->start_index) & RB_MASK_C;
    return length;

}

/* Append element to end and lengthen */
void rb_push_back_F( struct Ring_Buffer_F* p_buf, float value)
{
// Put data at index end
    p_buf->buffer[p_buf->end_index]=value;
// Increment the end index and wrap using the mask.
   (p_buf->end_index++) ;
   p_buf->end_index&= RB_MASK_F;
// If the end equals the start increment the start index`
    if (p_buf->end_index==p_buf->start_index)
       {p_buf->start_index++;
       p_buf->start_index&= RB_MASK_F;
       }
}
void rb_push_back_C( struct Ring_Buffer_C* p_buf, char value)
{

// Put data at index end
    p_buf->buffer[p_buf->end_index]=value;
// Increment the end index and wrap using the mask.
   (p_buf->end_index++) ;
   p_buf->end_index&= RB_MASK_C;
// If the end equals the start increment the start index`
    if (p_buf->end_index==p_buf->start_index)
       {p_buf->start_index++;
       p_buf->start_index&= RB_MASK_C;
       }
}

/* Append element to front and lengthen */
void rb_push_front_F( struct Ring_Buffer_F* p_buf, float value)
{
// Decrement the start index and wrap using the mask.
    p_buf->start_index--;
    p_buf->start_index&= RB_MASK_F;
// Put data at index start
    p_buf->buffer[p_buf->start_index]=value;
// If the end equals the start decrement the end index`
// Set the value at the start index as desired.
    if (p_buf->end_index==p_buf->start_index)
// Increment the end index and wrap using the mask.
       {p_buf->end_index--;
       p_buf->end_index&= RB_MASK_F;
       }

}
void rb_push_front_C( struct Ring_Buffer_C* p_buf, char value)
{

// Decrement the start index and wrap using the mask.
    p_buf->start_index--;
    p_buf->start_index&= RB_MASK_C;
// Put data at index start
    p_buf->buffer[p_buf->start_index]=value;
// If the end equals the start decrement the end index`
// Set the value at the start index as desired.
    if (p_buf->end_index==p_buf->start_index)
        // Increment the end index and wrap using the mask.
       {p_buf->end_index--;
       p_buf->end_index&= RB_MASK_C;
       }
}

/* Remove element from end and shorten */
float rb_pop_back_F( struct Ring_Buffer_F* p_buf)
{

// if end does not equal start (length zero),
     if (p_buf->end_index==p_buf->start_index)
        return 0;
     else
//    reduce end index by 1 and mask
       {p_buf->end_index--;
       p_buf->end_index&= RB_MASK_F;
// 	  return value at at end
       return  p_buf->buffer[p_buf->end_index];
       }
}
char  rb_pop_back_C( struct Ring_Buffer_C* p_buf)
{
// if end does not equal start (length zero),
   if (p_buf->end_index==p_buf->start_index)
        return 0;
     else
//    reduce end index by 1 and mask
       {p_buf->end_index--;
       p_buf->end_index&= RB_MASK_C;
// 	  return value at at end
       return  p_buf->buffer[p_buf->end_index];
       }
}

/* Remove element from start and shorten */
float rb_pop_front_F( struct Ring_Buffer_F* p_buf)
{

    float returnvalue=0;
    if (p_buf->end_index==p_buf->start_index)// if end equals start (length zero),return 0
        return 0;
     else
       {returnvalue=p_buf->buffer[p_buf->start_index];// get value to return at front
           p_buf->start_index++;//    increase start index by 1 and mask
       p_buf->start_index&= RB_MASK_F;
       return  returnvalue;
       }
}
char  rb_pop_front_C( struct Ring_Buffer_C* p_buf)
{

    float returnvalue=0;
    if (p_buf->end_index==p_buf->start_index) // if end equals start (length zero),return 0
        return 0;
     else
       {returnvalue=p_buf->buffer[p_buf->start_index];// get value to return at front
           p_buf->start_index++;//    increase start index by 1 and mask
       p_buf->start_index&= RB_MASK_C;
       return  returnvalue;
       }
}

/* access element */
float rb_get_F( const struct Ring_Buffer_F* p_buf, uint8_t index)
{
    // return value at start + index wrapped properly
   uint8_t rb_index=p_buf->start_index+index;
   rb_index&=RB_MASK_F;
    return p_buf->buffer[rb_index]; // update
}
char  rb_get_C( const struct Ring_Buffer_C* p_buf, uint8_t index)
{
    // return value at start + index wrapped properly
   uint8_t rb_index=p_buf->start_index+index;
   rb_index&=RB_MASK_C;
    return p_buf->buffer[rb_index]; // update
}

/* set element - This behavior is
   poorly defined if inedex is outside of active length.
   Use of the push_back or push_front methods are prefered.
*/
void  rb_set_F( struct Ring_Buffer_F* p_buf, uint8_t index, float value)
{
    // set value at start + index wrapped properly
    uint8_t rb_index=p_buf->start_index+index;
   rb_index&=RB_MASK_F;
    p_buf->buffer[rb_index]=value; // update
}
void  rb_set_C( struct Ring_Buffer_C* p_buf, uint8_t index, char value)
{
    // set value at start + index wrapped properly
    uint8_t rb_index=p_buf->start_index+index;
   rb_index&=RB_MASK_C;
    p_buf->buffer[rb_index]=value; // update
}

