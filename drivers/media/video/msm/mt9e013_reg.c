/* Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */


#include "mt9e013.h"

struct mt9e013_i2c_reg_conf mipi_settings[] = {
	/*Disable embedded data*/
	{0x3064, 0x7800},/*SMIA_TEST*/
	/*configure 2-lane MIPI*/
	{0x31AE, 0x0202},/*SERIAL_FORMAT*/
	{0x31B8, 0x0E3F},/*MIPI_TIMING_2*/
	/*set data to RAW10 format*/
	{0x0112, 0x0A0A},/*CCP_DATA_FORMAT*/
	{0x30F0, 0x8000},/*VCM CONTROL*/
};

/*PLL Configuration
(Ext=24MHz, vt_pix_clk=174MHz, op_pix_clk=69.6MHz)*/
struct mt9e013_i2c_reg_conf pll_settings[] = {
	{0x0300, 0x0004},/*VT_PIX_CLK_DIV*/
	{0x0302, 0x0001},/*VT_SYS_CLK_DIV*/
	{0x0304, 0x0002},/*PRE_PLL_CLK_DIV*/
	{0x0306, 0x003A},/*PLL_MULTIPLIER*/
	{0x0308, 0x000A},/*OP_PIX_CLK_DIV*/
	{0x030A, 0x0001},/*OP_SYS_CLK_DIV*/
};

struct mt9e013_i2c_reg_conf prev_settings[] = {
	/*Output Size (1632x1224)*/
	{0x0344, 0x0008},/*X_ADDR_START*/
	{0x0348, 0x0CC9},/*X_ADDR_END*/
	{0x0346, 0x0008},/*Y_ADDR_START*/
	{0x034A, 0x0999},/*Y_ADDR_END*/
	{0x034C, 0x0660},/*X_OUTPUT_SIZE*/
	{0x034E, 0x04C8},/*Y_OUTPUT_SIZE*/
	{0x306E, 0xFCB0},/*DATAPATH_SELECT*/
	{0x3040, 0x14C3},/*READ_MODE*/
	{0x3178, 0x0000},/*ANALOG_CONTROL5*/
	{0x3ED0, 0x1E24},/*DAC_LD_4_5*/
	{0x0400, 0x0002},/*SCALING_MODE*/
	{0x0404, 0x0010},/*SCALE_M*/
	/*Timing configuration*/
	{0x0342, 0x1018},/*LINE_LENGTH_PCK*/
	{0x0340, 0x055B},/*FRAME_LENGTH_LINES*/
	{0x0202, 0x0557},/*COARSE_INTEGRATION_TIME*/
	{0x3014, 0x0846},/*FINE_INTEGRATION_TIME_*/
	{0x3010, 0x0130},/*FINE_CORRECTION*/
};

struct mt9e013_i2c_reg_conf snap_settings[] = {
	/*Output Size (3264x2448)*/
	{0x0344, 0x0008},/*X_ADDR_START */
	{0x0348, 0x0CD7},/*X_ADDR_END*/
	{0x0346, 0x0008},/*Y_ADDR_START */
	{0x034A, 0x09A7},/*Y_ADDR_END*/
	{0x034C, 0x0CD0},/*X_OUTPUT_SIZE*/
	{0x034E, 0x09A0},/*Y_OUTPUT_SIZE*/
	{0x306E, 0xFC80},/*DATAPATH_SELECT*/
	{0x3040, 0x0041},/*READ_MODE*/
	{0x3178, 0x0000},/*ANALOG_CONTROL5*/
	{0x3ED0, 0x1E24},/*DAC_LD_4_5*/
	{0x0400, 0x0000},/*SCALING_MODE*/
	{0x0404, 0x0010},/*SCALE_M*/
	/*Timing configuration*/
	{0x0342, 0x13F8},/*LINE_LENGTH_PCK*/
	{0x0340, 0x0A2F},/*FRAME_LENGTH_LINES*/
	{0x0202, 0x0A1F},/*COARSE_INTEGRATION_TIME*/
	{0x3014, 0x03F6},/*FINE_INTEGRATION_TIME_ */
	{0x3010, 0x0078},/*FINE_CORRECTION*/
};

