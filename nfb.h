#ifndef NFB_H
#define NFB_H

#ifdef __cplusplus
extern "C" {
#endif

//============================//
//          INCLUDES          //
//============================//
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "linux_fb.h"
#include <unistd.h>



//============================//
//           DEFINES          //
//============================//

#define BITS_PER_PIXEL_32
#ifdef BITS_PER_PIXEL_32
    // data type to store pixel value
    #define PIXEL_DT uint32_t
#elif
    // data type to store pixel value
    #define PIXEL_DT uint32_t
#endif

enum
{
    FAILURE,
    MEMORY_ALLOCATION_FAILURE,
    READY
};




//============================//
//         PROTOTYPES         //
//============================//




//============================//
//          TYPEDEFS          //
//============================//
typedef struct screen_obj
{
    void *properties;
    PIXEL_DT *buffer_ptr;
    uint8_t obj_status;
    int (*create)(struct screen_obj*, int32_t x, int32_t y,
                  int32_t width, int32_t height);
    void (*swap_buffer)(struct screen_obj* s_obj);
    void (*draw_rectangle)(struct screen_obj* s_obj, int32_t x1, int32_t y1,
                   int32_t x2, int32_t y2, PIXEL_DT color);
}screen_obj;



screen_obj* new_screen_obj();
void delete_screen_obj(screen_obj*);





#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* NFB */
