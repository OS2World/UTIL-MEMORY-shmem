// JvW 22-04-2002  initial version
// JvW 25-04-2002  allow multiple (smaller) blocks
// JvW 28-04-2002  added "-hold" to "-test" and made -"test" default for ALL
// JvW 03-05-2002  Made 'all' the default parameter and renamed to SHMEM
// JvW 13-05-2002  Update to allow smaller memory fragments (more accurate)

#include <tplib.h>

#define KB_32   ((ULONG)   32 * 1024)
#define ONE_MB  ((ULONG) 1024 * 1024)


// Show usage of the SHMEM program
void shmemUsage
(
   char               *program                  // IN    program name
);

int main (int argc, char *argv[]);

/*****************************************************************************/
// Main function, entry point
/*****************************************************************************/
int main (int argc, char *argv[])
{
   APIRET              rc;
   ULONG               size = 0;

   TpaParseArgcArgv( argc, argv, TRUE, NULL);   // parse cmdline, free format

   if (strcmp( TpaExeArgv(1), "-") != 0)
   {
      Tprintf( "\n%s 1.4  Display/Eat shared memory.  "
               "(c) 2002  Fsys Software; Jan van Wijk\n", argv[0]);
   }
   if ( TpaExeMutEx( FALSE, "th", "", NULL) &&  // no option problem
       !TpaExeSwitch('?'))                      // and no help requested
   {
      MBUF             tstamp;
      time_t           tt = time( &tt);         // current date/time

      strftime( tstamp, MAXMBUF, "%A %d-%m-%Y %H:%M:%S", localtime( &tt));


      if (TpaExeArgc() > 1)                     // size of 'all' specified
      {
         sscanf( TpaExeArgv(1),"%lu", &size);
      }
      else                                      // no parameter, do 'all'
      {                                         // and show usage anyway
         shmemUsage( argv[0]);
      }

      if ((TpaExeSwitch('s')) && (size != 0))   // single block
      {
         PBYTE         pb;

         Tprintf( "%s - Allocate one block of %lu Mb shared memory.\n",
                        tstamp, size);

         rc = DosAllocSharedMem((PVOID *) &pb,
                                (PSZ) NULL,     // unnamed
                                 size * ONE_MB, // amount of memory
                                 fALLOCSHR);    // shareable memory
         if (rc == NO_ERROR)
         {
            Tprintf( "Success, ");

            if (TpaExeSwitch('h'))              // hold memory until key ...
            {
               Tprintf( "Press any key to free it again ...");
               getch();
            }
            DosFreeMem(pb);                     // Free the object
            Tprintf( "  Memory released!\n");
         }
         else
         {
            Tprintf( "\nError %lu allocating %lu Mb of shared memory\n", rc, size);
         }
      }
      else                                      // 1Mb blocks, possibly ALL
      {
         PBYTE        *blocks = NULL;           // array of pointers
         ULONG         i;
         ULONG         allocated = 0;
         BOOL          hold;
         SBUF          sizetxt;
         ULONG         bsize;
         ULONG         bcount;

         if (TpaOption('k'))                    // use 128 Kb blocks
         {
            strcpy( sizetxt, "128 Kb");
            bsize  = 4;
            bcount = 8;
         }
         else
         {
            strcpy( sizetxt, "1   Mb");
            bsize  = 32;
            bcount = 1;
         }

         if (size == 0)                         // max-size, default test
         {
            size = 4096;
            hold =  TpaOption('h');             // "-hold"
         }
         else                                   // explicit size, default hold
         {
            hold = !TpaOption('t');             // no "-test"
         }

         if ((blocks = TpAlloc( (size * bcount), sizeof(PBYTE))) != NULL)
         {
            for (i = 0; i < (size * bcount); i++)
            {
               rc = DosAllocSharedMem((PVOID *) &(blocks[i]),
                                      (PSZ) NULL, // unnamed
                                       bsize * KB_32,  // amount of memory
                                       fALLOCSHR); // shareable memory
               if (rc == NO_ERROR)
               {
                  allocated++;
               }
            }
            if (allocated != 0)              // at least one ?
            {
               double  megabytes = ((double)(allocated * bsize)) / 32;

               if (hold == TRUE)                // hold until key ...
               {
                  Tprintf( "%s - % 4lu %s blocks = %5.1lf Mb allocated.\n"
                           "Press any key to free it again ...\n",
                            tstamp, allocated, sizetxt, megabytes);
                  getch();
               }
               for (i = 0; i < (size * bcount); i++)
               {
                  if (blocks[i] != NULL)
                  {
                     DosFreeMem( blocks[i]);    // Free each block
                  }
               }
               if (hold == TRUE)
               {
                  Tprintf( "  Memory released!\n");
               }
               else
               {
                  Tprintf( "%s - % 4lu %s blocks = %5.1lf Mb available.\n",
                           tstamp, allocated, sizetxt, megabytes);
               }
            }
            else
            {
               Tprintf( "\nNo shared memory available!\n");
            }
         }
         else
         {
            Tprintf( "\nError allocating normal memory\n");
         }
      }
   }
   else
   {
      shmemUsage( argv[0]);
   }

   TpaDropParsedCommand( TRUE);                 // drop all cmd levels

   return(0);
}                                               // end 'main'
/*---------------------------------------------------------------------------*/

/*****************************************************************************/
// Show usage of the SHMEM program
/*****************************************************************************/
void shmemUsage
(
   char               *program                  // IN    program name
)
{
   Tprintf( "\nUsage: %s  [all | nr-of-megabytes]\n", program);

   Tprintf( "\nOptions:   -     Display 'all' shared memory, no usage\n"
              "           -s    allocate in one single block\n"
              "           -k    use 128 Kb blocks instead of 1 Mb\n"
              "           -h    hold memory until key pressed ...\n"
              "           -t    test only, no wait ...\n");

   Tprintf( "\n           When no parameters are given, 'all' is asumed\n"
              "           resulting in a display of all available shared\n"
              "           memory and this usage text...\n");

   Tprintf( "\n           Note: '-t' is default for 'all' memory, and\n"
              "                 '-h' is default for explicit sizes.\n"
              "                      They are mutually exclusive.\n\n");
}                                               // end 'shmemUsage'
/*---------------------------------------------------------------------------*/

