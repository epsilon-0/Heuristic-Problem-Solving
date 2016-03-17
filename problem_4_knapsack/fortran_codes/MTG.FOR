      SUBROUTINE MTG(N,M,P,W,C,MINMAX,Z,XSTAR,BACK,JCK,JB)
C
C THIS SUBROUTINE SOLVES THE GENERALIZED ASSIGNMENT PROBLEM
C
C OPT Z = P(1,1)*X(1,1) + ... + P(1,N)*X(1,N) +
C                         ...                 +
C         P(M,1)*X(M,1) + ... + P(M,N)*X(M,N)
C
C     (WHERE  OPT = MIN  IF  MINMAX = 1 ,  OPT = MAX  IF  MINMAX = 2 )
C
C SUBJECT TO:
C
C       W(I,1)*X(I,1) + ... + W(I,N)*X(I,N) .LE. C(I)  FOR I=1,...,M,
C       X(1,J) + ... + X(M,J) = 1                      FOR J=1,...,N,
C       X(I,J) = 0 OR 1                     FOR I=1,...,M, J=1,...,N.
C
C THE PROGRAM IS INCLUDED IN THE VOLUME
C   S. MARTELLO, P. TOTH, "KNAPSACK PROBLEMS: ALGORITHMS
C   AND COMPUTER IMPLEMENTATIONS", JOHN WILEY, 1990
C AND IMPLEMENTS THE BRANCH-AND-BOUND ALGORITHM DESCRIBED
C IN SECTIONS  7.3 - 7.5 .
C
C THE INPUT PROBLEM MUST SATISFY THE CONDITIONS
C
C   1) 2 .LE. M .LE. JDIMR ;
C   2) 2 .LE. N .LE. JDIMC
C      ( JDIMR  AND  JDIMC  ARE DEFINED BY THE FIRST TWO EXECUTABLE
C       STATEMENTS);
C   3) M .LE. JDIMPC
C      ( JDIMPC , DEFINED BY THE THIRD EXECUTABLE STATEMENT, IS USED
C       FOR PACKING ARRAY  Y , AND CANNOT BE GREATER THAN
C       (NUMBER OF BITS OF THE HOST) - 2 ; IF A HIGHER VALUE IS
C       DESIRED, SUBROUTINES YDEF AND YUSE MUST BE RE-STRUCTURED
C       ACCORDINGLY);
C   4) P(I,J), W(I,J) AND C(I) POSITIVE INTEGERS;
C   5) W(I,J) .LE. C(I) FOR AT LEAST ONE I, FOR J=1,...,N;
C   6) C(I) .GE. MIN (W(I,J)) FOR I=1,...,M.
C
C IN ADDITION, IT IS REQUIRED THAT
C
C   7) (MAXIMUM LEVEL OF THE DECISION-TREE) .LE. JNLEV .
C      ( JNLEV  IS DEFINED BY THE FOURTH EXECUTABLE STATEMENT.)
C
C MTG CALLS 24 PROCEDURES: CHMTG, DEFPCK, DMIND, FEAS, GHA, GHBCD,
C                          GHX, GR1, GR2, HEUR, KPMAX, KPMIN, PEN0,
C                          PEN1, PREPEN, SKP, SORTI, SORTR, TERMIN,
C                          TRIN, UBFJV, UBRS, YDEF AND YUSE.
C IF NOT PRESENT IN THE LIBRARY OF THE HOST, THE USER MUST SUPPLY AN
C INTEGER FUNCTION  JIAND(I1,I2)  WHICH SETS  JIAND TO THE BIT-BY-BIT
C LOGICAL AND OF  I1  AND  I2 . SUCH FUNCTION IS USED IN SUBROUTINES
C YDEF AND YUSE.
C
C COMMUNICATION TO THE PROGRAM IS  ACHIEVED SOLELY THROUGH THE
C PARAMETER LIST OF MTG.
C NO MACHINE-DEPENDENT CONSTANT IS USED.
C THE PROGRAM IS WRITTEN IN 1967 AMERICAN NATIONAL STANDARD FORTRAN
C AND IS ACCEPTED BY THE PFORT VERIFIER (PFORT IS THE PORTABLE
C SUBSET OF ANSI DEFINED BY THE ASSOCIATION FOR COMPUTING MACHINERY).
C THE PROGRAM HAS BEEN TESTED ON A DIGITAL VAX 11/780 AND AN H.P.
C 9000/840.
C
C MTG NEEDS
C   17 ARRAYS ( C ,  DD ,  UD ,  Q ,  PAKL ,  IP ,  IR ,  IL ,  IF ,
C               WOBBL ,  KQ ,  FLREP ,  DMYR1 ,  DMYR2 ,  DMYR3 ,
C               DMYR4  AND  DMYR5 )  OF LENGTH AT LEAST  M ;
C   25 ARRAYS ( XSTAR ,  XS ,  BS ,  B ,  KA ,  XXS ,  IOBBL ,  JOBBL ,
C               BEST ,  XJJUB ,  DS ,  DMYC1 ,  DMYC2 ,  DMYC3 ,
C               DMYC4 ,  DMYC5 ,  DMYC6 ,  DMYC7 ,  DMYC8 ,  DMYC9 ,
C               DMYC10 ,  DMYC11 ,  DMYC12 , DMYC13  AND  DMYCR1 ) OF
C               LENGTH AT LEAST  N ;
C    4 ARRAYS ( PS ,  WS ,  DMYCC1  AND  DMYCC2 )  OF LENGTH AT LEAST
C               N + 1 ;
C    6 ARRAYS ( E ,  CC ,  CS ,  TYPE ,  US  AND  UBL ) OF LENGTH AT
C               LEAST  JNLEV ;
C    7 ARRAYS ( P ,  W ,  A ,  X ,  PAK ,  KAP  AND  MIND ) OF LENGTH
C               AT LEAST  M X N ;
C    5 ARRAYS ( D ,  VS ,  V ,  LB  AND  UB )  OF LENGTH AT LEAST
C               JNLEV X M ;
C    1 ARRAY  ( Y )  OF LENGTH AT LEAST  JNLEV X N ;
C    2 ARRAYS ( MASK1  AND  ITWO ) OF LENGTH AT LEAST  JDIMPC .
C
C THE ARRAYS ARE CURRENTLY DIMENSIONED TO ALLOW PROBLEMS FOR WHICH
C       M .LE. 10 ,
C       N .LE. 100 ,
C   JNLEV .LE. 150 ,
C ON A 32-BIT COMPUTER (SO, IN THE CALLING PROGRAM, ARRAYS  P  AND  W
C MUST BE DIMENSIONED AT  (10,100) ). CHANGING SUCH LIMITS NECESSITATES 
C CHANGING THE DIMENSIONS OF ALL THE ARRAYS IN SUBROUTINE MTG AND IN 
C COMMON /PACK/ (WHICH IS INCLUDED IN SUBROUTINES MTG, YDEF AND YUSE),
C AS WELL AS THE FOUR FIRST EXECUTABLE STATEMENTS.
C
C MEANING OF THE INPUT PARAMETERS:
C N        = NUMBER OF ITEMS;
C M        = NUMBER OF KNAPSACKS;
C P(I,J)   = PROFIT OF ITEM  J  IF ASSIGNED TO KNAPSACK  I
C            (I=1,...,M; J=1,...,N);
C W(I,J)   = WEIGHT OF ITEM  J  IF ASSIGNED TO KNAPSACK  I
C            (I=1,...,M; J=1,...,N);
C C(I)     = CAPACITY OF KNAPSACK  I  (I=1,...,M);
C MINMAX   = 1 IF THE OBJECTIVE FUNCTION MUST BE MINIMIZED,
C          = 2 IF THE OBJECTIVE FUNCTION MUST BE MAXIMIZED;
C BACK     = - 1 IF EXACT SOLUTION IS REQUIRED,
C          = MAXIMUM NUMBER OF BACKTRACKINGS TO BE PERFORMED,
C            IF HEURISTIC SOLUTION IS REQUIRED;
C JCK      = 1 IF CHECK ON THE INPUT DATA IS DESIRED,
C          = 0 OTHERWISE.
C
C MEANING OF THE OUTPUT PARAMETERS:
C Z        = VALUE OF THE OPTIMAL SOLUTION IF Z .GT. 0 ,
C          = 0 IF NO FEASIBLE SOLUTION EXISTS,
C          = ERROR IN THE INPUT DATA (WHEN JCK=1) IF Z .LT. 0 : CONDI-
C            TION  - Z  IS VIOLATED;
C XSTAR(J) = KNAPSACK WHERE ITEM  J  IS INSERTED IN THE SOLUTION FOUND;
C JB       = LOWER BOUND (IF MINMAX=1) OR UPPER BOUND (IF MINMAX=2)
C            ON THE OPTIMAL SOLUTION VALUE.
C
C ALL THE PARAMETERS ARE INTEGER. ON RETURN OF MTG ALL THE INPUT
C PARAMETERS ARE UNCHANGED, WITH THE FOLLOWING TWO EXCEPTIONS.  BACK
C GIVES THE NUMBER OF BACKTRACKINGS PERFORMED;  P(I,J)  IS SET TO  0
C FOR ALL PAIRS  (I,J)  SUCH THAT  W(I,J) .GT. C(I) .
C
C MEANING OF THE MAIN INTERNAL VAIRABLES:
C B(J)   = 0 IF THE ASSIGNMENT OF ITEM  J  IS FIXED,
C        = 1 OTHERWISE;
C A(I,J) =   1 IF ASSIGNMENT OF ITEM  J  TO KNAPSACK  I  IS FIXED,
C        = - 1 IF ASSIGNMENT OF ITEM  J  TO KNAPSACK  I  IS PROHIBITED,
C        =   0 OTHERWISE;
C X(I,J) =   CURRENT SOLUTION OF THE RELAXED PROBLEM;
C Y(L,J) =   PACKED SOLUTION OF THE RELAXED PROBLEM FOR ITEM  J  AT
C            LEVEL  L  OF THE BRANCH-DECISION TREE.
C
      INTEGER       P(10,100),W(10,100),C(10),XSTAR(100),Z,BACK
      INTEGER       H,S,R,U,SU,VC,SB,T,QH,ZBOUND,VJJUB,PENALT
      INTEGER       DD(10),UD(10),Q(10),PAKL(10),IP(10),IR(10),IL(10),
     1              IF(10),WOBBL(10),KQ(10),FLREP(10)
      INTEGER       XS(100),BS(100),B(100),KA(100),XXS(100),IOBBL(100),
     1              JOBBL(100),BEST(100),XJJUB(100)
      REAL          DS(100)
      INTEGER       PS(101),WS(101)
      INTEGER       E(150),CC(150),CS(150),TYPE(150),US(150),UBL(150)
      INTEGER       A(10,100),X(10,100),PAK(10,100),KAP(10,100),
     1              MIND(10,100)
      INTEGER       D(150,10),VS(150,10),V(150,10),LB(150,10),UB(150,10)
      INTEGER       Y
      INTEGER       DMYR1(10),DMYR2(10),DMYR3(10),DMYR4(10),DMYR5(10)
      INTEGER       DMYC1(100),DMYC2(100),DMYC3(100),DMYC4(100),
     1              DMYC5(100),DMYC6(100),DMYC7(100),DMYC8(100),
     2              DMYC9(100),DMYC10(100),DMYC11(100),DMYC12(100),
     3              DMYC13(100)
      INTEGER       DMYCC1(101),DMYCC2(101)
      REAL          DMYCR1(100)
      COMMON /PACK/ MASK1(30),ITWO(30),MASK,Y(150,100)
C
C DEFINITION OF THE INTERNAL PARAMETERS.
C
      JDIMR = 10
      JDIMC = 100
      JDIMPC = 30
      JNLEV = 150
      Z = 0
      IF ( JCK .EQ. 1 ) CALL CHMTG(N,M,P,W,C,JDIMR,JDIMC,JDIMPC,Z)
      IF ( Z .LT. 0 ) RETURN
C
C STEP 1 (INITIALIZE).
C
      NUMNOD = 0
      INVST = 0
      IMULT = - 1
      JB = 0
      IF ( MINMAX .EQ. 2 ) GO TO 10
C TRANSFORM THE MINIMIZATION PROBLEM INTO A MAXIMIZATION PROBLEM.
      CALL TRIN(P,N,M,INVST,LAM,JDIMR,JDIMC)
      IMULT = 1
C
C SOLVE THE MAXIMIZATION PROBLEM.
C
C CHECK FOR INFEASIBILITY.
   10 CALL FEAS(N,M,P,W,C,XSTAR,JFI,JDIMR,JDIMC)
      IF ( JFI .EQ. 1 ) GO TO 880
