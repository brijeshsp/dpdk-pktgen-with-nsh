package.path = package.path ..";?.lua;test/?.lua;app/?.lua;"

printf(":: Transmitting packet Lua File ::\n");

pktgen.start("all");

pktgen.delay(1000);

pktgen.stop("all");

printf("\nTransmitted\n");

