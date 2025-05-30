#include "CTwofish.h"

#include "UMemory.h"

static constexpr uint8_t Q[2][256] = {
    {0xd8, 0x00, 0x01, 0x17, 0x02, 0x2e, 0x18, 0x53, 0x03, 0x6a, 0x2f, 0x93, 0x19, 0x34, 0x54,
     0x45, 0x04, 0x5c, 0x6b, 0xb6, 0x30, 0xa6, 0x94, 0x4b, 0x1a, 0x8c, 0x35, 0x81, 0x55, 0xaa,
     0x46, 0x0d, 0x05, 0x24, 0x5d, 0x87, 0x6c, 0x9b, 0xb7, 0xc1, 0x31, 0x2b, 0xa7, 0xa3, 0x95,
     0x98, 0x4c, 0xca, 0x1b, 0xe6, 0x8d, 0x73, 0x36, 0xcd, 0x82, 0x12, 0x56, 0x62, 0xab, 0xf0,
     0x47, 0x4f, 0x0e, 0xbd, 0x06, 0xd4, 0x25, 0xd2, 0x5e, 0x27, 0x88, 0x66, 0x6d, 0xd6, 0x9c,
     0x79, 0xb8, 0x08, 0xc2, 0xdf, 0x32, 0x68, 0x2c, 0xfd, 0xa8, 0x8a, 0xa4, 0x5a, 0x96, 0x29,
     0x99, 0x22, 0x4d, 0x60, 0xcb, 0xe4, 0x1c, 0x7b, 0xe7, 0x3b, 0x8e, 0x9e, 0x74, 0xf4, 0x37,
     0xd8, 0xce, 0xf9, 0x83, 0x6f, 0x13, 0xb2, 0x57, 0xe1, 0x63, 0xdc, 0xac, 0xc4, 0xf1, 0xaf,
     0x48, 0x0a, 0x50, 0x42, 0x0f, 0xba, 0xbe, 0xc7, 0x07, 0xde, 0xd5, 0x78, 0x26, 0x65, 0xd3,
     0xd1, 0x5f, 0xe3, 0x28, 0x21, 0x89, 0x59, 0x67, 0xfc, 0x6e, 0xb1, 0xd7, 0xf8, 0x9d, 0xf3,
     0x7a, 0x3a, 0xb9, 0xc6, 0x09, 0x41, 0xc3, 0xae, 0xe0, 0xdb, 0x33, 0x44, 0x69, 0x92, 0x2d,
     0x52, 0xfe, 0x16, 0xa9, 0x0c, 0x8b, 0x80, 0xa5, 0x4a, 0x5b, 0xb5, 0x97, 0xc9, 0x2a, 0xa2,
     0x9a, 0xc0, 0x23, 0x86, 0x4e, 0xbc, 0x61, 0xef, 0xcc, 0x11, 0xe5, 0x72, 0x1d, 0x3d, 0x7c,
     0xeb, 0xe8, 0xe9, 0x3c, 0xea, 0x8f, 0x7d, 0x9f, 0xec, 0x75, 0x1e, 0xf5, 0x3e, 0x38, 0xf6,
     0xd9, 0x3f, 0xcf, 0x76, 0xfa, 0x1f, 0x84, 0xa0, 0x70, 0xed, 0x14, 0x90, 0xb3, 0x7e, 0x58,
     0xfb, 0xe2, 0x20, 0x64, 0xd0, 0xdd, 0x77, 0xad, 0xda, 0xc5, 0x40, 0xf2, 0x39, 0xb0, 0xf7,
     0x49, 0xb4, 0x0b, 0x7f, 0x51, 0x15, 0x43, 0x91, 0x10, 0x71, 0xbb, 0xee, 0xbf, 0x85, 0xc8,
     0xa1},
    {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x4d, 0x9a, 0x79, 0xf2, 0xa9, 0x1f, 0x3e,
     0x7c, 0xf8, 0xbd, 0x37, 0x6e, 0xdc, 0xf5, 0xa7, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0,
     0xcd, 0xd7, 0xe3, 0x8b, 0x5b, 0xb6, 0x21, 0x42, 0x84, 0x45, 0x8a, 0x59, 0xb2, 0x29, 0x52,
     0xa4, 0x05, 0x0a, 0x14, 0x28, 0x50, 0xa0, 0x0d, 0x1a, 0x34, 0x68, 0xd0, 0xed, 0x97, 0x63,
     0xc6, 0xc1, 0xcf, 0xd3, 0xeb, 0x9b, 0x7b, 0xf6, 0xa1, 0x0f, 0x1e, 0x3c, 0x78, 0xf0, 0xad,
     0x17, 0x2e, 0x5c, 0xb8, 0x3d, 0x7a, 0xf4, 0xa5, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0x8d,
     0x57, 0xae, 0x11, 0x22, 0x44, 0x88, 0x5d, 0xba, 0x39, 0x72, 0xe4, 0x85, 0x47, 0x8e, 0x51,
     0xa2, 0x09, 0x12, 0x24, 0x48, 0x90, 0x6d, 0xda, 0xf9, 0xbf, 0x33, 0x66, 0xcc, 0xd5, 0xe7,
     0x83, 0x4b, 0x96, 0x61, 0xc2, 0xc9, 0xdf, 0xf3, 0xab, 0x1b, 0x36, 0x6c, 0xd8, 0xfd, 0xb7,
     0x23, 0x46, 0x8c, 0x55, 0xaa, 0x19, 0x32, 0x64, 0xc8, 0xdd, 0xf7, 0xa3, 0x0b, 0x16, 0x2c,
     0x58, 0xb0, 0x2d, 0x5a, 0xb4, 0x25, 0x4a, 0x94, 0x65, 0xca, 0xd9, 0xff, 0xb3, 0x2b, 0x56,
     0xac, 0x15, 0x2a, 0x54, 0xa8, 0x1d, 0x3a, 0x74, 0xe8, 0x9d, 0x77, 0xee, 0x91, 0x6f, 0xde,
     0xf1, 0xaf, 0x13, 0x26, 0x4c, 0x98, 0x7d, 0xfa, 0xb9, 0x3f, 0x7e, 0xfc, 0xb5, 0x27, 0x4e,
     0x9c, 0x75, 0xea, 0x99, 0x7f, 0xfe, 0xb1, 0x2f, 0x5e, 0xbc, 0x35, 0x6a, 0xd4, 0xe5, 0x87,
     0x43, 0x86, 0x41, 0x82, 0x49, 0x92, 0x69, 0xd2, 0xe9, 0x9f, 0x73, 0xe6, 0x81, 0x4f, 0x9e,
     0x71, 0xe2, 0x89, 0x5f, 0xbe, 0x31, 0x62, 0xc4, 0xc5, 0xc7, 0xc3, 0xcb, 0xdb, 0xfb, 0xbb,
     0x3b, 0x76, 0xec, 0x95, 0x67, 0xce, 0xd1, 0xef, 0x93, 0x6b, 0xd6, 0xe1, 0x8f, 0x53, 0xa6,
     0x01},
};