C HEURISTICS
      CALL HEUR(P,W,C,N,M,Z,XSTAR,IUB,JUB,BEST,KVST,INF,
     1         JDIMR,JDIMC,DMYR1,DMYR2,DMYR3,DMYR4,DMYR5,
     2         DMYC1,DMYC2,DMYC3,DMYC4,DMYCR1,A)
      IF ( Z .GE. JUB ) GO TO 880
      IF ( BACK .EQ. 0 ) GO TO 880
C FIRST REDUCTION.
      CALL GR1(P,W,C,N,M,Z,XSTAR,IUB,BEST,B,A,NR,KQ,KVST,JDIMR,JDIMC)
      IF ( NR .EQ. 0 ) GO TO 880
      KUB = IUB
C DEFINE THE VECTORS FOR PACKING Y.
      CALL DEFPCK(M,JDIMPC)
C COMPUTE THE INITIAL MARTELLO-TOTH BOUND (SU) FOR THE ROOT NODE.
      CALL DMIND(N,M,P,W,MIND,JDIMR,JDIMC,DMYC1,DMYCR1)
      DO 20 I=1,M
        FLREP(I) = 1
        Q(I) = KQ(I)
   20 CONTINUE
   30 SU = 0
      DO 130 I=1,M
        IF ( FLREP(I) .EQ. 1 ) GO TO 40
        SU = SU + V(1,I)
        GO TO 130
   40   LB(1,I) = 1
        V(1,I) = 0
        KK = 0
        ISUM = 0
        JSPR = 0
        DO 60 JJ=1,N
          J = MIND(I,JJ)
          XS(J) = 0
          IF ( A(I,J) .EQ. (- 1) ) GO TO 60
          IF ( B(J) .EQ. 1 ) GO TO 50
          XS(J) = 1
          JSPR = JSPR + P(I,J)
          GO TO 60
   50     IF ( W(I,J) .GT. Q(I) ) GO TO 60
          KK = KK + 1
          WS(KK) = W(I,J)
          ISUM = ISUM + WS(KK)
          PS(KK) = P(I,J)
          BS(KK) = J
   60   CONTINUE
        IF ( ISUM .GT. Q(I) ) GO TO 80
        IF ( KK .EQ. 0 ) GO TO 90
        DO 70 J=1,KK
          XXS(J) = 1
          V(1,I) = V(1,I) + PS(J)
   70   CONTINUE
        GO TO 90
   80   MUBF = - 1
        CALL KPMAX(KK,PS,WS,Q(I),V(1,I),XXS,MUBF,
     1             JDIMC+1,JDIMC,DMYC1,DMYC2,DMYC3,DMYC4,DMYC5)
   90   V(1,I) = V(1,I) + JSPR
        SU = SU + V(1,I)
        IF ( KK .EQ. 0 ) GO TO 110
        DO 100 J=1,KK
          INDEX = BS(J)
          XS(INDEX) = XXS(J)
  100   CONTINUE
  110   DO 120 J=1,N
          X(I,J) = XS(J)
          CALL YDEF(1,I,J,XS(J))
  120   CONTINUE
  130 CONTINUE
      L = 1
      CC(1) = 1
      D(1,1) = 1
      UB(1,1) = SU
      JUB = SU
      IF ( JUB .GT. KUB ) JUB = KUB
      IF ( JUB .LE. Z ) GO TO 880
      L = 2
C
C STEP 2 (FORWARD STEP).
C
  140 IF ( NUMNOD .EQ. BACK ) GO TO 880
      NUMNOD = NUMNOD + 1
      IF ( NUMNOD .GT. 1 ) GO TO 150
C COMPUTE THE FISHER-JAIKUMAR-VAN WASSENHOVE BOUND (JJUB).
      CALL UBFJV(N,M,P,W,Q,B,A,JJUB,XJJUB,VJJUB,Z,INF,
     1           JDIMR,JDIMC,JDIMC+1,DMYC1,DMYC2,DMYC3,DMYCC1,
     2           DMYCC2,DMYCR1,DMYC4,DMYC5,DMYC6,DMYC7,DMYC8,DMYC9,
     3           DMYC10,DMYC11,DMYR1,DMYR2,DMYR3,DMYC12,PAK)
      GO TO 160
C COMPUTE THE IMPROVED ROSS-SOLAND BOUND (JJUB).
  150 CALL UBRS(N,M,P,W,Q,B,A,JJUB,XJJUB,VJJUB,Z,INF,
     1          JDIMR,JDIMC,JDIMC+1,DMYR1,DMYC1,DMYC2,DMYC3,DMYC4,
     2          DMYC5,DMYC6,DMYC7,DMYC8,DMYC9,DMYC10,DMYC11,
     3          DMYC12,DMYC13,DMYCC1,DMYCC2,DMYCR1)
  160 IF ( JJUB .LE. Z ) GO TO 690
      IF ( JJUB .NE. VJJUB ) GO TO 180
      Z = VJJUB
      DO 170 J=1,N
        XSTAR(J) = XJJUB(J)
  170 CONTINUE
      GO TO 680
  180 UBL(L-1) = JJUB
      IF ( L .LT. JNLEV ) GO TO 190
      Z = - 7
      GO TO 880
C SEARCH FOR IMPLIED ASSIGNMENTS.
  190 KOBBL = 0
      DO 200 I=1,M
        WOBBL(I) = 0
  200 CONTINUE
      RZ = 0
      DO 280 S=1,N
        KA(S) = 1
        IF ( B(S) .EQ. 0 ) GO TO 280
        RPTOT = 0
        RP1 = 0
        KA(S) = 0
        KFEAS = 0
        DO 220 I=1,M
          RSUM = FLOAT(P(I,S))/FLOAT(W(I,S))
          IF ( X(I,S) .EQ. 0 ) GO TO 210
          KA(S) = KA(S) + 1
          RP1 = RP1 + RSUM
          RPTOT = RPTOT + RSUM
          KFEAS = KFEAS + 1
          IFEAS = I
          GO TO 220
  210     RPTOT = RPTOT + RSUM
          IF ( A(I,S) .EQ. (- 1) ) GO TO 220
          IF ( W(I,S) .GT. Q(I) ) GO TO 220
          KFEAS = KFEAS + 1
          IFEAS = I
  220   CONTINUE
        IF ( KFEAS .EQ. 0 ) GO TO 690
        IF ( KFEAS .GT. 1 ) GO TO 240
        WOBBL(IFEAS) = WOBBL(IFEAS) + W(IFEAS,S)
        IF ( WOBBL(IFEAS) .GT. Q(IFEAS) ) GO TO 690
        IF ( X(IFEAS,S) .EQ. 1 ) GO TO 230
        RZ = INF
        J = S
        JT = 0
        GO TO 280
C ITEM S MUST BE INSERTED INTO KNAPSACK IFEAS.
  230   KOBBL = KOBBL + 1
        IOBBL(KOBBL) = IFEAS
        JOBBL(KOBBL) = S
        GO TO 260
  240   IF ( KA(S) - 1 ) 250,280,260
  250   AK = RPTOT/FLOAT(M)
        GO TO 270
  260   AK = RP1
  270   DS(S) = AK
        IF ( AK .LE. RZ ) GO TO 280
        RZ = AK
        J = S
        JT = KA(S)
  280 CONTINUE
      IF ( RZ .LE. 0. ) GO TO 650
      IF ( KOBBL .EQ. 0 ) GO TO 310
C KOBBL PARTICULAR FORWARD STEPS.
      DO 300 I=1,KOBBL
        L1 = L - 1
        IK = IOBBL(I)
        JK = JOBBL(I)
        E(L) = JK
        CS(L) = 1
        D(L,1) = IK
        CC(L) = 1
        B(JK) = 0
        A(IK,JK) = 1
        Q(IK) = Q(IK) - W(IK,JK)
        INDEX = CC(L1)
        INDEX = D(L1,INDEX)
        UB(L,IK) = UB(L1,INDEX)
        UBL(L) = UBL(L1)
        TYPE(L) = 1
        DO 290 II=1,M
          LB(L,II) = LB(L1,II)
          V(L,II) = V(L1,II)
  290   CONTINUE
        L = L + 1
  300 CONTINUE
      GO TO 190
  310 IF ( Z .EQ. KVST ) GO TO 390
C COMPUTE THE PENALITIES FOR THE IMPROVED MARTELLO-TOTH BOUND.
      CALL PREPEN(N,M,P,W,Q,B,A,MIND,PAK,KAP,PAKL,IP,IR,IL,IF,
     1            JDIMR,JDIMC)
      IZMAX = - INF
      RZMAX = - INF
      ZBOUND = 0
      INDEX = CC(L-1)
      INDEX = D(L-1,INDEX)
      IUB = UB(L-1,INDEX)
      DO 370 JJ=1,N
        IF ( KA(JJ) .EQ. 1 ) GO TO 370
        IF ( KA(JJ) .EQ. 0 ) GO TO 320
        CALL PEN1(JJ,M,P,W,X,V,L-1,PAK,KAP,PAKL,IP,IR,IL,IF,PENALT,
     1            JFO,IUB,Z,JDIMR,JDIMC,JNLEV)
        IF ( JFO .EQ. 0 ) GO TO 330
        IZMAX = INF
        RZMAX = INF
        J = JJ
        JT = KA(JJ)
        GO TO 330
  320   CALL PEN0(JJ,M,P,W,Q,A,V,L-1,PAK,KAP,PAKL,IP,IR,IL,IF,
     1            PENALT,JFO,IUB,Z,INF,JDIMR,JDIMC,JNLEV)
        IF ( JFO .GT. 1 ) GO TO 330
        IZMAX = INF
        RZMAX = INF
        J = JJ
        JT = 0
  330   IF ( PENALT .LE. ZBOUND ) GO TO 340
        IF ( IUB - PENALT .LE. Z ) GO TO 690
        ZBOUND = PENALT
  340   IF ( PENALT .LT. IZMAX ) GO TO 370
        IF ( PENALT .EQ. IZMAX ) GO TO 350
        IZMAX = PENALT
        RZMAX = DS(JJ)
        GO TO 360
  350   IF ( DS(JJ) .LE. RZMAX ) GO TO 370
        RZMAX = DS(JJ)
  360   J = JJ
        JT = KA(JJ)
  370 CONTINUE
C COMPUTE THE IMPROVED MARTELLO-TOTH BOUND (IUB - ZBOUND).
      IF ( UBL(L-1) .GT. IUB - ZBOUND ) UBL(L-1) = IUB - ZBOUND
      IF ( NUMNOD .GT. 1 ) GO TO 390
      JKLIM = IUB - ZBOUND
      IF ( JUB .GT. UBL(1) ) JUB = UBL(1)
      IF ( JUB .GT. JKLIM ) JUB = JKLIM
C SECOND REDUCTION (EXECUTED ONLY FOR THE ROOT NODE).
      CALL GR2(N,M,P,W,Q,B,A,MIND,PAK,KAP,PAKL,IP,IR,IL,IF,NR,Z,
     1         XSTAR,UB(1,1),X,V,FLREP,KVST,JDIMR,JDIMC,JNLEV,DMYR1)
      IF ( NR .EQ. 0 ) GO TO 880
C CHECK FOR RE-EXECUTION.
      DO 380 I=1,M
        IF ( FLREP(I) .EQ. 0 ) GO TO 380
        NUMNOD = 0
        KUB = JUB
        GO TO 30
  380 CONTINUE
C FORWARD STEP ON ITEM J.
  390 E(L) = J
      TYPE(L) = JT
      T = 0
      VC = 0
      IF ( TYPE(L) .GT. 0 ) GO TO 420
      DO 410 I=1,M
        IF ( W(I,J) .GT. Q(I) ) GO TO 400
        IF ( A(I,J) .EQ. (- 1) ) GO TO 400
        T = T + 1
        D(L,T) = I
  400   VC = VC + V(L-1,I)
  410 CONTINUE
      IF ( T .EQ. 0 ) GO TO 690
      GO TO 450
  420 DO 440 I=1,M
        IF ( X(I,J) .EQ. 0 ) GO TO 430
        T = T + 1
        D(L,T) = I
        GO TO 440
  430   VC = VC + V(L-1,I)
  440 CONTINUE
  450 CS(L) = T
