center 0
 2.098455
center 1
 1.142235
center 2
 0.510667
center 3
 3.156
the group 0
DES:1.640、CAST128:1.721、TWOFISH:2.521、RC6:2.072、SERPENT:2.204、C2:1.782、SQUARE:1.880 M6:2.493、ICE:2.140、GRAND_CRU:1.950
the group 1
AES:1.450、BLOWFISH:1.240、CAMELLIA:0.890、GOST:1.121、SM4:1.151、TEA:0.931、XTEA:0.931、LUCIFER:0.910、CLEFIA:1.440、ARIA:1.380、PRESENT:1.080、MACGUFFIN:0.911、SHARK:1.380、CS_CIPHER:0.931、 NUSH:0.892E2:1.400、KHAZAD:1.380
the group 2
RC5:0.601、SPECK:0.460、SIMON:0.471
the group 3
IDEA:3.360、SEED:3.090S、KIPJECT:2.680、Q:3.810、HIEROCRYPT_L1:2.760、HIEROCRYPT_3:2.760

Control          Signal    Amount Functional Unit
control[xx:xx]    4         Arithmetic Unit
control[xx:xx]   24        Logical Operation Unit
control[xx:xx]  8         Table Lookup Unit
control[xx:xx]  8         Shifter/Rotator Unit
control[xx:xx] 384       Permutation/Expansion Unit

XOR
NOT
OR
AND




Control Signal Selected Bit
000000      operandA[0]
000001      operandA[1]
000010      operandA[2]
.           .         
.           .         
000011      operandA[31]
100000      operandB[0]
100001      operandB[1]
.           .         
.           .         
111101      operandB[29]
111110      operandB[30]
111111      operandB[31]

Shift-and-add 算法描述
Input：二元多项式a(x)、b(x)，最高次项系数最多为(n-1)
Output：c(x)=a(x)b(x) mod f(x)
(1)c<-0
(2)for i=n-1 to 1 do
   if ai=1 then c<-c+b
   c=c*x mod f(x)
(3)if a0=1 then c<-c+b
   return (c)





