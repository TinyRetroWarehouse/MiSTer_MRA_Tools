#ifndef _MRA_H_
#define _MRA_H_

#include <stdint.h>
#include "utils.h"
#include "globals.h"
#include "utils.h"
#include "sxmlc.h"

#pragma pack(1)

typedef struct s_part {
    int is_group;
    union {
        struct s_p {
            char *name;
            char *zip;
            uint32_t crc32;
            uint32_t repeat;
            uint32_t offset;
            uint32_t length;
            uint8_t *pattern;
            uint8_t *data;
            size_t data_length;
        } p;
        struct s_g {
            int is_interleaved;
            int width;
            int repeat;
            struct s_part *parts;
            int n_parts;
        } g;
    };
} t_part;

typedef struct s_patch
{
    uint32_t offset;
    uint8_t *data;
    size_t data_length;
} t_patch;

typedef struct s_rom {
    int index;
    char *md5;
    t_string_list type;
    t_string_list zip;
    t_part *parts;
    int n_parts;
    t_patch *patches;
    int n_patches;
} t_rom;

typedef struct s_dip_switch
{
    char *bits;
    char *name;
    char *ids;
} t_dip_switch;

typedef struct s_mra {
    XMLDoc _xml_doc;

    char *name;
    char *mratimestamp;
    char *mameversion;
    char *setname;
    char *year;
    char *manufacturer;
    char *rbf;

    t_string_list categories;
    
    t_dip_switch *switches;
    int n_switches;
    int switches_default, switches_base;
    
    t_rom *roms;
    int n_roms;
} t_mra;

int mra_load(char *filename, t_mra *mra);
int mra_dump(t_mra *mra);
int mra_get_next_rom0(t_mra *mra, int start_index);
int mra_get_rom_by_index(t_mra *mra, int index, int start_pos);

#endif