static constexpr uint8_t MDS[2][256] = {
    {0xa9, 0x67, 0xb3, 0xe8, 0x04, 0xfd, 0xa3, 0x76, 0x9a, 0x92, 0x80, 0x78, 0xe4, 0xdd, 0xd1,
     0x38, 0x0d, 0xc6, 0x35, 0x98, 0x18, 0xf7, 0xec, 0x6c, 0x43, 0x75, 0x37, 0x26, 0xfa, 0x13,
     0x94, 0x48, 0xf2, 0xd0, 0x8b, 0x30, 0x84, 0x54, 0xdf, 0x23, 0x19, 0x5b, 0x3d, 0x59, 0xf3,
     0xae, 0xa2, 0x82, 0x63, 0x01, 0x83, 0x2e, 0xd9, 0x51, 0x9b, 0x7c, 0xa6, 0xeb, 0xa5, 0xbe,
     0x16, 0x0c, 0xe3, 0x61, 0xc0, 0x8c, 0x3a, 0xf5, 0x73, 0x2c, 0x25, 0x0b, 0xbb, 0x4e, 0x89,
     0x6b, 0x53, 0x6a, 0xb4, 0xf1, 0xe1, 0xe6, 0xbd, 0x45, 0xe2, 0xf4, 0xb6, 0x66, 0xcc, 0x95,
     0x03, 0x56, 0xd4, 0x1c, 0x1e, 0xd7, 0xfb, 0xc3, 0x8e, 0xb5, 0xe9, 0xcf, 0xbf, 0xba, 0xea,
     0x77, 0x39, 0xaf, 0x33, 0xc9, 0x62, 0x71, 0x81, 0x79, 0x09, 0xad, 0x24, 0xcd, 0xf9, 0xd8,
     0xe5, 0xc5, 0xb9, 0x4d, 0x44, 0x08, 0x86, 0xe7, 0xa1, 0x1d, 0xaa, 0xed, 0x06, 0x70, 0xb2,
     0xd2, 0x41, 0x7b, 0xa0, 0x11, 0x31, 0xc2, 0x27, 0x90, 0x20, 0xf6, 0x60, 0xff, 0x96, 0x5c,
     0xb1, 0xab, 0x9e, 0x9c, 0x52, 0x1b, 0x5f, 0x93, 0x0a, 0xef, 0x91, 0x85, 0x49, 0xee, 0x2d,
     0x4f, 0x8f, 0x3b, 0x47, 0x87, 0x6d, 0x46, 0xd6, 0x3e, 0x69, 0x64, 0x2a, 0xce, 0xcb, 0x2f,
     0xfc, 0x97, 0x05, 0x7a, 0xac, 0x7f, 0xd5, 0x1a, 0x4b, 0x0e, 0xa7, 0x5a, 0x28, 0x14, 0x3f,
     0x29, 0x88, 0x3c, 0x4c, 0x02, 0xb8, 0xda, 0xb0, 0x17, 0x55, 0x1f, 0x8a, 0x7d, 0x57, 0xc7,
     0x8d, 0x74, 0xb7, 0xc4, 0x9f, 0x72, 0x7e, 0x15, 0x22, 0x12, 0x58, 0x07, 0x99, 0x34, 0x6e,
     0x50, 0xde, 0x68, 0x65, 0xbc, 0xdb, 0xf8, 0xc8, 0xa8, 0x2b, 0x40, 0xdc, 0xfe, 0x32, 0xa4,
     0xca, 0x10, 0x21, 0xf0, 0xd3, 0x5d, 0x0f, 0x00, 0x6f, 0x9d, 0x36, 0x42, 0x4a, 0x5e, 0xc1,
     0xe0},
    {0x75, 0xf3, 0xc6, 0xf4, 0xdb, 0x7b, 0xfb, 0xc8, 0x4a, 0xd3, 0xe6, 0x6b, 0x45, 0x7d, 0xe8,
     0x4b, 0xd6, 0x32, 0xd8, 0xfd, 0x37, 0x71, 0xf1, 0xe1, 0x30, 0x0f, 0xf8, 0x1b, 0x87, 0xfa,
     0x06, 0x3f, 0x5e, 0xba, 0xae, 0x5b, 0x8a, 0x00, 0xbc, 0x9d, 0x6d, 0xc1, 0xb1, 0x0e, 0x80,
     0x5d, 0xd2, 0xd5, 0xa0, 0x84, 0x07, 0x14, 0xb5, 0x90, 0x2c, 0xa3, 0xb2, 0x73, 0x4c, 0x54,
     0x92, 0x74, 0x36, 0x51, 0x38, 0xb0, 0xbd, 0x5a, 0xfc, 0x60, 0x62, 0x96, 0x6c, 0x42, 0xf7,
     0x10, 0x7c, 0x28, 0x27, 0x8c, 0x13, 0x95, 0x9c, 0xc7, 0x24, 0x46, 0x3b, 0x70, 0xca, 0xe3,
     0x85, 0xcb, 0x11, 0xd0, 0x93, 0xb8, 0xa6, 0x83, 0x20, 0xff, 0x9f, 0x77, 0xc3, 0xcc, 0x03,
     0x6f, 0x08, 0xbf, 0x40, 0xe7, 0x2b, 0xe2, 0x79, 0x0c, 0xaa, 0x82, 0x41, 0x3a, 0xea, 0xb9,
     0xe4, 0x9a, 0xa4, 0x97, 0x7e, 0xda, 0x7a, 0x17, 0x66, 0x94, 0xa1, 0x1d, 0x3d, 0xf0, 0xde,
     0xb3, 0x0b, 0x72, 0xa7, 0x1c, 0xef, 0xd1, 0x53, 0x3e, 0x8f, 0x33, 0x26, 0x5f, 0xec, 0x76,
     0x2a, 0x49, 0x81, 0x88, 0xee, 0x21, 0xc4, 0x1a, 0xeb, 0xd9, 0xc5, 0x39, 0x99, 0xcd, 0xad,
     0x31, 0x8b, 0x01, 0x18, 0x23, 0xdd, 0x1f, 0x4e, 0x2d, 0xf9, 0x48, 0x4f, 0xf2, 0x65, 0x8e,
     0x78, 0x5c, 0x58, 0x19, 0x8d, 0xe5, 0x98, 0x57, 0x67, 0x7f, 0x05, 0x64, 0xaf, 0x63, 0xb6,
     0xfe, 0xf5, 0xb7, 0x3c, 0xa5, 0xce, 0xe9, 0x68, 0x44, 0xe0, 0x4d, 0x43, 0x69, 0x29, 0x2e,
     0xac, 0x15, 0x59, 0xa8, 0x0a, 0x9e, 0x6e, 0x47, 0xdf, 0x34, 0x35, 0x6a, 0xcf, 0xdc, 0x22,
     0xc9, 0xc0, 0x9b, 0x89, 0xd4, 0xed, 0xab, 0x12, 0xa2, 0x0d, 0x52, 0xbb, 0x02, 0x2f, 0xa9,
     0xd7, 0x61, 0x1e, 0xb4, 0x50, 0x04, 0xf6, 0xc2, 0x16, 0x25, 0x86, 0x56, 0x55, 0x09, 0xbe,
     0x91},
};

