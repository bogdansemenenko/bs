/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mygrep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsemenen <bsemenen@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:25:47 by bsemenen          #+#    #+#             */
/*   Updated: 2025/12/10 03:57:23 by bsemenen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

//this shit is mandatory you nees this for errors ouputs use this as example
void usage(char *msg){

	fprintf(stderr, "%s\nUsage: mygrep [-i] [-o outfile] keyword [file...]", msg);
	exit(EXIT_FAILURE);

}

void error(char *msg){

	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int opt; // to start getopt
	int flag_i = 0; // those are just flag and thats it you switch them so
	int flag_o = 0; // there wouldnt be more than one option (e.g -i -i repeated 
					// are not allowed)
	FILE* output = stdout; // your standart output where you put your answer
	while ((opt = getopt(argc, argv, "io:")) != -1) // your options are given as characters
	{												// here are "io", ":" is for other options 
		switch (opt)
		{
		case 'i':									// this shit is for strcasestr because it doesnt differentiate
			if(flag_i)								// from lowercase and uppercase
				usage("too many options");
			flag_i = 1;								// here we switch flag so if they are repeated it would fail you
			break ;
		case 'o':
			if(flag_o)
				usage("too many options");
			flag_o = 1;
			output = fopen(optarg, "w+");			//this if -o option is given it will output it in given file 
			if(!output)								//optarg "w+" is for Writing into fila and + gives permission for reading it
				error(optarg);						//also a mandatory check if open fails
			break ;
		default: /* '?' */
			usage("invalid opt");
		}
	}
	if (optind >= argc)								//optind - points at the first occurance of argument after option in our case now this is keyword
		usage("you forgot an argument");	
	char *keyword = argv[optind++];					//initializing our keyword and go to next argument -> file1 

	while(optind < argc)							// we go through each argument file1 fil2 and so on
	{
		FILE* input = NULL;							
		if((argc - optind) == 0){					// if after keyword we dont find any name for file we requesting STANDART INPUT
			input = stdin;
		}else{
			input = fopen(argv[optind], "r");		// in case of existing checking file, setting to input and checking if it exists
			if(!input)
				error("fopen");
		}
	char *line = NULL;								// here we are cheking wheather keyword in any of files 
	size_t len = 0;										
		while (getline(&line, &len, input) != -1)	// if line anf len are set to NULL and zero getline automaticaly(if you can say that) allocates buffer BUT 
			{										// IT SHOULD BE FREED AT THE END!!	man 3 getline
				line[strlen(line) - 1] = '\0';		// this one excludes new line from parsed line can be avoid just dont add \n when you print it 
				if((strcasestr(line, keyword)) && flag_i) // this for -i flag 
				{
					fprintf(output, "%s\n", line);
	
				}else if(strstr(line, keyword)){			// no -i flag
					fprintf(output, "%s\n", line);
				}
			}
	free(line);							// free line
	fclose(input);						// close your input 
	optind++;							// loop in while (optind++ < argc)
	}
	fclose(output);						// cloeses output
	/* Other code omitted */
	exit(EXIT_SUCCESS);					// exit succ 
}
