/* Author: Brijesh brip@cisco.com */
/* The NSH header */

#ifndef _PKTGEN_NSH_H_
#define _PKTGEN_NSH_H_

#include <wr_inet.h>

#include "pktgen-port-cfg.h"
#include "pktgen-seq.h"


extern char * pktgen_nsh_hdr_ctor(port_info_t * info, pkt_seq_t * pkt, nshIp_t * nsh);

#endif  // _PKTGEN_NSH_H_