struct mt9e013_i2c_reg_conf recommend_settings[] = {
	{0x3044, 0x0590},
	{0x306E, 0xFC80},
	{0x30B2, 0xC000},
	{0x30D6, 0x0800},
	{0x316C, 0xB42F},
	{0x316E, 0x869C},
	{0x3170, 0x210E},
	{0x317A, 0x010E},
	{0x31E0, 0x1FB9},
	{0x31E6, 0x07FC},
	{0x37C0, 0x0000},
	{0x37C2, 0x0000},
	{0x37C4, 0x0000},
	{0x37C6, 0x0000},
	{0x3E02, 0x8801},
	{0x3E04, 0x2301},
	{0x3E06, 0x8449},
	{0x3E08, 0x6841},
	{0x3E0A, 0x400C},
	{0x3E0C, 0x1001},
	{0x3E0E, 0x2103},
	{0x3E10, 0x4B41},
	{0x3E12, 0x4B26},
	{0x3E16, 0x8802},
	{0x3E18, 0x84FF},
	{0x3E1A, 0x8601},
	{0x3E1C, 0x8401},
	{0x3E1E, 0x840A},
	{0x3E20, 0xFF00},
	{0x3E22, 0x8401},
	{0x3E24, 0x00FF},
	{0x3E26, 0x0088},
	{0x3E28, 0x2E8A},
	{0x3E32, 0x8801},
	{0x3E34, 0x4024},
	{0x3E38, 0x8469},
	{0x3E3C, 0x2301},
	{0x3E3E, 0x3E25},
	{0x3E40, 0x1C01},
	{0x3E42, 0x8486},
	{0x3E44, 0x8401},
	{0x3E46, 0x00FF},
	{0x3E48, 0x8401},
	{0x3E4A, 0x8601},
	{0x3E4C, 0x8402},
	{0x3E4E, 0x00FF},
	{0x3E50, 0x6623},
	{0x3E52, 0x8340},
	{0x3E54, 0x00FF},
	{0x3E56, 0x4A42},
	{0x3E58, 0x2203},
	{0x3E5A, 0x674D},
	{0x3E5C, 0x3F25},
	{0x3E5E, 0x846A},
	{0x3E60, 0x4C01},
	{0x3E62, 0x8401},
	{0x3E66, 0x3901},
	{0x3ECC, 0x00EB},
	{0x3ED0, 0x1E24},
	{0x3ED4, 0xAFC4},
	{0x3ED6, 0x909B},
	{0x3ED8, 0x0006},
	{0x3EDA, 0xCFC6},
	{0x3EDC, 0x4FE4},
	{0x3EE0, 0x2424},
	{0x3EE2, 0x9797},
	{0x3EE4, 0xC100},
	{0x3EE6, 0x0540}
};

