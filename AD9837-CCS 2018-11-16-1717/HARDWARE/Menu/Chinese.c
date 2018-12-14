/*本文件为16×16点阵中文字库文件,字的纵向8点构成一字节,上方的点在字节的低位,字符点阵四角按左上角→右上角→左下角→右下角取字*/
/*如你想在以后继续用HZDotReader打开文件,追加汉字点阵数据,请不要修改或增删所有注释*/

#define hzNum 69

unsigned char hzIndex[138] = {
0xb9,0xa6,0xc4,0xdc,0xb2,0xce,0xca,0xfd,0xb2,0xe2,0xc1,0xbf,0xd3,0xef,0xd1,0xd4,
0xca,0xd4,0xb6,0xc1,0xb3,0xf6,0xbe,0xdd,0xb1,0xb3,0xb9,0xe2,0xbf,0xd8,0xd6,0xc6,
0xb3,0xa7,0xc9,0xe8,0xd6,0xc3,0xd0,0xde,0xb8,0xc4,0xc3,0xdc,0xc2,0xeb,0xe3,0xd0,
0xd6,0xb5,0xcb,0xc0,0xca,0xb1,0xbc,0xe4,0xc1,0xe9,0xc3,0xf4,0xb6,0xc8,0xd6,0xd0,
0xce,0xc4,0xbc,0xec,0xc9,0xcf,0xc0,0xad,0xb5,0xe7,0xd7,0xe8,0xc7,0xe5,0xbf,0xd5,
0xb4,0xed,0xbc,0xc7,0xc2,0xbc,0xd4,0xda,0xcf,0xdf,0xc3,0xfc,0xc1,0xee,0xca,0xe4,
0xc8,0xeb,0xbf,0xda,0xc4,0xa3,0xc4,0xe2,0xd6,0xf7,0xd6,0xe1,0xd0,0xc5,0xba,0xc5,
0xbc,0xcc,0xc6,0xf7,0xd1,0xa1,0xd4,0xf1,0xc8,0xb7,0xc8,0xcf,0xc8,0xa1,0xcf,0xfb,
0xce,0xc2,0xca,0xaa,0xa1,0xe6,0xbf,0xd5,0xc6,0xf8
 };

