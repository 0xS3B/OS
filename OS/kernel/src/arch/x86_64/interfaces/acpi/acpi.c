#include "acpi.h"

#include <lib/string.h>

#include <log/log.h>

#define MODULE_NAME "acpi"

bool isXSDP = false;

bool acpi_RSDPChecksumValid(acpi_XSDPHeader_t* xsdpDesc) {
    uint8_t checksum = xsdpDesc->rsdpDesc.checksum;

    if(xsdpDesc->rsdpDesc.revision >= 1) {
        for(size_t i = 0; i < sizeof(acpi_XSDPHeader_t); i++) {
            checksum += ((uint8_t*) xsdpDesc)[i];
        }
        
        return (checksum & 0xFF) == xsdpDesc->rsdpDesc.checksum;
    } else {
        for(size_t i = 0; i < sizeof(acpi_RSDPHeader_t); i++) {
            checksum += ((uint8_t*) &(xsdpDesc->rsdpDesc))[i];
        }

        return (checksum & 0xFF) == xsdpDesc->rsdpDesc.checksum;
    }

    return NULL;
}

void* acpi_findTable(acpi_XSDPHeader_t* xsdpDesc, char* signature) {
    acpi_SDTHeader_t* sdt = NULL;
    uint64_t entries = 0;

    if(isXSDP) {
        sdt = (acpi_SDTHeader_t*) xsdpDesc->xsdtAddr;
        entries = (sdt->length - sizeof(acpi_SDTHeader_t)) / sizeof(uint64_t);
    } else {
        sdt = (acpi_SDTHeader_t*)(uintptr_t) xsdpDesc->rsdpDesc.rsdtAddr;
        entries = (sdt->length - sizeof(acpi_SDTHeader_t)) / sizeof(uint32_t);
    }

    acpi_SDTHeader_t* header = NULL;

    for(uint64_t i = 0; i < entries; i++) {
        if(isXSDP) {
            header = (acpi_SDTHeader_t*)((uint64_t)((acpi_XSDT_t*) sdt)->sdtEntries[i]);
        } else {
            header = (acpi_SDTHeader_t*)((uint64_t)((uint32_t)((acpi_RSDT_t*) sdt)->sdtEntries[i]));
        }

        if(!strncmp((char*) header->signature, signature, 4)){
            return header;
        }
    }

    return NULL;
}