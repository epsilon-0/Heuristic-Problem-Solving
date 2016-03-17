import java.util.*;
import java.lang.*;
import java.io.*;

class Ideone
{
 
 // program to store output in a file in a specified format
 public static void store (String fileName, double[]a,int d,double e) throws FileNotFoundException
 {
  try
  {
   File file = new File(fileName);
   if(!file.exists())
   {file.createNewFile();}
   FileWriter bw = new FileWriter(file.getName(),true);
    //BufferedWriter bw = new BufferedWriter(writer);
   for ( int i = 0; i < d; i++)
   {
    int x=(int)(Math.round(a[i]));
    //System.out.println(x);
    bw.append(Integer.toString(x)+"\n");
   }
   bw.close();
  }
  catch(IOException ex)
  {
   ex.printStackTrace();
  }
 }
 
 // program to invert a matrix
 public static double[][] invert(double a[][],int d)
 {
  int n = d;
  double x[][] = new double[n][n];
  double b[][] = new double[n][n];
  int index[] = new int[n];
  
  for (int i=0; i<n; ++i)
  b[i][i] = 1;
 
  gaussian(a, index);
 
  for (int i=0; i<n-1; ++i)
  for (int j=i+1; j<n; ++j)
  for (int k=0; k<n; ++k)
  b[index[j]][k] -= a[index[j]][i]*b[index[i]][k];
 
  for (int i=0; i<n; ++i)
  {
   x[n-1][i] = b[index[n-1]][i]/a[index[n-1]][n-1];
   for (int j=n-2; j>=0; --j)
   {
    x[j][i] = b[index[j]][i];
    for (int k=j+1; k<n; ++k)
    {
     x[j][i] -= a[index[j]][k]*x[k][i];
    }
    x[j][i] /= a[index[j]][j];
   }
  }
  return x;
 }
 
 public static void gaussian(double a[][], int index[])
 {
  int n = index.length;
  double c[] = new double[n];
  
  for (int i=0; i<n; ++i)
  index[i] = i;
 
  for (int i=0; i<n; ++i)
  {
   double c1 = 0;
   for (int j=0; j<n; ++j)
   {
    double c0 = Math.abs(a[i][j]);
    if (c0 > c1) c1 = c0;
   }
   c[i] = c1;
  }
 
  int k = 0;
  for (int j=0; j<n-1; ++j)
  {
   double pi1 = 0;
   for (int i=j; i<n; ++i)
   {
    double pi0 = Math.abs(a[index[i]][j]);
    pi0 /= c[index[i]];
    if (pi0 > pi1)
    {
     pi1 = pi0;
     k = i;
    }
   }
   int itmp = index[j];
   index[j] = index[k];
   index[k] = itmp;
   for (int i=j+1; i<n; ++i)     
   {
    double pj = a[index[i]][j]/a[index[j]][j];
    a[index[i]][j] = pj;
    for (int l=j+1; l<n; ++l)
    a[index[i]][l] -= pj*a[index[j]][l];
   }
  }
 }

 // program to calculate norm (euclidian distance )
 public static double calculateDistance(double[][] array1,int n,int d)
 {
  double Sum = 0.0;
  for(int i=0;i<d;i++)
  {
   Sum = Sum + (array1[n][i]*array1[n][i]);
  }
  return Math.sqrt(Sum);
 }

 // program to multiply two matrices ( one column and one nxn matrix)
 public static double[] multiply(double[][] a, double[] b,int d)
 {
  int rowsInA = d;
  int columnsInA = d; // same as rows in B
  int columnsInB = d;
  double[] c = new double[rowsInA];
  for (int i = 0; i < rowsInA; i++) 
  {
   for (int j = 0; j < columnsInB; j++) 
   { 
  	c[i] += a[i][j] * b[j];
   }
  }
  return c;
 } 