static constexpr uint8_t MDS_GF[4][256] = {
    {0x75, 0x32, 0xbc, 0xbc, 0xf3, 0x21, 0xec, 0xec, 0xc6, 0x43, 0x20, 0x20, 0xf4, 0xc9, 0xb3,
     0xb3, 0xdb, 0x03, 0xda, 0xda, 0x7b, 0x8b, 0x02, 0x02, 0xfb, 0x2b, 0xe2, 0xe2, 0xc8, 0xfa,
     0x9e, 0x9e, 0x4a, 0xec, 0xc9, 0xc9, 0xd3, 0x09, 0xd4, 0xd4, 0xe6, 0x6b, 0x18, 0x18, 0x6b,
     0x9f, 0x1e, 0x1e, 0x45, 0x0e, 0x98, 0x98, 0x7d, 0x38, 0xb2, 0xb2, 0xe8, 0xd2, 0xa6, 0xa6,
     0x4b, 0xb7, 0x26, 0x26, 0xd6, 0x57, 0x3c, 0x3c, 0x32, 0x8a, 0x93, 0x93, 0xd8, 0xee, 0x82,
     0x82, 0xfd, 0x98, 0x52, 0x52, 0x37, 0xd4, 0x7b, 0x7b, 0x71, 0x37, 0xbb, 0xbb, 0xf1, 0x97,
     0x5b, 0x5b, 0xe1, 0x83, 0x47, 0x47, 0x30, 0x3c, 0x24, 0x24, 0x0f, 0xe2, 0x51, 0x51, 0xf8,
     0xc6, 0xba, 0xba, 0x1b, 0xf3, 0x4a, 0x4a, 0x87, 0x48, 0xbf, 0xbf, 0xfa, 0x70, 0x0d, 0x0d,
     0x06, 0xb3, 0xb0, 0xb0, 0x3f, 0xde, 0x75, 0x75, 0x5e, 0xfd, 0xd2, 0xd2, 0xba, 0x20, 0x7d,
     0x7d, 0xae, 0x31, 0x66, 0x66, 0x5b, 0xa3, 0x3a, 0x3a, 0x8a, 0x1c, 0x59, 0x59, 0x00, 0x00,
     0x00, 0x00, 0xbc, 0x93, 0xcd, 0xcd, 0x9d, 0xe0, 0x1a, 0x1a, 0x6d, 0x2c, 0xae, 0xae, 0xc1,
     0xab, 0x7f, 0x7f, 0xb1, 0xc7, 0x2b, 0x2b, 0x0e, 0xb9, 0xbe, 0xbe, 0x80, 0xa0, 0xe0, 0xe0,
     0x5d, 0x10, 0x8a, 0x8a, 0xd2, 0x52, 0x3b, 0x3b, 0xd5, 0xba, 0x64, 0x64, 0xa0, 0x88, 0xd8,
     0xd8, 0x84, 0xa5, 0xe7, 0xe7, 0x07, 0xe8, 0x5f, 0x5f, 0x14, 0x11, 0x1b, 0x1b, 0xb5, 0xc2,
     0x2c, 0x2c, 0x90, 0xb4, 0xfc, 0xfc, 0x2c, 0x27, 0x31, 0x31, 0xa3, 0x65, 0x80, 0x80, 0xb2,
     0x2a, 0x73, 0x73, 0x73, 0x81, 0x0c, 0x0c, 0x4c, 0x5f, 0x79, 0x79, 0x54, 0x41, 0x6b, 0x6b,
     0x92, 0x02, 0x4b, 0x4b, 0x74, 0x69, 0x53, 0x53, 0x36, 0x8f, 0x94, 0x94, 0x51, 0x1f, 0x83,
     0x83},
    {0x39, 0x39, 0xd9, 0xa9, 0x17, 0x17, 0x90, 0x67, 0x9c, 0x9c, 0x71, 0xb3, 0xa6, 0xa6, 0xd2,
     0xe8, 0x07, 0x07, 0x05, 0x04, 0x52, 0x52, 0x98, 0xfd, 0x80, 0x80, 0x65, 0xa3, 0xe4, 0xe4,
     0xdf, 0x76, 0x45, 0x45, 0x08, 0x9a, 0x4b, 0x4b, 0x02, 0x92, 0xe0, 0xe0, 0xa0, 0x80, 0x5a,
     0x5a, 0x66, 0x78, 0xaf, 0xaf, 0xdd, 0xe4, 0x6a, 0x6a, 0xb0, 0xdd, 0x63, 0x63, 0xbf, 0xd1,
     0x2a, 0x2a, 0x36, 0x38, 0xe6, 0xe6, 0x54, 0x0d, 0x20, 0x20, 0x43, 0xc6, 0xcc, 0xcc, 0x62,
     0x35, 0xf2, 0xf2, 0xbe, 0x98, 0x12, 0x12, 0x1e, 0x18, 0xeb, 0xeb, 0x24, 0xf7, 0xa1, 0xa1,
     0xd7, 0xec, 0x41, 0x41, 0x77, 0x6c, 0x28, 0x28, 0xbd, 0x43, 0xbc, 0xbc, 0x32, 0x75, 0x7b,
     0x7b, 0xd4, 0x37, 0x88, 0x88, 0x9b, 0x26, 0x0d, 0x0d, 0x70, 0xfa, 0x44, 0x44, 0xf9, 0x13,
     0xfb, 0xfb, 0xb1, 0x94, 0x7e, 0x7e, 0x5a, 0x48, 0x03, 0x03, 0x7a, 0xf2, 0x8c, 0x8c, 0xe4,
     0xd0, 0xb6, 0xb6, 0x47, 0x8b, 0x24, 0x24, 0x3c, 0x30, 0xe7, 0xe7, 0xa5, 0x84, 0x6b, 0x6b,
     0x41, 0x54, 0xdd, 0xdd, 0x06, 0xdf, 0x60, 0x60, 0xc5, 0x23, 0xfd, 0xfd, 0x45, 0x19, 0x3a,
     0x3a, 0xa3, 0x5b, 0xc2, 0xc2, 0x68, 0x3d, 0x8d, 0x8d, 0x15, 0x59, 0xec, 0xec, 0x21, 0xf3,
     0x66, 0x66, 0x31, 0xae, 0x6f, 0x6f, 0x3e, 0xa2, 0x57, 0x57, 0x16, 0x82, 0x10, 0x10, 0x95,
     0x63, 0xef, 0xef, 0x5b, 0x01, 0xb8, 0xb8, 0x4d, 0x83, 0x86, 0x86, 0x91, 0x2e, 0x6d, 0x6d,
     0xb5, 0xd9, 0x83, 0x83, 0x1f, 0x51, 0xaa, 0xaa, 0x53, 0x9b, 0x5d, 0x5d, 0x63, 0x7c, 0x68,
     0x68, 0x3b, 0xa6, 0xfe, 0xfe, 0x3f, 0xeb, 0x30, 0x30, 0xd6, 0xa5, 0x7a, 0x7a, 0x25, 0xbe,
     0xac, 0xac, 0xa7, 0x16, 0x09, 0x09, 0x0f, 0x0c, 0xf0, 0xf0, 0x35, 0xe3, 0xa7, 0xa7, 0x23,
     0x61},
    {0x32, 0xbc, 0x75, 0xbc, 0x21, 0xec, 0xf3, 0xec, 0x43, 0x20, 0xc6, 0x20, 0xc9, 0xb3, 0xf4,
     0xb3, 0x03, 0xda, 0xdb, 0xda, 0x8b, 0x02, 0x7b, 0x02, 0x2b, 0xe2, 0xfb, 0xe2, 0xfa, 0x9e,
     0xc8, 0x9e, 0xec, 0xc9, 0x4a, 0xc9, 0x09, 0xd4, 0xd3, 0xd4, 0x6b, 0x18, 0xe6, 0x18, 0x9f,
     0x1e, 0x6b, 0x1e, 0x0e, 0x98, 0x45, 0x98, 0x38, 0xb2, 0x7d, 0xb2, 0xd2, 0xa6, 0xe8, 0xa6,
     0xb7, 0x26, 0x4b, 0x26, 0x57, 0x3c, 0xd6, 0x3c, 0x8a, 0x93, 0x32, 0x93, 0xee, 0x82, 0xd8,
     0x82, 0x98, 0x52, 0xfd, 0x52, 0xd4, 0x7b, 0x37, 0x7b, 0x37, 0xbb, 0x71, 0xbb, 0x97, 0x5b,
     0xf1, 0x5b, 0x83, 0x47, 0xe1, 0x47, 0x3c, 0x24, 0x30, 0x24, 0xe2, 0x51, 0x0f, 0x51, 0xc6,
     0xba, 0xf8, 0xba, 0xf3, 0x4a, 0x1b, 0x4a, 0x48, 0xbf, 0x87, 0xbf, 0x70, 0x0d, 0xfa, 0x0d,
     0xb3, 0xb0, 0x06, 0xb0, 0xde, 0x75, 0x3f, 0x75, 0xfd, 0xd2, 0x5e, 0xd2, 0x20, 0x7d, 0xba,
     0x7d, 0x31, 0x66, 0xae, 0x66, 0xa3, 0x3a, 0x5b, 0x3a, 0x1c, 0x59, 0x8a, 0x59, 0x00, 0x00,
     0x00, 0x00, 0x93, 0xcd, 0xbc, 0xcd, 0xe0, 0x1a, 0x9d, 0x1a, 0x2c, 0xae, 0x6d, 0xae, 0xab,
     0x7f, 0xc1, 0x7f, 0xc7, 0x2b, 0xb1, 0x2b, 0xb9, 0xbe, 0x0e, 0xbe, 0xa0, 0xe0, 0x80, 0xe0,
     0x10, 0x8a, 0x5d, 0x8a, 0x52, 0x3b, 0xd2, 0x3b, 0xba, 0x64, 0xd5, 0x64, 0x88, 0xd8, 0xa0,
     0xd8, 0xa5, 0xe7, 0x84, 0xe7, 0xe8, 0x5f, 0x07, 0x5f, 0x11, 0x1b, 0x14, 0x1b, 0xc2, 0x2c,
     0xb5, 0x2c, 0xb4, 0xfc, 0x90, 0xfc, 0x27, 0x31, 0x2c, 0x31, 0x65, 0x80, 0xa3, 0x80, 0x2a,
     0x73, 0xb2, 0x73, 0x81, 0x0c, 0x73, 0x0c, 0x5f, 0x79, 0x4c, 0x79, 0x41, 0x6b, 0x54, 0x6b,
     0x02, 0x4b, 0x92, 0x4b, 0x69, 0x53, 0x74, 0x53, 0x8f, 0x94, 0x36, 0x94, 0x1f, 0x83, 0x51,
     0x83},
};