unsigned char hzdot[2208] = {
/*功   CB9A6 */
0x00,0x04,0x04,0x04,0xFC,0x04,0x14,0x14,0x10,0x90,0x7F,0x10,0x10,0xF0,0x00,0x00,
0x04,0x0C,0x04,0x04,0x03,0x42,0x22,0x11,0x0C,0x23,0x20,0x60,0x20,0x1F,0x00,0x00,

/*能   CC4DC */
0x10,0xB8,0x97,0x92,0x90,0x94,0xB8,0x10,0x00,0x7F,0x48,0x48,0x44,0x74,0x20,0x00,
0x00,0xFF,0x0A,0x0A,0x4A,0x8A,0x7F,0x00,0x00,0x3F,0x44,0x44,0x42,0x72,0x20,0x00,

/*参   CB2CE */
0x20,0x20,0x28,0x2C,0xAA,0x6B,0x38,0xAC,0x24,0x64,0xA6,0x2C,0x20,0x20,0x00,0x00,
0x02,0x42,0x45,0x55,0x52,0x4A,0x29,0x24,0x24,0x12,0x12,0x09,0x0B,0x06,0x02,0x00,

/*数   CCAFD */
0x10,0x92,0x54,0x38,0xFF,0x38,0x54,0x52,0x80,0xF0,0x1F,0x12,0x10,0xF0,0x10,0x00,
0x42,0x42,0x2A,0x2E,0x13,0x1A,0x26,0x02,0x40,0x20,0x13,0x0C,0x33,0x60,0x20,0x00,

/*测   CB2E2 */
0x08,0x31,0x86,0x60,0x00,0xFE,0x02,0xF2,0x02,0xFE,0x00,0xF8,0x00,0x00,0xFF,0x00,
0x04,0xFC,0x03,0x00,0x80,0x47,0x30,0x0F,0x10,0x67,0x00,0x07,0x40,0x80,0x7F,0x00,

/*量   CC1BF */
0x40,0x40,0x40,0xDF,0x55,0x55,0x55,0xD5,0x55,0x55,0x55,0xDF,0x40,0x40,0x40,0x00,
0x40,0x40,0x40,0x57,0x55,0x55,0x55,0x7F,0x55,0x55,0x55,0x57,0x50,0x40,0x40,0x00,

/*语   CD3EF */
0x20,0x21,0xEE,0x04,0x00,0x80,0x92,0x92,0xF2,0x9E,0x92,0x92,0xF2,0x82,0x80,0x00,
0x00,0x00,0x7F,0x20,0x10,0x00,0x00,0x7E,0x22,0x22,0x22,0x22,0x7E,0x00,0x00,0x00,

/*言   CD1D4 */
0x00,0x04,0x04,0xA4,0xA4,0xA4,0xA5,0xA6,0xA4,0xA4,0xA4,0xA4,0x04,0x04,0x04,0x00,
0x00,0x00,0x00,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFC,0x00,0x00,0x00,0x00,

/*试   CCAD4 */
0x40,0x42,0xDC,0x08,0x00,0x90,0x90,0x90,0x90,0x90,0xFF,0x10,0x12,0x1C,0x10,0x00,
0x00,0x00,0x7F,0x20,0x10,0x20,0x20,0x1F,0x10,0x10,0x01,0x06,0x18,0x20,0x78,0x00,

/*读   CB6C1 */
0x40,0x42,0xCC,0x04,0x00,0x50,0x94,0x34,0xD4,0x1F,0xD4,0x14,0x54,0x34,0x10,0x00,
0x00,0x00,0x7F,0x20,0x10,0x82,0x43,0x22,0x12,0x0A,0x07,0x0A,0x12,0xE2,0x42,0x00,

/*出   CB3F6 */
0x00,0x00,0xFC,0x40,0x40,0x40,0x40,0xFF,0x40,0x40,0x40,0x40,0x40,0xFC,0x00,0x00,
0x00,0x00,0x7E,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x7E,0x00,0x00,

/*据   CBEDD */
0x08,0x08,0x08,0xFF,0x88,0x40,0xFE,0x92,0x92,0x92,0xF2,0x92,0x92,0x9E,0x80,0x00,
0x02,0x42,0x81,0x7F,0x40,0x30,0x0F,0xFC,0x44,0x44,0x47,0x44,0x44,0xFC,0x00,0x00,

/*背   CB1B3 */
0x20,0x64,0x24,0x94,0x94,0xBF,0x80,0x80,0x9F,0xA4,0xA4,0xA2,0x22,0x38,0x00,0x00,
0x00,0x00,0x00,0xFF,0x12,0x12,0x12,0x12,0x12,0x52,0x92,0x7F,0x00,0x00,0x00,0x00,

/*光   CB9E2 */
0x00,0x40,0x42,0x44,0x5C,0xC8,0x40,0x7F,0x40,0xC0,0x50,0x4E,0x44,0x60,0x40,0x00,
0x00,0x80,0x40,0x20,0x18,0x07,0x00,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x78,0x00,

/*控   CBFD8 */
0x08,0x08,0x08,0xFF,0x88,0x48,0x00,0x98,0x48,0x28,0x0A,0x2C,0x48,0xD8,0x08,0x00,
0x02,0x42,0x81,0x7F,0x00,0x00,0x40,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x40,0x00,

/*制   CD6C6 */
0x00,0x50,0x4F,0x4A,0x48,0xFF,0x48,0x48,0x48,0x00,0xFC,0x00,0x00,0xFF,0x00,0x00,
0x00,0x00,0x3F,0x01,0x01,0xFF,0x21,0x61,0x3F,0x00,0x0F,0x40,0x80,0x7F,0x00,0x00,

/*厂   CB3A7 */
0x00,0x00,0xFE,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x00,
0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

/*设   CC9E8 */
0x40,0x41,0xCE,0x04,0x00,0x80,0x40,0xBE,0x82,0x82,0x82,0xBE,0xC0,0x40,0x40,0x00,
0x00,0x00,0x7F,0x20,0x90,0x80,0x40,0x43,0x2C,0x10,0x10,0x2C,0x43,0xC0,0x40,0x00,

/*置   CD6C3 */
0x00,0x20,0x2F,0xA9,0xA9,0xAF,0xE9,0xB9,0xA9,0xAF,0xA9,0xA9,0x2F,0x20,0x00,0x00,
0x80,0x80,0x80,0xFF,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xFF,0x80,0x80,0x80,0x00,

/*修   CD0DE */
0x20,0x10,0xFC,0x07,0xF2,0x20,0x98,0x8F,0x54,0xA4,0x24,0x54,0xCC,0x80,0x80,0x00,
0x00,0x00,0x7F,0x00,0x03,0x54,0x54,0x4A,0x2B,0x25,0x15,0x12,0x0A,0x09,0x00,0x00,

/*改   CB8C4 */
0x00,0xC4,0x44,0x44,0x44,0x7C,0x80,0x40,0xF0,0x1F,0x12,0x10,0xF0,0x10,0x10,0x00,
0x00,0x7F,0x20,0x10,0x48,0x44,0x20,0x20,0x10,0x0B,0x0C,0x13,0x20,0x60,0x20,0x00,

/*密   CC3DC */
0x00,0x58,0x24,0x04,0xF4,0x04,0x8D,0xB6,0x44,0x34,0xCC,0x94,0x24,0xCC,0x04,0x00,
0x02,0x06,0x02,0x79,0x41,0x41,0x41,0x7D,0x41,0x41,0x41,0x40,0x78,0x00,0x00,0x00,

/*码   CC2EB */
0x02,0x82,0xE2,0x5E,0x42,0xC2,0x00,0x02,0xFA,0x82,0x82,0x82,0xFE,0x80,0x00,0x00,
0x01,0x00,0x7F,0x10,0x10,0x3F,0x00,0x04,0x04,0x04,0x44,0x84,0x40,0x3F,0x00,0x00,

/*阈   CE3D0 */
0x00,0xF8,0x01,0xD2,0x50,0x50,0xD2,0x12,0xFE,0x16,0x9A,0x12,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x09,0x09,0x05,0x15,0x10,0x09,0x06,0x09,0x5C,0x80,0x7F,0x00,0x00,

/*值   CD6B5 */
0x80,0x40,0xF0,0x2F,0x02,0x04,0xE4,0xA4,0xB4,0xAF,0xA6,0xA4,0xE4,0x04,0x00,0x00,
0x00,0x00,0xFF,0x00,0x40,0x40,0x7F,0x4A,0x4A,0x4A,0x4A,0x4A,0x7F,0x40,0x40,0x00,

/*死   CCBC0 */
0x00,0x02,0xC2,0xB2,0x1E,0x12,0x92,0x72,0x02,0xFE,0x82,0x42,0x42,0x22,0x22,0x00,
0x42,0x41,0x20,0x20,0x13,0x0C,0x03,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x78,0x00,

/*时   CCAB1 */
0x00,0xFC,0x44,0x44,0x44,0xFC,0x10,0x90,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x00,
0x00,0x07,0x04,0x04,0x04,0x07,0x00,0x00,0x03,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,

/*间   CBCE4 */
0x00,0xF8,0x01,0x06,0x00,0xF0,0x92,0x92,0x92,0x92,0xF2,0x02,0x02,0xFE,0x00,0x00,
0x00,0xFF,0x00,0x00,0x00,0x07,0x04,0x04,0x04,0x04,0x07,0x40,0x80,0x7F,0x00,0x00,

/*灵   CC1E9 */
0x00,0x00,0x22,0x2A,0x2A,0x2A,0x2A,0xEA,0xAA,0x2A,0x2A,0xAA,0x7F,0x02,0x00,0x00,
0x00,0x80,0x40,0x44,0x23,0x10,0x0C,0x03,0x04,0x08,0x12,0x21,0x60,0x20,0x00,0x00,

/*敏   CC3F4 */
0x20,0x1C,0xF7,0x34,0x54,0x14,0xF4,0x44,0x30,0xFF,0x12,0x10,0xF0,0x10,0x10,0x00,
0x01,0x01,0x1F,0x13,0x55,0x91,0x7F,0x11,0x90,0x41,0x36,0x0C,0x33,0xC0,0x40,0x00,

/*度   CB6C8 */
0x00,0x00,0xFC,0x04,0x24,0x24,0xFC,0xA5,0xA6,0xA4,0xFC,0x24,0x24,0x24,0x04,0x00,
0x80,0x60,0x1F,0x80,0x80,0x42,0x46,0x2A,0x12,0x12,0x2A,0x26,0x42,0xC0,0x40,0x00,

/*中   CD6D0 */
0x00,0x00,0xFC,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0xFC,0x08,0x00,0x00,
0x00,0x00,0x07,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x07,0x00,0x00,0x00,

/*文   CCEC4 */
0x08,0x08,0x08,0x08,0x78,0x88,0x09,0x0E,0x08,0x88,0x78,0x08,0x08,0x08,0x08,0x00,
0x40,0x40,0x40,0x20,0x20,0x11,0x0A,0x04,0x0A,0x11,0x10,0x20,0x60,0x20,0x20,0x00,

/*检   CBCEC */
0x08,0x88,0x68,0xFF,0x28,0x48,0x10,0x48,0x44,0x43,0x44,0x48,0x50,0x10,0x10,0x00,
0x02,0x01,0x00,0x7F,0x00,0x20,0x22,0x2C,0x21,0x2E,0x30,0x28,0x27,0x22,0x20,0x00,

/*上   CC9CF */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x60,0x40,0x00,

/*拉   CC0AD */
0x10,0x10,0x10,0xFF,0x90,0x50,0x00,0x48,0x89,0x0A,0x0E,0x08,0xE8,0x48,0x08,0x00,
0x02,0x42,0x81,0x7F,0x00,0x20,0x20,0x20,0x21,0x3E,0x20,0x3C,0x23,0x20,0x20,0x00,

/*电   CB5E7 */
0x00,0x00,0xF8,0x48,0x48,0x48,0x48,0xFF,0x48,0x48,0x48,0x48,0xF8,0x00,0x00,0x00,
0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0x3F,0x44,0x44,0x44,0x44,0x4F,0x40,0x70,0x00,

/*阻   CD7E8 */
0x00,0xFF,0x11,0x29,0xC7,0x01,0xFE,0x22,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
0x00,0xFF,0x02,0x04,0x43,0x40,0x7F,0x42,0x42,0x42,0x42,0x42,0x7F,0x40,0x40,0x00,

/*清   CC7E5 */
0x10,0x61,0x06,0xE0,0x18,0x20,0xAA,0xAA,0xAA,0xBF,0xAA,0xAA,0xAA,0x2A,0x00,0x00,
0x04,0x04,0xFF,0x00,0x00,0x00,0xFF,0x0A,0x0A,0x0A,0x4A,0x8A,0x7F,0x00,0x00,0x00,

/*空   CBFD5 */
0x10,0x0C,0x84,0x44,0x24,0x14,0x05,0x06,0x04,0x14,0x24,0x44,0x84,0x14,0x0C,0x00,
0x00,0x40,0x40,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x40,0x40,0x00,0x00,

/*错   CB4ED */
0x40,0x30,0x2C,0xE7,0x24,0x24,0x40,0x48,0x7F,0x48,0x48,0x7F,0x48,0x48,0x40,0x00,
0x01,0x01,0x01,0xFF,0x41,0x21,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,

/*记   CBCC7 */
0x40,0x41,0x4E,0xC4,0x00,0x00,0x00,0xC2,0x42,0x42,0x42,0x42,0x42,0x7E,0x00,0x00,
0x00,0x00,0x00,0x7F,0x20,0x10,0x00,0x3F,0x40,0x40,0x40,0x40,0x40,0x78,0x20,0x00,

/*录   CC2BC */
0x20,0x20,0x22,0xAA,0x2A,0x2A,0x2A,0xEA,0x2A,0x2A,0xAA,0xFE,0x20,0x20,0x20,0x00,
0x00,0x10,0x30,0x10,0x09,0x4A,0x84,0x7F,0x02,0x05,0x08,0x18,0x30,0x10,0x00,0x00,

/*在   CD4DA */
0x00,0x04,0x04,0xC4,0x64,0x9C,0x87,0x84,0x84,0xE4,0x84,0x84,0x84,0x84,0x04,0x00,
0x04,0x02,0x01,0x7F,0x00,0x20,0x20,0x20,0x20,0x3F,0x20,0x20,0x20,0x20,0x20,0x00,

/*线   CCFDF */
0x40,0x60,0x58,0xC7,0x62,0x00,0x90,0x90,0x90,0xFF,0x90,0x92,0x9C,0x94,0x80,0x00,
0x20,0x22,0x23,0x12,0x12,0x12,0x20,0x20,0x10,0x13,0x0C,0x14,0x22,0x40,0xF8,0x00,

/*命   CC3FC */
0x40,0x40,0xA0,0x90,0xA8,0xA4,0xA2,0x21,0xA2,0xA4,0xA8,0x90,0xB0,0x60,0x20,0x00,
0x00,0x00,0x3F,0x08,0x08,0x08,0x1F,0x00,0xFF,0x00,0x10,0x30,0x1F,0x00,0x00,0x00,

/*令   CC1EE */
0x80,0x80,0x40,0x40,0x20,0x10,0x0C,0x23,0x44,0x08,0x10,0xA0,0x60,0xC0,0x40,0x00,
0x00,0x00,0x00,0x01,0x01,0x09,0x11,0x21,0xF1,0x49,0x05,0x03,0x01,0x00,0x00,0x00,

/*输   CCAE4 */
0x44,0xF4,0x4F,0xE4,0x44,0x64,0x90,0x98,0x94,0x93,0x14,0x98,0x08,0xD0,0x10,0x00,
0x04,0x04,0x04,0xFF,0x02,0x02,0xFF,0x4A,0x8A,0x7F,0x00,0x3F,0x80,0xFF,0x00,0x00,

/*入   CC8EB */
0x00,0x00,0x00,0x00,0x01,0x83,0x76,0x18,0x60,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x40,0x20,0x10,0x08,0x06,0x01,0x00,0x00,0x00,0x00,0x03,0x04,0x18,0x30,0x10,0x00,

/*口   CBFDA */
0x00,0x00,0xFC,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0xFC,0x00,0x00,0x00,
0x00,0x00,0x3F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3F,0x00,0x00,0x00,

/*模   CC4A3 */
0x10,0xD0,0xFF,0x50,0x90,0x04,0xF4,0x54,0x5F,0x54,0x54,0x5F,0xF4,0x04,0x00,0x00,
0x03,0x00,0xFF,0x00,0x00,0x84,0x85,0x45,0x35,0x0F,0x15,0x25,0x65,0xC4,0x44,0x00,

/*拟   CC4E2 */
0x10,0x10,0x90,0xFF,0x50,0x10,0xFC,0x00,0x02,0x04,0x0C,0x00,0x00,0xFE,0x00,0x00,
0x01,0x21,0x40,0x3F,0x00,0x00,0x5F,0x48,0x24,0x22,0x10,0x10,0x0C,0x13,0x60,0x00,

/*主   CD6F7 */
0x00,0x00,0x10,0x10,0x10,0x10,0x11,0xF6,0x12,0x10,0x10,0x10,0x98,0x10,0x00,0x00,
0x00,0x20,0x21,0x21,0x21,0x21,0x21,0x3F,0x21,0x21,0x21,0x21,0x21,0x31,0x20,0x00,

/*轴   CD6E1 */
0xC8,0xB8,0x8F,0xEA,0x88,0x88,0x00,0xF0,0x10,0x10,0xFF,0x10,0x10,0xF0,0x00,0x00,
0x08,0x08,0x08,0xFF,0x04,0x04,0x00,0x7F,0x11,0x11,0x1F,0x11,0x11,0x7F,0x00,0x00,

/*信   CD0C5 */
0x80,0x40,0x30,0xFC,0x07,0x0A,0xA8,0xA8,0xA9,0xAE,0xAA,0xA8,0xA8,0x08,0x08,0x00,
0x00,0x00,0x00,0x7F,0x00,0x00,0x7E,0x22,0x22,0x22,0x22,0x22,0x7E,0x00,0x00,0x00,

/*号   CBAC5 */
0x40,0x40,0x40,0x5F,0xD1,0x51,0x51,0x51,0x51,0x51,0x51,0x5F,0x40,0x40,0x40,0x00,
0x00,0x00,0x00,0x02,0x07,0x02,0x02,0x22,0x42,0x82,0x42,0x3E,0x00,0x00,0x00,0x00,

/*继   CBCCC */
0x20,0x38,0xA7,0x62,0x30,0x00,0xFE,0x48,0x50,0xC0,0xFF,0xC0,0x50,0x4C,0x40,0x00,
0x22,0x23,0x22,0x12,0x12,0x00,0x7F,0x48,0x46,0x41,0x5F,0x40,0x41,0x46,0x40,0x00,

/*器   CC6F7 */
0x40,0x40,0x4F,0x49,0x49,0xC9,0xCF,0x70,0xC0,0xCF,0x49,0x59,0x69,0x4F,0x00,0x00,
0x02,0x02,0x7E,0x45,0x45,0x44,0x7C,0x00,0x7C,0x44,0x45,0x45,0x7E,0x06,0x02,0x00,

/*选   CD1A1 */
0x40,0x40,0x42,0xCC,0x00,0x50,0x4E,0xC8,0x48,0x7F,0xC8,0x48,0x48,0x40,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x48,0x46,0x41,0x40,0x40,0x47,0x48,0x48,0x4E,0x40,0x00,

/*择   CD4F1 */
0x08,0x08,0xFF,0x88,0x48,0x08,0x42,0x46,0x2A,0xD2,0x2A,0x46,0x42,0x80,0x80,0x00,
0x42,0x81,0x7F,0x00,0x00,0x08,0x09,0x09,0x09,0xFF,0x09,0x09,0x09,0x08,0x08,0x00,

/*确   CC8B7 */
0x00,0x84,0xE4,0x5C,0x44,0xC4,0x10,0xF8,0x97,0x92,0xF2,0x9A,0x96,0xF2,0x00,0x00,
0x01,0x00,0x3F,0x08,0x88,0x4F,0x30,0x0F,0x04,0x04,0x3F,0x44,0x84,0x7F,0x00,0x00,

/*认   CC8CF */
0x40,0x41,0x42,0xCC,0x04,0x00,0x00,0x00,0x80,0x7F,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x7F,0x20,0x90,0x60,0x18,0x07,0x00,0x03,0x0C,0x30,0xC0,0x40,0x00,

/*取   CC8A1 */
0x02,0x02,0xFE,0x92,0x92,0x92,0xFE,0x02,0x02,0x7C,0x84,0x04,0x84,0x7C,0x04,0x00,
0x10,0x10,0x0F,0x08,0x08,0x04,0xFF,0x04,0x22,0x10,0x09,0x06,0x09,0x30,0x10,0x00,

/*消   CCFFB */
0x08,0x30,0x01,0xC6,0x30,0x00,0xE4,0x38,0x20,0x3F,0x20,0x30,0x28,0xE4,0x00,0x00,
0x04,0x04,0xFF,0x00,0x00,0x00,0xFF,0x09,0x09,0x09,0x09,0x49,0x89,0x7F,0x00,0x00,

/*温   CCEC2 */
0x10,0x60,0x02,0x8C,0x00,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
0x04,0x04,0x7E,0x01,0x40,0x7E,0x42,0x42,0x7E,0x42,0x7E,0x42,0x42,0x7E,0x40,0x00,

/*湿   CCAAA */
0x10,0x60,0x02,0x8C,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
0x04,0x04,0x7E,0x01,0x44,0x48,0x50,0x7F,0x40,0x40,0x7F,0x50,0x48,0x44,0x40,0x00,

/*℃   CA1E6 */
0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,

/*空   CBFD5 */
0x10,0x0C,0x44,0x24,0x14,0x04,0x05,0x06,0x04,0x04,0x14,0x24,0x44,0x14,0x0C,0x00,
0x00,0x40,0x40,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x40,0x40,0x00,0x00,

/*气   CC6F8 */
0x20,0x10,0x4C,0x47,0x54,0x54,0x54,0x54,0x54,0x54,0x54,0xD4,0x04,0x04,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x30,0x40,0xF0,0x00

};

















