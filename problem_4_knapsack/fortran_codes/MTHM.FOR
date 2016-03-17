      SUBROUTINE MTHM(N,M,P,W,C,Z,X,JDN,JDM,LI,JCK,CR,MIN,XX,X1,F)
C
C THIS SUBROUTINE HEURISTICALLY SOLVES THE 0-1 MULTIPLE KNAPSACK
C PROBLEM
C
C MAXIMIZE  Z = P(1)*(Y(1,1) + ... + Y(M,1)) +
C                              ...           +
C               P(N)*(Y(1,N) + ... + Y(M,N))
C SUBJECT TO:
C
C   W(1)*Y(I,1) + ... + W(N)*Y(I,N) .LE. C(I)   FOR I=1,...,M,
C   Y(1,J) + ... + Y(M,J) .LE. 1                FOR J=1,...,N,
C   Y(I,J) = 0 OR 1                  FOR I=1,...,M, J=1,...,N.
C
C THE PROGRAM IS INCLUDED IN THE VOLUME
C   S. MARTELLO, P. TOTH, "KNAPSACK PROBLEMS: ALGORITHMS
C   AND COMPUTER IMPLEMENTATIONS", JOHN WILEY, 1990
C AND IMPLEMENTS THE POLYNOMIAL-TIME ALGORITHMS DESCRIBED
C IN SECTION  6.6.2 .
C THE PROGRAM DERIVES FROM AN EARLIER CODE PRESENTED IN
C   S. MARTELLO, P. TOTH, "HEURISTIC ALGORITHMS FOR THE
C   MULTIPLE KNAPSACK PROBLEM", COMPUTING, 1981.
C
C THE INPUT PROBLEM MUST SATISFY THE CONDITIONS
C
C   1) 2 .LE. N .LE. JDN - 1  AND  1 .LE. M .LE. JDM - 1 ;
C   2) P(J), W(J) AND C(I) POSITIVE INTEGERS;
C   3) MIN (C(I)) .GE. MIN (W(J));
C   4) MAX (W(J)) .LE. MAX (C(I));
C   5) MAX (C(I)) .LT. W(1) + ... + W(N);
C   6) P(J)/W(J) .GE. P(J+1)/W(J+1) FOR J=1,...,N-1;
C   7) C(I) .LE. C(I+1) FOR I=1,...,M-1.
C
C MTHM CAN CALL 6 SUBROUTINES:
C   CHMTHM TO CHECK THE INPUT DATA;
C   MGR1 OR MGR2 TO FIND AN INITIAL FEASIBLE SOLUTION;
C   REARR TO RE-ARRANGE A FEASIBLE SOLUTION;
C   IMPR1 AND IMPR2 TO IMPROVE ON A FEASIBLE SOLUTION.
C THE USER SELECTS THE SEQUENCE OF CALLS THROUGH INPUT PARAMETERS.
C
C THE PROGRAM IS COMPLETELY SELF-CONTAINED AND COMMUNICATION TO IT
C IS ACHIEVED SOLELY THROUGH THE PARAMETER LIST OF MTHM.
C THE ONLY MACHINE-DEPENDENT CONSTANT IS USED TO DEFINE  INF  (FIRST
C EXECUTABLE STATEMENT), WHICH MUST BE SET TO A LARGE POSITIVE
C INTEGER VALUE.
C THE PROGRAM IS WRITTEN IN 1967 AMERICAN NATIONAL STANDARD FORTRAN
C AND IS ACCEPTED BY THE PFORT VERIFIER (PFORT IS THE PORTABLE
C SUBSET OF ANSI DEFINED BY THE ASSOCIATION FOR COMPUTING MACHINERY).
C THE PROGRAM HAS BEEN TESTED ON A DIGITAL VAX 11/780 AND AN H.P.
C 9000/840.
C
C MTHM NEEDS
C   6  ARRAYS ( P ,  W ,  X ,  MIN ,  XX  AND  X1 ) OF LENGTH AT
C               LEAST  JDN ;
C   2  ARRAYS ( C  AND  CR ) OF LENGTH AT LEAST  JDM ;
C   1  ARRAY  ( F ) OF LENGTH AT LEAST  JDM X JDM .
C IN ADDITION, SUBROUTINE MGR2 USES
C   7  ARRAYS OF LENGTH  5 ;
C   1  ARRAY  OF LENGTH  201 ;
C   1  ARRAY  OF LENGTH  5 * 200 ;
C SUBROUTINE MGR2 IS CALLED ONLY WHEN  M .LE. 5  AND  N .LE. 200 .
C
C MEANING OF THE INPUT PARAMETERS:
C N    = NUMBER OF ITEMS;
C M    = NUMBER OF KNAPSACKS;
C P(J) = PROFIT OF ITEM  J  (J=1,...,N);
C W(J) = WEIGHT OF ITEM  J  (J=1,...,N);
C C(I) = CAPACITY OF KNAPSACK  I  (I=1,...,M);
C JDN  = DIMENSION OF ARRAYS  P ,  W ,  X ,  MIN ,  XX  AND  X1 ;
C JDM  = DIMENSION OF ARRAYS  C ,  CR  AND  F ;
C LI   = 0 TO OUTPUT THE INITIAL FEASIBLE SOLUTION,
C      = 1 TO ALSO PERFORM SUBROUTINES REARR AND IMPR1,
C      = 2 TO ALSO PERFORM SUBROUTINES REARR, IMPR1 AND IMPR2;
C JCK  = 1 IF CHECK ON THE INPUT DATA IS DESIRED,
C      = 0 OTHERWISE.
C
C MEANING OF THE OUTPUT PARAMETERS:
C Z     = VALUE OF THE SOLUTION FOUND IF  Z .GT. 0 ,
C       = ERROR IN THE INPUT DATA (WHEN JCK=1) IF  Z .LT. 0 :
C         CONDITION -Z IS VIOLATED;
C X(J)  = 0  IF ITEM  J  IS NOT IN THE SOLUTION FOUND
C         (I.E. IF  Y(I,J) = 0  FOR ALL  I ),
C       = KNAPSACK WHERE ITEM  J  IS INSERTED, OTHERWISE
C         (I.E. IF  Y(X(J),J) = 1 ).
C
C ARRAYS CR, MIN, XX, X1 AND F ARE DUMMY.
C
C ALL THE PARAMETERS ARE INTEGER. ON RETURN OF MTHM ALL THE
C INPUT PARAMETERS ARE UNCHANGED.
C
      INTEGER P(JDN),W(JDN),X(JDN),C(JDM),Z
      INTEGER MIN(JDN),XX(JDN),X1(JDN),CR(JDM),F(JDM,JDM),Z1
      INF = 999999999
      Z = 0
      IF ( JCK .EQ. 1 ) CALL CHMTHM(N,M,P,W,C,JDN,JDM,Z)
      IF ( Z .LT. 0 ) RETURN
      IF ( M .LE. 5 .AND. N .LE. 200 ) GO TO 10
      CALL MGR1(N,P,W,M,C,Z,X,CR,INF,JDN,JDM)
      GO TO 20
   10 CALL MGR2(N,P,W,M,C,Z,X,CR,INF,JDN,JDM)
   20 IF ( LI .EQ. 0 ) GO TO 60
      Z1 = Z
      DO 30 J=1,N
        X1(J) = X(J)
   30 CONTINUE
      CALL REARR(N,P,W,M,C,Z,X,CR,INF,JDN,JDM)
      CALL IMPR1(N,P,W,M,Z,X,CR,INF,JDN,JDM,F)
      IF ( LI .EQ. 1 ) GO TO 40
      CALL IMPR2(N,P,W,M,Z,X,CR,MIN,XX,INF,JDN,JDM)
   40 IF ( Z .GE. Z1 ) GO TO 60
      Z = Z1
      DO 50 J=1,N
        X(J) = X1(J)
   50 CONTINUE
   60 DO 70 J=1,N
        IF ( X(J) .GT. M ) X(J) = 0
   70 CONTINUE
      RETURN
      END
      SUBROUTINE CHMTHM(N,M,P,W,C,JDN,JDM,Z)
