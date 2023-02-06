#pragma once

#include "stdint.h"

typedef struct
{
    char VbeSignature[4];     // == "VESA"
    uint16_t VbeVersion;      // == 0x0300 for VBE 3.0
    uint16_t OemStringPtr[2]; // isa vbeFarPtr
    uint8_t Capabilities[4];
    uint16_t VideoModePtr[2]; // isa vbeFarPtr
    uint16_t TotalMemory;     // as # of 64KB blocks
} __attribute__((packed)) VbeInfoBlock;

int VBE_GetControllerInfo(VbeInfoBlock *info);