 //program to return index of maximum value
 public static int maxc (double []a, int len, List<Integer> array)
 {
  int ctr=0;
  //System.out.println("arraylist contents");
  double [] b = new double[150];
  double temp=0;
  int n=len;
  int t=0;
     
  //for(int i=0;i<array.size();i++)
      //System.out.println(array.get(i));
     
  for(int i=0;i<n;i++)
  b[i]=a[i];
  for(int i=0;i<n;i++)
  {
   for(int j=i;j<n;j++)
   if(b[i]>=b[j])
   {
    temp=b[i];
    b[i]=b[j];
    b[j]=temp;
   }
  }
  do
  {
      //System.out.println("array size "+array.size());
    for(int i=0;i<n;i++)
   {
       if(b[n-1]==a[i])
       {t=i;//System.out.println("match: "+t);
       }
   }
      if(array.contains(t))
      {
      ctr++;
      //System.out.println("n:"+n+"ctr:"+ctr);
      if(n!=0)
      {n--;}
      //System.out.println("n:"+n);
      }
      if(!array.contains(t))ctr++;
      //System.out.println(ctr);
      
  }
  while(ctr!=(array.size()+1) && !array.isEmpty());
     
  return t;
 }

 //program to return index of minimum value
 public static int minc (double []a, int len,List<Integer> array)
 {
  double min=a[0];
  int n=len;
  int t=0;
  for(int i=1;i<n;i++)
  {
   if(a[i]<=min)
   {t=i;min=a[i];}
  }
  return t;
 }
 
 //program to check if the solution is valid
 public static int check (double []b,int d, double e)
 {
  int n=d;
  int c=0;
  for(int i=0;i<n;i++)
  {
   double x=(b[i]-(int)b[i]);
   //System.out.println(x+" "+e);
   if((b[i]-(int)b[i])>e)
   {c++;//System.out.println("if the value isn't within small jiggle");
   }//if the value isn't within small jiggle
  }
  //System.out.println(c);
  return c;
 }
    
 //calls check
 public static int checksol (double[][]b, double[][]x,int t1,int d, double e)
 {
  double c[]=new double[150];
  double b1[]=new double[150];
  for (int i=0;i<d;i++)
  b1[i]=b[t1][i];
  c=multiply(x,b1,d);
  int d1=check(c,d,e);
  if(d1>(0.5*d))
  return 0; // fail
  else
  return 1; //success
 }
 
 //verification
 public static void checksol2 (String s,double[][]b, double[][]x,int t1,int d, double e) throws FileNotFoundException
 {
  double c[]=new double[150];
  double b1[]=new double[150];
  for (int i=0;i<d;i++)
  b1[i]=b[t1][i];
  c=multiply(x,b1,d);
  //for(int i=0;i<d;i++)
  //System.out.println(c[i]);
  store(s,c,d,e);
 }
 
 //calculates jiggle
 public static double calcepsilon(double[][]b, double[][]x,int t1,int d)
 {
  double c[]=new double[150];
  double b1[]=new double[150];
  for (int i=0;i<d;i++)
  b1[i]=b[t1][i];
  c=multiply(x,b1,d);
  double sum1=0;
  int n=d;
  //double sum1=0;
  for(int i=0;i<n;i++)
  {
  //System.out.println(b[i]-(int)b[i]);
   double x1=(c[i]-(int)c[i]);
   sum1+=x1;
  }
  return(sum1/n);
 }

