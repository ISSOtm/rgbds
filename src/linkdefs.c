
#include "linkdefs.h"

uint16_t startaddr[] = {
    [SECTTYPE_ROM0] = 0x0000, [SECTTYPE_ROMX] = 0x4000,  [SECTTYPE_VRAM] = 0x8000,
    [SECTTYPE_SRAM] = 0xA000, [SECTTYPE_WRAM0] = 0xC000, [SECTTYPE_WRAMX] = 0xD000,
    [SECTTYPE_OAM] = 0xFE00,  [SECTTYPE_HRAM] = 0xFF80};

uint16_t maxsize[] = {
    [SECTTYPE_ROM0] = 0x8000, [SECTTYPE_ROMX] = 0x4000,  [SECTTYPE_VRAM] = 0x2000,
    [SECTTYPE_SRAM] = 0x2000, [SECTTYPE_WRAM0] = 0x2000, [SECTTYPE_WRAMX] = 0x1000,
    [SECTTYPE_OAM] = 0x00A0,  [SECTTYPE_HRAM] = 0x007F};

uint32_t bankranges[][2] = {[SECTTYPE_ROM0] = {BANK_MIN_ROM0, BANK_MAX_ROM0},
                            [SECTTYPE_ROMX] = {BANK_MIN_ROMX, BANK_MAX_ROMX},
                            [SECTTYPE_VRAM] = {BANK_MIN_VRAM, BANK_MAX_VRAM},
                            [SECTTYPE_SRAM] = {BANK_MIN_SRAM, BANK_MAX_SRAM},
                            [SECTTYPE_WRAM0] = {BANK_MIN_WRAM0, BANK_MAX_WRAM0},
                            [SECTTYPE_WRAMX] = {BANK_MIN_WRAMX, BANK_MAX_WRAMX},
                            [SECTTYPE_OAM] = {BANK_MIN_OAM, BANK_MAX_OAM},
                            [SECTTYPE_HRAM] = {BANK_MIN_HRAM, BANK_MAX_HRAM}};

char const *const typeNames[] = {
    [SECTTYPE_ROM0] = "ROM0", [SECTTYPE_ROMX] = "ROMX",   [SECTTYPE_VRAM] = "VRAM",
    [SECTTYPE_SRAM] = "SRAM", [SECTTYPE_WRAM0] = "WRAM0", [SECTTYPE_WRAMX] = "WRAMX",
    [SECTTYPE_OAM] = "OAM",   [SECTTYPE_HRAM] = "HRAM"};

char const *const sectionModNames[] = {
    [SECTION_NORMAL] = "regular",
    [SECTION_UNION] = "union",
    [SECTION_FRAGMENT] = "fragment",
};
