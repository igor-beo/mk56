#!/usr/bin/env python3
"""
MK56-ASM Assembler
Assembles MK56-ASM source files to binary format.

Usage:
    python mk56asm.py input.asm [-o output.bin] [-l listing.lst] [-v]
"""

import sys
import re
import struct
import argparse
from dataclasses import dataclass
from typing import List, Dict, Optional, Tuple, Any
from enum import IntEnum

# ============================================================================
# OPCODE DEFINITIONS
# ============================================================================

class Opcode(IntEnum):
    """Instruction opcodes for MK-56"""
    # Stack operations (0x00-0x0F)
    NOP = 0x00
    ENTER = 0x01
    SWAP = 0x02
    CLX = 0x03
    ROLLDOWN = 0x04
    ROLLUP = 0x05
    
    # Arithmetic (0x10-0x1F)
    ADD = 0x10
    SUB = 0x11
    MUL = 0x12
    DIV = 0x13
    CHS = 0x14
    
    # Math functions (0x20-0x2F)
    SQ = 0x20
    SQRT = 0x21
    INV = 0x22
    POW = 0x23
    EXP = 0x24
    EXP10 = 0x25
    LN = 0x26
    LOG = 0x27
    SIN = 0x28
    COS = 0x29
    PI = 0x2A
    
    # Memory operations (0x30-0x4F)
    STO = 0x30      # + register (0-13)
    RCL = 0x40      # + register (0-13)
    STO_ADD = 0x50  # + register
    STO_SUB = 0x60  # + register
    
    # Flow control (0x70-0x7F)
    JMP = 0x70
    JGE = 0x71
    JLT = 0x72
    CALL = 0x73
    RTN = 0x74
    HALT = 0x75
    
    # Literals (0x80+)
    LITERAL = 0x80  # Followed by 8-byte float


# Instruction lookup table: mnemonic -> (opcode, operand_type)
# operand_type: None, 'reg', 'addr', 'literal'
INSTRUCTIONS = {
    # Stack
    'NOP': (Opcode.NOP, None),
    'ENTER': (Opcode.ENTER, None),
    'SWAP': (Opcode.SWAP, None),
    'CLX': (Opcode.CLX, None),
    'ROLLDOWN': (Opcode.ROLLDOWN, None),
    'ROLLUP': (Opcode.ROLLUP, None),
    
    # Arithmetic
    'ADD': (Opcode.ADD, None),
    'SUB': (Opcode.SUB, None),
    'MUL': (Opcode.MUL, None),
    'DIV': (Opcode.DIV, None),
    'CHS': (Opcode.CHS, None),
    
    # Math functions
    'SQ': (Opcode.SQ, None),
    'SQRT': (Opcode.SQRT, None),
    'INV': (Opcode.INV, None),
    'POW': (Opcode.POW, None),
    'EXP': (Opcode.EXP, None),
    'EXP10': (Opcode.EXP10, None),
    'LN': (Opcode.LN, None),
    'LOG': (Opcode.LOG, None),
    'SIN': (Opcode.SIN, None),
    'COS': (Opcode.COS, None),
    'PI': (Opcode.PI, None),
    
    # Memory
    'STO': (Opcode.STO, 'reg'),
    'RCL': (Opcode.RCL, 'reg'),
    'STO+': (Opcode.STO_ADD, 'reg'),
    'STO-': (Opcode.STO_SUB, 'reg'),
    
    # Flow control
    'JMP': (Opcode.JMP, 'addr'),
    'GOTO': (Opcode.JMP, 'addr'),  # Alias
    'JGE': (Opcode.JGE, 'addr'),
    'JLT': (Opcode.JLT, 'addr'),
    'CALL': (Opcode.CALL, 'addr'),
    'RTN': (Opcode.RTN, None),
    'RETURN': (Opcode.RTN, None),  # Alias
    'HALT': (Opcode.HALT, None),
    'STOP': (Opcode.HALT, None),   # Alias
}

# Register name to number mapping
REGISTERS = {
    'R0': 0, 'R1': 1, 'R2': 2, 'R3': 3, 'R4': 4,
    'R5': 5, 'R6': 6, 'R7': 7, 'R8': 8, 'R9': 9,
    'RA': 10, 'RB': 11, 'RC': 12, 'RD': 13,
    # Lowercase aliases
    'r0': 0, 'r1': 1, 'r2': 2, 'r3': 3, 'r4': 4,
    'r5': 5, 'r6': 6, 'r7': 7, 'r8': 8, 'r9': 9,
    'ra': 10, 'rb': 11, 'rc': 12, 'rd': 13,
}