C
C STEP 3 (BOUND).
C
C COMPUTE THE INITIAL MARTELLO-TOTH BOUND FOR THE SON NODES.
      KK = 0
      DO 560 R=1,T
        H = D(L,R)
        QH = Q(H)
        IF (TYPE(L) .EQ. 0 ) QH = QH - W(H,J)
        JW = W(H,J)
        W(H,J) = INF
        U = 0
        SB = 0
        ISU = 0
        DO 480 JS=1,N
          S = MIND(H,JS)
          IF ( B(S) .EQ. 0 ) GO TO 460
          IF ( W(H,S) .GT. QH ) GO TO 470
          IF ( A(H,S) .NE. 0 ) GO TO 470
          U = U + 1
          PS(U) = P(H,S)
          WS(U) = W(H,S)
          SB = SB + WS(U)
          BS(U) = S
          GO TO 480
  460     IF ( A(H,S) .NE. 1 ) GO TO 470
          CALL YDEF(L,H,S,1)
          ISU = ISU + P(H,S)
          GO TO 480
  470     CALL YDEF(L,H,S,0)
  480   CONTINUE
        IF ( TYPE(L) .GT. 0 ) GO TO 490
        CALL YDEF(L,H,J,1)
        ISU = ISU + P(H,J)
  490   INDEX = CC(L-1)
        IHS = D(L-1,INDEX)
        KSU = Z - UB(L-1,IHS) + V(L-1,H) - ISU
        SU = KSU
        IF ( SB .GT. QH ) GO TO 510
        SU = 0
        IF ( U .EQ. 0 ) GO TO 540
        DO 500 S=1,U
          XS(S) = 1
          SU = SU + PS(S)
  500   CONTINUE
        GO TO 520
  510   MUBF = - 1
        CALL KPMAX(U,PS,WS,QH,SU,XS,MUBF,
     1             JDIMC+1,JDIMC,DMYC1,DMYC2,DMYC3,DMYC4,DMYC5)
  520   DO 530 S=1,U
          JS = BS(S)
          CALL YDEF(L,H,JS,XS(S))
  530   CONTINUE
  540   IF ( SU .GT. KSU ) GO TO 550
        IF ( TYPE(L) .EQ. 0 ) GO TO 550
        KK = KK + 1
        IF ( KK .EQ. 1 ) GO TO 550
        W(H,J) = JW
        GO TO 690
  550   SU = SU + ISU
        VS(L,H) = SU
        IF ( TYPE(L) .GT. 0 ) VC = VC + SU
        W(H,J) = JW
  560 CONTINUE
C
C STEP 4 (SORT THE SON NODES).
C
      US(L) = VC
      JSIGN = 1
      IF ( TYPE(L) .EQ. 0 ) JSIGN = - 1
      DO 570 R=1,T
        H = D(L,R)
        JADD = V(L-1,H) - VS(L,H)
        UB(L,H) = VC + JADD*JSIGN
        DD(R) = H
        UD(H) = UB(L,H)
  570 CONTINUE
      CALL SORTI(T,UD,DD,JDIMR)
      DO 580 R=1,T
        D(L,R) = DD(R)
  580 CONTINUE
C
C STEP 5 (FIRST BRANCHING FROM A NODE).
C
      L1 = L - 1
      CC(L) = 1
      H = D(L,1)
      IF ( UB(L,H) .LE. Z  ) GO TO 690
      DO 590 I=1,M
        LB(L,I) = LB(L1,I)
        V(L,I) = V(L1,I)
  590 CONTINUE
      IF ( TYPE(L) .EQ. 0 ) GO TO 620
      DO 610 U=2,T
        R = D(L,U)
        LB(L,R) = L
        V(L,R) = VS(L,R)
        DO 600 S=1,N
          CALL YUSE(L,R,S,X(R,S))
  600   CONTINUE
  610 CONTINUE
      GO TO 640
  620 LB(L,H) = L
      V(L,H) = VS(L,H)
      DO 630 S=1,N
        CALL YUSE(L,H,S,X(H,S))
  630 CONTINUE
  640 A(H,J) = 1
      B(J) = 0
      Q(H) = Q(H) - W(H,J)
      L = L + 1
      GO TO 140
C
C STEP 6 (UPDATE THE CURRENT OPTIMAL SOLUTION).
C
  650 L1 = L - 1
      INDEX = CC(L1)
      H = D(L1,INDEX)
      IF ( Z .GE. UB(L1,H) ) GO TO 690
      Z = UB(L1,H)
      DO 670 J=1,N
        DO 660 I=1,M
          IF ( X(I,J) .NE. 1 ) GO TO 660
          XSTAR(J) = I
          GO TO 670
  660   CONTINUE
  670 CONTINUE
  680 IF ( Z .EQ. JUB ) GO TO 880
C
C STEP 7 (BACKTRACK AND BRANCHING FOR THE SUBSEQUENT SON NODES).
C
  690 L = L - 1
      IF ( L .LE. 1 ) GO TO 880
      INDEX = CC(L)
      H = D(L,INDEX)
      J = E(L)
      L1 = L - 1
      IF ( CC(L) .EQ. CS(L) ) GO TO 700
      JH = D(L,INDEX+1)
      IF ( UBL(L1) .LE. Z ) GO TO 700
      IF ( UB(L,JH) .GT. Z ) GO TO 780
      GO TO 710
  700 IF ( B(J) .EQ. 1 ) GO TO 720
  710 A(H,J) = 0
      B(J) = 1
      Q(H) = Q(H) + W(H,J)
  720 T = CS(L)
      IF ( TYPE(L) .GT. 0 ) GO TO 750
      LS = LB(L1,H)
      LB(L,H) = LS
      V(L,H) = V(L1,H)
      DO 730 U=1,T
        INDEX = D(L,U)
        A(INDEX,J) = 0
  730 CONTINUE
      DO 740 S=1,N
        CALL YUSE(LS,H,S,X(H,S))
  740 CONTINUE
      GO TO 690
  750 DO 770 U=1,T
        R = D(L,U)
        IF ( R .EQ. H ) GO TO 770
        LS = LB(L1,R)
        LB(L,R) = LS
        V(L,R) = V(L1,R)
        A(R,J) = 0
        DO 760 S=1,N
          CALL YUSE(LS,R,S,X(R,S))
  760   CONTINUE
  770 CONTINUE
      GO TO 690
  780 A(H,J) = - 1
      Q(H) = Q(H) + W(H,J)
      IF ( TYPE(L) .GT. 0 ) GO TO 810
      LS = LB(L1,H)
      LB(L,H) = LS
      V(L,H) = V(L1,H)
      DO 790 S=1,N
        CALL YUSE(LS,H,S,X(H,S))
  790 CONTINUE
      CC(L) = CC(L) + 1
      INDEX = CC(L)
      H = D(L,INDEX)
      LB(L,H) = L
      V(L,H) = VS(L,H)
      DO 800 S=1,N
        CALL YUSE(L,H,S,X(H,S))
  800 CONTINUE
      GO TO 850
  810 LB(L,H) = L
      V(L,H) = VS(L,H)
      DO 820 S=1,N
        CALL YUSE(L,H,S,X(H,S))
  820 CONTINUE
      CC(L) = CC(L) + 1
      INDEX = CC(L)
      H = D(L,INDEX)
      LS = LB(L1,H)
      LB(L,H) = LS
      V(L,H) = V(L1,H)
      DO 830 S=1,N
        CALL YUSE(LS,H,S,X(H,S))
  830 CONTINUE
      IF ( CC(L) .LT. CS(L) ) GO TO 850
      IF ( US(L) .LE. Z ) GO TO 850
      IF ( CS(L) .EQ. M ) GO TO 850
      DO 840 R=1,M
        IF ( A(R,J) .EQ. (- 1) ) GO TO 840
        IF ( W(R,J) .LE. Q(R) ) GO TO 860
  840 CONTINUE
  850 A(H,J) = 1
      Q(H) = Q(H) - W(H,J)
      GO TO 870
  860 A(H,J) = 0
      B(J) = 1
  870 L = L + 1
      GO TO 140
C
C TERMINATE.
C
  880 CALL TERMIN(JFI,INVST,JUB,IMULT,Z,KVST,NUMNOD,MINMAX,
     1            M,N,P,LAM,JDIMR,JDIMC,JB,BACK)
      RETURN
      END
      SUBROUTINE CHMTG(N,M,P,W,C,JDIMR,JDIMC,JDIMPC,Z)
C
C CHECK THE INPUT DATA.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),C(JDIMR),Z
      IF ( M .LE. 1 ) Z = - 1
      IF ( M .GT. JDIMR ) Z = - 1
      IF ( Z .LT. 0 ) RETURN
      IF ( N .LE. 1 ) Z = - 2
      IF ( N .GT. JDIMC ) Z = - 2
      IF ( Z .LT. 0 ) RETURN
      IF ( M .LE. JDIMPC) GO TO 10
      Z = - 3
      RETURN
   10 DO 50 I=1,M
        IF ( C(I) .GT. 0 ) GO TO 20
        Z = - 4
        RETURN
   20   MIN = C(I) + 1
        DO 40 J=1,N
          IF ( P(I,J) .GT. 0 .AND. W(I,J) .GT. 0 ) GO TO 30
          Z = - 4
          RETURN
   30     IF ( W(I,J) .LT. MIN ) MIN = W(I,J)
   40   CONTINUE
        IF ( C(I) .LT. MIN ) Z = - 6
   50 CONTINUE
      DO 70 J=1,N
        DO 60 I=1,M
          IF ( W(I,J) .LE. C(I) ) GO TO 70
   60   CONTINUE
        Z = - 5
        RETURN
   70 CONTINUE
      RETURN
      END
      SUBROUTINE DEFPCK(M,JDIMPC)
      INTEGER Y
      COMMON /PACK/ MASK1(30),ITWO(30),MASK,Y(150,100)
      DO 10 I=1,M
        ITWO(I) = 2**(I-1)
        MASK1(I) = 2**(JDIMPC) - 1 - ITWO(I)
   10 CONTINUE
      MASK = 1
      RETURN
      END
      SUBROUTINE DMIND(N,M,P,W,MIND,JDIMR,JDIMC,IND,PWV)
C
C DEFINE ARRAY MIND TO CONTAIN THE POINTERS TO THE SORTED ITEMS
C FOR THE 0-1 SINGLE KNAPSACK PROBLEMS.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),MIND(JDIMR,JDIMC)
      INTEGER IND(JDIMC)
      REAL    PWV(JDIMC)
      DO 30 I=1,M
        DO 10 J=1,N
          PWV(J) = FLOAT(P(I,J))/FLOAT(W(I,J))
          IND(J) = J
   10   CONTINUE
        CALL SORTR(N,PWV,IND,JDIMC)
        DO 20 J=1,N
          MIND(I,J) = IND(J)
   20   CONTINUE
   30 CONTINUE
      RETURN
      END
      SUBROUTINE FEAS(N,M,P,W,C,XSTAR,JFI,JDIMR,JDIMC)
C
C CHECK FOR INFEASIBILITY.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),C(JDIMR),XSTAR(JDIMC)
      JFI = 0
      DO 20 J=1,N
        XSTAR(J) = 0
        KINF = 0
        DO 10 I=1,M
          IF ( W(I,J) .LE. C(I) ) GO TO 10
          KINF = KINF + 1
          P(I,J) = 0
   10   CONTINUE
        IF ( KINF .EQ. M ) JFI = 1
   20 CONTINUE
      RETURN
      END
      SUBROUTINE GHA(P,W,C,N,M,Z,XSTAR,IUB,BEST,KVST,INF,
     1               JDIMR,JDIMC,KW,MW,PEN,FIRST,SECOND,BB)