 public static void main (String[] args) throws java.lang.Exception
 {
  int counter=0,globalcheck=0,f=0,l=0,k=0,d=0,c5=0,flag=0,tick=1,k12=0;
  double e=0.0002;
  //List<Integer> maxcount = new ArrayList<Integer>();
  double [] distance =new double[150];
  double [][]x=new double[150][150];
  double [][]a1=new double[150][150];
  double [][]a2=new double[150][150];
  double [][]a=new double[150][150];
  int exclude[] = new int[150];
     
  String [] items=new String[40000];
  
  try
  {
  // System.out.println("input");
   File file = new File(args[0]);
   Scanner scanner = new Scanner(file);
   String line;
   while (scanner.hasNextLine())
   {
    line = scanner.nextLine();
    items = line.split(" "); 
    if(c5==0)
    {
     for(int i=0;i<items.length-1;i++)
     {
      d=Integer.parseInt(items[i]);
      //n=Integer.parseInt(items[i+1]);}	
     }
    }
    if(c5>0)
    {
     for(int i=0;i<items.length;i++)
     {
      {a1[k][i]=Integer.parseInt(items[i]);}	
     }
     k++;
    }
    c5++; 
   }
   scanner.close(); 
  }  
  
  catch (IOException e1)
  {
   System.out.println("exception");
   e1.printStackTrace();
  }
  
  for(int i=0;i<d;i++)
  {
   exclude[i]=d+1;
   for(int j=0;j<d;j++)
   {a[i][j]=a1[i][j];a2[i][j]=a1[i][j];}
  }
  x=invert(a1,d);
  
  int sumlength;
  List<Integer> maxcount = new ArrayList<Integer>();
  long t11 = System.currentTimeMillis();
  long t21=0;
  do
  {
   //System.out.println("here2");
   //System.out.println("do loop 1");
   int t1=d+1;
   int t2=d+1;
   counter++;
   
   for(int i=0;i<d;i++)
   { 
    distance[i]=calculateDistance(a,i,d);
    //System.out.println(distance[i]);
    //System.out.println(i+" "+distance[i]);
   }
   //System.out.println("\n");
      
   sumlength=d;
   
   t1=maxc(distance,sumlength,maxcount);
   t2=minc(distance,sumlength,maxcount);
   
   //System.out.println("t1 "+t1);
   //System.out.println("t2 "+t2);
   //keeping track of modified array rows
   
    if(maxcount.isEmpty()){maxcount.add(t1);}
    else{
    if(!maxcount.contains(t1))
   {maxcount.add(t1);//System.out.println("added to list");
   }
    }
  
   //l++;
   int check2=1;
   do
   {
   	
    //System.out.println("here1");
    f=1;
    do
    {
     int i3=0;
     //System.out.println("0 "+a[t1][i]);
     //System.out.println("here");
     for(i3=0;i3<d;i3++)
     {a[t1][i3]-=f*a[t2][i3];
         //System.out.println("1 "+a[t1][i3]);
     }
     double d1=calculateDistance(a,t1,d);
     //System.out.println("d1 "+d1);
     for(i3=0;i3<d;i3++)
     {a[t1][i3]-=-1*f*a[t2][i3];
         //System.out.println("2 "+a[t1][i3]);
     }
     for(i3=0;i3<d;i3++)
     {a[t1][i3]-=-1*f*a[t2][i3];
         //System.out.println("3 "+a[t1][i3]);
     }
     double d2=calculateDistance(a,t1,d);
     //System.out.println("d2 "+d2);
     for(i3=0;i3<d;i3++)
     {a[t1][i3]-=f*a[t2][i3];
         //System.out.println("4 "+a[t1][i3]);
     }
     if(d1>=d2)
     flag=1;
     else
     flag=0;
     if(flag==1)
     {
      int i=0;
      for(i=0;i<d;i++)
      {a[t1][i]-=-1*f*a[t2][i];
          //System.out.println("5 "+a[t1][i]);
      }
     }
     else
     {
      int i=0;
      for(i=0;i<d;i++)
      {a[t1][i]-=f*a[t2][i];
          //System.out.println("6 "+a[t1][i]);
      }
     }
     //if(tick==1)
     {
      e=calcepsilon(a,x,t1,d);
     //tick++;
     }
     check2=checksol(a,x,t1,d,e);
     //System.out.println("check2 "+check2);
     f++;
     k12=(int)(e*d);
    }while(check2!=0);
    f--;
    if(flag==1)
    {
     for(int i=0;i<d;i++)
     a[t1][i]+=f*a[t2][i];
    }
    else
    {
     for(int i=0;i<d;i++)
     a[t1][i]+=-1*f*a[t2][i];
    }
    //System.out.println("done "+t1);
   }
   while(check2!=0); // check hasn't failed
   globalcheck+=1;
  
  }
  while(globalcheck<=d); // condition fails
 
  for(int i=0;i<d;i++)
  {
   distance[i]=calculateDistance(a,i,d);
   //System.out.println(distance[i]);
  }
  int y=minc(distance,d,maxcount); // this is the shortest vector
  //System.out.println(" y "+e);
  checksol2(args[1],a,x,y,d,e);
 }
}
