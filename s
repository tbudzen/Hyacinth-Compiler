SUB 0 # Kompilacja stałej 1 do adresu 1025
INC
STORE 1025 # Koniec kompilacji stałej 1 do adresu 1025
SUB 0 # Kompilacja stałej -1 do adresu 1026
DEC
STORE 1026 # Koniec kompilacji stałej -1 do adresu 1026
SUB 0 # Kompilacja stałej 1 do adresu 1027
INC
STORE 1027 # Koniec kompilacji stałej 1 do adresu 1027
SUB 0 # Kompilacja stałej -1 do adresu 1028
DEC
STORE 1028 # Koniec kompilacji stałej -1 do adresu 1028
SUB 0 # Kompilacja stałej 10 do adresu 1032
SUB 0 # Kompilacja stałej 10 do adresu 1032
INC
INC
INC
STORE 1
SUB 0
INC
SHIFT 1
STORE 1
SUB 0
ADD 1
INC
INC
STORE 1032 # Koniec kompilacji stałej 10 do adresu 1032
SUB 0 # Kompilacja stałej 0 do adresu 1033
STORE 1033 # Koniec kompilacji stałej 0 do adresu 1033
SUB 0 # Kompilacja stałej 9 do adresu 1034
SUB 0 # Kompilacja stałej 9 do adresu 1034
INC
INC
INC
STORE 1
SUB 0
INC
SHIFT 1
STORE 1
SUB 0
ADD 1
INC
STORE 1034 # Koniec kompilacji stałej 9 do adresu 1034
SUB 0 # Kompilacja stałej 0 do adresu 1035
STORE 1035 # Koniec kompilacji stałej 0 do adresu 1035
LOAD 1035 # Kompilacja FOR FROM TO
STORE 1036
SUB 0 # Kompilacja stałej 9 do adresu 1037
SUB 0 # Kompilacja stałej 9 do adresu 1037
INC
INC
INC
STORE 2
SUB 0
INC
SHIFT 2
STORE 2
SUB 0
ADD 2
INC
STORE 1037 # Koniec kompilacji stałej 9 do adresu 1037
LOAD 1037
STORE 1
LOAD 1036
SUB 1
JPOS 245
LOAD 1036 # regN = n
STORE 2
LOAD 1036 # regM = m
STORE 3
SUB 0 # -------------- START MUL, regConst1 = 1
INC
STORE 8
SUB 0 # regConstNeg2 = 2
DEC
DEC
STORE 9
SUB 0 # regConstNeg1 = -1
DEC
STORE 10
SUB 0
STORE 11 # STORE regSignN
SUB 0
STORE 12 # STORE regSignM
LOAD 2
JNEG 87 # regN < 0
JUMP 96
LOAD 2 # compileNegP0
SHIFT 8
STORE 13
LOAD 2
SUB 13
STORE 2
SUB 0 # compile1ToReg
INC
STORE 11
SUB 0 # ans = 0
STORE 4
SUB 0 # count = 0
STORE 7
LOAD 3
JNEG 103 # if regM < 0 then ...
JUMP 112
LOAD 3 # compileNegP0
SHIFT 8
STORE 13
LOAD 3
SUB 13
STORE 3
SUB 0 # compile1ToReg
INC
STORE 12
LOAD 3 # while (m)
JPOS 115 # if (m > 0)
JUMP 137
LOAD 3
SHIFT 10
SHIFT 8
STORE 6
LOAD 3
SUB 6
DEC
JZERO 124 # if (m % 2) = 1
JUMP 130
LOAD 2 # n0 = n << count
SHIFT 7
STORE 5
LOAD 4 # ans += n0
ADD 5
STORE 4
LOAD 7 # count ++
INC
STORE 7
LOAD 3 # m /= 2
SHIFT 10
STORE 3
JUMP 112
LOAD 11
ADD 12
DEC
JZERO 142
JUMP 148
LOAD 4 # compileNegP0
SHIFT 8
STORE 13
LOAD 4
SUB 13
STORE 4
LOAD 4
LOAD 4
STORE 2
SUB 0 # Kompilacja stałej 1036 do adresu 1038
SUB 0 # Kompilacja stałej 1036 do adresu 1038
INC
INC
INC
INC
INC
INC
INC
INC
INC
INC
STORE 3
SUB 0
INC
SHIFT 3
STORE 3
SUB 0 # Kompilacja stałej 1036 do adresu 1038
INC
INC
INC
STORE 4
SUB 0
INC
SHIFT 4
STORE 4
SUB 0
ADD 3
ADD 4
INC
INC
INC
INC
STORE 1038 # Koniec kompilacji stałej 1036 do adresu 1038
SUB 0 # Kompilacja stałej 10 do adresu 1039
SUB 0 # Kompilacja stałej 10 do adresu 1039
INC
INC
INC
STORE 3
SUB 0
INC
SHIFT 3
STORE 3
SUB 0
ADD 3
INC
INC
STORE 1039 # Koniec kompilacji stałej 10 do adresu 1039
SUB 0 # Kompilacja stałej 1030 do adresu 1040
SUB 0 # Kompilacja stałej 1030 do adresu 1040
INC
INC
INC
INC
INC
INC
INC
INC
INC
INC
STORE 3
SUB 0
INC
SHIFT 3
STORE 3
SUB 0 # Kompilacja stałej 1030 do adresu 1040
INC
INC
STORE 4
SUB 0
INC
SHIFT 4
STORE 4
SUB 0
ADD 3
ADD 4
INC
INC
STORE 1040 # Koniec kompilacji stałej 1030 do adresu 1040
LOAD 1038
STORE 3
LOAD 1039
STORE 4
LOADI 3
ADD 1040
SUB 4
STORE 5
LOAD 2
STOREI 5
LOAD 1036
INC
STORE 1036
JUMP 63
SUB 0 # Kompilacja stałej 1036 do adresu 1041
SUB 0 # Kompilacja stałej 1036 do adresu 1041
INC
INC
INC
INC
INC
INC
INC
INC
INC
INC
STORE 4
SUB 0
INC
SHIFT 4
STORE 4
SUB 0 # Kompilacja stałej 1036 do adresu 1041
INC
INC
INC
STORE 5
SUB 0
INC
SHIFT 5
STORE 5
SUB 0
ADD 4
ADD 5
INC
INC
INC
INC
STORE 1041 # Koniec kompilacji stałej 1036 do adresu 1041
SUB 0 # Kompilacja stałej 1030 do adresu 1042
SUB 0 # Kompilacja stałej 1030 do adresu 1042
INC
INC
INC
INC
INC
INC
INC
INC
INC
INC
STORE 4
SUB 0
INC
SHIFT 4
STORE 4
SUB 0 # Kompilacja stałej 1030 do adresu 1042
INC
INC
STORE 5
SUB 0
INC
SHIFT 5
STORE 5
SUB 0
ADD 4
ADD 5
INC
INC
STORE 1042 # Koniec kompilacji stałej 1030 do adresu 1042
SUB 0 # Kompilacja stałej 10 do adresu 1043
SUB 0 # Kompilacja stałej 10 do adresu 1043
INC
INC
INC
STORE 4
SUB 0
INC
SHIFT 4
STORE 4
SUB 0
ADD 4
INC
INC
STORE 1043 # Koniec kompilacji stałej 10 do adresu 1043
LOAD 1041
STORE 1
LOAD 1043
STORE 2
LOADI 1
ADD 1042
SUB 2
STORE 3
LOADI 3
STORE 0
STORE 1029
HALT
