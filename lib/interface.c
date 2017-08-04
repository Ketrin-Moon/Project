#include "../include/header.h"

//extern struct win interface;
struct win interface;

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
	int row, col;
	setlocale(LC_CTYPE, "ru_RU.UTF-8");
        initscr();
        cbreak();
        refresh();
        echo();
	curs_set(0);

	interface.wnd=window1(4,92,1,1);
        interface.subwnd=window2(interface.wnd,2,78,1,1);
	color_pair(interface.wnd, 4);
	color_pair(interface.subwnd, 4);

	interface.wnd2=window1(4,92,5,1);
        interface.subwnd2=window2(interface.wnd2,2,78,1,1);

	color_pair(interface.wnd2, 4);
	color_pair(interface.subwnd2, 4);
 
	interface.wnd3=window1(10,45,9,1);
        interface.subwnd3=window2(interface.wnd3,8,40,1,1);
	color_pair(interface.wnd3, 4);
	color_pair(interface.subwnd3, 4);

        interface.wnd4=window1(10,45,9,47);
        interface.subwnd4=window2(interface.wnd4,8,40,1,1);
	color_pair(interface.wnd4, 4);
	color_pair(interface.subwnd4, 4);

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
