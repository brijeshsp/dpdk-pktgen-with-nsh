/* Author: Brijesh brip@cisco.com */

#include "pktgen-nsh.h"
#include "pktgen.h"
/**************************************************************************//**
*
* pktgen_nsh_hdr_ctor - IPv4/NSH header construction routine.
*
* DESCRIPTION
* Construct an IPv4/NSH header in a packet buffer.
*
* RETURNS: Pointer to memory after the NSH header.
*
* SEE ALSO:
*/

char * pktgen_nsh_hdr_ctor(__attribute__ ((unused)) port_info_t * info, pkt_seq_t * pkt, nshIp_t * nsh)
{
        // Zero out the header space
        memset((char *)nsh, 0, sizeof(nshIp_t));

        // Create the IP header
        nsh->ip.vl    	= (IPv4_VERSION << 4) | (sizeof(ipHdr_t) /4);
        nsh->ip.tos     = 0;
        nsh->ip.tlen    = htons(pkt->pktSize - pkt->ether_hdr_size);

        pktgen.ident   	+= 27;          // bump by a prime number
        nsh->ip.ident   = htons(pktgen.ident);
        nsh->ip.ffrag   = 0;
        nsh->ip.ttl     = 64;
        nsh->ip.proto   = PG_IPPROTO_NSH;

        // FIXME don't hardcode
#define nsh_SRC_ADDR    (10 << 24) | (10 << 16) | (1 << 8) | 1
#define nsh_DST_ADDR    (10 << 24) | (10 << 16) | (1 << 8) | 2
        nsh->ip.src              = htonl(nsh_SRC_ADDR);
        nsh->ip.dst              = htonl(nsh_DST_ADDR);
#undef nsh_SRC_ADDR
#undef nsh_DST_ADDR

        nsh->ip.cksum    = cksum(nsh, sizeof(ipHdr_t), 0);

        // Create the nsh header
        nsh->nsh.version 				= 1;
        nsh->nsh.ops_and_mgmt      		= 0;
        nsh->nsh.context_hdr_present 	= 1;       
        nsh->nsh.reservedb_0 			= 0;
        nsh->nsh.length 				= 24;
        nsh->nsh.md_type     			= 3;
        nsh->nsh.next_protocol			= 2;				

		nsh->nsh.service_path_index		= 404;
        
		int count = 0;
        if (nsh->nsh.context_hdr_present) {
            for(count=0; count<4; count++ ){
				nsh->nsh.context_headers[count] = 500;	//metadata values
			}
        }
		else{
			for(count=0; count<4; count++ ){
					nsh->nsh.context_headers[count] = 0;	//metadata values set to zero as context headers irrelevant.
			}
		}

        // 4 * (3 - extra_count) is the amount of bytes that are not used by
        // optional fields, but are included in sizeof(nshIp_t).
        pkt->ether_hdr_size += sizeof(nshIp_t);
        return ((char *)(nsh + 1));
}