# ============================================================================
# DATA STRUCTURES
# ============================================================================

@dataclass
class Token:
    """Represents a lexical token"""
    type: str       # 'LABEL', 'INSTRUCTION', 'REGISTER', 'NUMBER', 'DIRECTIVE', 'COMMENT'
    value: Any
    line: int
    column: int


@dataclass
class Instruction:
    """Represents a parsed instruction"""
    address: int
    opcode: int
    operand: Optional[Any]
    operand_type: Optional[str]
    label: Optional[str]
    source_line: int
    source_text: str


@dataclass
class AssemblerError(Exception):
    """Assembler error with line information"""
    message: str
    line: int
    column: int = 0
    
    def __str__(self):
        return f"Error at line {self.line}: {self.message}"


# ============================================================================
# LEXER
# ============================================================================

class Lexer:
    """Tokenizes MK56-ASM source code"""
    
    def __init__(self, source: str):
        self.source = source
        self.lines = source.split('\n')
        self.tokens: List[Token] = []
        
    def tokenize(self) -> List[Tuple[int, List[Token]]]:
        """Tokenize source, returns list of (line_num, tokens) tuples"""
        result = []
        
        for line_num, line in enumerate(self.lines, 1):
            tokens = self._tokenize_line(line, line_num)
            if tokens:
                result.append((line_num, tokens))
                
        return result
    
    def _tokenize_line(self, line: str, line_num: int) -> List[Token]:
        """Tokenize a single line"""
        tokens = []
        
        # Remove comments
        comment_match = re.search(r'[;]|//', line)
        if comment_match:
            line = line[:comment_match.start()]
        
        line = line.strip()
        if not line:
            return []
        
        pos = 0
        while pos < len(line):
            # Skip whitespace
            while pos < len(line) and line[pos] in ' \t':
                pos += 1
            if pos >= len(line):
                break
                
            # Label definition (ends with :)
            match = re.match(r'([a-zA-Z_][a-zA-Z0-9_]*):', line[pos:])
            if match:
                tokens.append(Token('LABEL_DEF', match.group(1), line_num, pos))
                pos += len(match.group(0))
                continue
            
            # Directive (starts with .)
            match = re.match(r'\.([a-zA-Z_][a-zA-Z0-9_]*)', line[pos:])
            if match:
                tokens.append(Token('DIRECTIVE', match.group(1).upper(), line_num, pos))
                pos += len(match.group(0))
                continue
            
            # Number (including negative and scientific notation)
            match = re.match(r'-?[0-9]+\.?[0-9]*(?:[eE][+-]?[0-9]+)?', line[pos:])
            if match:
                num_str = match.group(0)
                try:
                    if '.' in num_str or 'e' in num_str.lower():
                        value = float(num_str)
                    else:
                        value = int(num_str)
                    tokens.append(Token('NUMBER', value, line_num, pos))
                except ValueError:
                    raise AssemblerError(f"Invalid number: {num_str}", line_num, pos)
                pos += len(match.group(0))
                continue
            
            # Identifier (instruction, register, or label reference)
            match = re.match(r'[a-zA-Z_][a-zA-Z0-9_]*[+\-]?', line[pos:])
            if match:
                word = match.group(0).upper()
                word_original = match.group(0)
                
                if word in REGISTERS or word_original in REGISTERS:
                    tokens.append(Token('REGISTER', word, line_num, pos))
                elif word in INSTRUCTIONS:
                    tokens.append(Token('INSTRUCTION', word, line_num, pos))
                else:
                    # Assume it's a label reference
                    tokens.append(Token('LABEL_REF', word_original, line_num, pos))
                pos += len(match.group(0))
                continue
            
            # Unknown character
            raise AssemblerError(f"Unexpected character: '{line[pos]}'", line_num, pos)
        
        return tokens


# ============================================================================
# PARSER
# ============================================================================

def get_instruction_size(opcode: int, operand_type: str) -> int:
    """Calculate instruction size in bytes"""
    if opcode == Opcode.LITERAL:
        return 9  # opcode + 8-byte double
    if operand_type == 'addr':
        return 2  # opcode + address byte
    return 1  # simple opcode (including reg ops)


