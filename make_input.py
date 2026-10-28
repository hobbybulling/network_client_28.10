import struct

with open('input.bin', 'wb') as f:
    f.write(struct.pack('I', 1))
    f.write(struct.pack('I', 2))
    f.write(struct.pack('2f', 1.5, 2.5))
