      SUBROUTINE MTHG(N,M,P,W,C,MINMAX,Z,XSTAR,JCK)
C
C THIS SUBROUTINE HEURISTICALLY SOLVES THE GENERALIZED ASSIGNMENT
C PROBLEM
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
C AND IMPLEMENTS THE POLYNOMIAL-TIME ALGORITHMS DESCRIBED
C IN SECTION  7.4 .
C
C THE INPUT PROBLEM MUST SATISFY THE CONDITIONS
C
C   1) 2 .LE. M .LE. JDIMR ;
C   2) 2 .LE. N .LE. JDIMC ;
C      ( JDIMR  AND  JDIMC  ARE DEFINED BY THE FIRST TWO EXECUTABLE
C       STATEMENTS;)
C   3) P(I,J), W(I,J) AND C(I) POSITIVE INTEGERS;
C   4) W(I,J) .LE. C(I) FOR AT LEAST ONE I, FOR J=1,...,N;
C   5) C(I) .GE. MIN (W(I,J)) FOR I=1,...,M.
C
C MTHG CALLS 6 PROCEDURES: CHMTHG, FEAS, GHA, GHBCD, GHX AND TRIN.
C
C THE PROGRAM IS COMPLETELY SELF-CONTAINED AND COMMUNICATION TO IT IS
C ACHIEVED SOLELY THROUGH THE PARAMETER LIST OF MTHG.
C NO MACHINE-DEPENDENT CONSTANT IS USED.
C THE PROGRAM IS WRITTEN IN 1967 AMERICAN NATIONAL STANDARD FORTRAN
C AND IS ACCEPTED BY THE PFORT VERIFIER (PFORT IS THE PORTABLE
C SUBSET OF ANSI DEFINED BY THE ASSOCIATION FOR COMPUTING MACHINERY).
C THE PROGRAM HAS BEEN TESTED ON A DIGITAL VAX 11/780 AND AN H.P.
C 9000/840.
C
C MTHG NEEDS
C   6 ARRAYS ( C ,  DMYR1 ,  DMYR2 ,  DMYR3 ,  DMYR4  AND  DMYR5 ) OF
C              LENGTH AT LEAST  JDIMR ;
C   7 ARRAYS ( XSTAR ,  BEST ,  DMYC1 ,  DMYC2 ,  DMYC3 ,  DMYC4  AND
C              DMYCR1 ) OF LENGTH AT LEAST  JDIMC ;
C   3 ARRAYS ( P ,  W  AND  A ) OF LENGTH AT LEAST  JDIMR X JDIMC .
C
C THE ARRAYS ARE CURRENTLY DIMENSIONED TO ALLOW PROBLEMS FOR WHICH
C       M .LE. 50 ,
C       N .LE. 500 
C (SO, IN THE CALLING PROGRAM, ARRAYS  P  AND  W  MUST BE DIMENSIONED
C AT  (50,500) ). CHANGING SUCH LIMITS NECESSITATES CHANGING THE 
C DIMENSION OF ALL THE ARRAYS IN SUBROUTINE MTHG, AS WELL AS THE FIRST 
C TWO EXECUTABLE STATEMENTS.
C
C MEANING OF THE INPUT PARAMETERS:
C N        = NUMBER OF ITEMS;
C M        = NUMBER OF KNAPSACKS;
C P(I,J)   = PROFIT OF ITEM J IF ASSIGNED TO KNAPSACK I
C            (I=1,...,M; J=1,...,N);
C W(I,J)   = WEIGHT OF ITEM J IF ASSIGNED TO KNAPSACK I
C            (I=1,...,M; J=1,...,N);
C C(I)     = CAPACITY OF KNAPSACK I (I=1,...,M);
C MINMAX   = 1 IF THE OBJECTIVE FUNCTION MUST BE MINIMIZED,
C          = 2 IF THE OBJECTIVE FUNCTION MUST BE MAXIMIZED;
C JCK      = 1 IF CHECK ON THE INPUT DATA IS DESIRED,
C          = 0 OTHERWISE.
C
C MEANING OF THE OUTPUT PARAMETERS:
C Z        = VALUE OF THE SOLUTION FOUND IF Z .GT. 0 ,
C          = 0 IF NO FEASIBLE SOLUTION IS FOUND,
C          = ERROR IN THE INPUT DATA (WHEN JCK=1) IF Z .LT. 0 : CONDI-
C            TION  - Z  IS VIOLATED;
C XSTAR(J) = KNAPSACK WHERE ITEM J IS INSERTED IN THE SOLUTION FOUND.
C
C ALL THE PARAMETERS ARE INTEGER. ON RETURN OF MTHG ALL THE INPUT
C PARAMETERS ARE UNCHANGED, BUT  P(I,J)  IS SET TO  0  FOR ALL PAIRS
C (I,J)  SUCH THAT  W(I,J) .GT. C(I) .
C
      INTEGER P(50,500),W(50,500),C(50),XSTAR(500),Z
      INTEGER ZM
      INTEGER BEST(500)
      INTEGER A(50,500)
      INTEGER DMYR1(50),DMYR2(50),DMYR3(50),DMYR4(50),DMYR5(50)
      INTEGER DMYC1(500),DMYC2(500),DMYC3(500),DMYC4(500)
      REAL    DMYCR1(500)
