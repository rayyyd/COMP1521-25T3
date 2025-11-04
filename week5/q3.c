a = 0x95    => 0b 1001 0101
b = 0xF1    => 0b 1111 0001
c = 0x01    => 0b 0000 0001


a) |    "write" -> when mask is 1, perform a write.
1001 0101          <- subject
1111 0001          <- mask
----------   |
1111 0101

b) &   "read"  -> copy the values where mask is 1.
1001 0101          <- subject
1111 0001          <- mask
----------   &
1001 0001
c) ^  "flip bits"
1001 0101          <- subject
1111 0001          <- mask
----------   ^
0110 0100

d) &~    "remove"
1001 0101          <- subject
1111 0001          <- mask
----------   &~
0000 0100