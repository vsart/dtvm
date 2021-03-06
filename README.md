![DTVM](images/Logo.png) <br>
<sup> Gecko made by [Freepik](http://www.flaticon.com/authors/freepik) from [flaticon](www.flaticon.com) and font [Abel](https://fonts.google.com/specimen/Abel) made by [MADType](http://www.madtype.com/)</sup>

A toy VM implemented in C++

This project is licensed under the terms of the MIT License. <br>
See the LICENSE file for further details.

## 1. Usage

`./dtvm [source] [options...]`

| Options | Description |
|---------|-------------|
| -no-acc <br> -no-ansi-color-codes |  Tells the application not to use ANSI color codes on outputs. |
| -parse-and-print | Makes it so the application only parses the code and print the interpreted version <br> to the stdout, not executing it. The only difference between the printed code from <br> the source is that there are no empty lines, labels or comments, and j** instructions <br> hold the index to be jumped to as their arguments. |
| -r`val` | Sets the number of registers of the VM to `val`. |
| -e`labname` | Sets the entry point of the program to be at label `labname` |
| -show-data | Only takes effect if -parse-and-print was given.  Also displays strings with the code. |
| -debug | Starts the VM into debugging mode |

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
`ods`  | lab    | Prints the constant string represented by lab.
`ofv`  | r1     | Output formatted value of r1 to stdout
`onl`  | None   | Print newline and flush stdout
`iiv`  | r1     | Reads integer value from stdin into r1.
`ifv`  | r1     | Reads floating point value from stdin into r1.
`ipf`  | r1     | Prompts failure on reading inputs onto r1. <br> r1 receives =0 for no error and >0 for error.
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

## 3. Comments about the assembly

Comments start with ';', and they can either start at the beginning
of a line or in the end of a line after a full instruction (the
instruction token and the arguments).

Label declarations need to be alone in a line (comments after the declaration aren't counted).
A label declaration needs to end with `:` and not contain any whitespace characters.
When referencing the label in a j** instruction, the last `:` should be removed.
Since a `halt` instruction is always added to the end of the code, a label declared in the end of
a file will reference a `halt` instruction.

The program starts execution on the entry point label, which defaults to `_start`, but can be set
through command line options.

Also, any label `.lab` starting with a dot is considered a sublabel and is expanded to `cl.lab`,
where `cl` is the context label, that being the last non-sublabel label read in the file.

Constant strings can be defined using the syntax `data string_name "string"`. They must be defined
before any reference to that string happens.

In general, see the examples folder for examples.
