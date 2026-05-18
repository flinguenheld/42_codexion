/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:53:04 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 18:12:30 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../data/data.h"
# include "../utils/utils.h"
# include "../scheduler/scheduler.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

/**
 * @brief
 * Parse the given arguments to fill data.
 * @return 0 if ok or the amount of wrong arguments
 */
char	parse(int argc, char **argv, t_data *data);

#endif
