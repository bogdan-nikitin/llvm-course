entry
    ALLOC x1 262144 
    MOV x4 x1 
    SET x2 0 
y_loop_init
    SET x3 0 
x_loop_init
    RAND x6
    AND x6 1
    STORE x6 x4
    INC x4
    LOOP x_loop_init x3 512 
x_loop_init_end
    LOOP y_loop_init x2 256 
y_loop_init_end
    SET x2 0 
main_loop
    MOV x3 x2
    SHL x3 17 
    SET x4 0 
    MOV x6 x1 
y_loop_draw
    SET x5 0 
x_loop_draw
    LOAD x10 x6 
    MOVIFZ x12 x10 4278190080 4294967295 
    PUTPIXEL x5 x4 x12
    INC x6
    LOOP x_loop_draw x5 512 
x_loop_draw_end
    LOOP y_loop_draw x4 256 
y_loop_draw_end
    FLUSH
    MOVIFZ x7 x2 131072 0 
    MOV x9 x7
    ADD x9 x1 
    MOV x8 x3 
    ADD x8 x1 
    SET x4 0
y_loop_main
    SET x5 0 
x_loop_main
    SET x11 0 
    SET x10 -1 
dy_loop
    MOV x12 x10 
    SET x13 -1 
    ADD x12 x4 
    SHL x12 9 
    AND x12 130560 
dx_loop
    BRZ loop_end x13 x10 
inner_loop
    ANDD x14 x13 x5 511 
    THOR x14 x12 x3
    ADD x14 x1 
    LOAD x15 x14 
    ADD x11 x15 
loop_end
    LOOP dx_loop x13 2 
dx_loop_end
    LOOP dy_loop x10 2 
dy_loop_end
    BREQ live x11 3 
die_or_remain
    BREQ remain x11 2 
die
    SET x10 0
    BR update
live
    SET x10 1
    BR update
remain
    LOAD x10 x8 
update
    STORE x10 x9
    INC x8
    INC x9
    LOOP x_loop_main x5 512 
x_loop_main_end
    LOOP y_loop_main x4 256 
y_loop_main_end
    XOR x2 1 
    BR main_loop
unreachable
    EXIT
