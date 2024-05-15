#pragma once

#include <types.h>

#include "dt/madt.h"

typedef struct {
    uint8_t signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemId[6];
    uint8_t oemTableId[8];
    uint32_t oemRevision;
    uint32_t creatorId;
    uint32_t creatorRevision;
} __attribute__((packed)) acpi_SDT_t;

typedef struct {
    char signature[8];
    uint8_t checksum;
    char oemId[6];
    uint8_t revision;
    uint32_t rsdtAddr;
} __attribute__((packed)) acpi_RSDP_t;

typedef struct {
    acpi_RSDP_t rsdpDesc; // rsdtAddr deprecated since version 2.0 (xsdp)
    uint32_t length;
    uint64_t xsdtAddr;
    uint8_t extendedCheckum;
    uint8_t reserved[3];
} __attribute__((packed)) acpi_XSDP_t;