static constexpr uint8_t P[512] = {
    0xa9, 0x75, 0x67, 0xf3, 0xb3, 0xc6, 0xe8, 0xf4, 0x04, 0xdb, 0xfd, 0x7b, 0xa3, 0xfb, 0x76, 0xc8,
    0x9a, 0x4a, 0x92, 0xd3, 0x80, 0xe6, 0x78, 0x6b, 0xe4, 0x45, 0xdd, 0x7d, 0xd1, 0xe8, 0x38, 0x4b,
    0x0d, 0xd6, 0xc6, 0x32, 0x35, 0xd8, 0x98, 0xfd, 0x18, 0x37, 0xf7, 0x71, 0xec, 0xf1, 0x6c, 0xe1,
    0x43, 0x30, 0x75, 0x0f, 0x37, 0xf8, 0x26, 0x1b, 0xfa, 0x87, 0x13, 0xfa, 0x94, 0x06, 0x48, 0x3f,
    0xf2, 0x5e, 0xd0, 0xba, 0x8b, 0xae, 0x30, 0x5b, 0x84, 0x8a, 0x54, 0x00, 0xdf, 0xbc, 0x23, 0x9d,
    0x19, 0x6d, 0x5b, 0xc1, 0x3d, 0xb1, 0x59, 0x0e, 0xf3, 0x80, 0xae, 0x5d, 0xa2, 0xd2, 0x82, 0xd5,
    0x63, 0xa0, 0x01, 0x84, 0x83, 0x07, 0x2e, 0x14, 0xd9, 0xb5, 0x51, 0x90, 0x9b, 0x2c, 0x7c, 0xa3,
    0xa6, 0xb2, 0xeb, 0x73, 0xa5, 0x4c, 0xbe, 0x54, 0x16, 0x92, 0x0c, 0x74, 0xe3, 0x36, 0x61, 0x51,
    0xc0, 0x38, 0x8c, 0xb0, 0x3a, 0xbd, 0xf5, 0x5a, 0x73, 0xfc, 0x2c, 0x60, 0x25, 0x62, 0x0b, 0x96,
    0xbb, 0x6c, 0x4e, 0x42, 0x89, 0xf7, 0x6b, 0x10, 0x53, 0x7c, 0x6a, 0x28, 0xb4, 0x27, 0xf1, 0x8c,
    0xe1, 0x13, 0xe6, 0x95, 0xbd, 0x9c, 0x45, 0xc7, 0xe2, 0x24, 0xf4, 0x46, 0xb6, 0x3b, 0x66, 0x70,
    0xcc, 0xca, 0x95, 0xe3, 0x03, 0x85, 0x56, 0xcb, 0xd4, 0x11, 0x1c, 0xd0, 0x1e, 0x93, 0xd7, 0xb8,
    0xfb, 0xa6, 0xc3, 0x83, 0x8e, 0x20, 0xb5, 0xff, 0xe9, 0x9f, 0xcf, 0x77, 0xbf, 0xc3, 0xba, 0xcc,
    0xea, 0x03, 0x77, 0x6f, 0x39, 0x08, 0xaf, 0xbf, 0x33, 0x40, 0xc9, 0xe7, 0x62, 0x2b, 0x71, 0xe2,
    0x81, 0x79, 0x79, 0x0c, 0x09, 0xaa, 0xad, 0x82, 0x24, 0x41, 0xcd, 0x3a, 0xf9, 0xea, 0xd8, 0xb9,
    0xe5, 0xe4, 0xc5, 0x9a, 0xb9, 0xa4, 0x4d, 0x97, 0x44, 0x7e, 0x08, 0xda, 0x86, 0x7a, 0xe7, 0x17,
    0xa1, 0x66, 0x1d, 0x94, 0xaa, 0xa1, 0xed, 0x1d, 0x06, 0x3d, 0x70, 0xf0, 0xb2, 0xde, 0xd2, 0xb3,
    0x41, 0x0b, 0x7b, 0x72, 0xa0, 0xa7, 0x11, 0x1c, 0x31, 0xef, 0xc2, 0xd1, 0x27, 0x53, 0x90, 0x3e,
    0x20, 0x8f, 0xf6, 0x33, 0x60, 0x26, 0xff, 0x5f, 0x96, 0xec, 0x5c, 0x76, 0xb1, 0x2a, 0xab, 0x49,
    0x9e, 0x81, 0x9c, 0x88, 0x52, 0xee, 0x1b, 0x21, 0x5f, 0xc4, 0x93, 0x1a, 0x0a, 0xeb, 0xef, 0xd9,
    0x91, 0xc5, 0x85, 0x39, 0x49, 0x99, 0xee, 0xcd, 0x2d, 0xad, 0x4f, 0x31, 0x8f, 0x8b, 0x3b, 0x01,
    0x47, 0x18, 0x87, 0x23, 0x6d, 0xdd, 0x46, 0x1f, 0xd6, 0x4e, 0x3e, 0x2d, 0x69, 0xf9, 0x64, 0x48,
    0x2a, 0x4f, 0xce, 0xf2, 0xcb, 0x65, 0x2f, 0x8e, 0xfc, 0x78, 0x97, 0x5c, 0x05, 0x58, 0x7a, 0x19,
    0xac, 0x8d, 0x7f, 0xe5, 0xd5, 0x98, 0x1a, 0x57, 0x4b, 0x67, 0x0e, 0x7f, 0xa7, 0x05, 0x5a, 0x64,
    0x28, 0xaf, 0x14, 0x63, 0x3f, 0xb6, 0x29, 0xfe, 0x88, 0xf5, 0x3c, 0xb7, 0x4c, 0x3c, 0x02, 0xa5,
    0xb8, 0xce, 0xda, 0xe9, 0xb0, 0x68, 0x17, 0x44, 0x55, 0xe0, 0x1f, 0x4d, 0x8a, 0x43, 0x7d, 0x69,
    0x57, 0x29, 0xc7, 0x2e, 0x8d, 0xac, 0x74, 0x15, 0xb7, 0x59, 0xc4, 0xa8, 0x9f, 0x0a, 0x72, 0x9e,
    0x7e, 0x6e, 0x15, 0x47, 0x22, 0xdf, 0x12, 0x34, 0x58, 0x35, 0x07, 0x6a, 0x99, 0xcf, 0x34, 0xdc,
    0x6e, 0x22, 0x50, 0xc9, 0xde, 0xc0, 0x68, 0x9b, 0x65, 0x89, 0xbc, 0xd4, 0xdb, 0xed, 0xf8, 0xab,
    0xc8, 0x12, 0xa8, 0xa2, 0x2b, 0x0d, 0x40, 0x52, 0xdc, 0xbb, 0xfe, 0x02, 0x32, 0x2f, 0xa4, 0xa9,
    0xca, 0xd7, 0x10, 0x61, 0x21, 0x1e, 0xf0, 0xb4, 0xd3, 0x50, 0x5d, 0x04, 0x0f, 0xf6, 0x00, 0xc2,
    0x6f, 0x16, 0x9d, 0x25, 0x36, 0x86, 0x42, 0x56, 0x4a, 0x55, 0x5e, 0x09, 0xc1, 0xbe, 0xe0, 0x91};

