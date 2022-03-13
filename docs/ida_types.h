#define MAX_REQLINES 40
#define MAX_LEVELS 24

typedef int16_t PHD_ANGLE;
typedef uint16_t SG_COL;

struct PHD_3DPOS {
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t x_rot;
    int16_t y_rot;
    int16_t z_rot;
};

struct PHD_MATRIX {
    int32_t _00;
    int32_t _01;
    int32_t _02;
    int32_t _03;
    int32_t _10;
    int32_t _11;
    int32_t _12;
    int32_t _13;
    int32_t _20;
    int32_t _21;
    int32_t _22;
    int32_t _23;
};

struct PHD_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
};

struct TEXTSTRING {
    uint32_t flags;
    uint16_t text_flags;
    uint16_t bgnd_flags;
    uint16_t outl_flags;
    int16_t xpos;
    int16_t ypos;
    int16_t zpos;
    int16_t letter_spacing;
    int16_t word_spacing;
    int16_t flash_rate;
    int16_t flash_count;
    int16_t bgnd_colour;
    SG_COL *bgnd_gour;
    int16_t outl_colour;
    SG_COL *outl_gour;
    int16_t bgnd_size_x;
    int16_t bgnd_size_y;
    int16_t bgnd_off_x;
    int16_t bgnd_off_y;
    int16_t bgnd_off_z;
    int32_t scale_h;
    int32_t scale_v;
    int16_t colour;
    char *string;
};

struct REQUEST_INFO {
    uint16_t noselector : 1;
    uint16_t items;
    uint16_t selected;
    uint16_t vis_lines;
    uint16_t line_offset;
    uint16_t line_oldoffset;
    uint16_t pix_width;
    uint16_t line_height;
    int16_t xpos;
    int16_t ypos;
    int16_t zpos;
    int16_t item_text_len;
    char *item_texts1;
    char *item_texts2;
    uint32_t *item_texts1_flags;
    uint32_t *item_texts2_flags;
    uint32_t heading1_flags;
    uint32_t heading2_flags;
    uint32_t background_flags;
    uint32_t moreup_flags;
    uint32_t moredown_flags;
    uint32_t texts1_flags[MAX_REQLINES];
    uint32_t texts2_flags[MAX_REQLINES];
    TEXTSTRING *heading1_text;
    TEXTSTRING *heading2_text;
    TEXTSTRING *background_text;
    TEXTSTRING *moreup_text;
    TEXTSTRING *moredown_text;
    TEXTSTRING *texts1[MAX_REQLINES];
    TEXTSTRING *texts2[MAX_REQLINES];
    char heading1_str[32];
    char heading2_str[32];
    int original_render_width;
    int original_render_height;
};

struct INVENTORY_SPRITE {
    int16_t shape;
    int16_t x;
    int16_t y;
    int16_t z;
    int32_t param1;
    int32_t param2;
    SG_COL *grdptr;
    int16_t sprnum;
};

struct INVENTORY_ITEM {
    char *item_text;
    int16_t object_number;
    int16_t frames_total;
    int16_t current_frame;
    int16_t goal_frame;
    int16_t open_frame;
    int16_t anim_direction;
    int16_t anim_speed;
    int16_t anim_count;
    PHD_ANGLE pt_xrot_sel;
    PHD_ANGLE pt_xrot;
    PHD_ANGLE x_rot_sel;
    PHD_ANGLE x_rot_nosel;
    PHD_ANGLE x_rot;
    PHD_ANGLE y_rot_sel;
    PHD_ANGLE y_rot;
    int32_t ytrans_sel;
    int32_t ytrans;
    int32_t ztrans_sel;
    int32_t ztrans;
    uint32_t which_meshes;
    uint32_t drawn_meshes;
    int16_t inv_pos;
    INVENTORY_SPRITE **sprlist;
    int32_t misc_data[4];
};

