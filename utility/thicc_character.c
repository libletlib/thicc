/*
 * TTTTTTTTTTTTTTTTTTTTTTThhhhhhh               iiii                              CCCCCCCCCCCCC
 * T:::::::::::::::::::::Th:::::h              i::::i                          CCC::::::::::::C
 * T:::::::::::::::::::::Th:::::h               iiii                         CC:::::::::::::::C
 * T:::::TT:::::::TT:::::Th:::::h                                           C:::::CCCCCCCC::::C
 * TTTTTT  T:::::T  TTTTTT h::::h hhhhh       iiiiiii     cccccccccccccccc C:::::C       CCCCCC
 *         T:::::T         h::::hh:::::hhh    i:::::i   cc:::::::::::::::cC:::::C
 *         T:::::T         h::::::::::::::hh   i::::i  c:::::::::::::::::cC:::::C
 *         T:::::T         h:::::::hhh::::::h  i::::i c:::::::cccccc:::::cC:::::C
 *         T:::::T         h::::::h   h::::::h i::::i c::::::c     cccccccC:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c:::::c             C:::::C
 *         T:::::T         h:::::h     h:::::h i::::i c::::::c     ccccccc C:::::C       CCCCCC
 *       TT:::::::TT       h:::::h     h:::::hi::::::ic:::::::cccccc:::::c  C:::::CCCCCCCC::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i c:::::::::::::::::c   CC:::::::::::::::C
 *       T:::::::::T       h:::::h     h:::::hi::::::i  cc:::::::::::::::c     CCC::::::::::::C
 *       TTTTTTTTTTT       hhhhhhh     hhhhhhhiiiiiiii    cccccccccccccccc        CCCCCCCCCCCCC
 *
 * Copyright 2021 - 2022 Ville Rissanen
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 * following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifdef __cplusplus
extern "C"
{
#endif

#include "thicc_character.h"

	MutableCharacter character_empty(void) {
		return '\0';
	}

	MutableSignedCharacter signed_character_empty(void) {
		return (signed char) '\0';
	}

	MutableUnsignedCharacter unsigned_character_empty(void) {
		return (unsigned char) '\0';
	}

	MutableBoolean character_is_empty(Character _character) {
		return _character == character_empty() ? THICC_YES : THICC_NO;
	}

	MutableBoolean signed_character_is_empty(SignedCharacter _signed_character) {
		return _signed_character == signed_character_empty() ? THICC_YES : THICC_NO;
	}

	MutableBoolean unsigned_character_is_empty(UnsignedCharacter _unsigned_character) {
		return _unsigned_character == unsigned_character_empty() ? THICC_YES : THICC_NO;
	}

	MutableCharacterPromotedType character_to_number(Character _character) {
		switch(_character) {
			case '0':
				return (CharacterPromotedType) 0X0;
			case '1':
				return (CharacterPromotedType) 0X1;
			case '2':
				return (CharacterPromotedType) 0X2;
			case '3':
				return (CharacterPromotedType) 0X3;
			case '4':
				return (CharacterPromotedType) 0X4;
			case '5':
				return (CharacterPromotedType) 0X5;
			case '6':
				return (CharacterPromotedType) 0X6;
			case '7':
				return (CharacterPromotedType) 0X7;
			case '8':
				return (CharacterPromotedType) 0X8;
			case '9':
				return (CharacterPromotedType) 0X9;
			case 'A':
			case 'a':
				return (CharacterPromotedType) 0XA;
			case 'B':
			case 'b':
				return (CharacterPromotedType) 0XB;
			case 'C':
			case 'c':
				return (CharacterPromotedType) 0XC;
			case 'D':
			case 'd':
				return (CharacterPromotedType) 0XD;
			case 'E':
			case 'e':
				return (CharacterPromotedType) 0XE;
			case 'F':
			case 'f':
				return (CharacterPromotedType) 0XF;
#if THICC_IF(THICC_CHAR_SIGNED)
			case -'0':
				return (CharacterPromotedType) -0X0;
			case -'1':
				return (CharacterPromotedType) -0X1;
			case -'2':
				return (CharacterPromotedType) -0X2;
			case -'3':
				return (CharacterPromotedType) -0X3;
			case -'4':
				return (CharacterPromotedType) -0X4;
			case -'5':
				return (CharacterPromotedType) -0X5;
			case -'6':
				return (CharacterPromotedType) -0X6;
			case -'7':
				return (CharacterPromotedType) -0X7;
			case -'8':
				return (CharacterPromotedType) -0X8;
			case -'9':
				return (CharacterPromotedType) -0X9;
			case -'A':
			case -'a':
				return (CharacterPromotedType) -0XA;
			case -'B':
			case -'b':
				return (CharacterPromotedType) -0XB;
			case -'C':
			case -'c':
				return (CharacterPromotedType) -0XC;
			case -'D':
			case -'d':
				return (CharacterPromotedType) -0XD;
			case -'E':
			case -'e':
				return (CharacterPromotedType) -0XE;
			case -'F':
			case -'f':
				return (CharacterPromotedType) -0XF;
#endif
			default:
				return (CharacterPromotedType) _character;
		}
	}

	MutableInteger signed_character_to_number(SignedCharacter _signed_character) {
		switch(_signed_character) {
			case '0':
				return 0X0;
			case -'0':
				return -0X0;
			case '1':
				return 0X1;
			case -'1':
				return -0X1;
			case '2':
				return 0X2;
			case -'2':
				return -0X2;
			case '3':
				return 0X3;
			case -'3':
				return -0X3;
			case '4':
				return 0X4;
			case -'4':
				return -0X4;
			case '5':
				return 0X5;
			case -'5':
				return -0X5;
			case '6':
				return 0X6;
			case -'6':
				return -0X6;
			case '7':
				return 0X7;
			case -'7':
				return -0X7;
			case '8':
				return 0X8;
			case -'8':
				return -0X8;
			case '9':
				return 0X9;
			case -'9':
				return -0X9;
			case 'A':
			case 'a':
				return 0XA;
			case -'A':
			case -'a':
				return -0XA;
			case 'B':
			case 'b':
				return 0XB;
			case -'B':
			case -'b':
				return -0XB;
			case 'C':
			case 'c':
				return 0XC;
			case -'C':
			case -'c':
				return -0XC;
			case 'D':
			case 'd':
				return 0XD;
			case -'D':
			case -'d':
				return -0XD;
			case 'E':
			case 'e':
				return 0XE;
			case -'E':
			case -'e':
				return -0XE;
			case 'F':
			case 'f':
				return 0XF;
			case -'F':
			case -'f':
				return -0XF;
			default:
				return (int) _signed_character;
		}
	}

	MutableUnsignedCharacterPromotedType unsigned_character_to_number(UnsignedCharacter _unsigned_character) {
		switch(_unsigned_character) {
			case '0':
				return (UnsignedCharacterPromotedType) 0X0;
			case '1':
				return (UnsignedCharacterPromotedType) 0X1;
			case '2':
				return (UnsignedCharacterPromotedType) 0X2;
			case '3':
				return (UnsignedCharacterPromotedType) 0X3;
			case '4':
				return (UnsignedCharacterPromotedType) 0X4;
			case '5':
				return (UnsignedCharacterPromotedType) 0X5;
			case '6':
				return (UnsignedCharacterPromotedType) 0X6;
			case '7':
				return (UnsignedCharacterPromotedType) 0X7;
			case '8':
				return (UnsignedCharacterPromotedType) 0X8;
			case '9':
				return (UnsignedCharacterPromotedType) 0X9;
			case 'A':
			case 'a':
				return (UnsignedCharacterPromotedType) 0XA;
			case 'B':
			case 'b':
				return (UnsignedCharacterPromotedType) 0XB;
			case 'C':
			case 'c':
				return (UnsignedCharacterPromotedType) 0XC;
			case 'D':
			case 'd':
				return (UnsignedCharacterPromotedType) 0XD;
			case 'E':
			case 'e':
				return (UnsignedCharacterPromotedType) 0XE;
			case 'F':
			case 'f':
				return (UnsignedCharacterPromotedType) 0XF;
			default:
				return (UnsignedCharacterPromotedType) _unsigned_character;
		}
	}

	MutableCharacter character_from_number(CharacterPromotedType _number) {
		switch(_number) {
			case 0x0:
				return '0';
			case 0x1:
				return '1';
			case 0x2:
				return '2';
			case 0x3:
				return '3';
			case 0x4:
				return '4';
			case 0x5:
				return '5';
			case 0x6:
				return '6';
			case 0x7:
				return '7';
			case 0x8:
				return '8';
			case 0x9:
				return '9';
			case 0xA:
				return 'A';
			case 0XB:
				return 'B';
			case 0XC:
				return 'C';
			case 0XD:
				return 'D';
			case 0XE:
				return 'E';
			case 0XF:
				return 'F';
#if THICC_IF(THICC_CHAR_SIGNED)
			case -0x1:
				return -'1';
			case -0x2:
				return -'2';
			case -0x3:
				return -'3';
			case -0x4:
				return -'4';
			case -0x5:
				return -'5';
			case -0x6:
				return -'6';
			case -0x7:
				return -'7';
			case -0x8:
				return -'8';
			case -0x9:
				return -'9';
			case -0xA:
				return -'A';
			case -0XB:
				return -'B';
			case -0XC:
				return -'C';
			case -0XD:
				return -'D';
			case -0XE:
				return -'E';
			case -0XF:
				return -'F';
#endif
			default:
				return (Character) _number;
		}
	}

	MutableSignedCharacter signed_character_from_number(Integer _number) {
		switch(_number) {
			case 0x0:
				return '0';
			case 0x1:
				return '1';
			case 0x2:
				return '2';
			case 0x3:
				return '3';
			case 0x4:
				return '4';
			case 0x5:
				return '5';
			case 0x6:
				return '6';
			case 0x7:
				return '7';
			case 0x8:
				return '8';
			case 0x9:
				return '9';
			case 0xA:
				return 'A';
			case 0XB:
				return 'B';
			case 0XC:
				return 'C';
			case 0XD:
				return 'D';
			case 0XE:
				return 'E';
			case 0XF:
				return 'F';
			case -0x1:
				return -'1';
			case -0x2:
				return -'2';
			case -0x3:
				return -'3';
			case -0x4:
				return -'4';
			case -0x5:
				return -'5';
			case -0x6:
				return -'6';
			case -0x7:
				return -'7';
			case -0x8:
				return -'8';
			case -0x9:
				return -'9';
			case -0xA:
				return -'A';
			case -0XB:
				return -'B';
			case -0XC:
				return -'C';
			case -0XD:
				return -'D';
			case -0XE:
				return -'E';
			case -0XF:
				return -'F';
			default:
				return (SignedCharacter) _number;
		}
	}

	MutableUnsignedCharacter unsigned_character_from_number(UnsignedCharacterPromotedType _number) {
		switch(_number) {
			case 0x0:
				return '0';
			case 0x1:
				return '1';
			case 0x2:
				return '2';
			case 0x3:
				return '3';
			case 0x4:
				return '4';
			case 0x5:
				return '5';
			case 0x6:
				return '6';
			case 0x7:
				return '7';
			case 0x8:
				return '8';
			case 0x9:
				return '9';
			case 0xA:
				return 'A';
			case 0XB:
				return 'B';
			case 0XC:
				return 'C';
			case 0XD:
				return 'D';
			case 0XE:
				return 'E';
			case 0XF:
				return 'F';
			default:
				return (UnsignedCharacter) _number;
		}
	}

#ifdef __cplusplus
}
#endif