class Parser:
    """Parses tokens into instruction list"""
    
    def __init__(self):
        self.instructions: List[Instruction] = []
        self.labels: Dict[str, int] = {}
        self.constants: Dict[str, Any] = {}
        self.current_address = 0
        self.origin = 0
        
    def parse(self, tokenized_lines: List[Tuple[int, List[Token]]], source_lines: List[str]) -> List[Instruction]:
        """Parse tokenized source into instructions"""
        self.instructions = []
        self.labels = {}
        self.current_address = 0
        
        for line_num, tokens in tokenized_lines:
            source_text = source_lines[line_num - 1].strip()
            self._parse_line(tokens, line_num, source_text)
        
        return self.instructions
    
    def _parse_line(self, tokens: List[Token], line_num: int, source_text: str):
        """Parse a single line of tokens"""
        if not tokens:
            return
            
        idx = 0
        label = None
        
        # Check for label definition
        if tokens[idx].type == 'LABEL_DEF':
            label = tokens[idx].value
            if label in self.labels:
                raise AssemblerError(f"Duplicate label: {label}", line_num)
            self.labels[label] = self.current_address
            idx += 1
            
        if idx >= len(tokens):
            return
            
        token = tokens[idx]
        
        # Handle directives
        if token.type == 'DIRECTIVE':
            self._handle_directive(tokens[idx:], line_num)
            return
            
        # Handle instructions
        if token.type == 'INSTRUCTION':
            mnemonic = token.value
            opcode, operand_type = INSTRUCTIONS[mnemonic]
            operand = None
            
            if operand_type is not None:
                if idx + 1 >= len(tokens):
                    raise AssemblerError(f"{mnemonic} requires an operand", line_num)
                operand_token = tokens[idx + 1]
                
                if operand_type == 'reg':
                    if operand_token.type != 'REGISTER':
                        raise AssemblerError(f"{mnemonic} requires a register operand", line_num)
                    operand = REGISTERS[operand_token.value]
                elif operand_type == 'addr':
                    if operand_token.type == 'NUMBER':
                        operand = int(operand_token.value)
                    elif operand_token.type == 'LABEL_REF':
                        operand = operand_token.value  # Resolve later
                    else:
                        raise AssemblerError(f"{mnemonic} requires an address operand", line_num)
            
            self.instructions.append(Instruction(
                address=self.current_address,
                opcode=opcode,
                operand=operand,
                operand_type=operand_type,
                label=label,
                source_line=line_num,
                source_text=source_text
            ))
            self.current_address += get_instruction_size(opcode, operand_type)
            return
            
        # Handle numeric literal (push to stack)
        if token.type == 'NUMBER':
            self.instructions.append(Instruction(
                address=self.current_address,
                opcode=Opcode.LITERAL,
                operand=float(token.value),
                operand_type='literal',
                label=label,
                source_line=line_num,
                source_text=source_text
            ))
            self.current_address += get_instruction_size(Opcode.LITERAL, 'literal')
            return
            
        raise AssemblerError(f"Unexpected token: {token.value}", line_num)
    
    def _handle_directive(self, tokens: List[Token], line_num: int):
        """Handle assembler directives"""
        directive = tokens[0].value
        
        if directive == 'ORG':
            if len(tokens) < 2 or tokens[1].type != 'NUMBER':
                raise AssemblerError(".ORG requires an address", line_num)
            self.current_address = int(tokens[1].value)
            self.origin = self.current_address
            
        elif directive == 'EQU':
            if len(tokens) < 3:
                raise AssemblerError(".EQU requires name and value", line_num)
            name = tokens[1].value
            value = tokens[2].value
            self.constants[name] = value
            
        elif directive == 'END':
            pass  # End of program, no action needed
            
        elif directive in ('ASSERT', 'TRACE', 'BREAK', 'INPUT'):
            pass  # Emulator-only directives, ignore in assembler
            
        else:
            raise AssemblerError(f"Unknown directive: .{directive}", line_num)


# ============================================================================
# ASSEMBLER
# ============================================================================

