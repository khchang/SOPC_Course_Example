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

#define FREQ    2


int main()
{
      int i,j;
      unsigned int plot_x,plot_y;
      unsigned int* current_buffer_addr;
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

/*     
    for(i=1;i<=7;i++)
    {
        switch(i)
        {
            case 1:
                color=0x0000ff;
            break;
            case 2:
                color=0x00ff00;
            break;
            case 3:
                color=0xff0000;
            break;
            case 4:
                color=0x00ffff;
            break;
            case 5:
                color=0xffff00;
            break;
            case 6:
                color=0xff00ff;
            break;
            case 7:
                color=0xffffff;
            break;
            
        }
        vid_draw_circle(WIDTH/2,HEIGHT/2,20*i,color,0,display_global);
    }     
  */
  
    
   sprintf(text,"Sine Wave: %d Hz\n",FREQ);
   vid_print_string_alpha(5, 10, COLOR_WHITE, COLOR_BLACK, tahomabold_20, display_global,text);

   
   current_buffer_addr=(unsigned int*)(display_global->buffer_ptrs[display_global->buffer_being_written]->buffer);
      
   while(1)
   {  
        for(j=1;j<=10;j++)
        {    
            for(i=0;i<WIDTH;i++)
            {
                plot_x=i;
                plot_y=(HEIGHT/2)-(int)((HEIGHT/2)*((double)j/10)*sin(2*3.1415925*FREQ*((double)i/WIDTH)));
                current_buffer_addr[plot_y*WIDTH+plot_x]=0x00FFFF;
                plot_y=(HEIGHT/2)+(int)((HEIGHT/2)*((double)j/10)*sin(2*3.1415925*FREQ*((double)i/WIDTH)));
                current_buffer_addr[plot_y*WIDTH+plot_x]=0xFFFF00;
                display_global->buffer_being_displayed=display_global->buffer_being_written;
                usleep(1*1*1000);
            }
        }
        for(j=1;j<=10;j++)
        {    
            for(i=0;i<WIDTH;i++)
            {
                plot_x=i;
                plot_y=(HEIGHT/2)-(int)((HEIGHT/2)*((double)j/10)*sin(2*3.1415925*FREQ*((double)i/WIDTH)));
                current_buffer_addr[plot_y*WIDTH+plot_x]=0x000000;
                plot_y=(HEIGHT/2)+(int)((HEIGHT/2)*((double)j/10)*sin(2*3.1415925*FREQ*((double)i/WIDTH)));
                current_buffer_addr[plot_y*WIDTH+plot_x]=0x000000;
                display_global->buffer_being_displayed=display_global->buffer_being_written;
                usleep(1*1*1000);
            }
        }        
    }  
    
    return 0;
}
    
    


