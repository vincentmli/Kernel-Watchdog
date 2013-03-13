#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

main ()
{
  time_t now;
  size_t count;

  time(&now);
  printf("%s", ctime(&now));

  char *timestamp = ctime(&now);

  FILE *ofp;
  char *outputFilename = "/var/log/lockupcli.log";


  ofp = fopen(outputFilename, "a");

  if (ofp == NULL) {
     fprintf(stderr, "Can't open output file %s!\n", outputFilename);
     exit(1);
  }

  fprintf(ofp, "executed lockupcli at: %s\n", timestamp);

  fsync((int)ofp);
  fsync((int)ofp);

  fclose(ofp);

  printf("sleep 5 seconds to save log file to disk\n" );
  sleep(5);
  printf("starting clear interrupt flag loop\n" );

  //cpu i/o privilege level 0 - 2
  iopl(3);
  //clear interrupt flag
  for (;;) { asm("cli"); }

}
