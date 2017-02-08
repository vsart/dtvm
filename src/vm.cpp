// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#include "vm.hpp"

#include <iostream>
#include <stack>

#include "args.hpp"
#include "error.hpp"


enum state_flag {
    VM_FLAG_GT = 0b100,
    VM_FLAG_EQ = 0b010,
    VM_FLAG_LT = 0b001,
};


void execute(Code code)
{
    std::stack<var> stack;
    std::stack<size_t> callstack;
    std::vector<var> reg(dtvm_args::num_regs, var(0));
    uint8_t flags = 0;

    var a1, a2;
    var_type optype;

    size_t pc;
    for (pc = 0; pc < code.size(); pc++) {
        const auto op = code[pc].as_op();

        if (code[pc].get_type() != var_type::operation) {
            std::cout << Error() << "VM tried to execute a non-operation at " << pc << std::endl;
            return;
        }

        switch (op) {
        case op::halt:
            return;

        case op::noop:
            break;

        case op::mov:
            reg[code[pc+2].as_int()] = reg[code[pc+1].as_int()];
            pc += 2;
            break;

        case op::push:
            stack.push(reg[code[pc+1].as_int()]);
            pc += 1;
            break;

        case op::pop:
            reg[code[pc+1].as_int()] = stack.top();
            stack.pop();
            pc += 1;
            break;

        case op::inc:
            a1 = reg[code[pc+1].as_int()];
            optype = a1.get_type();
            if (optype == var_type::integer)
                reg[code[pc+1].as_int()] = reg[code[pc+1].as_int()].as_int() + 1;
            else
                reg[code[pc+1].as_int()] = reg[code[pc+1].as_int()].as_float() + 1;
            pc += 1;
            break;

        case op::dec:
            a1 = reg[code[pc+1].as_int()];
            optype = a1.get_type();
            if (optype == var_type::integer)
                reg[code[pc+1].as_int()] = reg[code[pc+1].as_int()].as_int() - 1;
            else
                reg[code[pc+1].as_int()] = reg[code[pc+1].as_int()].as_float() - 1;
            pc += 1;
            break;

        case op::add:
            a1 = reg[code[pc+1].as_int()];
            a2 = reg[code[pc+2].as_int()];
            optype = a1.get_type();
            if (optype != a2.get_type()) {
                std::cerr << Error() << "Type mismatch at " << pc << std::endl;
                return;
            }
            if (optype == var_type::integer) {
                reg[code[pc+2].as_int()] = var(a2.as_int() + a1.as_int());
            } else {
                reg[code[pc+2].as_int()] = var(a2.as_float() + a1.as_float());
            }
            // Implicitly doing nothing when optype is `op` (shouldn't happen).
            pc += 2;
            break;

        case op::sub:
            a1 = reg[code[pc+1].as_int()];
            a2 = reg[code[pc+2].as_int()];
            optype = a1.get_type();
            if (optype != a2.get_type()) {
                std::cerr << Error() << "Type mismatch at " << pc << std::endl;
                return;
            }
            if (optype == var_type::integer) {
                reg[code[pc+2].as_int()] = var(a2.as_int() - a1.as_int());
            } else {
                reg[code[pc+2].as_int()] = var(a2.as_float() - a1.as_float());
            }
            // Implicitly doing nothing when optype is `op` (shouldn't happen).
            pc += 2;
            break;

        case op::mul:
            a1 = reg[code[pc+1].as_int()];
            a2 = reg[code[pc+2].as_int()];
            optype = a1.get_type();
            if (optype != a2.get_type()) {
                std::cerr << Error() << "Type mismatch at " << pc << std::endl;
                return;
            }
            if (optype == var_type::integer) {
                reg[code[pc+2].as_int()] = var(a2.as_int() * a1.as_int());
            } else {
                reg[code[pc+2].as_int()] = var(a2.as_float() * a1.as_float());
            }
            // Implicitly doing nothing when optype is `op` (shouldn't happen).
            pc += 2;
            break;

        case op::div:
            a1 = reg[code[pc+1].as_int()];
            a2 = reg[code[pc+2].as_int()];
            optype = a1.get_type();
            if (optype != a2.get_type()) {
                std::cerr << Error() << "Type mismatch at " << pc << std::endl;
                return;
            }
            if (optype == var_type::integer) {
                reg[code[pc+2].as_int()] = var(a2.as_int() / a1.as_int());
            } else {
                reg[code[pc+2].as_int()] = var(a2.as_float() / a1.as_float());
            }
            // Implicitly doing nothing when optype is `op` (shouldn't happen).
            pc += 2;
            break;

        case op::mod:
            a1 = reg[code[pc+1].as_int()];
            a2 = reg[code[pc+2].as_int()];
            optype = a1.get_type();
            if (optype != a2.get_type()) {
                std::cerr << Error() << "Type mismatch at " << pc << std::endl;
                return;
            }
            if (optype != var_type::integer) {
                std::cerr << Error() << "Invalid type at " << pc << std::endl;
                return;
            }
            reg[code[pc+2].as_int()] = var(a2.as_int() % a1.as_int());
            pc += 2;
            break;

        case op::cil:
            reg[code[pc+2].as_int()] = var(code[pc+1].as_int());
            pc += 2;
            break;

        case op::cfl:
            reg[code[pc+2].as_int()] = var(code[pc+1].as_float());
            pc += 2;
            break;

        case op::ofv:
            std::cout << reg[code[pc+1].as_int()] << ' ';
            pc += 1;
            break;

        case op::onl:
            std::cout << std::endl;
            break;

        case op::cmp:
            a1 = reg[code[pc+1].as_int()];
            a2 = reg[code[pc+2].as_int()];
            optype = a1.get_type();
            if (optype != a2.get_type()) {
                std::cerr << Error() << "Type mismatch at " << pc << std::endl;
                return;
            }
            if (optype == var_type::integer) {
                const auto v1 = a1.as_int();
                const auto v2 = a2.as_int();
                if (v1 < v2) {
                    flags = VM_FLAG_LT;
                } else if (v1 == v2) {
                    flags = VM_FLAG_EQ;
                } else {
                    flags = VM_FLAG_GT;
                }
            } else {
                const auto v1 = a1.as_float();
                const auto v2 = a2.as_float();
                if (v1 < v2) {
                    flags = VM_FLAG_LT;
                } else if (v1 == v2) {
                    flags = VM_FLAG_EQ;
                } else {
                    flags = VM_FLAG_GT;
                }
            }
            // Implicitly doing nothing when optype is `op` (shouldn't happen).
            pc += 2;
            break;

        case op::cmpz:
            a1 = reg[code[pc+1].as_int()];
            optype = a1.get_type();
            if (optype == var_type::integer) {
                const auto v1 = a1.as_int();
                if (v1 < 0) {
                    flags = VM_FLAG_LT;
                } else if (v1 == 0) {
                    flags = VM_FLAG_EQ;
                } else {
                    flags = VM_FLAG_GT;
                }
            } else {
                const auto v1 = a1.as_float();
                if (v1 < 0) {
                    flags = VM_FLAG_LT;
                } else if (v1 == 0) {
                    flags = VM_FLAG_EQ;
                } else {
                    flags = VM_FLAG_GT;
                }
            }
            // Implicitly doing nothing when optype is `op` (shouldn't happen).
            pc += 1;
            break;

        case op::jmp:
            pc = code[pc+1].as_int() - 1; // - 1 Because of increment
            break;

        case op::jgt:
            if (flags & VM_FLAG_GT)
                pc = code[pc+1].as_int() - 1; // - 1 Because of increment
            else
                pc += 1;
            break;

        case op::jeq:
            if (flags & VM_FLAG_EQ)
                pc = code[pc+1].as_int() - 1; // - 1 Because of increment
            else
                pc += 1;
            break;

        case op::jlt:
            if (flags & VM_FLAG_LT)
                pc = code[pc+1].as_int() - 1; // - 1 Because of increment
            else
                pc += 1;
            break;

        case op::call:
            callstack.push(pc + 1);
            pc = code[pc+1].as_int() - 1; // - 1 Because of increment
            break;

        case op::ret:
            if (callstack.empty()) {
                std::cerr << Error() << "`ret` in an empty callstack at " << pc << std::endl;
                return;
            }
            pc = callstack.top();
            callstack.pop();
            break;
        }
    }
}
