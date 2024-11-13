entry
    ALLOC x1 262144 
    MOV x4 x1 
    MOV x2 0 
y_loop_init
    MOV x3 0 
x_loop_init
    RAND x6
    AND x6 1
    STORE x6 x4
    ADD x4 1
    LOOP x_loop_init x3 512 
    LOOP y_loop_init x2 256 
    MOV x2 0 
main_loop
    MOV x3 x2
    SHL x3 17 
    MOV x4 0 
    MOV x6 x1 
    ADD x6 x3 
y_loop_draw
    MOV x5 0 
X_LOOP_DRAW
    LOAD x10 x6 
    MOVIFZ x10 x12 0xFF000000 0xFFFFFFFF 
    PUTPIXEL x5 x4 x12
    ADD x6 1
    LOOP x_loop_draw x5 512 
    LOOP y_loop_draw x4 256 
    FLUSH
    MOVIFZ x2 x7 131072 0 
    MOV x9 x7
    ADD x9 x1 
    MOV x8 x3 
    ADD x8 x1 
y_loop_main
    MOV x5 0 
x_loop_main
    MOV x11 0 
    MOV x10 -1 
dy_loop
    MOV x12 x10 
    MOV x13 -1 
    ADD x12 x4 
    SHL x12 9 
    AND x12 130560 
dx_loop
    BRZ loop_end x13 x10 
    ANDD x14 x13 x5 511 
    THOR x14 x12 x3
    ADD x14 x1 
    LOAD x15 x14 
    ADD x11 x15 
loop_end
    LOOP dx_loop x13 2 
    LOOP dy_loop x10 2 
    BREQ live x11 3 
    BREQ remain x11 2 
    MOV x10 0
    BR update
live
    MOV x10 1
    BR update
remain
    LOAD x10 x8 
update
    STORE x10 x16 
    ADD x8 1
    ADD x9 1
    LOOP x_loop_main x5 512 
    LOOP y_loop_main x4 256 
    XOR x2 1 
    BR main_loop
