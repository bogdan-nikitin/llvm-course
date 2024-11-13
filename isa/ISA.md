# ISA

Описание набора команд

16 регистров общего назначения `x1`...`x16`


* `ADD xi xj` - `xi += xj`
* `ALLOC xi imm` - выделить на стеке `imm` байт и 
записать указатель на начало в регистр `xi`
* `AND xi imm` - `xi &= imm`
* `ANDD xi xj xk imm` - `xi = (xj + xk) & imm`
* `BR label` - перейти на метку `label`
* `BREQ label xi imm` - перейти на метку `label` если `xi == imm`, 
иначе перейти к следующей инструкции
* `BRZ label xi xj` - перейти на метку `label` если `xi == 0 && xj == 0`
* `EXIT` - завершить исполнение
* `FLUSH` - `simFlush()`
* `INC xi` - `++xi`
* `LOAD xi xj` - загрузить в регистр `xj` байт по адресу, записанном в `xj`
* `LOOP label xi imm` - если `xi != imm`, перейти на метку `label` и 
увеличить значение `xi` на 1, иначе перейти к следующей инструкции
* `MOV xi xj` - `xi = xj`
* `MOVIFZ xi xj imm1 imm2` - `xi = xj == 0 ? imm1 : imm2`
* `PUTPIXEL xi xj xk` - `simPutPixel(xi, xj, xk)`
* `RAND xi` - `xi = simRand()`
* `SET xi imm` - `xi = imm`
* `SHL xi imm` - `xi <<= imm`
* `STORE xi xj` - записать в память по адресу `xj` байт `xi`
* `THOR xi xj xk` - `xi |= xj | xk`
* `XOR xi imm` - `xi ^= imm`
