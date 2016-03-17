      SUBROUTINE MTM(N,M,P,W,C,Z,X,BACK,JCK,JUB)
C
C THIS SUBROUTINE SOLVES THE 0-1 MULTIPLE KNAPSACK PROBLEM
C
C MAXIMIZE  Z = P(1)*(Y(1,1) + ... + Y(M,1)) +
C                              ...           +
C               P(N)*(Y(1,N) + ... + Y(M,N))
C SUBJECT TO:
C
C   W(1)*Y(I,1) + ... + W(N)*Y(I,N) .LE. C(I)  FOR I=1,...,M,
C   Y(1,J) + ... + Y(M,J) .LE. 1               FOR J=1,...,N,
C   Y(I,J) = 0 OR 1                 FOR I=1,...,M, J=1,...,N.
C
C THE PROGRAM IS INCLUDED IN THE VOLUME
C   S. MARTELLO, P. TOTH, "KNAPSACK PROBLEMS: ALGORITHMS
C   AND COMPUTER IMPLEMENTATIONS", JOHN WILEY, 1990
C AND IMPLEMENTS THE ENUMERATIVE ALGORITHM DESCRIBED IN
C SECTION  6.4.3 .
C THE PROGRAM DERIVES FROM AN EARLIER CODE PRESENTED IN
C   S. MARTELLO, P. TOTH, "ALGORITHM 632. A PROGRAM FOR THE 0-1
C   MULTIPLE KNAPSACK PROBLEM", ACM TRANSACTIONS ON MATHEMATICAL
C   SOFTWARE, 1985.
C
C THE INPUT PROBLEM MUST SATISFY THE CONDITIONS
C
C   1) 2 .LE. N .LE. MAXN AND 1 .LE. M .LE. MAXM , WHERE  MAXN  AND
C      MAXM  ARE DEFINED BY THE FIRST TWO EXECUTABLE STATEMENTS;
C   2) P(J), W(J) AND C(I) POSITIVE INTEGERS;
C   3) MIN (C(I)) .GE. MIN (W(J));
C   4) MAX (W(J)) .LE. MAX (C(I));
C   5) MAX (C(I)) .LT. W(1) + ... + W(N) ;
C   6) P(J)/W(J) .GE. P(J+1)/W(J+1) FOR J=1,...,N-1;
C   7) C(I) .LE. C(I+1) FOR I=1,...,M-1.
C
C MTM CALLS  5  PROCEDURES: CHMTM, PAR, PI, SIGMA AND SKP.
C
C THE PROGRAM IS COMPLETELY SELF-CONTAINED AND COMMUNICATION TO IT
C IS ACHIEVED SOLELY THROUGH THE PARAMETER LIST OF MTM.
C NO MACHINE-DEPENDENT CONSTANT IS USED.
C THE PROGRAM IS WRITTEN IN 1967 AMERICAN NATIONAL STANDARD FORTRAN
C AND IS ACCEPTED BY THE PFORT VERIFIER (PFORT IS THE PORTABLE
C SUBSET OF ANSI DEFINED BY THE ASSOCIATION FOR COMPUTING MACHINERY).
C THE PROGRAM HAS BEEN TESTED ON A DIGITAL VAX 11/780 AND AN H.P.
C 9000/840.
C
C MTM NEEDS
C   5  ARRAYS ( C ,  F ,  PBL ,  Q  AND  V ) OF LENGTH AT LEAST  M ;
C   8  ARRAYS ( P ,  W ,  X ,  UBB ,  BS ,  XS ,  LX  AND  LXI ) OF
C               LENGTH AT LEAST  N ;
C   3  ARRAYS ( B ,  PS  AND  WS ) OF LENGTH AT LEAST  N + 1 ;
C   3  ARRAYS ( BB ,  XC  AND  XL ) OF LENGTH AT LEAST  M X N ;
C   1  ARRAY  ( BL ) OF LENGTH  AT LEAST  M X (N + 1) ;
C   5  ARRAYS ( D ,  MIN ,  PBAR ,  WBAR  AND  ZBAR ) OF LENGTH AT
C               LEAST  N  (FOR INTERNAL USE IN SUBROUTINE SKP) .
C
C THE ARRAYS ARE CURRENTLY DIMENSIONED TO ALLOW PROBLEMS FOR WHICH
C M .LE. 10  AND  N .LE. 1000 . CHANGING SUCH DIMENSIONS ALSO REQUIRES
C CHANGING THE DIMENSIONS OF  BS ,  PS ,  WS ,  XS ,  LX  AND  LXI
C IN SUBROUTINE SIGMA, OF  BB ,  BL ,  XL ,  BS ,  PS ,  WS  AND  XS
C IN SUBROUTINE PI, OF BB ,  LX  AND  LXI  IN SUBROUTINE PAR, OF  D ,
C MIN ,  PBAR ,  WBAR  AND  ZBAR  IN SUBROUTINE SKP. IN ADDITION, THE
C VALUES OF MAXN AND MAXM MUST BE CONVENIENTLY DEFINED.
C
C MEANING OF THE INPUT PARAMETERS:
C N    = NUMBER OF ITEMS;
C M    = NUMBER OF KNAPSACKS;
C P(J) = PROFIT OF ITEM  J  (J=1,...,N);
C W(J) = WEIGHT OF ITEM  J  (J=1,...,N);
C C(I) = CAPACITY OF KNAPSACK  I  (I=1,...,M);
C BACK = -1 IF EXACT SOLUTION IS REQUIRED,
C      = MAXIMUM NUMBER OF BACKTRACKINGS TO BE PERFORMED, IF
C        HEURISTIC SOLUTION IS REQUIRED;
C JCK  = 1 IF CHECK ON THE INPUT DATA IS DESIRED,
C      = 0 OTHERWISE.
C
C MEANING OF THE OUTPUT PARAMETERS:
C Z    = VALUE OF THE SOLUTION FOUNDIF  Z .GT. 0 ,
C      = ERROR IN THE INPUT DATA (WHEN JCK=1) IF  Z .LT. 0 :
C        CONDITION -Z IS VIOLATED;
C X(J) = 0  IF ITEM  J  IS NOT IN THE SOLUTION FOUND,
C        (I.E. IF  Y(I,J) = 0  FOR ALL  I ),
C      = KNAPSACK WHERE ITEM  J  IS INSERTED, OTHERWISE
C        (I.E. IF  Y(X(J),J) = 1 );
C JUB  = UPPER BOUND ON THE OPTIMAL SOLUTION VALUE (TO EVALUATE
C        Z WHEN BACK .GT.0 ).
C
C ALL THE PARAMETERS ARE INTEGER. ON RETURN OF MTM ALL THE
C INPUT PARAMETERS ARE UNCHANGED EXCEPT  BACK , WHICH GIVES
C THE NUMBER OF BACKTRACKINGS PERFORMED.
C
C MEANING OF THE MAIN INTERNAL VARIABLES:
C I       = KNAPSACK CURRENTLY CONSIDERED.
C LB      = LOWER BOUND ON THE OPTIMAL SOLUTION.
C UB      = UPPER BOUND ON THE OPTIMAL SOLUTION.
C VB      = VALUE OF THE CURRENT SOLUTION.
C XC(I,J) = 1  IF ITEM  J  IS INSERTED IN KNAPSACK  I  IN
C              THE CURRENT SOLUTION.
C         = 0  OTHERWISE.
C F(I)    = POINTER TO THE LAST ITEM INSERTED IN KNAPSACK  I
C           ( = -1  IF KNAPSACK  I  IS EMPTY).
C BB(I,J) = POINTER TO THE ITEM INSERTED IN KNAPSACK  I
C           JUST BEFORE ITEM  J ( = -1  IF  J  IS THE FIRST
C           ITEM INSERTED IN KNAPSACK  I ).
C Q(I)    = CURRENT AVAILABLE CAPACITY OF KNAPSACK  I .
C B(J)    = 1  IF ITEM  J  IS NOT INSERTED IN ANY KNAPSACK.
C         = 0  IF ITEM  J  IS INSERTED IN A KNAPSACK.
C PBL(I)  = NUMBER OF THE ITEMS WHICH CAN BE INSERTED IN
C           KNAPSACK  I .
C BL(I,S) = POINTER TO THE  S-TH  ITEM WHICH CAN BE INSERTED
C           IN KNAPSACK  I .
C XL(I,J) = 1  IF ITEM  J  WAS INSERTED IN KNAPSACK  I  IN
C              THE LAST EXECUTION OF SUBROUTINE PI.
C         = 0  OTHERWISE.
C
      INTEGER       P(1000),W(1000),C(10),X(1000),BACK,Z
      INTEGER       BB(10,1000),BL(10,1001),XC(10,1000),XL(10,1000)
      INTEGER       B(1001),UBB(1000)
      INTEGER       F(10),PBL(10),Q(10),V(10),S,U,UB,VB
      INTEGER       BS,PS,WS,XS
      COMMON /SNGL/ BS(1000),PS(1001),WS(1001),XS(1000)
      COMMON /PUB/  LX(1000),LXI(1000),LR,LRI,LUBI
      MAXN = 1000
      MAXM = 10
      Z = 0
      IF ( JCK .EQ. 1 ) CALL CHMTM(N,M,P,W,C,MAXN,MAXM,Z)
      IF ( Z .LT. 0 ) RETURN
      IF ( M .EQ. 1 ) GO TO 230
