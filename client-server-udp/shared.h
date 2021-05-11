#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

const int buffer_size = 1024;

static FILE *udp_connect(const char *hostname, const char *port);
static FILE *create_server(const char *port);

struct conninfos
{
  char ip[INET_ADDRSTRLEN];
  char port[6];
  in_port_t rawport;
};

struct conninfos *getconninfos(struct addrinfo *rp)
{
  char ipname[INET_ADDRSTRLEN];
  char servicename[6]; // "65535\0"

  if (!getnameinfo(rp->ai_addr,
                   rp->ai_addrlen,
                   ipname,
                   sizeof(ipname),
                   servicename,
                   sizeof(servicename),
                   NI_NUMERICHOST | NI_NUMERICSERV))
  {

    struct conninfos *infos = malloc(sizeof(struct conninfos));
    infos->rawport = -1;

    if (rp->ai_family == AF_INET)
    {
      infos->rawport = ((struct sockaddr_in *)rp->ai_addr)->sin_port;
    }

    strcpy(infos->port, servicename);
    strcpy(infos->ip, ipname);

    return infos;
  }

  return NULL;
}