CTwofish::CTwofish(const void *key)
{
	auto input = reinterpret_cast<const uint8_t *>(key);
	uint8_t local[32] = {0};
	uint8_t bVar1 = 0, bVar2 = 0;

	for (auto i = 0; i < 32; ++i)
		if (input[i] != 0)
		{
			uint32_t uVar4 = Q[0][input[i]];
			local[i] = Q[1][uVar4];
			if ((i & 3) == 1)
				bVar1 ^= Q[1][uVar4 + 0x2d];
			else if ((i & 3) == 2)
				bVar1 ^= Q[1][uVar4 + 0x8a];
			else if ((i & 3) == 3)
				bVar1 ^= Q[1][uVar4 + 0xd1];
		}

	for (auto i = 0; i < 256; ++i)
	{
		mSBox[0][i] = MDS_GF[0][MDS_GF[0][MDS_GF[1][P[i] ^ bVar1] ^ local[0]] ^ local[8]];
		mSBox[1][i] = MDS_GF[1][MDS_GF[0][MDS_GF[1][P[i] ^ local[1]] ^ local[9]] ^ local[16]];
		mSBox[2][i] = MDS_GF[2][MDS_GF[1][MDS_GF[0][P[i] ^ local[2]] ^ local[10]] ^ local[17]];
		mSBox[3][i] = MDS_GF[3][MDS_GF[1][MDS_GF[0][P[i] ^ local[3]] ^ local[11]] ^ local[18]];
	}

	for (auto i = 0; i < 40; ++i)
		mKey[i] = MDS_GF[0][MDS_GF[1][input[i] ^ MDS_GF[1][input[i + 8] ^ 0x67]] ^ input[i + 16]];
}