C
C STEP 1 (INITIALIZATION).
C
      JBACK = BACK
      BACK = 0
      KUB = 0
      N1 = N + 1
      B(N1) = 1
      M1 = M - 1
      DO 20 J=1,N
        B(J) = 1
        DO 10 I=1,M
          XC(I,J) = 0
          BB(I,J) = 0
   10   CONTINUE
   20 CONTINUE
      DO 30 I=1,M1
        Q(I) = C(I)
        F(I) = -1
   30 CONTINUE
      Q(M) = C(M)
      Z = 0
      VB = 0
      I = 1
      CALL SIGMA(N,M,P,W,C,1,B,KUB,UB)
      JUB = UB
      DO 40 J=1,N
        LXI(J) = LX(J)
   40 CONTINUE
      LRI = LR
      LUBI = UB
      IFLAG = 0
C
C STEP 2 (HEURISTIC).
C
   50 KUB = Z - VB
      CALL PI(N,M,P,W,Q,I,B,BB,KUB,BL,LB,PBL,V,XL)
      IF ( LB + VB .LE. Z ) GO TO 120
      Z = LB + VB
      DO 70 J=1,N
        X(J) = 0
        DO 60 S=1,I
          IF ( XC(S,J) .EQ. 0 ) GO TO 60
          X(J) = S
          GO TO 70
   60   CONTINUE
   70 CONTINUE
      IP = PBL(I)
      IF ( IP .EQ. 0 ) GO TO 90
      DO 80 J=1,IP
        JJ = BL(I,J)
        IF ( XL(I,J) .EQ. 1 ) X(JJ) = I
   80 CONTINUE
   90 I1 = I + 1
      DO 110 II=I1,M
        IP = PBL(II)
        IF ( IP .EQ. 0 ) GO TO 110
        DO 100 J=1,IP
          JJ = BL(II,J)
          IF ( XL(II,J) .EQ. 1 ) X(JJ) = II
  100   CONTINUE
  110 CONTINUE
      IF ( JBACK .EQ. 1 ) RETURN
      IF ( UB .EQ. LB ) GO TO 180