#if defined(CONFIG_MACH_ACER_A5)
struct mt9e013_default_rolloff default_rolloff[] = {
	{0x0210, 0x01B0, 0x0310},
	{0x5E4D, 0x584D, 0x102E},
	{0x65B0, 0x6290, 0x7110},
	{0xAACC, 0xB56B, 0xAB2C},
	{0xEF6F, 0xF64F, 0x8950},
	{0x03F0, 0x03F0, 0x03B0},
	{0xBE0E, 0x920E, 0x8B4E},
	{0x1111, 0x1AB0, 0x3A10},
	{0x074F, 0x52CE, 0x530E},
	{0xAB30, 0x8FAF, 0xBACF},
	{0x05F0, 0x0570, 0x0450},
	{0x174E, 0x258E, 0x430E},
	{0x0B4F, 0x340F, 0x2F70},
	{0xE34E, 0xCA6E, 0xFAAD},
	{0x676B, 0x87ED, 0xCDEF},
	{0x0530, 0x03D0, 0x0350},
	{0xC44E, 0xC36E, 0xA08E},
	{0x0531, 0x6E30, 0x5FD0},
	{0x604E, 0x5DAE, 0x41AE},
	{0xA710, 0x90B0, 0x8990},
	{0xE44D, 0xDF6C, 0xC8CC},
	{0xA8CE, 0xA22E, 0xB44E},
	{0xDAEE, 0xDF4F, 0xE24F},
	{0x7D2D, 0x434D, 0x7A2D},
	{0x47CF, 0x3850, 0x3790},
	{0xB8CD, 0x89CC, 0xCAEA},
	{0x71AD, 0x516D, 0x4A4D},
	{0x88EE, 0xD54E, 0x8B2F},
	{0xE66E, 0xDE2E, 0xD58E},
	{0x2BCF, 0x6BCF, 0x0650},
	{0xB8A8, 0x79CC, 0x45CD},
	{0x4D8D, 0x26AE, 0x4F6E},
	{0x030D, 0xB56C, 0xACAD},
	{0x8E8E, 0xE2CE, 0x856F},
	{0xA1AC, 0x544D, 0x224E},
	{0x0ECC, 0x4B2D, 0x55CD},
	{0xC88E, 0xB98E, 0xBCCE},
	{0x614D, 0xBB6D, 0x980D},
	{0x49CE, 0x1FCE, 0x35AE},
	{0x83AE, 0x246E, 0x7A4D},
	{0x3011, 0x2311, 0x2331},
	{0x7ECF, 0x7DAF, 0x45EF},
	{0x87D3, 0x85D3, 0x8BF3},
	{0xFA90, 0x8A91, 0xC4D0},
	{0x3B33, 0x3E73, 0x44F3},
	{0x4F71, 0x0E11, 0x21B1},
	{0x53CE, 0x392D, 0x186C},
	{0x9273, 0xC632, 0xDE32},
	{0xDF70, 0xA190, 0xF0EF},
	{0x4793, 0x1433, 0x1E93},
	{0x0391, 0x7D50, 0x1771},
	{0x3C4F, 0x45CF, 0x458F},
	{0xBD12, 0xB412, 0xFBF2},
	{0x9BB0, 0xAFF0, 0xADD0},
	{0x1093, 0x0953, 0x36B3},
	{0x2291, 0x1A31, 0x1B31},
	{0x1F8F, 0x116F, 0x4B6E},
	{0x8E93, 0x85D3, 0x8393},
	{0x8D51, 0x81F1, 0xC950},
	{0x4C33, 0x4233, 0x3DD3},
	{0x964D, 0xE14E, 0xD74E},
	{0x230E, 0x6AED, 0x1D6E},
	{0x6910, 0x59F1, 0x5311},
	{0x970E, 0x9D4C, 0x8B8E},
	{0xEFF1, 0x9F32, 0x9692},
	{0x2C6D, 0x94E9, 0xC0EC},
	{0xB18E, 0x8BAE, 0x8DAE},
	{0x3FAF, 0x3790, 0x57B0},
	{0x3250, 0x6DCF, 0x770F},
	{0xB411, 0xA5B1, 0xB831},
	{0x99CE, 0x810F, 0xE2CE},
	{0xDD2E, 0xCE2F, 0xFBAF},
	{0x61EE, 0x738F, 0x300F},
	{0x4F6F, 0x2910, 0x62F0},
	{0xACCE, 0x304D, 0x3F6F},
	{0xC08D, 0xEA2E, 0xD5AE},
	{0x25CF, 0x18AF, 0x23AF},
	{0xCE0E, 0x52AF, 0x0BAF},
	{0xA230, 0xA410, 0xB450},
	{0x2790, 0x244F, 0x1C10},
	{0xD031, 0xC531, 0xCF91},
	{0x8731, 0x8BD1, 0xED90},
	{0x5EF3, 0x6693, 0x7073},
	{0x5A71, 0x04D2, 0x7431},
	{0xB7F2, 0xF392, 0xFD32},
	{0xCF71, 0x99B1, 0xAD71},
	{0xA24E, 0xA46D, 0x27EC},
	{0x5F13, 0x3CD3, 0x43F3},
	{0xEDB0, 0x9190, 0xBDD0},
	{0xE791, 0xAD32, 0x9832},
	{0xB591, 0xAA11, 0xBFB1},
	{0xF910, 0x9271, 0x96F1},
	{0x4573, 0x2A33, 0x41D3},
	{0x3651, 0x5DF1, 0x7C31},
	{0xED92, 0x9652, 0x9E72},
	{0xBBB1, 0xB5D1, 0xB531},
	{0xA4CE, 0xEA6D, 0x620C},
	{0x4FF3, 0x4ED3, 0x42D3},
	{0xCF4F, 0xFB8F, 0xAA30},
	{0x88F2, 0xA192, 0xFA91},
	{0x05FC, 0x05FC, 0x0614},
	{0x0530, 0x0560, 0x0560},
	{0xB489, 0xF7A9, 0x8729},
	{0x86EA, 0x84A8, 0x8000},
	{0x1CE9, 0x1F08, 0xAA87},
	{0xE628, 0xEE07, 0x8CA8},
	{0x03DB, 0x02DA, 0x028B}, //R/G(H)
	{0x0400, 0x0400, 0x0400}, //G/G(H)
	{0x0376, 0x0221, 0x0345}, //B/G(H)
};
#endif

struct mt9e013_reg mt9e013_regs = {
	.reg_mipi = &mipi_settings[0],
	.reg_mipi_size = ARRAY_SIZE(mipi_settings),
	.rec_settings = &recommend_settings[0],
	.rec_size = ARRAY_SIZE(recommend_settings),
	.reg_pll = &pll_settings[0],
	.reg_pll_size = ARRAY_SIZE(pll_settings),
	.reg_prev = &prev_settings[0],
	.reg_prev_size = ARRAY_SIZE(prev_settings),
	.reg_snap = &snap_settings[0],
	.reg_snap_size = ARRAY_SIZE(snap_settings),
#if defined(CONFIG_MACH_ACER_A5)
	.reg_default_rolloff = &default_rolloff[0],
	.reg_default_rolloff_size = ARRAY_SIZE(default_rolloff),
#endif
};