C
C CHECK THE INPUT DATA.
C
      INTEGER P(JDN),W(JDN),C(JDM),Z
      IF ( N .LE. 1 ) Z = - 1
      IF ( N .GE. JDN ) Z = - 1
      IF ( M .LE. 0 ) Z = - 1
      IF ( M .GE. JDM ) Z = - 1
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
      SUBROUTINE IMPR1(N,P,W,M,Z,X,CR,INF,JDN,JDM,F)
C
C FIRST IMPROVEMENT.
C
      INTEGER P(JDN),W(JDN),X(JDN),CR(JDM),Z
      INTEGER F(JDM,JDM),CP,WP,FF,U,T,Q,R,S,D
      MP1 = M + 1
      CR(MP1) = 0
      MAXF = 0
      CP = 0
      DO 20 I=1,M
        IP1 = I + 1
        DO 10 J=IP1,MP1
          F(I,J) = CR(I) + CR(J)
          F(J,I) = F(I,J)
          IF ( F(I,J) .LE. MAXF ) GO TO 10
          MAXF = F(I,J)
          IP = I
          JP = J
   10   CONTINUE
        F(I,I) = 0
        IF ( CP .LT. CR(I) ) CP = CR(I)
   20 CONTINUE
      F(MP1,MP1) = 0
      DO 30 J=1,N
        IF ( X(J) .LT. MP1 ) GO TO 30
        FF = J
        GO TO 40
   30 CONTINUE
      RETURN
   40 WP = W(FF)
      IF ( FF .EQ. N ) GO TO 60
      IF1 = FF + 1
      DO 50 J=IF1,N
        IF ( X(J) .LT. MP1 ) GO TO 50
        IF ( W(J) .LT. WP ) WP = W(J)
   50 CONTINUE
   60 IF ( F(IP,JP) .LT. WP ) RETURN
      J = 1
   70 IXJ = X(J)
      IF ( CR(IXJ) + CP .LT. WP ) GO TO 230
      K = J + 1
   80 IF ( K .GT. N ) GO TO 230
      IXJ = X(J)
      IXK = X(K)
      IF ( F(IXJ,IXK) .LT. WP ) GO TO 120
      IF ( W(J) - W(K) ) 90,120,100
   90 U = K
      T = J
      GO TO 110
  100 U = J
      T = K
  110 D = W(U) - W(T)
      I = X(U)
      IXT = X(T)
      IF ( D .GT. CR(IXT) )GO TO 120
      IF ( CR(I) + D .GE. WP ) GO TO 130
  120 K = K + 1
      GO TO 80
  130 ICIPD = CR(I) + D
      MAXP = 0
      DO 140 Q=FF,N
        IF ( X(Q) .LT. MP1 ) GO TO 140
        IF ( W(Q) .GT. ICIPD ) GO TO 140
        IF ( P(Q) .LE. MAXP ) GO TO 140
        R = Q
        MAXP = P(R)
  140 CONTINUE
      CR(I) = CR(I) + D - W(R)
      CR(IXT) = CR(IXT) - D
      Z = Z + P(R)
      DO 150 Q=1,M
        F(I,Q) = CR(I) + CR(Q)
        F(Q,I) = F(I,Q)
        F(IXT,Q) = CR(IXT) + CR(Q)
        F(Q,IXT) = F(IXT,Q)
  150 CONTINUE
      F(I,I) = 0
      F(IXT,IXT) = 0
      IF ( I .EQ. IP ) GO TO 160
      IF ( I .EQ. JP ) GO TO 160
      IF ( IXT .EQ. IP ) GO TO 160
      IF ( IXT .NE. JP ) GO TO 190
  160 MAXF = 0
      DO 180 Q=1,M
        IP1 = Q + 1
        DO 170 S=IP1,MP1
          IF ( F(Q,S) .LE. MAXF ) GO TO 170
          MAXF = F(Q,S)
          IP = Q
          JP = S
  170   CONTINUE
  180 CONTINUE
  190 X(R) = I
      X(U) = IXT
      X(T) = I
      IF ( W(R) .NE. WP ) GO TO 210
      WP = INF
      DO 200 S=FF,N
        IF ( X(S) .LT. MP1 ) GO TO 200
        IF ( W(S) .LT. WP ) WP = W(S)
  200 CONTINUE
  210 IF ( F(IP,JP) .LT. WP ) RETURN
      CP = 0
      DO 220 S=1,M
        IF ( CP .LT. CR(S) ) CP = CR(S)
  220 CONTINUE
      IXJ = X(J)
      IF ( CR(IXJ) + CP .LT. WP ) GO TO 230
      K = K + 1
      GO TO 80
  230 IF ( J .EQ. N ) RETURN
      J = J + 1
      GO TO 70
      END
      SUBROUTINE IMPR2(N,P,W,M,Z,X,CR,MIN,XX,INF,JDN,JDM)