C
C STEP 3 (UPDATING).
C
  120 IF ( V(I) .EQ. 0 ) GO TO 160
      IUV = UB + VB
      U = PBL(I)
      IBV = 0
      DO 150 S=1,U
        IF ( XL(I,S) .EQ. 0 ) GO TO 150
        J = BL(I,S)
        XC(I,J) = 1
        Q(I) = Q(I) - W(J)
        VB = VB + P(J)
        B(J) = 0
        BB(I,J) = F(I)
        UBB(J) = IUV
        IF ( IFLAG .EQ. 1 ) GO TO 130
        LUB = IUV
        LJ = J
        LI = I
  130   F(I) = J
        IBV = IBV + P(J)
        IF ( IBV .EQ. V(I) ) GO TO 160
        CALL PAR(I,I,UB,IFLAG,VB,LUB,LJ,LI,F,BB,Q,B,N)
        IF ( IFLAG .EQ. 1 ) GO TO 140
        KUB = Z - VB
        CALL SIGMA(N,M,P,W,Q,I,B,KUB,UB)
        LJ = N1
  140   IUV = UB + VB
        IF ( IUV .LE. Z ) GO TO 180
  150 CONTINUE
  160 IF ( I .EQ. M - 1 ) GO TO 180
      IP1 = I + 1
      CALL PAR(IP1,I,UB,IFLAG,VB,LUB,LJ,LI,F,BB,Q,B,N)
      IF ( IFLAG .EQ. 1 ) GO TO 170
      KUB = Z - VB
      CALL SIGMA(N,M,P,W,Q,IP1,B,KUB,UB)
      LJ = N1
  170 IF ( UB + VB .LE. Z ) GO TO 180
      I = I + 1
      GO TO 120
