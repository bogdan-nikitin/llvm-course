    alloc x1 262144 
    mov x4 x1 
    mov x2 0 
y_loop_init
    mov x3 0 
x_loop_init
    rand x6
    and x6 1
    store x6 x4
    add x4 1
    loop x3 512 x_loop_init
    loop x2 256 y_loop_init
    mov x2 0 
main_loop
    mov x3 x2
    shl x3 17 
    mov x4 0 
    mov x6 x1 
    add x6 x3 
y_loop_draw
    mov x5 0 
x_loop_draw
    load x10 x6 
    movifz x10 x12 0xFF000000 0xFFFFFFFF 
    putpixel x5 x4 x12
    add x6 1
    loop x5 512 x_loop_draw
    loop x4 256 y_loop_draw
    flush
    movifz x2 x7 131072 0 
    mov x9 x7
    add x9 x1 
    mov x8 x3 
    add x8 x1 
y_loop_main
    mov x5 0 
x_loop_main
    mov x11 0 
    mov x10 -1 
dy_loop
    mov x12 x10 
    mov x13 -1 
    add x12 x4 
    shl x12 9 
    and x12 130560 
dx_loop
    brz x13 x10 loop_end
    mov x14 x13
    add x14 x5 
    and x14 511 
    thor x14 x12 x3
    add x14 x1 
    load x15 x14 
    add x11 x15 
loop_end
    loop x13 2 dx_loop
    loop x10 2 dy_loop
    breq x11 3 live
    breq x11 2 remain
    mov x10 0
    br update
live
    mov x10 1
    br update
remain
    load x10 x8 
update
    store x10 x16 
    add x8 1
    add x9 1
    loop x5 512 x_loop_main
    loop x4 256 y_loop_main
    xor x2 1 
    br main_loop