C
C SECOND IMPROVEMENT.
C
      INTEGER P(JDN),W(JDN),X(JDN),MIN(JDN),XX(JDN),CR(JDM),Z
      INTEGER F,T,V,CB,U,S
      MP1 = M + 1
      MINK = INF
      MIN(N) = MINK
      DO 10 I=2,N
        KK = N + 2 - I
        IF ( W(KK) .LT. MINK ) MINK = W(KK)
        MIN(KK-1) = MINK
   10 CONTINUE
      DO 20 J=1,N
        IF ( X(J) .LE. M ) GO TO 20
        F = J
        GO TO 30
   20 CONTINUE
      RETURN
   30 S = N
      J = N
   40 IF ( X(J) .EQ. MP1 ) GO TO 140
      IXJ = X(J)
      CB = CR(IXJ) + W(J)
      IF ( CB*P(F)/W(F) .LE. P(J) ) GO TO 140
      IF ( CB .GE. W(F) ) GO TO 50
      IF ( CB .LT. MIN(F) ) GO TO 140
   50 K = F
      T = 0
      V = 0
   60 IF ( W(K) .GT. CB ) GO TO 70
      V = V + P(K)
      CB = CB - W(K)
      T = T + 1
      XX(T) = K
      IF ( CB .LT. MIN(K) ) GO TO 100
   70 IF ( K .EQ. N ) GO TO 100
      K1 = K + 1
      DO 80 U=K1,N
        IF ( X(U) .LE. M ) GO TO 80
        K = U
        GO TO 90
   80 CONTINUE
      GO TO 100
   90 IF ( V + CB*P(K)/W(K) .GT. P(J) ) GO TO 60
  100 IF ( V .LE. P(J) ) GO TO 140
      S = J
      IXJ = X(J)
      CR(IXJ) = CB
      DO 110  K=1,T
        IXXK = XX(K)
        X(IXXK) = X(J)
  110 CONTINUE
      X(J) = MP1
      Z = Z + V - P(J)
      IF ( J .GT. F ) GO TO 120
      F = J
      GO TO 140
  120 IF ( X(F) .EQ. MP1 ) GO TO 140
      IF1 = F + 1
      DO 130 U=IF1,N
        IF ( X(U) .LE. M ) GO TO 130
        F = U
        GO TO 140
  130 CONTINUE
  140 J = J - 1
      IF ( J .EQ. 0 ) J = N
      IF ( J .EQ. S ) RETURN
      GO TO  40
      END
      SUBROUTINE MGR1(N,P,W,M,C,Z,X,CR,INF,JDN,JDM)
