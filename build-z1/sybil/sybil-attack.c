#include "contiki.h"
#include "net/routing/rpl-lite/rpl.h"
#include "net/ipv6/uip-ds6.h"
#include <stdio.h>

PROCESS(sybil_attack_process, "Sybil Attack");
AUTOSTART_PROCESSES(&sybil_attack_process);

PROCESS_THREAD(sybil_attack_process, ev, data) {
  static struct etimer timer;
  PROCESS_BEGIN();
  
  printf("Sybil Attack Started on Mote %u\n", linkaddr_node_addr.u8[0]);
  
  etimer_set(&timer, CLOCK_SECOND * 20);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    
    // Changer d'identité périodiquement (comportement Sybil)
    static uint8_t fake_id = 0;
    linkaddr_t fake_addr;
    fake_addr.u8[0] = fake_id++;
    fake_addr.u8[1] = 0x00;
    
    printf("Sybil: Mote %u pretending to be Mote %u\n", 
           linkaddr_node_addr.u8[0], fake_addr.u8[0]);
    
    etimer_reset(&timer);
  }
  PROCESS_END();
}
