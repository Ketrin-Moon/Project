#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>

struct win{
        WINDOW*wnd;
        WINDOW*wnd2;
        WINDOW*wnd3;
        WINDOW*wnd4;
        WINDOW*wnd5;
        WINDOW*subwnd;
        WINDOW*subwnd2;
        WINDOW*subwnd3;
        WINDOW*subwnd4;
};

WINDOW* window1(int y, int x, int py, int px){
        WINDOW* wnd;
        wnd=newwin(y,x,py,px);
        box(wnd, 0, 0);
        wrefresh(wnd);
        refresh();
        return wnd;
}
WINDOW* window2(WINDOW* wnd, int y, int x, int py, int px){
        WINDOW* subwnd;
        subwnd=derwin(wnd,y,x,py,px);
        wrefresh(subwnd);
        scrollok(subwnd, TRUE);
        return subwnd;
}
void color_pair(WINDOW *win, int color_bg)
{
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLUE);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
        wbkgd(win, COLOR_PAIR(color_bg));
}

struct win create_interface(){
	struct win interface;
	int row, col;
        initscr();
        cbreak();
        refresh();
        echo();
	curs_set(0);
	getmaxyx(stdscr, row, col);
        interface.wnd5=window1(row,col,0,0);
	color_pair(interface.wnd5, 1);
	wrefresh(interface.wnd5);
        interface.wnd=window1(row-35,col-2,2,1);
	color_pair(interface.wnd, 4);
//        interface.subwnd=window2(interface.wnd,row-35,col-2,1,1);
        interface.wnd2=window1(row-35,col-2,row - 30,1);
	color_pair(interface.wnd2, 4);

  //      interface.subwnd2=window2(interface.wnd2,row-35,col-2,row-34,1);
        interface.wnd3=window1(row-20,col/2-2,row-22,1);
	color_pair(interface.wnd3, 4);

    //    interface.subwnd3=window2(interface.wnd3,row-20,col/2,row-25,1);
        interface.wnd4=window1(row-20,col/2-1,row-22,col/2);
	color_pair(interface.wnd4, 4);

//        interface.subwnd4=window2(interface.wnd4,row-20,col/2-2,row-25, col-88);
	wrefresh(interface.wnd);
	wrefresh(interface.wnd2);
	wrefresh(interface.wnd3);
	wrefresh(interface.wnd4);

        return interface;
}

void  del_interface(struct win *interface){
        delwin(interface->wnd);
        delwin(interface->subwnd);
        delwin(interface->wnd2);
        delwin(interface->subwnd2);
        delwin(interface->wnd3);
        delwin(interface->subwnd3);
        endwin();
        exit(EXIT_SUCCESS);
}

int main(){
	 struct win interface=create_interface();
	 getchar();
	 del_interface(&interface);
	return 0;
}
