#include "contiki.h"
#include "net/ipv6/uip-ds6.h"
#include "net/routing/rpl-lite/rpl.h"
#include "sys/log.h"
#include <stdio.h>

#define LOG_MODULE "RPL-Security"
#define LOG_LEVEL LOG_LEVEL_INFO

PROCESS(rpl_security_process, "RPL Security Process");
AUTOSTART_PROCESSES(&rpl_security_process);

PROCESS_THREAD(rpl_security_process, ev, data)
{
  static struct etimer timer;
  PROCESS_BEGIN();

  LOG_INFO("RPL Security Project - Starting...\n");
  

if(linkaddr_node_addr.u8[LINKADDR_SIZE-1] == 1) {
  uip_ipaddr_t root_ipaddr;
  uip_ip6addr(&root_ipaddr, 0xaaaa,0,0,0,0,0,0,1);  
  
  rpl_dag_root_set_prefix(&root_ipaddr, NULL);
  
  rpl_dag_root_start();
  
  LOG_INFO("This mote is the RPL DAG root!\n");
}

  etimer_set(&timer, CLOCK_SECOND * 10);

  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

    rpl_dag_t *dag = rpl_get_any_dag();

    if(dag != NULL) {
      rpl_parent_t *parent = dag->preferred_parent;

      LOG_INFO("Mote %u - DAG ID: ", linkaddr_node_addr.u8[LINKADDR_SIZE - 1]);

      LOG_INFO_6ADDR(&dag->dag_id);
      LOG_INFO_(" | Rank: %u", dag->rank);

      if(parent != NULL) {
        LOG_INFO_(" | Preferred parent rank: %u", parent->rank);
      } else {
        LOG_INFO_(" | No preferred parent");
      }

      LOG_INFO_("\n");
    } else {
      LOG_INFO("Mote %u - No RPL DAG joined\n",
               linkaddr_node_addr.u8[LINKADDR_SIZE - 1]);
    }

    etimer_reset(&timer);
  }

  PROCESS_END();
}