C
C APPLY THE APPROXIMATE ALGORITHM GH WITH FUNCTION (A) AND
C DEFINE THE INFINITE VALUE  INF .
C
C IF IUB = Z THE SOLUTION IS OPTIMAL;
C IF Z = KVST NO FEASIBLE SOLUTION WAS FOUND.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),C(JDIMR),XSTAR(JDIMC),
     1        BEST(JDIMC),Z
      INTEGER KW(JDIMR),MW(JDIMR),PEN(JDIMC),FIRST(JDIMC),
     1        SECOND(JDIMC),BB(JDIMC)
      INTEGER FMAX,SMAX
      INF = 0
      DO 10 I=1,M
        KW(I) = C(I)
        MW(I) = 0
        IF ( C(I) .GT. INF ) INF = C(I)
   10 CONTINUE
      IUB = 0
      Z = 0
      KVST = 0
      DO 40 J=1,N
        IPMIN = P(1,J)
        FMAX = P(1,J)
        IF = 1
        SMAX = 0
        DO 30 I=2,M
          IF ( P(I,J) .LT. IPMIN ) IPMIN = P(I,J)
          IF ( SMAX .GE. P(I,J) ) GO TO 30
          IF ( FMAX .GE. P(I,J) ) GO TO 20
          SMAX = FMAX
          IS = IF
          FMAX = P(I,J)
          IF = I
          GO TO 30
   20     SMAX = P(I,J)
          IS = I
   30   CONTINUE
        KVST = KVST + IPMIN
        FIRST(J) = IF
        BEST(J) = IF
        SECOND(J) = IS
        PEN(J) = FMAX - SMAX
        IF ( SMAX .EQ. 0 ) PEN(J) = - 1
        BB(J) = J
        IUB = IUB + FMAX
        IF ( W(IF,J) .GT. MW(IF) ) MW(IF) = W(IF,J)
        IF ( W(IS,J) .GT. MW(IS) ) MW(IS) = W(IS,J)
   40 CONTINUE
      IF ( KVST .GT. 0 ) KVST = KVST - 1
      IF ( IUB .GT. INF ) INF = IUB
      DO 50 J=1,N
        IF ( PEN(J) .EQ. (- 1) ) PEN(J) = INF
   50 CONTINUE
      NB = N
   60 MAXPEN = - 1
      DO 70 JJ=1,NB
        J = BB(JJ)
        IF ( PEN(J) .LE. MAXPEN ) GO TO 70
        MAXPEN = PEN(J)
        JJM = JJ
   70 CONTINUE
      JO = BB(JJM)
      IO = FIRST(JO)
      Z = Z + P(IO,JO)
      XSTAR(JO) = IO
      BB(JJM) = BB(NB)
      NB = NB - 1
      IF ( NB .EQ. 0 ) RETURN
      KW(IO) = KW(IO) - W(IO,JO)
      IF ( MW(IO) .LE. KW(IO) ) GO TO 60
      DO 120 JJ=1,NB
        J = BB(JJ)
        IF ( W(IO,J) .LE. KW(IO) ) GO TO 120
        IF ( FIRST(J) .NE. IO ) GO TO 80
        IF ( PEN(J) .EQ. INF ) GO TO 130
        FIRST(J) = SECOND(J)
        GO TO 90
   80   IF ( SECOND(J) .NE. IO ) GO TO 120
   90   INDEX = FIRST(J)
        W(INDEX,J) = W(INDEX,J) + INF
        NEWSEC = 0
        DO 100 I=1,M
          IF ( W(I,J) .GT. KW(I) ) GO TO 100
          IF ( P(I,J) .LE. NEWSEC ) GO TO 100
          NEWSEC = P(I,J)
          IS = I
  100   CONTINUE
        W(INDEX,J) = W(INDEX,J) - INF
        IF ( NEWSEC .EQ. 0 ) GO TO 110
        SECOND(J) = IS
        PEN(J) = P(INDEX,J) - NEWSEC
        IF ( W(IS,J) .GT. MW(IS) ) MW(IS) = W(IS,J)
        GO TO 120
  110   PEN(J) = INF
  120 CONTINUE
      GO TO 60
  130 Z = KVST
      RETURN
      END
      SUBROUTINE GHBCD(P,W,C,N,M,Z,XSTAR,INF,JDIMR,JDIMC,XSP,
     1           DMYR1,DMYR2,DMYR3,DMYR4,DMYR5,
     2           DMYC2,DMYC3,DMYC4,DMYCR1,DMYA)
C
C APPLY THE APPROXIMATE ALGORITHM GH WITH FUNCTIONS (B), (C) AND (D).
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),C(JDIMR),XSTAR(JDIMC),Z
      INTEGER VSP,XSP(JDIMC)
      INTEGER DMYR1(JDIMR),DMYR2(JDIMR),DMYR3(JDIMR),DMYR4(JDIMR),
     1        DMYR5(JDIMR),DMYC2(JDIMC),DMYC3(JDIMC),DMYC4(JDIMC),
     2        DMYA(JDIMR,JDIMC)
      REAL    DMYCR1(JDIMC)
      JJ = 2
      A1 = 1.
      A2 = 0.
      A3 = 0.
      A4 = 0.
      A5 = 1.
   10 CALL GHX(P,W,C,N,M,VSP,XSP,A1,A2,A3,A4,A5,INF,JDIMR,JDIMC,
     1         DMYR1,DMYR2,DMYR3,DMYR4,DMYR5,DMYC2,DMYC3,DMYC4,
     2         DMYCR1,DMYA)
      IF ( VSP .LE. Z ) GO TO 30
      Z = VSP
      DO 20 J=1,N
         XSTAR(J) = XSP(J)
   20 CONTINUE
   30 IF ( JJ .EQ. 3 ) GO TO 40
      IF ( JJ .EQ. 4 ) GO TO 50
      JJ = 3
      A1 = 1.
      A2 = 0.
      A3 = 1.
      A4 = 0.
      A5 = 0.
      GO TO 10
   40 JJ = 4
      A1 = 0.
      A2 = 1.
      A3 = 0.
      A4 = 1.
      A5 = 0.
      GO TO 10
   50 RETURN
      END
      SUBROUTINE GHX(P,W,C,N,M,Z,XSTAR,A1,A2,A3,A4,A5,INF,JDIMR,JDIMC,
     1               KW,MW,MINW,KCHAN,KWR,FIRST,SECOND,BB,PEN,WL)
C
C APPLY THE APPROXIMATE ALGORITHM GH WITH FUNCTION (B) OR (C) OR (D).
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),XSTAR(JDIMC),C(JDIMR),Z
      INTEGER KW(JDIMR),MW(JDIMR),MINW(JDIMR),KCHAN(JDIMR),KWR(JDIMR),
     1        FIRST(JDIMC),SECOND(JDIMC),BB(JDIMC),WL(JDIMR,JDIMC)
      REAL    PEN(JDIMC),MAXPEN
      DO 20 I=1,M
        KW(I) = C(I)
        MW(I) = 0
        MINW(I) = INF
        DO 10 J=1,N
          WL(I,J) = W(I,J)
          IF ( WL(I,J) .LT. MINW(I) ) MINW(I) = WL(I,J)
   10   CONTINUE
        KWR(I) = KW(I) - MINW(I)
   20 CONTINUE
      Z = 0
      DO 60 J=1,N
        FMAX = - INF
        IF = 0
        SMAX = - INF
        DO 40 I=1,M
          IF ( WL(I,J) .GT. KW(I) ) GO TO 40
          IF ( WL(I,J) .GT. KWR(I) ) WL(I,J) = KW(I)
          RWL = WL(I,J)
          RP = P(I,J)
          RKW = KW(I)
          S = (- A1*RWL + A2*RP)/(A3*RKW + A4*RWL + A5)
          IF ( SMAX .GE. S ) GO TO 40
          IF ( FMAX .GE. S ) GO TO 30
          SMAX = FMAX
          IS = IF
          FMAX = S
          IF = I
          GO TO 40
   30     SMAX = S
          IS = I
   40   CONTINUE
        FIRST(J) = IF
        SECOND(J) = IS
        PEN(J) = FMAX - SMAX
        BB(J) = J
        IF ( WL(IF,J) .GT. MW(IF) ) MW(IF) = WL(IF,J)
        IF ( SMAX .GT. FLOAT(- INF) ) GO TO 50
        PEN(J) = INF
        GO TO 60
   50   IF ( WL(IS,J) .GT. MW(IS) ) MW(IS) = WL(IS,J)
   60 CONTINUE
      NB = N
   70 MAXPEN = - 1
      DO 80 JJ=1,NB
        J = BB(JJ)
        IF ( PEN(J) .LE. MAXPEN ) GO TO 80
        MAXPEN = PEN(J)
        JJM = JJ
   80 CONTINUE
      JO = BB(JJM)
      IO = FIRST(JO)
      Z = Z + P(IO,JO)
      XSTAR(JO) = IO
      BB(JJM) = BB(NB)
      NB = NB - 1
      KW(IO) = KW(IO) - W(IO,JO)
      IF ( NB .EQ. 0 ) GO TO 210
      KK = 0
      DO 110 I=1,M
        KCHAN(I) = 0
        IF ( WL(I,JO) .GT. MINW(I) ) GO TO 100
        MINW(I) = INF
        DO 90 JJ=1,NB
          J = BB(JJ)
          IF ( WL(I,J) .LT. MINW(I) ) MINW(I) = WL(I,J)
   90   CONTINUE
        IF ( MINW(I) + MW(I) .LE. KW(I) ) GO TO 100
        KK = 1
        KCHAN(I) = 1
  100   KWR(I) = KW(I) - MINW(I)
  110 CONTINUE
      IF ( MW(IO) .LE. KW(IO) ) GO TO 120
      KK = 1
      KCHAN(IO) = 1
  120 IF ( KK .EQ. 0 ) GO TO 70
      DO 190 JJ=1,NB
        J = BB(JJ)
        JF = FIRST(J)
        IF ( PEN(J) .LT. FLOAT(INF) ) GO TO 130
        IF ( WL(JF,J) .GT. KW(JF) ) GO TO 200
        GO TO 190
  130   IF ( KCHAN(JF) .EQ. 0 ) GO TO 140
        IF ( WL(JF,J) .GT. KWR(JF) ) GO TO 150
  140   JS = SECOND(J)
        IF ( KCHAN(JS) .EQ. 0 ) GO TO 190
        IF ( WL(JS,J) .LE. KWR(JS) ) GO TO 190
  150   FMAX = - INF
        SMAX = - INF
        IF = 0
        DO 170 I=1,M
          IF ( WL(I,J) .GT. KW(I) ) GO TO 170
          IF ( WL(I,J) .GT. KWR(I) ) WL(I,J) = KW(I)
          RWL = WL(I,J)
          RP = P(I,J)
          RKW = KW(I)
          S = (- A1*RWL + A2*RP)/(A3*RKW + A4*RWL + A5)
          IF ( SMAX .GE. S ) GO TO 170
          IF ( FMAX .GE. S ) GO TO 160
          SMAX = FMAX
          IS = IF
          FMAX = S
          IF = I
          GO TO 170
  160     SMAX = S
          IS = I
  170   CONTINUE
        FIRST(J) = IF
        SECOND(J) = IS
        PEN(J) = FMAX - SMAX
        IF ( WL(IF,J) .GT. MW(IF) ) MW(IF) = WL(IF,J)
        IF ( SMAX .GT. FLOAT(- INF) ) GO TO 180
        PEN(J) = INF
        GO TO 190
  180   IF ( WL(IS,J) .GT. MW(IS) ) MW(IS) = WL(IS,J)
  190 CONTINUE
      GO TO 70
  200 Z = 0
      RETURN
C TRY TO IMPROVE ON THE CURRENT SOLUTION Z.
  210 DO 230 J=1,N
        IF = XSTAR(J)
        MAXP = P(IF,J)
        DO 220 I=1,M
          IF ( W(I,J) .GT. KW(I) ) GO TO 220
          IF ( P(I,J) .LE. MAXP ) GO TO 220
          MAXP = P(I,J)
          IF = I
  220   CONTINUE
        IP = XSTAR(J)
        IF ( IF .EQ. IP ) GO TO 230
        XSTAR(J) = IF
        Z = Z + P(IF,J) - P(IP,J)
        KW(IP) = KW(IP) + W(IP,J)
        KW(IF) = KW(IF) - W(IF,J)
  230 CONTINUE
      RETURN
      END
      SUBROUTINE GR1(P,W,C,N,M,Z,XSTAR,IUB,BEST,B,A,NR,KQ,KVST,
     1               JDIMR,JDIMC)
C
C REDUCE A MAXIMIZATION GAP.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),C(JDIMR),XSTAR(JDIMC),
     1        BEST(JDIMC),B(JDIMC),A(JDIMR,JDIMC),KQ(JDIMR),Z
      INTEGER PO,BEJ
      NR = N
      DO 10 I=1,M
        KQ(I) = C(I)
   10 CONTINUE
      DO 30 J=1,N
        B(J) = 1
        DO 20 I=1,M
          A(I,J) = 0
   20   CONTINUE
   30 CONTINUE
      IF ( Z .EQ. KVST ) RETURN
      M1 = M - 1
      JGAP = IUB - Z
   40 NVR = N*M
      NROLD = NR
      DO 90 J=1,N
        IF ( B(J) .EQ. 1 ) GO TO 50
        NVR = NVR - M
        GO TO 90
   50   BEJ = BEST(J)
        PO = P(BEJ,J)
        NF = 0
        DO 80 I=1,M
          IF ( W(I,J) .GT. KQ(I) ) GO TO 60
          IF ( PO - P(I,J) .LT. JGAP ) GO TO 70
   60     A(I,J) = - 1
          NF = NF + 1
          GO TO 80
   70     IB = I
   80   CONTINUE
        IF ( NF .GE. M ) GO TO 100
        NVR = NVR - NF
        IF ( NF .LT. M1 ) GO TO 90
        B(J) = 0
        A(IB,J) = 1
        KQ(IB) = KQ(IB) - W(IB,J)
        NR = NR - 1
        NVR = NVR - 1
   90 CONTINUE
      IF ( NR .EQ. 0 ) RETURN
      IF ( NR .LT. NROLD ) GO TO 40
      RETURN
  100 NR = 0
      NVR = 0
      RETURN
      END
      SUBROUTINE GR2(N,M,P,W,Q,B,A,MIND,PAK,KAP,PAKL,IP,IR,IL,IF,NR,
     1               Z,XSTAR,JUB,X,V,FLREP,KVST,JDIMR,JDIMC,JNLEV,IN)