C
C FIND AN INITIAL SOLUTION (QUICK ALGORITHM).
C
      INTEGER P(JDN),W(JDN),C(JDM),X(JDN),CR(JDM),Z
      DO 10 I=1,M
        CR(I) = C(I)
   10 CONTINUE
      MP1 = M + 1
      P(N+1) = 0
      W(N+1) = INF
      J = 1
      I = 1
      Z = 0
   20 IF ( W(J) .GT. CR(I) ) GO TO 30
      X(J) = I
      CR(I) = CR(I) - W(J)
      Z = Z + P(J)
      J = J + 1
      GO TO 20
   30 JS = J
      X(J) = MP1
      J = J + 1
      DO 40 JJ=J,N
        X(JJ) = MP1
        IF ( W(JJ) .GT. CR(I) ) GO TO 40
        X(JJ) = I
        CR(I) = CR(I) - W(JJ)
        Z = Z + P(JJ)
   40 CONTINUE
   50 IF ( I .LT. M ) GO TO 60
      GO TO 110
   60 I = I + 1
      DO 70 J=JS,N
        IF ( X(J) .LE. M ) GO TO 70
        IF ( W(J) .GT. CR(I) ) GO TO 80
        X(J) = I
        CR(I) = CR(I) - W(J)
        Z = Z + P(J)
   70 CONTINUE
      GO TO 110
   80 JS = J
      J = J + 1
   90 IF ( CR(I)*P(J)/W(J) .EQ. 0 ) GO TO 50
      IF ( X(J) .LE. M ) GO TO 100
      IF ( W(J) .GT. CR(I) ) GO TO 100
      X(J) = I
      CR(I) = CR(I) - W(J)
      Z = Z + P(J)
  100 J = J + 1
      GO TO 90
  110 CONTINUE
      RETURN
      END
      SUBROUTINE MGR2(N,P,W,M,C,Z,X,CR,INF,JDN,JDM)