class Assembler:
    """Assembles parsed instructions to binary"""
    
    def __init__(self, instructions: List[Instruction], labels: Dict[str, int]):
        self.instructions = instructions
        self.labels = labels
        self.binary: bytes = b''
        self.listing: List[str] = []
        
    def assemble(self) -> bytes:
        """Assemble instructions to binary"""
        output = bytearray()
        self.listing = []
        
        for instr in self.instructions:
            # Resolve label references
            if instr.operand_type == 'addr' and isinstance(instr.operand, str):
                label = instr.operand
                if label.upper() not in self.labels and label not in self.labels:
                    raise AssemblerError(f"Undefined label: {label}", instr.source_line)
                instr.operand = self.labels.get(label, self.labels.get(label.upper()))
            
            # Generate binary
            binary = self._encode_instruction(instr)
            output.extend(binary)
            
            # Generate listing line
            hex_bytes = ' '.join(f'{b:02X}' for b in binary)
            label_str = f"{instr.label}:" if instr.label else ""
            self.listing.append(
                f"{instr.address:03d}  {hex_bytes:<20}  {label_str:<12} {instr.source_text}"
            )
        
        self.binary = bytes(output)
        return self.binary
    
    def _encode_instruction(self, instr: Instruction) -> bytes:
        """Encode a single instruction to bytes"""
        if instr.opcode == Opcode.LITERAL:
            # Literal: opcode + 8-byte double
            return struct.pack('<Bd', Opcode.LITERAL, instr.operand)
        
        elif instr.operand_type == 'reg':
            # Register operation: opcode + register combined in one byte
            return bytes([instr.opcode + instr.operand])
        
        elif instr.operand_type == 'addr':
            # Address operation: opcode + 1-byte address
            if instr.operand < 0 or instr.operand > 255:
                raise AssemblerError(f"Address out of range: {instr.operand}", instr.source_line)
            return bytes([instr.opcode, instr.operand])
        
        else:
            # Simple opcode, no operand
            return bytes([instr.opcode])
    
    def get_listing(self) -> str:
        """Get assembly listing"""
        header = "ADDR  BYTES                 LABEL        SOURCE\n"
        header += "=" * 70 + "\n"
        return header + '\n'.join(self.listing)


# ============================================================================
# MAIN
# ============================================================================

def assemble_file(input_path: str, output_path: Optional[str] = None, 
                  listing_path: Optional[str] = None, verbose: bool = False) -> bool:
    """Assemble a single file"""
    try:
        # Read source
        with open(input_path, 'r', encoding='utf-8') as f:
            source = f.read()
        
        if verbose:
            print(f"Assembling: {input_path}")
        
        # Tokenize
        lexer = Lexer(source)
        tokenized = lexer.tokenize()
        
        if verbose:
            print(f"  Tokenized {len(tokenized)} lines")
        
        # Parse
        parser = Parser()
        instructions = parser.parse(tokenized, source.split('\n'))
        
        if verbose:
            print(f"  Parsed {len(instructions)} instructions")
            print(f"  Labels: {parser.labels}")
        
        # Assemble
        assembler = Assembler(instructions, parser.labels)
        binary = assembler.assemble()
        
        if verbose:
            print(f"  Generated {len(binary)} bytes")
        
        # Write output
        if output_path is None:
            output_path = input_path.rsplit('.', 1)[0] + '.bin'
        
        with open(output_path, 'wb') as f:
            f.write(binary)
        
        print(f"Output: {output_path} ({len(binary)} bytes)")
        
        # Write listing if requested
        if listing_path:
            with open(listing_path, 'w', encoding='utf-8') as f:
                f.write(assembler.get_listing())
            print(f"Listing: {listing_path}")
        
        if verbose:
            print("\nAssembly Listing:")
            print(assembler.get_listing())
        
        return True
        
    except AssemblerError as e:
        print(f"Assembly error: {e}", file=sys.stderr)
        return False
    except FileNotFoundError:
        print(f"File not found: {input_path}", file=sys.stderr)
        return False
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return False


def main():
    """Command-line entry point"""
    parser = argparse.ArgumentParser(
        description='MK56-ASM Assembler - Assemble MK56-ASM source to binary'
    )
    parser.add_argument('input', help='Input .asm file')
    parser.add_argument('-o', '--output', help='Output .bin file')
    parser.add_argument('-l', '--listing', help='Generate listing file')
    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
    
    args = parser.parse_args()
    
    success = assemble_file(
        args.input,
        args.output,
        args.listing,
        args.verbose
    )
    
    sys.exit(0 if success else 1)


if __name__ == '__main__':
    main()
