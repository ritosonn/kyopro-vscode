int numofbits(int bits){
    bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
    bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
    return (bits & 0x0000ffff) + (bits >>16 & 0x0000ffff);
}
int msb(int bits){
    bits |= (bits >> 1);
    bits |= (bits >> 2);
    bits |= (bits >> 4);
    bits |= (bits >> 8);
    bits |= (bits >> 16);
    return (bits + 1) >> 1;
}
int lsb(int bits){
    return bits & (-bits);
}