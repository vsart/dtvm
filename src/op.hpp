// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#pragma once

#include <ostream>


// Enumeration of the VM instructions
enum class op {
	halt, // Halts execution of the VM
	noop, // No operations happens

	mov,  // Move value from r1 to r2
	push, // Push value from r1 to top of stack
	pop,  // Pop value from top of stack to r1

	inc,  // Increments value of r1
	dec,  // Decrements value of r1
	add,  // Add value of r1 to r2
	sub,  // Subtract value of r1 from r2
	mul,  // Multiply value of r2 by 41
	div,  // Divide value of r2 by r1

	mod,  // Remainder of the integer division r2/r1

	cil,  // Copy integer literal to r1
	cfl,  // Copy floating point literal to r1

	ods,  // Outputs data string of label lab
	ofv,  // Output formated value of r1 to stdout
	onl,  // Output a newline to stdout and flush it

	iiv,  // Reads an integer value from stdin to r1
	ifv,  // Reads a floating point value from stdin to r1
	ipf,  // Prompts failure status of stdin into r1 (0 -> No failure)

	cmp,  // Compare r1 and r2
	cmpz, // Compare r1 to zero

	jmp,  // Jump to label
	jgt,  // Jump to label if last comparison was `true` for `>`
	jeq,  // Jump to label if last comparison was `true` for `=`
	jlt,  // Jump to label if last comparison was `true` for `<`

	call, // Jumps to a label
	ret,  // Go back to the instruction after the last ret called
};


// Makes `op` enumerations printable
std::ostream &operator<<(std::ostream &os, op const &o);
