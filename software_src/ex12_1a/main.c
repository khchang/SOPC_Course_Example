#include	"system.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>
#include	<io.h>
#include	<sys/alt_alarm.h>
#include	<unistd.h>
#include	<altera_avalon_sgdma.h>
#include	<altera_avalon_sgdma_descriptor.h>
#include	<altera_avalon_sgdma_regs.h>
#include	<alt_types.h>
#include	"video_sync_generator/alt_video_display.h"
#include	"video_sync_generator/fonts.h"
#include	"video_sync_generator/simple_graphics.h"


#define WIDTH  640
#define HEIGHT 480
#define NUM_FRAME 1
#define COLOR_R 0xFF0000
#define COLOR_G 0x00FF00
#define COLOR_B 0x0000FF
#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLACK 0x000000
#define COLOR_GRAY  0x7F7F7F


int main()
{
    alt_video_display* display_global;
    char text[100];
  
    printf("Initializing LCD display controller\n  ");
    display_global = alt_video_display_init( "/dev/sgdma_video",					// Name of video controller
                                            WIDTH,									// Width of display
                                            HEIGHT,									// Height of display
                                            32,										// Color depth (32 or 16)
                                            SDRAM_BASE+SDRAM_SPAN/2,				// Where we want our frame buffers
                                            ONCHIP_MEM_BASE,						// Where we want our descriptors
                                            NUM_FRAME );  
    if( display_global )
        printf(" - LCD Initialization OK\n");
    else
        printf(" - LCD FAILED\n"); 
    alt_video_display_clear_screen(display_global,0x0);

    
    sprintf(text,"1. Hello World!\n");
    vid_print_string_alpha(5, 10, COLOR_B+COLOR_G, COLOR_BLACK, tahomabold_20, display_global,text);
        
    sprintf(text,"2. National Formosa University!\n");
    vid_print_string_alpha(5, 40, COLOR_R+COLOR_G, COLOR_BLACK, tahomabold_20, display_global,text);
    
    sprintf(text,"3. Hello World!\n");
    //vid_print_string_alpha(5, 70, COLOR_BLACK, COLOR_B+COLOR_G, tahomabold_20, display_global,text);
    vid_print_string_alpha(5, 70, 0xffffff, 0xff66cc, tahomabold_20, display_global,text);
        
    sprintf(text,"4. National Formosa University!\n");
    vid_print_string_alpha(5, 100, COLOR_BLACK, COLOR_R+COLOR_G, tahomabold_20, display_global,text);

    sprintf(text,"5. Hello World!\n");            
    vid_print_string_alpha(5, (HEIGHT/2)+10, COLOR_B+COLOR_R, COLOR_BLACK, tahomabold_32, display_global,text);
        
    sprintf(text,"6. National Formosa University!\n");
    vid_print_string_alpha(5, (HEIGHT/2)+60, COLOR_G, COLOR_BLACK, tahomabold_32, display_global,text);
    
    sprintf(text,"7. Hello World!\n");
    //vid_print_string_alpha(5, (HEIGHT/2)+110, COLOR_BLACK, COLOR_B+COLOR_R, tahomabold_32, display_global,text);
    vid_print_string_alpha(5, (HEIGHT/2)+110, 0x0, 0xccccff, tahomabold_32, display_global,text);
        
    sprintf(text,"8. National Formosa University!\n");
    //vid_print_string_alpha(5, (HEIGHT/2)+160, COLOR_BLACK, COLOR_G, tahomabold_32, display_global,text);
    vid_print_string_alpha(5, (HEIGHT/2)+160, 0x0, 0x9999ff, tahomabold_32, display_global,text);

    return 0;
}
    
    


