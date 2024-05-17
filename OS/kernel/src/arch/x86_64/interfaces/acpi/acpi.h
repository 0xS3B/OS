#pragma once

#include <lib/types.h>

#include "dt/madt.h"

typedef struct {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    char oemId[6];
    char oemTableId[8];
    uint32_t oemRevision;
    uint32_t creatorId;
    uint32_t creatorRevision;
} __attribute__((packed)) acpi_SDTHeader_t;

typedef struct {
    char signature[8];
    uint8_t checksum;
    char oemId[6];
    uint8_t revision;
    uint32_t rsdtAddr;
} __attribute__((packed)) acpi_RSDPHeader_t;

typedef struct {
    acpi_SDTHeader_t header;
    uint32_t sdtEntries[];
}__attribute__((packed)) acpi_RSDT_t;

typedef struct {
    acpi_RSDPHeader_t rsdpDesc; // rsdtAddr deprecated since version 2.0 (xsdp)
    uint32_t length;
    uint64_t xsdtAddr;
    uint8_t extendedCheckum;
    uint8_t reserved[3];
} __attribute__((packed)) acpi_XSDPHeader_t;

typedef struct {
    acpi_SDTHeader_t header;
    uint64_t sdtEntries[];
}__attribute__((packed)) acpi_XSDT_t;


bool acpi_RSDPChecksumValid(acpi_XSDPHeader_t* xsdpDesc);

void* acpi_findTable(acpi_XSDPHeader_t* xsdpDesc, char* signature);