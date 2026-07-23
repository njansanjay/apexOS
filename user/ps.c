#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static const char *state_names[] = {
  [0] = "UNUSED  ",
  [1] = "USED    ",
  [2] = "SLEEPING",
  [3] = "RUNNABLE",
  [4] = "RUNNING ",
  [5] = "ZOMBIE  "
};

int
main(int argc, char *argv[])
{
  struct proc_info info[64];
  int count, i;

  count = procinfo(info, 64);
  if (count < 0) {
    printf("ps: failed to get process telemetry\n");
    exit(1);
  }

  printf("\n=== apexOS Process Manager ===\n");
  printf("PID\tPPID\tSTATE\t\tSIZE\t\tNAME\n");
  printf("-----------------------------------------------------------\n");

  for (i = 0; i < count; i++) {
    const char *st = "UNKNOWN ";
    if (info[i].state >= 0 && info[i].state <= 5) {
      st = state_names[info[i].state];
    }
    uint kb = (uint)(info[i].sz / 1024);
    printf("%d\t%d\t%s\t%d KB\t\t%s\n",
           info[i].pid,
           info[i].ppid,
           st,
           kb,
           info[i].name);
  }

  printf("-----------------------------------------------------------\n");
  printf("Total Active Processes: %d\n\n", count);

  exit(0);
}
