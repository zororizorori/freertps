#include <stdio.h>
#include "freertps/freertps.h"
#include <signal.h>

static bool g_done = false;
void sigint_handler(int signum)
{
  g_done = true;
}

void chatter_cb(const void *msg)
{
  printf("chatter_cb\n");
}

int main(int argc, char **argv)
{
  frudp_init();
  freertps_create_subscription("chatter", 
                               "simple_msgs::dds_::String_",
                               chatter_cb);
  signal(SIGINT, sigint_handler);
  while (!g_done)
  {
    if (!frudp_listen(1000))
      break;
    frudp_discovery_tick();
  }
  frudp_fini();
  return 0;
}