C
C REDUCE A MAXIMIZATION GAP.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),Q(JDIMR),B(JDIMC),
     1        A(JDIMR,JDIMC),MIND(JDIMR,JDIMC),PAK(JDIMR,JDIMC),
     2        KAP(JDIMR,JDIMC),PAKL(JDIMR),IP(JDIMR),IR(JDIMR),
     3        IL(JDIMR),IF(JDIMR),XSTAR(JDIMC),X(JDIMR,JDIMC),
     4        V(JNLEV,JDIMR),FLREP(JDIMR),Z
      INTEGER IN(JDIMR)
      DO 10 I=1,M
        FLREP(I) = 0
   10 CONTINUE
      IF ( Z .EQ. KVST ) RETURN
      CALL PREPEN(N,M,P,W,Q,B,A,MIND,PAK,KAP,PAKL,IP,IR,IL,IF,
     1            JDIMR,JDIMC)
      JGAP = JUB - Z
      NVR = 0
      IPNR0 = 0
      DO 210 J=1,N
        IF ( B(J) .EQ. 0 ) GO TO 210
        N1 = 0
        NA = 0
        ISUM = 0
        DO 140 I=1,M
          IF ( A(I,J) .EQ. (- 1) ) GO TO 140
          IF ( W(I,J) .GT. Q(I) ) GO TO 120
          IF ( X(I,J) .EQ. 0 ) GO TO 90
C COMPUTE THE LOSS LAM OF KNAPSACK I IF X(I,J) = 0 .
          JJ = KAP(I,J)
          KL = IL(I)
          KP = IP(I)
          KR = IR(I)
          IF ( JJ - (KL + 1) ) 40,20,130
   20     IF ( KL + 1 .EQ. PAKL(I) ) GO TO 30
          JKL = PAK(I,KL+2)
          RUB = FLOAT(KP) + FLOAT(P(I,JKL)*KR)/FLOAT(W(I,JKL))
          GO TO 80
   30     RUB = KP
          GO TO 80
   40     KP = KP - P(I,J)
          KR = KR + W(I,J)
          LA = KL + 1
          L2 = PAKL(I)
          IF ( LA .LE. L2 ) GO TO 50
          RUB = KP
          GO TO 80
   50     DO 60 JL=LA,L2
            JJ = PAK(I,JL)
            IF ( W(I,JJ) .GT. KR ) GO TO 70
            KR = KR - W(I,JJ)
            KP = KP + P(I,JJ)
   60     CONTINUE
          RUB = KP
          GO TO 80
   70     RUB = FLOAT(KP) + FLOAT(P(I,JJ)*KR)/FLOAT(W(I,JJ))
   80     IUB = RUB
          LAM = V( 1,I) - (IUB + IF(I))
          IF ( LAM .GE. JGAP ) GO TO 150
          IF ( LAM .LE. 0 ) GO TO 130
          ISUM = ISUM + LAM
          N1 = N1 + 1
          IN(N1) = I
          IF ( ISUM .GE. JGAP ) GO TO 170
          GO TO 130
C COMPUTE THE LOSS LAM OF KNAPSACK I IF X(I,J) = 1 .
   90     JJ = KAP(I,J)
          KL = IL(I)
          IF ( JJ .LE. KL ) GO TO 130
          KR = IR(I) - W(I,J)
          KP = IP(I) + P(I,J)
  100     IF ( KR .GE. 0 ) GO TO 110
          JKL = PAK(I,KL)
          KR = KR + W(I,JKL)
          KP = KP - P(I,JKL)
          KL = KL - 1
          GO TO 100
  110     JKL = PAK(I,KL+1)
          RUB = FLOAT(KP) + FLOAT(P(I,JKL)*KR)/FLOAT(W(I,JKL))
          IUB = RUB
          LAM = V(1,I) - (IUB + IF(I))
          IF ( LAM .LT. JGAP ) GO TO 130
          A(I,J) = - 1
          FLREP(I) = 1
          GO TO 140
  120     A(I,J) = - 1
          FLREP(I) = 1
          GO TO 140
  130     NA = NA + 1
          IB = I
  140   CONTINUE
        IF ( NA .EQ. 0 ) GO TO 310
        IF ( NA .GT. 1 ) GO TO 200
        I = IB
  150   B(J) = 0
        DO 160 II=1,M
          A(II,J) = - 1
          FLREP(II) = 1
  160   CONTINUE
        A(I,J) = 1
        NR = NR - 1
        Q(I) = Q(I) - W(I,J)
        IPNR0 = IPNR0 + P(I,J)
        GO TO 210
  170   DO 180 I=1,M
          IF ( A(I,J) .EQ. (- 1) ) GO TO 180
          A(I,J) = - 1
          FLREP(I) = FLREP(I) + 1
  180   CONTINUE
        DO 190 II=1,N1
          I = IN(II)
          A(I,J) = 0
          FLREP(I) = FLREP(I) - 1
  190   CONTINUE
        NA = N1
  200   NVR = NVR + NA
  210 CONTINUE
      DO 220 I=1,M
        IF ( FLREP(I) .GT. 1 ) FLREP(I) = 1
  220 CONTINUE
      IF ( NR .GT. 1 ) RETURN
      IF ( NR .EQ. 0 ) GO TO 260
      MAX = - 1
      DO 230 J=1,N
        IF ( B(J) .EQ. 1 ) GO TO 240
  230 CONTINUE
  240 B(J) = 0
      NR = 0
      DO 250 I=1,M
        IF ( A(I,J) .EQ. (- 1) ) GO TO 250
        IF ( W(I,J) .GT. Q(I) ) GO TO 250
        IF ( P(I,J) .LE. MAX ) GO TO 250
        MAX = P(I,J)
        II = I
  250 CONTINUE
      IF ( MAX .LT. 0 ) RETURN
      A(II,J) = 1
      Q(II) = Q(II) - W(II,J)
      IPNR0 = IPNR0 + P(II,J)
  260 DO 270 I=1,M
        IPNR0 = IPNR0 + IF(I)
  270 CONTINUE
      IF ( IPNR0 .LE. Z ) RETURN
      Z = IPNR0
      DO 300 J=1,N
        DO 280 I=1,M
          IF ( A(I,J) .EQ. 1 ) GO TO 290
  280   CONTINUE
  290   XSTAR(J) = I
  300 CONTINUE
      RETURN
  310 NR = 0
      RETURN
      END
      SUBROUTINE HEUR(P,W,C,N,M,Z,XSTAR,IUB,JUB,BEST,KVST,INF,
     1                JDIMR,JDIMC,DMYR1,DMYR2,DMYR3,DMYR4,DMYR5,
     2                DMYC1,DMYC2,DMYC3,DMYC4,DMYCR1,A)
C
C DETERMINE THE BEST INITIAL HEURISTIC SOLUTION.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),C(JDIMR),Z,XSTAR(JDIMC),
     1        BEST(JDIMC)
      INTEGER DMYR1(JDIMR),DMYR2(JDIMR),DMYR3(JDIMR),DMYR4(JDIMR),
     1        DMYR5(JDIMR)
      INTEGER DMYC1(JDIMC),DMYC2(JDIMC),DMYC3(JDIMC),DMYC4(JDIMC)
      REAL    DMYCR1(JDIMC)
      INTEGER A(JDIMR,JDIMC)
C FIRST HEURISTIC SOLUTION.
      CALL GHA(P,W,C,N,M,Z,XSTAR,IUB,BEST,KVST,INF,
     1         JDIMR,JDIMC,DMYR1,DMYR2,DMYC1,DMYC2,DMYC3,DMYC4)
      JUB = IUB
      IF ( Z .EQ. JUB ) RETURN
C SECOND HEURISTIC SOLUTION.
      CALL GHBCD(P,W,C,N,M,Z,XSTAR,INF,
     1           JDIMR,JDIMC,DMYC1,DMYR1,DMYR2,DMYR3,DMYR4,DMYR5,
     2           DMYC2,DMYC3,DMYC4,DMYCR1,A)
      RETURN
      END
      SUBROUTINE KPMAX(NG,PG,WG,CG,ZG,XG,MUBF,
     1                 JDIMC1,JDIMC,XXG,MIN,PSIGN,WSIGN,ZSIGN)
C
C SOLVE A 0-1 SINGLE KNAPSACK PROBLEM BY RECEIVING IN  ZG
C AN INITIAL VALUE OF THE SOLUTION.
C
C THIS SUBROUTINE IS A MODIFIED VERSION OF SUBROUTINE MT1.
C
      INTEGER PG(JDIMC1),WG(JDIMC1),XG(JDIMC),CG,ZG
      INTEGER XXG(JDIMC),MIN(JDIMC),PSIGN(JDIMC),WSIGN(JDIMC),
     1        ZSIGN(JDIMC)
      INTEGER CGS,CGF,DIFF,PROFIT,R,T
C INITIALIZE.
      CGF = CG
      IP = 0
      CGS = CG
      DO 10 LL=1,NG
        IF ( WG(LL) .GT. CGS ) GO TO 20
        IP = IP + PG(LL)
        CGS = CGS - WG(LL)
   10 CONTINUE
   20 LL = LL - 1
      IF ( CGS .EQ. 0 ) GO TO 50
      PG(NG+1) = 0
      WG(NG+1) = CG + 1
      LIM = IP + CGS*PG(LL+2)/WG(LL+2)
      A = WG(LL+1) - CGS
      LIM1 = FLOAT(IP) - A*FLOAT(PG(LL))/FLOAT(WG(LL)) +
     1       FLOAT(PG(LL+1))
      IF ( LIM1 .GT. LIM ) LIM = LIM1
      IF ( LIM .LE. ZG ) RETURN
      LEM = IP + CGS*PG(LL+1)/WG(LL+1)
      IF ( LEM .LE. MUBF ) GO TO 400
      MINK = CG + 1
      MIN(NG) = MINK
      DO 30 J=2,NG
        KK = NG + 2 - J
        IF ( WG(KK) .LT. MINK ) MINK = WG(KK)
        MIN(KK-1) = MINK
   30 CONTINUE
      DO 40 J=1,NG
        XXG(J) = 0
   40 CONTINUE
      PROFIT = 0
      LOLD = NG
      II = 1
      GO TO 170
   50 IF ( ZG .GE. IP ) RETURN
      ZG = IP
      DO 60 J=1,LL
        XG(J) = 1
   60 CONTINUE
      NN = LL + 1
      DO 70 J=NN,NG
        XG(J) = 0
   70 CONTINUE
      RETURN
C TRY TO INSERT THE II-TH ITEM INTO THE CURRENT SOLUTION.
   80 IF ( WG(II) .LE. CG ) GO TO 90
      II1 = II+1
      IF ( ZG .GE. CG*PG(II1)/WG(II1) + PROFIT ) GO TO 280
      II = II1
      GO TO 80
C BUILD A NEW CURRENT SOLUTION.
   90 IP = PSIGN(II)
      CGS = CG - WSIGN(II)
      IN = ZSIGN(II)
      DO 100 LL=IN,NG
        IF ( WG(LL) .GT. CGS ) GO TO 160
        IP = IP + PG(LL)
        CGS = CGS - WG(LL)
  100 CONTINUE
      LL = NG
  110 IF ( ZG .GE. IP + PROFIT ) GO TO 280
      ZG = IP + PROFIT
      NN = II - 1
      DO 120 J=1,NN
        XG(J) = XXG(J)
  120 CONTINUE
      DO 130 J=II,LL
        XG(J) = 1
  130 CONTINUE
      IF ( LL .EQ. NG ) GO TO 150
      NN = LL + 1
      DO 140 J=NN,NG
        XG(J) = 0
  140 CONTINUE
  150 IF ( ZG .NE. LIM ) GO TO 280
      CG = CGF
      RETURN
  160 LL = LL - 1
      IF ( CGS .EQ. 0 ) GO TO 110
      IF ( ZG .GE. PROFIT + IP + CGS*PG(LL+1)/WG(LL+1) ) GO TO 280
