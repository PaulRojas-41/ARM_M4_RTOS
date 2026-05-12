import zlib
import crc32_mpeg2

APP_BIN = "ARM_M4_RTOS_NO_HEADER.bin"

with open(APP_BIN, "rb") as f:
    data = f.read()

# 2. Calculate CRC on ONLY the app data

crc = crc32_mpeg2(data)

print(f"New CRC = 0x{crc:08X}")
print(f"Size = {len(data)}bytes")
