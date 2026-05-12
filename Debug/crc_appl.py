import zlib

APP_BIN = "ARM_M4_RTOS_NO_HEADER.bin"

with open(APP_BIN, "rb") as f:
    data = f.read()

crc = zlib.crc32(data) & 0xFFFFFFFF

print(f"New CRC = 0x{crc:08X}")
print(f"Size = {len(data)}bytes")
