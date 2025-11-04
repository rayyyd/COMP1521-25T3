
a)    2.5 = 1.25 * 2
sign: +
exp - 127 = 2, exp = 129 = 10000001
1.frac = 1.25, frac = 0.25
0.25 = 2^-2
010000000000000000000
total: 0 10000001 010000000000000000000000000

b)    0.375 / 0.25 = 1.5
sign: +
exp: 01111101
c)    27.0 / 

d)    100.0 


27 / 16


string: rwx r-x r-x
bin:    111 101 101
oct:     7   5   5


string: rw- -w- ---
bin:    110 010 000
oct:     6   2   0
defines:
S_IRUSR | S_IWUSR | S_IWGRP     
// user (owner) can read and write (S_IRUSR, S_IWUSR)
// group can write. (S_IWGRP)


mode_t mode = s.st_mode;
// mode is in binary/octal format.
//something like 
// rwxr-xr-x
// 111101101
// theres also the directory bit, but thats a bit more complicated.
char perm[11];
perm[0] = S_ISDIR(mode) ? 'd' : '-';
perm[1] = (mode & S_IRUSR) ? 'r' : '-';
perm[2] = (mode & S_IWUSR) ? 'w' : '-';
perm[3] = (mode & S_IXUSR) ? 'x' : '-';
perm[4] = (mode & S_IRGRP) ? 'r' : '-';
perm[5] = (mode & S_IWGRP) ? 'w' : '-';
perm[6] = (mode & S_IXGRP) ? 'x' : '-';
perm[7] = (mode & S_IROTH) ? 'r' : '-';
perm[8] = (mode & S_IWOTH) ? 'w' : '-';
perm[9] = (mode & S_IXOTH) ? 'x' : '-';
perm[10] = '\0';








00 11 22 33

if size = 1,, nelems = 4   <- read 1 byte 4 times, in order
00
11
22
33

if size = 4, nelems = 1    <- reads 4 bytes, it determines its own order.
little endian -> 33 22 11 00
big endian -> 00 11 22 33


char[10] buf = "hello";
fwrite(&buf, 1, sizeof(buf), stdout);
             ^
             set to 1
fread