C
C STEP 4 (BACKTRACKING).
C
  180 IF ( I .GT. 0 ) GO TO 190
      BACK = BACK - 1
      RETURN
  190 IF ( BACK .EQ. JBACK ) RETURN
      BACK = BACK + 1
      IF ( F(I) .NE. (-1) ) GO TO 210
      DO 200 J=1,N
        BB(I,J) = 0
  200 CONTINUE
      I = I - 1
      GO TO 180
  210 J = F(I)
      XC(I,J) = 0
      B(J) = 1
      VB = VB - P(J)
      Q(I) = Q(I) + W(J)
      DO 220 S=1,N
        IF ( BB(I,S) .EQ. J ) BB(I,S) = 0
  220 CONTINUE
      F(I) = BB(I,J)
      IF ( UBB(J) .LE. Z ) GO TO 180
      UB = UBB(J) - VB
      IFLAG = 1
      GO TO 50
C
C PARTICULAR CASE ( 0-1 SINGLE KNAPSACK PROBLEM).
C
  230 K1 = C(1)
      CALL SKP(N,P,W,K1,0,X,Z)
      BACK = 0
      RETURN
      END
      SUBROUTINE CHMTM(N,M,P,W,C,MAXN,MAXM,Z)
C
C CHECK THE INPUT DATA.
C
      INTEGER P(1000),W(1000),C(10),Z
      IF ( N .LE. 1 ) Z = - 1
      IF ( N .GT. MAXN ) Z = - 1
      IF ( M .LE. 0 ) Z = - 1
      IF ( M .GT. MAXM ) Z = - 1
      IF ( Z .LT. 0 ) RETURN
      MAXW = W(1)
      MINW = W(1)
      ISUMW = 0
      RR = P(1)
      DO 10 J=1,N
        IF ( P(J) .LE. 0 ) Z = - 2
        IF ( W(J) .LE. 0 ) Z = - 2
        IF ( Z .LT. 0 ) RETURN
        IF ( W(J) .GT. MAXW ) MAXW = W(J)
        IF ( W(J) .LT. MINW ) MINW = W(J)
        ISUMW = ISUMW + W(J)
        R = RR
        RR = FLOAT(P(J))/FLOAT(W(J))
        IF ( RR .LE. R ) GO TO 10
        Z = - 6
        RETURN
   10 CONTINUE
      IF ( C(1) .LE. 0 ) Z = - 2
      IF ( M .EQ. 1 ) GO TO 30
      DO 20 I=2,M
        IF ( C(I) .LE. 0 ) Z = - 2
        IF ( C(I) .GE. C(I-1) ) GO TO 20
        Z = - 7
        RETURN
   20 CONTINUE
   30 IF ( MINW .GT. C(1) ) Z = - 3
      IF ( MAXW .GT. C(M) ) Z = - 4
      IF ( ISUMW .LE. C(M) ) Z = - 5
      RETURN
      END
      SUBROUTINE PAR(I,II,UB,IFLAG,VB,LUB,LJ,LI,F,BB,Q,B,N)
C
C PARAMETRIC COMPUTATION OF THE UPPER BOUNDS.
C
      INTEGER      F(10),BB(10,1000),Q(10),B(1001),UB,VB,R,S
      COMMON /PUB/ LX(1000),LXI(1000),LR,LRI,LUBI
      IFLAG = 0
      IF ( B(LJ) .NE. 0 ) GO TO 60
      I1 = I - 1
      IF ( I1 .LT. LI ) GO TO 20
      IQ = 0
      DO 10 R=LI,I1
        IQ = IQ + Q(R)
   10 CONTINUE
      IF ( IQ .GT. LR ) RETURN
   20 R = II
      S = F(R)
   30 IF ( S .NE. (-1) ) GO TO 40
      R = R - 1
      S = F(R)
      GO TO 30
   40 IF ( LX(S) .EQ. 0 ) RETURN
      IF ( S .EQ. LJ ) GO TO 50
      S = BB(R,S)
      GO TO 30
   50 UB = LUB - VB
      IFLAG = 1
      RETURN
   60 I1 = I - 1
      IF ( I1 .LT. 1 ) GO TO 80
      IQ = 0
      DO 70 R=1,I1
        IQ = IQ + Q(R)
   70 CONTINUE
      IF ( IQ .GT. LRI ) RETURN
   80 DO 90 J=1,N
        IF ( B(J) .EQ. 1 ) GO TO 90
        IF ( LXI(J) .EQ. 0 ) RETURN
   90 CONTINUE
      UB = LUBI - VB
      IFLAG = 1
      RETURN
      END
      SUBROUTINE PI(N,M,P,W,Q,I,B,BB,KUB,BL,LB,PBL,V,XL)