C SAVE THE CURRENT SOLUTION.
  170 WSIGN(II) = CG - CGS
      PSIGN(II) = IP
      ZSIGN(II) = LL + 1
      XXG(II) = 1
      NN = LL - 1
      IF ( NN .LT. II) GO TO 190
      DO 180 J=II,NN
        WSIGN(J+1) = WSIGN(J) - WG(J)
        PSIGN(J+1) = PSIGN(J) - PG(J)
        ZSIGN(J+1) = LL + 1
        XXG(J+1) = 1
  180 CONTINUE
  190 J1 = LL + 1
      DO 200 J=J1,LOLD
        WSIGN(J) = 0
        PSIGN(J) = 0
        ZSIGN(J) = J
  200 CONTINUE
      LOLD = LL
      CG = CGS
      PROFIT = PROFIT + IP
      IF ( LL - (NG - 2) ) 240, 220, 210
  210 II = NG
      GO TO 250
  220 IF ( CG .LT. WG(NG) ) GO TO 230
      CG = CG - WG(NG)
      PROFIT = PROFIT + PG(NG)
      XXG(NG) = 1
  230 II = NG - 1
      GO TO 250
  240 II = LL + 2
      IF ( CG .GE. MIN(II-1) ) GO TO 80
C SAVE THE CURRENT OPTIMAL SOLUTION.
  250 IF ( ZG .GE. PROFIT ) GO TO 270
      ZG = PROFIT
      DO 260 J=1,NG
        XG(J) = XXG(J)
  260 CONTINUE
      IF ( ZG .NE. LIM ) GO TO 270
      CG = CGF
      RETURN
  270 IF ( XXG(NG) .EQ. 0 ) GO TO 280
      XXG(NG) = 0
      CG = CG + WG(NG)
      PROFIT = PROFIT - PG(NG)
C BACKTRACK.
  280 NN = II - 1
      IF ( NN .EQ. 0 ) RETURN
      DO 290 JJ=1,NN
        INDEX = II - JJ
        IF ( XXG(INDEX) .EQ. 1 ) GO TO 300
  290 CONTINUE
      RETURN
  300 KK = II - JJ
      R = CG
      CG = CG + WG(KK)
      PROFIT = PROFIT - PG(KK)
      XXG(KK) = 0
      IF ( R .LT. MIN(KK) ) GO TO 310
      II = KK + 1
      GO TO 80
  310 NN = KK + 1
      II = KK
C TRY TO SUBSTITUTE THE NN-TH ITEM FOR THE KK-TH.
  320 IF ( ZG .GE. PROFIT + CG*PG(NN)/WG(NN) ) GO TO 280
      DIFF = WG(NN) - WG(KK)
      IF ( DIFF ) 380, 330, 340
  330 NN = NN + 1
      GO TO 320
  340 IF ( DIFF .GT. R ) GO TO 330
      IF ( ZG .GE. PROFIT + PG(NN) ) GO TO 330
      ZG = PROFIT + PG(NN)
      DO 350 J=1,KK
        XG(J) = XXG(J)
  350 CONTINUE
      JJ = KK + 1
      DO 360 J=JJ,NG
        XG(J) = 0
  360 CONTINUE
      XG(NN) = 1
      IF ( ZG .NE. LIM ) GO TO 370
      CG = CGF
      RETURN
  370 R = R - DIFF
      KK = NN
      NN = NN + 1
      GO TO 320
  380 T = R - DIFF
      IF ( T .LT. MIN(NN) ) GO TO 330
      IF ( ZG .GE. PROFIT + PG(NN) + T*PG(NN+1)/WG(NN+1) ) GO TO 280
      CG = CG - WG(NN)
      PROFIT = PROFIT + PG(NN)
      XXG(NN) = 1
      II = NN + 1
      WSIGN(NN) = WG(NN)
      PSIGN(NN) = PG(NN)
      ZSIGN(NN) = II
      N1 = NN + 1
      DO 390 J=N1,LOLD
        WSIGN(J) = 0
        PSIGN(J) = 0
        ZSIGN(J) = J
  390 CONTINUE
      LOLD = NN
      GO TO 80
  400 ZG = MUBF
      DO 410 J=1,NG
        XG(J) = 0
  410 CONTINUE
      RETURN
      END
      SUBROUTINE KPMIN(KK,PEN,U,D,ZP,IY,KUBF,
     1                 JDIMC,JDIMC1,P,W,IND,IX,PW,
     2                 DMYC1,DMYC2,DMYC3,DMYC4,DMYC5)
C
C SOLVE A 0-1 SINGLE KNAPSACK PROBLEM IN  MINIMIZATION FORM THROUGH
C A SUBROUTINE, KPMAX, FOR THE CORRESPONDING MAXIMIZATION FORM.
C
      INTEGER PEN(JDIMC),U(JDIMC),IY(JDIMC),D,ZP
      INTEGER P(JDIMC1),W(JDIMC1),IND(JDIMC),IX(JDIMC),DS,SU,SPEN
      REAL    PW(JDIMC)
      INTEGER DMYC1(JDIMC),DMYC2(JDIMC),DMYC3(JDIMC),DMYC4(JDIMC),
     1        DMYC5(JDIMC)
      SU = 0
      SPEN = 0
      DO 10 K=1,KK
        SU = SU + U(K)
        PW(K) = FLOAT(PEN(K))/FLOAT(U(K))
        IX(K) = K
        SPEN = SPEN + PEN(K)
   10 CONTINUE
      DS = SU - D
      I = 0
      IU = 0
      IP = 0
      CALL SORTR(KK,PW,IX,JDIMC)
      DO 20 JK=1,KK
        K = IX(JK)
        IY(K) = 1
        IF ( U(K) .GT. DS ) GO TO 20
        I = I + 1
        P(I) = PEN(K)
        W(I) = U(K)
        IP = IP + P(I)
        IU = IU + W(I)
        IND(I) = K
   20 CONTINUE
      IF ( IU .LE. DS ) GO TO 60
      IZM = 0
      IF ( I .EQ. 0 ) GO TO 50
      IZM = - 1
      CALL KPMAX(I,P,W,DS,IZM,IX,SPEN-KUBF,
     1           JDIMC+1,JDIMC,DMYC1,DMYC2,DMYC3,DMYC4,DMYC5)
   30 DO 40 J=1,I
        K = IND(J)
        IY(K) = 1 - IX(J)
   40 CONTINUE
   50 ZP = SPEN - IZM
      RETURN
   60 DO 70 J=1,I
        IX(J) = 1
   70 CONTINUE
      IZM = IP
      GO TO 30
      END
      SUBROUTINE PEN0(J,M,P,W,Q,A,V,L1,PAK,KAP,PAKL,IP,IR,IL,IF,
     1                PENALT,JFO,JUB,JZ,INF,JDIMR,JDIMC,JNLEV)
C
C COMPUTE THE PENALTY CORRESPONDING TO AN ITEM  J  WHICH WAS
C ASSIGNED TO NO KNAPSACK.
C JFO = 1 IFF ITEM  J  CAN BE INSERTED IN ONLY ONE KNAPSACK.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),Q(JDIMR),A(JDIMR,JDIMC),
     1        V(JNLEV,JDIMR),PAK(JDIMR,JDIMC),KAP(JDIMR,JDIMC),
     2        PAKL(JDIMR),IP(JDIMR),IR(JDIMR),IL(JDIMR),IF(JDIMR)
      INTEGER PENALT,PMIN
      PMIN = INF
      JFO = 0
      DO 80 I=1,M
        IF ( A(I,J) .EQ. (- 1) ) GO TO 80
        IF ( W(I,J) .GT. Q(I) ) GO TO 80
        JFO = JFO + 1
        JJ = KAP(I,J)
        KL = IL(I)
        IF ( JJ .LE. KL ) GO TO 70
        KR = IR(I) - W(I,J)
        KP = IP(I) + P(I,J)
   10   IF ( KR .GE. 0 ) GO TO 20
        JKL = PAK(I,KL)
        KR = KR + W(I,JKL)
        KP = KP - P(I,JKL)
        KL = KL - 1
        GO TO 10
   20   KRTOT = Q(I) - W(I,J)
        W(I,J) = W(I,J) + INF
   30   KL = KL + 1
        IF ( KL .LE. PAKL(I) ) GO TO 40
        RUB = KP
        GO TO 60
   40   JKL = PAK(I,KL)
        IF ( W(I,JKL) .GT. KR ) GO TO 50
        KR = KR - W(I,JKL)
        KP = KP + P(I,JKL)
        GO TO 30
   50   IF ( W(I,JKL) .GT. KRTOT ) GO TO 30
        RUB = FLOAT(KP) + FLOAT(P(I,JKL)*KR)/FLOAT(W(I,JKL))
   60   IUB = RUB
        W(I,J) = W(I,J) - INF
        LAM = V(L1,I) - ( IUB + IF(I) )
        IF ( LAM .LE. 0 ) GO TO 70
        IF ( LAM .LT. PMIN ) PMIN = LAM
        IF ( JUB - LAM .LE. JZ ) JFO = JFO - 1
        GO TO 80
   70   PMIN = 0
   80 CONTINUE
      PENALT = PMIN
      RETURN
      END
      SUBROUTINE PEN1(J,M,P,W,X,V,L1,PAK,KAP,PAKL,IP,IR,IL,IF,PENALT,
     1                JFO,JUB,JZ,JDIMR,JDIMC,JNLEV)
C
C COMPUTE THE PENALTY CORRESPONDING TO AN ITEM  J  WHICH WAS
C ASSIGNED MORE THAN ONE KNAPSACK.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),X(JDIMR,JDIMC),
     1        V(JNLEV,JDIMR),PAK(JDIMR,JDIMC),KAP(JDIMR,JDIMC),
     2        PAKL(JDIMR),IP(JDIMR),IR(JDIMR),IL(JDIMR),IF(JDIMR)
      INTEGER PENALT,PSUM,PMAX
      PSUM = 0
      PMAX = 0
      JFO = 0
      DO 80 I=1,M
        IF ( X(I,J) .EQ. 0 ) GO TO 80
        JJ = KAP(I,J)
        KL = IL(I)
        KP = IP(I)
        KR = IR(I)
        IF ( JJ - (KL + 1) ) 30,10,80
   10   IF ( KL + 1 .EQ. PAKL(I) ) GO TO 20
        JKL = PAK(I,KL+2)
        RUB = FLOAT(KP) + FLOAT(P(I,JKL)*KR)/FLOAT(W(I,JKL))
        GO TO 70
   20   RUB = KP
        GO TO 70
   30   KP = KP - P(I,J)
        KR = KR + W(I,J)
        LA = KL + 1
        L2 = PAKL(I)
        IF ( LA .LE. L2 ) GO TO 40
        RUB = KP
        GO TO 70
   40   DO 50 JL=LA,L2
          JJ = PAK(I,JL)
          IF ( W(I,JJ) .GT. KR ) GO TO 60
          KR = KR - W(I,JJ)
          KP = KP + P(I,JJ)
   50   CONTINUE
        RUB = KP
        GO TO 70
   60   RUB = FLOAT(KP) + FLOAT(P(I,JJ)*KR)/FLOAT(W(I,JJ))
   70   IUB = RUB
        LAM = V(L1,I) - (IUB + IF(I))
        IF ( LAM .LE. 0 ) GO TO 80
        PSUM = PSUM + LAM
        IF ( LAM .GT. PMAX ) PMAX = LAM
        IF ( JUB - LAM .LE. JZ ) JFO = I
   80 CONTINUE
      PENALT = PSUM - PMAX
      RETURN
      END
      SUBROUTINE PREPEN(N,M,P,W,Q,B,A,MIND,PAK,KAP,PAKL,IP,IR,IL,IF,
     1                  JDIMR,JDIMC)
