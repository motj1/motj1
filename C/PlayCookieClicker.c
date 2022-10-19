// gcc PlayCookieClicker.c -oAuto -framework ApplicationServices
#include <ApplicationServices/ApplicationServices.h>

void rpeat(int times, float x, float y, int sleep){ // 251.0,510.0
    CGPoint CookiePos = CGPointMake(x, y);
    CGEventSourceRef src = CGEventSourceCreate(kCGEventSourceStateHIDSystemState);
    CGEventRef evt;
    for (int i=0; i<times; i++){
        evt = CGEventCreateMouseEvent(src, kCGEventLeftMouseDown, CookiePos, kCGMouseButtonLeft);
        CGEventPost (kCGHIDEventTap, evt);
        CFRelease (evt);
        evt = CGEventCreateMouseEvent(src, kCGEventLeftMouseUp, CookiePos, kCGMouseButtonLeft);
        CGEventPost (kCGHIDEventTap, evt);
        CFRelease (evt);
        usleep(sleep);
    }
    CFRelease (src);
}

int main(int argc, char * argv[]){
    usleep(2000000);
    int times = 100;
    if (argc > 1){
        for (int i=0; i<(floorf(atoi(argv[1])/1030)+1); i++){
            rpeat(900, 251.0, 510.0, 25000);
            rpeat(9, 1393.0, 296.0, 35000);
            rpeat(100, 251.0, 510.0, 25000);
            rpeat(1, 1440.0, 788.0, 15000);
            rpeat(1, 1440.0, 730.0, 15000);
            rpeat(1, 1440.0, 666.0, 15000);
            rpeat(2, 1440.0, 599.0, 15000);
            rpeat(2, 1440.0, 534.0, 15000);
            rpeat(4, 1440.0, 469.0, 15000);
            rpeat(10, 1440.0, 403.0, 20000);
        }
    }
    
    return 0;
}