C
C COMPUTE A FEASIBLE SOLUTION TO THE CURRENT PROBLEM.
C THE SOLUTION IS STORED IN ARRAY  XL , THE CORRESPONDING
C VALUE IN  LB .
C
      INTEGER       BB(10,1000),BL(10,1001),XL(10,1000)
      INTEGER       P(1000),W(1000),Q(10),B(1001),PBL(10),V(10)
      INTEGER       BS,PB,PS,QS,SB,U,WS,XS
      COMMON /SNGL/ BS(1000),PS(1001),WS(1001),XS(1000)
C
C STEP 1.
C
      U = 0
      DO 10 J=1,N
        IF ( B(J) .EQ. 0 ) GO TO 10
        U = U + 1
        BS(U) = J
   10 CONTINUE
      DO 20 J=I,M
        PBL(J) = 0
        V(J) = 0
   20 CONTINUE
      LB = 0
      IKUB = KUB
      IF ( U .EQ. 0 ) RETURN
      NS = 0
      SB = 0
      DO 30 J=1,U
        JJ = BS(J)
        IF ( BB(I,JJ) .NE. 0 ) GO TO 30
        IF ( W(JJ) .GT. Q(I) ) GO TO 30
        NS = NS + 1
        SB = SB + W(JJ)
        BL(I,NS) = JJ
        PS(NS) = P(JJ)
        WS(NS) = W(JJ)
   30 CONTINUE
      II = I
C
C STEP 2.
C
   40 PBL(II) = NS
      IF ( SB .GT. Q(II) ) GO TO 60
      PB = 0
      IF ( NS .EQ. 0 ) GO TO 80
      DO 50 J=1,NS
        PB = PB + PS(J)
        XL(II,J) = 1
   50 CONTINUE
      GO TO 80
   60 QS = Q(II)
      KUB = 0
      IF ( II .EQ. M ) KUB = IKUB
      CALL SKP(NS,PS,WS,QS,KUB,XS,PB)
      DO 70 J=1,NS
        XL(II,J) = XS(J)
   70 CONTINUE
   80 LB = LB + PB
      IKUB = IKUB - PB
      V(II) = PB
      BL(II,NS+1) = N + 1
C
C STEP 3.
C
      IF ( II .EQ. M ) RETURN
      JB = 1
      JBS = 0
      DO 100 J=1,U
        IF ( BS(J) .LT. BL(II,JB) ) GO TO 90
        JB = JB + 1
        IF ( XL(II,JB-1) .EQ. 1 ) GO TO 100
   90   JBS = JBS + 1
        BS(JBS) = BS(J)
  100 CONTINUE
      U = JBS
      IF ( U .EQ. 0 ) RETURN
      NS = 0
      SB = 0
      II = II + 1
      DO 110 J=1,U
        JJ = BS(J)
        IF( W(JJ) .GT. Q(II) ) GO TO 110
        NS = NS + 1
        SB = SB + W(JJ)
        BL(II,NS) = JJ
        PS(NS) = P(JJ)
        WS(NS) =  W(JJ)
  110 CONTINUE
      GO TO 40
      END
      SUBROUTINE SIGMA(N,M,P,W,Q,I,B,KUB,UB)
