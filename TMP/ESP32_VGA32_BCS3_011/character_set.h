static const byte character[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // 00
  , 0x00, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00    // 01
  , 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00    // 02
  , 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00    // 03
  , 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0xF0    // 04
  , 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0    // 05
  , 0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0, 0xF0, 0xF0    // 06
  , 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0xF0, 0xF0    // 07
  , 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F    // 08
  , 0x0F, 0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F    // 09
  , 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F    // 0A
  , 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x0F, 0x0F    // 0B
  , 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF    // 0C
  , 0xFF, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF    // 0D
  , 0xFF, 0x0F, 0x0F, 0x0F, 0x0F, 0xFF, 0xFF, 0xFF    // 0E
  , 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF    // 0F

  , 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // 10
  , 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // 11
  , 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80    // 12
  , 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01    // 13
  , 0x00, 0x22, 0x77, 0x7F, 0x7F, 0x3E, 0x1C, 0x08    // 14
  , 0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x7F, 0x2A, 0x08    // 15
  , 0x00, 0x08, 0x1C, 0x3E, 0x7F, 0x3E, 0x1C, 0x08    // 16
  , 0x00, 0x08, 0x1C, 0x2A, 0x7F, 0x2A, 0x08, 0x08    // 17
  , 0x1C, 0x1C, 0x3E, 0x7F, 0x7F, 0x7F, 0x7F, 0x3E    // 18
  , 0xFF, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F    // 19
  , 0x01, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03    // 1A
  , 0x80, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0    // 1B
  , 0xFF, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE    // 1C
  , 0xFF, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81    // 1D
  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // 1E
  , 0x00, 0x1C, 0x22, 0x22, 0x22, 0x14, 0x14, 0x36    // 1F

  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00    // 20
  , 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00    // 21
  , 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00    // 22
  , 0x14, 0x14, 0x3E, 0x14, 0x3E, 0x14, 0x14, 0x00    // 23
  , 0x08, 0x1E, 0x28, 0x1C, 0x0A, 0x3C, 0x08, 0x00    // 24
  , 0x30, 0x32, 0x04, 0x08, 0x10, 0x26, 0x06, 0x00    // 25
  , 0x08, 0x14, 0x14, 0x18, 0x2A, 0x24, 0x1A, 0x00    // 26
  , 0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00    // 27
  , 0x04, 0x08, 0x10, 0x10, 0x10, 0x08, 0x04, 0x00    // 28
  , 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x00    // 29
  , 0x00, 0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00, 0x00    // 2A
  , 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00    // 2B
  , 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x20, 0x00    // 2C
  , 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00    // 2D
  , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00    // 2E
  , 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00    // 2F
                                            
  , 0x1C, 0x22, 0x26, 0x2A, 0x32, 0x22, 0x1C, 0x00    // 30
  , 0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00    // 31
  , 0x1C, 0x22, 0x02, 0x0C, 0x10, 0x20, 0x3E, 0x00    // 32
  , 0x3E, 0x02, 0x04, 0x0C, 0x02, 0x22, 0x1C, 0x00    // 33
  , 0x04, 0x0C, 0x14, 0x24, 0x3E, 0x04, 0x04, 0x00    // 34
  , 0x3E, 0x20, 0x3C, 0x02, 0x02, 0x22, 0x1C, 0x00    // 35
  , 0x0E, 0x10, 0x20, 0x3C, 0x22, 0x22, 0x1C, 0x00    // 36
  , 0x3E, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00    // 37
  , 0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x1C, 0x00    // 38
  , 0x1C, 0x22, 0x22, 0x1E, 0x02, 0x04, 0x38, 0x00    // 39
  , 0x00, 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00    // 3A
  , 0x00, 0x00, 0x08, 0x00, 0x08, 0x08, 0x10, 0x00    // 3B
  , 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00    // 3C
  , 0x00, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x00, 0x00    // 3D
  , 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00    // 3E
  , 0x1C, 0x22, 0x02, 0x04, 0x08, 0x00, 0x08, 0x00    // 3F
                                            
  , 0x1C, 0x22, 0x26, 0x2A, 0x2E, 0x20, 0x1C, 0x00    // 40
  , 0x08, 0x14, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x00    // 41
  , 0x3C, 0x22, 0x22, 0x3C, 0x22, 0x22, 0x3C, 0x00    // 42
  , 0x1C, 0x22, 0x20, 0x20, 0x20, 0x22, 0x1C, 0x00    // 43
  , 0x3C, 0x12, 0x12, 0x12, 0x12, 0x12, 0x3C, 0x00    // 44
  , 0x3E, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x3E, 0x00    // 45
  , 0x3E, 0x20, 0x20, 0x3C, 0x20, 0x20, 0x20, 0x00    // 46
  , 0x1C, 0x22, 0x20, 0x20, 0x26, 0x22, 0x1E, 0x00    // 47
  , 0x22, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22, 0x00    // 48
  , 0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00    // 49
  , 0x02, 0x02, 0x02, 0x02, 0x22, 0x22, 0x1C, 0x00    // 4A
  , 0x22, 0x24, 0x28, 0x30, 0x28, 0x24, 0x22, 0x00    // 4B
  , 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3E, 0x00    // 4C
  , 0x22, 0x36, 0x2A, 0x2A, 0x22, 0x22, 0x22, 0x00    // 4D
  , 0x22, 0x22, 0x32, 0x2A, 0x26, 0x22, 0x22, 0x00    // 4E
  , 0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x00    // 4F
                                            
  , 0x3C, 0x22, 0x22, 0x3C, 0x20, 0x20, 0x20, 0x00    // 50
  , 0x1C, 0x22, 0x22, 0x22, 0x2A, 0x24, 0x1A, 0x00    // 51
  , 0x3C, 0x22, 0x22, 0x3C, 0x28, 0x24, 0x22, 0x00    // 52
  , 0x1C, 0x22, 0x20, 0x1C, 0x02, 0x22, 0x1C, 0x00    // 53
  , 0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00    // 54
  , 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x00    // 55
  , 0x22, 0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x00    // 56
  , 0x22, 0x22, 0x22, 0x2A, 0x2A, 0x2A, 0x14, 0x00    // 57
  , 0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22, 0x00    // 58
  , 0x22, 0x22, 0x22, 0x1C, 0x08, 0x08, 0x08, 0x00    // 59
  , 0x3E, 0x02, 0x04, 0x08, 0x10, 0x20, 0x3E, 0x00    // 5A
  , 0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1C, 0x00    // 5B
  , 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00    // 5C
  , 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00    // 5D
  , 0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00    // 5E
  , 0x7E, 0x4E, 0x66, 0x72, 0x66, 0x4E, 0x7E, 0x00    // 5F
                                            
  , 0x08, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00    // 60
  , 0x00, 0x00, 0x1C, 0x02, 0x1E, 0x22, 0x1E, 0x00    // 61
  , 0x20, 0x20, 0x3C, 0x22, 0x22, 0x22, 0x3E, 0x00    // 62
  , 0x00, 0x00, 0x1C, 0x20, 0x20, 0x20, 0x1C, 0x00    // 63
  , 0x02, 0x02, 0x1E, 0x22, 0x22, 0x22, 0x1E, 0x00    // 64
  , 0x00, 0x00, 0x1C, 0x22, 0x3E, 0x20, 0x1C, 0x00    // 65
  , 0x08, 0x14, 0x10, 0x38, 0x10, 0x10, 0x10, 0x00    // 66
  , 0x00, 0x00, 0x1E, 0x22, 0x22, 0x1E, 0x02, 0x1C    // 67
  , 0x20, 0x20, 0x3C, 0x22, 0x22, 0x22, 0x22, 0x00    // 68
  , 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x1C, 0x00    // 69
  , 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x28, 0x10    // 6A
  , 0x20, 0x20, 0x22, 0x24, 0x28, 0x34, 0x22, 0x00    // 6B
  , 0x10, 0x10, 0x10, 0x10, 0x10, 0x14, 0x08, 0x00    // 6C
  , 0x00, 0x00, 0x3C, 0x2A, 0x2A, 0x2A, 0x2A, 0x00    // 6D
  , 0x00, 0x00, 0x3C, 0x22, 0x22, 0x22, 0x22, 0x00    // 6E
  , 0x00, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00    // 6F
                                            
  , 0x00, 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x20, 0x20    // 70
  , 0x00, 0x00, 0x1E, 0x22, 0x22, 0x1E, 0x02, 0x02    // 71
  , 0x00, 0x00, 0x16, 0x18, 0x10, 0x10, 0x10, 0x00    // 72
  , 0x00, 0x00, 0x1C, 0x20, 0x18, 0x04, 0x38, 0x00    // 73
  , 0x10, 0x10, 0x38, 0x10, 0x10, 0x14, 0x08, 0x00    // 74
  , 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x1E, 0x00    // 75
  , 0x00, 0x00, 0x22, 0x22, 0x14, 0x14, 0x08, 0x00    // 76
  , 0x00, 0x00, 0x22, 0x2A, 0x2A, 0x2A, 0x14, 0x00    // 77
  , 0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00    // 78
  , 0x00, 0x00, 0x22, 0x22, 0x22, 0x1E, 0x02, 0x1C    // 79  'y'
  , 0x00, 0x00, 0x3E, 0x04, 0x08, 0x10, 0x3E, 0x00    // 7A
  , 0x14, 0x00, 0x1C, 0x02, 0x1E, 0x22, 0x1E, 0x00    // 7B
  , 0x14, 0x00, 0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00    // 7C
  , 0x14, 0x00, 0x22, 0x22, 0x22, 0x22, 0x1E, 0x00    // 7D
  , 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08    // 7E
  , 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00    // 7F
}
;