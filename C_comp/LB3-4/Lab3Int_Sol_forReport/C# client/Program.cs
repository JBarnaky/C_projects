using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Lb3Ind_autosvrLib;


namespace DotNewClient_lb3Ind
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Lb3Ind_autosvr.MyInd.1");
            var obj = new CoMyInd();
            IMyInd ind = obj;
            float result = ind.Fun151(22, 11);
            float result2 = ind.Fun152(10, 4, 2);
            double result3 = ind.Fun153(1.5);

            Console.WriteLine(String.Format("Fun151: 22 + 11 = {0}", result));
            Console.WriteLine(String.Format("Fun152: 10 - 4 - 2 = {0}", result2));
            Console.WriteLine(String.Format("Fun153: 1.5 * 1.5 = {0}", result3));
            Console.ReadLine();

            IMyInd_Author indAuthor;
            indAuthor = (IMyInd_Author) ind;
            Console.WriteLine(String.Format("Author: {0}",indAuthor.GetAuthor("Paul Yatskevich")));
           /* wchar_t* result4;
            pMath2->GetAuthor(&result4);
            printf("Author: ");
            wprintf(result4); */


        }
    }
}