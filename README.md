# Simple Virtual Machine
## Table of Contents
0. [Some info](#si)
   - 0.1. [Structure of the command](#sotc)
   - 0.2. [Debug flags](#df)
1. [Commands](#cmds)
   - 1.1. [0x](#Zero)
      - 1.1.1. [halt](#halt)
      - 1.1.2. [clrf](#clrf)
   - 1.2. [mov](#mov)
   - 1.3. [add](#add)
   - 1.4. [sub](#sub)
   - 1.5. [mul](#mul)
   - 1.6. [div](#div)
   - 1.7. [inc](#inc)
   - 1.8. [dec](#dec)
   - 1.9. [and](#and)
   - 1.10. [or](#or)
   - 1.11. [xor](#xor)
   - 1.12. [shift](#shift)
   - 1.13. [jmp variants](#jmpInstr)
      - 1.13.1. [jmp](#jmp)
      - 1.13.2. [je](#je)
      - 1.13.3. [jne](#jne)
      - 1.13.4. [jo](#jo)
      - 1.13.5. [jno](#jno)
      - 1.13.6. [jz](#jz)
      - 1.13.7. [jnz](#jnz)
      - 1.13.8. [jl](#jl)
      - 1.13.9. [jnl](#jnl)
   - 1.14. [Stack functions](#stk)
      - 1.14.1. [push](#push)
      - 1.14.2. [pop](#pop)
   - 1.15. [cmp](#cmp)
   - 1.17. [scall](#scall)

## Some info <a name="si"></a>
### Structure of the command <a name="sotc"></a>
The command is a type uint32_t. <br>
00000: <br>
1. First 4 bits - op code; <br>
2. Second 4 bits(nnnn) - mode; <br>
3. Third  4 bits(nnn) - register; <br>
4. Fourth 4 bits(nn) - register or
together with the Fifth 4 bits(n) represent the value(from 0 to 255); <br>
The modes of each operation are represented in the table below. <br>
```
Example:
1010A // mov r1, 10
11010 // mov r0, r1
```

### Debug flags <a name="df"></a>
The VM has 4 flags. A Equal(e), a Overflow(o), a Zero(z) and a Logic(l). By default all flags except zero flag is false. <br>
- Equal flag is true, if the result of cmp command is true.
- Overflow flag is true, if the result of the operation is bigger than 255
- Zero flag is true, if the result is 0
- Logic flag is true if the result of operations (or | and | xor) is true.
You can reset flags using function clrf or use jmp instructions.

## Commands <a name="cmds"></a>
### 0x <a name="Zero"></a>
   - #### Halt <a name="halt"></a>
     Halt - end of the program. <br>
     Op code: 00000 or 0 <br>
   - #### Clrf <a name="clrf"></a>
     Clrf - clear flags. <br>
     Op code: 01000 <br>

### Mov <a name="mov"></a>
Mov - set value to register. <br>
Op code: 10000 <br>
Has 2 mods(nnnn): <br>
1. 0 - Set value(nn) to the reg1
2. 1 - Set value of the reg2 to reg1
```
Example:
101FF // mov r1, 255
11010 // mov r0, r1
```

### Add <a name="add"></a>
Add - Sums up two registers or register and value. <br>
Op code: 20000 <br>
Has 2 mods(nnnn): <br>
1. 0 - Add value(nn) to the reg1
2. 1 - Add reg2 and reg1
```
Example:
2010A // add r1, 10
21010 // add r0, r1
```

### Sub <a name="sub"></a>
Sub - Subtracts two registers or register and value. <br>
Op code: 30000 <br>
Has 2 mods(nnnn): <br>
1. 0 - Sub value(nn) to the reg1
2. 1 - Sub reg2 and reg1
```
Example:
3010B // sub r1, 11
31100 // sub r1, r0
```

### Mul <a name="mul"></a>
Mul - Multiplies two registers or register and value. <br>
Op code: 40000 <br>
Has 2 mods(nnnn): <br>
1. 0 - Mul value(nn) to the reg1
2. 1 - Mul reg2 and reg1
```
Example:
4010B // mul r1, 11
41100 // mul r1, r0
```

### Div <a name="div"></a>
Div - Divides two registers or register and value. <br>
Op code: 50000 <br>
Has 2 mods(nnnn): <br>
1. 0 - Div value(nn) to the reg1
2. 1 - Div reg2 and reg1
```
Example:
5010B // div r1, 11
51100 // div r1, r0
```

### Inc <a name="inc"></a>
Inc - increment register <br>
Op code: 60000 <br>
```
Example:
60100 // inc r1
```

### Dec <a name="dec"></a>
Dec - decrement register <br>
Op code: 70000 <br>
```
Example:
70100 // dec r1
```

### And <a name="and"></a>

### Or <a name="or"></a>

### Xor <a name="xor"></a>

### Shift <a name="shift"></a>

### Jump variants <a name="jumpInstr"></a>

### Stack functions <a name="stk"></a>

### Cmp <a name="cmp"></a>
Cmp - Compares two registers or register and value. If they are equal Logic flag sets to true <br>
Op code: E0000 <br>
Has 2 mods(nnnn): <br>
1. 0 - Cmp value(nn) to the reg1
2. 1 - Cmp reg2 and reg1
```
Example:
E010B // cmp r1, 11
E1100 // cmp r1, r0
```

### SCALL <a name="scall"></a>