void CTwofish::EncryptCBCIteration(const void *inData, void *outData)
{
	auto input = reinterpret_cast<const uint32_t *>(inData);
	auto output = reinterpret_cast<uint32_t *>(outData);

	auto uVar1 = input[0] ^ mKey[0];
	auto uVar2 = input[1] ^ mKey[1];
	auto uVar3 = input[2] ^ mKey[2];
	auto uVar4 = input[3] ^ mKey[3];

	for (auto round = 0; round < 16; ++round)
	{
		auto t0 = mSBox[0][uVar2 & 0xFF] ^ mSBox[1][(uVar2 >> 8) & 0xFF] ^
		          mSBox[2][(uVar2 >> 16) & 0xFF] ^ mSBox[3][(uVar2 >> 24)];
		auto t1 = mSBox[0][uVar4 & 0xFF] ^ mSBox[1][(uVar4 >> 8) & 0xFF] ^
		          mSBox[2][(uVar4 >> 16) & 0xFF] ^ mSBox[3][(uVar4 >> 24)];

		auto f0 = (t0 + t1) ^ mKey[8 + (round << 1)];
		auto f1 = (t0 + 2 * t1) ^ mKey[9 + (round << 1)];

		auto temp = uVar1;
		uVar1 = uVar3 ^ f1;
		uVar3 = uVar4;
		uVar4 = uVar2 ^ f0;
		uVar2 = temp;
	}

	output[0] = uVar3 ^ mKey[4];
	output[1] = uVar4 ^ mKey[5];
	output[2] = uVar1 ^ mKey[6];
	output[3] = uVar2 ^ mKey[7];
}