C
C DEFINITION OF THE INTERNAL PARAMETERS.
C
      JDIMR = 50
      JDIMC = 500
      Z = 0
      IF ( JCK .EQ. 1 ) CALL CHMTHG(N,M,P,W,C,JDIMR,JDIMC,Z)
      IF ( Z .LT. 0 ) RETURN
C
C INITIALIZE.
C
      INVST = 0
      IMULT = - 1
      IF ( MINMAX .EQ. 2 ) GO TO 10
C TRANSFORM THE MINIMIZATION PROBLEM INTO A MAXIMIZATION PROBLEM.
      CALL TRIN(P,N,M,INVST,LAM,JDIMR,JDIMC)
      IMULT = 1
C
C SOLVE THE MAXIMIZATION PROBLEM.
C
C CHECK FOR INFEASIBILITY.
   10 CALL FEAS(N,M,P,W,C,XSTAR,JFI,JDIMR,JDIMC)
      IF ( JFI .EQ. 1 ) GO TO 30
C FIRST HEURISTIC SOLUTION.
      CALL GHA(P,W,C,N,M,Z,XSTAR,IUB,BEST,KVST,INF,
     1         JDIMR,JDIMC,DMYR1,DMYR2,DMYC1,DMYC2,DMYC3,DMYC4)
      IF ( Z .EQ. IUB ) GO TO 20
C SECOND HEURISTIC SOLUTION.
      CALL GHBCD(P,W,C,N,M,Z,XSTAR,INF,
     1           JDIMR,JDIMC,DMYC1,DMYR1,DMYR2,DMYR3,DMYR4,DMYR5,
     2           DMYC2,DMYC3,DMYC4,DMYCR1,A)
C
C TERMINATE.
C
   20 ZM = Z
      Z = 0
      IF ( ZM .GT. KVST ) Z = INVST - ZM*IMULT
   30 IF ( MINMAX .EQ. 2 ) RETURN
C RE-STORE THE ORIGINAL MINIMIZATION PROBLEM.
      DO 50 I=1,M
        DO 40 J=1,N
          IF ( P(I,J) .GT. 0 ) P(I,J) = LAM - P(I,J)
   40   CONTINUE
   50 CONTINUE
      RETURN
      END
      SUBROUTINE CHMTHG(N,M,P,W,C,JDIMR,JDIMC,Z)
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
      DO 40 I=1,M
        IF ( C(I) .GT. 0 ) GO TO 10
        Z = - 3
        RETURN
   10   MIN = C(I) + 1
        DO 30 J=1,N
          IF ( P(I,J) .GT. 0 .AND. W(I,J) .GT. 0 ) GO TO 20
          Z = - 3
          RETURN
   20     IF ( W(I,J) .LT. MIN ) MIN = W(I,J)
   30   CONTINUE
        IF ( C(I) .LT. MIN ) Z = - 5
   40 CONTINUE
      DO 60 J=1,N
        DO 50 I=1,M
          IF ( W(I,J) .LE. C(I) ) GO TO 60
   50   CONTINUE
        Z = - 4
        RETURN
   60 CONTINUE
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
