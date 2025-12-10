/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemenen <bsemenen@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:53 by bsemenen          #+#    #+#             */
/*   Updated: 2025/12/10 00:25:00 by bsemenen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
       #include <stdlib.h>
       #include <stdio.h>
#include <string.h>
       int
       main(int argc, char *argv[])
       {
           int flags, opt;
           int nsecs, tfnd;

           nsecs = 0;
           tfnd = 0;
           flags = 0;
           while ((opt = getopt(argc, argv, "nt:")) != -1) {
               switch (opt) {
               case 'n':
                   flags = 1;
                   break;
               case 't':
                   nsecs = atoi(optarg);
                   tfnd = 1;
                   break;
               default: /* '?' */
                   fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                           argv[0]);
                   exit(EXIT_FAILURE);
               }
           }
			

           printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d\n",
                   flags, tfnd, nsecs, optind);

           if (optind >= argc) {
               fprintf(stderr, "Expected argument after options\n");
				printf("argc: %d\n", argc);

               exit(EXIT_FAILURE);
           }
		
		printf("name argument = %s\n", argv[optind]);
		   /* Other code omitted */
		printf("argc: %d\n", argc);
           exit(EXIT_SUCCESS);
       }