void CTwofish::Encrypt(const void *inData, void *outData)
{
	auto input = reinterpret_cast<const uint32_t *>(inData);
	auto output = reinterpret_cast<uint32_t *>(outData);

	auto uVar1 = input[0] ^ mKey[0];
	auto uVar7 = input[1] ^ mKey[1];
	auto uVar3 = input[2] ^ mKey[2];
	auto uVar2 = input[3] ^ mKey[3];

	for (auto round = 0; round < 16; ++round)
	{
		auto t0 = mSBox[0][uVar7 & 0xFF] ^ mSBox[1][(uVar7 >> 8) & 0xFF] ^
		          mSBox[2][(uVar7 >> 16) & 0xFF] ^ mSBox[3][(uVar7 >> 24)];
		auto t1 = mSBox[0][uVar1 & 0xFF] ^ mSBox[1][(uVar1 >> 8) & 0xFF] ^
		          mSBox[2][(uVar1 >> 16) & 0xFF] ^ mSBox[3][(uVar1 >> 24)];

		auto f0 = (t0 + t1) ^ mKey[8 + (round << 1)];
		auto f1 = (t0 + 2 * t1) ^ mKey[9 + (round << 1)];

		auto temp = uVar3;
		uVar3 = uVar2 ^ f1;
		uVar2 = uVar1;
		uVar1 = uVar7 ^ f0;
		uVar7 = temp;
	}

	output[0] = uVar3 ^ mKey[4];
	output[1] = uVar2 ^ mKey[5];
	output[2] = uVar1 ^ mKey[6];
	output[3] = uVar7 ^ mKey[7];
}

void CTwofish::EncryptCBC(void *outData, size_t &ioPartialBlockSize, const void *inData,
                          size_t inDataSize, const void *inKey)
{
	auto outText = reinterpret_cast<uint8_t *>(outData);
	auto input = reinterpret_cast<const uint8_t *>(inData);

	if (ioPartialBlockSize)
	{
		auto remainingSpace = 16 - ioPartialBlockSize;
		if (inDataSize < remainingSpace)
		{
			UMemory::Move(outText + ioPartialBlockSize, input, inDataSize);
			ioPartialBlockSize += inDataSize;
			return;
		}

		UMemory::Move(outText + ioPartialBlockSize, input, remainingSpace);
		EncryptCBCIteration(outText, outText);
		input += remainingSpace;
		inDataSize -= remainingSpace;
		outText += 16;
		ioPartialBlockSize = 0;
	}

	while (inDataSize >= 16)
	{
		EncryptCBCIteration(input, outText);
		input += 16;
		outText += 16;
		inDataSize -= 16;
	}

	if (inDataSize > 0)
	{
		UMemory::Move(outText, input, inDataSize);
		ioPartialBlockSize = inDataSize;
	}
}