C
C DETERMINE  PAK ,  KAP  AND  PAKL (POINTERS FOR COMPUTING PENALTIES)
C AND  IP ,  IR ,  IL  AND  IF (GREEDY INITIAL SOLUTIONS).
C IF = PROFIT OF FIXED ITEMS;
C IL = BREAK ITEM (LAST WHICH FITS);
C IP = PROFIT OF THE FIRST  IL  ITEMS;
C IR = RESIDUAL CAPACITY CORRESPONDING TO  IP .
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),Q(JDIMR),B(JDIMC),
     1        A(JDIMR,JDIMC),MIND(JDIMR,JDIMC),PAK(JDIMR,JDIMC),
     2        KAP(JDIMR,JDIMC),PAKL(JDIMR),IP(JDIMR),IR(JDIMR),
     3        IL(JDIMR),IF(JDIMR)
      DO 60 I=1,M
        K = 0
        ISFIX = 0
        DO 20 JS=1,N
          J = MIND(I,JS)
          IF ( B(J) .EQ. 0 ) GO TO 10
          IF ( W(I,J) .GT. Q(I) ) GO TO 20
          IF ( A(I,J) .EQ. (- 1) ) GO TO 20
          K = K + 1
          PAK(I,K) = J
          KAP(I,J) = K
          GO TO 20
   10     IF ( A(I,J) .EQ. 1 ) ISFIX = ISFIX + P(I,J)
   20   CONTINUE
        PAKL(I) = K
        LK = 0
        IPK = 0
        IRK = Q(I)
        IF ( K .EQ. 0 ) GO TO 50
        DO 30 JK=1,K
          J = PAK(I,JK)
          IF ( W(I,J) .GT. IRK ) GO TO 40
          IRK = IRK - W(I,J)
          IPK = IPK + P(I,J)
   30   CONTINUE
        LK = K
        GO TO 50
   40   LK = JK - 1
   50   IP(I) = IPK
        IR(I) = IRK
        IL(I) = LK
        IF(I) = ISFIX
   60 CONTINUE
      RETURN
      END
      SUBROUTINE SKP(N,P,W,KQI,VSTI,I,KQRI,B,A,X,Y,U,JSTEP,
     1               JDIMR,JDIMC,JDIMC1,KPUNT,JP,KX,KP,KW,R,DMYC1,
     2               DMYC2,DMYC3,DMYC4,DMYC5)
C
C SOLVE A 0-1 SINGLE KNAPSACK PROBLEM.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),B(JDIMC),
     1        A(JDIMR,JDIMC),U(JDIMC),VSTI,X(JDIMR,JDIMC),Y(JDIMC)
      INTEGER KPUNT(JDIMC),JP(JDIMC),KP(JDIMC1),KW(JDIMC1),KX(JDIMC)
      INTEGER DMYC1(JDIMC),DMYC2(JDIMC),DMYC3(JDIMC),DMYC4(JDIMC),
     1        DMYC5(JDIMC)
      REAL    R(JDIMC)
      KN = 0
      KSW = 0
      DO 10 J=1,N
        IF ( B(J) .LE. 0 ) GO TO 10
        IF ( A(I,J) .NE. 0 ) GO TO 10
        IF ( W(I,J) .GT. KQI ) GO TO 10
        KKP = P(I,J) - U(J)
        IF ( KKP .LE. 0 ) GO TO 10
        KN = KN + 1
        R(KN) = FLOAT(KKP)/FLOAT(W(I,J))
        JP(KN) = KN
        KPUNT(KN) = J
        KSW = KSW + W(I,J)
   10 CONTINUE
      IF ( JSTEP .NE. 4 ) GO TO 30
      DO 20 J=1,N
        Y(J) = 0
   20 CONTINUE
   30 KQRI = KQI
      IF ( KN .EQ. 0 ) RETURN
      IF ( KSW .GT. KQI ) GO TO 50
      DO 40 KJ=1,KN
        J = KPUNT(KJ)
        VSTI = VSTI + (P(I,J) - U(J))
        KQRI = KQRI - W(I,J)
        IF ( JSTEP .EQ. 2 ) X(I,J) = 1
        IF ( JSTEP .EQ. 4 ) Y(J) = 1
   40 CONTINUE
      RETURN
   50 CALL SORTR(KN,R,JP,JDIMC)
      DO 60 KJ=1,KN
        K = JP(KJ)
        J = KPUNT(K)
        KP(KJ) = P(I,J) - U(J)
        KW(KJ) = W(I,J)
        JP(KJ) = J
   60 CONTINUE
      MUBF = 0
      JVSTI = - 1
      CALL KPMAX(KN,KP,KW,KQI,JVSTI,KX,MUBF,JDIMC+1,JDIMC,
     1           DMYC1,DMYC2,DMYC3,DMYC4,DMYC5)
      VSTI = VSTI + JVSTI
      KQRI = KQI
      DO 70 KJ=1,KN
        J = JP(KJ)
        IF ( JSTEP .EQ. 2 ) X(I,J) = KX(KJ)
        IF ( JSTEP .EQ. 4 ) Y(J) = KX(KJ)
        KQRI = KQRI - KX(KJ)*W(I,J)
   70 CONTINUE
      RETURN
      END
      SUBROUTINE SORTI(N,A,V,JDA)
C
C SORT THE INTEGER ARRAY A BY DECREASING VALUES (DERIVED FROM
C SUBROUTINE SORTZV OF THE C.E.R.N. LIBRARY).
C
C JDA           = LENGTH OF ARRAY A;
C N             = NUMBER OF ITEMS OF A TO BE SORTED;
C V(I) (INPUT)  = POINTER TO THE I-TH ITEM TO BE SORTED;
C V(I) (OUTPUT) = POINTER TO THE I-TH ITEM OF THE SORTED ARRAY.
C
C ON RETURN, ARRAY A IS UNCHANGED.
C
      INTEGER V(N),IU(20),IL(20)
      INTEGER A(JDA),T
      II = 1
      JJ = N
      IF ( N .LE. 1 ) RETURN
      M = 1
      I = II
      J = JJ
   10 IF ( I .GE. J ) GO TO 80
   20 K = I
      IJ = (J + I)/2
      IV = V(IJ)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 30
      V(IJ) = KI
      V(I) = IV
      IV = V(IJ)
      T = A(IV)
   30 L = J
      KI = V(J)
      IF ( A(KI) .LE. T ) GO TO 50
      V(IJ) = KI
      V(J) = IV
      IV = V(IJ)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 50
      V(IJ) = KI
      V(I) = IV
      IV = V(IJ)
      T = A(IV)
      GO TO 50
   40 V(L) = V(K)
      V(K) = IVT
   50 L = L - 1
      KI = V(L)
      IF ( A(KI) .LT. T ) GO TO 50
      IVT = KI
   60 K = K + 1
      KI = V(K)
      IF ( A(KI) .GT. T ) GO TO 60
      IF ( K .LE. L ) GO TO 40
      IF ( L - I .LE. J - K ) GO TO 70
      IL(M) = I
      IU(M) = L
      I = K
      M = M + 1
      GO TO 90
   70 IL(M) = K
      IU(M) = J
      J = L
      M = M + 1
      GO TO 90
   80 M = M - 1
      IF ( M .EQ. 0 ) RETURN
      I = IL(M)
      J = IU(M)
   90 IF ( J - I .GE. II ) GO TO 20
      IF ( I .EQ. II ) GO TO 10
      I = I - 1
  100 I = I + 1
      IF ( I .EQ. J ) GO TO 80
      IV = V(I+1)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 100
      K = I
  110 V(K+1) = V(K)
      K = K - 1
      KI = V(K)
      IF ( T .GT. A(KI) ) GO TO 110
      V(K+1) = IV
      GO TO 100
      END
      SUBROUTINE SORTR(N,A,V,JDA)
C
C SORT THE REAL ARRAY A BY DECREASING VALUES (DERIVED FROM SUBROUTINE
C SORTZV OF THE C.E.R.N. LIBRARY).
C
C JDA           = LENGTH OF ARRAY A;
C N             = NUMBER OF ITEMS OF A TO BE SORTED;
C V(I) (INPUT)  = POINTER TO THE I-TH ITEM TO BE SORTED;
C V(I) (OUTPUT) = POINTER TO THE I-TH ITEM OF THE SORTED ARRAY.
C
C ON RETURN, ARRAY A IS UNCHANGED.
C
      INTEGER V(N),IU(20),IL(20)
      REAL    A(JDA)
      II = 1
      JJ = N
      IF ( N .LE. 1 ) RETURN
      M = 1
      I = II
      J = JJ
   10 IF ( I .GE. J ) GO TO 80
   20 K = I
      IJ = (J + I)/2
      IV = V(IJ)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 30
      V(IJ) = KI
      V(I) = IV
      IV = V(IJ)
      T = A(IV)
   30 L = J
      KI = V(J)
      IF ( A(KI) .LE. T ) GO TO 50
      V(IJ) = KI
      V(J) = IV
      IV = V(IJ)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 50
      V(IJ) = KI
      V(I) = IV
      IV = V(IJ)
      T = A(IV)
      GO TO 50
   40 V(L) = V(K)
      V(K) = IVT
   50 L = L - 1
      KI = V(L)
      IF ( A(KI) .LT. T ) GO TO 50
      IVT = KI
   60 K = K + 1
      KI = V(K)
      IF ( A(KI) .GT. T ) GO TO 60
      IF ( K .LE. L ) GO TO 40
      IF ( L - I .LE. J - K ) GO TO 70
      IL(M) = I
      IU(M) = L
      I = K
      M = M + 1
      GO TO 90
   70 IL(M) = K
      IU(M) = J
      J = L
      M = M + 1
      GO TO 90
   80 M = M - 1
      IF ( M .EQ. 0 ) RETURN
      I = IL(M)
      J = IU(M)
   90 IF ( J - I .GE. II ) GO TO 20
      IF ( I .EQ. II ) GO TO 10
      I = I - 1
  100 I = I + 1
      IF ( I .EQ. J ) GO TO 80
      IV = V(I+1)
      T = A(IV)
      KI = V(I)
      IF ( A(KI) .GE. T ) GO TO 100
      K = I
  110 V(K+1) = V(K)
      K = K - 1
      KI = V(K)
      IF ( T .GT. A(KI) ) GO TO 110
      V(K+1) = IV
      GO TO 100
      END
      SUBROUTINE TERMIN(JFI,INVST,JUB,IMULT,Z,KVST,NUMNOD,MINMAX,
     1                  M,N,P,LAM,JDIMR,JDIMC,JB,BACK)
C
C TERMINATE THE EXECUTION.
C
      INTEGER Z,P(JDIMR,JDIMC),BACK
      INTEGER ZM
      IF ( JFI .EQ. 1 ) GO TO 10
      IF ( JUB .LT. Z ) JUB = Z
      JB = INVST - JUB*IMULT
      IF ( Z .EQ. (-7) ) GO TO 10
      ZM = Z
      Z = 0
      IF ( ZM .GT. KVST ) Z = INVST - ZM*IMULT
      BACK = NUMNOD
   10 IF ( MINMAX .EQ. 2 ) RETURN
C RE-STORE THE ORIGINAL MINIMIZATION PROBLEM.
      DO 30 I=1,M
        DO 20 J=1,N
          IF ( P(I,J) .GT. 0 ) P(I,J) = LAM - P(I,J)
   20   CONTINUE
   30 CONTINUE
      RETURN
      END
      SUBROUTINE TRIN(P,N,M,INVST,LAM,JDIMR,JDIMC)
C
C TRANSFORM AN INSTANCE OF GAP IN MINIMIZATION FORM INTO AN
C EQUIVALENT INSTANCE IN MAXIMIZATION FORM.
C
      INTEGER P(JDIMR,JDIMC)
      INVST = 0
      MAX = 0
      DO 20 J=1,N
        DO 10 I=1,M
          IF ( P(I,J) .GT. MAX ) MAX = P(I,J)
   10   CONTINUE
   20 CONTINUE
      LAM = MAX + 1
      DO 40 J=1,N
        DO 30 I=1,M
          P(I,J) = LAM - P(I,J)
   30   CONTINUE
        INVST = INVST + LAM
   40 CONTINUE
      RETURN
      END
      SUBROUTINE UBFJV(N,M,P,W,Q,B,A,JFJVU,XRS,VFJV,VSTAR,INF,
     1                 JDIMR,JDIMC,JDIMC1,DMYC1,DMYC2,DMYC3,DMYCC1,
     2                 DMYCC2,DMYCR1,DMYC4,DMYC5,DMYC6,DMYC7,DMYC8,
     3                 U,NOTS,Y,VST,KQ,KQR,MINY,X)
C
C COMPUTE THE FISHER-JAIKUMAR-VAN WASSENHOVE UPPER BOUND.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),Q(JDIMR),B(JDIMC),
     1        A(JDIMR,JDIMC),XRS(JDIMC)
      INTEGER VSTAR,VFJV
      INTEGER U(JDIMC),VST(JDIMR),KQ(JDIMR),KQR(JDIMR),
     1        NOTS(JDIMC),Y(JDIMC),DELTA,VSTI
      INTEGER X(JDIMR,JDIMC),MINY(JDIMC)
      INTEGER DMYC1(JDIMC),DMYC2(JDIMC),DMYC3(JDIMC),DMYC4(JDIMC),
     1        DMYC5(JDIMC),DMYC6(JDIMC),DMYC7(JDIMC),DMYC8(JDIMC),
     2        DMYCC1(JDIMC1),DMYCC2(JDIMC1)
      REAL    DMYCR1(JDIMC)