C
C FIND AN INITIAL SOLUTION (ACCURATE ALGORITHM).
C
      INTEGER P(JDN),W(JDN),C(JDM),X(JDN),CR(JDM),Z
      INTEGER S,D,ZCAP,VZCAP,CZCAP,VCAP,ZSTAR,VZSTAR,CZSTAR,Q
      INTEGER A(5,200),V(5),ZZ(5),CZ(5),VZ(5),OZ(5),B(5),IFB(5),
     1        MINW(201)
      Z = 0
      JSTAR = 1
      P(N+1) = 0
      W(N+1) = INF
      MP1 = M + 1
      MINK = INF
      MINW(N+1) = MINK
      DO 20 J=1,N
        X(J) = MP1
        KK = N + 1 - J
        IF ( W(KK) .LT. MINK ) MINK = W(KK)
        MINW(KK) = MINK
        DO 10 I=1,M
          A(I,J) = 0
   10   CONTINUE
   20 CONTINUE
      X(N+1) = MP1
      DO 30 I=1,M
        ZZ(I) = 1
        CZ(I) = C(I)
        VZ(I) = 0
        OZ(I) = 0
        B(I) = I
   30 CONTINUE
      IBOUND = 0
      KB = 0
      MB = M
   40 IF ( KB .EQ. MB ) GO TO 170
      KB = KB + 1
      I = B(KB)
      IF ( IBOUND .EQ. 0) GO TO 50
      ZCAP = ZZ(I)
      VZCAP = VZ(I)
      CZCAP = CZ(I)
      VCAP = V(I)
      IF ( S .GE. ZZ(I) ) GO TO 50
      VZ(I) = VZ(I) - P(S)
      CZ(I) = CZ(I) + W(S)
   50 J = ZZ(I)
      CR(I) = CZ(I)
      V(I) = VZ(I)
   60 IF ( CR(I) .LT. MINW(J) ) GO TO 70
      IF ( CR(I)*P(J)/W(J) .GE. 1 ) GO TO 80
   70 ZZ(I) = J
      CZ(I) = CR(I)
      VZ(I) = V(I)
      GO TO 140
   80 IF ( W(J) .GT. CR(I) ) GO TO 90
      CR(I) = CR(I) - W(J)
      V(I) = V(I) + P(J)
      A(I,J) = 1
      IOZ = J
      J = J + 1
      GO TO 60
   90 IF ( J .NE. JSTAR ) GO TO 100
      A(I,J) = 0
      J = J + 1
      GO TO 60
  100 ZZ(I) = J
      CZ(I) = CR(I)
      VZ(I) = V(I)
  110 IF ( CR(I) .LT. MINW(J) ) GO TO 140
      IF ( CR(I)*P(J)/W(J) .LT. 1 ) GO TO 140
      IF ( W(J) .GT. CR(I) ) GO TO 120
      CR(I) = CR(I) - W(J)
      V(I) = V(I) + P(J)
      A(I,J) = 1
      IOZ = J
      GO TO 130
  120 A(I,J) = 0
  130 J = J + 1
      GO TO 110
  140 JO = OZ(I)
      IF ( JO .LT. J ) GO TO 160
      DO 150 Q=J,JO
        A(I,Q) = 0
  150 CONTINUE
  160 OZ(I) = IOZ
      IF ( IBOUND .EQ. 0 ) GO TO 40
      IF ( VCAP - V(I) .LE. D ) GO TO 40
      D = VCAP - V(I)
      ISTAR = I
      ZSTAR = ZCAP
      VZSTAR = VZCAP
      CZSTAR = CZCAP
      GO TO 40
  170 IF ( IBOUND .EQ. 1 ) GO TO 180
      J = JSTAR
      GO TO 210
  180 Z = Z + P(S)
      X(S) = ISTAR
  190 IF ( X(JSTAR) .EQ. MP1 ) GO TO 200
      JSTAR = JSTAR + 1
      GO TO 190
  200 MB = 0
      KB = 0
      IBOUND = 0
      I = ISTAR
      ZZ(I) = ZSTAR
      VZ(I) = VZSTAR
      CZ(I) = CZSTAR
      GO TO 50
  210 IF ( J .GT. N ) RETURN
      MB = 0
      DO 220 I=1,M
        IFB(I) = 0
        IF ( A(I,J) .EQ. 0 ) GO TO 220
        MB = MB + 1
        B(MB) = I
        IFB(I) = 1
  220 CONTINUE
      KB = 0
      IF ( MB .LE. 1 ) GO TO 240
      IBOUND = 1
      S = J
      D = - INF
      JSTAR = J + 1
      DO 230 I=1,M
        IF ( ZZ(I) .GE. JSTAR ) GO TO 230
        ZZ(I) = JSTAR
        IF ( IFB(I) .EQ. 0 ) GO TO 230
        VZ(I) = VZ(I) + P(S)
        CZ(I) = CZ(I) - W(S)
  230 CONTINUE
      GO TO 40
  240 IF ( MB .EQ. 0 ) GO TO 250
      I = B(1)
      Z = Z + P(J)
      X(J) = I
      IF ( J .LT. ZZ(I) ) GO TO 250
      ZZ(I) = J + 1
      CZ(I) = CZ(I) - W(J)
      VZ(I) = VZ(I) + P(J)
  250 J = J + 1
      GO TO 210
      END
      SUBROUTINE REARR(N,P,W,M,C,Z,X,CR,INF,JDN,JDM)