C
C COMPUTE AN UPPER BOUND  UB  ON THE BEST FINAL SOLUTION WHICH
C CAN BE OBTAINED FROM THE CURRENT SOLUTION.
C
      INTEGER       P(1000),W(1000),Q(10),B(1001),UB
      INTEGER       BS,PS,QS,SB,WS,XS
      COMMON /SNGL/ BS(1000),PS(1001),WS(1001),XS(1000)
      COMMON /PUB/  LX(1000),LXI(1000),LR,LRI,LUBI
      NS = 0
      QS = 0
      DO 10 J=I,M
        QS = QS + Q(J)
   10 CONTINUE
      SB = 0
      DO 20 J=1,N
        LX(J) = 0
        IF ( B(J) .EQ. 0 ) GO TO 20
        NS = NS + 1
        BS(NS) = J
        PS(NS) = P(J)
        WS(NS) = W(J)
        SB = SB + W(J)
   20 CONTINUE
      IF ( SB .GT. QS ) GO TO 40
      LR = QS - SB
      UB = 0
      IF ( NS .EQ. 0 ) RETURN
      DO 30 J=1,NS
        UB = UB + PS(J)
        XS(J) = 1
   30 CONTINUE
      GO TO 50
   40 CALL SKP(NS,PS,WS,QS,KUB,XS,UB)
      LR = QS
   50 DO 60 J=1,NS
        JJ = BS(J)
        LX(JJ) = XS(J)
   60 CONTINUE
      RETURN
      END
      SUBROUTINE SKP(NS,PS,WS,QS,KUB,XS,VS)
