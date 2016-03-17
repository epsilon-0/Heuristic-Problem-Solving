% This is included in every cweb file of this program.
% This file is in the public domain.
\def\etal{{\it et al}}
\def\ie{\hbox{\it i.e.}}
\def\eg{\hbox{\it e.g.}}
\def\etc{{\it etc}}
\def\br{\hfill\penalty-10000\relax}
\def\module#1{{\sc #1}}
\def\file#1{{\tt #1}}
\def\instance#1{{\tt #1}}
\def\type#1{{\tt #1}}
\def\term#1{{\sl #1}}
\def\implies{\Rightarrow}
\def\iff{\Leftrightarrow}
\def\CWEB/{{\mc CWEB\spacefactor1000}}% Imitate the macros for \CEE/, etc.
\def\ML/{{\mc ML\spacefactor1000}}
\def\cost{\hbox{\it cost}}
\def\emphpar#1\par{{\medskip\narrower\noindent\relax #1\medskip}}
\def\centrepar#1{{\medskip\noindent\hbox{}\hfill\relax#1\relax\hfill{}\hbox{}%
\medskip}}
\def\book#1{{\sl #1}}
\def\mod{{\rm mod}}
\def\size#1{\,\mid\!#1\!\mid\,}
% The following are used in ifs.w for the list of characteristics of a
% fractal.
%\def\itempar#1{{\leftskip=100pt\rightskip=100pt\noindent\relax #1}}
\def\unnarrow{\advance\leftskip by -\parindent\advance\rightskip by -\parindent}
\def\li#1#2\par{\narrower\narrower\noindent\llap{(#1)\enspace}#2\par\unnarrow\unnarrow}
\def\itempar#1{\narrower\relax#1}
\def\itemskip{\smallskip}
\def\emphitemnum#1{({\it#1\/})}
\def\emphitem#1{\quad\quad\quad\llap{\emphitemnum{#1}}\quad}