C
C RE-ARRANGE THE INITIAL SOLUTION.
C
      INTEGER P(JDN),W(JDN),C(JDM),X(JDN),CR(JDM),Z
      Z = 0
      I = 1
      J = N
      IBAR = 1
      DO 10 KK=1,M
        CR(KK) = C(KK)
   10 CONTINUE
      MP1 = M + 1
      P(N+1) = 0
      W(N+1) = INF
   20 IF ( X(J) .EQ. MP1 ) GO TO 40
      IF ( W(J) .GT. CR(I) ) GO TO 30
      X(J) = I
      CR(I) = CR(I) - W(J)
      Z = Z + P(J)
      GO TO 40
   30 I = I + 1
      IF ( I .GT. M ) I = 1
      IF ( I .NE. IBAR ) GO TO 20
      X(J) = MP1
      I = I - 1
   40 J = J - 1
      IF ( J .EQ. 0 ) GO TO 50
      I = I + 1
      IF ( I .GT. M ) I = 1
      IBAR = I
      GO TO 20
   50 MAXC = CR(1)
      IMAXC = 1
      DO 60 I=2,M
        IF ( CR(I) .LE. MAXC ) GO TO 60
        MAXC = CR(I)
        IMAXC = I
   60 CONTINUE
      DO 80 J=1,N
        IF ( X(J) .LT. MP1 ) GO TO 80
        IF ( W(J) .GT. MAXC ) GO TO 80
        CR(IMAXC) = CR(IMAXC) - W(J)
        Z = Z + P(J)
        X(J) = IMAXC
        MAXC = CR(1)
        IMAXC = 1
        DO 70 I=2,M
          IF ( CR(I) .LE. MAXC ) GO TO 70
          MAXC = CR(I)
          IMAXC = I
   70   CONTINUE
   80 CONTINUE
      RETURN
      END
