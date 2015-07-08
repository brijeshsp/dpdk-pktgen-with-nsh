package.path = package.path ..";?.lua;test/?.lua;app/?.lua;"

printf(":: First Lua File ::\n");

printf("Lua Version      : %s\n", pktgen.info.Lua_Version);
printf("Pktgen Version   : %s\n", pktgen.info.Pktgen_Version);
printf("Pktgen Copyright : %s\n", pktgen.info.Pktgen_Copyright);
printf("Pktgen Authors   : %s\n", pktgen.info.Pktgen_Authors);

pktgen.capture("all","enable");
pktgen.capture("all","on");

pktgen.delay(100000);

pktgen.capture("all","off");

pktgen.quit();
