#include "contiki.h"
#include "net/routing/rpl-lite/rpl.h"
#include "net/ipv6/uip-ds6-route.h"
#include "net/linkaddr.h"
#include <stdio.h>

#define MAX_RANK_CHANGE 100

PROCESS(security_monitor_process, "RPL Security Monitor");
AUTOSTART_PROCESSES(&security_monitor_process);

/* ---- Blackhole detection (works in Contiki-NG) ---- */
static uint8_t detect_blackhole(void) {
  int route_count = uip_ds6_route_num_routes();

  if(route_count == 0) {
    printf("SECURITY ALERT: Possible Blackhole detected - no routes!\n");
    return 1;
  }
  return 0;
}

/* ---- Rank attack detection ---- */
static uint8_t detect_rank_attack(rpl_rank_t previous_rank) {
  rpl_dag_t *dag = rpl_get_any_dag();
  if(dag) {
    rpl_rank_t current_rank = dag->rank;   // Contiki-NG valid method

    if(previous_rank > 0 && current_rank < previous_rank - MAX_RANK_CHANGE) {
      printf("SECURITY ALERT: Possible Rank attack - suspicious rank change!\n");
      return 1;
    }
  }
  return 0;
}

PROCESS_THREAD(security_monitor_process, ev, data) {
  static struct etimer monitor_timer;
  static rpl_rank_t previous_rank = 0;

  PROCESS_BEGIN();

  printf("RPL Security Monitor Started on Mote %u\n", linkaddr_node_addr.u8[0]);

  etimer_set(&monitor_timer, CLOCK_SECOND * 15);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&monitor_timer));

    detect_blackhole();

    rpl_dag_t *dag = rpl_get_any_dag();
    if(dag) {
      detect_rank_attack(previous_rank);
      previous_rank = dag->rank;
    }

    printf("Security Status: Monitoring active - Mote %u\n", linkaddr_node_addr.u8[0]);

    etimer_reset(&monitor_timer);
  }

  PROCESS_END();
}