C
C STEP 1.
C
      VFJV = 0
      DO 20 I=1,M
        KQ(I) = Q(I)
        VST(I) = 0
        DO 10 J=1,N
          X(I,J) = 0
   10   CONTINUE
   20 CONTINUE
      JFJVU = 0
      DO 50 J=1,N
        U(J) = 0
        IF ( B(J) .EQ. 1 ) GO TO 50
        DO 30 I=1,M
          IF ( A(I,J) .EQ. 1 ) GO TO 40
   30   CONTINUE
   40   JFJVU = JFJVU + P(I,J)
   50 CONTINUE
   60 JREP = 0
      DO 110 J=1,N
        IF ( B(J) .LE. 0 ) GO TO 110
        MAX = - 1
        MAX2 = - 1
        DO 80 I=1,M
          IF ( A (I,J) .EQ. (- 1) ) GO TO 80
          IF ( W(I,J) .GT. KQ(I) ) GO TO 80
          IF ( P(I,J) .LE. MAX2 ) GO TO 80
          IF ( P(I,J) .GT. MAX ) GO TO 70
          MAX2 = P(I,J)
          GO TO 80
   70     MAX2 = MAX
          MAX = P(I,J)
          IMAX = I
   80   CONTINUE
        JFJVU = JFJVU - U(J)
        U(J) = MAX2
        IF ( MAX .GT. 0 ) GO TO 90
        JFJVU = - 1
        GO TO 360
   90   IF ( MAX2 .LE. 0 ) GO TO 100
        JFJVU = JFJVU + U(J)
        GO TO 110
  100   KQ(IMAX) = KQ(IMAX) - W(IMAX,J)
        JFJVU = JFJVU + P(IMAX,J)
        B(J) = - IMAX
        JREP = 1
  110 CONTINUE
      IF ( JREP .EQ. 1 ) GO TO 60
C
C STEP 2.
C
      DO 120 I=1,M
        CALL SKP(N,P,W,KQ(I),VST(I),I,KQR(I),B,A,X,Y,U,2,
     1           JDIMR,JDIMC,JDIMC+1,DMYC1,DMYC2,DMYC3,DMYCC1,DMYCC2,
     2           DMYCR1,DMYC4,DMYC5,DMYC6,DMYC7,DMYC8)
        JFJVU = JFJVU + VST(I)
  120 CONTINUE
C
C STEP 3.
C
  130 IF ( JFJVU .LE. VSTAR ) GO TO 360
C INITIALIZE NOTS.
      JNS = 0
      DO 150 J=1,N
        IF ( B(J) .LE. 0 ) GO TO 150
        DO 140 I=1,M
          IF ( X(I,J) .EQ. 1 ) GO TO 150
  140   CONTINUE
        JNS = JNS + 1
        NOTS(JNS) = J
  150 CONTINUE
C ITERATIVE PART.
  160 IF ( JNS .GT. 0 ) GO TO 240
      DO 230 J=1,N
        IF ( B(J) .EQ. 0 ) GO TO 200
        IF ( B(J) .GT. 0 ) GO TO 170
        I = - B(J)
        GO TO 190
  170   DO 180 I=1,M
          IF ( X(I,J) .EQ. 1 ) GO TO 190
  180   CONTINUE
  190   XRS(J) = I
        VFJV = VFJV + P(I,J)
        GO TO 230
  200   DO 210 I=1,M
          IF ( A(I,J) .EQ. 1 ) GO TO 220
  210   CONTINUE
  220   XRS(J) = I
        VFJV = VFJV + P(I,J)
  230 CONTINUE
      GO TO 360
  240 MAX = - 1
      DO 260 JJ=1,JNS
        J = NOTS(JJ)
        DO 250 I=1,M
          IF ( P(I,J) - U(J) .NE. 0 ) GO TO 250
          IF ( W(I,J) .GT. KQR(I) ) GO TO 250
          IF ( P(I,J) .LE. MAX ) GO TO 250
          MAX = P(I,J)
          IMAX = I
          JMAX = J
          JJMAX = JJ
  250   CONTINUE
  260 CONTINUE
      IF ( MAX .LT. 0 ) GO TO 270
      X(IMAX,JMAX) = 1
      KQR(IMAX) = KQR(IMAX) - W(IMAX,JMAX)
      NOTS(JJMAX) = NOTS(JNS)
      JNS = JNS - 1
      GO TO 160
C
C STEP 4.
C
  270 DO 330 JJ=1,JNS
        J = NOTS(JJ)
        MIN = INF
        MIN2 = MIN
        DO 300 I=1,M
          IF ( A(I,J) .NE. 0 ) GO TO 300
          IF ( W(I,J) .GT. KQ(I) ) GO TO 300
          A(I,J) = - 2
          KQI = KQ(I) - W(I,J)
          VSTI = P(I,J) - U(J)
          CALL SKP(N,P,W,KQI,VSTI,I,KQRI,B,A,X,Y,U,4,
     1             JDIMR,JDIMC,JDIMC+1,DMYC1,DMYC2,DMYC3,DMYCC1,DMYCC2,
     2             DMYCR1,DMYC4,DMYC5,DMYC6,DMYC7,DMYC8)
          A(I,J) = 0
          Y(J) = 1
          DELTA = VST(I) - VSTI
          IF ( DELTA .GE. MIN2 ) GO TO 300
          IF ( DELTA .LT. MIN ) GO TO 280
          MIN2 = DELTA
          IF ( MIN2 .LE. 0 ) GO TO 330
          GO TO 300
  280     MIN2 = MIN
          MIN = DELTA
          MINZ = VSTI
          MINKQ = KQRI
          MINI = I
          DO 290 K=1,N
            MINY(K) = Y(K)
  290     CONTINUE
          IF ( MIN2 .LE. 0 ) GO TO 330
  300   CONTINUE
        JSTAR = J
        ISTAR = MINI
        DO 320 K=1,N
          IF ( MINY(K) .EQ. 0 ) GO TO 320
          DO 310 I=1,M
            IF ( I .EQ. ISTAR ) GO TO 310
            IF ( X(I,K) .EQ. 1 ) GO TO 330
  310     CONTINUE
  320   CONTINUE
        GO TO 340
  330 CONTINUE
      GO TO 360
C
C STEP 5.
C
  340 U(JSTAR) = U(JSTAR) - MIN2
      VST(ISTAR) = MINZ + MIN2
      KQR(ISTAR) = MINKQ
      DO 350 J=1,N
        X(ISTAR,J) = MINY(J)
  350 CONTINUE
      JFJVU = JFJVU - MIN
      GO TO 130
C
C RETURN.
C
  360 DO 370 J=1,N
        IF ( B(J) .LT. 0 ) B(J) = 1
  370 CONTINUE
      RETURN
      END
      SUBROUTINE UBRS(N,M,P,W,Q,B,A,JRSU,XRS,VRS,Z,INF,
     1                JDIMR,JDIMC,JDIMC1,QH,PENRS,PEN,U,XK,
     2                DMYC1,DMYC2,DMYC3,DMYC4,DMYC5,DMYC6,DMYC7,
     3                ISMAX,KPOINT,DMYCC1,DMYCC2,DMYCR1)
C
C COMPUTE THE IMPROVED ROSS-SOLAND UPPER BOUND.
C
      INTEGER P(JDIMR,JDIMC),W(JDIMR,JDIMC),Q(JDIMR),B(JDIMC),
     1        A(JDIMR,JDIMC),XRS(JDIMC),VRS,Z
      INTEGER QH(JDIMR),PENRS(JDIMC),PEN(JDIMC),U(JDIMC),XK(JDIMC),
     1        ISMAX(JDIMC),KPOINT(JDIMC)
      INTEGER DMYC1(JDIMC),DMYC2(JDIMC),DMYC3(JDIMC),DMYC4(JDIMC),
     1        DMYC5(JDIMC),DMYC6(JDIMC),DMYC7(JDIMC)
      INTEGER DMYCC1(JDIMC1),DMYCC2(JDIMC1)
      REAL    DMYCR1(JDIMC)
      INTEGER FMAX,SMAX,D
      DO 10 I=1,M
        QH(I) = 0
   10 CONTINUE
      JV = 0
      MIND = INF
      DO 60 J=1,N
        IF ( B(J) .EQ. 1 ) GO TO 30
        DO 20 I=1,M
          IF ( A(I,J) .NE. 1 ) GO TO 20
          JV = JV + P(I,J)
          XRS(J) = I
          ISMAX(J) = 0
          GO TO 60
   20   CONTINUE
   30   FMAX = - INF
        IF = 0
        SMAX = - 2*INF
        DO 50 I=1,M
          IF ( A(I,J) .EQ. (- 1) ) GO TO 50
          IF ( W(I,J) .GT. Q(I) ) GO TO 50
          IF ( SMAX .GE. P(I,J) ) GO TO 50
          IF ( FMAX .GE. P(I,J) ) GO TO 40
          SMAX = FMAX
          IS = IF
          FMAX = P(I,J)
          IF = I
          GO TO 50
   40     SMAX = P(I,J)
          IS = I
   50   CONTINUE
        IF ( IF .EQ. 0 ) GO TO 160
        XRS(J) = IF
        ISMAX(J) = IS
        JV = JV + FMAX
        QH(IF) = QH(IF) + W(IF,J)
        PENRS(J) = FMAX - SMAX
        IF ( FMAX - SMAX .LT. MIND ) MIND = FMAX - SMAX
   60 CONTINUE
      DO 70 I=1,M
        IF ( QH(I) .GT. Q(I) ) GO TO 80
   70 CONTINUE
      JRSU = JV
      VRS = JV
      RETURN
   80 JRSU = JV - MIND
      VRS = 0
      IF ( JRSU .LE. Z ) RETURN
C COMPUTE THE MINIMUM PENALTY FOR EACH UNSATISFIED KNAPSACK.
      JRSU = JV
      DO 120 I=1,M
        IF ( QH(I) .LE. Q(I) ) GO TO 120
        D = QH(I) - Q(I)
        KK = 0
        MIND = INF
        DO 90 J=1,N
          IF ( B(J) .EQ. 0 ) GO TO 90
          IF ( XRS(J) .NE. I ) GO TO 90
          KK = KK + 1
          PEN(KK) = PENRS(J)
          U(KK) = W(I,J)
          IF ( PEN(KK) .LT. MIND ) MIND = PEN(KK)
          KPOINT(KK) = J
   90   CONTINUE
        IF ( JRSU - MIND .LE. Z ) GO TO 110
        KUBF = JRSU - Z
        CALL KPMIN(KK,PEN,U,D,MIND,XK,KUBF,
     1             JDIMC,JDIMC+1,DMYCC1,DMYCC2,DMYC6,DMYC7,DMYCR1,
     2             DMYC1,DMYC2,DMYC3,DMYC4,DMYC5)
        DO 100 KJ=1,KK
          IF ( XK(KJ) .EQ. 0 ) GO TO 100
          J = KPOINT(KJ)
          ISMAX(J) = - ISMAX(J)
  100   CONTINUE
  110   JRSU = JRSU - MIND
        IF ( JRSU .LE. Z ) RETURN
  120 CONTINUE
C TRY TO OBTAIN A FEASIBLE AND OPTIMAL SOLUTION.
      DO 130 I=1,M
        QH(I) = 0
  130 CONTINUE
      DO 150 J=1,N
        IF ( B(J) .EQ. 0 ) GO TO 150
        IF ( ISMAX(J) .GE. 0 ) GO TO 140
        XRS(J) = - ISMAX(J)
  140   I = XRS(J)
        QH(I) = QH(I) + W(I,J)
        IF ( QH(I) .GT. Q(I) ) RETURN
  150 CONTINUE
      VRS = JRSU
      RETURN
C INFEASIBILITY.
  160 JRSU = 0
      VRS = - 1
      RETURN
      END
      SUBROUTINE YDEF(L,I,J,NY)
C
C SET  Y(L,I,J) = NY .
C
      INTEGER       Y
      COMMON /PACK/ MASK1(30),ITWO(30),MASK,Y(150,100)
      IYLJ = Y(L,J)
      IMASK1 = MASK1(I)
      Y(L,J) = JIAND(IYLJ,IMASK1) + NY*ITWO(I)
      RETURN
      END
      SUBROUTINE YUSE(L,I,J,NY)
C
C SET  NY = Y(L,I,J) .
C
      INTEGER       Y
      COMMON /PACK/ MASK1(30),ITWO(30),MASK,Y(150,100)
      IYIT = Y(L,J)/ITWO(I)
      IMASK = MASK
      NY = JIAND(IYIT,IMASK)
      RETURN
      END
