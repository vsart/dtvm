# DTVM

A toy VM implemented in C++

This project is licensed under the terms of the MIT License. <br>
See the LICENSE file for further details.

## 1. Usage

`./dtvm [source] [options...]`

| Options | Description |
|---------|-------------|
| -no-acc <br> -no-ansi-color-codes |  Tells the application not to use ANSI color codes on outputs. |
| -parse-and-print | Makes it so the application only parses the code and print the interpreted version <br> to the stdout, not executing it. The only difference between the printed code from <br> the source is that there are no empty lines, labels or comments, and j** instructions <br> hold the index to be jumped to as their arguments. |
| -r8 <br> -r16 <br> -r32 | Sets the number of registers of the VM to 8, 16 and 32 respectively. |

## 2. Instructions

| Instruction | Arguments | Description |
|-------------|-----------|-------------|
`halt` | None   | Halts execution of the VM
`noop` | None   | No operations happen
`mov`  | r1 r2  | Copies the value of r1 into r2
`push` | r1     | Push value of r1 into the top of the stack
`pop`  | r1     | Pops the top of the stack into r1
`inc`  | r1     | Increments the value of r1 by 1.
`dec`  | r1     | Decrements the value of r1 by 1.
`add`¹ | r1 r2  | Adds value of r1 to r2
`sub`¹ | r1 r2  | Subtracts value of r1 from r2
`mul`¹ | r1 r2  | Multiplies value of r2 by r1
`div`¹ | r1 r2  | Divides r2 by r1
`mod`² | r1 r2  | Modulo operation of r2 by r1
`cil`  | lit r2 | Sets the value of r2 to match the integer literal lit
`cfl`  | lit r2 | Sets the value of r2 to match the floating point literal lit
`ofv`  | r1     | Output formatted value of r1 to stdout
`onl`  | None   | Print newline and flush stdout
`cmp`¹ | r1 r2  | Compare r1 and r2
`cmpz` | r1     | Compare r1 to the appropriate zero
`jmp`  | lab    | Jumps uncoditionally to label lab
`jgt`  | lab    | Jumps to label lab last comparison was `true` for `>`
`jeq`  | lab    | Jumps to label lab last comparison was `true` for `=`
`jlt`  | lab    | Jumps to label lab last comparison was `true` for `<`
`call` | lab    | Jumps to label lab pushing the address of the next instruction into<br>the call stack.
`ret`  | None   | Jumps to the address at the top of the callstack and pops it.

¹ Fails if the operands don't have the same type <br>
² Fails if the operands aren't both integers

## 3. Labels and Comments

Comments start with ';', and they can either start at the beginning
of a line or in the end of a line after a full instruction (the
instruction token and the arguments).

Label declarations need to be alone in a line. Since a `halt`
instruction is always added to the end of the code, a label declared
in the end of a file will reference a `halt` instruction.
A label needs to start with `@` and not contain any whitespace
characters. When referencing the label in a j** instruction, the
`@` should not be removed.
