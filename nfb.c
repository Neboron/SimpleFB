
//============================//
//          INCLUDES          //
//============================//
#include "nfb.h"



//============================//
//      STATIC VARIABLES      //
//============================//
typedef struct screen_obj_prop
{
    int x;
    int y;
    int width;
    int height;
} screen_obj_prop;



//============================//
//    FUNCTIONS PROTOTYPES    //
//============================//
void draw_rectangle(struct screen_obj* s_obj, int32_t x1, int32_t y1,
               int32_t x2, int32_t y2, PIXEL_DT color);
void swap_buffer(struct screen_obj* s_obj);



//============================//
//      GLOBAL FUNCTIONS      //
//============================//

int
create_screen_obj(struct screen_obj* s_obj, int32_t x, int32_t y,
                  int32_t width, int32_t height)
{
    ((struct screen_obj_prop*)(s_obj->properties))->x =
            x < 0 ? 0 : x;
    ((struct screen_obj_prop*)(s_obj->properties))->y =
            y < 0 ? 0 : y;
    ((struct screen_obj_prop*)(s_obj->properties))->width =
            width <= 0 ? 10 : width;
    ((struct screen_obj_prop*)(s_obj->properties))->height =
            height <= 0 ? 10 : height;

    uint32_t buffer_len =
            ((struct screen_obj_prop*)(s_obj->properties))->width *\
            ((struct screen_obj_prop*)(s_obj->properties))->height *\
            sizeof(PIXEL_DT);

    s_obj->buffer_ptr = malloc(buffer_len);
    if (!s_obj->buffer_ptr)
    {
        s_obj->obj_status = MEMORY_ALLOCATION_FAILURE;
        return -1;
    }
    s_obj->obj_status = READY;
    return 1;
}




screen_obj*
new_screen_obj()
{
    screen_obj* ptr;
    ptr = (screen_obj*) malloc(sizeof (screen_obj));
    ptr->properties = malloc(sizeof (screen_obj_prop));
    ptr->create = &create_screen_obj;
    ptr->draw_rectangle = &draw_rectangle;
    ptr->swap_buffer = &swap_buffer;

    return ptr;
}




void delete_screen_obj(screen_obj *s_obj)
{
    free(s_obj);
}




void
swap_buffer(struct screen_obj* s_obj)
{
    fb_flush(((struct screen_obj_prop*)(s_obj->properties))->x,
             ((struct screen_obj_prop*)(s_obj->properties))->y,
             ((struct screen_obj_prop*)(s_obj->properties))->x +\
             ((struct screen_obj_prop*)(s_obj->properties))->width-1,
             ((struct screen_obj_prop*)(s_obj->properties))->y +\
             ((struct screen_obj_prop*)(s_obj->properties))->height-1,
             s_obj->buffer_ptr);
}



void
draw_rectangle(struct screen_obj* s_obj, int32_t x1, int32_t y1,
               int32_t x2, int32_t y2, PIXEL_DT color)
{
    if (s_obj->obj_status != READY ||
        x1 >= ((struct screen_obj_prop*)(s_obj->properties))->width ||
        y1 >= ((struct screen_obj_prop*)(s_obj->properties))->height) return;

    x1 = x1 < 0 ? 0 : x1;
    y1 = y1 < 0 ? 0 : y1;
    x2 = x2 > ((struct screen_obj_prop*)(s_obj->properties))->width ?\
             ((struct screen_obj_prop*)(s_obj->properties))->width : x2;
    y2 = y2 > ((struct screen_obj_prop*)(s_obj->properties))->width ?\
             ((struct screen_obj_prop*)(s_obj->properties))->width : y2;


    int32_t  y;
    uint32_t location = y1*((struct screen_obj_prop*)(s_obj->properties))->width + x1;
    uint32_t line_length = x2 - x1;
    uint32_t line_end_location = location + line_length;
    uint32_t offset = ((struct screen_obj_prop*)(s_obj->properties))->width - (x2 - x1);

    printf("%d,%d,%d,%d\n", location, line_length, line_end_location, offset);

    for(y = y1; y < y2; y++)
    {
        while(location < line_end_location)
        {
            s_obj->buffer_ptr[location] = color;
            location++;
        }
        location += offset;
        line_end_location += (offset + line_length);
    }
}