C
C SUBROUTINE TO SOLVE THE 0-1 SINGLE KNAPSACK PROBLEM
C
C MAXIMIZE    VS = PS(1)*XS(1) + ... + PS(NS)*XS(NS)
C SUBJECT TO:      WS(1)*XS(1) + ... + WS(NS)*XS(NS) .LE. QS ,
C                  XS(J) = 0 OR 1  FOR J=1,...,NS,
C                  VS .GT. KUB .
C
C THIS SUBROUTINE IS A MODIFIED VERSION OF SUBROUTINE MT1.
C
      INTEGER PS(1001),WS(1001),XS(1000),QS,VS
      INTEGER D(1000),MIN(1000),PBAR(1000),WBAR(1000),ZBAR(1000)
      INTEGER DIFF,PR,R,T
      VS = KUB
      IP = 0
      MS = QS
      DO 10 L=1,NS
        LL = L
        IF ( WS(L) .GT. MS ) GO TO 20
        IP = IP + PS(L)
        MS = MS - WS(L)
   10 CONTINUE
   20 LL = LL - 1
      IF ( MS .EQ. 0 ) GO TO 50
      PS(NS+1) = 0
      WS(NS+1) = QS + 1
      LIM = IP + MS*PS(LL+2)/WS(LL+2)
      A = IP + PS(LL+1)
      B = (WS(LL+1) - MS)*PS(LL)
      C = WS(LL)
      LIM1 = A - B/C
      IF ( LIM1 .GT. LIM ) LIM = LIM1
      IF ( LIM .LE. VS ) RETURN
      MINK = QS + 1
      MIN(NS) = MINK
      DO 30 J=2,NS
        KK = NS + 2 - J
        IF ( WS(KK) .LT. MINK ) MINK = WS(KK)
        MIN(KK-1) = MINK
   30 CONTINUE
      DO 40 J=1,NS
        D(J) = 0
   40 CONTINUE
      PR = 0
      LOLD = NS
      II = 1
      GO TO 170
   50 IF ( VS .GE. IP ) RETURN
      VS = IP
      DO 60 J=1,LL
        XS(J) = 1
   60 CONTINUE
      NN = LL + 1
      DO 70 J=NN,NS
        XS(J) = 0
   70 CONTINUE
      QS = 0
      RETURN
   80 IF ( WS(II) .LE. QS ) GO TO 90
      II1 = II + 1
      IF ( VS .GE. QS*PS(II1)/WS(II1) + PR ) GO TO 280
      II = II1
      GO TO 80
   90 IP = PBAR(II)
      MS = QS - WBAR(II)
      IN = ZBAR(II)
      LL = NS
      IF ( IN .GT. NS ) GO TO 110
      DO 100 L=IN,NS
        LL = L
        IF ( WS(L) .GT. MS ) GO TO 160
        IP = IP + PS(L)
        MS = MS - WS(L)
  100 CONTINUE
  110 IF ( VS .GE. IP + PR ) GO TO 280
      VS = IP + PR
      MFIRST = MS
      NN = II - 1
      DO 120 J=1,NN
        XS(J) = D(J)
  120 CONTINUE
      DO 130 J=II,LL
        XS(J) = 1
  130 CONTINUE
      IF ( LL .EQ. NS ) GO TO 150
      NN = LL + 1
      DO 140 J=NN,NS
        XS(J) = 0
  140 CONTINUE
  150 IF ( VS .NE. LIM ) GO TO 280
      QS = MFIRST
      RETURN
  160 L = LL
      LL = LL - 1
      IF ( MS .EQ. 0 ) GO TO 110
      IF ( VS .GE. PR + IP + MS*PS(L)/WS(L) ) GO TO 280
  170 WBAR(II) = QS - MS
      PBAR(II) = IP
      ZBAR(II) = LL + 1
      D(II) = 1
      NN = LL - 1
      IF ( NN .LT. II ) GO TO 190
      DO 180 J=II,NN
        WBAR(J+1) = WBAR(J) - WS(J)
        PBAR(J+1) = PBAR(J) - PS(J)
        ZBAR(J+1) = LL + 1
        D(J+1) = 1
  180 CONTINUE
  190 J1 = LL + 1
      DO 200 J=J1,LOLD
        WBAR(J) = 0
        PBAR(J) = 0
        ZBAR(J) = J
  200 CONTINUE
      LOLD = LL
      QS = MS
      PR = PR + IP
      IF ( LL - (NS - 2) ) 240, 220, 210
  210 II = NS
      GO TO 250
  220 IF ( QS .LT. WS(NS) ) GO TO 230
      QS = QS - WS(NS)
      PR = PR + PS(NS)
      D(NS) = 1
  230 II = NS - 1
      GO TO 250
  240 II = LL + 2
      IF ( QS .GE. MIN(II-1) ) GO TO 80
  250 IF ( VS .GE. PR ) GO TO 270
      VS = PR
      DO 260 J=1,NS
        XS(J) = D(J)
  260 CONTINUE
      MFIRST = QS
      IF ( VS .EQ. LIM ) RETURN
  270 IF ( D(NS) .EQ. 0 ) GO TO 280
      D(NS) = 0
      QS = QS + WS(NS)
      PR = PR - PS(NS)
  280 NN = II - 1
      IF ( NN .EQ. 0 ) GO TO 300
      DO 290 J=1,NN
        KK = II - J
        IF ( D(KK) .EQ. 1 ) GO TO 310
  290 CONTINUE
  300 QS = MFIRST
      RETURN
  310 R = QS
      QS = QS + WS(KK)
      PR = PR - PS(KK)
      D(KK) = 0
      IF ( R .LT. MIN(KK) ) GO TO 320
      II = KK + 1
      GO TO 80
  320 NN = KK + 1
      II = KK
  330 IF ( VS .GE. PR + QS*PS(NN)/WS(NN) ) GO TO 280
      DIFF = WS(NN) - WS(KK)
      IF ( DIFF ) 390, 340, 350
  340 NN = NN + 1
      GO TO 330
  350 IF ( DIFF .GT. R ) GO TO 340
      IF ( VS .GE. PR + PS(NN) ) GO TO 340
      VS = PR + PS(NN)
      DO 360 J=1,KK
        XS(J) = D(J)
  360 CONTINUE
      JJ = KK + 1
      DO 370 J=JJ,NS
        XS(J) = 0
  370 CONTINUE
      XS(NN) = 1
      MFIRST = QS - WS(NN)
      IF ( VS .NE. LIM ) GO TO 380
      QS = MFIRST
      RETURN
  380 R = R - DIFF
      KK = NN
      NN = NN + 1
      GO TO 330
  390 T = R - DIFF
      IF ( T .LT. MIN(NN) ) GO TO 340
      N = NN + 1
      IF ( VS .GE. PR + PS(NN) + T*PS(N)/WS(N) ) GO TO 280
      QS = QS - WS(NN)
      PR = PR + PS(NN)
      D(NN) = 1
      II = NN + 1
      WBAR(NN) = WS(NN)
      PBAR(NN) = PS(NN)
      ZBAR(NN) = II
      N1 = NN + 1
      DO 400 J=N1,LOLD
        WBAR(J) = 0
        PBAR(J) = 0
        ZBAR(J) = J
  400 CONTINUE
      LOLD = NN
      GO TO 80
      END
